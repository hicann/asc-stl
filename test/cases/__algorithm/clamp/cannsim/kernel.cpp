/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#include "kernel_operator.h"

#include <asc/std/__algorithm/clamp.h>

namespace {

constexpr uint32_t kElementCount = 64;

struct Descending {
    CANN_ASC_STL_DETAIL_AICORE_FN constexpr bool operator()(float left, float right) const
    {
        return left > right;
    }
};

}  // namespace

extern "C" __global__ __aicore__ void asc_stl_cannsim_clamp(
    GM_ADDR input, GM_ADDR default_output, GM_ADDR comparator_output)
{
    AscendC::GlobalTensor<float> input_tensor;
    AscendC::GlobalTensor<float> default_tensor;
    AscendC::GlobalTensor<float> comparator_tensor;
    input_tensor.SetGlobalBuffer(reinterpret_cast<__gm__ float*>(input), kElementCount);
    default_tensor.SetGlobalBuffer(reinterpret_cast<__gm__ float*>(default_output), kElementCount);
    comparator_tensor.SetGlobalBuffer(reinterpret_cast<__gm__ float*>(comparator_output), kElementCount);

    AscendC::TQue<AscendC::TPosition::VECIN, 1> input_queue;
    AscendC::TQue<AscendC::TPosition::VECOUT, 1> default_queue;
    AscendC::TQue<AscendC::TPosition::VECOUT, 1> comparator_queue;
    AscendC::TPipe pipe;
    pipe.InitBuffer(input_queue, 1, kElementCount * sizeof(float));
    pipe.InitBuffer(default_queue, 1, kElementCount * sizeof(float));
    pipe.InitBuffer(comparator_queue, 1, kElementCount * sizeof(float));

    auto input_local = input_queue.AllocTensor<float>();
    AscendC::DataCopy(input_local, input_tensor, kElementCount);
    input_queue.EnQue(input_local);
    input_local = input_queue.DeQue<float>();
    auto default_local = default_queue.AllocTensor<float>();
    auto comparator_local = comparator_queue.AllocTensor<float>();
    for (uint32_t index = 0; index < kElementCount; ++index) {
        const float value = input_local.GetValue(index);
        default_local.SetValue(index, asc::std::clamp(value, 10.0F, 100.0F));
        comparator_local.SetValue(index, asc::std::clamp(value, 100.0F, 10.0F, Descending{}));
    }

    default_queue.EnQue(default_local);
    comparator_queue.EnQue(comparator_local);
    input_queue.FreeTensor(input_local);

    default_local = default_queue.DeQue<float>();
    comparator_local = comparator_queue.DeQue<float>();
    AscendC::DataCopy(default_tensor, default_local, kElementCount);
    AscendC::DataCopy(comparator_tensor, comparator_local, kElementCount);
    default_queue.FreeTensor(default_local);
    comparator_queue.FreeTensor(comparator_local);
}
