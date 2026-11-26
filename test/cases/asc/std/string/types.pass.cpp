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

#include <asc/std/string>
#include <cstddef>
#include <type_traits>
#include "../../../../support/b028_allocator.h"

namespace s = asc::std;

using alloc = asc_stl_b028_test::arena_allocator<char>;
using text = s::basic_string<char, s::char_traits<char>, alloc>;
static_assert(std::is_same_v<text::value_type, char>);
static_assert(std::is_same_v<text::size_type, std::size_t>);
static_assert(std::is_same_v<text::reference, char&>);
static_assert(std::is_same_v<text::const_reference, const char&>);
static_assert(std::is_same_v<text::pointer, char*>);
static_assert(std::is_same_v<text::const_pointer, const char*>);
static_assert(std::is_same_v<text::iterator, char*>);
static_assert(std::is_same_v<text::const_iterator, const char*>);
static_assert(std::is_same_v<text::traits_type, s::char_traits<char>>);
static_assert(std::is_same_v<text::allocator_type, alloc>);
template <class Char>
constexpr bool traits()
{
    using tr = s::char_traits<Char>;
    return std::is_same_v<typename tr::char_type, Char> && std::is_integral_v<typename tr::int_type> &&
        std::is_same_v<decltype(tr::to_int_type(Char{})), typename tr::int_type>;
}
static_assert(traits<char>() && traits<wchar_t>() && traits<char16_t>() && traits<char32_t>());
#if defined(__cpp_char8_t)
static_assert(traits<char8_t>());
#endif

static_assert(!std::is_copy_constructible_v<text> && !std::is_copy_assignable_v<text>);
static_assert(!std::is_move_constructible_v<text> && !std::is_move_assignable_v<text>);

int main()
{}
