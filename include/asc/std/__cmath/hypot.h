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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_HYPOT_H
#define CANN_ASC_STL_ASC_STD___CMATH_HYPOT_H

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

// hypot, three-layer dispatch: the float primary name and suffix aliases
// route through the backend — pure SIMT TUs go to the simt_api scalar
// library (reachable from __aicore__), everything else uses the compiler
// builtins; double/long double primary names, the l-suffix alias, and
// mixed-type promote are host-only (double is forbidden on the vector cores,
// long double on device); extended floating point (half/bfloat16/fp8 family)
// transits through float precision and round-trips in its original format.
// Three-argument hypot composes two two-argument layers (each call already
// scales internally, isomorphic to the libstdc++ three-argument std::hypot
// implementation), fixing the intermediate overflow that the direct
// x*x+y*y+z*z sum suffers on large-magnitude inputs.

//! @brief Overflow-free implementation of sqrt(x*x + y*y) (internal scaling;
//! the NaN/infinity contract is carried by native hypotf).
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float hypot(
    float x, float y) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(hypotf, __builtin_hypotf, (x, y));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float hypotf(
    float x, float y) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(hypotf, __builtin_hypotf, (x, y));
}

//! @brief Three-dimensional hypotenuse sqrt(x*x+y*y+z*z): two two-argument
//! layers composed, no intermediate overflow/underflow.
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float hypot(
    float x, float y, float z) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(
        hypotf, __builtin_hypotf, (CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(hypotf, __builtin_hypotf, (x, y)), z));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float hypotf(
    float x, float y, float z) noexcept
{
    return ::asc::std::hypot(x, y, z);
}

//! @brief Extended floating point (half/bfloat16/fp8 family) hypot: transits
//! through float precision, returns in the original format.
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp hypot(
    Tp x, Tp y) noexcept
{
    return ::asc::std::__fp_cast<Tp>(
        ::asc::std::hypot(::asc::std::__fp_cast<float>(x), ::asc::std::__fp_cast<float>(y)));
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp hypot(
    Tp x, Tp y, Tp z) noexcept
{
    return ::asc::std::__fp_cast<Tp>(::asc::std::hypot(
        ::asc::std::__fp_cast<float>(x), ::asc::std::__fp_cast<float>(y), ::asc::std::__fp_cast<float>(z)));
}

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// Full host type surface: double/long double primary names, the l-suffix
// alias, and mixed-type promote (a mixed int+float call normalizes to the
// common width through __promote_t, same shape as libstdc++).

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double hypot(double x, double y) noexcept
{
    return __builtin_hypot(x, y);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double hypot(long double x, long double y) noexcept
{
    return __builtin_hypotl(x, y);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double hypotl(long double x, long double y) noexcept
{
    return __builtin_hypotl(x, y);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

//! @brief hypot over two arithmetic operands of different types: both promote
//! to the common width first.
template <class Tp, class Up, ::asc::std::enable_if_t<is_arithmetic_v<Tp> && is_arithmetic_v<Up>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr __promote_t<Tp, Up> hypot(Tp x, Up y) noexcept
{
    using result_type = __promote_t<Tp, Up>;
    static_assert(!(is_same_v<Tp, result_type> && is_same_v<Up, result_type>));
    return ::asc::std::hypot(static_cast<result_type>(x), static_cast<result_type>(y));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double hypot(double x, double y, double z) noexcept
{
    return __builtin_hypot(__builtin_hypot(x, y), z);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double hypot(
    long double x, long double y, long double z) noexcept
{
    return __builtin_hypotl(__builtin_hypotl(x, y), z);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double hypotl(
    long double x, long double y, long double z) noexcept
{
    return ::asc::std::hypot(x, y, z);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

//! @brief hypot over three arithmetic operands of different types: all promote
//! to the common width first.
template <class Tp, class Up, class Vp,
    ::asc::std::enable_if_t<is_arithmetic_v<Tp> && is_arithmetic_v<Up> && is_arithmetic_v<Vp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr __promote_t<Tp, Up, Vp> hypot(Tp x, Up y, Vp z) noexcept
{
    using result_type = __promote_t<Tp, Up, Vp>;
    static_assert(!(is_same_v<Tp, result_type> && is_same_v<Up, result_type> && is_same_v<Vp, result_type>));
    return ::asc::std::hypot(static_cast<result_type>(x), static_cast<result_type>(y), static_cast<result_type>(z));
}

#endif  // !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_HYPOT_H
