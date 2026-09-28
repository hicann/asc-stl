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

#ifndef CANN_ASC_STL_ASC_STD___MEMORY_ALIGN_H
#define CANN_ASC_STL_ASC_STD___MEMORY_ALIGN_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__memory/assume_aligned.h>
#include <asc/std/__memory/is_valid_alignment.h>
#include <asc/std/__memory/runtime_assume_aligned.h>
#include <asc/std/cstddef>
#include <asc/std/cstdint>

CANN_ASC_STL_BEGIN_NAMESPACE

CANN_ASC_STL_API void* align(size_t alignment, size_t size, void*& pointer, size_t& space) noexcept
{
    if (!__is_valid_alignment(alignment) || pointer == nullptr || space < size) {
        return nullptr;
    }
    const uintptr_t address = reinterpret_cast<uintptr_t>(pointer);
    const uintptr_t mask = static_cast<uintptr_t>(alignment - 1);
    if (address > static_cast<uintptr_t>(-1) - mask) {
        return nullptr;
    }
    const uintptr_t aligned_address = (address + mask) & ~mask;
    const size_t adjustment = static_cast<size_t>(aligned_address - address);
    if (adjustment > space - size) {
        return nullptr;
    }
    pointer = reinterpret_cast<void*>(aligned_address);  // NOLINT(performance-no-int-to-ptr)
    space -= adjustment;
    return __runtime_assume_aligned(pointer, alignment);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MEMORY_ALIGN_H
