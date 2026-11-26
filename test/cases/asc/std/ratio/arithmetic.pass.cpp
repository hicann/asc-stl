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

#include <asc/std/ratio>

#include <cstdint>
#include <limits>
#include <ratio>

namespace s = asc::std;

template <class A, class B>
constexpr bool matches = A::num == B::num && A::den == B::den;

#define CHECK_PREFIX(name) static_assert(matches<s::name, std::name>)
CHECK_PREFIX(atto);
CHECK_PREFIX(femto);
CHECK_PREFIX(pico);
CHECK_PREFIX(nano);
CHECK_PREFIX(micro);
CHECK_PREFIX(milli);
CHECK_PREFIX(centi);
CHECK_PREFIX(deci);
CHECK_PREFIX(deca);
CHECK_PREFIX(hecto);
CHECK_PREFIX(kilo);
CHECK_PREFIX(mega);
CHECK_PREFIX(giga);
CHECK_PREFIX(tera);
CHECK_PREFIX(peta);
CHECK_PREFIX(exa);

template <std::intmax_t A, std::intmax_t B, std::intmax_t C, std::intmax_t D>
constexpr bool operations()
{
    using x = s::ratio<A, B>;
    using y = s::ratio<C, D>;
    using u = std::ratio<A, B>;
    using v = std::ratio<C, D>;
    static_assert(matches<typename x::type, typename u::type> && matches<typename y::type, typename v::type>);
    static_assert(matches<s::ratio_add<x, y>, std::ratio_add<u, v>>);
    static_assert(matches<s::ratio_subtract<x, y>, std::ratio_subtract<u, v>>);
    static_assert(matches<s::ratio_multiply<x, y>, std::ratio_multiply<u, v>>);
    if constexpr (C != 0) {
        static_assert(matches<s::ratio_divide<x, y>, std::ratio_divide<u, v>>);
    }
    return s::ratio_equal<x, y>::value == std::ratio_equal_v<u, v> &&
        s::ratio_equal_v<x, y> == std::ratio_equal_v<u, v> &&
        s::ratio_not_equal_v<x, y> == std::ratio_not_equal_v<u, v> &&
        s::ratio_less_v<x, y> == std::ratio_less_v<u, v> && s::ratio_greater_v<x, y> == std::ratio_greater_v<u, v> &&
        s::ratio_less_equal_v<x, y> == std::ratio_less_equal_v<u, v> &&
        s::ratio_greater_equal_v<x, y> == std::ratio_greater_equal_v<u, v>;
}
static_assert(operations<-12, -8, 3, 2>() && operations<7, -9, 0, -127>() && operations<0, 1, 0, 1>() &&
    operations<4, 5, 7, 11>() && operations<-1, 4, 2, -7>());

constexpr auto hi = std::numeric_limits<std::intmax_t>::max();
using near_one = s::ratio<hi - 1, hi>;
using smaller = s::ratio<hi - 2, hi - 1>;
static_assert(s::ratio_less_v<smaller, near_one> && !s::ratio_less_v<near_one, smaller>);
static_assert(matches<s::ratio_multiply<near_one, s::ratio<hi, hi - 1>>, std::ratio<1>>);

int main()
{}
