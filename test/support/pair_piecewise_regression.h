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

#ifndef ASC_STL_TEST_PAIR_PIECEWISE_REGRESSION_H
#define ASC_STL_TEST_PAIR_PIECEWISE_REGRESSION_H

#include <asc/std/tuple>
#include <asc/std/type_traits>
#include <asc/std/utility>

namespace asc_stl_pair_piecewise_test {
struct value_pair {
    int first;
    int second;
    CANN_ASC_STL_API value_pair(int left, int right) noexcept : first(left), second(right)
    {}
    value_pair(const value_pair&) = delete;
    value_pair(value_pair&&) = delete;
};

CANN_ASC_STL_API bool evaluate(int input)
{
    asc::std::pair<int, int> empty(asc::std::piecewise_construct, asc::std::tuple<>{}, asc::std::tuple<>{});
    asc::std::pair<value_pair, int&> values(
        asc::std::piecewise_construct, asc::std::make_tuple(input, 3), asc::std::forward_as_tuple(input));
    asc::std::tuple<int&> reference(input);
    const asc::std::tuple<int&> const_reference(input);
    static_assert(asc::std::is_same_v<decltype(asc::std::get<0>(asc::std::move(reference))), int&>);
    static_assert(asc::std::is_same_v<decltype(asc::std::get<0>(asc::std::move(const_reference))), int&>);
    const int original = input;
    if (&asc::std::get<0>(asc::std::move(reference)) != &input ||
        &asc::std::get<int&>(asc::std::move(const_reference)) != &input)  // NOLINT(build/include_what_you_use)
        return false;
    values.second = 9;
    return empty.first == 0 && empty.second == 0 && values.first.first == original && values.first.second == 3 &&
        input == 9 && &values.second == &input;
}
}  // namespace asc_stl_pair_piecewise_test

#endif  // ASC_STL_TEST_PAIR_PIECEWISE_REGRESSION_H
