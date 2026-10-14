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

#ifndef CANN_ASC_STL_ASC___MEMORY_BUFFERS_H
#define CANN_ASC_STL_ASC___MEMORY_BUFFERS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

namespace asc::detail {

// Ownership vocabulary for the move-only typed buffers exposed by the later
// public facade: a buffer owns exactly one explicit allocation and records no
// hidden work.  The release marker hands the allocation back without freeing,
// matching the resource that produced it.
struct buffer_state {
    void* data;
    __SIZE_TYPE__ bytes;
    __SIZE_TYPE__ alignment;
    bool owns;

    CANN_ASC_STL_API constexpr buffer_state() noexcept : data(nullptr), bytes(0), alignment(0), owns(false)
    {}
    CANN_ASC_STL_API constexpr buffer_state(
        void* data_pointer, __SIZE_TYPE__ size_bytes, __SIZE_TYPE__ size_alignment) noexcept
        : data(data_pointer), bytes(size_bytes), alignment(size_alignment), owns(data_pointer != nullptr)
    {}

    CANN_ASC_STL_API constexpr void* release() noexcept
    {
        owns = false;
        return data;
    }
};

// Byte-size helpers shared by the buffer factories; overflows report zero so
// factories can fail closed without exceptions.
CANN_ASC_STL_API constexpr __SIZE_TYPE__ buffer_element_bytes(
    __SIZE_TYPE__ element_size, __SIZE_TYPE__ element_count) noexcept
{
    if (element_size == 0 || element_count == 0)
        return 0;
    const __SIZE_TYPE__ total = element_size * element_count;
    // The division round-trip alone is sufficient: unsigned wraparound makes
    // total < element_size * element_count, hence total / element_count <
    // element_size, so a failed round-trip already rejects every overflow.
    // The remainder test is kept purely as belt-and-braces documentation of
    // the exact-multiple expectation; it can never fail when the round-trip
    // holds.
    return total / element_count == element_size && total % element_size == 0 ? total : 0;
}

CANN_ASC_STL_API constexpr bool buffer_alignment_valid(__SIZE_TYPE__ alignment) noexcept
{
    return alignment != 0 && (alignment & (alignment - 1)) == 0;
}

}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___MEMORY_BUFFERS_H
