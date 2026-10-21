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

#ifndef CANN_ASC_STL_ASC___TENSOR_COPY_BACKEND_H
#define CANN_ASC_STL_ASC___TENSOR_COPY_BACKEND_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

// Multidimensional asynchronous GM-to-UB transfer backend for the later public
// <asc/tensor_copy>.  The ND-DMA C API exists only in ordinary AICore, so the
// transfer vocabulary is compiled exclusively in D-SIMD; the element gating
// remains visible everywhere for Host validation.  The first native element
// set is int8/uint8/int16/uint16/int32/uint32/float; no 64-bit or unapproved
// low-precision overload exists, and visibility after the transfer is owned
// by the pipeline event contract rather than by this backend.  This root
// shares one delivery unit with the descriptor root and therefore cannot
// include it: the transfer functions are generic over the descriptor
// interface (rank/extent/source_stride/destination_stride/left_padding/
// right_padding) so both roots stay self-contained.

#if CANN_ASC_STL_DETAIL_SIMD_COMPILATION()
// The load-cache vocabulary is a scoped enum the delivery unit owns; it is
// included by name instead of relying on the transfer header's impl chain
// leaking it, so this root stays self-sufficient.
#include <c_api/utils/enum.h>
#include <c_api/vector_datamove/vector_datamove.h>
#endif

