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

#ifndef CANN_ASC_STL_DETAIL_TYPE_TRAITS_IS_INSTANTIABLE_WITH_H
#define CANN_ASC_STL_DETAIL_TYPE_TRAITS_IS_INSTANTIABLE_WITH_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/is_valid_expansion.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

template <template <class...> class _Fn, class... _Ts>
concept __is_instantiable_with = requires { typename _Fn<_Ts...>; };

#else  // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv

template <template <class...> class _Fn, class... _Ts>
inline constexpr bool __is_instantiable_with = ::asc::std::_IsValidExpansion<_Fn, _Ts...>::value;

#endif  // ^^^ !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_TYPE_TRAITS_IS_INSTANTIABLE_WITH_H
