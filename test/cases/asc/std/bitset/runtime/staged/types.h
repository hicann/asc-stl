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

#ifndef ASC_STL_TEST_B027_STAGED_TYPES_H
#define ASC_STL_TEST_B027_STAGED_TYPES_H
#include <asc/std/string>
#include <asc/std/new>
#include "../../../../../../support/string_arena_test_allocator.h"
namespace asc_stl_b027_staged {
struct storage {
    char* bytes;
    __SIZE_TYPE__ capacity = 256;
    __SIZE_TYPE__ used = 0;
    int allocations = 0;
    int deallocations = 0;
    const char* address = nullptr;
    int before_append = 0;
    int sso_allocations = 0;
    int sso_deallocations = 0;
    unsigned allocation_sizes[3]{};
};
template <class StatePointer>
struct arena_allocator {
    StatePointer state;
    CANN_ASC_STL_API char* allocate(__SIZE_TYPE__ count)
    {
        if (count > state->capacity - state->used)
            return nullptr;
        char* result = state->bytes + state->used;
        state->used += count;
        if (state->allocations < 3)
            state->allocation_sizes[state->allocations] = static_cast<unsigned>(count);
        ++state->allocations;
        return result;
    }
    CANN_ASC_STL_API void deallocate(char* pointer, __SIZE_TYPE__ count)
    {
        asc_stl_string_arena_test::poison_retired_storage(state, pointer, count);
    }
};
using allocator_type = arena_allocator<storage*>;
using string_type = asc::std::basic_string<char, asc::std::arena_char_traits<char>, allocator_type>;
static_assert(sizeof(storage) <= 64, "GM state packet is too small");
static_assert(sizeof(string_type) <= 128, "GM string packet is too small");
}  // namespace asc_stl_b027_staged
#endif  // ASC_STL_TEST_B027_STAGED_TYPES_H
