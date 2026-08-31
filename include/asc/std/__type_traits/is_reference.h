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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_REFERENCE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_REFERENCE_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/integral_constant.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_LVALUE_REFERENCE) &&            \
    !defined(CANN_ASC_STL_DETAIL_ACCL_USE_IS_LVALUE_REFERENCE_FALLBACK) && \
    defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_RVALUE_REFERENCE) &&            \
    !defined(CANN_ASC_STL_DETAIL_ACCL_USE_IS_RVALUE_REFERENCE_FALLBACK) && \
    defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_REFERENCE) && !defined(CANN_ASC_STL_DETAIL_ACCL_USE_IS_REFERENCE_FALLBACK)

template <class _Tp>
struct is_lvalue_reference : bool_constant<CANN_ASC_STL_DETAIL_BUILTIN_IS_LVALUE_REFERENCE(_Tp)> {};

template <class _Tp>
struct is_rvalue_reference : bool_constant<CANN_ASC_STL_DETAIL_BUILTIN_IS_RVALUE_REFERENCE(_Tp)> {};

template <class _Tp>
struct is_reference : bool_constant<CANN_ASC_STL_DETAIL_BUILTIN_IS_REFERENCE(_Tp)> {};

template <class _Tp>
inline constexpr bool is_lvalue_reference_v = CANN_ASC_STL_DETAIL_BUILTIN_IS_LVALUE_REFERENCE(_Tp);
template <class _Tp>
inline constexpr bool is_rvalue_reference_v = CANN_ASC_STL_DETAIL_BUILTIN_IS_RVALUE_REFERENCE(_Tp);
template <class _Tp>
inline constexpr bool is_reference_v = CANN_ASC_STL_DETAIL_BUILTIN_IS_REFERENCE(_Tp);

#else

template <class _Tp>
inline constexpr bool is_lvalue_reference_v = false;
template <class _Tp>
inline constexpr bool is_lvalue_reference_v<_Tp&> = true;

template <class _Tp>
struct is_lvalue_reference : bool_constant<is_lvalue_reference_v<_Tp> > {};

template <class _Tp>
inline constexpr bool is_rvalue_reference_v = false;
template <class _Tp>
inline constexpr bool is_rvalue_reference_v<_Tp&&> = true;

template <class _Tp>
struct is_rvalue_reference : bool_constant<is_rvalue_reference_v<_Tp> > {};

template <class _Tp>
inline constexpr bool is_reference_v = false;
template <class _Tp>
inline constexpr bool is_reference_v<_Tp&> = true;
template <class _Tp>
inline constexpr bool is_reference_v<_Tp&&> = true;

template <class _Tp>
struct is_reference : bool_constant<is_reference_v<_Tp> > {};

#endif  // !CANN_ASC_STL_DETAIL_BUILTIN_IS_LVALUE_REFERENCE

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_REFERENCE_H
