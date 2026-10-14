/*
 * Copyright 2026 湖北多样性算力应用创新研究院 (Hubei Institute for Heterogeneous Computing Applications)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CANN_ASC_STL_ASC___ALGORITHM_FRONTEND_H
#define CANN_ASC_STL_ASC___ALGORITHM_FRONTEND_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__algorithm/byte_operations.h>
#include <asc/__parallel/adjacent_difference.h>
#include <asc/__parallel/find.h>
#include <asc/__parallel/for.h>
#include <asc/__parallel/merge.h>
#include <asc/__parallel/merge_sort.h>
#include <asc/__parallel/partition.h>
#include <asc/__parallel/radix_sort.h>
#include <asc/__parallel/reduce.h>
#include <asc/__parallel/scan.h>
#include <asc/__parallel/select.h>
#include <asc/__parallel/temporary_storage.h>
#include <asc/__parallel/transform.h>
#include <asc/__runtime/launch.h>
#include <asc/execution>
#include <asc/execution.policy.h>
#include <asc/std/__functional/operations.h>
#include <asc/std/__type_traits/is_floating_point.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/cstddef>
#include <asc/std/cstdint>

namespace asc::detail {

template <class T>
struct equal_value {
    T value;
    template <class U>
    CANN_ASC_STL_DEVICE_API bool operator()(const U& input) const
    {
        return input == value;
    }
};
template <class Predicate>
struct negated_predicate {
    Predicate predicate;
    template <class T>
    CANN_ASC_STL_DEVICE_API bool operator()(const T& value) const
    {
        return !predicate(value);
    }
};

// True when Compare is one of the asc::std::less specializations, i.e. the
// sort frontend may route natural-order arithmetic keys to the radix kernel.
template <class Compare>
struct natural_order_compare {
    static constexpr bool value = false;
};
template <class T>
struct natural_order_compare<asc::std::less<T>> {
    static constexpr bool value = true;
};

// Grid-stride companions of the element-wise operations live beside their
// families in asc/__parallel/for.h and asc/__parallel/transform.h: each
// device thread visits the elements whose linear index is congruent to its
// thread index modulo the total thread count, so every element is still
// visited exactly once while the launch spans the whole grid.

// Derives a conservative 1-D launch geometry for an element-wise operation
// over count elements. The grid-stride loops absorb any excess, so the caps
// only bound parallelism, never coverage.
CANN_ASC_STL_HOST_API launch_state elementwise_launch_state(__SIZE_TYPE__ count) noexcept
{
    constexpr unsigned int block_threads = 256;
    constexpr unsigned int block_limit = 65535;
    launch_state state{};
    state.threads = count < block_threads ? static_cast<unsigned int>(count) : block_threads;
    if (state.threads == 0) {
        state.threads = 1;
    }
    const __SIZE_TYPE__ blocks_needed = (count + state.threads - 1) / state.threads;
    state.blocks = blocks_needed > block_limit ? block_limit : static_cast<unsigned int>(blocks_needed);
    if (state.blocks == 0) {
        state.blocks = 1;
    }
    return state;
}

#if defined(__clang__) && defined(CANN_ASC_STL_USE_SIMT_LAUNCH)
// Availability gate: every asc::parallel::* frontend in this header exists
// only on __clang__ builds that define CANN_ASC_STL_USE_SIMT_LAUNCH (the CCE
// toolchain contract); the macro is a build-time contract with no in-tree
// default, so a build that omits it compiles the facade to plain includes
// with no parallel names. The registry semantic column is expected to state
// the same availability rule; adding Host fallback stubs that return
// execution_status{execution_errc::unsupported} on other toolchains would
// widen the public surface and stays a product decision.
//
// Result-sink contract, pinned here for all frontends below: the scalar,
// predicate, iterator-position and selected-count results are written to
// explicit caller-owned sinks that must live in device global memory; the
// values become valid in the policy stream's order and are never copied
// through host addresses. Passing a host (stack) pointer to an output
// parameter is a contract violation the frontend does not validate.
template <class Operation>
CANN_ASC_STL_HOST_API execution_status submit(device_policy policy, Operation operation) noexcept
{
    static_assert(__is_trivially_copyable(Operation), "ASC-STL parallel operation state must be trivially copyable");
    execution_status status = validate_parallel_policy(policy);
    return status.success() ? submit_parallel_operation(policy.stream(), operation) : status;
}

// Element-wise submission channel: routes the operation through the
// coordinate-parameterized kernel so pure per-element work runs grid-strided
// across the launch. The routed families are for_each/for_each_n,
// transform, copy/copy_n, fill/fill_n, generate/generate_n, the replace
// family and swap_ranges - all free of cross-element dependencies, so the
// visit order is an implementation detail (stateful callables keep the
// exactly-once-per-element guarantee but not the sequential call order).
// Order- and dependency-sensitive operations (reduce, scan, merge,
// adjacent_difference, find, select, partition and both sorts) intentionally
// keep the single-thread submit channel above: their device-side semantics
// are sequential, and parallelizing them needs the batched plans tracked for
// the later runtime work rather than an unsafe thread fan-out here.
template <class Operation>
CANN_ASC_STL_HOST_API execution_status submit_elementwise(
    device_policy policy, __SIZE_TYPE__ count, Operation operation) noexcept
{
    static_assert(__is_trivially_copyable(Operation), "ASC-STL parallel operation state must be trivially copyable");
    execution_status status = validate_parallel_policy(policy);
    return status.success() ? submit_parallel_operation(policy.stream(), elementwise_launch_state(count), operation) :
                              status;
}

template <class Value>
struct synchronous_slot {
    device_policy backend_policy{};
    Value* device_value{};
    Value host_value{};
    execution_status status{};
};

struct synchronous_indices {
    ::asc::std::size_t values[2]{};
};

template <class Value>
CANN_ASC_STL_HOST_API synchronous_slot<Value> make_synchronous_slot(device_policy policy) noexcept
{
    synchronous_slot<Value> slot{};
    // Shares the null-stream/size validation with the sort frontends through
    // require_temporary_storage instead of duplicating it here.
    execution_status status = require_temporary_storage(policy, sizeof(Value));
    if (!status.success()) {
        slot.status = status;
        return slot;
    }
    temporary_storage_ref storage = policy.temporary_storage();
    const auto begin = reinterpret_cast<__UINTPTR_TYPE__>(storage.data());
    const auto end = begin + storage.size_bytes();
    if (end < begin) {
        slot.status = execution_status{execution_errc::invalid_argument};
        return slot;
    }
    const auto address = (end - sizeof(Value)) & ~static_cast<__UINTPTR_TYPE__>(alignof(Value) - 1);
    if (address < begin) {
        slot.status = execution_status{execution_errc::insufficient_storage};
        return slot;
    }
    slot.backend_policy = policy.with_temporary_storage(
        temporary_storage_ref(storage.data(), static_cast<__SIZE_TYPE__>(address - begin), memory_space::global));
    slot.device_value = reinterpret_cast<Value*>(address);
    return slot;
}

CANN_ASC_STL_HOST_API execution_status finish_synchronous(device_policy policy, execution_status status) noexcept
{
    if (!status.success())
        return status;
    return policy.stream().synchronize() ? execution_status{} : execution_status{execution_errc::backend_error, -1};
}

template <class Value>
CANN_ASC_STL_HOST_API execution_status finish_synchronous(
    device_policy policy, execution_status status, synchronous_slot<Value>& slot) noexcept
{
    if (!status.success())
        return status;
    status = copy_bytes_runtime(
        policy.stream(), &slot.host_value, slot.device_value, sizeof(Value), copy_direction::device_to_host);
    return finish_synchronous(policy, status);
}
#endif

}  // namespace asc::detail

#if defined(__clang__) && defined(CANN_ASC_STL_USE_SIMT_LAUNCH)
namespace asc::parallel {

template <class Input, class Output, class BinaryOperation>
CANN_ASC_STL_HOST_API execution_status adjacent_difference(
    device_policy policy, Input first, Input last, Output result, BinaryOperation operation) noexcept
{
    return detail::submit(
        policy, detail::adjacent_difference_operation<Input, Output, BinaryOperation>{first, last, result, operation});
}

template <class Forward, class BinaryPredicate>
CANN_ASC_STL_HOST_API execution_status adjacent_find(device_policy policy, Forward first, Forward last,
    ::asc::std::size_t* output_index, BinaryPredicate predicate) noexcept
{
    if (output_index == nullptr)
        return execution_status{execution_errc::invalid_argument};
    return detail::submit(
        policy, detail::adjacent_find_operation<Forward, BinaryPredicate>{first, last, output_index, predicate});
}

template <class Input, class UnaryPredicate>
CANN_ASC_STL_HOST_API execution_status all_of(device_policy policy, Input first, Input last,
    ::asc::std::uint32_t* output_value, UnaryPredicate predicate) noexcept
{
    if (output_value == nullptr)
        return execution_status{execution_errc::invalid_argument};
    return detail::submit(policy,
        detail::bool_reduce_operation<Input, UnaryPredicate>{first, last, output_value, predicate, true, false});
}

template <class Input, class UnaryPredicate>
CANN_ASC_STL_HOST_API execution_status any_of(device_policy policy, Input first, Input last,
    ::asc::std::uint32_t* output_value, UnaryPredicate predicate) noexcept
{
    if (output_value == nullptr)
        return execution_status{execution_errc::invalid_argument};
    return detail::submit(policy,
        detail::bool_reduce_operation<Input, UnaryPredicate>{first, last, output_value, predicate, false, false});
}

template <class Input, class Output>
CANN_ASC_STL_HOST_API execution_status copy(
    device_policy policy, Input first, Input last, Output result) noexcept  // NOLINT(build/include_what_you_use)
{
    const __SIZE_TYPE__ count = static_cast<__SIZE_TYPE__>(last - first);
    return detail::submit_elementwise(
        policy, count, detail::grid_strided_copy_operation<Input, Output>{first, count, result});
}

template <class Input, class Output, class UnaryPredicate>
CANN_ASC_STL_HOST_API execution_status copy_if(device_policy policy, Input first, Input last, Output result,
    ::asc::std::size_t* output_count, UnaryPredicate predicate) noexcept
{
    if (output_count == nullptr)
        return execution_status{execution_errc::invalid_argument};
    return detail::submit(policy,
        detail::select_copy_operation<Input, Output, UnaryPredicate>{first, last, result, output_count, predicate});
}

template <class Input, class Size, class Output>
CANN_ASC_STL_HOST_API execution_status copy_n(device_policy policy, Input first, Size count, Output result) noexcept
{
    const __SIZE_TYPE__ total = count > 0 ? static_cast<__SIZE_TYPE__>(count) : 0;
    return detail::submit_elementwise(
        policy, total, detail::grid_strided_copy_operation<Input, Output>{first, total, result});
}

template <class Input, class T>
CANN_ASC_STL_HOST_API execution_status count(
    device_policy policy, Input first, Input last, const T& value, ::asc::std::size_t* output_count) noexcept
{
    if (output_count == nullptr)
        return execution_status{execution_errc::invalid_argument};
    return detail::submit(
        policy, detail::count_operation<Input, detail::equal_value<T>>{first, last, output_count, {value}});
}

template <class Input, class UnaryPredicate>
CANN_ASC_STL_HOST_API execution_status count_if(
    device_policy policy, Input first, Input last, ::asc::std::size_t* output_count, UnaryPredicate predicate) noexcept
{
    if (output_count == nullptr)
        return execution_status{execution_errc::invalid_argument};
    return detail::submit(policy, detail::count_operation<Input, UnaryPredicate>{first, last, output_count, predicate});
}

template <class Input1, class Input2, class BinaryPredicate>
CANN_ASC_STL_HOST_API execution_status equal(device_policy policy, Input1 first1, Input1 last1, Input2 first2,
    Input2 last2, ::asc::std::uint32_t* output_value, BinaryPredicate predicate) noexcept
{
    if (output_value == nullptr)
        return execution_status{execution_errc::invalid_argument};
    return detail::submit(policy,
        detail::equal_operation<Input1, Input2, BinaryPredicate>{
            first1, last1, first2, last2, output_value, predicate});
}

template <class Input, class Output, class T, class BinaryOperation>
CANN_ASC_STL_HOST_API execution_status exclusive_scan(
    device_policy policy, Input first, Input last, Output result, T init, BinaryOperation operation) noexcept
{
    return detail::submit(policy,
        detail::scan_operation<Input, Output, T, BinaryOperation, detail::identity_operation<T>>{
            first, last, result, init, operation, {}, false});
}

template <class Forward, class T>
CANN_ASC_STL_HOST_API execution_status fill(device_policy policy, Forward first, Forward last, const T& value) noexcept
{
    const __SIZE_TYPE__ count = static_cast<__SIZE_TYPE__>(last - first);
    return detail::submit_elementwise(
        policy, count, detail::grid_strided_fill_operation<Forward, T>{first, count, value});
}

template <class Output, class Size, class T>
CANN_ASC_STL_HOST_API execution_status fill_n(device_policy policy, Output first, Size count, const T& value) noexcept
{
    const __SIZE_TYPE__ total = count > 0 ? static_cast<__SIZE_TYPE__>(count) : 0;
    return detail::submit_elementwise(
        policy, total, detail::grid_strided_fill_operation<Output, T>{first, total, value});
}

template <class Input, class T>
CANN_ASC_STL_HOST_API execution_status find(
    device_policy policy, Input first, Input last, const T& value, ::asc::std::size_t* output_index) noexcept
{
    if (output_index == nullptr)
        return execution_status{execution_errc::invalid_argument};
    return detail::submit(
        policy, detail::find_index_operation<Input, detail::equal_value<T>>{first, last, output_index, {value}});
}

template <class Input, class UnaryPredicate>
CANN_ASC_STL_HOST_API execution_status find_if(
    device_policy policy, Input first, Input last, ::asc::std::size_t* output_index, UnaryPredicate predicate) noexcept
{
    if (output_index == nullptr)
        return execution_status{execution_errc::invalid_argument};
    return detail::submit(
        policy, detail::find_index_operation<Input, UnaryPredicate>{first, last, output_index, predicate});
}

template <class Input, class UnaryPredicate>
CANN_ASC_STL_HOST_API execution_status find_if_not(
    device_policy policy, Input first, Input last, ::asc::std::size_t* output_index, UnaryPredicate predicate) noexcept
{
    if (output_index == nullptr)
        return execution_status{execution_errc::invalid_argument};
    using negated = detail::negated_predicate<UnaryPredicate>;
    return detail::submit(policy, detail::find_index_operation<Input, negated>{first, last, output_index, {predicate}});
}

template <class Input, class Function>
CANN_ASC_STL_HOST_API execution_status for_each(
    device_policy policy, Input first, Input last, Function function) noexcept
{
    const __SIZE_TYPE__ count = static_cast<__SIZE_TYPE__>(last - first);
    return detail::submit_elementwise(
        policy, count, detail::grid_strided_for_each_operation<Input, Function>{first, count, function});
}

template <class Input, class Size, class Function>
CANN_ASC_STL_HOST_API execution_status for_each_n(
    device_policy policy, Input first, Size count, Function function) noexcept
{
    const __SIZE_TYPE__ total = count > 0 ? static_cast<__SIZE_TYPE__>(count) : 0;
    return detail::submit_elementwise(
        policy, total, detail::grid_strided_for_each_operation<Input, Function>{first, total, function});
}

template <class Forward, class Generator>
CANN_ASC_STL_HOST_API execution_status generate(
    device_policy policy, Forward first, Forward last, Generator generator) noexcept
{
    const __SIZE_TYPE__ count = static_cast<__SIZE_TYPE__>(last - first);
    return detail::submit_elementwise(
        policy, count, detail::grid_strided_generate_operation<Forward, Generator>{first, count, generator});
}

template <class Output, class Size, class Generator>
CANN_ASC_STL_HOST_API execution_status generate_n(
    device_policy policy, Output first, Size count, Generator generator) noexcept
{
    const __SIZE_TYPE__ total = count > 0 ? static_cast<__SIZE_TYPE__>(count) : 0;
    return detail::submit_elementwise(
        policy, total, detail::grid_strided_generate_operation<Output, Generator>{first, total, generator});
}

template <class Input, class Output, class T, class BinaryOperation>
CANN_ASC_STL_HOST_API execution_status inclusive_scan(
    device_policy policy, Input first, Input last, Output result, T init, BinaryOperation operation) noexcept
{
    return detail::submit(policy,
        detail::scan_operation<Input, Output, T, BinaryOperation, detail::identity_operation<T>>{
            first, last, result, init, operation, {}, true});
}

template <class Random, class Compare>
CANN_ASC_STL_HOST_API execution_status is_heap(
    device_policy policy, Random first, Random last, ::asc::std::uint32_t* output_value, Compare compare) noexcept
{
    if (output_value == nullptr)
        return execution_status{execution_errc::invalid_argument};
    return detail::submit(policy, detail::is_heap_operation<Random, Compare>{first, last, output_value, compare});
}

template <class Random, class Compare>
CANN_ASC_STL_HOST_API execution_status is_heap_until(
    device_policy policy, Random first, Random last, ::asc::std::size_t* output_index, Compare compare) noexcept
{
    if (output_index == nullptr)
        return execution_status{execution_errc::invalid_argument};
    return detail::submit(policy, detail::is_heap_until_operation<Random, Compare>{first, last, output_index, compare});
}

template <class Input, class UnaryPredicate>
CANN_ASC_STL_HOST_API execution_status is_partitioned(device_policy policy, Input first, Input last,
    ::asc::std::uint32_t* output_value, UnaryPredicate predicate) noexcept
{
    if (output_value == nullptr)
        return execution_status{execution_errc::invalid_argument};
    return detail::submit(
        policy, detail::is_partitioned_operation<Input, UnaryPredicate>{first, last, output_value, predicate});
}

template <class Forward, class Compare>
CANN_ASC_STL_HOST_API execution_status is_sorted(
    device_policy policy, Forward first, Forward last, ::asc::std::uint32_t* output_value, Compare compare) noexcept
{
    if (output_value == nullptr)
        return execution_status{execution_errc::invalid_argument};
    return detail::submit(policy, detail::is_sorted_operation<Forward, Compare>{first, last, output_value, compare});
}

template <class Forward, class Compare>
CANN_ASC_STL_HOST_API execution_status is_sorted_until(
    device_policy policy, Forward first, Forward last, ::asc::std::size_t* output_index, Compare compare) noexcept
{
    if (output_index == nullptr)
        return execution_status{execution_errc::invalid_argument};
    return detail::submit(
        policy, detail::is_sorted_until_operation<Forward, Compare>{first, last, output_index, compare});
}

template <class Forward, class Compare>
CANN_ASC_STL_HOST_API execution_status max_element(
    device_policy policy, Forward first, Forward last, ::asc::std::size_t* output_index, Compare compare) noexcept
{
    if (output_index == nullptr)
        return execution_status{execution_errc::invalid_argument};
    return detail::submit(
        policy, detail::extremum_operation<Forward, Compare>{first, last, output_index, compare, true});
}

template <class Input1, class Input2, class Output, class Compare>
CANN_ASC_STL_HOST_API execution_status merge(device_policy policy, Input1 first1, Input1 last1, Input2 first2,
    Input2 last2, Output result, Compare compare) noexcept
{
    return detail::submit(policy,
        detail::merge_operation<Input1, Input2, Output, Compare>{first1, last1, first2, last2, result, compare});
}

template <class Forward, class Compare>
CANN_ASC_STL_HOST_API execution_status min_element(
    device_policy policy, Forward first, Forward last, ::asc::std::size_t* output_index, Compare compare) noexcept
{
    if (output_index == nullptr)
        return execution_status{execution_errc::invalid_argument};
    return detail::submit(
        policy, detail::extremum_operation<Forward, Compare>{first, last, output_index, compare, false});
}

template <class Input1, class Input2, class BinaryPredicate>
CANN_ASC_STL_HOST_API execution_status mismatch(device_policy policy, Input1 first1, Input1 last1, Input2 first2,
    Input2 last2, ::asc::std::size_t* output_indices, BinaryPredicate predicate) noexcept
{
    if (output_indices == nullptr)
        return execution_status{execution_errc::invalid_argument};
    return detail::submit(policy,
        detail::mismatch_operation<Input1, Input2, BinaryPredicate>{
            first1, last1, first2, last2, output_indices, predicate});
}

template <class Input, class UnaryPredicate>
CANN_ASC_STL_HOST_API execution_status none_of(device_policy policy, Input first, Input last,
    ::asc::std::uint32_t* output_value, UnaryPredicate predicate) noexcept
{
    if (output_value == nullptr)
        return execution_status{execution_errc::invalid_argument};
    return detail::submit(
        policy, detail::bool_reduce_operation<Input, UnaryPredicate>{first, last, output_value, predicate, true, true});
}

template <class Forward, class UnaryPredicate>
CANN_ASC_STL_HOST_API execution_status partition(device_policy policy, Forward first, Forward last,
    ::asc::std::size_t* output_count, UnaryPredicate predicate) noexcept
{
    if (output_count == nullptr)
        return execution_status{execution_errc::invalid_argument};
    return detail::submit(
        policy, detail::partition_operation<Forward, UnaryPredicate>{first, last, output_count, predicate});
}

template <class Input, class Output1, class Output2, class UnaryPredicate>
CANN_ASC_STL_HOST_API execution_status partition_copy(device_policy policy, Input first, Input last,
    Output1 true_result, Output2 false_result, ::asc::std::size_t* output_true_count, UnaryPredicate predicate) noexcept
{
    if (output_true_count == nullptr)
        return execution_status{execution_errc::invalid_argument};
    return detail::submit(policy,
        detail::partition_copy_operation<Input, Output1, Output2, UnaryPredicate>{
            first, last, true_result, false_result, output_true_count, predicate});
}

template <class Input, class T, class BinaryOperation>
CANN_ASC_STL_HOST_API execution_status reduce(
    device_policy policy, Input first, Input last, T init, T* output_value, BinaryOperation operation) noexcept
{
    if (output_value == nullptr)
        return execution_status{execution_errc::invalid_argument};
    return detail::submit(
        policy, detail::reduce_operation<Input, T, BinaryOperation>{first, last, init, output_value, operation});
}

template <class Forward, class T>
CANN_ASC_STL_HOST_API execution_status remove(
    device_policy policy, Forward first, Forward last, const T& value, ::asc::std::size_t* output_count) noexcept
{
    if (output_count == nullptr)
        return execution_status{execution_errc::invalid_argument};
    using predicate = detail::negated_predicate<detail::equal_value<T>>;
    return detail::submit(
        policy, detail::select_in_place_operation<Forward, predicate>{first, last, output_count, {{{value}}}});
}

template <class Input, class Output, class T>
CANN_ASC_STL_HOST_API execution_status remove_copy(device_policy policy, Input first, Input last, Output result,
    const T& value, ::asc::std::size_t* output_count) noexcept
{
    if (output_count == nullptr)
        return execution_status{execution_errc::invalid_argument};
    using predicate = detail::negated_predicate<detail::equal_value<T>>;
    return detail::submit(policy,
        detail::select_copy_operation<Input, Output, predicate>{first, last, result, output_count, {{{value}}}});
}

template <class Input, class Output, class UnaryPredicate>
CANN_ASC_STL_HOST_API execution_status remove_copy_if(device_policy policy, Input first, Input last, Output result,
    ::asc::std::size_t* output_count, UnaryPredicate predicate) noexcept
{
    if (output_count == nullptr)
        return execution_status{execution_errc::invalid_argument};
    using negated = detail::negated_predicate<UnaryPredicate>;
    return detail::submit(
        policy, detail::select_copy_operation<Input, Output, negated>{first, last, result, output_count, {predicate}});
}

template <class Forward, class UnaryPredicate>
CANN_ASC_STL_HOST_API execution_status remove_if(device_policy policy, Forward first, Forward last,
    ::asc::std::size_t* output_count, UnaryPredicate predicate) noexcept
{
    if (output_count == nullptr)
        return execution_status{execution_errc::invalid_argument};
    using negated = detail::negated_predicate<UnaryPredicate>;
    return detail::submit(
        policy, detail::select_in_place_operation<Forward, negated>{first, last, output_count, {predicate}});
}

template <class Forward, class T>
CANN_ASC_STL_HOST_API execution_status replace(
    device_policy policy, Forward first, Forward last, const T& old_value, const T& new_value) noexcept
{
    const __SIZE_TYPE__ count = static_cast<__SIZE_TYPE__>(last - first);
    return detail::submit_elementwise(
        policy, count, detail::grid_strided_replace_value_operation<Forward, T>{first, count, old_value, new_value});
}

template <class Input, class Output, class T>
CANN_ASC_STL_HOST_API execution_status replace_copy(
    device_policy policy, Input first, Input last, Output result, const T& old_value, const T& new_value) noexcept
{
    const __SIZE_TYPE__ count = static_cast<__SIZE_TYPE__>(last - first);
    return detail::submit_elementwise(policy, count,
        detail::grid_strided_replace_copy_equal_operation<Input, Output, T, detail::equal_value<T>>{
            first, count, result, {old_value}, new_value});
}

template <class Input, class Output, class UnaryPredicate, class T>
CANN_ASC_STL_HOST_API execution_status replace_copy_if(
    device_policy policy, Input first, Input last, Output result, UnaryPredicate predicate, const T& new_value) noexcept
{
    const __SIZE_TYPE__ count = static_cast<__SIZE_TYPE__>(last - first);
    return detail::submit_elementwise(policy, count,
        detail::grid_strided_replace_copy_operation<Input, Output, T, UnaryPredicate>{
            first, count, result, predicate, new_value});
}

template <class Forward, class UnaryPredicate, class T>
CANN_ASC_STL_HOST_API execution_status replace_if(
    device_policy policy, Forward first, Forward last, UnaryPredicate predicate, const T& new_value) noexcept
{
    const __SIZE_TYPE__ count = static_cast<__SIZE_TYPE__>(last - first);
    return detail::submit_elementwise(policy, count,
        detail::grid_strided_replace_operation<Forward, T, UnaryPredicate>{first, count, predicate, new_value});
}

template <class Bidirectional>
CANN_ASC_STL_HOST_API execution_status reverse(device_policy policy, Bidirectional first, Bidirectional last) noexcept
{
    return detail::submit(policy, detail::reverse_operation<Bidirectional>{first, last});
}

template <class Bidirectional, class Output>
CANN_ASC_STL_HOST_API execution_status reverse_copy(
    device_policy policy, Bidirectional first, Bidirectional last, Output result) noexcept
{
    return detail::submit(policy, detail::reverse_copy_operation<Bidirectional, Output>{first, last, result});
}

template <class Forward>
CANN_ASC_STL_HOST_API execution_status rotate(
    device_policy policy, Forward first, Forward middle, Forward last) noexcept
{
    return detail::submit(policy, detail::rotate_operation<Forward>{first, middle, last});
}

template <class Forward, class Output>
CANN_ASC_STL_HOST_API execution_status rotate_copy(
    device_policy policy, Forward first, Forward middle, Forward last, Output result) noexcept
{
    return detail::submit(policy, detail::rotate_copy_operation<Forward, Output>{first, middle, last, result});
}

template <class Forward>
CANN_ASC_STL_HOST_API execution_status shift_left(
    device_policy policy, Forward first, Forward last, ::asc::std::size_t count) noexcept
{
    return detail::submit(policy, detail::shift_left_operation<Forward>{first, last, count});
}

template <class Forward>
CANN_ASC_STL_HOST_API execution_status shift_right(
    device_policy policy, Forward first, Forward last, ::asc::std::size_t count) noexcept
{
    return detail::submit(policy, detail::shift_right_operation<Forward>{first, last, count});
}

template <class Random, class Compare>
CANN_ASC_STL_HOST_API execution_status sort(
    device_policy policy, Random first, Random last, Compare compare) noexcept  // NOLINT(build/include_what_you_use)
{
    using element = typename asc::std::remove_cvref<decltype(*first)>::type;
    const __SIZE_TYPE__ count = static_cast<__SIZE_TYPE__>(last - first);
    // Natural-order arithmetic keys of at most eight bytes take the LSD radix
    // kernel; every other comparator drives the iterative bottom-up merge
    // kernel. Both are non-recursive and hold the O(N log N) frontend contract
    // when the policy provides the scratch the registry contract requires;
    // without scratch, or below the insertion threshold, both kernels fall
    // back to the shared stable insertion path.
    constexpr bool radix_path = detail::natural_order_compare<Compare>::value &&
        (asc::std::is_integral<element>::value || asc::std::is_floating_point<element>::value) && sizeof(element) <= 8;
    if (radix_path) {
        constexpr __SIZE_TYPE__ histogram_bytes = 256 * sizeof(__SIZE_TYPE__);
        if (detail::require_temporary_storage(policy, histogram_bytes + count * sizeof(element)).success()) {
            __SIZE_TYPE__* histogram = detail::temporary_storage_pointer<__SIZE_TYPE__>(policy);
            // The histogram block is a whole number of size_t slots, so the
            // element scratch behind it stays suitably aligned for the
            // at-most-eight-byte keys accepted above.
            element* scratch = detail::temporary_storage_pointer<element>(policy, histogram_bytes);
            return detail::submit(
                policy, detail::radix_sort_operation<Random, Compare>{first, last, compare, histogram, scratch});
        }
    }
    element* buffer = nullptr;
    if (detail::require_temporary_storage(policy, count * sizeof(element)).success()) {
        buffer = detail::temporary_storage_pointer<element>(policy);
    }
    return detail::submit(policy, detail::merge_sort_operation<Random, Compare>{first, last, compare, buffer});
}

template <class Bidirectional, class UnaryPredicate>
CANN_ASC_STL_HOST_API execution_status stable_partition(device_policy policy, Bidirectional first, Bidirectional last,
    ::asc::std::size_t* output_count, UnaryPredicate predicate) noexcept
{
    if (output_count == nullptr)
        return execution_status{execution_errc::invalid_argument};
    // One buffer element per input element turns the O(n^2) rotation fallback
    // into the O(n) two-pass form; without policy storage the operation keeps
    // the storage-less rotation path.
    using element = typename asc::std::remove_cvref<decltype(*first)>::type;
    const __SIZE_TYPE__ count = static_cast<__SIZE_TYPE__>(last - first);
    element* buffer = nullptr;
    if (detail::require_temporary_storage(policy, count * sizeof(element)).success()) {
        buffer = detail::temporary_storage_pointer<element>(policy);
    }
    return detail::submit(policy,
        detail::stable_partition_operation<Bidirectional, UnaryPredicate>{
            first, last, output_count, predicate, buffer});
}

template <class Forward1, class Forward2>
CANN_ASC_STL_HOST_API execution_status swap_ranges(
    device_policy policy, Forward1 first1, Forward1 last1, Forward2 first2) noexcept
{
    const __SIZE_TYPE__ count = static_cast<__SIZE_TYPE__>(last1 - first1);
    return detail::submit_elementwise(
        policy, count, detail::grid_strided_swap_ranges_operation<Forward1, Forward2>{first1, count, first2});
}

template <class Input, class Output, class UnaryOperation>
CANN_ASC_STL_HOST_API execution_status transform(
    device_policy policy, Input first, Input last, Output result, UnaryOperation operation) noexcept
{
    const __SIZE_TYPE__ count = static_cast<__SIZE_TYPE__>(last - first);
    return detail::submit_elementwise(policy, count,
        detail::grid_strided_transform_operation<Input, Output, UnaryOperation>{first, count, result, operation});
}

template <class Input, class Output, class T, class BinaryOperation, class UnaryOperation>
CANN_ASC_STL_HOST_API execution_status transform_exclusive_scan(device_policy policy, Input first, Input last,
    Output result, T init, BinaryOperation binary_operation, UnaryOperation unary_operation) noexcept
{
    return detail::submit(policy,
        detail::scan_operation<Input, Output, T, BinaryOperation, UnaryOperation>{
            first, last, result, init, binary_operation, unary_operation, false});
}

template <class Input, class Output, class BinaryOperation, class UnaryOperation, class T>
CANN_ASC_STL_HOST_API execution_status transform_inclusive_scan(device_policy policy, Input first, Input last,
    Output result, BinaryOperation binary_operation, UnaryOperation unary_operation, T init) noexcept
{
    return detail::submit(policy,
        detail::scan_operation<Input, Output, T, BinaryOperation, UnaryOperation>{
            first, last, result, init, binary_operation, unary_operation, true});
}

template <class Input, class T, class BinaryOperation, class UnaryOperation>
CANN_ASC_STL_HOST_API execution_status transform_reduce(device_policy policy, Input first, Input last, T init,
    T* output_value, BinaryOperation binary_operation, UnaryOperation unary_operation) noexcept
{
    if (output_value == nullptr)
        return execution_status{execution_errc::invalid_argument};
    return detail::submit(policy,
        detail::transform_reduce_operation<Input, T, BinaryOperation, UnaryOperation>{
            first, last, init, output_value, binary_operation, unary_operation});
}

template <class Forward, class BinaryPredicate>
CANN_ASC_STL_HOST_API execution_status unique(device_policy policy, Forward first, Forward last,
    ::asc::std::size_t* output_count, BinaryPredicate predicate) noexcept
{
    if (output_count == nullptr)
        return execution_status{execution_errc::invalid_argument};
    return detail::submit(
        policy, detail::unique_operation<Forward, BinaryPredicate>{first, last, output_count, predicate});
}

template <class Input, class Output, class BinaryPredicate>
CANN_ASC_STL_HOST_API execution_status unique_copy(device_policy policy, Input first, Input last, Output result,
    ::asc::std::size_t* output_count, BinaryPredicate predicate) noexcept
{
    if (output_count == nullptr)
        return execution_status{execution_errc::invalid_argument};
    return detail::submit(policy,
        detail::unique_copy_operation<Input, Output, BinaryPredicate>{first, last, result, output_count, predicate});
}

}  // namespace asc::parallel
#endif

#endif  // CANN_ASC_STL_ASC___ALGORITHM_FRONTEND_H
