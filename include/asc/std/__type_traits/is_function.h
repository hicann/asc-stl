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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_FUNCTION_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_FUNCTION_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_const.h>
#include <asc/std/__type_traits/is_reference.h>

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(is_function)
#define CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_FUNCTION(...) __is_function(__VA_ARGS__)
#endif  // CANN_ASC_STL_DETAIL_CHECK_BUILTIN(is_function)

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if defined(CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_FUNCTION)

template <class _Tp>
struct is_function : bool_constant<CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_FUNCTION(_Tp)> {};

template <class _Tp>
inline constexpr bool is_function_v = CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_FUNCTION(_Tp);

#else  // ^^^ CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_FUNCTION ^^^ / vvv !CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_FUNCTION vvv

CANN_ASC_STL_DETAIL_DIAG_PUSH
CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_MSVC(4180)  // qualifier applied to function type has no meaning; ignored

template <class _Tp>
struct is_function : bool_constant<!(is_reference_v<_Tp> || is_const_v<const _Tp>)> {};

template <class _Tp>
inline constexpr bool is_function_v = !(is_reference_v<_Tp> || is_const_v<const _Tp>);

CANN_ASC_STL_DETAIL_DIAG_POP

#endif  // ^^^ !CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_FUNCTION ^^^

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_FUNCTION_H
