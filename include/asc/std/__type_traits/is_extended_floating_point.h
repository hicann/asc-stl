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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_EXTENDED_FLOATING_POINT_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_EXTENDED_FLOATING_POINT_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/remove_cv.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp>
inline constexpr bool __is_extended_floating_point_v = false;

#if CANN_ASC_STL_DETAIL_HAS_HALF()
template <>
inline constexpr bool __is_extended_floating_point_v<half> = true;
#endif  // CANN_ASC_STL_DETAIL_HAS_HALF()

#if CANN_ASC_STL_DETAIL_HAS_BFLOAT16()
template <>
inline constexpr bool __is_extended_floating_point_v<bfloat16_t> = true;
#endif  // CANN_ASC_STL_DETAIL_HAS_BFLOAT16()

#if CANN_ASC_STL_DETAIL_HAS_FP8_E4M3()
template <>
inline constexpr bool __is_extended_floating_point_v<float8_e4m3_t> = true;
#endif  // CANN_ASC_STL_DETAIL_HAS_FP8_E4M3()

#if CANN_ASC_STL_DETAIL_HAS_FP8_E5M2()
template <>
inline constexpr bool __is_extended_floating_point_v<float8_e5m2_t> = true;
#endif  // CANN_ASC_STL_DETAIL_HAS_FP8_E5M2()

#if CANN_ASC_STL_DETAIL_HAS_FP8_E8M0()
template <>
inline constexpr bool __is_extended_floating_point_v<float8_e8m0_t> = true;
#endif  // CANN_ASC_STL_DETAIL_HAS_FP8_E8M0()

// FP6 E2M3, FP6 E3M2, and FP4 E2M1 have no scalar equivalent in ASC SIMT,
// so no specializations are provided for those formats.

#if CANN_ASC_STL_DETAIL_HAS_FLOAT128()
template <>
inline constexpr bool __is_extended_floating_point_v<__float128> = true;
#endif  // CANN_ASC_STL_DETAIL_HAS_FLOAT128()

template <class _Tp>
inline constexpr bool __is_cv_extended_floating_point_v = __is_extended_floating_point_v<asc::std::remove_cv_t<_Tp>>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_EXTENDED_FLOATING_POINT_H
