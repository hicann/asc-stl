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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_EXPONENTIAL_FUNCTIONS_H
#define CANN_ASC_STL_ASC_STD___CMATH_EXPONENTIAL_FUNCTIONS_H

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
#include <asc/std/__type_traits/is_arithmetic.h>
#include <asc/std/__type_traits/is_extended_floating_point.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/promote.h>
#include <asc/std/__type_traits/is_constant_evaluated.h>

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

// Exponential/scaling family, three-layer dispatch: the primary float name
// and the suffix aliases route through the backend — pure SIMT TUs go to the
// simt_api scalar library (reachable from __aicore__, including the frexpf
// form with the pointer out-param; expf/exp2f flush subnormal inputs and
// outputs), everything else uses the compiler builtins; double/long
// double/integral promotion and the l-suffix alias are host-only (the vector
// cores have no double-precision arithmetic, and long double is forbidden on
// device); extended floating point transits through float precision and
// round-trips in its original format.

// Extended floating point set for the exponential family: half/bfloat16 only
// (the fp8 scalar conversion path is unavailable on this compiler, so
// exposing the overloads would advertise calls that fail to compile).
template <class Tp>
inline constexpr bool __expo_supported_extended_v = false;
#if CANN_ASC_STL_DETAIL_HAS_HALF()
template <>
inline constexpr bool __expo_supported_extended_v<half> = true;
#endif
#if CANN_ASC_STL_DETAIL_HAS_BFLOAT16()
template <>
inline constexpr bool __expo_supported_extended_v<bfloat16_t> = true;
#endif

