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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_INVERSE_TRIGONOMETRIC_FUNCTIONS_H
#define CANN_ASC_STL_ASC_STD___CMATH_INVERSE_TRIGONOMETRIC_FUNCTIONS_H

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
#include <asc/std/__bit/bit_cast.h>
#include <asc/std/__cmath/backend.h>
#include <asc/std/__floating_point/cast.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_arithmetic.h>
#include <asc/std/__type_traits/is_extended_floating_point.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/promote.h>
#include <asc/std/numbers>

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

// Inverse trigonometric family, three-layer dispatch: the primary float name
// and the suffix aliases route through the backend — pure SIMT TUs go to the
// simt_api scalar library (reachable from __aicore__), with a direct signed-
// zero path for atan2. Other targets use the compiler builtins; double/long
// double/integral promotion and the l-suffix alias are host-only (the vector
// cores have no double-precision arithmetic, and long double is forbidden on
// device); extended floating point transits through float precision and
// round-trips in its original format.

//! @brief Inverse cosine, domain [-1, 1], range [0, π].
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float acos(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(acosf, __builtin_acosf, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float acosf(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(acosf, __builtin_acosf, (value));
}

//! @brief Extended floating point (half/bfloat16/fp8 family) acos: transits
//! through float precision, returns in the original format.
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp acos(Tp value) noexcept
{
    return ::asc::std::__fp_cast<Tp>(::asc::std::acos(::asc::std::__fp_cast<float>(value)));
}

//! @brief Inverse sine, domain [-1, 1], range [-π/2, π/2].
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float asin(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(asinf, __builtin_asinf, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float asinf(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(asinf, __builtin_asinf, (value));
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp asin(Tp value) noexcept
{
    return ::asc::std::__fp_cast<Tp>(::asc::std::asin(::asc::std::__fp_cast<float>(value)));
}

//! @brief Inverse tangent, range (-π/2, π/2).
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float atan(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(atanf, __builtin_atanf, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float atanf(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(atanf, __builtin_atanf, (value));
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp atan(Tp value) noexcept
{
    return ::asc::std::__fp_cast<Tp>(::asc::std::atan(::asc::std::__fp_cast<float>(value)));
}

//! @brief Inverse tangent of @p y / @p x, quadrant determined by the signs of
//! both arguments (range [-π, π]).
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float atan2(
    float y, float x) noexcept
{
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    // BiSheng cannot select the native atan2f sign operation for a constant zero ordinate.
    // Inspect the binary32 magnitude so flush-to-zero cannot classify a subnormal as zero.
    const unsigned y_bits = ::asc::std::bit_cast<unsigned>(y);
    const unsigned x_bits = ::asc::std::bit_cast<unsigned>(x);
    if ((y_bits & 0x7fffffffU) == 0) {
        if ((x_bits & 0x7fffffffU) > 0x7f800000U) {
            return ::asc::std::bit_cast<float>(x_bits | 0x00400000U);
        }
        if ((x_bits >> 31) != 0) {
            return ::asc::std::bit_cast<float>(y_bits | ::asc::std::bit_cast<unsigned>(numbers::pi_v<float>));
        }
        return y;
    }
    // A nonzero ordinate on the imaginary axis has an exact quadrant even when SIMT flushes tiny ratios.
    if ((x_bits & 0x7fffffffU) == 0) {
        if ((y_bits & 0x7fffffffU) > 0x7f800000U) {
            return ::asc::std::bit_cast<float>(y_bits | 0x00400000U);
        }
        constexpr unsigned half_pi = ::asc::std::bit_cast<unsigned>(numbers::pi_v<float> * 0.5F);
        return ::asc::std::bit_cast<float>(half_pi | (y_bits & 0x80000000U));
    }
#endif
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(atan2f, __builtin_atan2f, (y, x));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float atan2f(
    float y, float x) noexcept
{
    return ::asc::std::atan2(y, x);
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp atan2(
    Tp y, Tp x) noexcept
{
    return ::asc::std::__fp_cast<Tp>(
        ::asc::std::atan2(::asc::std::__fp_cast<float>(y), ::asc::std::__fp_cast<float>(x)));
}

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// Full host type surface: double/long double primary names, the l-suffix
// alias, and integral promotion. Integral promotion aligns with the <cmath>
// standard: integral arguments are promoted to double, computed and returned
// as double.

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double acos(double value) noexcept
{
    return __builtin_acos(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double acos(long double value) noexcept
{
    return __builtin_acosl(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double acosl(long double value) noexcept
{
    return __builtin_acosl(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double acos(Tp value) noexcept
{
    return ::asc::std::acos(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double asin(double value) noexcept
{
    return __builtin_asin(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double asin(long double value) noexcept
{
    return __builtin_asinl(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double asinl(long double value) noexcept
{
    return __builtin_asinl(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double asin(Tp value) noexcept
{
    return ::asc::std::asin(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double atan(double value) noexcept
{
    return __builtin_atan(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double atan(long double value) noexcept
{
    return __builtin_atanl(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double atanl(long double value) noexcept
{
    return __builtin_atanl(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double atan(Tp value) noexcept
{
    return ::asc::std::atan(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double atan2(double y, double x) noexcept
{
    return __builtin_atan2(y, x);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double atan2(long double y, long double x) noexcept
{
    return __builtin_atan2l(y, x);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double atan2l(long double y, long double x) noexcept
{
    return __builtin_atan2l(y, x);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

//! @brief atan2 over two arithmetic operands of different types: both promote
//! to the common width first.
template <class Tp, class Up, ::asc::std::enable_if_t<is_arithmetic_v<Tp> && is_arithmetic_v<Up>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr __promote_t<Tp, Up> atan2(Tp y, Up x) noexcept
{
    using result_type = __promote_t<Tp, Up>;
    static_assert(!(is_same_v<Tp, result_type> && is_same_v<Up, result_type>));
    return ::asc::std::atan2(static_cast<result_type>(y), static_cast<result_type>(x));
}

#endif  // !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_INVERSE_TRIGONOMETRIC_FUNCTIONS_H
