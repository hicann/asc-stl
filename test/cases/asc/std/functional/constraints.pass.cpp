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

#include <asc/std/functional>
#include <utility>
#include "support/detected.h"

template <class T>
using ref_result = decltype(asc::std::ref(std::declval<T>()));
template <class T>
using cref_result = decltype(asc::std::cref(std::declval<T>()));
static_assert(asc_stl_test::detected<ref_result, int&> && asc_stl_test::detected<cref_result, const int&>);
static_assert(!asc_stl_test::detected<ref_result, int&&> && !asc_stl_test::detected<ref_result, const int&&>);
static_assert(!asc_stl_test::detected<cref_result, int&&> && !asc_stl_test::detected<cref_result, const int&&>);

template <class... Operations>
constexpr bool transparent()
{
    return (std::is_void_v<typename Operations::is_transparent> && ...);
}
namespace s = asc::std;
static_assert(transparent<s::plus<>, s::minus<>, s::multiplies<>, s::divides<>, s::modulus<>, s::negate<>, s::bit_and<>,
    s::bit_or<>, s::bit_xor<>, s::bit_not<>, s::equal_to<>, s::not_equal_to<>, s::less<>, s::greater<>, s::less_equal<>,
    s::greater_equal<>, s::logical_and<>, s::logical_or<>, s::logical_not<>>());

int main()
{}
