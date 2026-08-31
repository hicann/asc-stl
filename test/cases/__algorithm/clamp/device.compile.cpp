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

#include "kernel_operator.h"  // NOLINT(build/include_order): defines AscendC attributes used by the header.

// NOLINTNEXTLINE(build/include_order): the kernel header must define __aicore__ first.
#include <asc/std/__algorithm/clamp.h>

namespace {

struct Greater {
    CANN_ASC_STL_DETAIL_AICORE_FN constexpr bool operator()(int left, int right) const
    {
        return left > right;
    }
};

}  // namespace

extern "C" __global__ __aicore__ void asc_stl_clamp_semantic_kernel()
{
    const int value = 6;
    const int low = 0;
    const int high = 10;
    const int descending_low = 10;
    const int descending_high = 0;
    const float float_value = 1.25F;
    const float float_low = -2.5F;
    const float float_high = 4.5F;

    const int& default_result = asc::std::clamp(value, low, high);
    const int& comparator_result = asc::std::clamp(value, descending_low, descending_high, Greater{});
    const float& float_result = asc::std::clamp(float_value, float_low, float_high);
    (void)default_result;
    (void)comparator_result;
    (void)float_result;
}
