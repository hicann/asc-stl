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

#ifndef CANN_ASC_STL_ASC_STD___RANDOM_IS_VALID_H
#define CANN_ASC_STL_ASC_STD___RANDOM_IS_VALID_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_floating_point.h>
#include <asc/std/__type_traits/is_integer.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_unsigned.h>
#include <asc/std/__type_traits/is_unsigned_integer.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// [rand.req.genl]（P4037R1 措辞）：对应 RealType 模板形参的实参必须是
// cv 非限定的（扩展）浮点类型，否则程序非良构。判定保持 cv 敏感：
// const float 等带限定浮点类型不满足要求（此前经剥 cv 的 is_floating_point_v
// 误放行）。
template <class T>
inline constexpr bool __asc_random_is_valid_realtype = is_floating_point_v<T> && is_same_v<T, remove_cv_t<T>>;

// [rand.req.genl]（P4037R1 措辞）：对应 IntType 模板形参的实参必须是
// cv 非限定的（扩展）整数类型；__is_integer_v 恰为该语义：含 signed char
// 与 unsigned char，排除 char、bool 与各种字符宽字符类型。
template <class T>
inline constexpr bool __asc_random_is_valid_inttype = __is_integer_v<T>;

// [rand.req.genl]（P4037R1 措辞）：对应 UIntType 模板形参的实参必须是
// cv 非限定的（扩展）无符号整数类型。P4037R1 4.5 节把 unsigned char
// 纳入实现定义子集，使 linear_congruential_engine<unsigned char, ...>
// 一类窄引擎可用。
template <class T>
inline constexpr bool __asc_random_is_valid_uinttype = __is_unsigned_integer_v<T>;

// [rand.req.urng]：G 满足均匀随机位生成器要求，当且仅当 invoke_result_t<G&>
// 为无符号整数类型，且 G 提供与之一致的嵌套 result_type。带符号结果类型
// 的发生器被拒绝（分布实现无法处理）。
template <class, class = void>
inline constexpr bool __asc_random_is_valid_urng = false;
template <class G>
inline constexpr bool __asc_random_is_valid_urng<G,
    enable_if_t<is_unsigned_v<typename G::result_type> &&
        is_same_v<decltype(::asc::std::declval<G&>()()), typename G::result_type>>> = true;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANDOM_IS_VALID_H
