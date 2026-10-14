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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_ROUNDING_FUNCTIONS_H
#define CANN_ASC_STL_ASC_STD___CMATH_ROUNDING_FUNCTIONS_H

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

// Rounding/nearest-integer family, three-layer dispatch: the primary float
// name and the suffix aliases route through the backend — pure SIMT TUs go to
// the simt_api scalar library (reachable from __aicore__), everything else
// uses the compiler builtins; double/long double/integral promotion and the
// l-suffix alias are host-only (the vector cores have no double-precision
// arithmetic, and long double is forbidden on device); extended floating
// point (half/bfloat16/fp8 family) transits through float precision and
// round-trips in its original format.

//! @brief Smallest integer value not less than @p value. Zero returns
//! directly with its sign preserved (-0.0 -> -0.0).
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float ceil(
    float value) noexcept
{
    if (value == 0.0F)
        return value;
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(ceilf, __builtin_ceilf, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float ceilf(
    float value) noexcept
{
    if (value == 0.0F)
        return value;
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(ceilf, __builtin_ceilf, (value));
}

//! @brief Extended floating point (half/bfloat16/fp8 family) ceil: transits
//! through float precision, returns in the original format.
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp ceil(Tp value) noexcept
{
    return static_cast<Tp>(::asc::std::ceil(static_cast<float>(value)));
}

//! @brief Largest integer value not greater than @p value. Zero returns
//! directly with its sign preserved (-0.0 -> -0.0).
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float floor(
    float value) noexcept
{
    if (value == 0.0F)
        return value;
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(floorf, __builtin_floorf, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float floorf(
    float value) noexcept
{
    if (value == 0.0F)
        return value;
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(floorf, __builtin_floorf, (value));
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp floor(
    Tp value) noexcept
{
    return static_cast<Tp>(::asc::std::floor(static_cast<float>(value)));
}

//! @brief Rounds toward zero. Zero returns directly with its sign preserved
//! (-0.0 -> -0.0).
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float trunc(
    float value) noexcept
{
    if (value == 0.0F)
        return value;
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(truncf, __builtin_truncf, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float truncf(
    float value) noexcept
{
    if (value == 0.0F)
        return value;
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(truncf, __builtin_truncf, (value));
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp trunc(
    Tp value) noexcept
{
    return static_cast<Tp>(::asc::std::trunc(static_cast<float>(value)));
}

//! @brief Rounds to nearest, halfway cases away from zero (round(2.5) = 3,
//! round(-2.5) = -3).
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float round(
    float value) noexcept
{
    if (value == 0.0F)
        return value;
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(roundf, __builtin_roundf, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float roundf(
    float value) noexcept
{
    if (value == 0.0F)
        return value;
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(roundf, __builtin_roundf, (value));
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp round(
    Tp value) noexcept
{
    return static_cast<Tp>(::asc::std::round(static_cast<float>(value)));
}

//! @brief Rounds to nearest according to the current rounding mode (even by
//! default).
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float rint(
    float value) noexcept
{
    if (value == 0.0F)
        return value;
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(rintf, __builtin_rintf, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float rintf(
    float value) noexcept
{
    if (value == 0.0F)
        return value;
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(rintf, __builtin_rintf, (value));
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp rint(Tp value) noexcept
{
    return static_cast<Tp>(::asc::std::rint(static_cast<float>(value)));
}

//! @brief Rounds to nearest (same as rint) but does not raise the inexact
//! floating-point exception.
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float nearbyint(
    float value) noexcept
{
    if (value == 0.0F)
        return value;
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(nearbyintf, __builtin_nearbyintf, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float nearbyintf(
    float value) noexcept
{
    if (value == 0.0F)
        return value;
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(nearbyintf, __builtin_nearbyintf, (value));
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp nearbyint(
    Tp value) noexcept
{
    return static_cast<Tp>(::asc::std::nearbyint(static_cast<float>(value)));
}

//! @brief Rounds according to the current rounding mode and converts to
//! long.
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR long lrint(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(lrintf, __builtin_lrintf, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR long lrintf(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(lrintf, __builtin_lrintf, (value));
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp lrint(
    Tp value) noexcept
{
    return static_cast<Tp>(::asc::std::lrint(static_cast<float>(value)));
}

//! @brief Rounds to nearest (halfway cases away from zero) and converts to
//! long.
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR long lround(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(lroundf, __builtin_lroundf, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR long lroundf(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(lroundf, __builtin_lroundf, (value));
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp lround(
    Tp value) noexcept
{
    return static_cast<Tp>(::asc::std::lround(static_cast<float>(value)));
}

//! @brief Rounds according to the current rounding mode and converts to
//! long long.
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR long long llrint(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(llrintf, __builtin_llrintf, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR long long llrintf(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(llrintf, __builtin_llrintf, (value));
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp llrint(
    Tp value) noexcept
{
    return static_cast<Tp>(::asc::std::llrint(static_cast<float>(value)));
}

//! @brief Rounds to nearest (halfway cases away from zero) and converts to
//! long long.
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR long long llround(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(llroundf, __builtin_llroundf, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR long long llroundf(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(llroundf, __builtin_llroundf, (value));
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp llround(
    Tp value) noexcept
{
    return static_cast<Tp>(::asc::std::llround(static_cast<float>(value)));
}

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// Full host type surface: double/long double primary names, the l-suffix
// alias, and integral promotion. Integral promotion aligns with the <cmath>
// standard: integral arguments are promoted to double, computed and returned
// as double.

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double ceil(double value) noexcept
{
    return __builtin_ceil(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double ceil(long double value) noexcept
{
    return __builtin_ceill(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double ceill(long double value) noexcept
{
    return __builtin_ceill(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double ceil(Tp value) noexcept
{
    return ::asc::std::ceil(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double floor(double value) noexcept
{
    return __builtin_floor(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double floor(long double value) noexcept
{
    return __builtin_floorl(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double floorl(long double value) noexcept
{
    return __builtin_floorl(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double floor(Tp value) noexcept
{
    return ::asc::std::floor(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double trunc(double value) noexcept
{
    return __builtin_trunc(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double trunc(long double value) noexcept
{
    return __builtin_truncl(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double truncl(long double value) noexcept
{
    return __builtin_truncl(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double trunc(Tp value) noexcept
{
    return ::asc::std::trunc(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double round(double value) noexcept
{
    return __builtin_round(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double round(long double value) noexcept
{
    return __builtin_roundl(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double roundl(long double value) noexcept
{
    return __builtin_roundl(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double round(Tp value) noexcept
{
    return ::asc::std::round(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double rint(double value) noexcept
{
    return __builtin_rint(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double rint(long double value) noexcept
{
    return __builtin_rintl(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double rintl(long double value) noexcept
{
    return __builtin_rintl(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double rint(Tp value) noexcept
{
    return ::asc::std::rint(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double nearbyint(double value) noexcept
{
    return __builtin_nearbyint(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double nearbyint(long double value) noexcept
{
    return __builtin_nearbyintl(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double nearbyintl(long double value) noexcept
{
    return __builtin_nearbyintl(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double nearbyint(Tp value) noexcept
{
    return ::asc::std::nearbyint(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long lrint(double value) noexcept
{
    return __builtin_lrint(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long lrint(long double value) noexcept
{
    return __builtin_lrintl(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long lrintl(long double value) noexcept
{
    return __builtin_lrintl(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long lrint(Tp value) noexcept
{
    return ::asc::std::lrint(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long lround(double value) noexcept
{
    return __builtin_lround(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long lround(long double value) noexcept
{
    return __builtin_lroundl(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long lroundl(long double value) noexcept
{
    return __builtin_lroundl(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long lround(Tp value) noexcept
{
    return ::asc::std::lround(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long long llrint(double value) noexcept
{
    return __builtin_llrint(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long long llrint(long double value) noexcept
{
    return __builtin_llrintl(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long long llrintl(long double value) noexcept
{
    return __builtin_llrintl(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long long llrint(Tp value) noexcept
{
    return ::asc::std::llrint(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long long llround(double value) noexcept
{
    return __builtin_llround(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long long llround(long double value) noexcept
{
    return __builtin_llroundl(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long long llroundl(long double value) noexcept
{
    return __builtin_llroundl(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long long llround(Tp value) noexcept
{
    return ::asc::std::llround(static_cast<double>(value));
}

// nexttoward: simt_api has no counterpart (absent from the SIMT API
// documentation), so it is host-only; the second parameter is long double
// per the C99 contract.
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr float nexttoward(float value, long double toward) noexcept
{
    return __builtin_nexttowardf(value, toward);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr float nexttowardf(float value, long double toward) noexcept
{
    return __builtin_nexttowardf(value, toward);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double nexttoward(double value, long double toward) noexcept
{
    return __builtin_nexttoward(value, toward);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double nexttoward(
    long double value, long double toward) noexcept
{
    return __builtin_nexttowardl(value, toward);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double nexttowardl(
    long double value, long double toward) noexcept
{
    return __builtin_nexttowardl(value, toward);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

#endif  // !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_ROUNDING_FUNCTIONS_H
