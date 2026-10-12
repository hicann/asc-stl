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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_ISNORMAL_H
#define CANN_ASC_STL_ASC_STD___CMATH_ISNORMAL_H

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
#include <asc/std/__floating_point/fp.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_extended_floating_point.h>
#include <asc/std/__type_traits/is_floating_point.h>
#include <asc/std/__type_traits/is_integral.h>

// Inline equivalent of the dev CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE() gate
// (the master config does not provide it): long double is host-only — AI-core
// compilation does not support long double.
#if !defined(CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE)
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && !defined(ASC_DISABLE_LONG_DOUBLE_SUPPORT)
#define CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE() 0
#endif
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE

CANN_ASC_STL_BEGIN_NAMESPACE

//! @brief Classification through the storage representation: the exponent
//! field alone separates normal numbers from everything else — an all-zero
//! exponent encodes zero or subnormal, an all-ones exponent encodes infinity
//! or NaN. Bit-exact with the source semantics for every IEEE-754 style
//! format, standard and extended alike, without touching numeric_limits or
//! any floating-point arithmetic. Formats beyond the delivered storage
//! vocabulary (x87 fp80 / binary128 native long double) classify through the
//! compiler's bit-exact isnormal builtin, which performs the same
//! exponent-field check.
template <class Tp>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool __isnormal_impl(Tp x) noexcept
{
    static_assert(
        is_floating_point_v<Tp> || __is_extended_floating_point_v<Tp>, "Only floating-point types are supported");
    if constexpr (__fp_format_of_v<Tp> == __fp_format::__binary16 ||  // NOLINT(readability/braces)
        __fp_format_of_v<Tp> == __fp_format::__bfloat16 || __fp_format_of_v<Tp> == __fp_format::__binary32 ||
        __fp_format_of_v<Tp> == __fp_format::__binary64) {
        const auto exponent = ::asc::std::__fp_get_storage(x) & __fp_exp_mask_of_v<Tp>;
        return exponent != 0 && exponent != __fp_exp_mask_of_v<Tp>;
    } else {
        return __builtin_isnormal(x);
    }
}

//! @brief Reports whether @p x is a normal number: non-zero, not subnormal,
//! not infinity and not NaN. Constexpr on every path, host and device alike,
//! built from the migrated floating-point storage surface.
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool isnormal(float x) noexcept
{
    return ::asc::std::__isnormal_impl(x);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool isnormal(double x) noexcept
{
    return ::asc::std::__isnormal_impl(x);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool isnormal(long double x) noexcept
{
    return ::asc::std::__isnormal_impl(x);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

//! @brief Extended floating-point formats (half, bfloat16 and friends)
//! classify through the same exponent-field check, replacing the source's
//! per-format overloads with the extended floating-point surface.
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool isnormal(Tp x) noexcept
{
    return ::asc::std::__isnormal_impl(x);
}

//! @brief Integral values are never subnormal, infinite or NaN: they are
//! normal exactly when non-zero, matching the source contract.
template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool isnormal(Tp x) noexcept
{
    return x != 0;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_ISNORMAL_H
