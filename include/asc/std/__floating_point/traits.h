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
#include <asc/std/__type_traits/is_extended_floating_point.h>

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
// The neutral Ascend extended floating-point predicate: the __asc_fp wrapper
// vocabulary plus the CCE native extended scalars (half, bfloat16_t and the
// fp8 spellings) when the capability gates in
// __type_traits/is_extended_floating_point.h provide them.

template <class T>
inline constexpr bool __is_ext_asc_fp_v = false;

template <class T>
inline constexpr bool __is_ext_asc_fp_v<const T> = __is_ext_asc_fp_v<T>;

template <class T>
inline constexpr bool __is_ext_asc_fp_v<volatile T> = __is_ext_asc_fp_v<T>;

template <class T>
inline constexpr bool __is_ext_asc_fp_v<const volatile T> = __is_ext_asc_fp_v<T>;

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

template <__fp_format Fmt>
inline constexpr bool __is_ext_asc_fp_v<__asc_fp<Fmt>> = true;

// __fp_is_compiler_fp_v
//
// Traits-local equivalent of the compiler-extension floating-point predicate
// (__float128 when the detection gate provides it). The
// __is_ext_compiler_fp_v spelling stays owned by the inline copy in
// __floating_point/native_type.h, which includes this header, so a same-name
// definition here would collide in every translation unit that pulls both.

template <class T>
inline constexpr bool __fp_is_compiler_fp_v = false;

template <class T>
inline constexpr bool __fp_is_compiler_fp_v<const T> = __fp_is_compiler_fp_v<T>;

template <class T>
inline constexpr bool __fp_is_compiler_fp_v<volatile T> = __fp_is_compiler_fp_v<T>;

template <class T>
inline constexpr bool __fp_is_compiler_fp_v<const volatile T> = __fp_is_compiler_fp_v<T>;

#if CANN_ASC_STL_DETAIL_HAS_FLOAT128()
template <>
inline constexpr bool __fp_is_compiler_fp_v<__float128> = true;
#endif  // CANN_ASC_STL_DETAIL_HAS_FLOAT128()

// __is_ext_accl_fp_v
//
// The __asc_fp wrapper vocabulary proper. The wrappers also satisfy
// __is_ext_asc_fp_v above; storage-layer dispatch tests this predicate first.

template <class T>
inline constexpr bool __is_ext_accl_fp_v = false;

template <class T>
inline constexpr bool __is_ext_accl_fp_v<const T> = __is_ext_accl_fp_v<T>;

template <class T>
inline constexpr bool __is_ext_accl_fp_v<volatile T> = __is_ext_accl_fp_v<T>;

template <class T>
inline constexpr bool __is_ext_accl_fp_v<const volatile T> = __is_ext_accl_fp_v<T>;

template <__fp_format Fmt>
inline constexpr bool __is_ext_accl_fp_v<__asc_fp<Fmt>> = true;

// __is_ext_fp_v

template <class T>
inline constexpr bool __is_ext_fp_v = __is_ext_asc_fp_v<T> || __fp_is_compiler_fp_v<T> || __is_ext_accl_fp_v<T>;

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
