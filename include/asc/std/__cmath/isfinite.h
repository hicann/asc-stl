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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_ISFINITE_H
#define CANN_ASC_STL_ASC_STD___CMATH_ISFINITE_H

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
#include <asc/std/__type_traits/is_floating_point.h>
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

//! @brief Finite check through the storage representation: inspect only the
//! exponent field — all-ones means NaN or infinity, everything else (zero,
//! subnormal and normal numbers alike) is finite. Bit-exact with the reference
//! semantics, constexpr and free of floating-point arithmetic on every
//! compilation path, host and AI-core alike.
template <class Tp>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool __isfinite_impl(Tp x) noexcept
{
    static_assert(is_floating_point_v<Tp>, "Only standard floating-point types are supported");
    return (::asc::std::__fp_get_storage(x) & __fp_exp_mask_of_v<Tp>) != __fp_exp_mask_of_v<Tp>;
}

//! @brief Reports whether @p x is a finite value (zero, subnormal or normal —
//! not NaN, not infinity).
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool isfinite(float x) noexcept
{
    return ::asc::std::__isfinite_impl(x);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool isfinite(double x) noexcept
{
    return ::asc::std::__isfinite_impl(x);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool isfinite(long double x) noexcept
{
    return ::asc::std::__isfinite_impl(x);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

//! @brief Extended floating point (half/bfloat16/fp8 family) isfinite:
//! float-precision transit (every extended format is a proper subset of
//! float, so the widening is lossless); NaN/infinity are never misreported.
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool isfinite(Tp x) noexcept
{
    return ::asc::std::isfinite(static_cast<float>(x));
}

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool isfinite(Tp) noexcept
{
    return true;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_ISFINITE_H
