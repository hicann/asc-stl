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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_ISINF_H
#define CANN_ASC_STL_ASC_STD___CMATH_ISINF_H

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

//! @brief Infinity check through the storage representation: the exponent
//! field is all ones and the significand keeps only the explicit integer bit
//! (zero for implicit-bit formats, the top significand bit for the x87
//! extended layout) — false for NaNs, bit-exact with the source semantics,
//! constexpr and free of floating-point arithmetic on every compilation
//! path, host and AI-core alike.
template <class Tp>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool __isinf_impl(Tp x) noexcept
{
    static_assert(is_floating_point_v<Tp>, "Only standard floating-point types are supported");
    return (::asc::std::__fp_get_storage(x) & __fp_exp_mant_mask_of_v<Tp>) ==
        static_cast<__fp_storage_of_t<Tp>>(__fp_exp_mask_of_v<Tp> | __fp_explicit_bit_mask_of_v<Tp>);
}

//! @brief Reports whether @p x is an infinity.
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool isinf(float x) noexcept
{
    return ::asc::std::__isinf_impl(x);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool isinf(double x) noexcept
{
    return ::asc::std::__isinf_impl(x);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool isinf(long double x) noexcept
{
    return ::asc::std::__isinf_impl(x);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

//! @brief 扩展浮点（half/bfloat16/fp8 族）isinf：float 精度中转（扩展格式
//! 全部为 float 的真子集，宽化无损），NaN 不误报。
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool isinf(Tp x) noexcept
{
    return ::asc::std::isinf(static_cast<float>(x));
}

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool isinf(Tp) noexcept
{
    return false;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_ISINF_H
