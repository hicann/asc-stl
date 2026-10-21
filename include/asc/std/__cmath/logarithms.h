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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_LOGARITHMS_H
#define CANN_ASC_STL_ASC_STD___CMATH_LOGARITHMS_H

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
#include <asc/std/__type_traits/is_same.h>

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

// C99 ilogb special-value contract macros (when the host <math.h> is already
// included its values are reused, keeping consistency with the runtime
// ::ilogb result; device TUs lack that header, so glibc-identical fallback
// values are provided).
#ifndef FP_ILOGB0
#define FP_ILOGB0 (-2147483647 - 1)
#endif
#ifndef FP_ILOGBNAN
#define FP_ILOGBNAN 2147483647
#endif

// Hardware logarithm family for half/bfloat16 in pure SIMT TUs: the hlog
// family takes the dedicated hardware path, whose saturation mode changes
// the special values per the SIMT API documentation; header presence is
// probed with __has_include — older toolchain lineages fall back to the
// float-precision transit.
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
#if defined(__has_include)
#if __has_include(<simt_api/asc_fp16.h>)
#include <simt_api/asc_fp16.h>
#define CANN_ASC_STL_DETAIL_LOG_HW_HALF 1
#endif
#if __has_include(<simt_api/asc_bf16.h>)
#include <simt_api/asc_bf16.h>
#define CANN_ASC_STL_DETAIL_LOG_HW_BF16 1
#endif
#endif
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

// Logarithm family, three-layer dispatch: the primary float name and the
// suffix aliases route through the backend — pure SIMT TUs go to the simt_api
// scalar library (reachable from __aicore__), everything else uses the
// compiler builtins; double/long double/integral promotion and the l-suffix
// alias are host-only (the vector cores have no double-precision arithmetic,
// and long double is forbidden on device); extended floating point transits
// through float precision and round-trips in its original format.