namespace asc {

namespace detail {

template <class T>
struct is_ndim_copy_element {
    static constexpr bool value = false;
};

#define CANN_ASC_STL_DETAIL_NDIM_ELEMENT(...)  \
    template <>                                \
    struct is_ndim_copy_element<__VA_ARGS__> { \
        static constexpr bool value = true;    \
    };
CANN_ASC_STL_DETAIL_NDIM_ELEMENT(__INT8_TYPE__)
CANN_ASC_STL_DETAIL_NDIM_ELEMENT(__UINT8_TYPE__)
CANN_ASC_STL_DETAIL_NDIM_ELEMENT(__INT16_TYPE__)
CANN_ASC_STL_DETAIL_NDIM_ELEMENT(__UINT16_TYPE__)
CANN_ASC_STL_DETAIL_NDIM_ELEMENT(__INT32_TYPE__)
CANN_ASC_STL_DETAIL_NDIM_ELEMENT(__UINT32_TYPE__)
CANN_ASC_STL_DETAIL_NDIM_ELEMENT(float)
#undef CANN_ASC_STL_DETAIL_NDIM_ELEMENT

#if CANN_ASC_STL_DETAIL_SIMD_COMPILATION()

// The ND-DMA pad counters are 8-bit hardware fields.  Descriptor validation
// rejects padding above 255 before any transfer path reaches this
// narrowing, and the guard below keeps the narrowing contract-checked even
// for callers that bypass validate(), so a value of 300 can no longer
// silently deform into 44.  The parameter keeps the descriptor's own size
// type: this root cannot include the descriptor root, so the narrowing is
// generic over the value exactly like the transfer functions around it.
template <class SizeType>
CANN_ASC_STL_DEVICE_API unsigned char tensor_copy_padding_count(SizeType padding) noexcept
{
    if (static_cast<unsigned long long>(padding) > 255ull) {
        // The cce back end lowers builtin traps to an uncallable abort symbol; an
        // invalid volatile store emits the device fault instead.
        *reinterpret_cast<volatile unsigned char*>(-1) = 0;
        for (;;) {
        }
    }
    return static_cast<unsigned char>(padding);
}

// Loop 0 is the innermost descriptor dimension; loops 1..4 map to the outer
// dimensions.  Dimensions beyond the rank stay at size one with zero strides
// exactly as the raw feasibility probe validated.  The descriptor's own
// Rank static_assert (1..5) is the first line of defense; the load entry
// below adds the runtime mirror of that bound for generic descriptors that
// bypass the in-tree class, because the five-loop transfer vocabulary would
// silently truncate a wider rank instead of failing.
template <class Descriptor>
CANN_ASC_STL_DEVICE_API void tensor_copy_configure_strides(const Descriptor& descriptor) noexcept
{
    const unsigned rank = descriptor.rank();
    asc_set_ndim_loop0_stride(descriptor.destination_stride(rank - 1), descriptor.source_stride(rank - 1));
    asc_set_ndim_loop1_stride(
        rank > 1 ? descriptor.destination_stride(rank - 2) : 0, rank > 1 ? descriptor.source_stride(rank - 2) : 0);
    asc_set_ndim_loop2_stride(
        rank > 2 ? descriptor.destination_stride(rank - 3) : 0, rank > 2 ? descriptor.source_stride(rank - 3) : 0);
    asc_set_ndim_loop3_stride(
        rank > 3 ? descriptor.destination_stride(rank - 4) : 0, rank > 3 ? descriptor.source_stride(rank - 4) : 0);
    asc_set_ndim_loop4_stride(
        rank > 4 ? descriptor.destination_stride(rank - 5) : 0, rank > 4 ? descriptor.source_stride(rank - 5) : 0);
}

template <class Descriptor, class T>
CANN_ASC_STL_DEVICE_API void tensor_copy_configure_padding(const Descriptor& descriptor, T fill_value) noexcept
{
    const unsigned rank = descriptor.rank();
    asc_ndim_pad_count_config pad_count{};
    if (rank > 1) {
        pad_count.loop1_lp_count = tensor_copy_padding_count(descriptor.left_padding(rank - 2));
        pad_count.loop1_rp_count = tensor_copy_padding_count(descriptor.right_padding(rank - 2));
    }
    if (rank > 2) {
        pad_count.loop2_lp_count = tensor_copy_padding_count(descriptor.left_padding(rank - 3));
        pad_count.loop2_rp_count = tensor_copy_padding_count(descriptor.right_padding(rank - 3));
    }
    if (rank > 3) {
        pad_count.loop3_lp_count = tensor_copy_padding_count(descriptor.left_padding(rank - 4));
        pad_count.loop3_rp_count = tensor_copy_padding_count(descriptor.right_padding(rank - 4));
    }
    if (rank > 4) {
        pad_count.loop4_lp_count = tensor_copy_padding_count(descriptor.left_padding(rank - 5));
        pad_count.loop4_rp_count = tensor_copy_padding_count(descriptor.right_padding(rank - 5));
    }
    asc_set_ndim_pad_count(pad_count);
    asc_set_ndim_pad_value(fill_value);
}

template <class Descriptor>
CANN_ASC_STL_DEVICE_API __UINT32_TYPE__ tensor_copy_loop_size(
    const Descriptor& descriptor, unsigned loop_index) noexcept
{
    const unsigned rank = descriptor.rank();
    if (loop_index == 0) {
        return descriptor.extent(rank - 1);
    }
    return loop_index < rank ? descriptor.extent(rank - 1 - loop_index) : 1;
}

// The borrowed C API aligned-transfer contract: every datablock both
// endpoints address must sit on the engine's 32-byte boundary (the C API's
// single-datablock size, the same contract the reference implementation's
// aligned checks anchor on).  The public load entry turns a violated
// boundary into a status return instead of issuing a misaligned transfer;
// row-level pitch guidance is what descriptor.required_alignment() reports.
inline constexpr unsigned int tensor_copy_datablock_bytes = 32;

template <class T>
CANN_ASC_STL_DEVICE_API bool tensor_copy_address_aligned(const T* address) noexcept
{
    return reinterpret_cast<unsigned long long>(address) % tensor_copy_datablock_bytes == 0;
}

// The load's L2 cache policy defaults to first-victim - the streaming-staging
// default, since a stage buffer is read once per round and has no residency
// reuse to exploit.  The defaulted parameter is the internal selection point
// for callers whose global-memory read pattern justifies another policy; the
// registered public signatures stay untouched.
template <class Descriptor, class T>
CANN_ASC_STL_DEVICE_API void tensor_copy_load_ndim(__ubuf__ T* destination, __gm__ const T* source,
    const Descriptor& descriptor, T fill_value,
    asc_load_l2_cache_mode cache_mode = asc_load_l2_cache_mode::NORMAL_FIRST_VICTIM) noexcept
{
    static_assert(is_ndim_copy_element<T>::value, "the native ND-DMA load supports the approved element set only");
    const unsigned rank = descriptor.rank();
    if (rank == 0 || rank > 5) {
        // The odometer-style loop vocabulary addresses exactly five loops;
        // a rank outside 1..5 cannot be transferred and traps here rather
        // than silently truncating the outer dimensions.
        // The cce back end lowers builtin traps to an uncallable abort symbol; an
        // invalid volatile store emits the device fault instead.
        *reinterpret_cast<volatile unsigned char*>(-1) = 0;
        for (;;) {
        }
    }
    asc_ndim_copy_dci();
    tensor_copy_configure_strides(descriptor);
    tensor_copy_configure_padding(descriptor, fill_value);
    asc_ndim_copy_gm2ub(destination, const_cast<__gm__ T*>(source), tensor_copy_loop_size(descriptor, 0),
        tensor_copy_loop_size(descriptor, 1), tensor_copy_loop_size(descriptor, 2),
        tensor_copy_loop_size(descriptor, 3), tensor_copy_loop_size(descriptor, 4),
        tensor_copy_padding_count(descriptor.left_padding(descriptor.rank() - 1)),
        tensor_copy_padding_count(descriptor.right_padding(descriptor.rank() - 1)), true, cache_mode);
}

// UB-to-GM mirror of the load path above.  The ND-DMA engine only exists in
// the GM-to-UB direction, so the store decomposes the transfer into its
// contiguous innermost runs: an odometer walks the outer dimensions, each
// padded unified-buffer row is read past its left padding (the padding fill
// is simply skipped, never transferred), and every run is issued through the
// linear aligned copy the borrowed pipeline backend already uses for this
// direction - the length is a 32-bit byte count and both endpoints must meet
// the C API alignment requirement by caller precondition, exactly as for
// pipeline copy_async.  A strided innermost dimension cannot form a burst and
// falls back to an element-wise loop.  Offsets accumulate in 64 bits; the
// public entry validates that the innermost run length fits the 32-bit byte
// count before reaching this backend.  Descriptors describe at most rank 5,
// matching the load path's loop budget.
template <class Descriptor, class T>
CANN_ASC_STL_DEVICE_API void tensor_copy_store_ndim(
    __gm__ T* destination, __ubuf__ const T* source, const Descriptor& descriptor) noexcept
{
    static_assert(is_ndim_copy_element<T>::value, "the native UB-to-GM store supports the approved element set only");
    const unsigned rank = descriptor.rank();
    if (rank > 5) {
        // The odometer indices cover the load path's five-loop budget; a
        // wider generic descriptor is outside the product contract and traps
        // instead of walking out of bounds.
        // The cce back end lowers builtin traps to an uncallable abort symbol; an
        // invalid volatile store emits the device fault instead.
        *reinterpret_cast<volatile unsigned char*>(-1) = 0;
        for (;;) {
        }
    }
    const unsigned outer = rank - 1;
    const bool contiguous = descriptor.source_stride(rank - 1) == 1 && descriptor.destination_stride(rank - 1) == 1;
    const __UINT32_TYPE__ run_length = descriptor.extent(rank - 1);
    const unsigned int run_bytes = static_cast<unsigned int>(static_cast<unsigned long long>(run_length) * sizeof(T));
    __UINT32_TYPE__ indices[5]{};
    for (;;) {
        unsigned long long source_offset = static_cast<unsigned long long>(descriptor.left_padding(rank - 1)) *
            descriptor.destination_stride(rank - 1);
        unsigned long long destination_offset = 0;
        for (unsigned dimension = 0; dimension < outer; ++dimension) {
            source_offset +=
                (static_cast<unsigned long long>(descriptor.left_padding(dimension)) + indices[dimension]) *
                descriptor.destination_stride(dimension);
            destination_offset +=
                static_cast<unsigned long long>(indices[dimension]) * descriptor.source_stride(dimension);
        }
        if (contiguous) {
            asc_copy_ub2gm_align(destination + destination_offset, const_cast<__ubuf__ T*>(source + source_offset),
                run_bytes);  // NOLINT(build/include_what_you_use)
        } else {
            for (__UINT32_TYPE__ element = 0; element < run_length; ++element) {
                destination[destination_offset +
                    static_cast<unsigned long long>(element) * descriptor.source_stride(rank - 1)] =
                    source[source_offset +
                        static_cast<unsigned long long>(element) * descriptor.destination_stride(rank - 1)];
            }
        }
        unsigned int dimension = outer;
        bool wrapped = true;
        while (dimension > 0) {
            --dimension;
            if (++indices[dimension] < descriptor.extent(dimension)) {
                wrapped = false;
                break;
            }
            indices[dimension] = 0;
        }
        if (wrapped) {
            break;
        }
    }
}

#endif  // D-SIMD transfer vocabulary

}  // namespace detail

}  // namespace asc

#endif  // CANN_ASC_STL_ASC___TENSOR_COPY_BACKEND_H
