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

#ifndef ASC_STL_TEST_B028_SEMANTICS_H
#define ASC_STL_TEST_B028_SEMANTICS_H

#include <asc/std/__bit/byteswap.h>
#include <asc/std/__cerrno/portable_constants.h>
#include <asc/std/__functional/mem_fn.h>
#include <asc/std/__functional/not_fn.h>
#include <asc/std/__new/nonallocating_new.h>
#include <asc/std/__system_error/lightweight_error.h>
#include <asc/std/__type_traits/has_unique_object_representation.h>
#include <asc/std/__type_traits/has_virtual_destructor.h>
#include <asc/std/__type_traits/is_aggregate.h>
#include <asc/std/__type_traits/is_bounded_array.h>
#include <asc/std/__type_traits/is_polymorphic.h>
#include <asc/std/__utility/rel_ops.h>
#include <asc/std/list>
#include <asc/std/map>

#include "b028_allocator.h"
#include "inline_arena_allocator.h"

namespace asc_stl_b028_test {

struct aggregate_type {
    int value;
};
struct polymorphic_type {
    CANN_ASC_STL_API virtual ~polymorphic_type() = default;
};
struct padded_type {
    char first;
    int second;
};

static_assert(asc::std::is_aggregate<aggregate_type>::value);
static_assert(asc::std::is_aggregate_v<aggregate_type>);
static_assert(!asc::std::is_aggregate_v<polymorphic_type>);
static_assert(asc::std::is_polymorphic_v<polymorphic_type>);
static_assert(asc::std::has_virtual_destructor_v<polymorphic_type>);
static_assert(!asc::std::has_virtual_destructor_v<aggregate_type>);
static_assert(asc::std::is_bounded_array_v<int[3]>);
static_assert(!asc::std::is_bounded_array_v<int[]>);
static_assert(asc::std::has_unique_object_representations_v<unsigned int>);
static_assert(!asc::std::has_unique_object_representations_v<padded_type>);

struct callable {
    int value;

    CANN_ASC_STL_API int add(int input) &
    {
        return value + input;
    }
    CANN_ASC_STL_API int read() const&
    {
        return value;
    }
};

struct predicate {
    int threshold;

