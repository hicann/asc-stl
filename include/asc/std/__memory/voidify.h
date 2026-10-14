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

#ifndef CANN_ASC_STL_STD_DETAIL_MEMORY_VOIDIFY_H
#define CANN_ASC_STL_STD_DETAIL_MEMORY_VOIDIFY_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__memory/addressof.h>

// Base asc/__config provides no CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 macro.
// __voidify performs a cv-qualified pointer conversion, which risks being
// ill-formed NDR if marked constexpr unconditionally before C++20, so gate it
// on the macro; #ifndef-guarded against a future shared definition.
#ifndef CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20
#if CANN_ASC_STL_DETAIL_HAS_CXX20()
#define CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 constexpr
#else
#define CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20
#endif
#endif  // CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void* __voidify(T& value) noexcept
{
    // Cast away cv-qualifiers to allow modifying elements of a range through const iterators.
    return const_cast<void*>(static_cast<const volatile void*>(asc::std::addressof(value)));
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_MEMORY_VOIDIFY_H
