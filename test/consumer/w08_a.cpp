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

#include <asc/tensor_copy>
#include <asc/std/execution>
#include <asc/std/functional>
#include <asc/std/semaphore>

int asc_stl_w08_consumer_a()
{
    const unsigned int extents[1] = {8};
    const unsigned int strides[1] = {1};
    const unsigned int padding[1] = {0};
    const auto descriptor = asc::make_tensor_copy_descriptor<1>(extents, strides, strides, padding, padding);
    static_assert(asc::std::is_execution_policy_v<asc::std::execution::unsequenced_policy>);
    return descriptor.required_elements() == 8 && asc::std::plus<int>{}(2, 5) == 7 ? 0 : 1;
}
