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

#ifndef ASC_STL_TEST_COUNTING_ALLOCATOR_H
#define ASC_STL_TEST_COUNTING_ALLOCATOR_H

#include <cstddef>
#include <memory>

namespace asc_stl_allocation_test {

struct allocation_counts {
    int allocated = 0;
    int deallocated = 0;
    bool fail_next = false;

    int outstanding() const
    {
        return allocated - deallocated;
    }
};

template <class T>
struct counting_allocator {
    using value_type = T;
    using pointer = T*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    template <class U>
    struct rebind {
        using other = counting_allocator<U>;
    };

    allocation_counts* state;

    explicit counting_allocator(allocation_counts& counts) noexcept : state(&counts)
    {}
    template <class U>
    counting_allocator(const counting_allocator<U>& other) noexcept : state(other.state)
    {}

    T* allocate(size_type n)
    {
        if (state->fail_next) {
            state->fail_next = false;
            return nullptr;
        }
        T* output = std::allocator<T>{}.allocate(n);
        ++state->allocated;
        return output;
    }

    void deallocate(T* pointer, size_type n) noexcept
    {
        ++state->deallocated;
        std::allocator<T>{}.deallocate(pointer, n);
    }
};

}  // namespace asc_stl_allocation_test

#endif  // ASC_STL_TEST_COUNTING_ALLOCATOR_H
