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

#ifndef ASC_STL_TEST_STRING_ALIASING_SEMANTICS_H
#define ASC_STL_TEST_STRING_ALIASING_SEMANTICS_H

#include <asc/std/string>

#include "string_arena_test_allocator.h"

namespace asc_stl_string_aliasing_test {

struct storage {
    char bytes[256];
    __SIZE_TYPE__ used = 0;
    int allocations = 0;
    int deallocations = 0;
};

template <class StatePointer>
using arena_test_allocator = asc_stl_string_arena_test::inline_arena_allocator<StatePointer>;

template <class StringPointer, class StatePointer>
CANN_ASC_STL_API int check_self_append(StringPointer text, StatePointer memory, int before_growth)
{
    if (text->size() != 48 || memory->allocations != before_growth + 1)
        return 1;
    for (__SIZE_TYPE__ i = 0; i < 48; ++i) {
        if ((*text)[i] != static_cast<char>('a' + i % 24))
            return 2;
    }
    if (text->c_str()[48] != '\0')
        return 3;
    return 0;
}

template <class StringPointer, class StatePointer>
CANN_ASC_STL_API int check_suffix_append(
    StringPointer text, StatePointer memory, int before_append, const char* address)
{
    if (text->size() != 56 || text->data() != address || memory->allocations != before_append)
        return 4;
    for (__SIZE_TYPE__ i = 0; i < 8; ++i) {
        if ((*text)[48 + i] != static_cast<char>('q' + i))
            return 5;
    }
    return 0;
}

template <class StringPointer>
CANN_ASC_STL_API int check_suffix_assignment(StringPointer text, const char* address)
{
    if (text->size() != 32 || text->data() != address || (*text)[0] != 'a' || (*text)[24] != 'q' ||
        (*text)[31] != 'x' || text->c_str()[32] != '\0')
        return 6;
    return 0;
}

template <class StringPointer>
CANN_ASC_STL_API int check_self_assignment(StringPointer text)
{
    if (text->size() != 32 || (*text)[0] != 'a' || (*text)[31] != 'x')
        return 7;
    return 0;
}

template <class StringPointer>
CANN_ASC_STL_API int check_empty_assignment(StringPointer text)
{
    if (!text->empty() || text->c_str()[0] != '\0')
        return 8;
    return 0;
}

template <class StringPointer, class StatePointer>
CANN_ASC_STL_API int check_small_assignment(StringPointer small, StatePointer memory, int before)
{
    if (small->size() != 5 || (*small)[0] != 'b' || (*small)[4] != 'c' || memory->allocations != before)
        return 9;
    return 0;
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE int evaluate()
{
    storage memory;
    using allocator_type = arena_test_allocator<decltype(&memory)>;
    using string_type = asc::std::basic_string<char, asc::std::arena_char_traits<char>, allocator_type>;
    {
        char initial[25]{};
        for (__SIZE_TYPE__ index = 0; index < 24; ++index)
            initial[index] = static_cast<char>('a' + index);
        string_type text(initial, allocator_type{&memory});
        const int before_growth = memory.allocations;
        text.append(text.data());
        const int self_append = check_self_append(&text, &memory, before_growth);
        if (self_append != 0)
            return self_append;
        text.reserve(96);
        const int before_append = memory.allocations;
        const char* address = text.data();
        text.append(text.data() + 40);
        const int suffix_append = check_suffix_append(&text, &memory, before_append, address);
        if (suffix_append != 0)
            return suffix_append;
        text = text.data() + 24;
        const int suffix_assignment = check_suffix_assignment(&text, address);
        if (suffix_assignment != 0)
            return suffix_assignment;
        text = text.c_str();
        const int self_assignment = check_self_assignment(&text);
        if (self_assignment != 0)
            return self_assignment;
        text = text.data() + text.size();
        const int empty_assignment = check_empty_assignment(&text);
        if (empty_assignment != 0)
            return empty_assignment;
    }
    {
        char initial[] = {'a', 'b', 'c', '\0'};
        string_type small(initial, allocator_type{&memory});
        const int before = memory.allocations;
        small.append(small.data());
        small = small.data() + 1;
        const int small_assignment = check_small_assignment(&small, &memory, before);
        if (small_assignment != 0)
            return small_assignment;
    }
    return memory.allocations == memory.deallocations ? 0 : 10;
}

}  // namespace asc_stl_string_aliasing_test

#endif  // ASC_STL_TEST_STRING_ALIASING_SEMANTICS_H
