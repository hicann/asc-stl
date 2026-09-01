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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_NOTHROW_CONSTRUCTIBLE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_NOTHROW_CONSTRUCTIBLE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_scalar.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_NOTHROW_CONSTRUCTIBLE) && \
    !defined(CANN_ASC_STL_DETAIL_USE_IS_NOTHROW_CONSTRUCTIBLE_FALLBACK)

template <class _Tp, class... _Args>
struct is_nothrow_constructible
    : integral_constant<bool, CANN_ASC_STL_DETAIL_BUILTIN_IS_NOTHROW_CONSTRUCTIBLE(_Tp, _Args...)> {};

template <class _Tp, class... _Args>
inline constexpr bool is_nothrow_constructible_v = CANN_ASC_STL_DETAIL_BUILTIN_IS_NOTHROW_CONSTRUCTIBLE(_Tp, _Args...);

#else

template <bool, class _Tp, class... _Args>
inline constexpr bool __accl_is_nothrow_constructible = false;

template <class _Tp, class... _Args>
inline constexpr bool __accl_is_nothrow_constructible<true, _Tp, _Args...> = noexcept(_Tp(declval<_Args>()...));

template <class _Tp, class _Arg>
inline constexpr bool __accl_is_nothrow_constructible<true, _Tp, _Arg> = noexcept(static_cast<_Tp>(declval<_Arg>()));

template <class _Tp, size_t _Size>
inline constexpr bool __accl_is_nothrow_constructible<true, _Tp[_Size]> = __accl_is_nothrow_constructible<true, _Tp>;

template <class _Tp, class... _Args>
inline constexpr bool is_nothrow_constructible_v =
    __accl_is_nothrow_constructible<is_constructible_v<_Tp, _Args...>, _Tp, _Args...>;

template <class _Tp, class... _Args>
struct is_nothrow_constructible : bool_constant<is_nothrow_constructible_v<_Tp, _Args...> > {};

#endif

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_NOTHROW_CONSTRUCTIBLE_H
