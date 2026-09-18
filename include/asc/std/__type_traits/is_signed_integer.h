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

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/remove_cv.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp>
inline constexpr bool __asc_is_signed_integer_v = false;

template <>
inline constexpr bool __asc_is_signed_integer_v<signed char> = true;

template <>
inline constexpr bool __asc_is_signed_integer_v<signed short> = true;

template <>
inline constexpr bool __asc_is_signed_integer_v<signed int> = true;

template <>
inline constexpr bool __asc_is_signed_integer_v<signed long> = true;

template <>
inline constexpr bool __asc_is_signed_integer_v<signed long long> = true;

#if CANN_ASC_STL_DETAIL_HAS_INT128()
template <>
inline constexpr bool __asc_is_signed_integer_v<__int128_t> = true;
#endif  // CANN_ASC_STL_DETAIL_HAS_INT128()

template <class _Tp>
inline constexpr bool __asc_is_cv_signed_integer_v = __asc_is_signed_integer_v<remove_cv_t<_Tp>>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_SIGNED_INTEGER_H
