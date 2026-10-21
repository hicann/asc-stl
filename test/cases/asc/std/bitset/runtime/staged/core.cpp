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
#include "../../../../../../support/b027_core_semantics.h"

__global__ void asc_stl_b027_core_kernel(
    asc_stl_b027_staged::stage_result* result, char* backing, void* state_packet, void* string_packet)
{
    result->code = static_cast<unsigned>(asc_stl_b027_core_test::evaluate());
}
extern "C" void asc_stl_b027_launch_core(asc_stl_b027_staged::stage_result* result, char* backing, void* state_packet,
    void* string_packet, aclrtStream stream)
{
    asc_stl_b027_core_kernel<<<1, 1, 0, stream>>>(result, backing, state_packet, string_packet);
}
