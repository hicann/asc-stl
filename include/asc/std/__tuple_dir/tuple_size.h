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

#ifndef CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_SIZE_H
#define CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_SIZE_H

#include <asc/std/detail/__config>

#include <asc/std/__cstddef/types.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_const.h>
#include <asc/std/__type_traits/is_volatile.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp>
struct tuple_size;

template <class _Tp, class...>
using __enable_if_tuple_size_imp = _Tp;

template <class _Tp>
struct tuple_size<__enable_if_tuple_size_imp<const _Tp, enable_if_t<!is_volatile_v<_Tp>>,
    integral_constant<size_t, sizeof(tuple_size<_Tp>)>>> : integral_constant<size_t, tuple_size<_Tp>::value> {};

template <class _Tp>
struct tuple_size<__enable_if_tuple_size_imp<volatile _Tp, enable_if_t<!is_const_v<_Tp>>,
    integral_constant<size_t, sizeof(tuple_size<_Tp>)>>> : integral_constant<size_t, tuple_size<_Tp>::value> {};

template <class _Tp>
struct tuple_size<__enable_if_tuple_size_imp<const volatile _Tp, integral_constant<size_t, sizeof(tuple_size<_Tp>)>>>
    : integral_constant<size_t, tuple_size<_Tp>::value> {};

template <class _Tp>
inline constexpr size_t tuple_size_v = tuple_size<_Tp>::value;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_STD

template <class _Tp>
struct tuple_size;

#if CANN_ASC_STL_DETAIL_FREESTANDING() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

template <class _Tp>
struct tuple_size<asc::std::__enable_if_tuple_size_imp<const _Tp, asc::std::enable_if_t<!asc::std::is_volatile_v<_Tp>>,
    asc::std::integral_constant<asc::std::size_t, sizeof(tuple_size<_Tp>)>>>
    : asc::std::integral_constant<asc::std::size_t, tuple_size<_Tp>::value> {};

template <class _Tp>
struct tuple_size<asc::std::__enable_if_tuple_size_imp<volatile _Tp, asc::std::enable_if_t<!asc::std::is_const_v<_Tp>>,
    asc::std::integral_constant<asc::std::size_t, sizeof(tuple_size<_Tp>)>>>
    : asc::std::integral_constant<asc::std::size_t, tuple_size<_Tp>::value> {};

template <class _Tp>
struct tuple_size<asc::std::__enable_if_tuple_size_imp<const volatile _Tp,
    asc::std::integral_constant<asc::std::size_t, sizeof(tuple_size<_Tp>)>>>
    : asc::std::integral_constant<asc::std::size_t, tuple_size<_Tp>::value> {};
#endif  // CANN_ASC_STL_DETAIL_FREESTANDING() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_SIZE_H
