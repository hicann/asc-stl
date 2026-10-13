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

#ifndef ASC_STL_TEST_TENSOR_DESCRIPTOR_BOUNDARIES_H
#define ASC_STL_TEST_TENSOR_DESCRIPTOR_BOUNDARIES_H

#include <asc/tensor_copy>

namespace asc_stl_tensor_descriptor_test {

CANN_ASC_STL_API constexpr asc::tensor_copy_descriptor<2> make_pair_descriptor(
    unsigned int first, unsigned int first_pad, unsigned int second, unsigned int second_pad) noexcept
{
    const unsigned int extents[2] = {first, second};
    const unsigned int strides[2] = {1, 1};
    const unsigned int pads[2] = {first_pad, second_pad};
    const unsigned int zeros[2] = {0, 0};
    return asc::make_tensor_copy_descriptor(extents, strides, strides, pads, zeros);
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned int evaluate(unsigned int maximum)
{
    unsigned int failures = 0;
    const auto low_product = make_pair_descriptor(maximum, 0, maximum, 0);
    failures += low_product.validate() != asc::tensor_copy_status::success;
    failures += low_product.required_elements() != 0xfffffffe00000001ULL;

    const auto largest = make_pair_descriptor(maximum, 2, maximum, 0);
    failures += largest.validate() != asc::tensor_copy_status::success;
    failures += largest.required_elements() != ~0ULL;

    const auto carry_overflow = make_pair_descriptor(maximum, 3, maximum, 0);
    failures += carry_overflow.validate() != asc::tensor_copy_status::size_overflow;
    failures += carry_overflow.required_elements() != 0;

    const auto high_product = make_pair_descriptor(maximum, 1, maximum, 1);
    failures += high_product.validate() != asc::tensor_copy_status::size_overflow;
    failures += high_product.required_elements() != 0;

    const unsigned int extents[3] = {maximum, 65536, maximum};
    const unsigned int strides[3] = {1, 1, 1};
    const unsigned int pads[3] = {1, 0, 0};
    const unsigned int zeros[3] = {0, 0, 0};
    const auto middle_overflow = asc::make_tensor_copy_descriptor(extents, strides, strides, pads, zeros);
    failures += middle_overflow.validate() != asc::tensor_copy_status::size_overflow;
    failures += middle_overflow.required_elements() != 0;

    const auto zero_extent = make_pair_descriptor(0, 0, maximum, 0);
    failures += zero_extent.validate() != asc::tensor_copy_status::zero_extent;
    failures += zero_extent.required_elements() != 0;
    return failures;
}

}  // namespace asc_stl_tensor_descriptor_test

#endif  // ASC_STL_TEST_TENSOR_DESCRIPTOR_BOUNDARIES_H
