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

#ifndef CANN_ASC_STL_ASC___RUNTIME_LAUNCH_H
#define CANN_ASC_STL_ASC___RUNTIME_LAUNCH_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/execution>
#include <asc/stream>

namespace asc::detail {

// Dimension carrier for algorithm submission: the 1-D grid geometry an
// algorithm derives from its element count. It parameterizes the
// submit_parallel_operation overload below; the asc/launch facade remains the
// single place that talks to the underlying runtime. The deliberately 1-D
// blocks/threads pair is the internal submission vocabulary and stays
// separate from the public 3-D extent3d/aicore_launch_config vocabularies:
// the parallel frontends only ever derive one linear geometry, and widening
// the carrier to three dimensions would couple every algorithm submit to the
// public launch surface for no coverage gain.
struct launch_state {
    unsigned int blocks{};
    unsigned int threads{};
};

// CANN_ASC_STL_USE_SIMT_LAUNCH is a build-time contract with no in-tree
// default: the submit channel below (and the asc::launch/asc::parallel
// surfaces gated by the same macro) exists only on __clang__ builds that
// define it through the build command line. Giving the macro a defaulted
// toolchain probe belongs in asc/__config so that every gated facade sees the
// same value; that file is outside this header's ownership, so the dependency
// is documented here instead.
#if defined(__clang__) && defined(CANN_ASC_STL_USE_SIMT_LAUNCH)
// Coordinate-parameterized companion of the asc/launch parallel_operation_
// kernel: instead of admitting only thread (0, 0, 0), every launched thread
// executes the operation with its linear thread index and the total thread
// count, so element-wise operations can visit their range grid-strided while
// order-sensitive operations keep using the single-thread channel.
template <class Operation>
#if CANN_ASC_STL_USE_SIMT_LAUNCH
__global__ void parallel_elementwise_kernel(Operation operation)
#else
__vector__ __global__ __aicore__ void parallel_elementwise_kernel(Operation operation)
#endif
{
#if CANN_ASC_STL_USE_SIMT_LAUNCH
    operation(blockIdx.x * blockDim.x + threadIdx.x, gridDim.x * blockDim.x);
#else
    if (block_idx != 0) {
        return;
    }
    operation(0, 1);
#endif
}

// Dimension-parameterized submission channel. The two-argument
// submit_parallel_operation in asc/launch keeps the historical single-thread
// contract for order-sensitive algorithms; pure element-wise algorithms
// submit through this overload with an elementwise_launch_state geometry.
// Extent authority: this channel validates only structural sanity (non-null
// stream, non-zero blocks/threads); whether a geometry fits the target device
// is adjudicated by the runtime at launch. Frontends derive conservative
// geometries (see elementwise_launch_state) whose grid-stride loops absorb
// any excess, so a device-side cap rejection can never lose coverage.
template <class Operation>
CANN_ASC_STL_HOST_API execution_status submit_parallel_operation(
    stream_ref stream, launch_state state, Operation operation) noexcept
{
    static_assert(__is_trivially_copyable(Operation), "ASC-STL parallel operation state must be trivially copyable");
    if (!stream || state.blocks == 0 || state.threads == 0) {
        return execution_status{execution_errc::invalid_argument};
    }
#if CANN_ASC_STL_USE_SIMT_LAUNCH
    dim3 grid(state.blocks, 1, 1);
    dim3 block(state.threads, 1, 1);
    parallel_elementwise_kernel<Operation><<<grid, block, 0, stream.native_handle()>>>(operation);
#else
    parallel_elementwise_kernel<Operation><<<state.blocks, 0, stream.native_handle()>>>(operation);
#endif
    return execution_status{};
}
#endif

}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___RUNTIME_LAUNCH_H
