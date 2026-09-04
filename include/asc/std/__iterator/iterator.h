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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_ITERATOR_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_ITERATOR_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
struct iterator {
    using iterator_category = Category;
    using value_type = T;
    using difference_type = Distance;
    using pointer = Pointer;
    using reference = Reference;
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_ITERATOR_H
