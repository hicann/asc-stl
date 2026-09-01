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
#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_REFERENCE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_REFERENCE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/integral_constant.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class>
inline constexpr bool is_lvalue_reference_v = false;
template <class T>
inline constexpr bool is_lvalue_reference_v<T&> = true;
template <class T>
struct is_lvalue_reference : bool_constant<is_lvalue_reference_v<T>> {};
template <class>
inline constexpr bool is_rvalue_reference_v = false;
template <class T>
inline constexpr bool is_rvalue_reference_v<T&&> = true;
template <class T>
struct is_rvalue_reference : bool_constant<is_rvalue_reference_v<T>> {};
template <class T>
inline constexpr bool is_reference_v = is_lvalue_reference_v<T> || is_rvalue_reference_v<T>;
template <class T>
struct is_reference : bool_constant<is_reference_v<T>> {};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_REFERENCE_H
