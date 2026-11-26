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

#ifndef ASC_STL_TEST_UTILITY_DEVICE_CHECKS_H
#define ASC_STL_TEST_UTILITY_DEVICE_CHECKS_H

#include <asc/std/utility>

namespace asc_stl_test_utility {

enum class signed_code : short { negative = -9 };

CANN_ASC_STL_API int check(int seed = 7)
{
    using asc::std::swap;
    static_assert(
        asc::std::make_index_sequence<0>::size() == 0 && asc::std::make_integer_sequence<int, 5>::size() == 5);
    static_assert(
        asc::std::is_same_v<decltype(asc::std::forward_like<const int&>(asc::std::declval<int&>())), const int&>);
    static_assert(asc::std::is_same_v<decltype(asc::std::forward_like<int>(asc::std::declval<int&>())), int&&>);
    static_assert(asc::std::is_same_v<decltype(asc::std::move_if_noexcept(asc::std::declval<int&>())), int&&>);
    int value = seed;
    const int& alias = asc::std::as_const(value);
    int& forwarded = asc::std::forward<int&>(value);
    if (&alias != &value || &forwarded != &value || asc::std::exchange(value, -2) != 7 || value != -2)
        return 1;

    const unsigned large = ~0U;
    if (asc::std::cmp_equal(-1, large) || !asc::std::cmp_not_equal(large, -1) || !asc::std::cmp_less(-1, large) ||
        asc::std::cmp_less(large, -1) || !asc::std::cmp_greater(large, -1) || !asc::std::cmp_greater_equal(0U, 0) ||
        !asc::std::cmp_less_equal(0, 0U) || !asc::std::in_range<unsigned char>(255U) ||
        asc::std::in_range<unsigned char>(256U) || asc::std::in_range<unsigned char>(-1) ||
        asc::std::to_underlying(signed_code::negative) != -9)
        return 2;

    int left[] = {1, 3};
    int right[] = {4, 7};
    swap(left, right);
    if (left[0] != 4 || left[1] != 7 || right[0] != 1 || right[1] != 3)
        return 3;
    auto pair1 = asc::std::make_pair(-3, 8U);  // NOLINT(build/include_what_you_use)
    asc::std::pair<int, unsigned> pair2(4, 6);
    pair1.swap(pair2);
    if (asc::std::get<0>(pair1) != 4 || asc::std::get<unsigned>(pair2) != 8 || pair1 == pair2)
        return 4;
    return 0;
}

}  // namespace asc_stl_test_utility

#endif  // ASC_STL_TEST_UTILITY_DEVICE_CHECKS_H
