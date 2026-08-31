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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_SCALAR_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_SCALAR_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_arithmetic.h>
#include <asc/std/__type_traits/is_enum.h>
#include <asc/std/__type_traits/is_member_pointer.h>
#include <asc/std/__type_traits/is_null_pointer.h>
#include <asc/std/__type_traits/is_pointer.h>
#include <asc/std/cstddef>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if defined(CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_SCALAR) && !defined(CANN_ASC_STL_DETAIL_ACCL_USE_IS_SCALAR_FALLBACK)

template <class _Tp>
struct is_scalar : bool_constant<CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_SCALAR(_Tp)> {};

template <class _Tp>
inline constexpr bool is_scalar_v = CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_SCALAR(_Tp);

#else

template <class _Tp>
inline constexpr bool is_scalar_v =
    is_arithmetic_v<_Tp> || is_member_pointer_v<_Tp> || is_pointer_v<_Tp> || is_null_pointer_v<_Tp> || is_enum_v<_Tp>;

template <class _Tp>
struct is_scalar : bool_constant<is_scalar_v<_Tp> > {};

#endif

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_SCALAR_H
