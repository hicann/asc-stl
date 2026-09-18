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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_OPERATIONS_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_OPERATIONS_H

#include <asc/std/detail/__config>

#include <asc/std/__cstddef/types.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/void_t.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

// Use expression-SFINAE rather than native requires-expressions. ASC-STL has a
// C++17 floor, while this internal facility must also remain usable as a
// boolean constraint expression in C++20 and later.

template <class _Tp>
_Tp&& __operation_declval() noexcept;

#define CANN_ASC_STL_DETAIL_ACCL_DEFINE_UNARY_OPERATION(_Name, _Expression) \
    template <class _Tp, class = void>                                      \
    struct _Name##_impl : false_type {};                                    \
    template <class _Tp>                                                    \
    struct _Name##_impl<_Tp, void_t<decltype(_Expression)>> : true_type {}; \
    template <class _Tp>                                                    \
    inline constexpr bool _Name = _Name##_impl<_Tp>::value

#define CANN_ASC_STL_DETAIL_ACCL_DEFINE_BINARY_OPERATION(_Name, _Expression) \
    template <class _Tp, class = void>                                       \
    struct _Name##_impl : false_type {};                                     \
    template <class _Tp>                                                     \
    struct _Name##_impl<_Tp, void_t<decltype(_Expression)>> : true_type {};  \
    template <class _Tp>                                                     \
    inline constexpr bool _Name = _Name##_impl<_Tp>::value

// unary operator constraints

CANN_ASC_STL_DETAIL_ACCL_DEFINE_UNARY_OPERATION(__has_pre_increment, ++__operation_declval<_Tp&>());
CANN_ASC_STL_DETAIL_ACCL_DEFINE_UNARY_OPERATION(__has_post_increment, __operation_declval<_Tp&>()++);
CANN_ASC_STL_DETAIL_ACCL_DEFINE_UNARY_OPERATION(__has_pre_decrement, --__operation_declval<_Tp&>());
CANN_ASC_STL_DETAIL_ACCL_DEFINE_UNARY_OPERATION(__has_post_decrement, __operation_declval<_Tp&>()--);
CANN_ASC_STL_DETAIL_ACCL_DEFINE_UNARY_OPERATION(__has_negate, !__operation_declval<const _Tp&>());
CANN_ASC_STL_DETAIL_ACCL_DEFINE_UNARY_OPERATION(__has_bitwise_not, ~__operation_declval<const _Tp&>());
CANN_ASC_STL_DETAIL_ACCL_DEFINE_UNARY_OPERATION(__has_unary_plus, +__operation_declval<const _Tp&>());
CANN_ASC_STL_DETAIL_ACCL_DEFINE_UNARY_OPERATION(__has_unary_minus, -__operation_declval<const _Tp&>());

// binary operator constraints

CANN_ASC_STL_DETAIL_ACCL_DEFINE_BINARY_OPERATION(
    __has_binary_plus, __operation_declval<_Tp&>() + __operation_declval<_Tp&>());
CANN_ASC_STL_DETAIL_ACCL_DEFINE_BINARY_OPERATION(
    __has_binary_minus, __operation_declval<_Tp&>() - __operation_declval<_Tp&>());
CANN_ASC_STL_DETAIL_ACCL_DEFINE_BINARY_OPERATION(
    __has_multiplies, __operation_declval<_Tp&>() * __operation_declval<_Tp&>());
CANN_ASC_STL_DETAIL_ACCL_DEFINE_BINARY_OPERATION(
    __has_divides, __operation_declval<_Tp&>() / __operation_declval<_Tp&>());
CANN_ASC_STL_DETAIL_ACCL_DEFINE_BINARY_OPERATION(
    __has_modulo, __operation_declval<_Tp&>() % __operation_declval<_Tp&>());
CANN_ASC_STL_DETAIL_ACCL_DEFINE_BINARY_OPERATION(
    __has_bitwise_and, __operation_declval<_Tp&>() & __operation_declval<_Tp&>());
CANN_ASC_STL_DETAIL_ACCL_DEFINE_BINARY_OPERATION(
    __has_bitwise_or, __operation_declval<_Tp&>() | __operation_declval<_Tp&>());
CANN_ASC_STL_DETAIL_ACCL_DEFINE_BINARY_OPERATION(
    __has_bitwise_xor, __operation_declval<_Tp&>() ^ __operation_declval<_Tp&>());
CANN_ASC_STL_DETAIL_ACCL_DEFINE_BINARY_OPERATION(
    __has_shift_left, __operation_declval<_Tp&>() << __operation_declval<_Tp&>());
CANN_ASC_STL_DETAIL_ACCL_DEFINE_BINARY_OPERATION(
    __has_shift_right, __operation_declval<_Tp&>() >> __operation_declval<_Tp&>());
CANN_ASC_STL_DETAIL_ACCL_DEFINE_UNARY_OPERATION(__has_shift_left_size, __operation_declval<_Tp&>() << ptrdiff_t{});
CANN_ASC_STL_DETAIL_ACCL_DEFINE_UNARY_OPERATION(__has_shift_right_size, __operation_declval<_Tp&>() >> ptrdiff_t{});

// comparison operator constraints

CANN_ASC_STL_DETAIL_ACCL_DEFINE_BINARY_OPERATION(
    __has_equal_to, __operation_declval<_Tp&>() == __operation_declval<_Tp&>());
CANN_ASC_STL_DETAIL_ACCL_DEFINE_BINARY_OPERATION(
    __has_not_equal_to, __operation_declval<_Tp&>() != __operation_declval<_Tp&>());
CANN_ASC_STL_DETAIL_ACCL_DEFINE_BINARY_OPERATION(
    __has_greater_equal, __operation_declval<_Tp&>() >= __operation_declval<_Tp&>());
CANN_ASC_STL_DETAIL_ACCL_DEFINE_BINARY_OPERATION(
    __has_less_equal, __operation_declval<_Tp&>() <= __operation_declval<_Tp&>());
CANN_ASC_STL_DETAIL_ACCL_DEFINE_BINARY_OPERATION(
    __has_greater, __operation_declval<_Tp&>() > __operation_declval<_Tp&>());
CANN_ASC_STL_DETAIL_ACCL_DEFINE_BINARY_OPERATION(__has_less, __operation_declval<_Tp&>() < __operation_declval<_Tp&>());

#undef CANN_ASC_STL_DETAIL_ACCL_DEFINE_BINARY_OPERATION
#undef CANN_ASC_STL_DETAIL_ACCL_DEFINE_UNARY_OPERATION

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_OPERATIONS_H
