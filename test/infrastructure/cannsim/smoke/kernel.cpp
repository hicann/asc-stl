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

extern "C" __global__ __aicore__ void asc_stl_cannsim_add(GM_ADDR x, GM_ADDR y, GM_ADDR output)
{
    constexpr uint32_t kElementCount = 64;
    AscendC::GlobalTensor<int32_t> x_tensor;
    AscendC::GlobalTensor<int32_t> y_tensor;
    AscendC::GlobalTensor<int32_t> output_tensor;
    x_tensor.SetGlobalBuffer(reinterpret_cast<__gm__ int32_t*>(x), kElementCount);
    y_tensor.SetGlobalBuffer(reinterpret_cast<__gm__ int32_t*>(y), kElementCount);
    output_tensor.SetGlobalBuffer(reinterpret_cast<__gm__ int32_t*>(output), kElementCount);

    AscendC::TQue<AscendC::TPosition::VECIN, 1> x_queue;
    AscendC::TQue<AscendC::TPosition::VECIN, 1> y_queue;
    AscendC::TQue<AscendC::TPosition::VECOUT, 1> output_queue;
    AscendC::TPipe pipe;
    pipe.InitBuffer(x_queue, 1, kElementCount * sizeof(int32_t));
    pipe.InitBuffer(y_queue, 1, kElementCount * sizeof(int32_t));
    pipe.InitBuffer(output_queue, 1, kElementCount * sizeof(int32_t));

    auto x_local = x_queue.AllocTensor<int32_t>();
    auto y_local = y_queue.AllocTensor<int32_t>();
    AscendC::DataCopy(x_local, x_tensor, kElementCount);
    AscendC::DataCopy(y_local, y_tensor, kElementCount);
    x_queue.EnQue(x_local);
    y_queue.EnQue(y_local);

    x_local = x_queue.DeQue<int32_t>();
    y_local = y_queue.DeQue<int32_t>();
    auto output_local = output_queue.AllocTensor<int32_t>();
    for (uint32_t index = 0; index < kElementCount; ++index) {
        output_local.SetValue(index, x_local.GetValue(index) + y_local.GetValue(index));
    }
    output_queue.EnQue(output_local);
    x_queue.FreeTensor(x_local);
    y_queue.FreeTensor(y_local);

    output_local = output_queue.DeQue<int32_t>();
    AscendC::DataCopy(output_tensor, output_local, kElementCount);
    output_queue.FreeTensor(output_local);
}
