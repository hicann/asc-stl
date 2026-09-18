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
#include <asc/std/__algorithm/comp.h>

extern "C" __global__ __aicore__ void asc_stl_comp_semantic_kernel()
{
    float in0_val = static_cast<float>(0);
    float in1_val = static_cast<float>(0);
    float x_val = in0_val;
    float y_val = in1_val;
    float out0_val = static_cast<float>(0);
    float& z_val = out0_val;
    {  // NOLINT(whitespace/braces): isolate the reviewed element operation.
        out0_val = asc::std::__less{}(in0_val, in1_val) ? 1.0f : 0.0f;
    }
    (void)x_val;
    (void)y_val;
    (void)z_val;
    (void)in0_val;
    (void)in1_val;
    (void)out0_val;
}
