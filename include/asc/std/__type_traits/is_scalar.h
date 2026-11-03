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
#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_SCALAR_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_SCALAR_H

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
#include <asc/std/__type_traits/is_enum.h>
#include <asc/std/__type_traits/is_member_pointer.h>
#include <asc/std/__type_traits/is_null_pointer.h>
#include <asc/std/__type_traits/is_pointer.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

// CCE may resolve __is_scalar to a declaration from hosted headers.
// Use the standard trait composition consistently across its compilation passes.
#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__is_scalar) && !defined(CANN_ASC_STL_DETAIL_USE_IS_SCALAR_FALLBACK) && \
    !CANN_ASC_STL_DETAIL_COMPILER_CCE

template <class T>
struct is_scalar : bool_constant<__is_scalar(T)> {};

template <class T>
inline constexpr bool is_scalar_v = __is_scalar(T);

#else

template <class T>
inline constexpr bool is_scalar_v =
    is_arithmetic_v<T> || is_member_pointer_v<T> || is_pointer_v<T> || is_null_pointer_v<T> || is_enum_v<T>;

template <class T>
struct is_scalar : bool_constant<is_scalar_v<T> > {};

#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_SCALAR_H
