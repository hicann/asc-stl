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
#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_ASSIGNABLE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_ASSIGNABLE_H

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
#include <asc/std/__type_traits/is_void.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <typename, typename T>
struct __select_2nd {
    using type = T;
};

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__is_assignable)

template <class T1, class T2>
struct is_assignable : integral_constant<bool, __is_assignable(T1, T2)> {};

template <class T1, class T2>
inline constexpr bool is_assignable_v = __is_assignable(T1, T2);

#else

// The upstream catch-all __is_assignable_test(...) probe is not portable to
// CCE aicore, so the negative overload takes long: the int overload still
// wins exactly for viable argument pairs and the conversion fallback covers
// the rest.
template <class Tp, class Arg>
CANN_ASC_STL_API typename __select_2nd<decltype((asc::std::declval<Tp>() = asc::std::declval<Arg>())), true_type>::type
__is_assignable_test(int);

template <class, class>
CANN_ASC_STL_API false_type __is_assignable_test(long);

template <class Tp, class Arg, bool = is_void_v<Tp> || is_void_v<Arg> >
struct __is_assignable_imp : decltype((asc::std::__is_assignable_test<Tp, Arg>(0))) {};

template <class Tp, class Arg>
struct __is_assignable_imp<Tp, Arg, true> : false_type {};

template <class Tp, class Arg>
struct is_assignable : __is_assignable_imp<Tp, Arg> {};

template <class Tp, class Arg>
inline constexpr bool is_assignable_v = is_assignable<Tp, Arg>::value;

#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_ASSIGNABLE_H
