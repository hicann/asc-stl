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

#ifndef CANN_ASC_STL_ASC_STD___FWD_STRING_VIEW_H
#define CANN_ASC_STL_ASC_STD___FWD_STRING_VIEW_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__fwd/char_traits.h>

// Hosted ::std interoperation gate: a host standard library has been pulled in.
#ifndef CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB
#if defined(__GLIBCXX__) || defined(_LIBCPP_VERSION) || defined(_MSVC_STL_VERSION)
#define CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB() 0
#endif
#endif  // CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB

// std:: forward declarations

#if CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB() && defined(__cpp_lib_string_view) && __cpp_lib_string_view >= 201606L
namespace std {
template <class, class>
class basic_string_view;
}  // namespace std
#endif  // CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB() && __cpp_lib_string_view >= 201606L

// asc::std:: forward declarations

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Character, class Traits = char_traits<Character>>  // NOLINT(build/include_what_you_use)
class basic_string_view;
using string_view = basic_string_view<char>;
#if CANN_ASC_STL_DETAIL_HAS_CHAR8_T()
using u8string_view = basic_string_view<char8_t>;
#endif
using u16string_view = basic_string_view<char16_t>;
using u32string_view = basic_string_view<char32_t>;
using wstring_view = basic_string_view<wchar_t>;
template <class T>
inline constexpr bool __is_std_basic_string_view_v = false;
#if CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB() && defined(__cpp_lib_string_view) && __cpp_lib_string_view >= 201606L
template <class Character, class Traits>
inline constexpr bool __is_std_basic_string_view_v<::std::basic_string_view<Character, Traits>> = true;
#endif  // CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB() && __cpp_lib_string_view >= 201606L
template <class T>
inline constexpr bool __is_asc_std_basic_string_view_v = false;
template <class T>
inline constexpr bool __is_asc_std_basic_string_view_v<const T> = __is_asc_std_basic_string_view_v<T>;
template <class T>
inline constexpr bool __is_asc_std_basic_string_view_v<volatile T> = __is_asc_std_basic_string_view_v<T>;
template <class T>
inline constexpr bool __is_asc_std_basic_string_view_v<const volatile T> = __is_asc_std_basic_string_view_v<T>;
template <class Character, class Traits>
inline constexpr bool __is_asc_std_basic_string_view_v<basic_string_view<Character, Traits>> = true;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___FWD_STRING_VIEW_H
