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
#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_NOTHROW_ASSIGNABLE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_NOTHROW_ASSIGNABLE_H

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
#include <asc/std/__type_traits/is_assignable.h>
#include <asc/std/__type_traits/is_scalar.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__is_nothrow_assignable)

template <class Tp, class Arg>
struct is_nothrow_assignable : integral_constant<bool, __is_nothrow_assignable(Tp, Arg)> {};

template <class Tp, class Arg>
inline constexpr bool is_nothrow_assignable_v = __is_nothrow_assignable(Tp, Arg);

#else

template <bool, class Tp, class Arg>
struct __asc_is_nothrow_assignable;
template <class Tp, class Arg>
struct __asc_is_nothrow_assignable<false, Tp, Arg> : public false_type {};
template <class Tp, class Arg>
struct __asc_is_nothrow_assignable<true, Tp, Arg>
    : public integral_constant<bool, noexcept(asc::std::declval<Tp>() = asc::std::declval<Arg>())> {};

template <class Tp, class Arg>
struct is_nothrow_assignable : public __asc_is_nothrow_assignable<is_assignable_v<Tp, Arg>, Tp, Arg> {};

template <class Tp, class Arg>
inline constexpr bool is_nothrow_assignable_v = is_nothrow_assignable<Tp, Arg>::value;

#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_NOTHROW_ASSIGNABLE_H
