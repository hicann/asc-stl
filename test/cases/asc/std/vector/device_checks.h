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

#ifndef ASC_STL_TEST_VECTOR_DEVICE_CHECKS_H
#define ASC_STL_TEST_VECTOR_DEVICE_CHECKS_H

#include <asc/std/vector>
#include "../../../../support/inline_arena_allocator.h"

namespace asc_stl_test_vector {
CANN_ASC_STL_HOST_SIMT_API int check(int seed, void* workspace)
{
    using allocator = asc_stl_test::inline_arena_allocator<int>;
    using table = asc::std::vector<int, allocator>;
    auto& state = asc_stl_test::start_inline_arena(workspace);
    {
        table a{allocator(&state)};
        if (!a.empty() || a.begin() != a.end())
            return 1;
        const int first = seed;
        const auto& c = a;
        a.reserve(1);
        a.push_back(first);
        a.push_back(9);
        if (&a.emplace_back(a[0]) != &a.back() || a.size() != 3 || a.capacity() < 3 || a.begin() != a.data() ||
            a.end() != a.data() + 3 || a.front() != 7 || c.begin() != c.data() || c.end() != c.data() + 3 ||
            c.front() != 7 || c.back() != 7 || c[1] != 9 || a.get_allocator().state != &state)
            return 2;
        a.reserve(a.capacity());
        table moved(static_cast<table&&>(a));
        a = static_cast<table&&>(moved);
        if (!moved.empty() || a.size() != 3 || a[2] != 7)
            return 3;
        a.pop_back();
        a.clear();
        if (!a.empty() || a.begin() != a.end())
            return 6;
    }
    return state.allocations == state.deallocations ? 0 : 7;
}
}  // namespace asc_stl_test_vector

#endif  // ASC_STL_TEST_VECTOR_DEVICE_CHECKS_H
