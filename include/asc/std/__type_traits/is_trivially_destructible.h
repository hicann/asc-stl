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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_destructible.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_TRIVIALLY_DESTRUCTIBLE)

template <class _Tp>
inline constexpr bool is_trivially_destructible_v = CANN_ASC_STL_DETAIL_BUILTIN_IS_TRIVIALLY_DESTRUCTIBLE(_Tp);

#elif defined(CANN_ASC_STL_DETAIL_BUILTIN_HAS_TRIVIAL_DESTRUCTOR)

template <class _Tp>
inline constexpr bool is_trivially_destructible_v =
    is_destructible_v<_Tp> && CANN_ASC_STL_DETAIL_BUILTIN_HAS_TRIVIAL_DESTRUCTOR(_Tp);

#else
#error "ASC-STL requires a compiler builtin for is_trivially_destructible"
#endif

template <class _Tp>
struct is_trivially_destructible : bool_constant<is_trivially_destructible_v<_Tp>> {};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_H
