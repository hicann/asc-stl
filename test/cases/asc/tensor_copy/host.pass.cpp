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

#include <asc/std/execution>
#include <asc/tensor_copy>

#include "../../../support/tensor_descriptor_boundaries.h"

int main()
{
    constexpr auto maximum_descriptor = asc_stl_tensor_descriptor_test::make_pair_descriptor(~0u, 2, ~0u, 0);
    static_assert(maximum_descriptor.validate() == asc::tensor_copy_status::success);
    static_assert(maximum_descriptor.required_elements() == ~0ULL);
    volatile unsigned int maximum = ~0u;
    if (asc_stl_tensor_descriptor_test::evaluate(maximum) != 0) {
        return 2;
    }
    const unsigned int extents[2] = {3, 5};
    const unsigned int source_strides[2] = {8, 1};
    const unsigned int destination_strides[2] = {8, 1};
    const unsigned int left_padding[2] = {0, 1};
    const unsigned int right_padding[2] = {0, 2};
    const auto descriptor =
        asc::make_tensor_copy_descriptor<2>(extents, source_strides, destination_strides, left_padding, right_padding);

    static_assert(asc::std::is_execution_policy_v<asc::std::execution::sequenced_policy>);
    static_assert(asc::std::is_execution_policy_v<asc::std::execution::parallel_policy>);
    static_assert(asc::std::is_execution_policy_v<asc::std::execution::parallel_unsequenced_policy>);
    static_assert(asc::std::is_execution_policy_v<asc::std::execution::unsequenced_policy>);
    static_assert(!asc::std::is_execution_policy_v<int>);
    return descriptor.validate() == asc::tensor_copy_status::success && descriptor.rank() == 2 &&
            descriptor.extent(1) == 5 && descriptor.required_elements() == 24 &&
            asc::tensor_copy_required_alignment<unsigned int>(descriptor) == 32 ?
        0 :
        1;
}
