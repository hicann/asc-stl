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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_ABS_H
#define CANN_ASC_STL_ASC_STD___CMATH_ABS_H

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

//! @brief Absolute value of @p x.
//!
//! Floating arguments clear the sign bit through their storage
//! representation — bit-exact with the reference semantics, so -0.0 yields
//! +0.0 and NaNs stay NaNs, with no floating-point arithmetic involved.
//! Integral arguments widen to double on host; the vector cores have no
//! double-precision arithmetic, so the widening is rejected at compile
//! time in device TUs instead of silently changing the contract.
//! Unsigned types return their value unchanged. Formats beyond the
//! delivered storage vocabulary (x87 fp80 / binary128 native long double)
//! clear the sign through the compiler's bit-exact fabs builtin.
template <class Tp, ::asc::std::enable_if_t<__is_extended_arithmetic_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr auto fabs(Tp x) noexcept
{
    if constexpr (is_integral_v<Tp>) {
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        static_assert(sizeof(Tp) == 0, "integral fabs widens to double, which device TUs do not support");
#else
        if constexpr (numeric_limits<Tp>::is_signed) {
            return x < 0 ? -static_cast<double>(x) : static_cast<double>(x);
        } else {
            return static_cast<double>(x);
        }
#endif
    } else if constexpr (__fp_format_of_v<Tp> == __fp_format::__binary16 ||  // NOLINT(readability/braces)
        __fp_format_of_v<Tp> == __fp_format::__bfloat16 || __fp_format_of_v<Tp> == __fp_format::__binary32 ||
        __fp_format_of_v<Tp> == __fp_format::__binary64 || __fp_format_of_v<Tp> == __fp_format::__fp8_e4m3 ||
        __fp_format_of_v<Tp> == __fp_format::__fp8_e5m2 || __fp_format_of_v<Tp> == __fp_format::__fp8_e8m0) {
        const auto val = ::asc::std::__fp_get_storage(x) & __fp_exp_mant_mask_of_v<Tp>;
        return ::asc::std::__fp_from_storage<Tp>(static_cast<__fp_storage_of_t<Tp>>(val));
    } else {
        if constexpr (is_same_v<Tp, long double>) {
            return __builtin_fabsl(x);
        } else {
            return __builtin_fabs(x);
        }
    }
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr float fabsf(float x) noexcept
{
    return ::asc::std::fabs(x);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr long double fabsl(long double x) noexcept
{
    return ::asc::std::fabs(x);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

// Floating-point abs entry points: presence taken from the classic cmath
// surface, implementation forwarded to the constexpr template fabs above
// (never the non-constexpr builtin path).
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr float abs(float x) noexcept
{
    return ::asc::std::fabs(x);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr double abs(double x) noexcept
{
    return ::asc::std::fabs(x);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr long double abs(long double x) noexcept
{
    return ::asc::std::fabs(x);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_ABS_H
