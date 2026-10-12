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
#ifndef CANN_ASC_STL_STD_DETAIL_FLOATING_POINT_FORMAT_H
#define CANN_ASC_STL_STD_DETAIL_FLOATING_POINT_FORMAT_H

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
#include <asc/std/__fwd/fp.h>
#include <asc/std/__type_traits/is_extended_floating_point.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/cfloat>

// Inline equivalent of the dev CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE() gate
// (the base __config does not provide it): long double is host-only — ASC
// device compilation (AI Core) does not support long double.
#if !defined(CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE)
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && !defined(ASC_DISABLE_LONG_DOUBLE_SUPPORT)
#define CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE() 0
#endif
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE

// Inline equivalents of the dev FP6 / FP4 scalar capability gates: the scalar
// FP6 E2M3 / E3M2 and FP4 E2M1 spellings have no ASC SIMT equivalent (only the
// packed X2/X4 vector variants exist upstream), so the probes below compile
// them out on every target this delivery supports.
#if !defined(CANN_ASC_STL_DETAIL_HAS_FP6_E2M3)
#define CANN_ASC_STL_DETAIL_HAS_FP6_E2M3() 0
#endif  // CANN_ASC_STL_DETAIL_HAS_FP6_E2M3

#if !defined(CANN_ASC_STL_DETAIL_HAS_FP6_E3M2)
#define CANN_ASC_STL_DETAIL_HAS_FP6_E3M2() 0
#endif  // CANN_ASC_STL_DETAIL_HAS_FP6_E3M2

#if !defined(CANN_ASC_STL_DETAIL_HAS_FP4_E2M1)
#define CANN_ASC_STL_DETAIL_HAS_FP4_E2M1() 0
#endif  // CANN_ASC_STL_DETAIL_HAS_FP4_E2M1

CANN_ASC_STL_BEGIN_NAMESPACE

enum class __fp_format {
    __binary16,   // IEEE 754 binary16
    __binary32,   // IEEE 754 binary32
    __binary64,   // IEEE 754 binary64
    __binary128,  // IEEE 754 binary128
    __bfloat16,   // 16-bit brain float
    __fp80_x86,   // x86 80-bit extended precision
    __fp8_e4m3,   // FP8 E4M3
    __fp8_e5m2,   // FP8 E5M2
    __fp8_e8m0,   // FP8 E8M0
    __fp6_e2m3,   // FP6 E2M3
    __fp6_e3m2,   // FP6 E3M2
    __fp4_e2m1,   // FP4 E2M1

    __invalid,
};

// CCE pure SIMT rejects references to __device__ functions in global
// initializers, so the probing helpers below are plain constexpr (no
// CANN_ASC_STL_API): the __fp_format_of_v variable templates call them from
// their initializers.

// Probing for float / double / long double formats.
template <class T>
CANN_ASC_STL_NODISCARD constexpr __fp_format __fp_format_of_basic() noexcept
{
    if constexpr (is_same_v<T, float>) {
        return __fp_format::__binary32;
    } else if constexpr (is_same_v<T, double>) {
        return __fp_format::__binary64;
    } else if constexpr (is_same_v<T, long double>) {
// 探测用编译器预定义宏（设备侧 <cfloat> 宏面按需裁剪，__LDBL_* 内建恒在）。
#if __LDBL_MIN_EXP__ == -1021 && __LDBL_MAX_EXP__ == 1024 && __LDBL_MANT_DIG__ == 53
        return __fp_format::__binary64;
#elif __LDBL_MIN_EXP__ == -16381 && __LDBL_MAX_EXP__ == 16384 && __LDBL_MANT_DIG__ == 64
        static_assert(
            sizeof(long double) == 16, "the x86 80-bit extended floating-point layout requires a 16-byte long double");
        return __fp_format::__fp80_x86;
#elif __LDBL_MIN_EXP__ == -16381 && __LDBL_MAX_EXP__ == 16384 && __LDBL_MANT_DIG__ == 113
        return __fp_format::__binary128;
#else
#error "Unknown long double format on this frozen toolchain."
#endif
    } else {
        return __fp_format::__invalid;
    }
}

