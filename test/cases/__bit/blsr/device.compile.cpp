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

#include "kernel_operator.h"  // NOLINT(build/include_order): defines AscendC attributes.

// NOLINTNEXTLINE(build/include_order): kernel_operator.h must define attributes first.
#include <asc/std/__bit/blsr.h>

extern "C" __global__ __aicore__ void asc_stl_blsr_semantic_kernel()
{
    int32_t in0_val = static_cast<int32_t>(0);
    int32_t x_val = in0_val;
    int32_t y_val = static_cast<int32_t>(0);
    int32_t out0_val = static_cast<int32_t>(0);
    int32_t& z_val = out0_val;
    {  // NOLINT(whitespace/braces): isolate the reviewed element operation.
        out0_val = static_cast<int32_t>(asc::std::__accl_blsr(static_cast<unsigned>(in0_val)));
    }
    (void)x_val;
    (void)y_val;
    (void)z_val;
    (void)in0_val;
    (void)out0_val;
}
