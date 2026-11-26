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

#include <asc/std/complex>
#include <asc/std/tuple>
#include <type_traits>

namespace s = asc::std;
template <class T, class = void>
struct has_element_type : std::false_type {};
template <class T>
struct has_element_type<T, std::void_t<typename T::type>> : std::true_type {};
static_assert(!has_element_type<s::tuple_element<0, s::tuple<>>>::value);
static_assert(!has_element_type<s::tuple_element<3, s::tuple<int, int, int>>>::value);
using fields = s::tuple<long, const int, char&>;
static_assert(s::tuple_size<fields>::value == 3);
static_assert(s::tuple_size<const fields>::value == 3);
static_assert(s::tuple_size<volatile fields>::value == 3);
static_assert(s::tuple_size<const volatile fields>::value == 3);
static_assert(s::tuple_size_v<const volatile s::tuple<>> == 0);
static_assert(std::is_same_v<typename s::tuple_element<0, fields>::type, long>);
static_assert(std::is_same_v<typename s::tuple_element<0, const fields>::type, const long>);
static_assert(std::is_same_v<typename s::tuple_element<1, volatile fields>::type, const volatile int>);
static_assert(std::is_same_v<typename s::tuple_element<2, const volatile fields>::type, char&>);
static_assert(std::is_same_v<s::tuple_element_t<0, const volatile fields>, const volatile long>);
using numbers = s::complex<float>;
static_assert(s::tuple_size<numbers>::value == 2);
static_assert(std::is_same_v<typename s::tuple_element<0, numbers>::type, float>);
static_assert(std::is_same_v<typename s::tuple_element<1, numbers>::type, float>);
static_assert(std::is_same_v<s::tuple_element_t<1, const numbers>, const float>);

int main()
{
    char c = 'x';
    fields data{11L, 9, c};
    auto& [first, second, third] = data;
    third = 'z';
    return first != 11 || second != 9 || c != 'z' || &s::get<2>(data) != &c;
}
