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

#include <asc/__tensor_copy/backend.h>
#include <asc/__tensor_copy/descriptor.h>

#include <cassert>
#include <cstdint>

int main()
{
    // Rank 1..5 descriptors exist; the innermost dimension is index Rank - 1.
    constexpr std::uint32_t extents1[1] = {32};
    constexpr std::uint32_t unit_strides1[1] = {1};
    constexpr std::uint32_t no_padding1[1] = {0};
    constexpr auto rank1 =
        asc::make_tensor_copy_descriptor<1>(extents1, unit_strides1, unit_strides1, no_padding1, no_padding1);
    (void)rank1;

    const std::uint32_t extents2[2] = {3, 5};
    const std::uint32_t source_strides2[2] = {8, 1};
    const std::uint32_t destination_strides2[2] = {8, 1};
    const std::uint32_t left_padding2[2] = {0, 1};
    const std::uint32_t right_padding2[2] = {0, 2};
    const auto descriptor2 = asc::make_tensor_copy_descriptor<2>(
        extents2, source_strides2, destination_strides2, left_padding2, right_padding2);
    assert(descriptor2.rank() == 2);
    assert(descriptor2.extent(0) == 3 && descriptor2.extent(1) == 5);
    assert(descriptor2.source_stride(0) == 8 && descriptor2.source_stride(1) == 1);
    assert(descriptor2.destination_stride(0) == 8 && descriptor2.destination_stride(1) == 1);
    assert(descriptor2.left_padding(1) == 1 && descriptor2.right_padding(1) == 2);
    assert(descriptor2.validate() == asc::tensor_copy_status::success);

    // The padded destination footprint drives allocation and alignment.
    assert(descriptor2.required_elements() == 3 * (5 + 1 + 2));
    assert(descriptor2.required_alignment() == 5 + 1 + 2);

    // Out-of-range queries stay at zero instead of reading invalid storage.
    assert(descriptor2.extent(2) == 0);
    assert(descriptor2.source_stride(2) == 0);

    // Validation rejects zero extents and zero strides.
    const std::uint32_t zero_extents[1] = {0};
    const std::uint32_t unit_strides[1] = {1};
    const std::uint32_t no_padding[1] = {0};
    const auto invalid_extent =
        asc::make_tensor_copy_descriptor<1>(zero_extents, unit_strides, unit_strides, no_padding, no_padding);
    assert(invalid_extent.validate() == asc::tensor_copy_status::zero_extent);
    const std::uint32_t unit_extents[1] = {4};
    const std::uint32_t zero_strides[1] = {0};
    const auto invalid_stride =
        asc::make_tensor_copy_descriptor<1>(unit_extents, zero_strides, unit_strides, no_padding, no_padding);
    assert(invalid_stride.validate() == asc::tensor_copy_status::zero_stride);

    // Rank 3..5 descriptors keep the same per-dimension contract.
    const std::uint32_t extents3[3] = {2, 3, 4};
    const std::uint32_t strides3[3] = {12, 4, 1};
    const std::uint32_t pads3[3] = {0, 0, 0};
    const auto descriptor3 = asc::make_tensor_copy_descriptor<3>(extents3, strides3, strides3, pads3, pads3);
    assert(descriptor3.validate() == asc::tensor_copy_status::success);
    assert(descriptor3.required_elements() == 24);

    const std::uint32_t extents5[5] = {2, 2, 2, 2, 2};
    const std::uint32_t strides5[5] = {16, 8, 4, 2, 1};
    const std::uint32_t pads5[5] = {0, 0, 0, 0, 0};
    const auto descriptor5 = asc::make_tensor_copy_descriptor<5>(extents5, strides5, strides5, pads5, pads5);
    assert(descriptor5.validate() == asc::tensor_copy_status::success);
    assert(descriptor5.required_elements() == 32);

    // The native ND-DMA element set is gated; 64-bit and float types match.
    static_assert(asc::detail::is_ndim_copy_element<float>::value);
    static_assert(asc::detail::is_ndim_copy_element<std::int32_t>::value);
    static_assert(asc::detail::is_ndim_copy_element<std::uint8_t>::value);
    static_assert(!asc::detail::is_ndim_copy_element<std::int64_t>::value);
    static_assert(!asc::detail::is_ndim_copy_element<double>::value);
    static_assert(!asc::detail::is_ndim_copy_element<bool>::value);
    return 0;
}
