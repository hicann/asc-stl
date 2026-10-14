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
#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_SIGNED_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_SIGNED_H

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
#include <asc/std/__type_traits/is_arithmetic.h>
#include <asc/std/__type_traits/is_integral.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// BiSheng/CCE 的 __has_builtin 会报告 __is_signed，但 dav 后端不支持在
// 类型上下文使用该内建 trait，设备编译一律走纯库回退。
#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__is_signed) && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

template <class T>
struct is_signed : bool_constant<__is_signed(T)> {};

template <class T>
inline constexpr bool is_signed_v = __is_signed(T);

#else

template <class T, bool = is_integral_v<T> >
inline constexpr bool __is_signed_helper_v = true;

template <class T>
inline constexpr bool __is_signed_helper_v<T, true> = T(-1) < T(0);

template <class T>
inline constexpr bool is_signed_v = is_arithmetic_v<T> && __is_signed_helper_v<T>;

template <class T>
struct is_signed : bool_constant<is_signed_v<T> > {};

#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_SIGNED_H
