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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_REMAINDER_H
#define CANN_ASC_STL_ASC_STD___CMATH_REMAINDER_H

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
#include <asc/std/__floating_point/fp.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_arithmetic.h>
#include <asc/std/__type_traits/is_extended_floating_point.h>
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

// remainder/remquo/nextafter, three-layer dispatch: the float primary name
// and suffix aliases route through the backend — pure SIMT TUs go to the
// simt_api scalar library (reachable from __aicore__), everything else uses
// the compiler builtins; double/long double primary names, the l-suffix
// alias, and mixed-type promote are host-only (double is forbidden on the
// vector cores, long double on device); extended floating point
// (half/bfloat16/fp8 family) transits through float precision and
// round-trips in its original format, except nextafter, which steps in the
// original encoding. The whole remquo family stays
// float-precision only: the pinned contract asserts
// decltype(remquo(1.0L, 2.0L, int*)) == float — adding double/long double
// overloads would make that call ambiguous (two floating-point conversions
// of the same rank). The nextafter family has a single definition point
// across the whole tree, here rather than on the rounding side, and the
// full family is defined in place.

//! @brief IEEE remainder x - n*y (n is the nearest quotient, ties to even):
//! |result| <= |y|/2; the nearest-even quotient can produce either sign.
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float remainder(
    float x, float y) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(remainderf, __builtin_remainderf, (x, y));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float remainderf(
    float x, float y) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(remainderf, __builtin_remainderf, (x, y));
}

//! @brief Extended floating point (half/bfloat16/fp8 family) remainder:
//! transits through float precision, returns in the original format.
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp remainder(
    Tp x, Tp y) noexcept
{
    return ::asc::std::__fp_cast<Tp>(
        ::asc::std::remainder(::asc::std::__fp_cast<float>(x), ::asc::std::__fp_cast<float>(y)));
}

//! @brief Same as remainder, additionally writing the remainder of n modulo
//! a backend-defined power of two (at least three low quotient bits, with
//! sign following x/y) into
//! @p quotient. Returns the IEEE remainder.
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float remquo(
    float x, float y, int* quotient) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(remquof, __builtin_remquof, (x, y, quotient));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float remquof(
    float x, float y, int* quotient) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(remquof, __builtin_remquof, (x, y, quotient));
}

//! @brief Extended floating point remquo: transits through float precision,
//! returns in the original format.
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp remquo(
    Tp x, Tp y, int* quotient) noexcept
{
    return ::asc::std::__fp_cast<Tp>(
        ::asc::std::remquo(::asc::std::__fp_cast<float>(x), ::asc::std::__fp_cast<float>(y), quotient));
}

//! @brief Next representable value in the direction of @p y (returns x when
//! x == y; equal signed zero returns y).
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float nextafter(
    float x, float y) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(nextafterf, __builtin_nextafterf, (x, y));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float nextafterf(
    float x, float y) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(nextafterf, __builtin_nextafterf, (x, y));
}

//! @brief Step one encoding in the original format, avoiding a float step
//! that can round back to the original half/bfloat16/fp8 value.
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp nextafter(
    Tp x, Tp y) noexcept
{
    using storage_type = __fp_storage_of_t<Tp>;
    using comparison_type = conditional_t<(sizeof(Tp) > sizeof(float)), Tp, float>;
    const comparison_type from = ::asc::std::__fp_cast<comparison_type>(x);
    const comparison_type toward = ::asc::std::__fp_cast<comparison_type>(y);
    if (from != from)
        return x;
    if (toward != toward || from == toward)
        return y;
    storage_type bits = ::asc::std::__fp_get_storage(x);
    if constexpr (__fp_is_signed_v<__fp_format_of_v<Tp>>) {
        const storage_type sign = bits & __fp_sign_mask_of_v<Tp>;
        if ((bits & __fp_exp_mant_mask_of_v<Tp>) == 0) {
            const storage_type target_sign = ::asc::std::__fp_get_storage(y) & __fp_sign_mask_of_v<Tp>;
            return ::asc::std::__fp_from_storage<Tp>(static_cast<storage_type>(target_sign | storage_type{1}));
        }
        bits = static_cast<storage_type>((from < toward) == (sign == 0) ? bits + 1 : bits - 1);
    } else {
        // E8M0 has positive finite encodings and a NaN, with no zero/sign bit.
        bits = static_cast<storage_type>(from < toward ? bits + 1 : bits - 1);
    }
    return ::asc::std::__fp_from_storage<Tp>(bits);
}

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// Full host type surface: double/long double primary names, the l-suffix
// alias, and mixed-type promote (a mixed int+float call normalizes to the
// common width through __promote_t, same shape as libstdc++).

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double remainder(double x, double y) noexcept
{
    return __builtin_remainder(x, y);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double remainder(long double x, long double y) noexcept
{
    return __builtin_remainderl(x, y);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double remainderl(long double x, long double y) noexcept
{
    return __builtin_remainderl(x, y);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

//! @brief remainder over two arithmetic operands of different types: both
//! promote to the common width first.
template <class Tp, class Up, ::asc::std::enable_if_t<is_arithmetic_v<Tp> && is_arithmetic_v<Up>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr __promote_t<Tp, Up> remainder(Tp x, Up y) noexcept
{
    using result_type = __promote_t<Tp, Up>;
    static_assert(!(is_same_v<Tp, result_type> && is_same_v<Up, result_type>));
    return ::asc::std::remainder(static_cast<result_type>(x), static_cast<result_type>(y));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double nextafter(double x, double y) noexcept
{
    return __builtin_nextafter(x, y);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double nextafter(long double x, long double y) noexcept
{
    return __builtin_nextafterl(x, y);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double nextafterl(long double x, long double y) noexcept
{
    return __builtin_nextafterl(x, y);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

//! @brief nextafter over two arithmetic operands of different types: both
//! promote to the common width first.
template <class Tp, class Up, ::asc::std::enable_if_t<is_arithmetic_v<Tp> && is_arithmetic_v<Up>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr __promote_t<Tp, Up> nextafter(Tp x, Up y) noexcept
{
    using result_type = __promote_t<Tp, Up>;
    static_assert(!(is_same_v<Tp, result_type> && is_same_v<Up, result_type>));
    return ::asc::std::nextafter(static_cast<result_type>(x), static_cast<result_type>(y));
}

#endif  // !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_REMAINDER_H
