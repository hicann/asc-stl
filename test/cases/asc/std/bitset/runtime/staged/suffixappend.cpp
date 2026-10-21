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

__global__ void asc_stl_b027_suffixappend_kernel(
    asc_stl_b027_staged::stage_result* result, char* backing, void* state_packet, void* string_packet)
{
    using asc_stl_b027_staged::allocator_type;
    using asc_stl_b027_staged::storage;
    using asc_stl_b027_staged::string_type;
    storage& memory = *reinterpret_cast<storage*>(state_packet);
    string_type& text = *reinterpret_cast<string_type*>(string_packet);
    const int before_append = memory.before_append;
    const char* address = memory.address;
    text.append(text.data() + 40);
    if (text.size() != 56 || text.data() != address || memory.allocations != before_append) {
        result->code = 4;
        return;
    }
    for (__SIZE_TYPE__ i = 0; i < 8; ++i) {
        if (text[48 + i] != static_cast<char>('q' + i)) {
            result->code = 5;
            return;
        }
    }
    result->code = 0;
}
extern "C" void asc_stl_b027_launch_suffixappend(asc_stl_b027_staged::stage_result* result, char* backing,
    void* state_packet, void* string_packet, aclrtStream stream)
{
    asc_stl_b027_suffixappend_kernel<<<1, 1, 0, stream>>>(result, backing, state_packet, string_packet);
}
