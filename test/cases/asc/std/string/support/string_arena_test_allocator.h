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

#ifndef ASC_STL_TEST_STRING_ARENA_TEST_ALLOCATOR_H
#define ASC_STL_TEST_STRING_ARENA_TEST_ALLOCATOR_H

#include <asc/__config>

namespace asc_stl_string_arena_test {

template <class StatePointer>
CANN_ASC_STL_API void poison_retired_storage(StatePointer state, char* pointer, __SIZE_TYPE__ count)
{
    // Poison retired storage so aliasing reads fail even when the arena does
    // not reuse bytes. Keep the counter update after the original poison loop.
    for (__SIZE_TYPE__ i = 0; i < count; ++i)
        pointer[i] = '#';
    ++state->deallocations;
}

template <class StatePointer>
struct inline_arena_allocator {
    StatePointer state;

    CANN_ASC_STL_API char* allocate(__SIZE_TYPE__ count)
    {
        if (count > sizeof(state->bytes) - state->used)
            return nullptr;
        char* result = state->bytes + state->used;
        state->used += count;
        ++state->allocations;
        return result;
    }

    CANN_ASC_STL_API void deallocate(char* pointer, __SIZE_TYPE__ count)
    {
        asc_stl_string_arena_test::poison_retired_storage(state, pointer, count);
    }
};

}  // namespace asc_stl_string_arena_test

#endif  // ASC_STL_TEST_STRING_ARENA_TEST_ALLOCATOR_H
