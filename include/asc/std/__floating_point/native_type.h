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

#ifndef CANN_ASC_STL_ASC_STD___FLOATING_POINT_NATIVE_TYPE_H
#define CANN_ASC_STL_ASC_STD___FLOATING_POINT_NATIVE_TYPE_H

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
#include <asc/std/__floating_point/format.h>
#include <asc/std/__floating_point/traits.h>
#include <asc/std/__type_traits/is_void.h>
#include <asc/std/cfloat>

// <asc/__config> does not provide CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE():
// inline the gate here — long double is host-only, ASC device compilation
// (AI Core) does not support long double.
#if !defined(CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE)
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && !defined(ASC_DISABLE_LONG_DOUBLE_SUPPORT)
#define CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE() 0
#endif
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE

// <asc/__config> does not provide CANN_ASC_STL_DETAIL_HAS_FLOAT128(): inline
// the gate here — __float128 needs __int128, a Linux non-ARM64 target, a
// compiler that advertises the type, host compilation only (CCE device
// compilation does not support __float128), and GCC must not run strict-ANSI
// without extended numeric literals (no q/Q floating point literals under
// __STRICT_ANSI__).
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

// __is_ext_compiler_fp_v
//
// Predicate for the compiler-extension floating-point vocabulary:
// __float128 when the detection gate above provides it.

template <class T>
inline constexpr bool __is_ext_compiler_fp_v = false;

template <class T>
inline constexpr bool __is_ext_compiler_fp_v<const T> = __is_ext_compiler_fp_v<T>;

template <class T>
inline constexpr bool __is_ext_compiler_fp_v<volatile T> = __is_ext_compiler_fp_v<T>;

template <class T>
inline constexpr bool __is_ext_compiler_fp_v<const volatile T> = __is_ext_compiler_fp_v<T>;

#if CANN_ASC_STL_DETAIL_HAS_FLOAT128()
template <>
inline constexpr bool __is_ext_compiler_fp_v<__float128> = true;
#endif  // CANN_ASC_STL_DETAIL_HAS_FLOAT128()

//! @brief Maps a format to its native C++ type: binary32/64 always exist;
//! binary128 and x86 fp80 are provided only when the host long double matches
//! the format bit for bit (LDBL_* characteristic macros), otherwise the
//! mapping is void (no native type). Device TUs are judged by the same
//! characteristic macros (Ascend devices have no 128-bit floating point, so
//! binary128/fp80 are always void there).
template <__fp_format Fmt>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr auto __fp_native_type_impl() noexcept
{
    if constexpr (Fmt == __fp_format::__binary32) {
        return float{};
    } else if constexpr (Fmt == __fp_format::__binary64) {
        return double{};
    } else if constexpr (Fmt == __fp_format::__binary128) {
#if CANN_ASC_STL_DETAIL_HAS_FLOAT128()
        return __float128{0.0};
#elif CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE() && LDBL_MIN_EXP == -16381 && LDBL_MAX_EXP == 16384 && LDBL_MANT_DIG == 113
        return static_cast<long double>(0);
#else   // ^^^ native binary128 ^^^ / vvv no native binary128 vvv
        return;
#endif  // ^^^ no native binary128 ^^^
    } else if constexpr (Fmt == __fp_format::__fp80_x86) {
#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE() && LDBL_MIN_EXP == -16381 && LDBL_MAX_EXP == 16384 && LDBL_MANT_DIG == 64
        return static_cast<long double>(0);
#else   // ^^^ native x86 fp80 ^^^ / vvv no native x86 fp80 vvv
        return;
#endif  // ^^^ no native x86 fp80 ^^^
    } else {
        return;
    }
}

template <__fp_format Fmt>
using __fp_native_type_t = decltype(__fp_native_type_impl<Fmt>());

//! @brief Whether the format has a native C++ type (the mapping is not void).
template <__fp_format Fmt>
inline constexpr bool __fp_has_native_type_v = !is_void_v<__fp_native_type_t<Fmt>>;

//! @brief Whether T is a native floating-point type (standard fp or
//!        compiler-extension fp).
template <class T>
inline constexpr bool __fp_is_native_type_v = __is_std_fp_v<T> || __is_ext_compiler_fp_v<T>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___FLOATING_POINT_NATIVE_TYPE_H
