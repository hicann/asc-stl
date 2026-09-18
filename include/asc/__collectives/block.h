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

#ifndef CANN_ASC_STL_ASC___COLLECTIVES_BLOCK_H
#define CANN_ASC_STL_ASC___COLLECTIVES_BLOCK_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__hierarchy/query.h>
#include <asc/__warp/operations.h>

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
#include <simt_api/device_sync_functions.h>
#endif

namespace asc::detail {

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
template <class T>
CANN_ASC_STL_SIMT_API T collective_add(T left, T right) noexcept
{
    return left + right;
}

template <class T>
CANN_ASC_STL_SIMT_API T collective_min(T left, T right) noexcept
{
    return right < left ? right : left;
}

template <class T>
CANN_ASC_STL_SIMT_API T collective_max(T left, T right) noexcept
{
    return left < right ? right : left;
}

template <class T, class Operation>
CANN_ASC_STL_SIMT_API T block_reduce_impl(T* workspace, T value, Operation operation) noexcept
{
    const auto lane = lane_id();
    const auto flat_thread = static_cast<unsigned int>(thread_index());
    const auto warp = flat_thread / warp_size;
    const auto warps = static_cast<unsigned int>(thread_count()) / warp_size;
    T warp_value = value;
    for (unsigned int offset = warp_size / 2; offset != 0; offset /= 2) {
        const T other = warp_shuffle_down_value<32>(warp_value, static_cast<int>(offset));
        if (lane + offset < warp_size) {
            warp_value = operation(warp_value, other);
        }
    }
    if (lane == 0) {
        workspace[warp] = warp_value;
    }
    asc_syncthreads();
    if (flat_thread == 0) {
        T result = workspace[0];
        for (unsigned int index = 1; index < warps; ++index) {
            result = operation(result, workspace[index]);
        }
        workspace[0] = result;
    }
    asc_syncthreads();
    return workspace[0];
}

template <class T>
CANN_ASC_STL_SIMT_API T block_reduce_add_impl(T* workspace, T value) noexcept
{
    return block_reduce_impl(workspace, value, collective_add<T>);
}

template <class T>
CANN_ASC_STL_SIMT_API T block_reduce_min_impl(T* workspace, T value) noexcept
{
    return block_reduce_impl(workspace, value, collective_min<T>);
}

template <class T>
CANN_ASC_STL_SIMT_API T block_reduce_max_impl(T* workspace, T value) noexcept
{
    return block_reduce_impl(workspace, value, collective_max<T>);
}

template <class T>
CANN_ASC_STL_SIMT_API T block_broadcast_impl(T* workspace, T value, unsigned int source_thread) noexcept
{
    if (thread_index() == source_thread) {
        workspace[0] = value;
    }
    asc_syncthreads();
    const T result = workspace[0];
    asc_syncthreads();
    return result;
}

template <class T, bool Inclusive>
CANN_ASC_STL_SIMT_API T block_scan_add_impl(T* workspace, T value) noexcept
{
    const auto lane = lane_id();
    const auto flat_thread = static_cast<unsigned int>(thread_index());
    const auto warp = flat_thread / warp_size;
    const auto warps = static_cast<unsigned int>(thread_count()) / warp_size;
    T inclusive = value;
    for (unsigned int offset = 1; offset < warp_size; offset *= 2) {
        const T other = warp_shuffle_up_value<32>(inclusive, static_cast<int>(offset));
        if (lane >= offset) {
            inclusive = other + inclusive;
        }
    }
    T exclusive{};
    if constexpr (!Inclusive) {
        const T previous = warp_shuffle_up_value<32>(inclusive, 1);
        if (lane != 0) {
            exclusive = previous;
        }
    }
    if (lane == warp_size - 1) {
        workspace[warp] = inclusive;
    }
    asc_syncthreads();
    if (flat_thread == 0) {
        T prefix{};
        for (unsigned int index = 0; index < warps; ++index) {
            const T warp_total = workspace[index];
            workspace[index] = prefix;
            prefix = prefix + warp_total;
        }
    }
    asc_syncthreads();
    const T prior_warps = workspace[warp];
    const T result = Inclusive ? prior_warps + inclusive : prior_warps + exclusive;
    asc_syncthreads();
    return result;
}

template <class T>
CANN_ASC_STL_SIMT_API T block_inclusive_scan_add_impl(T* workspace, T value) noexcept
{
    return block_scan_add_impl<T, true>(workspace, value);
}

template <class T>
CANN_ASC_STL_SIMT_API T block_exclusive_scan_add_impl(T* workspace, T value) noexcept
{
    return block_scan_add_impl<T, false>(workspace, value);
}

CANN_ASC_STL_SIMT_API bool block_all_impl(unsigned int* workspace, bool predicate) noexcept
{
    return block_reduce_min_impl(workspace, static_cast<unsigned int>(predicate)) != 0;
}

CANN_ASC_STL_SIMT_API bool block_any_impl(unsigned int* workspace, bool predicate) noexcept
{
    return block_reduce_max_impl(workspace, static_cast<unsigned int>(predicate)) != 0;
}
#endif

}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___COLLECTIVES_BLOCK_H
