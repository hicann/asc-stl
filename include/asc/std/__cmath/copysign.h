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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_COPYSIGN_H
#define CANN_ASC_STL_ASC_STD___CMATH_COPYSIGN_H

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
#include <asc/std/__floating_point/fp.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_extended_arithmetic.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/limits>
#include <limits>

// Inline definition of the CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE() gate (the
// config does not provide it): long double is host-only — AI-core compilation
// does not support long double.
#if !defined(CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE)
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && !defined(ASC_DISABLE_LONG_DOUBLE_SUPPORT)
#define CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE() 0
#endif
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE

CANN_ASC_STL_BEGIN_NAMESPACE

//! @brief Copies the sign of @p y onto the magnitude of @p x.
//!
//! Integral arguments widen to double and take the sign; unsigned types
//! have no sign to take and return their magnitude unchanged. Floating
//! arguments are rebuilt through their storage representation: exponent
//! and mantissa of @p x combined with the sign bit of @p y — bit-exact
//! with the reference semantics, no arithmetic involved. Formats beyond the
//! delivered storage vocabulary (x87 fp80 / binary128 native long double)
//! recombine through the compiler's bit-exact copysign builtin, which is
//! the same magnitude-of-x / sign-of-y bit operation.
template <class Tp, ::asc::std::enable_if_t<__is_extended_arithmetic_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr auto copysign(Tp x, Tp y) noexcept
{
    if constexpr (is_integral_v<Tp>) {
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        // The vector cores have no double-precision arithmetic: reject the
        // integral widening instead of silently changing the contract. The
        // gate covers every device context (mixed CCE and pure SIMT alike —
        // __CCE__ alone is not defined in pure-SIMT TUs, where the unselected
        // double-widening branch still parses inside the aicore-reachable
        // template body and gets rejected.
        static_assert(sizeof(Tp) == 0, "integral copysign widens to double, which AI-core TUs do not support");
#else
        if constexpr (!numeric_limits<Tp>::is_signed) {
            return static_cast<double>(x);
        } else {
            const auto x_dbl = static_cast<double>(x);
            if (y < 0) {
                return (x < 0) ? x_dbl : -x_dbl;
            } else {
                return (x < 0) ? -x_dbl : x_dbl;
            }
        }
#endif
    } else {  // ^^^ integral ^^^ / vvv floating_point vvv
        if constexpr (!numeric_limits<Tp>::is_signed) {
            return x;
        } else if constexpr (__fp_format_of_v<Tp> == __fp_format::__binary16 ||  // NOLINT(readability/braces)
            __fp_format_of_v<Tp> == __fp_format::__bfloat16 || __fp_format_of_v<Tp> == __fp_format::__binary32 ||
            __fp_format_of_v<Tp> == __fp_format::__binary64 || __fp_format_of_v<Tp> == __fp_format::__fp8_e4m3 ||
            __fp_format_of_v<Tp> == __fp_format::__fp8_e5m2 || __fp_format_of_v<Tp> == __fp_format::__fp8_e8m0) {
            const auto val = (::asc::std::__fp_get_storage(x) & __fp_exp_mant_mask_of_v<Tp>) |
                (::asc::std::__fp_get_storage(y) & __fp_sign_mask_of_v<Tp>);
            return ::asc::std::__fp_from_storage<Tp>(static_cast<__fp_storage_of_t<Tp>>(val));
        } else {
            // The storage vocabulary does not cover >64-bit formats (x87 fp80 /
            // binary128 native long double): the bit-level sign recombination
            // goes through the compiler's bit-exact copysign builtin
            // (exponent+mantissa of x, sign bit of y — the same bit-operation
            // semantics).
            if constexpr (is_same_v<Tp, long double>) {
                return __builtin_copysignl(x, y);
            } else {
                return __builtin_copysign(x, y);
            }
        }
    }
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr float copysignf(float x, float y) noexcept
{
    return ::asc::std::copysign(x, y);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr long double copysignl(long double x, long double y) noexcept
{
    return ::asc::std::copysign(x, y);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_COPYSIGN_H
