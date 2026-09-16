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
#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_NOTHROW_CONSTRUCTIBLE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_NOTHROW_CONSTRUCTIBLE_H

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
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_scalar.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__is_nothrow_constructible)

template <class Tp, class... Args>
struct is_nothrow_constructible : integral_constant<bool, __is_nothrow_constructible(Tp, Args...)> {};

template <class Tp, class... Args>
inline constexpr bool is_nothrow_constructible_v = __is_nothrow_constructible(Tp, Args...);

#else

template <bool, class Tp, class... Args>
inline constexpr bool __asc_is_nothrow_constructible = false;
template <class Tp, class... Args>
inline constexpr bool __asc_is_nothrow_constructible<true, Tp, Args...> = noexcept(Tp(asc::std::declval<Args>()...));
template <class Tp, class Arg>
inline constexpr bool __asc_is_nothrow_constructible<true, Tp, Arg> =
    noexcept(static_cast<Tp>(asc::std::declval<Arg>()));
template <class Tp, size_t Ns>
inline constexpr bool __asc_is_nothrow_constructible<true, Tp[Ns]> = __asc_is_nothrow_constructible<true, Tp>;

template <class Tp, class... Args>
inline constexpr bool is_nothrow_constructible_v =
    __asc_is_nothrow_constructible<is_constructible_v<Tp, Args...>, Tp, Args...>;

template <class Tp, class... Args>
struct is_nothrow_constructible : bool_constant<is_nothrow_constructible_v<Tp, Args...> > {};

#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_NOTHROW_CONSTRUCTIBLE_H
