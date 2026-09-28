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

#ifndef ASC_STL_TEST_B028_ALLOCATOR_H
#define ASC_STL_TEST_B028_ALLOCATOR_H

#include <asc/__config>

namespace asc_stl_b028_test {

struct arena_state {
    unsigned char* storage;
    __SIZE_TYPE__ capacity;
    __SIZE_TYPE__ offset;
    int allocations;
    int deallocations;
};

template <class T>
struct arena_allocator {
    using value_type = T;
    using pointer = T*;
    using size_type = __SIZE_TYPE__;
    template <class U>
    struct rebind {
        using other = arena_allocator<U>;
    };

    arena_state* state = nullptr;
    CANN_ASC_STL_HOST_SIMT_API arena_allocator() = default;
    CANN_ASC_STL_HOST_SIMT_API explicit arena_allocator(arena_state* input) : state(input)
    {}
    template <class U>
    CANN_ASC_STL_HOST_SIMT_API arena_allocator(const arena_allocator<U>& other) : state(other.state)
    {}
    CANN_ASC_STL_HOST_SIMT_API pointer allocate(size_type count)
    {
        const size_type alignment = alignof(T);
        const size_type begin = (state->offset + alignment - 1) / alignment * alignment;
        if (begin + count * sizeof(T) > state->capacity)
            return nullptr;
        pointer result = reinterpret_cast<pointer>(state->storage + begin);
        state->offset = begin + count * sizeof(T);
        ++state->allocations;
        return result;
    }
    CANN_ASC_STL_HOST_SIMT_API void deallocate(pointer, size_type) noexcept
    {
        ++state->deallocations;
    }
};

struct less_int {
    CANN_ASC_STL_HOST_SIMT_API bool operator()(int left, int right) const noexcept
    {
        return left < right;
    }
};

}  // namespace asc_stl_b028_test

#endif  // ASC_STL_TEST_B028_ALLOCATOR_H