//! @brief Natural logarithm ln(@p value).
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float log(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(logf, __builtin_logf, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float logf(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(logf, __builtin_logf, (value));
}

//! @brief Extended floating point (half/bfloat16/fp8 family) log: SIMT
//! hardware hlog family first (saturation-mode special values per the SIMT
//! API documentation), otherwise float-precision transit, returned in the
//! original format.
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp log(Tp value) noexcept
{
#if defined(CANN_ASC_STL_DETAIL_LOG_HW_HALF)
    if constexpr (is_same_v<Tp, half>) {
        return ::hlog(value);
    } else  // NOLINT(readability/braces)
#endif
#if defined(CANN_ASC_STL_DETAIL_LOG_HW_BF16)
        if constexpr (is_same_v<Tp, bfloat16_t>) {
        return ::hlog(value);
    } else  // NOLINT(readability/braces)
#endif
        return ::asc::std::__fp_cast<Tp>(::asc::std::log(::asc::std::__fp_cast<float>(value)));
}

//! @brief Common (base-10) logarithm log10(@p value).
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float log10(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(log10f, __builtin_log10f, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float log10f(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(log10f, __builtin_log10f, (value));
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp log10(
    Tp value) noexcept
{
#if defined(CANN_ASC_STL_DETAIL_LOG_HW_HALF)
    if constexpr (is_same_v<Tp, half>) {
        return ::hlog10(value);
    } else  // NOLINT(readability/braces)
#endif
#if defined(CANN_ASC_STL_DETAIL_LOG_HW_BF16)
        if constexpr (is_same_v<Tp, bfloat16_t>) {
        return ::hlog10(value);
    } else  // NOLINT(readability/braces)
#endif
        return ::asc::std::__fp_cast<Tp>(::asc::std::log10(::asc::std::__fp_cast<float>(value)));
}

//! @brief log(1 + @p value); preserves precision when @p value is close to 0.
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float log1p(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(log1pf, __builtin_log1pf, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float log1pf(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(log1pf, __builtin_log1pf, (value));
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp log1p(
    Tp value) noexcept
{
    return ::asc::std::__fp_cast<Tp>(::asc::std::log1p(::asc::std::__fp_cast<float>(value)));
}

//! @brief Base-2 logarithm.
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float log2(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(log2f, __builtin_log2f, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float log2f(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(log2f, __builtin_log2f, (value));
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp log2(Tp value) noexcept
{
#if defined(CANN_ASC_STL_DETAIL_LOG_HW_HALF)
    if constexpr (is_same_v<Tp, half>) {
        return ::hlog2(value);
    } else  // NOLINT(readability/braces)
#endif
#if defined(CANN_ASC_STL_DETAIL_LOG_HW_BF16)
        if constexpr (is_same_v<Tp, bfloat16_t>) {
        return ::hlog2(value);
    } else  // NOLINT(readability/braces)
#endif
        return ::asc::std::__fp_cast<Tp>(::asc::std::log2(::asc::std::__fp_cast<float>(value)));
}

//! @brief Normalized exponent of @p value (unbiased exponent, returned as an
//! integer). NaN contract: the device's native ilogbf returns ASCRT_MIN_VAL_S
//! for NaN, so FP_ILOGBNAN is returned here per the C++ contract; 0 returns
//! FP_ILOGB0.
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR int ilogb(
    float value) noexcept
{
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    return value != value ? FP_ILOGBNAN : ::ilogbf(value);
#else
    return __builtin_ilogbf(value);
#endif
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR int ilogbf(
    float value) noexcept
{
    return ::asc::std::ilogb(value);
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR int ilogb(
    Tp value) noexcept
{
    return ::asc::std::ilogb(::asc::std::__fp_cast<float>(value));
}

//! @brief Normalized exponent of @p value (returned as floating point).
//! ±0 -> -inf, ±inf -> +inf, NaN -> NaN.
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float logb(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(logbf, __builtin_logbf, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float logbf(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(logbf, __builtin_logbf, (value));
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp logb(Tp value) noexcept
{
    return ::asc::std::__fp_cast<Tp>(::asc::std::logb(::asc::std::__fp_cast<float>(value)));
}

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// Full host type surface: double/long double primary names, the l-suffix
// alias, and integral promotion. Integral promotion aligns with the <cmath>
// standard: integral arguments are promoted to double, computed and returned
// as double.

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double log(double value) noexcept
{
    return __builtin_log(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double log(long double value) noexcept
{
    return __builtin_logl(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double logl(long double value) noexcept
{
    return __builtin_logl(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double log(Tp value) noexcept
{
    return ::asc::std::log(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double log10(double value) noexcept
{
    return __builtin_log10(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double log10(long double value) noexcept
{
    return __builtin_log10l(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double log10l(long double value) noexcept
{
    return __builtin_log10l(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double log10(Tp value) noexcept
{
    return ::asc::std::log10(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double log1p(double value) noexcept
{
    return __builtin_log1p(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double log1p(long double value) noexcept
{
    return __builtin_log1pl(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double log1pl(long double value) noexcept
{
    return __builtin_log1pl(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double log1p(Tp value) noexcept
{
    return ::asc::std::log1p(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double log2(double value) noexcept
{
    return __builtin_log2(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double log2(long double value) noexcept
{
    return __builtin_log2l(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double log2l(long double value) noexcept
{
    return __builtin_log2l(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double log2(Tp value) noexcept
{
    return ::asc::std::log2(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr int ilogb(double value) noexcept
{
    return __builtin_ilogb(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr int ilogb(long double value) noexcept
{
    return __builtin_ilogbl(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr int ilogbl(long double value) noexcept
{
    return __builtin_ilogbl(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr int ilogb(Tp value) noexcept
{
    return ::asc::std::ilogb(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double logb(double value) noexcept
{
    return __builtin_logb(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double logb(long double value) noexcept
{
    return __builtin_logbl(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double logbl(long double value) noexcept
{
    return __builtin_logbl(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double logb(Tp value) noexcept
{
    return ::asc::std::logb(static_cast<double>(value));
}

#endif  // !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_LOGARITHMS_H
