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

#ifndef CANN_ASC_STL_ASC_STD___MEMORY_IS_VALID_ALIGNMENT_H
#define CANN_ASC_STL_ASC_STD___MEMORY_IS_VALID_ALIGNMENT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__type_traits/is_void.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// Alignment validity in one template: the void lane checks plain power-of-two
// alignment, the typed lane additionally requires enough alignment for T. A
// single entry point avoids a same-signature overload pair and keeps one
// judgement source for every caller.
template <class T = void>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool __is_valid_alignment(__SIZE_TYPE__ alignment) noexcept
{
    if constexpr (is_void_v<T>) {
        return alignment != 0 && (alignment & (alignment - 1)) == 0;
    } else {
        return alignment >= alignof(T) && __is_valid_alignment(alignment);
    }
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MEMORY_IS_VALID_ALIGNMENT_H
