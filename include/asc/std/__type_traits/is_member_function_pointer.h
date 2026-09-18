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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_MEMBER_FUNCTION_POINTER_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_MEMBER_FUNCTION_POINTER_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_function.h>
#include <asc/std/__type_traits/remove_cv.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp>
struct __accl_is_member_pointer {
    enum { __is_member = false, __is_func = false, __is_obj = false };
};

template <class _Tp, class _Up>
struct __accl_is_member_pointer<_Tp _Up::*> {
    enum { __is_member = true, __is_func = is_function_v<_Tp>, __is_obj = !__is_func };
};

template <class _Tp>
struct is_member_function_pointer : bool_constant<__accl_is_member_pointer<remove_cv_t<_Tp>>::__is_func> {};

template <class _Tp>
inline constexpr bool is_member_function_pointer_v = is_member_function_pointer<_Tp>::value;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_MEMBER_FUNCTION_POINTER_H
