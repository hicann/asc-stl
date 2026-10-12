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
#ifndef CANN_ASC_STL_ASC_STD___TYPE_TRAITS_IS_EXTENDED_FLOATING_POINT_H
#define CANN_ASC_STL_ASC_STD___TYPE_TRAITS_IS_EXTENDED_FLOATING_POINT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/__detail/execution_space.h>
#include <asc/std/__type_traits/remove_cv.h>

// Inline equivalents of the dev extended-data-type capability gates (dev
// __asc/extended_data_types.h / __asc/asc_capabilities.h; the base __config
// does not provide them). half and bfloat16_t are baseline CCE scalar types,
// so they are available in every ASC device compilation mode.
#if !defined(CANN_ASC_STL_DETAIL_HAS_HALF)
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#define CANN_ASC_STL_DETAIL_HAS_HALF() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_HALF() 0
#endif
#endif  // CANN_ASC_STL_DETAIL_HAS_HALF

#if !defined(CANN_ASC_STL_DETAIL_HAS_BFLOAT16)
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#define CANN_ASC_STL_DETAIL_HAS_BFLOAT16() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_BFLOAT16() 0
#endif
#endif  // CANN_ASC_STL_DETAIL_HAS_BFLOAT16

// Inline AI-core family detection (dev __asc/asc_capabilities.h): the stable
// family markers are the dedicated toolchain macros __DAV_C310__ /
// __DAV_C310_VEC__; legacy __NPU_ARCH__ values are toolchain-version
// dependent and kept only as a secondary fallback.
#if !defined(CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_950)
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() &&            \
    (defined(__DAV_C310__) || defined(__DAV_C310_VEC__) || \
        (defined(__NPU_ARCH__) && (__NPU_ARCH__ == 5102 || __NPU_ARCH__ == 5161 || __NPU_ARCH__ == 3101)))
#define CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_950() 1
#else
#define CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_950() 0
#endif
#endif  // CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_950

#if !defined(CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_C310)
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && !CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_950() && \
    (defined(__DAV_C310__) || defined(__DAV_C310_VEC__))
#define CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_C310() 1
#else
#define CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_C310() 0
#endif
#endif  // CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_C310

// The FP8 scalar spellings (e4m3, e5m2, e8m0) are builtin types on the 950
// family in both compilation modes; the C310 family provides them in
// mixed-mode builds only.
#if !defined(CANN_ASC_STL_DETAIL_HAS_FP8_E4M3)
#if CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_950() || \
    (CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_C310() && !CANN_ASC_STL_DETAIL_SIMT_COMPILATION())
#define CANN_ASC_STL_DETAIL_HAS_FP8_E4M3() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_FP8_E4M3() 0
#endif
#endif  // CANN_ASC_STL_DETAIL_HAS_FP8_E4M3

#if !defined(CANN_ASC_STL_DETAIL_HAS_FP8_E5M2)
#if CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_950() || \
    (CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_C310() && !CANN_ASC_STL_DETAIL_SIMT_COMPILATION())
#define CANN_ASC_STL_DETAIL_HAS_FP8_E5M2() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_FP8_E5M2() 0
#endif
#endif  // CANN_ASC_STL_DETAIL_HAS_FP8_E5M2

#if !defined(CANN_ASC_STL_DETAIL_HAS_FP8_E8M0)
#if CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_950() || \
    (CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_C310() && !CANN_ASC_STL_DETAIL_SIMT_COMPILATION())
#define CANN_ASC_STL_DETAIL_HAS_FP8_E8M0() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_FP8_E8M0() 0
#endif
#endif  // CANN_ASC_STL_DETAIL_HAS_FP8_E8M0

// Inline equivalent of the dev CANN_ASC_STL_DETAIL_HAS_FLOAT128() gate
// (dev __asc/extended_data_types.h; same inline copy as
// __floating_point/native_type.h): __float128 needs __int128, a Linux
// non-ARM64 target, a compiler that advertises the type, host compilation
// only (CCE device compilation does not support __float128), and GCC must
// not run strict-ANSI without extended numeric literals (no q/Q floating
// point literals under __STRICT_ANSI__).
#if !defined(CANN_ASC_STL_DETAIL_HAS_FLOAT128)
#define CANN_ASC_STL_DETAIL_HAS_FLOAT128() 0
#if (defined(__SIZEOF_FLOAT128__) || defined(__FLOAT128__)) && defined(__SIZEOF_INT128__) &&                         \
    (defined(__linux__) || defined(__LP64__)) &&                                                                     \
    !(defined(__aarch64__) || defined(_M_ARM64) || defined(_M_ARM64EC)) && !defined(ASC_DISABLE_FLOAT128_SUPPORT) && \
    !defined(ASC_DISABLE_INT128_SUPPORT) && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() &&                             \
    !(defined(__GNUC__) && !defined(__clang__) && defined(__STRICT_ANSI__) &&                                        \
        !defined(ASC_GCC_HAS_EXTENDED_NUMERIC_LITERALS))
#undef CANN_ASC_STL_DETAIL_HAS_FLOAT128
#define CANN_ASC_STL_DETAIL_HAS_FLOAT128() 1
#endif
#endif  // CANN_ASC_STL_DETAIL_HAS_FLOAT128

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
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

template <class T>
inline constexpr bool __is_cv_extended_floating_point_v = __is_extended_floating_point_v<asc::std::remove_cv_t<T>>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___TYPE_TRAITS_IS_EXTENDED_FLOATING_POINT_H
