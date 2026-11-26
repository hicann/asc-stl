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

#include <asc/std/variant>
#include <type_traits>

namespace s = asc::std;
using choice = s::variant<s::monostate, long, const int, long>;
static_assert(s::variant_size<choice>::value == 4);
static_assert(s::variant_size<const choice>::value == 4);
static_assert(s::variant_size<volatile choice>::value == 4);
static_assert(s::variant_size<const volatile choice>::value == 4);
static_assert(s::variant_size_v<const volatile choice> == 4);
static_assert(std::is_same_v<typename s::variant_alternative<0, choice>::type, s::monostate>);
static_assert(std::is_same_v<typename s::variant_alternative<1, const choice>::type, const long>);
static_assert(std::is_same_v<typename s::variant_alternative<2, volatile choice>::type, const volatile int>);
static_assert(std::is_same_v<typename s::variant_alternative<3, const volatile choice>::type, const volatile long>);
static_assert(std::is_same_v<s::variant_alternative_t<3, choice>, long>);
static_assert(s::variant_npos == static_cast<__SIZE_TYPE__>(-1));

int main()
{
    const choice x(s::in_place_index<1>, 11L), y(s::in_place_index<3>, 11L);
    const choice z(s::in_place_index<1>, 11L);
    return x.index() != 1 || y.index() != 3 || x == y || x != z;
}
