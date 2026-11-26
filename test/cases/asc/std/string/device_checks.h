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

#ifndef ASC_STL_TEST_STRING_DEVICE_CHECKS_H
#define ASC_STL_TEST_STRING_DEVICE_CHECKS_H

#include <asc/std/string>
#include "../../../../support/inline_arena_allocator.h"

#include "character_traits_checks.h"

namespace asc_stl_test_string {
CANN_ASC_STL_HOST_SIMT_API int check(int seed, void* workspace)
{
    if (int result = check_character_traits(seed))
        return 20 + result;
    using traits = asc::std::char_traits<char>;
    using alloc = asc_stl_test::inline_arena_allocator<char>;
    using text = asc::std::basic_string<char, traits, alloc>;
    // Runtime character ranges reside in the same address space as the allocator's buffer.
    auto& state = asc_stl_test::start_inline_arena(workspace);
    char* suffix = static_cast<char*>(workspace) + sizeof(state);
    suffix[0] = static_cast<char>('x' + seed - 7);
    suffix[1] = 'y';
    suffix[2] = '\0';
    char* expected = suffix + 3;
    expected[0] = 'a';
    expected[1] = 'd';
    expected[2] = 'c';
    expected[3] = '!';
    for (int i = 4; i < 10; ++i)
        expected[i] = static_cast<char>('x' + (i - 4) % 3);
    expected[10] = '\0';
    {
        text s("abc", alloc(&state));
        const text& c = s;
        if (s.get_allocator().state != &state || c.front() != 'a' || c.back() != 'c' || s.front() != 'a' ||
            s.back() != 'c' || s.begin() != s.data() || s.end() != s.data() + 3 || c.begin() != c.data() ||
            c.end() != c.data() + 3 || c[1] != 'b' || c.c_str()[3] != 0)
            return 1;
        s.reserve(static_cast<unsigned>(seed + 33));
        s[1] = 'd';
        s += '!';
        s += suffix;
        s.push_back('z');
        s.append(s.data() + 4);
        if (s.length() != 10 || s.capacity() < 40 || traits::compare(s.c_str(), expected, 11))
            return 2;
        s = s.c_str() + 4;
        if (s.size() != 6 || traits::compare(s.data(), expected + 4, 7))
            return 3;
        s.clear();
        text empty{alloc(&state)};
        if (!s.empty() || !empty.empty() || s.c_str()[0] != 0 || empty.data()[0] != 0)
            return 4;
    }
    return state.allocations == state.deallocations ? 0 : 5;
}
}  // namespace asc_stl_test_string

#endif  // ASC_STL_TEST_STRING_DEVICE_CHECKS_H
