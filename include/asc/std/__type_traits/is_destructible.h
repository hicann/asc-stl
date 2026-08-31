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

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_function.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/remove_all_extents.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_DESTRUCTIBLE) && \
    !defined(CANN_ASC_STL_DETAIL_ACCL_USE_IS_DESTRUCTIBLE_FALLBACK)

template <class _Tp>
struct is_destructible : integral_constant<bool, CANN_ASC_STL_DETAIL_BUILTIN_IS_DESTRUCTIBLE(_Tp)> {};

template <class _Tp>
inline constexpr bool is_destructible_v = CANN_ASC_STL_DETAIL_BUILTIN_IS_DESTRUCTIBLE(_Tp);

#else

template <class>
struct __is_destructible_apply {
    using type = int;
};

template <class _Tp, class = void>
struct __is_destructor_wellformed : false_type {};

template <class _Tp>
struct __is_destructor_wellformed<_Tp, void_t<decltype(declval<_Tp&>().~_Tp())> > : true_type {};

template <class _Tp, bool>
struct __destructible_imp;

template <class _Tp>
struct __destructible_imp<_Tp, false>
    : integral_constant<bool, __is_destructor_wellformed<remove_all_extents_t<_Tp> >::value> {};

template <class _Tp>
struct __destructible_imp<_Tp, true> : true_type {};

template <class _Tp, bool>
struct __destructible_false;

template <class _Tp>
struct __destructible_false<_Tp, false> : __destructible_imp<_Tp, is_reference<_Tp>::value> {};

template <class _Tp>
struct __destructible_false<_Tp, true> : false_type {};

template <class _Tp>
struct is_destructible : __destructible_false<_Tp, is_function<_Tp>::value> {};

template <class _Tp>
struct is_destructible<_Tp[]> : false_type {};

template <>
struct is_destructible<void> : false_type {};

template <class _Tp>
inline constexpr bool is_destructible_v = is_destructible<_Tp>::value;

#endif

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_DESTRUCTIBLE_H
