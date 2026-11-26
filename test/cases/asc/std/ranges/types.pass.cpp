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

#include <asc/std/ranges>
#include <cstddef>
#include <type_traits>
#include <utility>

namespace s = asc::std;

namespace r = s::ranges;
using view = r::iota_view<int, int>;
using iter = decltype(std::declval<view>().begin());
static_assert(std::is_same_v<iter::iterator_concept, s::random_access_iterator_tag>);
static_assert(std::is_same_v<iter::iterator_category, s::random_access_iterator_tag>);
static_assert(std::is_same_v<iter::value_type, int>);
static_assert(std::is_same_v<iter::reference, int>);
static_assert(std::is_same_v<iter::pointer, void>);
using ci = s::counted_iterator<int*>;
using open = r::subrange<int*, s::unreachable_sentinel_t, r::subrange_kind::unsized>;
static_assert(std::is_constructible_v<open, int*, s::unreachable_sentinel_t>);
using sr = r::subrange<ci, s::default_sentinel_t>;
static_assert(std::is_same_v<sr::iterator, ci>);
static_assert(std::is_same_v<sr::sentinel, s::default_sentinel_t>);
static_assert(std::is_same_v<sr::size_type, std::make_unsigned_t<std::ptrdiff_t>>);
static_assert(std::is_base_of_v<r::view_interface<sr>, sr>);
static_assert(s::tuple_size<sr>::value == 2);
static_assert(std::is_same_v<s::tuple_element<0, sr>::type, ci> &&
    std::is_same_v<s::tuple_element<1, sr>::type, s::default_sentinel_t> &&
    std::is_same_v<s::tuple_element<0, const sr>::type, ci> &&
    std::is_same_v<s::tuple_element<1, const sr>::type, s::default_sentinel_t>);

int main()
{}
