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

#ifndef ASC_STL_TEST_CONSTRUCT_AT_CARDINALITY_SEMANTICS_H
#define ASC_STL_TEST_CONSTRUCT_AT_CARDINALITY_SEMANTICS_H

#include <asc/std/memory>

namespace asc_stl_construct_at_cardinality_test {

template <class T>
union object_slot {
    unsigned char inactive;
    T object;
    CANN_ASC_STL_API object_slot() noexcept : inactive(0)
    {}
    CANN_ASC_STL_API ~object_slot() noexcept
    {}
};

template <class CounterPointer>
struct tracked_value {
    CounterPointer destroyed = nullptr;
    CounterPointer checksum = nullptr;
    int value;
    CANN_ASC_STL_API tracked_value() noexcept : value(11)
    {}
    CANN_ASC_STL_API explicit tracked_value(int input) noexcept : value(input)
    {}
    CANN_ASC_STL_API tracked_value(int first, int second, int third) noexcept : value(first * 100 + second * 10 + third)
    {}
    CANN_ASC_STL_API tracked_value(int first, int second, int third, int fourth) noexcept
        : value(first * 1000 + second * 100 + third * 10 + fourth)
    {}
    CANN_ASC_STL_API ~tracked_value() noexcept
    {
        if (destroyed != nullptr)
            ++*destroyed;
        if (checksum != nullptr)
            *checksum += value;
    }
};

CANN_ASC_STL_API int evaluate_lifetime() noexcept
{
    int destroyed = 0;
    int checksum = 0;
    using value_type = tracked_value<decltype(&destroyed)>;
    object_slot<value_type> slot;
    auto* first = asc::std::construct_at(&slot.object);
    if (first != &slot.object || first->value != 11)
        return 121;
    first->destroyed = &destroyed;
    first->checksum = &checksum;
    asc::std::destroy_at(first);
    auto* second = asc::std::construct_at(&slot.object, 13);
    if (second->value != 13)
        return 122;
    second->destroyed = &destroyed;
    second->checksum = &checksum;
    asc::std::destroy_at(second);
    auto* third = asc::std::construct_at(&slot.object, 1, 2, 3);
    if (third->value != 123)
        return 123;
    third->destroyed = &destroyed;
    third->checksum = &checksum;
    asc::std::destroy_at(third);
    auto* fourth = asc::std::construct_at(&slot.object, 4, 3, 2, 1);
    if (fourth->value != 4321)
        return 124;
    fourth->destroyed = &destroyed;
    fourth->checksum = &checksum;
    asc::std::destroy_at(fourth);
    return destroyed == 4 && checksum == 4468 ? 0 : 125;
}

static_assert(asc::std::__detail::__check_narrowing<int>::value);
static_assert(asc::std::__detail::__check_narrowing<int, int, int, int>::value);
static_assert(asc::std::__detail::__can_optimize_construct_at<int, int>);
static_assert(!asc::std::__detail::__can_optimize_construct_at<int>);
static_assert(!asc::std::__detail::__can_optimize_construct_at<int, float>);

CANN_ASC_STL_API int evaluate_scalar() noexcept
{
    object_slot<int> slot;
    auto* zero = asc::std::construct_at(&slot.object);
    if (zero != &slot.object || *zero != 0)
        return 126;
    auto* copied = asc::std::construct_at(zero, 7);
    if (copied != zero || *copied != 7)
        return 127;
    auto* narrowed = asc::std::construct_at(copied, 9.75F);
    const bool valid = narrowed == copied && *narrowed == 9;
    asc::std::destroy_at(narrowed);
    return valid ? 0 : 128;
}

#if defined(__cpp_aggregate_paren_init) && __cpp_aggregate_paren_init >= 201902L
struct aggregate_value {
    int first;
    int second;
};
static_assert(!asc::std::__detail::__can_optimize_construct_at<aggregate_value, float, float>);

CANN_ASC_STL_API int evaluate_aggregate() noexcept
{
    object_slot<aggregate_value> slot;
    auto* value = asc::std::construct_at(&slot.object, 1.75F, 2.75F);
    const bool valid = value == &slot.object && value->first == 1 && value->second == 2;
    asc::std::destroy_at(value);
    return valid ? 0 : 129;
}
#endif

CANN_ASC_STL_API int evaluate() noexcept
{
    const int lifetime_result = evaluate_lifetime();
    if (lifetime_result != 0)
        return lifetime_result;
    const int scalar_result = evaluate_scalar();
    if (scalar_result != 0)
        return scalar_result;
#if defined(__cpp_aggregate_paren_init) && __cpp_aggregate_paren_init >= 201902L
    return evaluate_aggregate();
#else
    return 0;
#endif
}

}  // namespace asc_stl_construct_at_cardinality_test

#endif  // ASC_STL_TEST_CONSTRUCT_AT_CARDINALITY_SEMANTICS_H
