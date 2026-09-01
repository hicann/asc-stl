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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_NOTHROW_DESTRUCTIBLE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_NOTHROW_DESTRUCTIBLE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_destructible.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/is_scalar.h>
#include <asc/std/__type_traits/remove_all_extents.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/cstddef>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

// is_nothrow_destructible

#if defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_NOTHROW_DESTRUCTIBLE) && \
    !defined(CANN_ASC_STL_DETAIL_USE_IS_NOTHROW_DESTRUCTIBLE_FALLBACK)

template <class _Tp>
struct is_nothrow_destructible
    : public integral_constant<bool, CANN_ASC_STL_DETAIL_BUILTIN_IS_NOTHROW_DESTRUCTIBLE(_Tp)> {};

template <class _Tp>
inline constexpr bool is_nothrow_destructible_v = CANN_ASC_STL_DETAIL_BUILTIN_IS_NOTHROW_DESTRUCTIBLE(_Tp);

#else  // ^^^ CANN_ASC_STL_DETAIL_BUILTIN_IS_NOTHROW_DESTRUCTIBLE ^^^ / vvv
       // !CANN_ASC_STL_DETAIL_BUILTIN_IS_NOTHROW_DESTRUCTIBLE vvv

template <class _Tp, bool = is_destructible<_Tp>::value>
struct __asc_is_nothrow_destructible : false_type {};

template <class _Tp>
struct __asc_is_nothrow_destructible<_Tp, true>
    : public integral_constant<bool, noexcept(::asc::std::declval<_Tp>().~_Tp())> {};

template <class _Tp>
struct is_nothrow_destructible : public __asc_is_nothrow_destructible<_Tp> {};

template <class _Tp, size_t _Ns>
struct is_nothrow_destructible<_Tp[_Ns]> : public is_nothrow_destructible<_Tp> {};

template <class _Tp>
struct is_nothrow_destructible<_Tp&> : public true_type {};

template <class _Tp>
struct is_nothrow_destructible<_Tp&&> : public true_type {};

template <class _Tp>
inline constexpr bool is_nothrow_destructible_v = is_nothrow_destructible<_Tp>::value;

#endif  // !CANN_ASC_STL_DETAIL_BUILTIN_IS_NOTHROW_DESTRUCTIBLE

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_NOTHROW_DESTRUCTIBLE_H
