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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_GAMMA_H
#define CANN_ASC_STL_ASC_STD___CMATH_GAMMA_H

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
#include <asc/std/__floating_point/cast.h>
#include <asc/std/__cmath/backend.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_extended_floating_point.h>
#include <asc/std/__type_traits/is_integral.h>

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

// Gamma-function family, three-layer dispatch: the primary float name and
// the suffix aliases route through the backend — pure SIMT TUs go to the
// simt_api scalar library (reachable from __aicore__, device exposes the
// primary name only), everything else uses the compiler builtins;
// double/long double/integral promotion and the l-suffix alias are host-only
// (the vector cores have no double-precision arithmetic, and long double is
// forbidden on device); extended floating point transits through float
// precision and round-trips in its original format.

//! @brief Γ(@p value). The non-positive-integer poles produce a domain error
//! (±0 and negative integers -> ±inf/NaN per the libm contract).
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float tgamma(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(tgammaf, __builtin_tgammaf, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float tgammaf(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(tgammaf, __builtin_tgammaf, (value));
}

//! @brief Extended floating point (half/bfloat16/fp8 family) tgamma:
//! transits through float precision, returns in the original format.
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp tgamma(
    Tp value) noexcept
{
    return ::asc::std::__fp_cast<Tp>(::asc::std::tgamma(::asc::std::__fp_cast<float>(value)));
}

//! @brief ln|Γ(@p value)|. The sign of the gamma is obtained separately
//! through the signgam global (libm contract).
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float lgamma(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(lgammaf, __builtin_lgammaf, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float lgammaf(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(lgammaf, __builtin_lgammaf, (value));
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp lgamma(
    Tp value) noexcept
{
    return ::asc::std::__fp_cast<Tp>(::asc::std::lgamma(::asc::std::__fp_cast<float>(value)));
}

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// Full host type surface: double/long double primary names, the l-suffix
// alias, and integral promotion. Integral promotion aligns with the <cmath>
// standard: integral arguments are promoted to double, computed and returned
// as double.

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double tgamma(double value) noexcept
{
    return __builtin_tgamma(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double tgamma(long double value) noexcept
{
    return __builtin_tgammal(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double tgammal(long double value) noexcept
{
    return __builtin_tgammal(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double tgamma(Tp value) noexcept
{
    return ::asc::std::tgamma(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double lgamma(double value) noexcept
{
    return __builtin_lgamma(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double lgamma(long double value) noexcept
{
    return __builtin_lgammal(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double lgammal(long double value) noexcept
{
    return __builtin_lgammal(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double lgamma(Tp value) noexcept
{
    return ::asc::std::lgamma(static_cast<double>(value));
}

#endif  // !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_GAMMA_H
