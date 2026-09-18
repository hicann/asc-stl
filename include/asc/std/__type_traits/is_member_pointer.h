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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_MEMBER_POINTER_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_MEMBER_POINTER_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_member_function_pointer.h>
#include <asc/std/__type_traits/remove_cv.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_MEMBER_POINTER) && \
    !defined(CANN_ASC_STL_DETAIL_ACCL_USE_IS_MEMBER_POINTER_FALLBACK)

template <class _Tp>
struct is_member_pointer : integral_constant<bool, CANN_ASC_STL_DETAIL_BUILTIN_IS_MEMBER_POINTER(_Tp)> {};

template <class _Tp>
inline constexpr bool is_member_pointer_v = CANN_ASC_STL_DETAIL_BUILTIN_IS_MEMBER_POINTER(_Tp);

#else

template <class _Tp>
struct is_member_pointer : integral_constant<bool, __accl_is_member_pointer<remove_cv_t<_Tp> >::__is_member> {};

template <class _Tp>
inline constexpr bool is_member_pointer_v = is_member_pointer<_Tp>::value;

#endif

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_MEMBER_POINTER_H