// Probing for half / bfloat16 formats.
template <class T>
CANN_ASC_STL_NODISCARD constexpr __fp_format __fp_format_of_16bit() noexcept
{
#if CANN_ASC_STL_DETAIL_HAS_HALF()
    if constexpr (is_same_v<T, half>) {
        return __fp_format::__binary16;
    } else  // NOLINT(readability/braces)
#endif
#if CANN_ASC_STL_DETAIL_HAS_BFLOAT16()
        if constexpr (is_same_v<T, bfloat16_t>) {
        return __fp_format::__bfloat16;
    } else  // NOLINT(readability/braces)
#endif
    {
        return __fp_format::__invalid;
    }
}

// Probing for the FP8 family formats.
template <class T>
CANN_ASC_STL_NODISCARD constexpr __fp_format __fp_format_of_fp8() noexcept
{
#if CANN_ASC_STL_DETAIL_HAS_FP8_E4M3()
    if constexpr (is_same_v<T, float8_e4m3_t>) {
        return __fp_format::__fp8_e4m3;
    } else  // NOLINT(readability/braces)
#endif
#if CANN_ASC_STL_DETAIL_HAS_FP8_E5M2()
        if constexpr (is_same_v<T, float8_e5m2_t>) {
        return __fp_format::__fp8_e5m2;
    } else  // NOLINT(readability/braces)
#endif
#if CANN_ASC_STL_DETAIL_HAS_FP8_E8M0()
        if constexpr (is_same_v<T, float8_e8m0_t>) {
        return __fp_format::__fp8_e8m0;
    } else  // NOLINT(readability/braces)
#endif
    {
        return __fp_format::__invalid;
    }
}

// Probing for FP6 / FP4 / __float128 formats.
template <class T>
CANN_ASC_STL_NODISCARD constexpr __fp_format __fp_format_of_narrow_and_qlike() noexcept
{
#if CANN_ASC_STL_DETAIL_HAS_FP6_E2M3()
    if constexpr (is_same_v<T, float6_e2m3_t>) {
        return __fp_format::__fp6_e2m3;
    } else  // NOLINT(readability/braces)
#endif
#if CANN_ASC_STL_DETAIL_HAS_FP6_E3M2()
        if constexpr (is_same_v<T, float6_e3m2_t>) {
        return __fp_format::__fp6_e3m2;
    } else  // NOLINT(readability/braces)
#endif
#if CANN_ASC_STL_DETAIL_HAS_FP4_E2M1()
        if constexpr (is_same_v<T, float4_e2m1_t>) {
        return __fp_format::__fp4_e2m1;
    } else  // NOLINT(readability/braces)
#endif
#if CANN_ASC_STL_DETAIL_HAS_FLOAT128()
        if constexpr (is_same_v<T, __float128>) {
        return __fp_format::__binary128;
    } else  // NOLINT(readability/braces)
#endif
    {
        return __fp_format::__invalid;
    }
}

template <class T>
CANN_ASC_STL_NODISCARD constexpr __fp_format __fp_format_of_v_impl() noexcept
{
    const __fp_format basic = __fp_format_of_basic<T>();
    if (basic != __fp_format::__invalid) {
        return basic;
    }
    const __fp_format half_width = __fp_format_of_16bit<T>();
    if (half_width != __fp_format::__invalid) {
        return half_width;
    }
    const __fp_format fp8 = __fp_format_of_fp8<T>();
    if (fp8 != __fp_format::__invalid) {
        return fp8;
    }
    return __fp_format_of_narrow_and_qlike<T>();
}

template <class T>
inline constexpr __fp_format __fp_format_of_v = __fp_format_of_v_impl<T>();

template <class T>
inline constexpr __fp_format __fp_format_of_v<const T> = __fp_format_of_v<T>;

template <class T>
inline constexpr __fp_format __fp_format_of_v<volatile T> = __fp_format_of_v<T>;

template <class T>
inline constexpr __fp_format __fp_format_of_v<const volatile T> = __fp_format_of_v<T>;

template <__fp_format Fmt>
inline constexpr __fp_format __fp_format_of_v<__asc_fp<Fmt>> = Fmt;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_FLOATING_POINT_FORMAT_H
