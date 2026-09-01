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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_NOTHROW_ASSIGNABLE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_NOTHROW_ASSIGNABLE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_assignable.h>
#include <asc/std/__type_traits/is_scalar.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_NOTHROW_ASSIGNABLE) && \
    !defined(CANN_ASC_STL_DETAIL_USE_IS_NOTHROW_ASSIGNABLE_FALLBACK)

template <class _Tp, class _Arg>
struct is_nothrow_assignable
    : public integral_constant<bool, CANN_ASC_STL_DETAIL_BUILTIN_IS_NOTHROW_ASSIGNABLE(_Tp, _Arg)> {};

template <class _Tp, class _Arg>
inline constexpr bool is_nothrow_assignable_v = CANN_ASC_STL_DETAIL_BUILTIN_IS_NOTHROW_ASSIGNABLE(_Tp, _Arg);

#else  // ^^^ CANN_ASC_STL_DETAIL_BUILTIN_IS_NOTHROW_ASSIGNABLE ^^^ / vvv
       // !CANN_ASC_STL_DETAIL_BUILTIN_IS_NOTHROW_ASSIGNABLE vvv

template <bool, class _Tp, class _Arg>
struct __asc_is_nothrow_assignable;

template <class _Tp, class _Arg>
struct __asc_is_nothrow_assignable<false, _Tp, _Arg> : public false_type {};

template <class _Tp, class _Arg>
struct __asc_is_nothrow_assignable<true, _Tp, _Arg>
    : public integral_constant<bool, noexcept(::asc::std::declval<_Tp>() = ::asc::std::declval<_Arg>())> {};

template <class _Tp, class _Arg>
struct is_nothrow_assignable : public __asc_is_nothrow_assignable<is_assignable_v<_Tp, _Arg>, _Tp, _Arg> {};

template <class _Tp, class _Arg>
inline constexpr bool is_nothrow_assignable_v = is_nothrow_assignable<_Tp, _Arg>::value;

#endif  // !CANN_ASC_STL_DETAIL_BUILTIN_IS_NOTHROW_ASSIGNABLE

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_NOTHROW_ASSIGNABLE_H
