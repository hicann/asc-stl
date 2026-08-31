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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_COMPLETE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_COMPLETE_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/void_t.h>  // IWYU pragma: keep

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#ifdef CANN_ASC_STL_DETAIL_BUILTIN_IS_COMPLETE_TYPE

template <typename T>
inline constexpr bool __is_complete_v = CANN_ASC_STL_DETAIL_BUILTIN_IS_COMPLETE_TYPE(T);

#else   // ^^^  CANN_ASC_STL_DETAIL_BUILTIN_IS_COMPLETE_TYPE ^^^ / vvv no builtin vvv
// Must be a SFINAE trait instead of
//
// template <typename T>
// inline constexpr __is_complete_v = sizeof(T) > 0;
//
// Because some compilers don't even allow you to utter the phrase sizeof(T) if T is incomplete
template <typename T, typename = void>
inline constexpr bool __is_complete_v = false;

template <typename T>
inline constexpr bool __is_complete_v<T, void_t<decltype(sizeof(T))> > = (sizeof(T) > 0);
#endif  // ^^^ no builtin ^^^

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_COMPLETE_H
