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

#ifndef CANN_ASC_STL_STD_DETAIL_TUPLE_TUPLE_ELEMENT_H
#define CANN_ASC_STL_STD_DETAIL_TUPLE_TUPLE_ELEMENT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__cstddef/types.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <size_t Index, class T>
struct tuple_element;
template <size_t Index, class T>
using tuple_element_t = typename tuple_element<Index, T>::type;
template <size_t Index, class T>
struct tuple_element<Index, const T> {
    using type = const tuple_element_t<Index, T>;
};
template <size_t Index, class T>
struct tuple_element<Index, volatile T> {
    using type = volatile tuple_element_t<Index, T>;
};
template <size_t Index, class T>
struct tuple_element<Index, const volatile T> {
    using type = const volatile tuple_element_t<Index, T>;
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TUPLE_TUPLE_ELEMENT_H
