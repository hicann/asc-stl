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
#ifndef CANN_ASC_STL_STD_DETAIL_FLOATING_POINT_PROPERTIES_H
#define CANN_ASC_STL_STD_DETAIL_FLOATING_POINT_PROPERTIES_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__floating_point/format.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// __fp_is_signed_v

template <__fp_format Fmt>
inline constexpr bool __fp_is_signed_v = true;

template <>
inline constexpr bool __fp_is_signed_v<__fp_format::__fp8_e8m0> = false;

// __fp_exp_nbits_v

template <__fp_format Fmt>
inline constexpr int __fp_exp_nbits_v = 0;

template <>
inline constexpr int __fp_exp_nbits_v<__fp_format::__binary16> = 5;

template <>
inline constexpr int __fp_exp_nbits_v<__fp_format::__binary32> = 8;

template <>
inline constexpr int __fp_exp_nbits_v<__fp_format::__binary64> = 11;

template <>
inline constexpr int __fp_exp_nbits_v<__fp_format::__binary128> = 15;

template <>
inline constexpr int __fp_exp_nbits_v<__fp_format::__bfloat16> = 8;

template <>
inline constexpr int __fp_exp_nbits_v<__fp_format::__fp80_x86> = 15;

template <>
inline constexpr int __fp_exp_nbits_v<__fp_format::__fp8_e4m3> = 4;

template <>
inline constexpr int __fp_exp_nbits_v<__fp_format::__fp8_e5m2> = 5;

template <>
inline constexpr int __fp_exp_nbits_v<__fp_format::__fp8_e8m0> = 8;

template <>
inline constexpr int __fp_exp_nbits_v<__fp_format::__fp6_e2m3> = 2;

template <>
inline constexpr int __fp_exp_nbits_v<__fp_format::__fp6_e3m2> = 3;

template <>
inline constexpr int __fp_exp_nbits_v<__fp_format::__fp4_e2m1> = 2;

// __fp_exp_bias_v

template <__fp_format Fmt>
inline constexpr int __fp_exp_bias_v = (1 << (__fp_exp_nbits_v<Fmt> - 1)) - 1;

// __fp_exp_min_v

template <__fp_format Fmt>
inline constexpr int __fp_exp_min_v = 1 - __fp_exp_bias_v<Fmt>;

template <>
inline constexpr int __fp_exp_min_v<__fp_format::__fp8_e8m0> = -127;

// __fp_exp_max_v

template <__fp_format Fmt>
inline constexpr int __fp_exp_max_v = (1 << __fp_exp_nbits_v<Fmt>)-2 - __fp_exp_bias_v<Fmt>;

// The narrow vendor formats reserve exponent encodings differently from the
// IEEE progression, so their maxima are stated per format.

template <>
inline constexpr int __fp_exp_max_v<__fp_format::__fp8_e4m3> = 8;

template <>
inline constexpr int __fp_exp_max_v<__fp_format::__fp6_e2m3> = 2;

template <>
inline constexpr int __fp_exp_max_v<__fp_format::__fp6_e3m2> = 4;

template <>
inline constexpr int __fp_exp_max_v<__fp_format::__fp4_e2m1> = 2;

// __fp_mant_nbits_v

template <__fp_format Fmt>
inline constexpr int __fp_mant_nbits_v = 0;

template <>
inline constexpr int __fp_mant_nbits_v<__fp_format::__binary16> = 10;

template <>
inline constexpr int __fp_mant_nbits_v<__fp_format::__binary32> = 23;

template <>
inline constexpr int __fp_mant_nbits_v<__fp_format::__binary64> = 52;

template <>
inline constexpr int __fp_mant_nbits_v<__fp_format::__binary128> = 112;

template <>
inline constexpr int __fp_mant_nbits_v<__fp_format::__bfloat16> = 7;

template <>
inline constexpr int __fp_mant_nbits_v<__fp_format::__fp80_x86> = 64;

template <>
inline constexpr int __fp_mant_nbits_v<__fp_format::__fp8_e4m3> = 3;

template <>
inline constexpr int __fp_mant_nbits_v<__fp_format::__fp8_e5m2> = 2;

template <>
inline constexpr int __fp_mant_nbits_v<__fp_format::__fp8_e8m0> = 0;

template <>
inline constexpr int __fp_mant_nbits_v<__fp_format::__fp6_e2m3> = 3;

template <>
inline constexpr int __fp_mant_nbits_v<__fp_format::__fp6_e3m2> = 2;

template <>
inline constexpr int __fp_mant_nbits_v<__fp_format::__fp4_e2m1> = 1;

// __fp_has_implicit_bit_v

template <__fp_format Fmt>
inline constexpr bool __fp_has_implicit_bit_v = true;

template <>
inline constexpr bool __fp_has_implicit_bit_v<__fp_format::__fp80_x86> = false;

// __fp_digits_v

template <__fp_format Fmt>
inline constexpr int __fp_digits_v = __fp_mant_nbits_v<Fmt> + static_cast<int>(__fp_has_implicit_bit_v<Fmt>);

// __fp_has_denorm_v

template <__fp_format Fmt>
inline constexpr bool __fp_has_denorm_v = true;

template <>
inline constexpr bool __fp_has_denorm_v<__fp_format::__fp8_e8m0> = false;

// __fp_has_inf_v

template <__fp_format Fmt>
inline constexpr bool __fp_has_inf_v = true;

template <>
inline constexpr bool __fp_has_inf_v<__fp_format::__fp8_e4m3> = false;

template <>
inline constexpr bool __fp_has_inf_v<__fp_format::__fp8_e8m0> = false;

template <>
inline constexpr bool __fp_has_inf_v<__fp_format::__fp6_e2m3> = false;

template <>
inline constexpr bool __fp_has_inf_v<__fp_format::__fp6_e3m2> = false;

template <>
inline constexpr bool __fp_has_inf_v<__fp_format::__fp4_e2m1> = false;

// __fp_has_nan_v

template <__fp_format Fmt>
inline constexpr bool __fp_has_nan_v = true;

template <>
inline constexpr bool __fp_has_nan_v<__fp_format::__fp6_e2m3> = false;

template <>
inline constexpr bool __fp_has_nan_v<__fp_format::__fp6_e3m2> = false;

template <>
inline constexpr bool __fp_has_nan_v<__fp_format::__fp4_e2m1> = false;

// __fp_has_nans_v: signaling-NaN capability, distinct from quiet NaNs.
// E4M3 and E8M0 have a NaN encoding but no distinct signaling encoding.

template <__fp_format Fmt>
inline constexpr bool __fp_has_nans_v = true;

template <>
inline constexpr bool __fp_has_nans_v<__fp_format::__fp8_e4m3> = false;

template <>
inline constexpr bool __fp_has_nans_v<__fp_format::__fp8_e8m0> = false;

template <>
inline constexpr bool __fp_has_nans_v<__fp_format::__fp6_e2m3> = false;

template <>
inline constexpr bool __fp_has_nans_v<__fp_format::__fp6_e3m2> = false;

template <>
inline constexpr bool __fp_has_nans_v<__fp_format::__fp4_e2m1> = false;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_FLOATING_POINT_PROPERTIES_H
