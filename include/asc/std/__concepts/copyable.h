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

#ifndef CANN_ASC_STL_ASC_STD___CONCEPTS_COPYABLE_H
#define CANN_ASC_STL_ASC_STD___CONCEPTS_COPYABLE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/assignable.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/movable.h>

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class T>
concept copyable = copy_constructible<T> && movable<T> && assignable_from<T&, T&> && assignable_from<T&, const T&> &&
    assignable_from<T&, const T>;
#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CONCEPTS_COPYABLE_H
