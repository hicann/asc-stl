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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_INTEGRAL_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_INTEGRAL_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/remove_cv.h>

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(is_integral)
#define CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_INTEGRAL(...) __is_integral(__VA_ARGS__)
#endif  // CANN_ASC_STL_DETAIL_CHECK_BUILTIN(is_integral)

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if defined(CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_INTEGRAL)

template <class _Tp>
struct is_integral : bool_constant<CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_INTEGRAL(_Tp)> {};

template <class _Tp>
inline constexpr bool is_integral_v = CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_INTEGRAL(_Tp);

#else  // ^^^ CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_INTEGRAL ^^^ / vvv !CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_INTEGRAL vvv

template <class _Tp>
inline constexpr bool __asc_is_integral_helper_v = false;

template <>
inline constexpr bool __asc_is_integral_helper_v<bool> = true;

// char types

template <>
inline constexpr bool __asc_is_integral_helper_v<char> = true;

#if CANN_ASC_STL_DETAIL_HAS_CHAR8_T()
template <>
inline constexpr bool __asc_is_integral_helper_v<char8_t> = true;
#endif  // CANN_ASC_STL_DETAIL_HAS_CHAR8_T()

template <>
inline constexpr bool __asc_is_integral_helper_v<char16_t> = true;

template <>
inline constexpr bool __asc_is_integral_helper_v<char32_t> = true;

template <>
inline constexpr bool __asc_is_integral_helper_v<wchar_t> = true;

// signed integer types

template <>
inline constexpr bool __asc_is_integral_helper_v<signed char> = true;

template <>
inline constexpr bool __asc_is_integral_helper_v<short> = true;

template <>
inline constexpr bool __asc_is_integral_helper_v<int> = true;

template <>
inline constexpr bool __asc_is_integral_helper_v<long> = true;

template <>
inline constexpr bool __asc_is_integral_helper_v<long long> = true;

#if CANN_ASC_STL_DETAIL_HAS_INT128()
template <>
inline constexpr bool __asc_is_integral_helper_v<__int128_t> = true;
#endif  // CANN_ASC_STL_DETAIL_HAS_INT128()

// unsigned integer types

template <>
inline constexpr bool __asc_is_integral_helper_v<unsigned char> = true;

template <>
inline constexpr bool __asc_is_integral_helper_v<unsigned short> = true;

template <>
inline constexpr bool __asc_is_integral_helper_v<unsigned int> = true;

template <>
inline constexpr bool __asc_is_integral_helper_v<unsigned long> = true;

template <>
inline constexpr bool __asc_is_integral_helper_v<unsigned long long> = true;

#if CANN_ASC_STL_DETAIL_HAS_INT128()
template <>
inline constexpr bool __asc_is_integral_helper_v<__uint128_t> = true;
#endif  // CANN_ASC_STL_DETAIL_HAS_INT128()

template <class _Tp>
inline constexpr bool is_integral_v = __asc_is_integral_helper_v<remove_cv_t<_Tp> >;

template <class _Tp>
struct is_integral : public bool_constant<is_integral_v<_Tp> > {};

#endif  // ^^^ !CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_INTEGRAL ^^^

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_INTEGRAL_H
