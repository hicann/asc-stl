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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_MODULO_H
#define CANN_ASC_STL_ASC_STD___CMATH_MODULO_H

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

// fmod, three-layer dispatch: the float primary name and suffix aliases
// route through the backend — pure SIMT TUs go to the simt_api scalar
// library (reachable from __aicore__), everything else uses the compiler
// builtins; double/long double primary names, the l-suffix alias, and
// mixed-type promote are host-only (double is forbidden on the vector cores,
// long double on device); extended floating point (half/bfloat16/fp8 family)
// transits through float precision and round-trips in its original format.
// The sibling modf/modff are defined in __cmath/exponential_functions.h
// (host + device-SIMT surface); moving them into this file would cause
// redefinitions, so this file keeps the fmod family only.

//! @brief Floating-point remainder: the result has the same sign as @p x and
//! satisfies |result| < |y| (quotient truncated toward zero). Domain error
//! when y is 0 or x is infinite; the contract is carried by native fmodf
//! (returns NaN).
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float fmod(
    float x, float y) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(fmodf, __builtin_fmodf, (x, y));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float fmodf(
    float x, float y) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(fmodf, __builtin_fmodf, (x, y));
}

//! @brief Extended floating point (half/bfloat16/fp8 family) fmod: transits
//! through float precision, returns in the original format.
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp fmod(
    Tp x, Tp y) noexcept
{
    return ::asc::std::__fp_cast<Tp>(
        ::asc::std::fmod(::asc::std::__fp_cast<float>(x), ::asc::std::__fp_cast<float>(y)));
}

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// Full host type surface: double/long double primary names, the l-suffix
// alias, and mixed-type promote (a mixed int+float call normalizes to the
// common width through __promote_t, same shape as libstdc++).

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double fmod(double x, double y) noexcept
{
    return __builtin_fmod(x, y);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double fmod(long double x, long double y) noexcept
{
    return __builtin_fmodl(x, y);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double fmodl(long double x, long double y) noexcept
{
    return __builtin_fmodl(x, y);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

//! @brief fmod over two arithmetic operands of different types: both promote
//! to the common width first.
template <class Tp, class Up, ::asc::std::enable_if_t<is_arithmetic_v<Tp> && is_arithmetic_v<Up>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr __promote_t<Tp, Up> fmod(Tp x, Up y) noexcept
{
    using result_type = __promote_t<Tp, Up>;
    static_assert(!(is_same_v<Tp, result_type> && is_same_v<Up, result_type>));
    return ::asc::std::fmod(static_cast<result_type>(x), static_cast<result_type>(y));
}

#endif  // !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_MODULO_H
