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

#ifndef ASC_STL_EXAMPLES_TUPLE_TRAITS_H
#define ASC_STL_EXAMPLES_TUPLE_TRAITS_H

#include <asc/std/array>
#include <asc/std/tuple>
#include <asc/std/type_traits>

#include "example_types.h"

namespace example {

// Keep the supported input domain explicit; widening is not a general overflow check.
template <class T, asc::std::size_t Size>
CANN_ASC_STL_API auto summarize(const asc::std::array<T, Size>& values)
{
    static_assert(asc::std::is_same_v<T, int> || asc::std::is_same_v<T, float>);
    using accumulator = asc::std::conditional_t<asc::std::is_integral_v<T>, long long, float>;
    accumulator sum = 0;
    for (T value : values) {
        sum += static_cast<accumulator>(value);
    }
    return asc::std::tuple<accumulator, unsigned int>(sum, static_cast<unsigned int>(Size));
}

CANN_ASC_STL_API Result evaluate(const Input& input)
{
    const asc::std::array<int, 3> integers{input.integers[0], input.integers[1], input.integers[2]};
    const asc::std::array<float, 3> fractions{input.fractions[0], input.fractions[1], input.fractions[2]};
    const auto integer_stats = summarize(integers);
    const auto real_stats = summarize(fractions);
    static_assert(asc::std::is_same_v<asc::std::tuple_element_t<0, decltype(summarize(integers))>, long long>);
    static_assert(asc::std::is_same_v<asc::std::tuple_element_t<0, decltype(summarize(fractions))>, float>);
    return {asc::std::get<0>(integer_stats), asc::std::get<0>(real_stats), asc::std::get<1>(integer_stats),
        asc::std::get<1>(real_stats)};
}

}  // namespace example

#endif  // ASC_STL_EXAMPLES_TUPLE_TRAITS_H
