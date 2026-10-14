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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_MIN_MAX_H
#define CANN_ASC_STL_ASC_STD___CMATH_MIN_MAX_H

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
#include <asc/std/__cmath/isnan.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_extended_arithmetic.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/promote.h>

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

//! @brief Largest of two values. NaN-aware: a NaN operand yields the
//! other operand; -0.0 and +0.0 may be returned in either order (the
//! comparison cannot distinguish them).
//!
//! Floating arguments take the comparison path — no arithmetic beyond
//! the ordering itself. Integral arguments widen to double on host; the
//! vector cores have no double-precision arithmetic, so the widening is
//! rejected at compile time in device TUs instead of silently changing
//! the contract.
template <class Tp, ::asc::std::enable_if_t<__is_extended_arithmetic_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr conditional_t<is_integral_v<Tp>, double, Tp> fmax(Tp x, Tp y) noexcept
{
    if constexpr (is_integral_v<Tp>) {
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        static_assert(sizeof(Tp) == 0, "integral fmax widens to double, which device TUs do not support");
#else
        return x < y ? static_cast<double>(y) : static_cast<double>(x);
#endif
    } else {
        if (::asc::std::isnan(x)) {
            return y;
        } else if (::asc::std::isnan(y)) {
            return x;
        } else {
            return x < y ? y : x;
        }
    }
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr float fmaxf(float x, float y) noexcept
{
    return ::asc::std::fmax(x, y);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr long double fmaxl(long double x, long double y) noexcept
{
    return ::asc::std::fmax(x, y);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

//! @brief fmax over two floating-point types of different width: both
//! operands promote to the wider type first.
template <class Tp, class Up,
    ::asc::std::enable_if_t<::asc::std::is_floating_point_v<Tp>&& ::asc::std::is_floating_point_v<Up>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr auto fmax(Tp x, Up y) noexcept
{
    using result_type = __promote_t<Tp, Up>;
    static_assert(!(is_same_v<Tp, result_type> && is_same_v<Up, result_type>));
    return ::asc::std::fmax(static_cast<result_type>(x), static_cast<result_type>(y));
}

//! @brief Smallest of two values. NaN-aware in the same way as fmax: a
//! NaN operand yields the other operand. Integral widening is host-only
//! for the same double-precision reason as fmax.
template <class Tp, ::asc::std::enable_if_t<__is_extended_arithmetic_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr conditional_t<is_integral_v<Tp>, double, Tp> fmin(Tp x, Tp y) noexcept
{
    if constexpr (is_integral_v<Tp>) {
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        static_assert(sizeof(Tp) == 0, "integral fmin widens to double, which device TUs do not support");
#else
        return x < y ? static_cast<double>(x) : static_cast<double>(y);
#endif
    } else {
        if (::asc::std::isnan(x)) {
            return y;
        } else if (::asc::std::isnan(y)) {
            return x;
        } else {
            return x < y ? x : y;
        }
    }
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr float fminf(float x, float y) noexcept
{
    return ::asc::std::fmin(x, y);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr long double fminl(long double x, long double y) noexcept
{
    return ::asc::std::fmin(x, y);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

//! @brief fmin over two floating-point types of different width: both
//! operands promote to the wider type first.
template <class Tp, class Up,
    ::asc::std::enable_if_t<::asc::std::is_floating_point_v<Tp>&& ::asc::std::is_floating_point_v<Up>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr auto fmin(Tp x, Up y) noexcept
{
    using result_type = __promote_t<Tp, Up>;
    static_assert(!(is_same_v<Tp, result_type> && is_same_v<Up, result_type>));
    return ::asc::std::fmin(static_cast<result_type>(x), static_cast<result_type>(y));
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_MIN_MAX_H
