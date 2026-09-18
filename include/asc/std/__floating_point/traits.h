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

#include <asc/std/detail/__config>

#include <asc/std/__floating_point/properties.h>
#include <asc/std/__fwd/fp.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp>
inline constexpr bool __is_std_fp_v = false;

template <class _Tp>
inline constexpr bool __is_std_fp_v<const _Tp> = __is_std_fp_v<_Tp>;
template <class _Tp>
inline constexpr bool __is_std_fp_v<volatile _Tp> = __is_std_fp_v<_Tp>;
template <class _Tp>
inline constexpr bool __is_std_fp_v<const volatile _Tp> = __is_std_fp_v<_Tp>;

template <>
inline constexpr bool __is_std_fp_v<float> = true;
template <>
inline constexpr bool __is_std_fp_v<double> = true;
template <>
inline constexpr bool __is_std_fp_v<long double> = true;

template <class _Tp>
inline constexpr bool __is_ext_asc_fp_v = false;

template <class _Tp>
inline constexpr bool __is_ext_asc_fp_v<const _Tp> = __is_ext_asc_fp_v<_Tp>;
template <class _Tp>
inline constexpr bool __is_ext_asc_fp_v<volatile _Tp> = __is_ext_asc_fp_v<_Tp>;
template <class _Tp>
inline constexpr bool __is_ext_asc_fp_v<const volatile _Tp> = __is_ext_asc_fp_v<_Tp>;

#if CANN_ASC_STL_DETAIL_HAS_HALF()
template <>
inline constexpr bool __is_ext_asc_fp_v<half> = true;
#endif  // CANN_ASC_STL_DETAIL_HAS_HALF()

#if CANN_ASC_STL_DETAIL_HAS_BFLOAT16()
template <>
inline constexpr bool __is_ext_asc_fp_v<bfloat16_t> = true;
#endif  // CANN_ASC_STL_DETAIL_HAS_BFLOAT16()

#if CANN_ASC_STL_DETAIL_HAS_FP8_E4M3()
template <>
inline constexpr bool __is_ext_asc_fp_v<float8_e4m3_t> = true;
#endif  // CANN_ASC_STL_DETAIL_HAS_FP8_E4M3()

#if CANN_ASC_STL_DETAIL_HAS_FP8_E5M2()
template <>
inline constexpr bool __is_ext_asc_fp_v<float8_e5m2_t> = true;
#endif  // CANN_ASC_STL_DETAIL_HAS_FP8_E5M2()

#if CANN_ASC_STL_DETAIL_HAS_FP8_E8M0()
template <>
inline constexpr bool __is_ext_asc_fp_v<float8_e8m0_t> = true;
#endif  // CANN_ASC_STL_DETAIL_HAS_FP8_E8M0()

template <class _Tp>
inline constexpr bool __is_ext_compiler_fp_v = false;

template <class _Tp>
inline constexpr bool __is_ext_compiler_fp_v<const _Tp> = __is_ext_compiler_fp_v<_Tp>;
template <class _Tp>
inline constexpr bool __is_ext_compiler_fp_v<volatile _Tp> = __is_ext_compiler_fp_v<_Tp>;
template <class _Tp>
inline constexpr bool __is_ext_compiler_fp_v<const volatile _Tp> = __is_ext_compiler_fp_v<_Tp>;

#if CANN_ASC_STL_DETAIL_HAS_FLOAT128()
template <>
inline constexpr bool __is_ext_compiler_fp_v<__float128> = true;
#endif  // CANN_ASC_STL_DETAIL_HAS_FLOAT128()

template <class _Tp>
inline constexpr bool __is_ext_accl_fp_v = false;

template <class _Tp>
inline constexpr bool __is_ext_accl_fp_v<const _Tp> = __is_ext_accl_fp_v<_Tp>;
template <class _Tp>
inline constexpr bool __is_ext_accl_fp_v<volatile _Tp> = __is_ext_accl_fp_v<_Tp>;
template <class _Tp>
inline constexpr bool __is_ext_accl_fp_v<const volatile _Tp> = __is_ext_accl_fp_v<_Tp>;

template <__fp_format _Fmt>
inline constexpr bool __is_ext_accl_fp_v<__asc_fp<_Fmt>> = true;

template <class _Tp>
inline constexpr bool __is_ext_fp_v = __is_ext_asc_fp_v<_Tp> || __is_ext_compiler_fp_v<_Tp> || __is_ext_accl_fp_v<_Tp>;

template <class _Tp>
inline constexpr bool __is_fp_v = __is_std_fp_v<_Tp> || __is_ext_fp_v<_Tp>;

template <__fp_format _LhsFmt, __fp_format _RhsFmt>
inline constexpr bool __fp_is_subset_v = (!__fp_is_signed_v<_LhsFmt> || __fp_is_signed_v<_RhsFmt>) &&
    __fp_exp_min_v<_LhsFmt> >= __fp_exp_min_v<_RhsFmt> && __fp_exp_max_v<_LhsFmt> <= __fp_exp_max_v<_RhsFmt> &&
    __fp_digits_v<_LhsFmt> <= __fp_digits_v<_RhsFmt> && (!__fp_has_denorm_v<_LhsFmt> || __fp_has_denorm_v<_RhsFmt>);

template <class _Lhs, class _Rhs>
inline constexpr bool __fp_is_subset_of_v = __fp_is_subset_v<__fp_format_of_v<_Lhs>, __fp_format_of_v<_Rhs>>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FLOATING_POINT_TRAITS_H
