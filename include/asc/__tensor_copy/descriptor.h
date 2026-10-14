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

// Simulator finding (cann-9.2.0-beta.2, dav-3510 vector core): the optnone
// attribute previously applied here miscompiles the validate() body on the
// CCE device path - validate() returned size_overflow for every descriptor,
// which made tensor_load_async retire before producer_commit and deadlocked
// pipeline consumer_wait (w08.simd). Plain 64-bit multiply/division and the
// segmented checked_multiply below all compile, link and execute correctly
// at -O3 on the pinned toolchain, so no optnone guard is applied; the
// segmented 32-bit multiply stays as defensive arithmetic only.
#define CANN_ASC_STL_DETAIL_TENSOR_VALIDATE_OPTNONE

// Tensor-transfer descriptor value vocabulary for the later public
// <asc/tensor_copy>.  A descriptor records, per dimension, the extent, the GM
// source element stride, the UB destination element stride and the left/right
// padding applied to the destination; the innermost dimension has index
// Rank - 1.  The descriptor holds no memory, is constructible from Host
// tiling results and inside ordinary AICore, and passes by value into a
// kernel.  Every range and stride must pass construction validation.

namespace asc {

namespace detail {

// Avoid division-based overflow tests that some BiSheng versions lower to
// an unavailable __multi3 helper. Each product below has two 32-bit factors.
// The result is written only when the full unsigned 64-bit product fits.
CANN_ASC_STL_API constexpr bool tensor_copy_checked_multiply(
    unsigned long long left, unsigned long long right, unsigned long long& result) noexcept
{
    const unsigned long long left_low = static_cast<__UINT32_TYPE__>(left);
    const unsigned long long left_high = left >> 32;
    const unsigned long long right_low = static_cast<__UINT32_TYPE__>(right);
    const unsigned long long right_high = right >> 32;
    if (left_high != 0 && right_high != 0) {
        return false;
    }
    const unsigned long long low = left_low * right_low;
    // At most one cross product is nonzero after the high/high check.
    const unsigned long long middle = left_high * right_low + left_low * right_high;
    if ((middle >> 32) != 0) {
        return false;
    }
    const unsigned long long high = (low >> 32) + middle;
    if ((high >> 32) != 0) {
        return false;
    }
    result = (high << 32) | static_cast<__UINT32_TYPE__>(low);
    return true;
}

}  // namespace detail

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

    // Accumulates (count - 1) * stride - the reach of the furthest element
    // from the base - into span, with wrap detection on both the multiply and
    // the accumulate.  Shared by validate() so a standalone validation
    // verdict covers the same stride arithmetic the transfer paths apply.
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_TENSOR_VALIDATE_OPTNONE constexpr bool accumulate_stride_span(
        unsigned long long& span, unsigned long long count, size_type stride) const noexcept
    {
        const unsigned long long reach = count - 1;
        // 除零守卫：零步长无最远元素可达，直接判溢出，下方除数永不为 0。
        if (stride == 0 || reach > ~0ULL / stride) {
            return false;
        }
        const unsigned long long contribution = reach * stride;
        if (contribution > ~0ULL - span) {
            return false;
        }
        span += contribution;
        return true;
    }

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

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_TENSOR_VALIDATE_OPTNONE constexpr tensor_copy_status validate() const noexcept
    {
        unsigned long long elements = 1;
        unsigned long long source_span = 1;
        unsigned long long destination_span = 1;
        for (unsigned dimension = 0; dimension < Rank; ++dimension) {
            if (extents_[dimension] == 0) {
                return tensor_copy_status::zero_extent;
            }
            if (source_strides_[dimension] == 0 || destination_strides_[dimension] == 0) {
                return tensor_copy_status::zero_stride;
            }
            // The ND-DMA pad counters are 8-bit hardware fields, so padding
            // above 255 is not transferable; it is rejected here instead of
            // being silently truncated by the backend narrowing.
            if (left_padding_[dimension] > size_type(255) || right_padding_[dimension] > size_type(255)) {
                return tensor_copy_status::size_overflow;
            }
            // extents_[dimension] >= 1 past the zero-extent screen above, so
            // the padded row below never re-wraps to zero in this loop.
            const unsigned long long padded = static_cast<unsigned long long>(extents_[dimension]) +
                left_padding_[dimension] + right_padding_[dimension];
            // elements *= padded 走 32 位分段乘法：旧 BiSheng 会把 64x64 乘法
            // 降级成设备侧不可用的 __multi3 链接符号。
            if (padded == 0 || !detail::tensor_copy_checked_multiply(elements, padded, elements)) {
                return tensor_copy_status::size_overflow;
            }
            if (!accumulate_stride_span(source_span, extents_[dimension], source_strides_[dimension]) ||
                !accumulate_stride_span(destination_span, padded, destination_strides_[dimension])) {
                return tensor_copy_status::size_overflow;
            }
        }
        return tensor_copy_status::success;
    }

    CANN_ASC_STL_API constexpr unsigned long long required_elements() const noexcept
    {
        unsigned long long elements = 1;
        for (unsigned dimension = 0; dimension < Rank; ++dimension) {
            // Unlike validate(), this walk carries no zero-extent screen, so
            // the zero test below is the live division guard, not a dead
            // branch: an all-zero descriptor reaches it with padded == 0.
            const unsigned long long padded = static_cast<unsigned long long>(extents_[dimension]) +
                left_padding_[dimension] + right_padding_[dimension];
            if (padded == 0 || !detail::tensor_copy_checked_multiply(elements, padded, elements)) {
                return 0;
            }
        }
        return elements;
    }

    // Destination row pitch in elements: the padded innermost row length the
    // UB stage must be sized and pitched for.  The byte width - four times
    // larger for float - is what tensor_copy_required_alignment reports; the
    // two same-named results must not be mixed up at a call site.
    CANN_ASC_STL_API constexpr size_type required_alignment() const noexcept
    {
        // The padded innermost row length decides the destination alignment the
        // caller must provide for the UB stage.
        return extents_[Rank - 1] + left_padding_[Rank - 1] + right_padding_[Rank - 1];
    }

    // A dimension outside [0, Rank) is a caller precondition violation the
    // no-status vocabulary reports nowhere: the write is silently skipped,
    // exactly as the registered dynamic-violation contract prescribes.
    // make_tensor_copy_descriptor is the sanctioned bulk writer and never
    // crosses the bound.
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
    // Byte width of the member above, computed in 64 bits because the padded
    // row (uint32 elements) times the element size can leave the 32-bit
    // result range.  Overflow reports as zero - the same sentinel convention
    // tensor_copy_required_elements already uses for its own overflow.
    const unsigned long long bytes = static_cast<unsigned long long>(descriptor.required_alignment()) * sizeof(T);
    return bytes > ~0u ? 0u : static_cast<unsigned int>(bytes);
}

}  // namespace asc

#undef CANN_ASC_STL_DETAIL_TENSOR_VALIDATE_OPTNONE

#endif  // CANN_ASC_STL_ASC___TENSOR_COPY_DESCRIPTOR_H
