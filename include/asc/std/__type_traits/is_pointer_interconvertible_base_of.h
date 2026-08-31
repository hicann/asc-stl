/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_POINTER_INTERCONVERTIBLE_BASE_OF_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_POINTER_INTERCONVERTIBLE_BASE_OF_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_class.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_POINTER_INTERCONVERTIBLE_BASE_OF)

template <class _Tp, class _Up>
inline constexpr bool is_pointer_interconvertible_base_of_v =
    CANN_ASC_STL_DETAIL_BUILTIN_IS_POINTER_INTERCONVERTIBLE_BASE_OF(_Tp, _Up);

#if CANN_ASC_STL_DETAIL_COMPILER(CLANG)
// clang's builtin evaluates is_pointer_interconvertible_base_of_v<T, T> to be false which is not right
template <class _Tp>
inline constexpr bool is_pointer_interconvertible_base_of_v<_Tp, _Tp> = is_class_v<_Tp>;
template <class _Tp>
inline constexpr bool is_pointer_interconvertible_base_of_v<_Tp, const _Tp> = is_class_v<_Tp>;
template <class _Tp>
inline constexpr bool is_pointer_interconvertible_base_of_v<_Tp, volatile _Tp> = is_class_v<_Tp>;
template <class _Tp>
inline constexpr bool is_pointer_interconvertible_base_of_v<_Tp, const volatile _Tp> = is_class_v<_Tp>;
template <class _Tp>
inline constexpr bool is_pointer_interconvertible_base_of_v<const _Tp, _Tp> = is_class_v<_Tp>;
template <class _Tp>
inline constexpr bool is_pointer_interconvertible_base_of_v<const _Tp, const _Tp> = is_class_v<_Tp>;
template <class _Tp>
inline constexpr bool is_pointer_interconvertible_base_of_v<const _Tp, volatile _Tp> = is_class_v<_Tp>;
template <class _Tp>
inline constexpr bool is_pointer_interconvertible_base_of_v<const _Tp, const volatile _Tp> = is_class_v<_Tp>;
template <class _Tp>
inline constexpr bool is_pointer_interconvertible_base_of_v<volatile _Tp, _Tp> = is_class_v<_Tp>;
template <class _Tp>
inline constexpr bool is_pointer_interconvertible_base_of_v<volatile _Tp, const _Tp> = is_class_v<_Tp>;
template <class _Tp>
inline constexpr bool is_pointer_interconvertible_base_of_v<volatile _Tp, volatile _Tp> = is_class_v<_Tp>;
template <class _Tp>
inline constexpr bool is_pointer_interconvertible_base_of_v<volatile _Tp, const volatile _Tp> = is_class_v<_Tp>;
template <class _Tp>
inline constexpr bool is_pointer_interconvertible_base_of_v<const volatile _Tp, _Tp> = is_class_v<_Tp>;
template <class _Tp>
inline constexpr bool is_pointer_interconvertible_base_of_v<const volatile _Tp, const _Tp> = is_class_v<_Tp>;
template <class _Tp>
inline constexpr bool is_pointer_interconvertible_base_of_v<const volatile _Tp, volatile _Tp> = is_class_v<_Tp>;
template <class _Tp>
inline constexpr bool is_pointer_interconvertible_base_of_v<const volatile _Tp, const volatile _Tp> = is_class_v<_Tp>;
#endif  // CANN_ASC_STL_DETAIL_COMPILER(CLANG)

template <class _Tp, class _Up>
struct is_pointer_interconvertible_base_of : bool_constant<is_pointer_interconvertible_base_of_v<_Tp, _Up>> {};

#endif  // CANN_ASC_STL_DETAIL_BUILTIN_IS_POINTER_INTERCONVERTIBLE_BASE_OF

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_POINTER_INTERCONVERTIBLE_BASE_OF_H
