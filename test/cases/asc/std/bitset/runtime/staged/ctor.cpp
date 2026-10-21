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

__global__ void asc_stl_b027_ctor_kernel(
    asc_stl_b027_staged::stage_result* result, char* backing, void* state_packet, void* string_packet)
{
    using asc_stl_b027_staged::allocator_type;
    using asc_stl_b027_staged::storage;
    using asc_stl_b027_staged::string_type;
    storage& memory = *::new (state_packet) storage{backing};
    char initial[25]{};
    for (__SIZE_TYPE__ index = 0; index < 24; ++index)
        initial[index] = static_cast<char>('a' + index);
    string_type& text = *::new (string_packet) string_type(initial, allocator_type{&memory});
    if (text.size() != 24 || text.capacity() != 24 || memory.allocations != 1 || memory.deallocations != 0) {
        result->code = 101;
        return;
    }
    for (__SIZE_TYPE__ index = 0; index < 24; ++index) {
        if (text[index] != static_cast<char>('a' + index)) {
            result->code = 102;
            return;
        }
    }
    if (text.c_str()[24] != char{}) {
        result->code = 103;
        return;
    }
    result->code = 0;
}
extern "C" void asc_stl_b027_launch_ctor(asc_stl_b027_staged::stage_result* result, char* backing, void* state_packet,
    void* string_packet, aclrtStream stream)
{
    asc_stl_b027_ctor_kernel<<<1, 1, 0, stream>>>(result, backing, state_packet, string_packet);
}
