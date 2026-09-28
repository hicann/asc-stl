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

/* Copyright 2026 湖北多样性算力应用创新研究院 */
#ifndef ASC_STL_TEST_ASC_WARP_RUNTIME_SEMANTICS_H
#define ASC_STL_TEST_ASC_WARP_RUNTIME_SEMANTICS_H
#include <asc/std/atomic>
#include <asc/warp>
#include <acl/acl.h>
#ifndef ASC_STL_ATOMIC_VISIBILITY_ROUNDS
#define ASC_STL_ATOMIC_VISIBILITY_ROUNDS 256
#endif
void launch_asc_stl_b017_cannsim(int*, aclrtStream);
void launch_asc_stl_b017(int*, aclrtStream);
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
namespace asc_stl_b017_runtime {
template <class OutputPointer>
CANN_ASC_STL_DEVICE_API void evaluate(OutputPointer output)
{
    unsigned int failures = 0;
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    const unsigned int lane = asc::lane_id();
    const auto active = asc::active_mask();
    failures |= static_cast<unsigned int>(active != asc::lane_mask::all()) << 0U;
    failures |= static_cast<unsigned int>(asc::lane_mask::this_lane().value() != (1U << lane)) << 1U;
    const unsigned int expected_lower = lane == 0U ? 0U : (1U << lane) - 1U;
    failures |= static_cast<unsigned int>(asc::lane_mask::all_less().value() != expected_lower) << 2U;
    failures |= static_cast<unsigned int>(!asc::warp_all(true) || !asc::warp_any(lane == 0)) << 3U;
    failures |= static_cast<unsigned int>(asc::warp_ballot(true) != active) << 4U;
    failures |= static_cast<unsigned int>(!asc::warp_match_all(7, active)) << 5U;
    const asc::lane_mask expected_match(0x11111111U << (lane & 3U));
    failures |= static_cast<unsigned int>(asc::warp_match_any(lane & 3U, active) != expected_match) << 6U;
    const auto indexed = asc::warp_shuffle_idx<32>(lane, 0, active);
    failures |= static_cast<unsigned int>(!indexed.valid || indexed.data != 0U) << 7U;
    const auto up = asc::warp_shuffle_up<32>(lane, 1, active);
    failures |= static_cast<unsigned int>(up.valid != (lane != 0U)) << 8U;
    failures |= static_cast<unsigned int>(up.valid && up.data != lane - 1U) << 9U;
    failures |= static_cast<unsigned int>(asc::warp_reduce_add(lane) != 496U) << 10U;
    failures |= static_cast<unsigned int>(asc::warp_reduce_min(lane) != 0U) << 11U;
    failures |= static_cast<unsigned int>(asc::warp_reduce_max(lane) != 31U) << 12U;
    failures |= static_cast<unsigned int>(output[2] != 0 && lane == 1U) << 13U;
    if (blockIdx.x == 0U && threadIdx.x == 0U) {
        output[3] = 0;
        asc::std::atomic_ref<int> weak_reference(output[3]);
        int expected = 0;
        failures |= static_cast<unsigned int>(!weak_reference.compare_exchange_weak(
                        expected, 1, asc::std::memory_order_relaxed, asc::std::memory_order_relaxed))
            << 14U;
    }
    if (lane == 0U) {
        asc::std::atomic_ref<int> count(output[1]);
        (void)count.fetch_add(1, asc::std::memory_order_relaxed);
    }
    if (failures != 0) {
        asc::std::atomic_ref<int> failure_count(output[0]);
        (void)failure_count.fetch_add(1, asc::std::memory_order_relaxed);
    }
    output[8U + static_cast<unsigned int>(blockIdx.x) * 64U + static_cast<unsigned int>(threadIdx.x)] =
        static_cast<int>(failures);
#else
    output[0] = failures;
#endif
}

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
template <class OutputPointer>
CANN_ASC_STL_SIMT_API void evaluate_message_passing(OutputPointer output)
{
    if (threadIdx.x != 0U)
        return;
    constexpr unsigned int rounds = ASC_STL_ATOMIC_VISIBILITY_ROUNDS;
    constexpr unsigned int spin_limit = 10000000U;
    asc::std::atomic_ref<int> published(output[4]);
    asc::std::atomic_ref<int> acknowledged(output[5]);
    asc::std::atomic_ref<int> errors(output[6]);
    asc::std::atomic_ref<int> timeouts(output[7]);
    if (blockIdx.x == 0U) {
        for (unsigned int round = 1; round <= rounds; ++round) {
            output[3] = static_cast<int>(round ^ 0x5A5A5A5AU);
            published.store(static_cast<int>(round), asc::std::memory_order_release);
            unsigned int spins = 0;
            while (
                acknowledged.load(asc::std::memory_order_acquire) < static_cast<int>(round) && ++spins < spin_limit) {
            }
            if (spins == spin_limit) {
                (void)timeouts.fetch_add(1, asc::std::memory_order_relaxed);
                return;
            }
        }
    } else if (blockIdx.x == 1U) {
        for (unsigned int round = 1; round <= rounds; ++round) {
            unsigned int spins = 0;
            while (published.load(asc::std::memory_order_acquire) < static_cast<int>(round) && ++spins < spin_limit) {
            }
            if (spins == spin_limit) {
                (void)timeouts.fetch_add(1, asc::std::memory_order_relaxed);
                return;
            }
            if (output[3] != static_cast<int>(round ^ 0x5A5A5A5AU))
                (void)errors.fetch_add(1, asc::std::memory_order_relaxed);
            acknowledged.store(static_cast<int>(round), asc::std::memory_order_release);
        }
    }
}
#endif
}  // namespace asc_stl_b017_runtime
#endif
#endif  // ASC_STL_TEST_ASC_WARP_RUNTIME_SEMANTICS_H
