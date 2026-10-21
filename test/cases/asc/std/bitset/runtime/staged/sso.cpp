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

#include "stage_api.h"
#include "types.h"
#include "../../../../../../support/string_arena_test_allocator.h"
namespace asc_stl_b027_sso {
struct storage {
    char bytes[256];
    __SIZE_TYPE__ used = 0;
    int allocations = 0;
    int deallocations = 0;
};

template <class StatePointer>
using local_allocator = asc_stl_string_arena_test::inline_arena_allocator<StatePointer>;

}  // namespace asc_stl_b027_sso

__global__ void asc_stl_b027_sso_kernel(
    asc_stl_b027_staged::stage_result* result, char* backing, void* state_packet, void* string_packet)
{
    asc_stl_b027_sso::storage memory;
    using allocator_type = asc_stl_b027_sso::local_allocator<decltype(&memory)>;
    using string_type = asc::std::basic_string<char, asc::std::arena_char_traits<char>, allocator_type>;
    {
        char initial[] = {'a', 'b', 'c', '\0'};
        string_type small(initial, allocator_type{&memory});
        const int before = memory.allocations;
        small.append(small.data());
        small = small.data() + 1;
        if (small.size() != 5 || small[0] != 'b' || small[4] != 'c' || memory.allocations != before) {
            result->code = 9;
            return;
        }
    }
    auto& global = *reinterpret_cast<asc_stl_b027_staged::storage*>(state_packet);
    global.sso_allocations = memory.allocations;
    global.sso_deallocations = memory.deallocations;
    result->code = 0;
}
extern "C" void asc_stl_b027_launch_sso(asc_stl_b027_staged::stage_result* result, char* backing, void* state_packet,
    void* string_packet, aclrtStream stream)
{
    asc_stl_b027_sso_kernel<<<1, 1, 0, stream>>>(result, backing, state_packet, string_packet);
}
