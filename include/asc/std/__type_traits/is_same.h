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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_SAME_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_SAME_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/integral_constant.h>

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__is_same_as) || CANN_ASC_STL_DETAIL_COMPILER(GCC)
#define CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_SAME_AS(...) __is_same_as(__VA_ARGS__)
#endif  // CANN_ASC_STL_DETAIL_HAS_BUILTIN(__is_same_as) || CANN_ASC_STL_DETAIL_COMPILER(GCC)

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if defined(CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_SAME_AS)

template <class _Tp, class _Up>
struct is_same : bool_constant<CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_SAME_AS(_Tp, _Up)> {};

template <class _Tp, class _Up>
inline constexpr bool is_same_v = CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_SAME_AS(_Tp, _Up);

// _IsSame<T,U> has the same effect as is_same<T,U> but instantiates fewer types:
// is_same<A,B> and is_same<C,D> are guaranteed to be different types, but
// _IsSame<A,B> and _IsSame<C,D> are the same type (namely, false_type).
// Neither GCC nor Clang can mangle the __is_same builtin, so _IsSame
// mustn't be directly used anywhere that contributes to name-mangling
// (such as in a dependent return type).

template <class _Tp, class _Up>
using _IsSame = bool_constant<CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_SAME_AS(_Tp, _Up)>;

template <class _Tp, class _Up>
using _IsNotSame = bool_constant<!CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_SAME_AS(_Tp, _Up)>;

#else  // ^^^ CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_SAME_AS ^^^ / vvv !CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_SAME_AS vvv

template <class _Tp, class _Up>
struct is_same : false_type {};
template <class _Tp>
struct is_same<_Tp, _Tp> : true_type {};

template <class _Tp, class _Up>
inline constexpr bool is_same_v = false;
template <class _Tp>
inline constexpr bool is_same_v<_Tp, _Tp> = true;

// _IsSame<T,U> has the same effect as is_same<T,U> but instantiates fewer types:
// is_same<A,B> and is_same<C,D> are guaranteed to be different types, but
// _IsSame<A,B> and _IsSame<C,D> are the same type (namely, false_type).
// Neither GCC nor Clang can mangle the __is_same builtin, so _IsSame
// mustn't be directly used anywhere that contributes to name-mangling
// (such as in a dependent return type).

template <class _Tp, class _Up>
using _IsSame = bool_constant<is_same_v<_Tp, _Up> >;

template <class _Tp, class _Up>
using _IsNotSame = bool_constant<!is_same_v<_Tp, _Up> >;

#endif  // ^^^ !CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_SAME_AS ^^^

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_SAME_H
