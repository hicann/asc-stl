/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#ifndef CANN_ASC_STL_STD_DETAIL_FWD_STRING_VIEW_H
#define CANN_ASC_STL_STD_DETAIL_FWD_STRING_VIEW_H

#include <asc/std/detail/__config>

#include <asc/std/__fwd/char_traits.h>

// std:: forward declarations

#if CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB() && __cpp_lib_string_view >= 201606L
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_STD

template <class _CharT, class _Traits>
class basic_string_view;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_STD
#endif  // CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB() && __cpp_lib_string_view >= 201606L

// asc::std:: forward declarations

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _CharT, class _Traits = char_traits<_CharT>>  // NOLINT(build/include_what_you_use)
class basic_string_view;

using string_view = basic_string_view<char>;
#if CANN_ASC_STL_DETAIL_HAS_CHAR8_T()
using u8string_view = basic_string_view<char8_t>;
#endif  // CANN_ASC_STL_DETAIL_HAS_CHAR8_T()
using u16string_view = basic_string_view<char16_t>;
using u32string_view = basic_string_view<char32_t>;
#if CANN_ASC_STL_DETAIL_HAS_WCHAR_T()
using wstring_view = basic_string_view<wchar_t>;
#endif  // CANN_ASC_STL_DETAIL_HAS_WCHAR_T()

template <class _Tp>
inline constexpr bool __is_std_basic_string_view_v = false;
#if CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB() && __cpp_lib_string_view >= 201606L
template <class _CharT, class _Traits>
inline constexpr bool __is_std_basic_string_view_v<::std::basic_string_view<_CharT, _Traits>> = true;
#endif  // CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB() && __cpp_lib_string_view >= 201606L

template <class _Tp>
inline constexpr bool __is_asc_std_basic_string_view_v = false;
template <class _Tp>
inline constexpr bool __is_asc_std_basic_string_view_v<const _Tp> = __is_asc_std_basic_string_view_v<_Tp>;
template <class _Tp>
inline constexpr bool __is_asc_std_basic_string_view_v<volatile _Tp> = __is_asc_std_basic_string_view_v<_Tp>;
template <class _Tp>
inline constexpr bool __is_asc_std_basic_string_view_v<const volatile _Tp> = __is_asc_std_basic_string_view_v<_Tp>;
template <class _CharT, class _Traits>
inline constexpr bool __is_asc_std_basic_string_view_v<basic_string_view<_CharT, _Traits>> = true;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FWD_STRING_VIEW_H
