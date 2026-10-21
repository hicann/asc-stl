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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_FMA_H
#define CANN_ASC_STL_ASC_STD___CMATH_FMA_H

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

// Native half-precision fused multiply-add for pure SIMT TUs: the 9.3.0
// toolchain lineage provides __hfma through simt_api/asc_fp16.h (numerically
// validated on 950 real hardware); header presence is probed with
// __has_include — the 9.2.0 lineage and the host fall back to the
// float-precision transit.
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
#if defined(__has_include)
#if __has_include(<simt_api/asc_fp16.h>)
#include <simt_api/asc_fp16.h>
#define CANN_ASC_STL_DETAIL_FMA_HW_HALF 1
#endif
#endif
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

// fma, three-layer dispatch: the float primary name and suffix aliases route
// through the backend — pure SIMT TUs go to the simt_api scalar library
// (reachable from __aicore__; real-machine testing confirmed its fmaf
// performs a single rounding), everything else uses the compiler builtins;
// double/long double primary names, the l-suffix alias, and mixed-type
// promote are host-only (double is forbidden on the vector cores, long
// double on device); extended floating point (half/bfloat16/fp8 family)
// transits through float precision and round-trips in its original format,
// and half takes the native fused path when SIMT and the toolchain provide
// __hfma.

//! @brief Fused multiply-add x*y + z (single rounding).
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float fma(
    float x, float y, float z) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(fmaf, __builtin_fmaf, (x, y, z));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float fmaf(
    float x, float y, float z) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(fmaf, __builtin_fmaf, (x, y, z));
}

//! @brief Extended floating point (half/bfloat16/fp8 family) fma: SIMT
//! hardware __hfma first (native half-precision fusion), otherwise
//! float-precision transit, returned in the original format.
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp fma(
    Tp x, Tp y, Tp z) noexcept
{
#if defined(CANN_ASC_STL_DETAIL_FMA_HW_HALF)
    if constexpr (is_same_v<Tp, half>) {
        return ::asc::std::__fp_cast<Tp>(::__hfma(x, y, z));
    } else  // NOLINT(readability/braces)
#endif
        return ::asc::std::__fp_cast<Tp>(::asc::std::fma(
            ::asc::std::__fp_cast<float>(x), ::asc::std::__fp_cast<float>(y), ::asc::std::__fp_cast<float>(z)));
}

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// Full host type surface: double/long double primary names, the l-suffix
// alias, integral promotion, and mixed-type promote. The pinned contract
// asserts decltype(fma(1, 2.0F, 3.0F)) == float: integral/float mixes
// resolve through implicit conversion to the non-template float overload
// (int->float and int->double have the same conversion rank, and the float
// overload wins the exact match on the floating arguments), all-integral
// combinations are disambiguated by the integral ternary overload and keep
// float precision; the promote template participates only when a
// double/long double argument is present and normalizes to the common width
// (a float+double mix would otherwise be ambiguous).

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double fma(double x, double y, double z) noexcept
{
    return __builtin_fma(x, y, z);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double fma(
    long double x, long double y, long double z) noexcept
{
    return __builtin_fmal(x, y, z);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double fmal(
    long double x, long double y, long double z) noexcept
{
    return __builtin_fmal(x, y, z);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

//! @brief All-integral fma: computes at float precision, preserving the
//! observable contract of the float-only era, and disambiguates the mixed
//! int-to-floating conversion ranks.
template <class Tp, class Up, class Vp,
    ::asc::std::enable_if_t<is_integral_v<Tp> && is_integral_v<Up> && is_integral_v<Vp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr float fma(Tp x, Up y, Vp z) noexcept
{
    return ::asc::std::fma(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
}

//! @brief fma over three arithmetic operands including at least one double or
//! long double: all promote to the common width first.
template <class Tp, class Up, class Vp,
    ::asc::std::enable_if_t<is_arithmetic_v<Tp> && is_arithmetic_v<Up> && is_arithmetic_v<Vp> &&
            (is_same_v<Tp, double> || is_same_v<Up, double> || is_same_v<Vp, double> || is_same_v<Tp, long double> ||
                is_same_v<Up, long double> || is_same_v<Vp, long double>),
        int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr __promote_t<Tp, Up, Vp> fma(Tp x, Up y, Vp z) noexcept
{
    using result_type = __promote_t<Tp, Up, Vp>;
    return ::asc::std::fma(static_cast<result_type>(x), static_cast<result_type>(y), static_cast<result_type>(z));
}

#endif  // !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_FMA_H
