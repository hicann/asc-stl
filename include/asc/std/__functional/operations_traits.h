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

#ifndef CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_OPERATIONS_TRAITS_H
#define CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_OPERATIONS_TRAITS_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__functional/operations.h>
#include <asc/std/__type_traits/is_same.h>

#if CANN_ASC_STL_DETAIL_HOSTED()
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_STD

template <typename>
struct plus;
template <typename>
struct multiplies;
template <typename>
struct bit_and;
template <typename>
struct bit_or;
template <typename>
struct bit_xor;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_STD
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <typename _BinaryOp>
#if CANN_ASC_STL_DETAIL_HOSTED()
inline constexpr bool __is_plus_op_v = is_same_v<_BinaryOp, plus<>> || is_same_v<_BinaryOp, ::std::plus<void>>;
#else
inline constexpr bool __is_plus_op_v = is_same_v<_BinaryOp, plus<>>;
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

template <typename _BinaryOp>
#if CANN_ASC_STL_DETAIL_HOSTED()
inline constexpr bool __is_multiplies_op_v =
    is_same_v<_BinaryOp, multiplies<>> || is_same_v<_BinaryOp, ::std::multiplies<void>>;
#else
inline constexpr bool __is_multiplies_op_v = is_same_v<_BinaryOp, multiplies<>>;  // NOLINT(build/include_what_you_use)
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

template <typename _BinaryOp>
#if CANN_ASC_STL_DETAIL_HOSTED()
inline constexpr bool __is_bit_and_op_v = is_same_v<_BinaryOp, bit_and<>> || is_same_v<_BinaryOp, ::std::bit_and<void>>;
#else
inline constexpr bool __is_bit_and_op_v = is_same_v<_BinaryOp, bit_and<>>;
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

template <typename _BinaryOp>
#if CANN_ASC_STL_DETAIL_HOSTED()
inline constexpr bool __is_bit_or_op_v = is_same_v<_BinaryOp, bit_or<>> || is_same_v<_BinaryOp, ::std::bit_or<void>>;
#else
inline constexpr bool __is_bit_or_op_v = is_same_v<_BinaryOp, bit_or<>>;
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

template <typename _BinaryOp>
#if CANN_ASC_STL_DETAIL_HOSTED()
inline constexpr bool __is_bit_xor_op_v = is_same_v<_BinaryOp, bit_xor<>> || is_same_v<_BinaryOp, ::std::bit_xor<void>>;
#else
inline constexpr bool __is_bit_xor_op_v = is_same_v<_BinaryOp, bit_xor<>>;
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_OPERATIONS_TRAITS_H
