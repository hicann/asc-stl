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
#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_SIGNED_INTEGER_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_SIGNED_INTEGER_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/remove_cv.h>

// Inline equivalent of the dev CANN_ASC_STL_DETAIL_HAS_INT128() gate (dev
// __asc/extended_data_types.h; the base __config does not provide it): the
// compiler-provided 128-bit integer types are available on LP64 Linux targets
// unless explicitly disabled.
#if !defined(CANN_ASC_STL_DETAIL_HAS_INT128)
#if !defined(ASC_DISABLE_INT128_SUPPORT) && (defined(__linux__) || defined(__LP64__)) && defined(__SIZEOF_INT128__)
#define CANN_ASC_STL_DETAIL_HAS_INT128() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_INT128() 0
#endif
#endif  // CANN_ASC_STL_DETAIL_HAS_INT128

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
inline constexpr bool __is_signed_integer_v = false;

template <>
inline constexpr bool __is_signed_integer_v<signed char> = true;

template <>
inline constexpr bool __is_signed_integer_v<signed short> = true;

template <>
inline constexpr bool __is_signed_integer_v<signed int> = true;

template <>
inline constexpr bool __is_signed_integer_v<signed long> = true;

template <>
inline constexpr bool __is_signed_integer_v<signed long long> = true;

#if CANN_ASC_STL_DETAIL_HAS_INT128()
template <>
inline constexpr bool __is_signed_integer_v<__int128_t> = true;
#endif  // CANN_ASC_STL_DETAIL_HAS_INT128()

template <class T>
inline constexpr bool __is_cv_signed_integer_v = __is_signed_integer_v<asc::std::remove_cv_t<T>>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_SIGNED_INTEGER_H
