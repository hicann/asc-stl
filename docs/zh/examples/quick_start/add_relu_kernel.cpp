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

#include <asc/pipeline>
#include <asc/std/algorithm>

#include "basic_api/kernel_tensor.h"

extern "C" __global__ __aicore__ void add_relu_kernel(__gm__ float* x, __gm__ float* y, __gm__ float* z)
{
    constexpr unsigned int count = 64;
    __ubuf__ float x_local[count];
    __ubuf__ float y_local[count];
    __ubuf__ float z_local[count];
    // This kernel owns event IDs 2 and 3; they are not shared with TPipe/TQue.
    asc::pipeline_ref pipeline(2, 3);
    pipeline.producer_acquire(0);
    asc::copy_async(pipeline, 0, asc::ub_span<float>(x_local, count), asc::gm_span<const float>(x, count));
    asc::copy_async(pipeline, 0, asc::ub_span<float>(y_local, count), asc::gm_span<const float>(y, count));
    pipeline.producer_commit(0);
    pipeline.consumer_wait(0);
    for (unsigned int index = 0; index < count; ++index)
        // NOLINTNEXTLINE(build/include_what_you_use)
        z_local[index] = asc::std::max(x_local[index] + y_local[index], 0.0F);
    pipeline.consumer_release(0);
    asc::copy_async(pipeline, 0, asc::gm_span<float>(z, count), asc::ub_span<const float>(z_local, count));
    pipeline.wait();
}
