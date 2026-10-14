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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_FPCLASSIFY_H
#define CANN_ASC_STL_ASC_STD___CMATH_FPCLASSIFY_H

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
#include <asc/std/__floating_point/mask.h>
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

// Classification return values use the glibc/facade numbering as bare
// literals (FP_NAN=0, FP_INFINITE=1, FP_ZERO=2, FP_SUBNORMAL=3, FP_NORMAL=4).
// The FP_* macro surface is not defined in this header: on the host the
// asc/std/cmath facade provides same-value fallbacks at the end of the file,
// and when host math.h is already included its values are reused;
// predefining the macros here would break, through macro expansion, the
// FP_NAN enum technique (an enum member named like the macro) of a host
// math.h included afterwards.

CANN_ASC_STL_BEGIN_NAMESPACE

//! @brief Classification through the storage representation: the exponent
//! field alone separates the all-ones class (infinity keeps only the
//! explicit integer bit, any other significand is a NaN — the explicit-bit
//! formats such as the x87 extended layout included) from zero/subnormal
//! (all-zero exponent, distinguished by the significand) and the normal
//! numbers. Bit-exact with the reference semantics, constexpr and free of
//! floating-point arithmetic and of any numeric_limits surface on every
//! compilation path — usable for the extended floating-point formats too.
template <class Tp>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr int __fpclassify_impl(Tp x) noexcept
{
    static_assert(__fp_has_denorm_v<__fp_format_of_v<Tp>>, "The type must have denorm support");
    const auto storage = ::asc::std::__fp_get_storage(x);
    const auto exponent = static_cast<decltype(storage)>(storage & __fp_exp_mask_of_v<Tp>);
    const auto significand = static_cast<decltype(storage)>(storage & __fp_mant_mask_of_v<Tp>);
    if (exponent == __fp_exp_mask_of_v<Tp>) {
        return significand == __fp_explicit_bit_mask_of_v<Tp> ? 1 : 0;  // FP_INFINITE : FP_NAN
    }
    if (exponent == 0) {
        return significand != 0 ? 3 : 2;  // FP_SUBNORMAL : FP_ZERO
    }
    return 4;  // FP_NORMAL
}

//! @brief Classifies @p x as FP_NAN, FP_INFINITE, FP_NORMAL, FP_SUBNORMAL or
//! FP_ZERO — constexpr on every path, host and AI-core alike, through the
//! storage representation.
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr int fpclassify(float x) noexcept
{
    return ::asc::std::__fpclassify_impl(x);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr int fpclassify(double x) noexcept
{
    return ::asc::std::__fpclassify_impl(x);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr int fpclassify(long double x) noexcept
{
    return ::asc::std::__fpclassify_impl(x);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

//! @brief Extended floating point (half/bfloat16/fp8 family) classification:
//! goes directly through the storage bits (no numeric_limits surface
//! dependency), judged in the original format.
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr int fpclassify(Tp x) noexcept
{
    return ::asc::std::__fpclassify_impl(x);
}

//! @brief Classification for integral arguments: 0 is FP_ZERO, everything
//! else (bool included) is always FP_NORMAL (any integral type is a finite
//! normal number once given a floating-point representation). Exact matching
//! disambiguates the equal-rank int->float/int->double conversions.
template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr int fpclassify(Tp x) noexcept
{
    return x == Tp{} ? 2 : 4;  // FP_ZERO : FP_NORMAL
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_FPCLASSIFY_H
