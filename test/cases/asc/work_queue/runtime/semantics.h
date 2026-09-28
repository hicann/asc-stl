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
#ifndef ASC_STL_TEST_ASC_WORK_QUEUE_RUNTIME_SEMANTICS_H
#define ASC_STL_TEST_ASC_WORK_QUEUE_RUNTIME_SEMANTICS_H

#include <asc/atomic>
#include <asc/hierarchy>
#include <asc/std/__atomic/backend.h>
#include <asc/warp>
#include <asc/work_queue>

namespace asc_stl_work_queue_runtime {

// Shared dynamic-work-claim evaluator: ordinary AICore blocks claim through
// the core path while pure-SIMT warps claim through their lane-0 leader and
// broadcast the chunk through the delivered warp vocabulary.  Every element
// of [0, items) must be visited exactly once; the result word packs the
// failure bits (element 0: coverage failure count, element 1: acquisition
// protocol failure).
// The caller initializes the complete cursor before launch; the device code
// never writes it, so no plain store can race the atomic cursor advance.
template <class VisitsPointer, class CursorPointer>
CANN_ASC_STL_API void evaluate(VisitsPointer visits, CursorPointer cursor, unsigned items, unsigned grain)
{
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    const unsigned lane = static_cast<unsigned>(threadIdx.x) & 31u;
    for (;;) {
        asc::work_chunk<unsigned> chunk{};
        bool claimed = false;
        if (lane == 0) {
            claimed = asc::acquire_work(cursor, items, grain, chunk);
        }
        const auto broadcast =
            asc::warp_shuffle_idx(claimed ? (chunk.begin * 2u + 1u) : 0u, 0, asc::lane_mask(0xFFFFFFFFu));
        const bool have_claim = broadcast.data & 1u;
        if (!have_claim) {
            break;
        }
        const unsigned begin = broadcast.data >> 1;
        const unsigned end = begin + grain < items ? begin + grain : items;
        if (broadcast.valid) {
            for (unsigned item = begin + lane; item < end; item += 32u) {
                ::asc::detail::atomic_add(&visits[item], 1u);
            }
        }
        (void)chunk;
        (void)claimed;
    }
#else
    // Ordinary AICore: the core claim takes the caller-owned global-memory
    // cursor through the __gm__-qualified acquisition path.
    asc::work_chunk<unsigned> chunk{};
    while (asc::acquire_work(cursor, items, grain, chunk)) {
        for (unsigned item = chunk.begin; item < chunk.end; ++item) {
            asc_atomic_add(&visits[item], 1u);
        }
    }
#endif
}

template <class ResultPointer, class CursorPointer>
CANN_ASC_STL_API void evaluate_uint64_boundary(ResultPointer result, CursorPointer cursor)
{
    constexpr __UINT64_TYPE__ high_bit = static_cast<__UINT64_TYPE__>(1) << 63;
    asc::work_chunk<__UINT64_TYPE__> chunk{};
    unsigned failures = 0;
    failures += !asc::acquire_work(cursor, high_bit + 3, static_cast<__UINT64_TYPE__>(2), chunk);
    failures += chunk.begin != high_bit - 2 || chunk.end != high_bit;
    failures += !asc::acquire_work(cursor, high_bit + 3, static_cast<__UINT64_TYPE__>(2), chunk);
    failures += chunk.begin != high_bit || chunk.end != high_bit + 2;
    failures += !asc::acquire_work(cursor, high_bit + 3, static_cast<__UINT64_TYPE__>(2), chunk);
    failures += chunk.begin != high_bit + 2 || chunk.end != high_bit + 3;
    failures += asc::acquire_work(cursor, high_bit + 3, static_cast<__UINT64_TYPE__>(2), chunk);
    result[0] = failures;
}

}  // namespace asc_stl_work_queue_runtime

#endif  // ASC_STL_TEST_ASC_WORK_QUEUE_RUNTIME_SEMANTICS_H
