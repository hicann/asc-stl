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

#ifndef CANN_ASC_STL_ASC___WARP_OPERATIONS_H
#define CANN_ASC_STL_ASC___WARP_OPERATIONS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
#include <simt_api/device_warp_functions.h>
#endif

namespace asc::detail {

using warp_mask = unsigned int;

CANN_ASC_STL_API constexpr bool warp_lane_is_active(warp_mask mask, unsigned int lane) noexcept
{
    return lane < 32U && (mask & (warp_mask{1} << lane)) != 0;
}

CANN_ASC_STL_API constexpr warp_mask warp_lower_lanes(unsigned int lane) noexcept
{
    return lane == 0 ? 0 : (lane >= 32U ? ~warp_mask{0} : (warp_mask{1} << lane) - 1U);
}

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
CANN_ASC_STL_SIMT_API warp_mask warp_active_mask() noexcept
{
    return asc_activemask();
}

// A shuffle may only read the register file of a lane that is running: the
// primitive returns an unspecified value when the source lane is absent from
// the hardware active mask, and match-style consumers turn that garbage into
// spurious equality hits (a false match bit). Converge the requested source
// against the active mask and redirect it to the anchor lane - the lowest
// active lane, located with ctz exactly as in the reference warp_match
// implementation - whenever the source is not currently running. Redirection
// keeps every issued shuffle on a live register, so consumers observe either
// the requested source's value or a well-defined anchor value, never an
// unspecified one. Directional shuffles (up/down/xor) derive their source
// from lane arithmetic inside the primitive and stay under the caller's
// validity contract.
CANN_ASC_STL_SIMT_API int warp_converged_source(int source_lane) noexcept
{
    const warp_mask active = warp_active_mask();
    if (source_lane >= 0 && source_lane < 32 && warp_lane_is_active(active, static_cast<unsigned int>(source_lane))) {
        return source_lane;
    }
    return active != 0 ? __builtin_ctz(active) : source_lane;
}

CANN_ASC_STL_SIMT_API bool warp_vote_all(bool value) noexcept
{
    return asc_all(value ? 1 : 0) != 0;
}
CANN_ASC_STL_SIMT_API bool warp_vote_any(bool value) noexcept
{
    return asc_any(value ? 1 : 0) != 0;
}
CANN_ASC_STL_SIMT_API warp_mask warp_vote_ballot(bool value) noexcept
{
    return asc_ballot(value ? 1 : 0);
}

// Shuffle family. The hardware primitives only accept the 32/64-bit integer
// and float registers, so every trivially copyable scalar up to 8 bytes
// (double, half, pointers, smaller integers) is transported through the
// same-width integer register with bit-preserving __builtin_memcpy in both
// directions; anything larger fails to compile instead of silently
// truncating. The reinterpretation is value-preserving, so the directional
// variants keep their exact per-lane semantics.
template <int Width, class T>
CANN_ASC_STL_SIMT_API T warp_shuffle_index(T value, int source_lane) noexcept
{
    static_assert(sizeof(T) <= 8, "warp shuffle supports scalar values up to 8 bytes");
    if constexpr (sizeof(T) == 4) {
        unsigned int raw = 0;
        __builtin_memcpy(&raw, &value, sizeof(T));
        const unsigned int transported = asc_shfl(raw, warp_converged_source(source_lane), Width);
        T result;
        __builtin_memcpy(&result, &transported, sizeof(T));
        return result;
    } else {
        __UINT64_TYPE__ raw = 0;
        __builtin_memcpy(&raw, &value, sizeof(T));
        const __UINT64_TYPE__ transported = asc_shfl(raw, warp_converged_source(source_lane), Width);
        T result;
        __builtin_memcpy(&result, &transported, sizeof(T));
        return result;
    }
}
template <int Width, class T>
CANN_ASC_STL_SIMT_API T warp_shuffle_up_value(T value, int delta) noexcept
{
    static_assert(sizeof(T) <= 8, "warp shuffle supports scalar values up to 8 bytes");
    const unsigned int count = static_cast<unsigned int>(delta);
    if constexpr (sizeof(T) == 4) {
        unsigned int raw = 0;
        __builtin_memcpy(&raw, &value, sizeof(T));
        const unsigned int transported = asc_shfl_up(raw, count, Width);
        T result;
        __builtin_memcpy(&result, &transported, sizeof(T));
        return result;
    } else {
        __UINT64_TYPE__ raw = 0;
        __builtin_memcpy(&raw, &value, sizeof(T));
        const __UINT64_TYPE__ transported = asc_shfl_up(raw, count, Width);
        T result;
        __builtin_memcpy(&result, &transported, sizeof(T));
        return result;
    }
}
template <int Width, class T>
CANN_ASC_STL_SIMT_API T warp_shuffle_down_value(T value, int delta) noexcept
{
    static_assert(sizeof(T) <= 8, "warp shuffle supports scalar values up to 8 bytes");
    const unsigned int count = static_cast<unsigned int>(delta);
    if constexpr (sizeof(T) == 4) {
        unsigned int raw = 0;
        __builtin_memcpy(&raw, &value, sizeof(T));
        const unsigned int transported = asc_shfl_down(raw, count, Width);
        T result;
        __builtin_memcpy(&result, &transported, sizeof(T));
        return result;
    } else {
        __UINT64_TYPE__ raw = 0;
        __builtin_memcpy(&raw, &value, sizeof(T));
        const __UINT64_TYPE__ transported = asc_shfl_down(raw, count, Width);
        T result;
        __builtin_memcpy(&result, &transported, sizeof(T));
        return result;
    }
}
template <int Width, class T>
CANN_ASC_STL_SIMT_API T warp_shuffle_xor_value(T value, int xor_mask) noexcept
{
    static_assert(sizeof(T) <= 8, "warp shuffle supports scalar values up to 8 bytes");
    if constexpr (sizeof(T) == 4) {
        unsigned int raw = 0;
        __builtin_memcpy(&raw, &value, sizeof(T));
        const unsigned int transported = asc_shfl_xor(raw, xor_mask, Width);
        T result;
        __builtin_memcpy(&result, &transported, sizeof(T));
        return result;
    } else {
        __UINT64_TYPE__ raw = 0;
        __builtin_memcpy(&raw, &value, sizeof(T));
        const __UINT64_TYPE__ transported = asc_shfl_xor(raw, xor_mask, Width);
        T result;
        __builtin_memcpy(&result, &transported, sizeof(T));
        return result;
    }
}
template <class T>
CANN_ASC_STL_SIMT_API T warp_reduce_add_value(T value) noexcept
{
    return asc_reduce_add(value);
}
template <class T>
CANN_ASC_STL_SIMT_API T warp_reduce_min_value(T value) noexcept
{
    return asc_reduce_min(value);
}
template <class T>
CANN_ASC_STL_SIMT_API T warp_reduce_max_value(T value) noexcept
{
    return asc_reduce_max(value);
}

// Bit-level equality for match-style consumers. Union type punning is
// undefined behavior in C++; read the object representation through
// __builtin_memcpy instead. Floating types must not fall back to == :
// +0.0/-0.0 and NaNs are bit-distinct patterns that == collapses or
// always-rejects.
CANN_ASC_STL_SIMT_API bool warp_bitwise_equal(float left, float right) noexcept
{
    unsigned int left_raw = 0;
    unsigned int right_raw = 0;
    __builtin_memcpy(&left_raw, &left, sizeof(left));
    __builtin_memcpy(&right_raw, &right, sizeof(right));
    return left_raw == right_raw;
}
CANN_ASC_STL_SIMT_API bool warp_bitwise_equal(double left, double right) noexcept
{
    __UINT64_TYPE__ left_raw = 0;
    __UINT64_TYPE__ right_raw = 0;
    __builtin_memcpy(&left_raw, &left, sizeof(left));
    __builtin_memcpy(&right_raw, &right, sizeof(right));
    return left_raw == right_raw;
}
template <class T>
CANN_ASC_STL_SIMT_API bool warp_bitwise_equal(T left, T right) noexcept
{
    // Integral (and pointer-like) operands only: for these, == is exactly
    // bitwise equality. Floating operands resolve to the overloads above.
    return left == right;
}
#endif

}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___WARP_OPERATIONS_H
