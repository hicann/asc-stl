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

#ifndef ASC_STL_TEST_MAP_DEVICE_CHECKS_H
#define ASC_STL_TEST_MAP_DEVICE_CHECKS_H

#include <asc/std/map>
#include "../../../../support/inline_arena_allocator.h"

namespace asc_stl_test_map {
struct ascending {
    CANN_ASC_STL_HOST_SIMT_API bool operator()(int a, int b) const
    {
        return a < b;
    }
};

CANN_ASC_STL_HOST_SIMT_API int check(int seed, void* workspace)
{
    using allocator = asc_stl_test::inline_arena_allocator<asc::std::__arena_pair<const int, int>>;
    using table = asc::std::map<int, int, ascending, allocator>;  // NOLINT(build/include_what_you_use)
    using value = typename table::value_type;
    auto& state = asc_stl_test::start_inline_arena(workspace);
    {
        table a{ascending{}, allocator(&state)};
        if (!a.empty() || a.begin() != a.end() || a.count(9) || a.find(9) != a.end())
            return 1;
        for (int n = 0; n < 19; ++n) {
            const int k = (seed * n) % 19;
            const value input = value{k, -k};
            auto inserted = a.insert(input);
            auto duplicate = a.insert(value(k, k + 100));
            if (!inserted.second || duplicate.second || inserted.first != duplicate.first || a.count(k) != 1)
                return 2;
            if (inserted.first->first != k || duplicate.first->second != -k || a[k] != -k)
                return 3;
        }
        unsigned visited = 0;
        unsigned members = 0;
        for (auto it = a.begin(); it != a.end(); ++it) {
            const int key = it->first;
            if (key != static_cast<int>(visited))
                return 5;
            if (key < 0 || key >= 19 || (members & (1u << key)))
                return 6;
            members |= 1u << key;
            ++visited;
        }
        if (visited != a.size() || members != (1u << 19) - 1 || a.find(23) != a.end())
            return 7;
        table moved(static_cast<table&&>(a));
        table target{allocator(&state)};
        target.insert(value(-1, 2));
        target = static_cast<table&&>(moved);
        if (!a.empty() || !moved.empty() || target.size() != 19 || target.count(-1) != 0)
            return 8;
        if (target[31] != 0 || target.size() != 20 || target.count(31) != 1)
            return 10;
        target.clear();
        if (!target.empty() || target.begin() != target.end() || target.find(7) != target.end())
            return 11;
    }
    return state.allocations == state.deallocations ? 0 : 12;
}
}  // namespace asc_stl_test_map

#endif  // ASC_STL_TEST_MAP_DEVICE_CHECKS_H
