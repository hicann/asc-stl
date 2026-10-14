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

#ifndef CANN_ASC_STL_ASC_STD___FLOATING_POINT_COMMON_TYPE_H
#define CANN_ASC_STL_ASC_STD___FLOATING_POINT_COMMON_TYPE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__floating_point/conversion_rank_order.h>
#include <asc/std/__type_traits/always_false.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_integral.h>

CANN_ASC_STL_BEGIN_NAMESPACE

//! @brief Common type of two floating-point types: the one with the higher
//! conversion rank (the __greater side). Unordered pairs, or pairs containing
//! an unknown type, make this alias substitution fail (SFINAE-friendly).
template <class Lhs, class Rhs>
using __fp_common_type_t = enable_if_t<__fp_conv_rank_order_v<Lhs, Rhs> != __fp_conv_rank_order::__unordered &&
        __fp_conv_rank_order_v<Lhs, Rhs> != __fp_conv_rank_order::__invalid,
    conditional_t<__fp_conv_rank_order_v<Lhs, Rhs> == __fp_conv_rank_order::__greater, Lhs, Rhs>>;

//! @brief Same as __fp_common_type_t, with integral types treated as double.
template <class Lhs, class Rhs>
using __fp_int_ext_common_type_t =
    __fp_common_type_t<conditional_t<is_integral_v<Lhs>, double, Lhs>, conditional_t<is_integral_v<Rhs>, double, Rhs>>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___FLOATING_POINT_COMMON_TYPE_H
