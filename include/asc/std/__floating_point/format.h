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

#ifndef CANN_ASC_STL_STD_DETAIL_FLOATING_POINT_FORMAT_H
#define CANN_ASC_STL_STD_DETAIL_FLOATING_POINT_FORMAT_H

#include <asc/std/detail/__config>

#include <asc/std/__fwd/fp.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/cfloat>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

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

// Probing for float / double / long double formats.
template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr __fp_format __fp_format_of_basic() noexcept
{
    if constexpr (is_same_v<_Tp, float>) {
        return __fp_format::__binary32;
    } else if constexpr (is_same_v<_Tp, double>) {
        return __fp_format::__binary64;
#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
    } else if constexpr (is_same_v<_Tp, long double>) {
#if LDBL_MIN_EXP == -1021 && LDBL_MAX_EXP == 1024 && LDBL_MANT_DIG == 53
        return __fp_format::__binary64;
#elif LDBL_MIN_EXP == -16381 && LDBL_MAX_EXP == 16384 && LDBL_MANT_DIG == 64
        static_assert(sizeof(long double) == 16,
            "When the long double format is x86 80-bit extended floating point, ASC-STL requires the size of long "
            "double to be 16 bytes.");
        return __fp_format::__fp80_x86;
#elif LDBL_MIN_EXP == -16381 && LDBL_MAX_EXP == 16384 && LDBL_MANT_DIG == 113
        return __fp_format::__binary128;
#else
#error "Unknown long double format. Define ASC_DISABLE_LONG_DOUBLE_SUPPORT to disable long double support in ASC-STL."
#endif
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
    } else {
        return __fp_format::__invalid;
    }
}

// Probing for half / bfloat16 formats.
template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr __fp_format __fp_format_of_16bit() noexcept
{
#if CANN_ASC_STL_DETAIL_HAS_HALF()
    if constexpr (is_same_v<_Tp, half>) {
        return __fp_format::__binary16;
    } else  // NOLINT(readability/braces)
#endif
#if CANN_ASC_STL_DETAIL_HAS_BFLOAT16()
        if constexpr (is_same_v<_Tp, bfloat16_t>) {
        return __fp_format::__bfloat16;
    } else  // NOLINT(readability/braces)
#endif
    {
        return __fp_format::__invalid;
    }
}

// Probing for the FP8 family formats.
template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr __fp_format __fp_format_of_fp8() noexcept
{
#if CANN_ASC_STL_DETAIL_HAS_FP8_E4M3()
    if constexpr (is_same_v<_Tp, float8_e4m3_t>) {
        return __fp_format::__fp8_e4m3;
    } else  // NOLINT(readability/braces)
#endif
#if CANN_ASC_STL_DETAIL_HAS_FP8_E5M2()
        if constexpr (is_same_v<_Tp, float8_e5m2_t>) {
        return __fp_format::__fp8_e5m2;
    } else  // NOLINT(readability/braces)
#endif
#if CANN_ASC_STL_DETAIL_HAS_FP8_E8M0()
        if constexpr (is_same_v<_Tp, float8_e8m0_t>) {
        return __fp_format::__fp8_e8m0;
    } else  // NOLINT(readability/braces)
#endif
    {
        return __fp_format::__invalid;
    }
}

// Probing for FP6 / FP4 / __float128 formats.
template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr __fp_format __fp_format_of_narrow_and_qlike() noexcept
{
#if CANN_ASC_STL_DETAIL_HAS_FP6_E2M3()
    if constexpr (is_same_v<_Tp, float6_e2m3_t>) {
        return __fp_format::__fp6_e2m3;
    } else  // NOLINT(readability/braces)
#endif
#if CANN_ASC_STL_DETAIL_HAS_FP6_E3M2()
        if constexpr (is_same_v<_Tp, float6_e3m2_t>) {
        return __fp_format::__fp6_e3m2;
    } else  // NOLINT(readability/braces)
#endif
#if CANN_ASC_STL_DETAIL_HAS_FP4_E2M1()
        if constexpr (is_same_v<_Tp, float4_e2m1_t>) {
        return __fp_format::__fp4_e2m1;
    } else  // NOLINT(readability/braces)
#endif
#if CANN_ASC_STL_DETAIL_HAS_FLOAT128()
        if constexpr (is_same_v<_Tp, __float128>) {
        return __fp_format::__binary128;
    } else  // NOLINT(readability/braces)
#endif
    {
        return __fp_format::__invalid;
    }
}

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr __fp_format __fp_format_of_v_impl() noexcept
{
    const __fp_format __basic = __fp_format_of_basic<_Tp>();
    if (__basic != __fp_format::__invalid) {
        return __basic;
    }
    const __fp_format __half_width = __fp_format_of_16bit<_Tp>();
    if (__half_width != __fp_format::__invalid) {
        return __half_width;
    }
    const __fp_format __fp8 = __fp_format_of_fp8<_Tp>();
    if (__fp8 != __fp_format::__invalid) {
        return __fp8;
    }
    return __fp_format_of_narrow_and_qlike<_Tp>();
}

template <class _Tp>
inline constexpr __fp_format __fp_format_of_v = ::asc::std::__fp_format_of_v_impl<_Tp>();

template <class _Tp>
inline constexpr __fp_format __fp_format_of_v<const _Tp> = __fp_format_of_v<_Tp>;

template <class _Tp>
inline constexpr __fp_format __fp_format_of_v<volatile _Tp> = __fp_format_of_v<_Tp>;

template <class _Tp>
inline constexpr __fp_format __fp_format_of_v<const volatile _Tp> = __fp_format_of_v<_Tp>;

template <__fp_format _Fmt>
inline constexpr __fp_format __fp_format_of_v<__asc_fp<_Fmt>> = _Fmt;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FLOATING_POINT_FORMAT_H
