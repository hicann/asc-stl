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

#ifndef CANN_ASC_STL_ASC___TENSOR_COPY_DESCRIPTOR_H
#define CANN_ASC_STL_ASC___TENSOR_COPY_DESCRIPTOR_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

// Tensor-transfer descriptor value vocabulary for the later public
// <asc/tensor_copy>.  A descriptor records, per dimension, the extent, the GM
// source element stride, the UB destination element stride and the left/right
// padding applied to the destination; the innermost dimension has index
// Rank - 1.  The descriptor holds no memory, is constructible from Host
// tiling results and inside ordinary AICore, and passes by value into a
// kernel.  Every range and stride must pass construction validation.

namespace asc {

enum class tensor_copy_status : int {
    success = 0,
    zero_extent = 1,
    zero_stride = 2,
    size_overflow = 3,
    insufficient_source = 4,
    insufficient_destination = 5,
    invalid_stage = 6,
};

template <unsigned Rank>
class tensor_copy_descriptor {
    static_assert(Rank >= 1 && Rank <= 5, "tensor_copy_descriptor supports ranks 1 through 5");

public:
    using size_type = __UINT32_TYPE__;

private:
    size_type extents_[Rank]{};
    size_type source_strides_[Rank]{};
    size_type destination_strides_[Rank]{};
    size_type left_padding_[Rank]{};
    size_type right_padding_[Rank]{};

public:
    constexpr tensor_copy_descriptor() noexcept = default;

    CANN_ASC_STL_API constexpr size_type extent(unsigned dimension) const noexcept
    {
        return dimension < Rank ? extents_[dimension] : size_type(0);
    }
    CANN_ASC_STL_API constexpr size_type source_stride(unsigned dimension) const noexcept
    {
        return dimension < Rank ? source_strides_[dimension] : size_type(0);
    }
    CANN_ASC_STL_API constexpr size_type destination_stride(unsigned dimension) const noexcept
    {
        return dimension < Rank ? destination_strides_[dimension] : size_type(0);
    }
    CANN_ASC_STL_API constexpr size_type left_padding(unsigned dimension) const noexcept
    {
        return dimension < Rank ? left_padding_[dimension] : size_type(0);
    }
    CANN_ASC_STL_API constexpr size_type right_padding(unsigned dimension) const noexcept
    {
        return dimension < Rank ? right_padding_[dimension] : size_type(0);
    }

    CANN_ASC_STL_API constexpr unsigned rank() const noexcept
    {
        return Rank;
    }

    CANN_ASC_STL_API constexpr tensor_copy_status validate() const noexcept
    {
        unsigned long long elements = 1;
        for (unsigned dimension = 0; dimension < Rank; ++dimension) {
            if (extents_[dimension] == 0) {
                return tensor_copy_status::zero_extent;
            }
            if (source_strides_[dimension] == 0 || destination_strides_[dimension] == 0) {
                return tensor_copy_status::zero_stride;
            }
            const unsigned long long padded = static_cast<unsigned long long>(extents_[dimension]) +
                left_padding_[dimension] + right_padding_[dimension];
            if (padded == 0 || elements > ~0ULL / padded) {
                return tensor_copy_status::size_overflow;
            }
            elements *= padded;
        }
        return tensor_copy_status::success;
    }

    CANN_ASC_STL_API constexpr unsigned long long required_elements() const noexcept
    {
        unsigned long long elements = 1;
        for (unsigned dimension = 0; dimension < Rank; ++dimension) {
            const unsigned long long padded = static_cast<unsigned long long>(extents_[dimension]) +
                left_padding_[dimension] + right_padding_[dimension];
            if (padded == 0 || elements > ~0ULL / padded) {
                return 0;
            }
            elements *= padded;
        }
        return elements;
    }

    CANN_ASC_STL_API constexpr size_type required_alignment() const noexcept
    {
        // The padded innermost row length decides the destination alignment the
        // caller must provide for the UB stage.
        return extents_[Rank - 1] + left_padding_[Rank - 1] + right_padding_[Rank - 1];
    }

    CANN_ASC_STL_API constexpr void set_dimension(unsigned dimension, size_type extent_value, size_type source_stride,
        size_type destination_stride, size_type left_pad, size_type right_pad) noexcept
    {
        if (dimension < Rank) {
            extents_[dimension] = extent_value;
            source_strides_[dimension] = source_stride;
            destination_strides_[dimension] = destination_stride;
            left_padding_[dimension] = left_pad;
            right_padding_[dimension] = right_pad;
        }
    }
};

template <unsigned Rank>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr tensor_copy_descriptor<Rank> make_tensor_copy_descriptor(
    const unsigned int (&extents)[Rank], const unsigned int (&source_strides)[Rank],
    const unsigned int (&destination_strides)[Rank], const unsigned int (&left_padding)[Rank],
    const unsigned int (&right_padding)[Rank]) noexcept
{
    tensor_copy_descriptor<Rank> descriptor;
    for (unsigned dimension = 0; dimension < Rank; ++dimension) {
        descriptor.set_dimension(dimension, extents[dimension], source_strides[dimension],
            destination_strides[dimension], left_padding[dimension], right_padding[dimension]);
    }
    return descriptor;
}

template <unsigned Rank>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr tensor_copy_status validate_tensor_copy_descriptor(
    const tensor_copy_descriptor<Rank>& descriptor) noexcept
{
    return descriptor.validate();
}

template <unsigned Rank>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr unsigned long long tensor_copy_required_elements(
    const tensor_copy_descriptor<Rank>& descriptor) noexcept
{
    return descriptor.required_elements();
}

template <class T, unsigned Rank>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr unsigned int tensor_copy_required_alignment(
    const tensor_copy_descriptor<Rank>& descriptor) noexcept
{
    return descriptor.required_alignment() * static_cast<unsigned int>(sizeof(T));
}

}  // namespace asc

#endif  // CANN_ASC_STL_ASC___TENSOR_COPY_DESCRIPTOR_H
