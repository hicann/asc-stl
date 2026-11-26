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

#include <asc/std/utility>
#include <type_traits>

namespace s = asc::std;
using pair = s::pair<const short, long&>;
static_assert(std::is_same_v<pair::first_type, const short> && std::is_same_v<pair::second_type, long&>);
static_assert(s::tuple_size<pair>::value == 2);
static_assert(std::is_same_v<typename s::tuple_element<0, pair>::type, const short>);
static_assert(std::is_same_v<typename s::tuple_element<1, pair>::type, long&>);
static_assert(std::is_same_v<s::tuple_element_t<1, const pair>, long&>);
using seq = s::integer_sequence<short, 3, -1, 3>;
static_assert(s::tuple_size<seq>::value == 3);
static_assert(std::is_same_v<typename s::tuple_element<0, seq>::type, short>);
static_assert(std::is_same_v<typename s::tuple_element<2, const seq>::type, short>);
static_assert(s::get<0>(seq{}) == 3 && s::get<1>(seq{}) == -1 && s::get<2>(seq{}) == 3);

int main()
{
    return 0;
}
