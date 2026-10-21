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

#ifndef ASC_STL_TEST_B013_RUNTIME_SEMANTICS_H
#define ASC_STL_TEST_B013_RUNTIME_SEMANTICS_H
#include <asc/atomic>
namespace asc_stl_b013_runtime {
CANN_ASC_STL_SIMT_API void evaluate(__INT32_TYPE__* output) noexcept
{
    asc::atomic_ref<__INT32_TYPE__> value(output[0]);
    value.store(10, asc::std::memory_order_relaxed);
    output[1] = value.fetch_add(5, asc::std::memory_order_relaxed);
    output[2] = value.fetch_sub(3, asc::std::memory_order_relaxed);
    output[3] = value.exchange(6, asc::std::memory_order_relaxed);
    __INT32_TYPE__ expected = 6;
    output[4] =
        value.compare_exchange_strong(expected, 12, asc::std::memory_order_relaxed, asc::std::memory_order_relaxed) ?
        1 :
        0;
    output[5] = value.fetch_and(10, asc::std::memory_order_relaxed);
    output[6] = value.fetch_or(5, asc::std::memory_order_relaxed);
    output[7] = value.fetch_xor(3, asc::std::memory_order_relaxed);
    output[8] = value.fetch_min(4, asc::std::memory_order_relaxed);
    output[9] = value.fetch_max(9, asc::std::memory_order_relaxed);
    asc::relaxed_atomic_ref<__INT32_TYPE__> relaxed(output[0]);
    output[10] = relaxed.load();
    output[11] = relaxed.fetch_add(2);
    output[12] = relaxed.fetch_sub(1);
    output[13] = relaxed.exchange(7);
    expected = 7;
    output[14] = relaxed.compare_exchange_strong(expected, 11) ? 1 : 0;
    asc::atomic_thread_fence(asc::std::memory_order_relaxed, asc::memory_scope::device);
    asc::atomic_thread_fence(asc::std::memory_order_release, asc::memory_scope::block);
    output[15] = value.load(asc::std::memory_order_relaxed);
    ::asc::detail::spin_backoff backoff;
    bool backoff_valid = true;
    for (unsigned index = 0; index < 63; ++index)
        backoff_valid = backoff.poll() && backoff_valid;
    backoff_valid = !backoff.poll() && backoff_valid;
    backoff.poll_count_ = 2147483647;
    for (unsigned index = 0; index < 3; ++index)
        backoff_valid = !backoff.poll() && backoff.poll_count_ == 2147483647 && backoff_valid;
    if (!backoff_valid)
        output[15] = -991;
}

CANN_ASC_STL_SIMT_API void evaluate_visibility(__INT32_TYPE__* output) noexcept
{
    if (threadIdx.x != 0U)
        return;
    constexpr unsigned int rounds = 20000U;
    constexpr unsigned int spin_limit = 10000000U;
    asc::atomic_ref<__INT32_TYPE__> published(output[17]);
    asc::atomic_ref<__INT32_TYPE__> acknowledged(output[18]);
    asc::atomic_ref<__INT32_TYPE__> errors(output[19]);
    asc::atomic_ref<__INT32_TYPE__> timeouts(output[20]);
    if (blockIdx.x == 0U) {
        for (unsigned int round = 1; round <= rounds; ++round) {
            output[16] = static_cast<int>(round ^ 0x13579BDFU);
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
            if (output[16] != static_cast<int>(round ^ 0x13579BDFU))
                (void)errors.fetch_add(1, asc::std::memory_order_relaxed);
            acknowledged.store(static_cast<int>(round), asc::std::memory_order_release);
        }
    }
}
}  // namespace asc_stl_b013_runtime
#endif
