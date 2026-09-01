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
#ifndef CANN_ASC_STL_STD_DETAIL_TUPLE_TUPLE_SIZE_H
#define CANN_ASC_STL_STD_DETAIL_TUPLE_TUPLE_SIZE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__cstddef/types.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_const.h>
#include <asc/std/__type_traits/is_volatile.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
struct tuple_size;

template <class T, class...>
using __enable_if_tuple_size_imp = T;

template <class T>
struct tuple_size<__enable_if_tuple_size_imp<const T, enable_if_t<!is_volatile_v<T>>,
    integral_constant<size_t, sizeof(tuple_size<T>)>>> : integral_constant<size_t, tuple_size<T>::value> {};

template <class T>
struct tuple_size<__enable_if_tuple_size_imp<volatile T, enable_if_t<!is_const_v<T>>,
    integral_constant<size_t, sizeof(tuple_size<T>)>>> : integral_constant<size_t, tuple_size<T>::value> {};

template <class T>
struct tuple_size<__enable_if_tuple_size_imp<const volatile T, integral_constant<size_t, sizeof(tuple_size<T>)>>>
    : integral_constant<size_t, tuple_size<T>::value> {};

template <class T>
inline constexpr size_t tuple_size_v = tuple_size<T>::value;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TUPLE_TUPLE_SIZE_H
