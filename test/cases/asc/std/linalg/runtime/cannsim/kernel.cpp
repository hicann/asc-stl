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

#if defined(ASC_STL_W13_W14_SIMT)
#include <simt_api/device_sync_functions.h>
#endif

#include "support/w13_w14_semantics.h"

#if defined(ASC_STL_W13_W14_SIMT)
__global__ void asc_stl_w13_w14_utility_kernel(unsigned int* result)
{
    result[5] = asc_stl_w13_w14_test::evaluate_utility_cctype();
}

__global__ void asc_stl_w13_w14_bit_kernel(unsigned int* result)
{
    result[6] = asc_stl_w13_w14_test::evaluate_bit();
}

__global__ void asc_stl_w13_w14_types_kernel(unsigned int* result)
{
    result[8] = asc_stl_w13_w14_test::evaluate_types();
    result[9] = asc_stl_w13_w14_test::evaluate_cwide();
    result[7] = result[8] + result[9];
    result[0] = result[5] + result[6] + result[7];
}

__global__ void asc_stl_w13_w14_linalg_kernel(unsigned int* result)
{
    result[1] = asc_stl_w13_w14_test::evaluate_linalg();
}

__global__ void asc_stl_w13_w14_random_kernel(unsigned int* result)
{
    result[2] = asc_stl_w13_w14_test::evaluate_random();
}

__global__ void asc_stl_w13_w14_numeric_kernel(unsigned int* result)
{
    result[3] = asc_stl_w13_w14_test::evaluate_numeric();
}

__global__ void asc_stl_w13_w14_sync_kernel(unsigned int* result)
{
    const unsigned int sync = asc_stl_w13_w14_test::evaluate_sync(result, 4);
    if (threadIdx.x == 0) {
        result[4] = sync;
    }
}
#else
__global__ __vector__ void asc_stl_w13_w14_kernel(__gm__ unsigned int* result)
{
    result[5] = asc_stl_w13_w14_test::evaluate_utility_cctype();
    result[6] = asc_stl_w13_w14_test::evaluate_bit();
    result[8] = asc_stl_w13_w14_test::evaluate_types();
    result[9] = asc_stl_w13_w14_test::evaluate_cwide();
    result[7] = result[8] + result[9];
    result[0] = result[5] + result[6] + result[7];
    result[1] = asc_stl_w13_w14_test::evaluate_linalg();
    result[2] = asc_stl_w13_w14_test::evaluate_random();
    result[3] = asc_stl_w13_w14_test::evaluate_numeric();
    result[4] = 0;
}
#endif

void launch_asc_stl_w13_w14(unsigned int* result, void* stream)
{
#if defined(ASC_STL_W13_W14_SIMT)
    asc_stl_w13_w14_utility_kernel<<<1, 1, 0, stream>>>(result);
    asc_stl_w13_w14_bit_kernel<<<1, 1, 0, stream>>>(result);
    asc_stl_w13_w14_types_kernel<<<1, 1, 0, stream>>>(result);
    asc_stl_w13_w14_linalg_kernel<<<1, 1, 0, stream>>>(result);
    asc_stl_w13_w14_random_kernel<<<1, 1, 0, stream>>>(result);
    asc_stl_w13_w14_numeric_kernel<<<1, 1, 0, stream>>>(result);
    asc_stl_w13_w14_sync_kernel<<<1, 4, 0, stream>>>(result);
#else
    asc_stl_w13_w14_kernel<<<1, nullptr, stream>>>(result);
#endif
}
