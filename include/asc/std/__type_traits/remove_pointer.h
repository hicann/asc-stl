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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_REMOVE_POINTER_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_REMOVE_POINTER_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>

// Inline equivalent of the dev builtin hook (dev __asc/builtin.h): use the
// compiler's __remove_pointer type transform when available.
#if !defined(CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_POINTER)
#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__remove_pointer)
#define CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_POINTER(...) __remove_pointer(__VA_ARGS__)
#endif
#endif  // CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_POINTER

CANN_ASC_STL_BEGIN_NAMESPACE

#if defined(CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_POINTER) && !defined(CANN_ASC_STL_DETAIL_USE_REMOVE_POINTER_FALLBACK)

template <class T>
struct remove_pointer {
    using type = CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_POINTER(T);
};

template <class T>
using remove_pointer_t = CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_POINTER(T);

#else

template <class T>
struct remove_pointer {
    using type = T;
};
template <class T>
struct remove_pointer<T*> {
    using type = T;
};
template <class T>
struct remove_pointer<T* const> {
    using type = T;
};
template <class T>
struct remove_pointer<T* volatile> {
    using type = T;
};
template <class T>
struct remove_pointer<T* const volatile> {
    using type = T;
};

template <class T>
using remove_pointer_t = typename remove_pointer<T>::type;

#endif  // defined(CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_POINTER) &&
        // !defined(CANN_ASC_STL_DETAIL_USE_REMOVE_POINTER_FALLBACK)

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_REMOVE_POINTER_H
