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

#ifndef ASC_STL_TEST_V1_ALGORITHM_SEMANTICS_H
#define ASC_STL_TEST_V1_ALGORITHM_SEMANTICS_H

#include <asc/std/algorithm>
#include <asc/std/type_traits>

namespace asc_stl_v1_algorithm_test {

struct record {
    int key;
};
struct project_key {
    CANN_ASC_STL_API constexpr int operator()(const record& value) const noexcept
    {
        return value.key;
    }
};
struct is_two {
    CANN_ASC_STL_API constexpr bool operator()(int value) const noexcept
    {
        return value == 2;
    }
};
struct count_values {
    int total = 0;
    CANN_ASC_STL_API constexpr void operator()(int value)
    {
        total += value;
    }
};
struct descending {
    CANN_ASC_STL_API constexpr bool operator()(int left, int right) const noexcept
    {
        return left > right;
    }
};
struct owned_range {
    record* first;
    record* last;
    CANN_ASC_STL_API constexpr record* begin() const noexcept
    {
        return first;
    }
    CANN_ASC_STL_API constexpr record* end() const noexcept
    {
        return last;
    }
};
struct borrowed_range : owned_range {};

}  // namespace asc_stl_v1_algorithm_test

namespace asc::std::ranges {
template <>
inline constexpr bool enable_borrowed_range<asc_stl_v1_algorithm_test::borrowed_range> = true;
}  // namespace asc::std::ranges

namespace asc_stl_v1_algorithm_test {

using dangling_find = decltype(asc::std::ranges::find_if(owned_range{}, is_two{}, project_key{}));
using dangling_min = decltype(asc::std::ranges::min_element(owned_range{}, asc::std::ranges::less{}, project_key{}));
using dangling_each = decltype(asc::std::ranges::for_each(owned_range{}, count_values{}, project_key{}));
using borrowed_find = decltype(asc::std::ranges::find_if(borrowed_range{}, is_two{}, project_key{}));
static_assert(asc::std::is_same_v<dangling_find, asc::std::ranges::dangling>);
static_assert(asc::std::is_same_v<dangling_min, asc::std::ranges::dangling>);
static_assert(asc::std::is_same_v<decltype(dangling_each{}.in), asc::std::ranges::dangling>);
static_assert(asc::std::is_same_v<borrowed_find, record*>);

CANN_ASC_STL_API int evaluate()
{
    record values[] = {{3}, {2}, {1}};
    auto found = asc::std::ranges::find_if(values, is_two{}, project_key{});
    auto not_found = asc::std::ranges::find_if_not(values, values + 3, is_two{}, project_key{});
    auto minimum = asc::std::ranges::min(values, asc::std::ranges::less{}, project_key{});
    auto minimum_position = asc::std::ranges::min_element(values, asc::std::ranges::less{}, project_key{});
    auto counted = asc::std::ranges::for_each(values, count_values{}, project_key{});
    auto counted_n = asc::std::ranges::for_each_n(values, 3, count_values{}, project_key{});
    const record* borrowed = asc::std::ranges::find_if(values, is_two{}, project_key{});
    int lower = 1;
    int upper = 3;
    int middle = 2;
    int below = 0;
    int above = 4;
    const int& low_result = asc::std::clamp(below, lower, upper);
    const int& high_result = asc::std::clamp(above, lower, upper);
    const int& middle_result = asc::std::clamp(middle, lower, upper);
    const int& reversed = asc::std::clamp(above, upper, lower, descending{});
    return found != values + 1 || not_found != values || minimum.key != 1 || minimum_position != values + 2 ||
        counted.in != values + 3 || counted.fun.total != 6 || counted_n.in != values + 3 || counted_n.fun.total != 6 ||
        borrowed != values + 1 || &low_result != &lower || &high_result != &upper || &middle_result != &middle ||
        &reversed != &upper;
}

}  // namespace asc_stl_v1_algorithm_test

#endif  // ASC_STL_TEST_V1_ALGORITHM_SEMANTICS_H
