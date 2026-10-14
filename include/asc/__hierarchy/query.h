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

#ifndef CANN_ASC_STL_ASC___HIERARCHY_QUERY_H
#define CANN_ASC_STL_ASC___HIERARCHY_QUERY_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
#include <simt_api/device_functions.h>
#elif CANN_ASC_STL_DETAIL_SIMD_COMPILATION()
// Optional: some CANN packages (for example the bare 9.2.0-beta.2 install on
// the CI machine) ship the compiler headers without this sysvar header; the
// block identifiers used below are provided by the rest of the cce runtime
// include set either way, so a missing header is not an error.
#if defined(__has_include)
#if __has_include(<c_api/utils/sys_var.h>)
#include <c_api/utils/sys_var.h>
#elif __has_include(<c_api/sys_var/sys_var.h>)
#include <c_api/sys_var/sys_var.h>
#endif
#endif
#endif

// The lane-id primitive laneid() ships with CANN >= 9.2: the 9.0 toolkit's
// simt_api/device_functions.h does not declare it, and using it there fails
// with an undeclared-identifier error deep inside this header. A build on
// such a toolkit defines CANN_ASC_STL_DETAIL_NO_SIMT_LANEID to get a clear,
// actionable error up front instead of the bare compiler failure; the
// lane_id()/warp_index() queries genuinely require the primitive, so on an
// old toolkit the only correct answer is the explicit one below.
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION() && defined(CANN_ASC_STL_DETAIL_NO_SIMT_LANEID)
#error "asc/hierarchy lane_id()/warp_index() require the laneid() primitive (CANN >= 9.2); "
"upgrade the toolkit or avoid these queries"
#endif

    namespace asc
{
#if defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
#define CANN_ASC_STL_DETAIL_HIERARCHY_VALUE_API __host__ __aicore__ CANN_ASC_STL_DETAIL_VISIBILITY_HIDDEN inline
#else
#define CANN_ASC_STL_DETAIL_HIERARCHY_VALUE_API CANN_ASC_STL_API
#endif

    struct thread_level {};
    struct warp_level {};
    struct block_level {};
    struct grid_level {};
    inline constexpr thread_level thread{};
    inline constexpr warp_level warp{};
    inline constexpr block_level block{};
    inline constexpr grid_level grid{};
    inline constexpr unsigned int warp_size = 32;

    struct extent3d {
        unsigned int x;
        unsigned int y;
        unsigned int z;
        CANN_ASC_STL_DETAIL_HIERARCHY_VALUE_API constexpr extent3d(
            unsigned int x_value = 1, unsigned int y_value = 1, unsigned int z_value = 1) noexcept
            : x(x_value), y(y_value), z(z_value)
        {}
        // Precondition: per-axis extents stay within hardware launch limits
        // (each axis well below 2^21 on current Ascend parts), so the 64-bit
        // three-axis product cannot wrap. The axes are deliberately 32-bit to
        // halve device-side index arithmetic; a hypothetical product beyond
        // 2^64 is outside every supported launch configuration.
        CANN_ASC_STL_DETAIL_HIERARCHY_VALUE_API constexpr unsigned long long count() const noexcept
        {
            return static_cast<unsigned long long>(x) * y * z;
        }
        CANN_ASC_STL_DETAIL_HIERARCHY_VALUE_API constexpr bool operator==(extent3d other) const noexcept
        {
            return x == other.x && y == other.y && z == other.z;
        }
        CANN_ASC_STL_DETAIL_HIERARCHY_VALUE_API constexpr bool operator!=(extent3d other) const noexcept
        {
            return !(*this == other);
        }
    };

    template <class Level>
    struct level_dimensions {
        extent3d extents;
    };
    CANN_ASC_STL_DETAIL_HIERARCHY_VALUE_API constexpr level_dimensions<grid_level> grid_dims(extent3d value) noexcept
    {
        return {value};
    }
    CANN_ASC_STL_DETAIL_HIERARCHY_VALUE_API constexpr level_dimensions<block_level> block_dims(extent3d value) noexcept
    {
        return {value};
    }
    template <unsigned int X, unsigned int Y = 1, unsigned int Z = 1>
    CANN_ASC_STL_DETAIL_HIERARCHY_VALUE_API constexpr level_dimensions<grid_level> grid_dims() noexcept
    {
        return {{X, Y, Z}};
    }
    template <unsigned int X, unsigned int Y = 1, unsigned int Z = 1>
    CANN_ASC_STL_DETAIL_HIERARCHY_VALUE_API constexpr level_dimensions<block_level> block_dims() noexcept
    {
        return {{X, Y, Z}};
    }

