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

#ifndef CANN_ASC_STL_STD_DETAIL_CONCEPT_MACROS_H
#define CANN_ASC_STL_STD_DETAIL_CONCEPT_MACROS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/enable_if.h>

// Keep library constraints expressible in C++17. These two macros are paired:
// TEMPLATE(class T) REQUIRES(predicate<T>) declares one constrained template.
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#define CANN_ASC_STL_DETAIL_TEMPLATE(...) template <__VA_ARGS__>
#define CANN_ASC_STL_DETAIL_REQUIRES(...) requires(__VA_ARGS__)
#define CANN_ASC_STL_DETAIL_TRAILING_REQUIRES(...) requires(__VA_ARGS__)
#else
#define CANN_ASC_STL_DETAIL_TEMPLATE(...) template <__VA_ARGS__
#define CANN_ASC_STL_DETAIL_REQUIRES(...) \
    , bool __asc_constraint = true, ::asc::std::enable_if_t < (__VA_ARGS__) && __asc_constraint, int > = 0 >
// A trailing clause cannot constrain an ordinary member in C++17. Use a
// dependent member template and the paired macros above on that path.
#endif

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
#define CANN_ASC_STL_DETAIL_CONCEPT concept
#else
#define CANN_ASC_STL_DETAIL_CONCEPT inline constexpr bool
#endif

#endif  // CANN_ASC_STL_STD_DETAIL_CONCEPT_MACROS_H