    CANN_ASC_STL_API bool operator()(int value) &
    {
        return value > threshold;
    }
    CANN_ASC_STL_API bool operator()(int value) const&
    {
        return value >= threshold;
    }
    CANN_ASC_STL_API bool operator()(int value) &&
    {
        return value != threshold;
    }
    CANN_ASC_STL_API bool operator()(int value) const&&
    {
        return value == threshold;
    }
};

struct ordered_value {
    int value;
};
CANN_ASC_STL_API bool operator==(const ordered_value& left, const ordered_value& right)
{
    return left.value == right.value;
}
CANN_ASC_STL_API bool operator<(const ordered_value& left, const ordered_value& right)
{
    return left.value < right.value;
}

CANN_ASC_STL_API int evaluate_foundation()
{
    if (asc::std::byteswap(static_cast<unsigned char>(0x5a)) != 0x5a)
        return 1;
    if (asc::std::byteswap(static_cast<unsigned short>(0x1234)) != 0x3412)
        return 2;
    if (asc::std::byteswap(0x12345678u) != 0x78563412u)
        return 3;
    if (asc::std::byteswap(0x0123456789abcdefULL) != 0xefcdab8967452301ULL)
        return 4;

    callable value{7};
    const callable constant{9};
    if (asc::std::mem_fn(&callable::value)(value) != 7)
        return 5;
    asc::std::mem_fn (&callable::value)(value) = 11;
    if (asc::std::mem_fn(&callable::add)(value, 4) != 15)
        return 6;
    if (asc::std::mem_fn(&callable::read)(&constant) != 9)
        return 7;

    auto negated = asc::std::not_fn(predicate{5});
    if (negated(6) || !negated(4))
        return 8;
    const auto const_negated = asc::std::not_fn(predicate{5});
    if (!const_negated(4) || const_negated(5))
        return 9;
    if (!static_cast<decltype(negated)&&>(negated)(5))
        return 10;
    if (static_cast<const decltype(const_negated)&&>(const_negated)(5))
        return 11;

    using asc::std::rel_ops::operator!=;
    using asc::std::rel_ops::operator<=;
    using asc::std::rel_ops::operator>=;
    using asc::std::rel_ops::operator>;  // NOLINT(whitespace/operators)
    const ordered_value one{1};
    const ordered_value two{2};
    if (!(one != two) || !(two > one) || !(one <= two) || !(two >= one))
        return 12;

    alignas(int) unsigned char storage[sizeof(int)]{};
    int* object = ::new (static_cast<void*>(storage)) int(23);  // NOLINT(readability/casting)
    if (*asc::std::launder(object) != 23)
        return 13;
    using object_type = int;
    object->~object_type();
    if (EDOM <= 0 || EILSEQ <= 0 || ERANGE <= 0)
        return 14;
    if (asc::std::errc::invalid_argument == asc::std::errc::result_out_of_range)
        return 15;
    if (asc::std::is_error_code_enum<asc::std::errc>::value)
        return 16;
    if (!asc::std::is_error_condition_enum<asc::std::errc>::value)
        return 17;
    return 0;
}

#if defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__) || !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <class StoragePointer>
CANN_ASC_STL_HOST_SIMT_API int evaluate_containers(StoragePointer storage, __SIZE_TYPE__ capacity)
{
    if (capacity < sizeof(asc_stl_test::inline_arena))
        return 19;
    auto& state = asc_stl_test::start_inline_arena(storage);
    using int_allocator = asc_stl_test::inline_arena_allocator<int>;
    {
        asc::std::list<int, int_allocator> values{int_allocator(&state)};
        if (!values.empty() || values.size() != 0)
            return 20;
        values.emplace_back(2);
        values.push_front(1);
        values.push_back(3);
        if (values.size() != 3 || values.front() != 1 || values.back() != 3)
            return 21;
        auto iterator = values.begin();
        if (*iterator++ != 1 || *iterator++ != 2 || *iterator++ != 3 || iterator != values.end())
            return 22;
        values.pop_front();
        values.pop_back();
        if (values.size() != 1 || values.front() != 2)
            return 23;
        asc::std::list<int, int_allocator> moved{static_cast<decltype(values)&&>(values)};
        if (!values.empty() || moved.size() != 1 || moved.front() != 2)
            return 24;
        values = static_cast<decltype(moved)&&>(moved);
        if (!moved.empty() || values.size() != 1)
            return 25;
        values.clear();
        values.emplace_front(7);
        if (values.front() != 7)
            return 26;
    }
    if (state.allocations != state.deallocations)
        return 27;

    using pair_type = asc::std::__arena_pair<const int, int>;
    using pair_allocator = asc_stl_test::inline_arena_allocator<pair_type>;
    {
        using map_type = asc::std::map<int, int, less_int, pair_allocator>;  // NOLINT(build/include_what_you_use)
        map_type values{less_int{}, pair_allocator(&state)};
        if (!values.empty() || values.size() != 0)
            return 30;
        const auto inserted = values.insert(pair_type(2, 20));
        if (!inserted.second || inserted.first->second != 20)
            return 31;
        inserted.first->second = 21;
        if (values.insert(pair_type(2, 99)).second || values.size() != 1)
            return 32;
        values[1] = 10;
        values[3] = 30;
        if (values.size() != 3 || values.count(2) != 1 || values.count(9) != 0)
            return 33;
        auto iterator = values.begin();
        if (iterator->first != 1 || (++iterator)->first != 2 || (++iterator)->first != 3)
            return 34;
        map_type moved{static_cast<map_type&&>(values)};
        if (!values.empty() || moved.find(2)->second != 21)
            return 35;
        values = static_cast<map_type&&>(moved);
        if (!moved.empty() || values.size() != 3)
            return 36;
        values.clear();
        values[4] = 40;
        if (values.size() != 1 || values.find(4)->second != 40)
            return 37;
    }
    if (state.allocations != state.deallocations)
        return 38;
    return 0;
}
#endif

template <class StoragePointer>
CANN_ASC_STL_API int evaluate_device(StoragePointer storage, __SIZE_TYPE__ capacity)
{
    const int foundation = evaluate_foundation();
    if (foundation != 0)
        return foundation;
#if defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__) || !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return evaluate_containers(storage, capacity);
#else
    (void)storage;
    (void)capacity;
    return 0;
#endif
}

}  // namespace asc_stl_b028_test

#endif  // ASC_STL_TEST_B028_SEMANTICS_H
