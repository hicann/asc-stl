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

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__fwd/fp.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/cfloat>

CANN_ASC_STL_BEGIN_NAMESPACE

enum class __fp_format {
    __binary16,   // IEEE 754 binary16
    __binary32,   // IEEE 754 binary32
    __binary64,   // IEEE 754 binary64
    __binary128,  // IEEE 754 binary128
    __bfloat16,   // 16-bit brain float
    __fp80_x86,   // x86 80-bit extended precision

    __invalid,
};

// CCE pure SIMT rejects references to __device__ functions in global
// initializers, so the long-double classification is a constant instead of a
// call into a CANN_ASC_STL_API function.
#if LDBL_MIN_EXP == -1021 && LDBL_MAX_EXP == 1024 && LDBL_MANT_DIG == 53
inline constexpr __fp_format __long_double_format = __fp_format::__binary64;
#elif LDBL_MIN_EXP == -16381 && LDBL_MAX_EXP == 16384 && LDBL_MANT_DIG == 64
static_assert(
    sizeof(long double) == 16, "the x86 80-bit extended floating-point layout requires a 16-byte long double");
inline constexpr __fp_format __long_double_format = __fp_format::__fp80_x86;
#elif LDBL_MIN_EXP == -16381 && LDBL_MAX_EXP == 16384 && LDBL_MANT_DIG == 113
inline constexpr __fp_format __long_double_format = __fp_format::__binary128;
#else
#error "Unknown long double format on this frozen toolchain."
#endif

template <class T>
inline constexpr __fp_format __fp_format_of_v = is_same_v<T, float> ? __fp_format::__binary32 :
    is_same_v<T, double>                                            ? __fp_format::__binary64 :
    is_same_v<T, long double>                                       ? __long_double_format :
                                                                      __fp_format::__invalid;

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