//! @brief Natural exponential e^@p value.
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float exp(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(expf, __builtin_expf, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float expf(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(expf, __builtin_expf, (value));
}

//! @brief Extended floating point (half/bfloat16) exp: transits through
//! float precision, returns in the original format.
template <class Tp, ::asc::std::enable_if_t<__expo_supported_extended_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp exp(Tp value) noexcept
{
    return static_cast<Tp>(::asc::std::exp(static_cast<float>(value)));
}

//! @brief 2 raised to the power @p value.
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float exp2(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(exp2f, __builtin_exp2f, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float exp2f(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(exp2f, __builtin_exp2f, (value));
}

template <class Tp, ::asc::std::enable_if_t<__expo_supported_extended_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp exp2(Tp value) noexcept
{
    return static_cast<Tp>(::asc::std::exp2(static_cast<float>(value)));
}

//! @brief e^@p value - 1; preserves precision when @p value is close to 0.
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float expm1(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(expm1f, __builtin_expm1f, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float expm1f(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(expm1f, __builtin_expm1f, (value));
}

template <class Tp, ::asc::std::enable_if_t<__expo_supported_extended_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp expm1(
    Tp value) noexcept
{
    return static_cast<Tp>(::asc::std::expm1(static_cast<float>(value)));
}

//! @brief Decomposes into a mantissa ([0.5, 1) or 0) and a base-2 exponent
//! (delivered through the @p exponent out-param).
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float frexp(
    float value, int* exponent) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(frexpf, __builtin_frexpf, (value, exponent));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float frexpf(
    float value, int* exponent) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(frexpf, __builtin_frexpf, (value, exponent));
}

template <class Tp, ::asc::std::enable_if_t<__expo_supported_extended_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp frexp(
    Tp value, int* exponent) noexcept
{
    return static_cast<Tp>(::asc::std::frexp(static_cast<float>(value), exponent));
}

//! @brief @p value * 2^@p exponent (inverse of frexp).
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float ldexp(
    float value, int exponent) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(ldexpf, __builtin_ldexpf, (value, exponent));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float ldexpf(
    float value, int exponent) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(ldexpf, __builtin_ldexpf, (value, exponent));
}

template <class Tp, ::asc::std::enable_if_t<__expo_supported_extended_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp ldexp(
    Tp value, int exponent) noexcept
{
    return static_cast<Tp>(::asc::std::ldexp(static_cast<float>(value), exponent));
}

//! @brief Splits into integral and fractional parts (integral part delivered
//! through the @p integer_part out-param, with the same sign as @p value).
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float modf(
    float value, float* integer_part) noexcept
{
    return __builtin_modff(value, integer_part);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float modff(
    float value, float* integer_part) noexcept
{
    return __builtin_modff(value, integer_part);
}

//! @brief @p value * FLT_RADIX^@p exponent (FLT_RADIX = 2).
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float scalbn(
    float value, int exponent) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(scalbnf, __builtin_scalbnf, (value, exponent));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float scalbnf(
    float value, int exponent) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(scalbnf, __builtin_scalbnf, (value, exponent));
}

template <class Tp, ::asc::std::enable_if_t<__expo_supported_extended_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp scalbn(
    Tp value, int exponent) noexcept
{
    return static_cast<Tp>(::asc::std::scalbn(static_cast<float>(value), exponent));
}

//! @brief Same as scalbn, with a long exponent.
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float scalbln(
    float value, long exponent) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(scalblnf, __builtin_scalblnf, (value, exponent));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float scalblnf(
    float value, long exponent) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(scalblnf, __builtin_scalblnf, (value, exponent));
}

template <class Tp, ::asc::std::enable_if_t<__expo_supported_extended_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp scalbln(
    Tp value, long exponent) noexcept
{
    return static_cast<Tp>(::asc::std::scalbln(static_cast<float>(value), exponent));
}

//! @brief @p base raised to the power @p exponent.
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float pow(
    float base, float exponent) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(powf, __builtin_powf, (base, exponent));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float powf(
    float base, float exponent) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(powf, __builtin_powf, (base, exponent));
}

template <class Tp, ::asc::std::enable_if_t<__expo_supported_extended_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp pow(
    Tp base, Tp exponent) noexcept
{
    return static_cast<Tp>(::asc::std::pow(static_cast<float>(base), static_cast<float>(exponent)));
}

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// Full host type surface: double/long double primary names, the l-suffix
// alias, and integral promotion. Integral promotion aligns with the <cmath>
// standard: integral arguments are promoted to double, computed and returned
// as double.

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double exp(double value) noexcept
{
    return __builtin_exp(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double exp(long double value) noexcept
{
    return __builtin_expl(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double expl(long double value) noexcept
{
    return __builtin_expl(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double exp(Tp value) noexcept
{
    return ::asc::std::exp(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double exp2(double value) noexcept
{
    return __builtin_exp2(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double exp2(long double value) noexcept
{
    return __builtin_exp2l(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double exp2l(long double value) noexcept
{
    return __builtin_exp2l(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double exp2(Tp value) noexcept
{
    return ::asc::std::exp2(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double expm1(double value) noexcept
{
    return __builtin_expm1(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double expm1(long double value) noexcept
{
    return __builtin_expm1l(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double expm1l(long double value) noexcept
{
    return __builtin_expm1l(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double expm1(Tp value) noexcept
{
    return ::asc::std::expm1(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double frexp(double value, int* exponent) noexcept
{
    return __builtin_frexp(value, exponent);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double frexp(long double value, int* exponent) noexcept
{
    return __builtin_frexpl(value, exponent);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double frexpl(long double value, int* exponent) noexcept
{
    return __builtin_frexpl(value, exponent);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double frexp(Tp value, int* exponent) noexcept
{
    return ::asc::std::frexp(static_cast<double>(value), exponent);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double ldexp(double value, int exponent) noexcept
{
    return __builtin_ldexp(value, exponent);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double ldexp(long double value, int exponent) noexcept
{
    return __builtin_ldexpl(value, exponent);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double ldexpl(long double value, int exponent) noexcept
{
    return __builtin_ldexpl(value, exponent);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double ldexp(Tp value, int exponent) noexcept
{
    return ::asc::std::ldexp(static_cast<double>(value), exponent);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double scalbn(double value, int exponent) noexcept
{
    return __builtin_scalbn(value, exponent);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double scalbn(long double value, int exponent) noexcept
{
    return __builtin_scalbnl(value, exponent);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double scalbnl(long double value, int exponent) noexcept
{
    return __builtin_scalbnl(value, exponent);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double scalbn(Tp value, int exponent) noexcept
{
    return ::asc::std::scalbn(static_cast<double>(value), exponent);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double scalbln(double value, long exponent) noexcept
{
    return __builtin_scalbln(value, exponent);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double scalbln(long double value, long exponent) noexcept
{
    return __builtin_scalblnl(value, exponent);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double scalblnl(long double value, long exponent) noexcept
{
    return __builtin_scalblnl(value, exponent);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double scalbln(Tp value, long exponent) noexcept
{
    return ::asc::std::scalbln(static_cast<double>(value), exponent);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double pow(double base, double exponent) noexcept
{
    return __builtin_pow(base, exponent);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double pow(long double base, long double exponent) noexcept
{
    return __builtin_powl(base, exponent);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double powl(long double base, long double exponent) noexcept
{
    return __builtin_powl(base, exponent);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

//! @brief pow over two arithmetic operands of different types: both promote
//! to the common width first.
template <class Tp, class Up, ::asc::std::enable_if_t<is_arithmetic_v<Tp> && is_arithmetic_v<Up>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr __promote_t<Tp, Up> pow(Tp base, Up exponent) noexcept
{
    using result_type = __promote_t<Tp, Up>;
    static_assert(!(is_same_v<Tp, result_type> && is_same_v<Up, result_type>));
    return ::asc::std::pow(static_cast<result_type>(base), static_cast<result_type>(exponent));
}

#endif  // !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

//! @brief Constant-evaluation-safe scalbn (used by internal components such
//! as complex division): in constant contexts a square-and-multiply loop
//! covers the full unsigned magnitude of INT_MIN (a plain square-and-multiply
//! loop drops one base factor for every nonzero exponent — avoided here); at
//! runtime it dispatches back to scalbn (device hardware / host libm).
template <class Tp>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp __constexpr_scalbn(
    Tp value, int exponent) noexcept
{
    if (::asc::std::is_constant_evaluated()) {
        if (value == Tp(0) || exponent == 0 || value != value)
            return value;
        const bool negative = exponent < 0;
        unsigned int magnitude =
            negative ? static_cast<unsigned int>(-(exponent + 1)) + 1U : static_cast<unsigned int>(exponent);
        // The delivered floating point formats (binary16/32/64, bfloat16)
        // all have radix 2, so use the literal directly and avoid a
        // dependency on the limits specialization in device TUs.
        Tp multiplier = negative ? Tp(1) / Tp(2) : Tp(2);
        while (magnitude != 0) {
            if ((magnitude & 1U) != 0U)
                value *= multiplier;
            magnitude >>= 1U;
            if (magnitude != 0)
                multiplier *= multiplier;
        }
        return value;
    }
    return ::asc::std::scalbn(value, exponent);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_EXPONENTIAL_FUNCTIONS_H
