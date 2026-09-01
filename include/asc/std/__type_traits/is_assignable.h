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

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_void.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <typename, typename _Tp>
struct __select_2nd {
    using type = _Tp;
};

#if defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_ASSIGNABLE) && !defined(CANN_ASC_STL_DETAIL_USE_IS_ASSIGNABLE_FALLBACK)

template <class _T1, class _T2>
struct is_assignable : public integral_constant<bool, CANN_ASC_STL_DETAIL_BUILTIN_IS_ASSIGNABLE(_T1, _T2)> {};

template <class _T1, class _T2>
inline constexpr bool is_assignable_v = CANN_ASC_STL_DETAIL_BUILTIN_IS_ASSIGNABLE(_T1, _T2);

#else

template <class _Tp, class _Arg>
CANN_ASC_STL_API
    typename __select_2nd<decltype((::asc::std::declval<_Tp>() = ::asc::std::declval<_Arg>())), true_type>::type
    __is_assignable_test(int);

template <class, class>
CANN_ASC_STL_API false_type __is_assignable_test(...);

template <class _Tp, class _Arg, bool = is_void_v<_Tp> || is_void_v<_Arg> >
struct __is_assignable_imp : public decltype((::asc::std::__is_assignable_test<_Tp, _Arg>(0))) {};

template <class _Tp, class _Arg>
struct __is_assignable_imp<_Tp, _Arg, true> : public false_type {};

template <class _Tp, class _Arg>
struct is_assignable : public __is_assignable_imp<_Tp, _Arg> {};

template <class _Tp, class _Arg>
inline constexpr bool is_assignable_v = is_assignable<_Tp, _Arg>::value;

#endif  // defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_ASSIGNABLE) &&
        // !defined(CANN_ASC_STL_DETAIL_USE_IS_ASSIGNABLE_FALLBACK)

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_ASSIGNABLE_H
