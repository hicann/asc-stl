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

// Loop 0 is the innermost descriptor dimension; loops 1..4 map to the outer
// dimensions.  Dimensions beyond the rank stay at size one with zero strides
// exactly as the raw feasibility probe validated.
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
        pad_count.loop1_lp_count = static_cast<unsigned char>(descriptor.left_padding(rank - 2));
        pad_count.loop1_rp_count = static_cast<unsigned char>(descriptor.right_padding(rank - 2));
    }
    if (rank > 2) {
        pad_count.loop2_lp_count = static_cast<unsigned char>(descriptor.left_padding(rank - 3));
        pad_count.loop2_rp_count = static_cast<unsigned char>(descriptor.right_padding(rank - 3));
    }
    if (rank > 3) {
        pad_count.loop3_lp_count = static_cast<unsigned char>(descriptor.left_padding(rank - 4));
        pad_count.loop3_rp_count = static_cast<unsigned char>(descriptor.right_padding(rank - 4));
    }
    if (rank > 4) {
        pad_count.loop4_lp_count = static_cast<unsigned char>(descriptor.left_padding(rank - 5));
        pad_count.loop4_rp_count = static_cast<unsigned char>(descriptor.right_padding(rank - 5));
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

template <class Descriptor, class T>
CANN_ASC_STL_DEVICE_API void tensor_copy_load_ndim(
    __ubuf__ T* destination, __gm__ const T* source, const Descriptor& descriptor, T fill_value) noexcept
{
    static_assert(is_ndim_copy_element<T>::value, "the native ND-DMA load supports the approved element set only");
    asc_ndim_copy_dci();
    tensor_copy_configure_strides(descriptor);
    tensor_copy_configure_padding(descriptor, fill_value);
    asc_ndim_copy_gm2ub(destination, const_cast<__gm__ T*>(source), tensor_copy_loop_size(descriptor, 0),
        tensor_copy_loop_size(descriptor, 1), tensor_copy_loop_size(descriptor, 2),
        tensor_copy_loop_size(descriptor, 3), tensor_copy_loop_size(descriptor, 4),
        static_cast<unsigned char>(descriptor.left_padding(descriptor.rank() - 1)),
        static_cast<unsigned char>(descriptor.right_padding(descriptor.rank() - 1)), true,
        asc_load_l2_cache_mode::NORMAL_FIRST_VICTIM);
}

#endif  // D-SIMD transfer vocabulary

}  // namespace detail

}  // namespace asc

#endif  // CANN_ASC_STL_ASC___TENSOR_COPY_BACKEND_H
