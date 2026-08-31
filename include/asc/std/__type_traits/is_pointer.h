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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_POINTER_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_POINTER_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/remove_cv.h>

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(is_pointer)
#define CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_POINTER(...) __is_pointer(__VA_ARGS__)
#endif  // CANN_ASC_STL_DETAIL_CHECK_BUILTIN(is_pointer)

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if defined(CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_POINTER) && !defined(CANN_ASC_STL_DETAIL_ACCL_USE_IS_POINTER_FALLBACK)

template <class _Tp>
struct is_pointer : public bool_constant<CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_POINTER(_Tp)> {};

template <class _Tp>
inline constexpr bool is_pointer_v = CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_POINTER(_Tp);

#else

template <class _Tp>
inline constexpr bool __asc_is_pointer_helper_v = false;

template <class _Tp>
inline constexpr bool __asc_is_pointer_helper_v<_Tp*> = true;

template <class _Tp>
inline constexpr bool is_pointer_v = __asc_is_pointer_helper_v<remove_cv_t<_Tp> >;

template <class _Tp>
struct is_pointer : public bool_constant<is_pointer_v<_Tp> > {};

#endif  // defined(CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_POINTER) &&
        // !defined(CANN_ASC_STL_DETAIL_ACCL_USE_IS_POINTER_FALLBACK)

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_POINTER_H
