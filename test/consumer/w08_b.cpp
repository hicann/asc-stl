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

#include <asc/std/queue>
#include <asc/std/deque>
#include <asc/std/shared_mutex>
#include <asc/std/latch>
#include <asc/std/semaphore>
#include <asc/std/functional>
#include <asc/std/execution>
#include <asc/tensor_copy>

int asc_stl_w08_consumer_b()
{
    asc::std::binary_semaphore semaphore(1);
    const bool acquired = semaphore.try_acquire();
    const unsigned int extents[1] = {4};
    const unsigned int strides[1] = {1};
    const unsigned int padding[1] = {0};
    const auto descriptor = asc::make_tensor_copy_descriptor<1>(extents, strides, strides, padding, padding);
    return acquired && descriptor.extent(0) == 4 ? 0 : 1;
}
