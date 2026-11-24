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

#include <asc/memory>
#include <asc/std/algorithm>
#include <asc/std/functional>
#include <asc/std/iterator>
#include <asc/std/map>
#include <asc/std/set>
#include <asc/std/utility>

int main()
{
    alignas(64) unsigned char storage[512]{};
    asc::monotonic_arena arena(storage, sizeof(storage));
    using set_type = asc::std::set<int, asc::std::less<int>, asc::arena_allocator<int>>;
    set_type keys{asc::arena_allocator<int>(arena)};
    static_assert(asc::std::forward_iterator<set_type::iterator>);
    keys.insert(3);
    keys.insert(1);
    auto key = keys.begin();
    if (*key++ != 1 || key != asc::std::ranges::find(keys, 3) || *key++ != 3 || key != keys.end())
        return 1;

    using allocator = asc::arena_allocator<asc::std::pair<const int, int>>;
    using map_type = asc::std::map<int, int, asc::std::less<int>, allocator>;  // NOLINT(build/include_what_you_use)
    map_type values{allocator(arena)};
    static_assert(asc::std::forward_iterator<map_type::iterator>);
    values[3] = 30;
    values[1] = 10;
    auto entry = values.begin();
    auto first = entry++;
    first->second = 11;
    if (first->first != 1 || values[1] != 11 ||
        entry != asc::std::ranges::find(values, 3, &map_type::value_type::first))
        return 2;
    return (entry++)->second == 30 && entry == values.end() ? 0 : 3;
}
