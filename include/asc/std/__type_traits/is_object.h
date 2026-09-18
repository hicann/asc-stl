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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_OBJECT_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_OBJECT_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_array.h>
#include <asc/std/__type_traits/is_class.h>
#include <asc/std/__type_traits/is_scalar.h>
#include <asc/std/__type_traits/is_union.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_OBJECT) && !defined(CANN_ASC_STL_DETAIL_ACCL_USE_IS_OBJECT_FALLBACK)

template <class _Tp>
struct is_object : public bool_constant<CANN_ASC_STL_DETAIL_BUILTIN_IS_OBJECT(_Tp)> {};

template <class _Tp>
inline constexpr bool is_object_v = CANN_ASC_STL_DETAIL_BUILTIN_IS_OBJECT(_Tp);

#else

template <class _Tp>
inline constexpr bool is_object_v = is_scalar_v<_Tp> || is_array_v<_Tp> || is_union_v<_Tp> || is_class_v<_Tp>;

template <class _Tp>
struct is_object : public bool_constant<is_object_v<_Tp> > {};

#endif  // defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_OBJECT) && !defined(CANN_ASC_STL_DETAIL_ACCL_USE_IS_OBJECT_FALLBACK)

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_OBJECT_H
