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

#ifndef ASC_STL_TEST_INLINE_ARENA_ALLOCATOR_H
#define ASC_STL_TEST_INLINE_ARENA_ALLOCATOR_H

#include <asc/std/new>

namespace asc_stl_test {

struct alignas(64) inline_arena {
    unsigned offset;
    int allocations;
    int deallocations;
    alignas(64) unsigned char bytes[2048];
};

// SIMT passes this allocator between operations that may execute out of line.
// Keep its metadata and payload in a single block of device global memory.
CANN_ASC_STL_HOST_SIMT_API inline_arena& start_inline_arena(void* workspace)
{
    auto* arena = static_cast<inline_arena*>(workspace);
    ::new (static_cast<void*>(arena)) inline_arena;
    arena->offset = 0;
    arena->allocations = 0;
    arena->deallocations = 0;
    return *arena;
}

template <class T>
struct inline_arena_allocator {
    using value_type = T;
    using pointer = T*;
    using size_type = __SIZE_TYPE__;
    template <class U>
    struct rebind {
        using other = inline_arena_allocator<U>;
    };

    inline_arena* state;

    CANN_ASC_STL_HOST_SIMT_API explicit inline_arena_allocator(inline_arena* input) : state(input)
    {}
    template <class U>
    CANN_ASC_STL_HOST_SIMT_API inline_arena_allocator(const inline_arena_allocator<U>& other) : state(other.state)
    {}
    CANN_ASC_STL_HOST_SIMT_API pointer allocate(size_type count)
    {
        static_assert(alignof(T) <= alignof(inline_arena));
        static_assert(sizeof(T) <= sizeof(state->bytes));
        const size_type start = (state->offset + alignof(T) - 1) & ~(alignof(T) - 1);
        if (count > sizeof(state->bytes) || count * sizeof(T) > sizeof(state->bytes) - start)
            return nullptr;
        state->offset = static_cast<unsigned>(start + count * sizeof(T));
        ++state->allocations;
        return reinterpret_cast<pointer>(state->bytes + start);
    }
    CANN_ASC_STL_HOST_SIMT_API void deallocate(pointer, size_type) noexcept
    {
        ++state->deallocations;
    }
};

}  // namespace asc_stl_test

#endif  // ASC_STL_TEST_INLINE_ARENA_ALLOCATOR_H
