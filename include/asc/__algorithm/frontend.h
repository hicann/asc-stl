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
#include <asc/execution>
#include <asc/execution.policy.h>

namespace asc::std {
using size_t = __SIZE_TYPE__;
using uint32_t = __UINT32_TYPE__;
}  // namespace asc::std

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
template <class T>
struct passthrough {
    CANN_ASC_STL_DEVICE_API T operator()(const T& value) const
    {
        return value;
    }
};

#if defined(__clang__) && defined(CANN_ASC_STL_USE_SIMT_LAUNCH)
template <class Operation>
CANN_ASC_STL_HOST_API execution_status submit(device_policy policy, Operation operation) noexcept
{
    static_assert(__is_trivially_copyable(Operation), "ASC-STL parallel operation state must be trivially copyable");
    execution_status status = validate_parallel_policy(policy);
    return status.success() ? submit_parallel_operation(policy.stream(), operation) : status;
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
CANN_ASC_STL_HOST_API execution_status copy(  // NOLINT(build/include_what_you_use)
    device_policy policy, Input first, Input last, Output result) noexcept
{
    return detail::submit(policy, detail::copy_operation<Input, Output>{first, last, result});
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
    return detail::submit(policy, detail::copy_n_operation<Input, Size, Output>{first, count, result});
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
        detail::scan_operation<Input, Output, T, BinaryOperation, detail::passthrough<T>>{
            first, last, result, init, operation, {}, false});
}

template <class Forward, class T>
CANN_ASC_STL_HOST_API execution_status fill(device_policy policy, Forward first, Forward last, const T& value) noexcept
{
    return detail::submit(policy, detail::fill_operation<Forward, Forward, T>{first, last, value});
}

template <class Output, class Size, class T>
CANN_ASC_STL_HOST_API execution_status fill_n(device_policy policy, Output first, Size count, const T& value) noexcept
{
    return detail::submit(policy, detail::fill_n_operation<Output, Size, T>{first, count, value});
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
    return detail::submit(policy, detail::for_each_operation<Input, Input, Function>{first, last, function});
}

template <class Input, class Size, class Function>
CANN_ASC_STL_HOST_API execution_status for_each_n(
    device_policy policy, Input first, Size count, Function function) noexcept
{
    return detail::submit(policy, detail::for_each_n_operation<Input, Size, Function>{first, count, function});
}

template <class Forward, class Generator>
CANN_ASC_STL_HOST_API execution_status generate(
    device_policy policy, Forward first, Forward last, Generator generator) noexcept
{
    return detail::submit(policy, detail::generate_operation<Forward, Forward, Generator>{first, last, generator});
}

template <class Output, class Size, class Generator>
CANN_ASC_STL_HOST_API execution_status generate_n(
    device_policy policy, Output first, Size count, Generator generator) noexcept
{
    return detail::submit(policy, detail::generate_n_operation<Output, Size, Generator>{first, count, generator});
}

template <class Input, class Output, class T, class BinaryOperation>
CANN_ASC_STL_HOST_API execution_status inclusive_scan(
    device_policy policy, Input first, Input last, Output result, T init, BinaryOperation operation) noexcept
{
    return detail::submit(policy,
        detail::scan_operation<Input, Output, T, BinaryOperation, detail::passthrough<T>>{
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
    return detail::submit(
        policy, detail::replace_operation<Forward, T, detail::equal_value<T>>{first, last, {old_value}, new_value});
}

template <class Input, class Output, class T>
CANN_ASC_STL_HOST_API execution_status replace_copy(
    device_policy policy, Input first, Input last, Output result, const T& old_value, const T& new_value) noexcept
{
    return detail::submit(policy,
        detail::replace_copy_operation<Input, Output, T, detail::equal_value<T>>{
            first, last, result, {old_value}, new_value});
}

template <class Input, class Output, class UnaryPredicate, class T>
CANN_ASC_STL_HOST_API execution_status replace_copy_if(
    device_policy policy, Input first, Input last, Output result, UnaryPredicate predicate, const T& new_value) noexcept
{
    return detail::submit(policy,
        detail::replace_copy_operation<Input, Output, T, UnaryPredicate>{first, last, result, predicate, new_value});
}

template <class Forward, class UnaryPredicate, class T>
CANN_ASC_STL_HOST_API execution_status replace_if(
    device_policy policy, Forward first, Forward last, UnaryPredicate predicate, const T& new_value) noexcept
{
    return detail::submit(
        policy, detail::replace_operation<Forward, T, UnaryPredicate>{first, last, predicate, new_value});
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
CANN_ASC_STL_HOST_API execution_status sort(  // NOLINT(build/include_what_you_use)
    device_policy policy, Random first, Random last, Compare compare) noexcept
{
    return detail::submit(policy, detail::radix_sort_operation<Random, Compare>{first, last, compare});
}

template <class Bidirectional, class UnaryPredicate>
CANN_ASC_STL_HOST_API execution_status stable_partition(device_policy policy, Bidirectional first, Bidirectional last,
    ::asc::std::size_t* output_count, UnaryPredicate predicate) noexcept
{
    if (output_count == nullptr)
        return execution_status{execution_errc::invalid_argument};
    return detail::submit(policy,
        detail::stable_partition_operation<Bidirectional, UnaryPredicate>{first, last, output_count, predicate});
}

template <class Forward1, class Forward2>
CANN_ASC_STL_HOST_API execution_status swap_ranges(
    device_policy policy, Forward1 first1, Forward1 last1, Forward2 first2) noexcept
{
    return detail::submit(policy, detail::swap_ranges_operation<Forward1, Forward2>{first1, last1, first2});
}

template <class Input, class Output, class UnaryOperation>
CANN_ASC_STL_HOST_API execution_status transform(
    device_policy policy, Input first, Input last, Output result, UnaryOperation operation) noexcept
{
    return detail::submit(
        policy, detail::transform_operation<Input, Output, UnaryOperation>{first, last, result, operation});
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
