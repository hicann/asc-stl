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

// auto-workload=fast (n=64, cores=1, tiles=1x64, inputs=2, outputs=1, dtype=float)
#include "kernel_operator.h"
#include <asc/std/__algorithm/comp.h>

namespace {

struct Kernel {
public:
    _ACCL_AICORE_FN void Init(GM_ADDR input0, GM_ADDR input1, GM_ADDR output)
    {
        const uint32_t block_id = AscendC::GetBlockIdx();
        input0_gm_.SetGlobalBuffer(reinterpret_cast<__gm__ float*>(input0) + block_id * kBlockLength, kBlockLength);
        input1_gm_.SetGlobalBuffer(reinterpret_cast<__gm__ float*>(input1) + block_id * kBlockLength, kBlockLength);
        output_gm_.SetGlobalBuffer(reinterpret_cast<__gm__ float*>(output) + block_id * kBlockLength, kBlockLength);
        pipe_.InitBuffer(input0_queue_, 1, kTileSize * sizeof(float));
        pipe_.InitBuffer(input1_queue_, 1, kTileSize * sizeof(float));
        pipe_.InitBuffer(output_queue_, 1, kTileSize * sizeof(float));
    }

    _ACCL_AICORE_FN void Run()
    {
        CopyIn();
        Compute();
        CopyOut();
    }

private:
    _ACCL_AICORE_FN void CopyIn()
    {
        auto input0 = input0_queue_.AllocTensor<float>();
        auto input1 = input1_queue_.AllocTensor<float>();
        AscendC::DataCopy(input0, input0_gm_, kTileSize);
        AscendC::DataCopy(input1, input1_gm_, kTileSize);
        input0_queue_.EnQue(input0);
        input1_queue_.EnQue(input1);
    }

    _ACCL_AICORE_FN void Compute()
    {
        auto input0 = input0_queue_.DeQue<float>();
        auto input1 = input1_queue_.DeQue<float>();
        auto output = output_queue_.AllocTensor<float>();
        for (int32_t index = 0; index < kTileSize; ++index) {
            const float left = input0.GetValue(index);
            const float right = input1.GetValue(index);
            output.SetValue(index, asc::std::__less{}(left, right) ? 1.0F : 0.0F);
        }
        output_queue_.EnQue(output);
        input0_queue_.FreeTensor(input0);
        input1_queue_.FreeTensor(input1);
    }

    _ACCL_AICORE_FN void CopyOut()
    {
        auto output = output_queue_.DeQue<float>();
        AscendC::DataCopy(output_gm_, output, kTileSize);
        output_queue_.FreeTensor(output);
    }

    static constexpr int32_t kBlockLength = 64;
    static constexpr int32_t kTileSize = 64;
    AscendC::GlobalTensor<float> input0_gm_;
    AscendC::GlobalTensor<float> input1_gm_;
    AscendC::GlobalTensor<float> output_gm_;
    AscendC::TQue<AscendC::TPosition::VECIN, 1> input0_queue_;
    AscendC::TQue<AscendC::TPosition::VECIN, 1> input1_queue_;
    AscendC::TQue<AscendC::TPosition::VECOUT, 1> output_queue_;
    AscendC::TPipe pipe_;
};

}  // namespace

extern "C" __global__ __aicore__ void comp_kernel(GM_ADDR input0, GM_ADDR input1, GM_ADDR output)
{
    Kernel kernel;
    kernel.Init(input0, input1, output);
    kernel.Run();
}