    struct simt_hierarchy {
        extent3d grid_extents;
        extent3d block_extents;
        CANN_ASC_STL_DETAIL_HIERARCHY_VALUE_API constexpr extent3d extents(grid_level) const noexcept
        {
            return grid_extents;
        }
        CANN_ASC_STL_DETAIL_HIERARCHY_VALUE_API constexpr extent3d extents(block_level) const noexcept
        {
            return block_extents;
        }
        CANN_ASC_STL_DETAIL_HIERARCHY_VALUE_API constexpr unsigned long long count(grid_level) const noexcept
        {
            return grid_extents.count();
        }
        CANN_ASC_STL_DETAIL_HIERARCHY_VALUE_API constexpr unsigned long long count(block_level) const noexcept
        {
            return block_extents.count();
        }
    };
    CANN_ASC_STL_DETAIL_HIERARCHY_VALUE_API constexpr simt_hierarchy make_hierarchy(
        level_dimensions<grid_level> grid_value, level_dimensions<block_level> block_value) noexcept
    {
        return {grid_value.extents, block_value.extents};
    }
    struct launch_dimensions {
        extent3d grid;
        extent3d block;
    };
    CANN_ASC_STL_DETAIL_HIERARCHY_VALUE_API constexpr launch_dimensions get_launch_dimensions(
        simt_hierarchy hierarchy) noexcept
    {
        return {hierarchy.grid_extents, hierarchy.block_extents};
    }

#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    CANN_ASC_STL_DEVICE_API unsigned long long block_index() noexcept
    {
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
        return static_cast<unsigned long long>(blockIdx.x);
#else
        return static_cast<unsigned long long>(block_idx);
#endif
    }

    CANN_ASC_STL_DEVICE_API unsigned long long block_count() noexcept
    {
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
        // Same hardware launch-limit precondition as extent3d::count: the three
        // 32-bit axes cannot produce a wrapping 64-bit product on real grids.
        return static_cast<unsigned long long>(gridDim.x) * gridDim.y * gridDim.z;
#else
        return static_cast<unsigned long long>(block_num);
#endif
    }

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    CANN_ASC_STL_DEVICE_API extent3d thread_index_3d() noexcept
    {
        return {threadIdx.x, threadIdx.y, threadIdx.z};
    }
    CANN_ASC_STL_DEVICE_API extent3d thread_extents_3d() noexcept
    {
        return {blockDim.x, blockDim.y, blockDim.z};
    }
    CANN_ASC_STL_DEVICE_API extent3d block_index_3d() noexcept
    {
        return {blockIdx.x, blockIdx.y, blockIdx.z};
    }
    CANN_ASC_STL_DEVICE_API extent3d block_extents_3d() noexcept
    {
        return {gridDim.x, gridDim.y, gridDim.z};
    }
    CANN_ASC_STL_DEVICE_API unsigned long long thread_index() noexcept
    {
        return threadIdx.x +
            static_cast<unsigned long long>(blockDim.x) *
            (threadIdx.y + static_cast<unsigned long long>(blockDim.y) * threadIdx.z);
    }
    CANN_ASC_STL_DEVICE_API unsigned long long thread_count() noexcept
    {
        // Same hardware launch-limit precondition as extent3d::count.
        return static_cast<unsigned long long>(blockDim.x) * blockDim.y * blockDim.z;
    }
    CANN_ASC_STL_DEVICE_API unsigned int lane_id() noexcept
    {
        return static_cast<unsigned int>(laneid());
    }
    CANN_ASC_STL_DEVICE_API unsigned int warp_index() noexcept
    {
        return static_cast<unsigned int>(thread_index() / warp_size);
    }
    CANN_ASC_STL_DEVICE_API unsigned int warp_count() noexcept
    {
        return static_cast<unsigned int>((thread_count() + warp_size - 1) / warp_size);
    }
#else
    CANN_ASC_STL_DEVICE_API unsigned int sub_block_index() noexcept
    {
#if defined(__has_include) && __has_include(<c_api/utils/sys_var.h>)
        return static_cast<unsigned int>(asc_get_sub_block_id());
#else
        // Some CANN builds expose the sub-block query under the un-prefixed
        // name instead; pick whichever this toolkit declares.
        return static_cast<unsigned int>(get_subblockid());
#endif
    }
    CANN_ASC_STL_DEVICE_API unsigned int sub_block_count() noexcept
    {
#if defined(__has_include) && __has_include(<c_api/utils/sys_var.h>)
        return static_cast<unsigned int>(asc_get_sub_block_num());
#else
        // Same naming drift as sub_block_index: this toolkit exposes the
        // sub-block count as the dimension intrinsic.
        return static_cast<unsigned int>(get_subblockdim());
#endif
    }
#endif
#endif

    namespace detail {
    CANN_ASC_STL_API constexpr unsigned int hierarchy_zero() noexcept
    {
        return 0;
    }
    }  // namespace detail

#undef CANN_ASC_STL_DETAIL_HIERARCHY_VALUE_API

}  // namespace asc

#endif  // CANN_ASC_STL_ASC___HIERARCHY_QUERY_H
