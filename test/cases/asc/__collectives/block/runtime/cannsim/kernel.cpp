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

#include <asc/collectives>
#include "../semantics.h"
__global__ __launch_bounds__(64) void asc_stl_b018_cannsim_kernel(unsigned int* output)
{
    extern __ubuf__ unsigned int shared[];
    const unsigned int thread = static_cast<unsigned int>(threadIdx.x);
    const unsigned int value = thread + 1;
    unsigned int* row = output + thread * 6;
    row[0] = asc::detail::block_reduce_add_impl(shared, value);
    row[1] = asc::detail::block_reduce_min_impl(shared, value);
    row[2] = asc::detail::block_reduce_max_impl(shared, value);
    row[3] = asc::detail::block_broadcast_impl(shared, value, 17);
    row[4] = asc::detail::block_inclusive_scan_add_impl(shared, value);
    row[5] = asc::detail::block_exclusive_scan_add_impl(shared, value);
}
void launch_asc_stl_b018_cannsim(unsigned int* output, aclrtStream stream)
{
    asc_stl_b018_cannsim_kernel<<<1, 64, 32 * sizeof(unsigned int), stream>>>(output);
}
