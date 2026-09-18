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

#include "kernel_operator.h"  // NOLINT(build/include_order): defines AscendC attributes used by the header.

// NOLINTNEXTLINE(build/include_order): the kernel header must define __aicore__ first.
#include <asc/std/detail/__config>

template <class _Tp>
CANN_ASC_STL_API constexpr _Tp asc_stl_config_identity(_Tp value)
{
    return value;
}

extern "C" __global__ __aicore__ void asc_stl_config_api_contract_kernel()
{
    const int value = asc_stl_config_identity(42);
    (void)value;
}
