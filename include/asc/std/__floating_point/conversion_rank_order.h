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

#ifndef CANN_ASC_STL_ASC_STD___FLOATING_POINT_CONVERSION_RANK_ORDER_H
#define CANN_ASC_STL_ASC_STD___FLOATING_POINT_CONVERSION_RANK_ORDER_H

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
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__floating_point/traits.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_same.h>

// <asc/__config> does not provide CANN_ASC_STL_DETAIL_CONSTEVAL: inline a
// minimal equivalent (consteval in C++20 and newer when the compiler advertises
// <consteval>, constexpr otherwise).
#if !defined(CANN_ASC_STL_DETAIL_CONSTEVAL)
#if CANN_ASC_STL_DETAIL_HAS_CXX20() && defined(__cpp_consteval) && __cpp_consteval >= 201811L
#define CANN_ASC_STL_DETAIL_CONSTEVAL consteval
#else
#define CANN_ASC_STL_DETAIL_CONSTEVAL constexpr
#endif
#endif  // CANN_ASC_STL_DETAIL_CONSTEVAL

// <asc/__config> does not provide CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE():
// inline the gate here — long double is host-only, ASC device compilation
// (AI Core) does not support long double.
#if !defined(CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE)
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && !defined(ASC_DISABLE_LONG_DOUBLE_SUPPORT)
#define CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE() 0
#endif
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE

CANN_ASC_STL_BEGIN_NAMESPACE

//! @brief Conversion-rank order between two floating-point formats (P1467
//!        semantics, ordered by format containment).
enum class __fp_conv_rank_order {
    __invalid = -1,
    __unordered,
    __greater,
    __equal,
    __less,
};

template <class Lhs, class Rhs>
constexpr __fp_conv_rank_order __fp_conv_rank_order_v_impl() noexcept
{
    if constexpr (__is_fp_v<Lhs> && __is_fp_v<Rhs>) {
        if constexpr (__fp_is_subset_of_v<Lhs, Rhs> && __fp_is_subset_of_v<Rhs, Lhs>) {
#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
            // When double and long double have identical properties, long double
            // takes the higher sub-rank
            if constexpr (__fp_is_subset_of_v<long double, double>) {
                if constexpr (is_same_v<Lhs, long double> && !is_same_v<Rhs, long double>) {
                    return __fp_conv_rank_order::__greater;
                } else if constexpr (!is_same_v<Lhs, long double> && is_same_v<Rhs, long double>) {
                    return __fp_conv_rank_order::__less;
                } else {
                    return __fp_conv_rank_order::__equal;
                }
            } else  // NOLINT(readability/braces)
#endif              // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
            {
                return __fp_conv_rank_order::__equal;
            }
        } else if constexpr (__fp_is_subset_of_v<Rhs, Lhs>) {
            return __fp_conv_rank_order::__greater;
        } else if constexpr (__fp_is_subset_of_v<Lhs, Rhs>) {
            return __fp_conv_rank_order::__less;
        } else {
            return __fp_conv_rank_order::__unordered;
        }
    } else {
        return __fp_conv_rank_order::__invalid;
    }
}

//! @brief Returns the conversion-rank order between two types. Returns
//!        __fp_conv_rank_order::__invalid when either type is not a known
//!        floating-point type.
template <class Lhs, class Rhs>
inline constexpr __fp_conv_rank_order __fp_conv_rank_order_v = __fp_conv_rank_order_v_impl<Lhs, Rhs>();

//! @brief Returns the conversion-rank order between two types. Integral types
//!        are treated as double; other non-floating-point types count as
//!        unknown and return __fp_conv_rank_order::__invalid.
template <class Lhs, class Rhs>
inline constexpr __fp_conv_rank_order __fp_conv_rank_order_int_ext_v =
    __fp_conv_rank_order_v<conditional_t<is_integral_v<Lhs>, double, Lhs>,
        conditional_t<is_integral_v<Rhs>, double, Rhs>>;

//! @brief Whether From converts implicitly to To under the floating-point
//!        conversion-rank rules.
//! @warning Callers must ensure both types are known floating-point types.
//! @note Use __fp_is_explicit_conversion_v to check explicit conversions.
template <class From, class To>
inline constexpr bool __fp_is_implicit_conversion_v =
    __fp_conv_rank_order_v<From, To> == __fp_conv_rank_order::__less ||
    __fp_conv_rank_order_v<From, To> == __fp_conv_rank_order::__equal;

//! @brief Whether From converts explicitly to To under the floating-point
//!        conversion-rank rules.
//! @warning Callers must ensure both types are known floating-point types.
//! @note Use __fp_is_implicit_conversion_v to check implicit conversions.
template <class From, class To>
inline constexpr bool __fp_is_explicit_conversion_v =
    __fp_conv_rank_order_v<From, To> == __fp_conv_rank_order::__greater ||
    __fp_conv_rank_order_v<From, To> == __fp_conv_rank_order::__unordered;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___FLOATING_POINT_CONVERSION_RANK_ORDER_H
