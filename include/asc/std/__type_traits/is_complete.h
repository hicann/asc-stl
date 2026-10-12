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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_COMPLETE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_COMPLETE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/void_t.h>

#ifndef CANN_ASC_STL_DETAIL_BUILTIN_IS_COMPLETE_TYPE
#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__is_complete_type)
#define CANN_ASC_STL_DETAIL_BUILTIN_IS_COMPLETE_TYPE(...) __is_complete_type(__VA_ARGS__)
#endif
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

#ifdef CANN_ASC_STL_DETAIL_BUILTIN_IS_COMPLETE_TYPE

template <class T>
inline constexpr bool __is_complete_v = CANN_ASC_STL_DETAIL_BUILTIN_IS_COMPLETE_TYPE(T);

#else   // ^^^ builtin __is_complete_type ^^^ / vvv SFINAE fallback vvv
// Must be a SFINAE trait instead of
//
// template <class T>
// inline constexpr bool __is_complete_v = sizeof(T) > 0;
//
// Because some compilers don't even allow you to utter the phrase sizeof(T) if T is incomplete
template <class T, class = void>
inline constexpr bool __is_complete_v = false;

template <class T>
inline constexpr bool __is_complete_v<T, void_t<decltype(sizeof(T))> > = sizeof(T) > 0;
#endif  // ^^^ SFINAE fallback ^^^

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_COMPLETE_H
