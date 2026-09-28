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

#include <asc/std/list>
#include <asc/std/map>
#include <asc/std/__bit/byteswap.h>
#include <asc/std/__new/nonallocating_new.h>

namespace {
struct arena {
    unsigned char* storage;
    __SIZE_TYPE__ offset;
};

template <class T>
struct allocator {
    using value_type = T;
    using pointer = T*;
    template <class U>
    struct rebind {
        using other = allocator<U>;
    };

    arena* state;
    explicit allocator(arena* input) : state(input)
    {}
    template <class U>
    allocator(const allocator<U>& other) : state(other.state)
    {}
    pointer allocate(__SIZE_TYPE__ count)
    {
        const __SIZE_TYPE__ alignment = alignof(T);
        state->offset = (state->offset + alignment - 1) / alignment * alignment;
        pointer result = reinterpret_cast<pointer>(state->storage + state->offset);
        state->offset += count * sizeof(T);
        return result;
    }
    void deallocate(pointer, __SIZE_TYPE__) noexcept
    {}
};

struct less_int {
    bool operator()(int left, int right) const noexcept
    {
        return left < right;
    }
};
}  // namespace

int asc_stl_b028_consumer_a()
{
    alignas(16) unsigned char storage[2048]{};
    arena state{storage, 0};
    asc::std::list<int, allocator<int>> list{allocator<int>(&state)};
    list.push_back(7);
    using pair_type = asc::std::__arena_pair<const int, int>;
    using map_type = asc::std::map<int, int, less_int, allocator<pair_type>>;  // NOLINT(build/include_what_you_use)
    map_type map{allocator<pair_type>(&state)};                                // NOLINT(build/include_what_you_use)
    map[3] = 9;
    return list.front() == 7 && map.find(3)->second == 9 && asc::std::byteswap(0x1234u) == 0x34120000u ? 0 : 1;
}
