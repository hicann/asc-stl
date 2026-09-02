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
#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_ADD_POINTER_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_ADD_POINTER_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/is_referenceable.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_void.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/remove_reference.h>

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__add_pointer)

template <class T>
using add_pointer_t = __add_pointer(T);

#else

template <class T, bool = __is_referenceable<T>::value || is_void<T>::value>
struct __add_pointer_impl {
    using type = remove_reference_t<T>*;
};

template <class T>
struct __add_pointer_impl<T, false> {
    using type = T;
};

template <class T>
using add_pointer_t = typename __add_pointer_impl<T>::type;

#endif

template <class T>
struct add_pointer {
    using type = add_pointer_t<T>;
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_ADD_POINTER_H
