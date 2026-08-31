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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_FUNDAMENTAL_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_FUNDAMENTAL_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_arithmetic.h>
#include <asc/std/__type_traits/is_null_pointer.h>
#include <asc/std/__type_traits/is_void.h>

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(is_fundamental)
#define CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_FUNDAMENTAL(...) __is_fundamental(__VA_ARGS__)
#endif  // CANN_ASC_STL_DETAIL_CHECK_BUILTIN(is_fundamental)

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if defined(CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_FUNDAMENTAL)

template <class _Tp>
struct is_fundamental : bool_constant<CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_FUNDAMENTAL(_Tp)> {};

template <class _Tp>
inline constexpr bool is_fundamental_v = CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_FUNDAMENTAL(_Tp);

#else  // ^^^ CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_FUNDAMENTAL ^^^ / vvv !CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_FUNDAMENTAL
       // vvv

template <class _Tp>
inline constexpr bool is_fundamental_v = is_void_v<_Tp> || is_null_pointer_v<_Tp> || is_arithmetic_v<_Tp>;

template <class _Tp>
struct is_fundamental : bool_constant<is_fundamental_v<_Tp> > {};

#endif  // !CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_FUNDAMENTAL

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_FUNDAMENTAL_H
