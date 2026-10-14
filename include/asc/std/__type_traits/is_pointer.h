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
#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_POINTER_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_POINTER_H

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
#include <asc/std/__type_traits/remove_cv.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// The __is_pointer keyword fast path is disabled under CCE: libstdc++
// bits/cpp_type_traits.h declares a same-named template, and in the ASC
// toolchain's auxiliary compilation pass (dav-c310-vec) that declaration
// shadows the keyword, so __is_pointer(_Tp) parses as a call to the template
// (triggered only when host headers such as <vector> are included first). The
// fallback branch is semantically complete (_Tp* specialization plus
// remove_cv), so CCE always takes it; on real clang the declaration never
// affects keyword precedence, so the fast path is kept there. Define
// CANN_ASC_STL_DETAIL_USE_IS_POINTER_FALLBACK to force the fallback manually.
#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__is_pointer) && !defined(CANN_ASC_STL_DETAIL_USE_IS_POINTER_FALLBACK) && \
    !CANN_ASC_STL_DETAIL_COMPILER_CCE

template <class T>
struct is_pointer : bool_constant<__is_pointer(T)> {};

template <class T>
inline constexpr bool is_pointer_v = __is_pointer(T);

#else

template <class T>
inline constexpr bool __is_pointer_helper_v = false;

template <class T>
inline constexpr bool __is_pointer_helper_v<T*> = true;

template <class T>
inline constexpr bool is_pointer_v = __is_pointer_helper_v<asc::std::remove_cv_t<T> >;

template <class T>
struct is_pointer : bool_constant<is_pointer_v<T> > {};

#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_POINTER_H
