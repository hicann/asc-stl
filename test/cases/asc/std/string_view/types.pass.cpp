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

#include <asc/std/string_view>
#include <cstddef>
#include <type_traits>

namespace s = asc::std;

using view = s::u16string_view;
static_assert(std::is_same_v<view::traits_type, s::char_traits<char16_t>>);
static_assert(std::is_same_v<view::value_type, char16_t>);
static_assert(std::is_same_v<view::pointer, char16_t*>);
static_assert(std::is_same_v<view::const_pointer, const char16_t*>);
static_assert(std::is_same_v<view::reference, char16_t&>);
static_assert(std::is_same_v<view::const_reference, const char16_t&>);
static_assert(std::is_same_v<view::iterator, const char16_t*>);
static_assert(std::is_same_v<view::const_iterator, const char16_t*>);
static_assert(std::is_same_v<view::reverse_iterator, s::reverse_iterator<const char16_t*>>);
static_assert(std::is_same_v<view::const_reverse_iterator, s::reverse_iterator<const char16_t*>>);
static_assert(std::is_same_v<view::size_type, std::size_t>);
static_assert(std::is_same_v<view::difference_type, std::ptrdiff_t>);
static_assert(std::is_invocable_r_v<std::size_t, s::hash<view>, view>);

int main()
{}
