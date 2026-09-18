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

#ifndef CANN_ASC_STL_STD_DETAIL_FWD_CHAR_TRAITS_H
#define CANN_ASC_STL_STD_DETAIL_FWD_CHAR_TRAITS_H

#include <asc/std/detail/__config>

// std:: forward declarations

#if CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_STD

template <class _CharT>
struct char_traits;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_STD
#endif  // CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()

// asc::std:: forward declarations

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _CharT>
struct char_traits;
template <>
struct char_traits<char>;
#if CANN_ASC_STL_DETAIL_HAS_CHAR8_T()
template <>
struct char_traits<char8_t>;
#endif  // CANN_ASC_STL_DETAIL_HAS_CHAR8_T()
template <>
struct char_traits<char16_t>;
template <>
struct char_traits<char32_t>;
#if CANN_ASC_STL_DETAIL_HAS_WCHAR_T()
template <>
struct char_traits<wchar_t>;
#endif  // CANN_ASC_STL_DETAIL_HAS_WCHAR_T()

template <class _Tp>
inline constexpr bool __is_std_char_traits_v = false;
#if CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()
template <class _Tp>
inline constexpr bool __is_std_char_traits_v<::std::char_traits<_Tp>> = true;
#endif  // CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()

template <class _Tp>
inline constexpr bool __is_asc_std_char_traits_v = false;
template <class _Tp>
inline constexpr bool __is_asc_std_char_traits_v<char_traits<_Tp>> = true;  // NOLINT(build/include_what_you_use)

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FWD_CHAR_TRAITS_H
