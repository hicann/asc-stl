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

#ifndef ASC_STL_TEST_VECTOR_ALIASING_SEMANTICS_H
#define ASC_STL_TEST_VECTOR_ALIASING_SEMANTICS_H

#include <asc/std/vector>

namespace asc_stl_vector_aliasing_test {

struct storage {
    alignas(16) unsigned char bytes[256];
    __SIZE_TYPE__ used = 0;
    int allocations = 0;
    int deallocations = 0;
};

template <class T>
struct poisoning_allocator {
    storage* state;
    CANN_ASC_STL_API T* allocate(__SIZE_TYPE__ count)
    {
        const __SIZE_TYPE__ offset = (state->used + alignof(T) - 1) / alignof(T) * alignof(T);
        if (count > (sizeof(state->bytes) - offset) / sizeof(T))
            return nullptr;
        T* result = reinterpret_cast<T*>(state->bytes + offset);
        state->used = offset + count * sizeof(T);
        ++state->allocations;
        return result;
    }
    CANN_ASC_STL_API void deallocate(T* address, __SIZE_TYPE__ count)
    {
        unsigned char* bytes = reinterpret_cast<unsigned char*>(address);
        for (__SIZE_TYPE__ index = 0; index < count * sizeof(T); ++index)
            bytes[index] = 0xa5;
        ++state->deallocations;
    }
};

struct item {
    int value;
    CANN_ASC_STL_API explicit item(int number) : value(number)
    {}
    CANN_ASC_STL_API item(const int& left, const int& right) : value(left + right)
    {}
    CANN_ASC_STL_API item(const item& other) : value(other.value)
    {}
    CANN_ASC_STL_API item(item&& other) : value(other.value)
    {
        other.value = -1;
    }
    CANN_ASC_STL_API ~item()
    {
        value = -2;
    }
};

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE int integers()
{
    storage memory;
    {
        asc::std::vector<int, poisoning_allocator<int>> values{poisoning_allocator<int>{&memory}};
        values.push_back(11);
        values.push_back(22);
        values.push_back(values[0]);
        if (values.size() != 3 || values[0] != 11 || values[2] != 11)
            return 1;
        values.push_back(values[1]);
        if (values.size() != 4 || values[3] != 22)
            return 2;
        int& appended = values.emplace_back(values[3]);
        if (values.size() != 5 || appended != 22 || &appended != &values[4])
            return 3;
    }
    return memory.allocations == memory.deallocations ? 0 : 4;
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE int subobjects()
{
    storage memory;
    {
        asc::std::vector<item, poisoning_allocator<item>> values{poisoning_allocator<item>{&memory}};
        values.emplace_back(7);
        values.emplace_back(11);
        values.emplace_back(values[0].value, values[1].value);
        if (values.size() != 3 || values[0].value != 7 || values[1].value != 11 || values[2].value != 18)
            return 5;
        values.emplace_back(values[0].value, values[2].value);
        if (values[3].value != 25)
            return 6;
        values.push_back(values[1]);
        if (values.size() != 5 || values[1].value != 11 || values[4].value != 11)
            return 7;
    }
    return memory.allocations == memory.deallocations ? 0 : 8;
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE int move_alias()
{
    storage memory;
    {
        asc::std::vector<item, poisoning_allocator<item>> values{poisoning_allocator<item>{&memory}};
        values.emplace_back(13);
        values.emplace_back(17);
        values.push_back(static_cast<item&&>(values[0]));
        if (values.size() != 3 || values[0].value != -1 || values[1].value != 17 || values[2].value != 13)
            return 9;
    }
    return memory.allocations == memory.deallocations ? 0 : 10;
}

CANN_ASC_STL_API int evaluate()
{
    const int integer_result = integers();
    if (integer_result != 0)
        return integer_result;
    const int subobject_result = subobjects();
    if (subobject_result != 0)
        return subobject_result;
    return move_alias();
}

}  // namespace asc_stl_vector_aliasing_test

#endif  // ASC_STL_TEST_VECTOR_ALIASING_SEMANTICS_H
