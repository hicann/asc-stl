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
#ifndef CANN_ASC_STL_STD_DETAIL_FLOATING_POINT_TRAITS_H
#define CANN_ASC_STL_STD_DETAIL_FLOATING_POINT_TRAITS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__floating_point/properties.h>
#include <asc/std/__fwd/fp.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// __is_std_fp_v

template <class T>
inline constexpr bool __is_std_fp_v = false;

template <class T>
inline constexpr bool __is_std_fp_v<const T> = __is_std_fp_v<T>;

template <class T>
inline constexpr bool __is_std_fp_v<volatile T> = __is_std_fp_v<T>;

template <class T>
inline constexpr bool __is_std_fp_v<const volatile T> = __is_std_fp_v<T>;

template <>
inline constexpr bool __is_std_fp_v<float> = true;

template <>
inline constexpr bool __is_std_fp_v<double> = true;

template <>
inline constexpr bool __is_std_fp_v<long double> = true;

// __is_ext_asc_fp_v
//
// The neutral Ascend extended floating-point predicate. The ASC-STL wrapper
// vocabulary is a delivered extended family; the SoC-gated CCE fp8/fp4/hifloat
// scalar specializations are added by the later vector-family batch, whose
// execution target supports those type spellings.

template <class T>
inline constexpr bool __is_ext_asc_fp_v = false;

template <class T>
inline constexpr bool __is_ext_asc_fp_v<const T> = __is_ext_asc_fp_v<T>;

template <class T>
inline constexpr bool __is_ext_asc_fp_v<volatile T> = __is_ext_asc_fp_v<T>;

template <class T>
inline constexpr bool __is_ext_asc_fp_v<const volatile T> = __is_ext_asc_fp_v<T>;

template <__fp_format Fmt>
inline constexpr bool __is_ext_asc_fp_v<__asc_fp<Fmt>> = true;

// __is_ext_fp_v

template <class T>
inline constexpr bool __is_ext_fp_v = __is_ext_asc_fp_v<T>;

// __is_fp_v

template <class T>
inline constexpr bool __is_fp_v = __is_std_fp_v<T> || __is_ext_fp_v<T>;

// __fp_is_subset_v

template <__fp_format LhsFmt, __fp_format RhsFmt>
inline constexpr bool __fp_is_subset_v = (!__fp_is_signed_v<LhsFmt> || __fp_is_signed_v<RhsFmt>) &&
    __fp_exp_min_v<LhsFmt> >= __fp_exp_min_v<RhsFmt> && __fp_exp_max_v<LhsFmt> <= __fp_exp_max_v<RhsFmt> &&
    __fp_digits_v<LhsFmt> <= __fp_digits_v<RhsFmt> && (!__fp_has_denorm_v<LhsFmt> || __fp_has_denorm_v<RhsFmt>);

// __fp_is_subset_of_v

template <class Lhs, class Rhs>
inline constexpr bool __fp_is_subset_of_v = __fp_is_subset_v<__fp_format_of_v<Lhs>, __fp_format_of_v<Rhs>>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_FLOATING_POINT_TRAITS_H
