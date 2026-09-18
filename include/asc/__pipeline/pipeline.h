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

#ifndef CANN_ASC_STL_ASC___PIPELINE_PIPELINE_H
#define CANN_ASC_STL_ASC___PIPELINE_PIPELINE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#if CANN_ASC_STL_DETAIL_SIMD_COMPILATION()

// The aggregated CANN C API owns the pipe_t/event_t vocabulary, the MTE2/MTE3
// aligned async-copy primitives and the cross-pipe event synchronization.  It
// is included only by this designated private backend so the public
// <asc/pipeline> surface stays vendor-neutral.
#include <c_api/asc_simd.h>

#endif

namespace asc::detail {

// Borrowed coordinator state: the caller owns the GM/UB storage and supplies
// one load and one store event ID per stage (at most two stages).
struct pipeline_state {
    unsigned char stages{};
    unsigned char load_events[2]{};
    unsigned char store_events[2]{};
};

#if CANN_ASC_STL_DETAIL_SIMD_COMPILATION()

CANN_ASC_STL_DEVICE_API void pipeline_load_commit(unsigned char load_event) noexcept
{
    asc_sync_notify(pipe_t::PIPE_MTE2, pipe_t::PIPE_S, static_cast<event_t>(load_event));
}

CANN_ASC_STL_DEVICE_API void pipeline_load_wait(unsigned char load_event) noexcept
{
    asc_sync_wait(pipe_t::PIPE_MTE2, pipe_t::PIPE_S, static_cast<event_t>(load_event));
}

CANN_ASC_STL_DEVICE_API void pipeline_store_release(unsigned char store_event) noexcept
{
    asc_sync_notify(pipe_t::PIPE_S, pipe_t::PIPE_MTE3, static_cast<event_t>(store_event));
}

CANN_ASC_STL_DEVICE_API void pipeline_store_wait(unsigned char store_event) noexcept
{
    asc_sync_wait(pipe_t::PIPE_S, pipe_t::PIPE_MTE3, static_cast<event_t>(store_event));
}

CANN_ASC_STL_DEVICE_API void pipeline_producer_acquire(unsigned char store_event) noexcept
{
    asc_sync_notify(pipe_t::PIPE_MTE3, pipe_t::PIPE_S, static_cast<event_t>(store_event));
    asc_sync_wait(pipe_t::PIPE_MTE3, pipe_t::PIPE_S, static_cast<event_t>(store_event));
}

CANN_ASC_STL_DEVICE_API void pipeline_drain() noexcept
{
    asc_sync_pipe(pipe_t::PIPE_ALL);
}

// Aligned asynchronous transfers for the approved scalar set.  The typed C
// API overloads resolve per element type; both ranges meet the alignment
// requirement by caller precondition.
template <class T>
CANN_ASC_STL_DEVICE_API void pipeline_copy_gm2ub(
    __ubuf__ T* destination, __gm__ const T* source, unsigned int bytes) noexcept
{
    asc_copy_gm2ub_align(destination, const_cast<__gm__ T*>(source), bytes);  // NOLINT(build/include_what_you_use)
}

template <class T>
CANN_ASC_STL_DEVICE_API void pipeline_copy_ub2gm(
    unsigned char store_event, __gm__ T* destination, __ubuf__ const T* source, unsigned int bytes) noexcept
{
    pipeline_store_wait(store_event);
    asc_copy_ub2gm_align(destination, const_cast<__ubuf__ T*>(source), bytes);  // NOLINT(build/include_what_you_use)
}

#endif

}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___PIPELINE_PIPELINE_H
