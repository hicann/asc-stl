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

#ifndef ASC_STL_TEST_FORWARD_LIST_DEVICE_CHECKS_H
#define ASC_STL_TEST_FORWARD_LIST_DEVICE_CHECKS_H

#include <asc/std/forward_list>
#include "../../../../support/inline_arena_allocator.h"

namespace asc_stl_test_forward_list {
CANN_ASC_STL_HOST_SIMT_API int check(int seed, void* workspace)
{
    using allocator = asc_stl_test::inline_arena_allocator<int>;
    using table = asc::std::forward_list<int, allocator>;
    auto& state = asc_stl_test::start_inline_arena(workspace);
    {
        table a{allocator(&state)};
        if (!a.empty() || a.begin() != a.end())
            return 1;
        const int first = seed - 4;
        a.push_front(first);
        a.push_front(2);
        const auto& c = a;
        if (&a.emplace_front(1) != &c.front() || c.front() != 1)
            return 2;
        auto it = a.begin();
        if (*it.operator->() != 1 || *it++ != 1 || *++it != 3 || ++it != a.end())
            return 3;
        a.pop_front();
        table moved(static_cast<table&&>(a));
        a = static_cast<table&&>(moved);
        if (!moved.empty() || a.front() != 2)
            return 4;
        a.clear();
        if (!a.empty() || a.begin() != a.end())
            return 6;
    }
    return state.allocations == state.deallocations ? 0 : 7;
}
}  // namespace asc_stl_test_forward_list

#endif  // ASC_STL_TEST_FORWARD_LIST_DEVICE_CHECKS_H
