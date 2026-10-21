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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_INVERSE_HYPERBOLIC_FUNCTIONS_H
#define CANN_ASC_STL_ASC_STD___CMATH_INVERSE_HYPERBOLIC_FUNCTIONS_H

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

// Inverse hyperbolic family, three-layer dispatch: the primary float name
// and the suffix aliases route through the backend — pure SIMT TUs go to the
// simt_api scalar library (reachable from __aicore__; the device-side
// asinhf input domain is [-65504, 65504]), everything else uses the compiler
// builtins; double/long double/integral promotion and the l-suffix alias are
// host-only (the vector cores have no double-precision arithmetic, and long
// double is forbidden on device); extended floating point transits through
// float precision and round-trips in its original format.

//! @brief Inverse hyperbolic cosine, domain [1, +inf), range [0, +inf).
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float acosh(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(acoshf, __builtin_acoshf, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float acoshf(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(acoshf, __builtin_acoshf, (value));
}

//! @brief Extended floating point (half/bfloat16/fp8 family) acosh: transits
//! through float precision, returns in the original format.
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp acosh(
    Tp value) noexcept
{
    return ::asc::std::__fp_cast<Tp>(::asc::std::acosh(::asc::std::__fp_cast<float>(value)));
}

//! @brief Inverse hyperbolic sine, domain (-inf, +inf), range (-inf, +inf).
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float asinh(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(asinhf, __builtin_asinhf, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float asinhf(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(asinhf, __builtin_asinhf, (value));
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp asinh(
    Tp value) noexcept
{
    return ::asc::std::__fp_cast<Tp>(::asc::std::asinh(::asc::std::__fp_cast<float>(value)));
}

//! @brief Inverse hyperbolic tangent, domain (-1, 1), range (-inf, +inf).
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float atanh(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(atanhf, __builtin_atanhf, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float atanhf(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(atanhf, __builtin_atanhf, (value));
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp atanh(
    Tp value) noexcept
{
    return ::asc::std::__fp_cast<Tp>(::asc::std::atanh(::asc::std::__fp_cast<float>(value)));
}

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// Full host type surface: double/long double primary names, the l-suffix
// alias, and integral promotion. Integral promotion aligns with the <cmath>
// standard: integral arguments are promoted to double, computed and returned
// as double.

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double acosh(double value) noexcept
{
    return __builtin_acosh(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double acosh(long double value) noexcept
{
    return __builtin_acoshl(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double acoshl(long double value) noexcept
{
    return __builtin_acoshl(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double acosh(Tp value) noexcept
{
    return ::asc::std::acosh(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double asinh(double value) noexcept
{
    return __builtin_asinh(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double asinh(long double value) noexcept
{
    return __builtin_asinhl(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double asinhl(long double value) noexcept
{
    return __builtin_asinhl(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double asinh(Tp value) noexcept
{
    return ::asc::std::asinh(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double atanh(double value) noexcept
{
    return __builtin_atanh(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double atanh(long double value) noexcept
{
    return __builtin_atanhl(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double atanhl(long double value) noexcept
{
    return __builtin_atanhl(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double atanh(Tp value) noexcept
{
    return ::asc::std::atanh(static_cast<double>(value));
}

#endif  // !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_INVERSE_HYPERBOLIC_FUNCTIONS_H
