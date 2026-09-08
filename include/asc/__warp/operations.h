/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

template <int Width, class T>
CANN_ASC_STL_SIMT_API T warp_shuffle_index(T value, int source_lane) noexcept
{
    return asc_shfl(value, source_lane, Width);
}
template <int Width>
CANN_ASC_STL_SIMT_API long long warp_shuffle_index(long long value, int source_lane) noexcept
{
    return static_cast<long long>(asc_shfl(static_cast<__INT64_TYPE__>(value), source_lane, Width));
}
template <int Width>
CANN_ASC_STL_SIMT_API unsigned long long warp_shuffle_index(unsigned long long value, int source_lane) noexcept
{
    return static_cast<unsigned long long>(asc_shfl(static_cast<__UINT64_TYPE__>(value), source_lane, Width));
}
template <int Width, class T>
CANN_ASC_STL_SIMT_API T warp_shuffle_up_value(T value, int delta) noexcept
{
    return asc_shfl_up(value, static_cast<unsigned int>(delta), Width);
}
template <int Width>
CANN_ASC_STL_SIMT_API long long warp_shuffle_up_value(long long value, int delta) noexcept
{
    return static_cast<long long>(
        asc_shfl_up(static_cast<__INT64_TYPE__>(value), static_cast<unsigned int>(delta), Width));
}
template <int Width>
CANN_ASC_STL_SIMT_API unsigned long long warp_shuffle_up_value(unsigned long long value, int delta) noexcept
{
    return static_cast<unsigned long long>(
        asc_shfl_up(static_cast<__UINT64_TYPE__>(value), static_cast<unsigned int>(delta), Width));
}
template <int Width, class T>
CANN_ASC_STL_SIMT_API T warp_shuffle_down_value(T value, int delta) noexcept
{
    return asc_shfl_down(value, static_cast<unsigned int>(delta), Width);
}
template <int Width>
CANN_ASC_STL_SIMT_API long long warp_shuffle_down_value(long long value, int delta) noexcept
{
    return static_cast<long long>(
        asc_shfl_down(static_cast<__INT64_TYPE__>(value), static_cast<unsigned int>(delta), Width));
}
template <int Width>
CANN_ASC_STL_SIMT_API unsigned long long warp_shuffle_down_value(unsigned long long value, int delta) noexcept
{
    return static_cast<unsigned long long>(
        asc_shfl_down(static_cast<__UINT64_TYPE__>(value), static_cast<unsigned int>(delta), Width));
}
template <int Width, class T>
CANN_ASC_STL_SIMT_API T warp_shuffle_xor_value(T value, int xor_mask) noexcept
{
    return asc_shfl_xor(value, xor_mask, Width);
}
template <int Width>
CANN_ASC_STL_SIMT_API long long warp_shuffle_xor_value(long long value, int xor_mask) noexcept
{
    return static_cast<long long>(asc_shfl_xor(static_cast<__INT64_TYPE__>(value), xor_mask, Width));
}
template <int Width>
CANN_ASC_STL_SIMT_API unsigned long long warp_shuffle_xor_value(unsigned long long value, int xor_mask) noexcept
{
    return static_cast<unsigned long long>(asc_shfl_xor(static_cast<__UINT64_TYPE__>(value), xor_mask, Width));
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

CANN_ASC_STL_SIMT_API bool warp_bitwise_equal(float left, float right) noexcept
{
    union bits {
        float value;
        unsigned int raw;
    } left_bits{left}, right_bits{right};
    return left_bits.raw == right_bits.raw;
}
template <class T>
CANN_ASC_STL_SIMT_API bool warp_bitwise_equal(T left, T right) noexcept
{
    return left == right;
}
#endif

}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___WARP_OPERATIONS_H
