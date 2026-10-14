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

// The borrowed CANN C API owns the pipe_t/event_t vocabulary, the MTE2/MTE3
// aligned async-copy primitives and the cross-pipe event synchronization.  It
// is included only by this designated private backend so the public
// <asc/pipeline> surface stays vendor-neutral.  The split delivery-unit
// headers are the precise, stable SDK surface (the same pair the reference
// implementation consumes); the coarser c_api/asc_simd.h aggregate exists on
// the pinned SDK and pulls in both split headers among a dozen unrelated
// units, so the split pair is provably equivalent on it while parsing far
// less and staying independent of the aggregate's per-delivery composition.
#include <c_api/sync/sync.h>
#include <c_api/vector_datamove/vector_datamove.h>

#endif

namespace asc::detail {

// Element gating for the typed asynchronous transfers, mirrored from the
// tensor-copy backend (this root shares no delivery unit with that root, so
// the seven-line trait is duplicated rather than included).  The borrowed C
// API overloads exist for exactly the approved scalar set, so the public
// copy_async templates reject every other element type at the call site
// instead of failing deep inside the C API layer.  Host-visible on purpose:
// the trait doubles as the Host-side validation of the approved set.
template <class T>
struct is_pipeline_copy_element {
    static constexpr bool value = false;
};

#define CANN_ASC_STL_DETAIL_PIPELINE_ELEMENT(...)  \
    template <>                                    \
    struct is_pipeline_copy_element<__VA_ARGS__> { \
        static constexpr bool value = true;        \
    };
CANN_ASC_STL_DETAIL_PIPELINE_ELEMENT(__INT8_TYPE__)
CANN_ASC_STL_DETAIL_PIPELINE_ELEMENT(__UINT8_TYPE__)
CANN_ASC_STL_DETAIL_PIPELINE_ELEMENT(__INT16_TYPE__)
CANN_ASC_STL_DETAIL_PIPELINE_ELEMENT(__UINT16_TYPE__)
CANN_ASC_STL_DETAIL_PIPELINE_ELEMENT(__INT32_TYPE__)
CANN_ASC_STL_DETAIL_PIPELINE_ELEMENT(__UINT32_TYPE__)
CANN_ASC_STL_DETAIL_PIPELINE_ELEMENT(float)
#undef CANN_ASC_STL_DETAIL_PIPELINE_ELEMENT

// Borrowed coordinator state: the caller owns the GM/UB storage and supplies
// one load and one store event ID per stage (at most two stages).  Event IDs
// keep the unsigned int width of the public pipeline_event_id through every
// storage; the only narrowing happens at the C API boundary into event_t,
// whose probe-validated budget is the four slots 0..3.
//
// Event channel allocation matrix (per pipeline instance):
//
//   channel        direction   event numbers                  pairing
//   -------------- ----------- ------------------------------ ----------------------------------
//   load issued    MTE2 -> S   caller load_event per stage     producer_commit -> consumer_wait
//   store issued   S -> MTE3   caller store_event per stage    consumer_release -> store_wait
//   store drained  MTE3 -> S   derived drain slot (shared)     producer_acquire notify+wait self-pair
//   WAR recycle    S -> MTE2   derived WAR slot (shared)       producer_acquire notify+wait self-pair
//
// The hardware names a flag by the (source pipe, destination pipe, event id)
// triple - the C API's own HardEvent vocabulary enumerates S_MTE2, MTE2_S,
// S_MTE3 and MTE3_S as distinct channels - but the on-device probes behind
// the borrowed backend only ever exercised each id in a single direction, so
// this coordinator keeps the two S <-> MTE3 directions on independent ids:
// the drain slot (MTE3 -> S) never reuses a caller store_event (S -> MTE3).
// Both derived channels are consumed as notify+wait self-pairs, so one id per
// channel serves every stage without cross-site identity.  Construction
// derives them as the first ids in 0..3 that no caller event occupies; when a
// two-stage pipeline's four caller events already fill 0..3, the documented
// direction-scoped fallback applies (drain <- load_event0 on MTE3 -> S, WAR <-
// load_event1 on S -> MTE2).  Every (source, destination, id) triple stays
// unique in all cases, and no S <-> MTE3 id is shared across its directions.
struct pipeline_state {
    unsigned char stages{};
    unsigned int load_events[2]{};
    unsigned int store_events[2]{};
    unsigned int drain_event{};
    unsigned int war_event{};
};

CANN_ASC_STL_API constexpr bool pipeline_event_reserved(
    const unsigned int* reserved, unsigned int count, unsigned int id) noexcept
{
    for (unsigned int index = 0; index < count; ++index) {
        if (reserved[index] == id) {
            return true;
        }
    }
    return false;
}

// Derivation of the shared drain (MTE3 -> S) and WAR-recycle (S -> MTE2)
// slots described in the allocation matrix above.  A one-stage pipeline
// always leaves at least two of the four budget slots free, so both derived
// ids stay clear of every caller event; only a two-stage pipeline whose
// caller events fill 0..3 reaches the fallback assignments.
CANN_ASC_STL_API constexpr void pipeline_allocate_auxiliary_events(unsigned char stages,
    const unsigned int (&load_events)[2], const unsigned int (&store_events)[2], unsigned int& drain_event,
    unsigned int& war_event) noexcept
{
    const unsigned int reserved[4] = {load_events[0], store_events[0], load_events[1], store_events[1]};
    const unsigned int count = static_cast<unsigned int>(stages) * 2u;
    drain_event = load_events[0];
    war_event = stages > 1 ? load_events[1] : load_events[0];
    bool drain_assigned = false;
    bool war_assigned = false;
    for (unsigned int id = 0; id < 4u; ++id) {
        if (pipeline_event_reserved(reserved, count, id)) {
            continue;
        }
        if (!drain_assigned) {
            drain_event = id;
            drain_assigned = true;
        } else if (!war_assigned) {
            war_event = id;
            war_assigned = true;
        }
    }
}

#if CANN_ASC_STL_DETAIL_SIMD_COMPILATION()

CANN_ASC_STL_DEVICE_API void pipeline_load_commit(unsigned int load_event) noexcept
{
    asc_sync_notify(pipe_t::PIPE_MTE2, pipe_t::PIPE_S, static_cast<event_t>(load_event));
}

CANN_ASC_STL_DEVICE_API void pipeline_load_wait(unsigned int load_event) noexcept
{
    asc_sync_wait(pipe_t::PIPE_MTE2, pipe_t::PIPE_S, static_cast<event_t>(load_event));
}

CANN_ASC_STL_DEVICE_API void pipeline_store_release(unsigned int store_event) noexcept
{
    asc_sync_notify(pipe_t::PIPE_S, pipe_t::PIPE_MTE3, static_cast<event_t>(store_event));
}

CANN_ASC_STL_DEVICE_API void pipeline_store_wait(unsigned int store_event) noexcept
{
    asc_sync_wait(pipe_t::PIPE_S, pipe_t::PIPE_MTE3, static_cast<event_t>(store_event));
}

// Producer-side refill gate.  The WAR edge first retires the scalar pipe's
// in-flight reads of the stage buffer: the next MTE2 load may not overwrite
// storage the consumer is still reading.  The drain edge then retires the
// store engine's in-flight reads of the same buffer before the refill.  Both
// edges are notify+wait self-pairs on their own direction-scoped slots, so
// the gate is round-safe from the first acquisition onward.
CANN_ASC_STL_DEVICE_API void pipeline_producer_acquire(unsigned int drain_event, unsigned int war_event) noexcept
{
    asc_sync_notify(pipe_t::PIPE_S, pipe_t::PIPE_MTE2, static_cast<event_t>(war_event));
    asc_sync_wait(pipe_t::PIPE_S, pipe_t::PIPE_MTE2, static_cast<event_t>(war_event));
    asc_sync_notify(pipe_t::PIPE_MTE3, pipe_t::PIPE_S, static_cast<event_t>(drain_event));
    asc_sync_wait(pipe_t::PIPE_MTE3, pipe_t::PIPE_S, static_cast<event_t>(drain_event));
}

CANN_ASC_STL_DEVICE_API void pipeline_drain() noexcept
{
    asc_sync_pipe(pipe_t::PIPE_ALL);
}

// Aligned asynchronous transfers for the supported scalar set.  The typed C
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
    unsigned int store_event, __gm__ T* destination, __ubuf__ const T* source, unsigned int bytes) noexcept
{
    pipeline_store_wait(store_event);
    asc_copy_ub2gm_align(destination, const_cast<__ubuf__ T*>(source), bytes);  // NOLINT(build/include_what_you_use)
}

#endif

}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___PIPELINE_PIPELINE_H
