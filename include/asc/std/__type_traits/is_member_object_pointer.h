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
#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_MEMBER_OBJECT_POINTER_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_MEMBER_OBJECT_POINTER_H

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
#include <asc/std/__type_traits/is_member_function_pointer.h>
#include <asc/std/__type_traits/remove_cv.h>

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__is_member_object_pointer)

template <class T>
struct is_member_object_pointer : integral_constant<bool, __is_member_object_pointer(T)> {};

template <class T>
inline constexpr bool is_member_object_pointer_v = __is_member_object_pointer(T);

#else

template <class T>
struct is_member_object_pointer : integral_constant<bool, __asc_is_member_pointer<remove_cv_t<T> >::__is_obj> {};

template <class T>
inline constexpr bool is_member_object_pointer_v = is_member_object_pointer<T>::value;

#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_MEMBER_OBJECT_POINTER_H
