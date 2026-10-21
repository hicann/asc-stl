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

__global__ void asc_stl_b027_balance_kernel(
    asc_stl_b027_staged::stage_result* result, char* backing, void* state_packet, void* string_packet)
{
    using asc_stl_b027_staged::allocator_type;
    using asc_stl_b027_staged::storage;
    using asc_stl_b027_staged::string_type;
    storage& memory = *reinterpret_cast<storage*>(state_packet);
    result->allocations = static_cast<unsigned>(memory.allocations);
    result->deallocations = static_cast<unsigned>(memory.deallocations);
    result->used = static_cast<unsigned>(memory.used);
    for (unsigned index = 0; index < 3; ++index)
        result->allocation_sizes[index] = memory.allocation_sizes[index];
    result->sso_allocations = static_cast<unsigned>(memory.sso_allocations);
    result->sso_deallocations = static_cast<unsigned>(memory.sso_deallocations);
    const bool balanced = memory.allocations == memory.deallocations;
    const bool local_balanced = memory.sso_allocations == memory.sso_deallocations;
    memory.~storage();
    result->code = balanced && local_balanced ? 0 : 10;
}
extern "C" void asc_stl_b027_launch_balance(asc_stl_b027_staged::stage_result* result, char* backing,
    void* state_packet, void* string_packet, aclrtStream stream)
{
    asc_stl_b027_balance_kernel<<<1, 1, 0, stream>>>(result, backing, state_packet, string_packet);
}
