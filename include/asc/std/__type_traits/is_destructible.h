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
#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_DESTRUCTIBLE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_DESTRUCTIBLE_H

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
#include <asc/std/__type_traits/is_function.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/remove_all_extents.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__is_destructible)

template <class T>
struct is_destructible : integral_constant<bool, __is_destructible(T)> {};

template <class T>
inline constexpr bool is_destructible_v = __is_destructible(T);

#else

//  if it's a reference, return true
//  if it's a function, return false
//  if it's   void,     return false
//  if it's an array of unknown bound, return false
//  Otherwise, return "declval<Up&>().~Up()" is well-formed
//    where Up is remove_all_extents<T>::type
//
// The upstream catch-all __test(...) probe is not portable to CCE aicore,
// so the well-formedness check is a partial specialization over a local
// void alias (the __type_traits/promote.h detection pattern).
template <class...>
using __destructible_void_t = void;

template <class T, class = void>
struct __is_destructor_wellformed {
    static const bool value = false;
};

template <class T>
struct __is_destructor_wellformed<T, __destructible_void_t<decltype(asc::std::declval<T&>().~T())> > {
    static const bool value = true;
};

template <class T, bool>
struct __destructible_imp;

template <class T>
struct __destructible_imp<T, false>
    : integral_constant<bool, __is_destructor_wellformed<remove_all_extents_t<T> >::value> {};

template <class T>
struct __destructible_imp<T, true> : true_type {};

template <class T, bool>
struct __destructible_false;

template <class T>
struct __destructible_false<T, false> : __destructible_imp<T, is_reference<T>::value> {};

template <class T>
struct __destructible_false<T, true> : false_type {};

template <class T>
struct is_destructible : __destructible_false<T, is_function<T>::value> {};

template <class T>
struct is_destructible<T[]> : false_type {};

template <>
struct is_destructible<void> : false_type {};

template <class T>
inline constexpr bool is_destructible_v = is_destructible<T>::value;

#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_DESTRUCTIBLE_H
