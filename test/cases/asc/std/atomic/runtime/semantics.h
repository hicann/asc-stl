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

#ifndef ASC_STL_TEST_ASC_STD_ATOMIC_RUNTIME_SEMANTICS_H
#define ASC_STL_TEST_ASC_STD_ATOMIC_RUNTIME_SEMANTICS_H

#include <asc/std/atomic>
#include <asc/std/ccomplex>
#include <asc/std/__algorithm/rotate.h>
#include <asc/std/__algorithm/shift_left.h>
#include <asc/std/__algorithm/shift_right.h>
#include <asc/std/__algorithm/sort_heap.h>
#include <asc/std/__algorithm/all_of.h>
#include <asc/std/__algorithm/transform.h>
#include <asc/std/__algorithm/make_heap.h>
#include <asc/std/__semaphore/counting_semaphore.h>

#include "../../../../../support/b022_runtime_inputs.h"
#include "../support/narrow_atomic_cas_semantics.h"
#include "native_overloads.h"

namespace asc_stl_b022_runtime {

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
template <class OutputPointer>
CANN_ASC_STL_SIMT_API void asc_stl_b022_device_semantics(OutputPointer output)
{
    int failures = asc_stl_native_atomic_test::check(output + 4, output[asc_stl_b022_runtime_inputs::seed_slot] + 7);

    auto* shared = reinterpret_cast<asc::std::atomic<__INT32_TYPE__>*>(&output[0]);
    shared->store(0, asc::std::memory_order_relaxed);
    failures += shared->fetch_add(3, asc::std::memory_order_acq_rel) != 0;
    failures += shared->fetch_add(4, asc::std::memory_order_relaxed) != 3;
    __INT32_TYPE__ expected = 7;
    failures +=
        !shared->compare_exchange_strong(expected, 10, asc::std::memory_order_acq_rel, asc::std::memory_order_acquire);
    failures += shared->load(asc::std::memory_order_acquire) != 10;
    failures += shared->exchange(4, asc::std::memory_order_release) != 10;
    failures += asc::std::atomic_exchange(shared, 6) != 4;
    failures += asc::std::atomic_load_explicit(shared, asc::std::memory_order_acquire) != 6;
    asc::std::atomic_init(shared, 1);
    failures += asc::std::atomic_fetch_add(shared, 5) != 1;
    __INT32_TYPE__ failed_expected = 99;
    failures += shared->compare_exchange_strong(
        failed_expected, 7, asc::std::memory_order_acq_rel, asc::std::memory_order_acquire);
    failures += failed_expected != 6;
    __INT32_TYPE__ weak_expected = 6;
    failures += !shared->compare_exchange_weak(
        weak_expected, 8, asc::std::memory_order_acq_rel, asc::std::memory_order_acquire);

    auto* narrow = reinterpret_cast<asc::std::atomic<__UINT16_TYPE__>*>(&output[8]);
    narrow->store(65535, asc::std::memory_order_relaxed);
    failures += narrow->fetch_add(1, asc::std::memory_order_release) != 65535;
    failures += narrow->load(asc::std::memory_order_relaxed) != 0;

    auto* flag = reinterpret_cast<asc::std::atomic_flag*>(&output[16]);
    flag->clear(asc::std::memory_order_relaxed);
    failures += flag->test_and_set(asc::std::memory_order_acq_rel);
    failures += !flag->test(asc::std::memory_order_acquire);
    failures += !flag->test_and_set(asc::std::memory_order_acq_rel);
    asc::std::atomic_flag_clear(flag);
    failures += asc::std::atomic_flag_test(flag);

    asc::std::atomic_thread_fence(asc::std::memory_order_relaxed);
    asc::std::atomic_thread_fence(asc::std::memory_order_release);
    failures += asc::std::kill_dependency(3) != 3;

    *reinterpret_cast<__INT64_TYPE__*>(&output[24]) = 0;
    auto& semaphore = *reinterpret_cast<asc::std::counting_semaphore<2>*>(&output[24]);
    semaphore.release(2);
    failures += !semaphore.try_acquire();
    failures += !semaphore.try_acquire();
    failures += semaphore.try_acquire();
    semaphore.release(1);
    semaphore.acquire();
    failures += semaphore.try_acquire();
    failures += asc::std::counting_semaphore<1>::max() != 1;
    failures |= asc_stl_narrow_atomic_cas_test::evaluate_device(output + 48) != 0 ? 65536 : 0;
    output[31] = failures;
}

CANN_ASC_STL_SIMT_API void publish_visibility(__INT32_TYPE__* output)
{
    constexpr unsigned int rounds = 20000U;
    constexpr unsigned int spin_limit = 10000000U;
    auto* published = reinterpret_cast<asc::std::atomic<__INT32_TYPE__>*>(&output[41]);
    auto* acknowledged = reinterpret_cast<asc::std::atomic<__INT32_TYPE__>*>(&output[42]);
    auto* timeouts = reinterpret_cast<asc::std::atomic<__INT32_TYPE__>*>(&output[44]);
    auto* flag = reinterpret_cast<asc::std::atomic_flag*>(&output[45]);
    for (unsigned int round = 1; round <= rounds; ++round) {
        output[40] = static_cast<int>(round ^ 0x2468ACE0U);
        if ((round & 1U) != 0U)
            (void)flag->test_and_set(asc::std::memory_order_release);
        else if ((round & 2U) != 0U)
            published->store(static_cast<int>(round));
        else
            published->store(static_cast<int>(round), asc::std::memory_order_release);
        unsigned int spins = 0;
        while (acknowledged->load(asc::std::memory_order_acquire) < static_cast<int>(round) && ++spins < spin_limit) {
        }
        if (spins == spin_limit) {
            (void)timeouts->fetch_add(1, asc::std::memory_order_relaxed);
            return;
        }
    }
}

CANN_ASC_STL_SIMT_API void consume_visibility(__INT32_TYPE__* output)
{
    constexpr unsigned int rounds = 20000U;
    constexpr unsigned int spin_limit = 10000000U;
    auto* published = reinterpret_cast<asc::std::atomic<__INT32_TYPE__>*>(&output[41]);
    auto* acknowledged = reinterpret_cast<asc::std::atomic<__INT32_TYPE__>*>(&output[42]);
    auto* errors = reinterpret_cast<asc::std::atomic<__INT32_TYPE__>*>(&output[43]);
    auto* timeouts = reinterpret_cast<asc::std::atomic<__INT32_TYPE__>*>(&output[44]);
    auto* flag = reinterpret_cast<asc::std::atomic_flag*>(&output[45]);
    for (unsigned int round = 1; round <= rounds; ++round) {
        unsigned int spins = 0;
        while (++spins < spin_limit) {
            const bool ready = (round & 1U) != 0U ?
                flag->test(asc::std::memory_order_acquire) :
                ((round & 2U) != 0U ? published->load() : published->load(asc::std::memory_order_acquire)) >=
                    static_cast<int>(round);
            if (ready)
                break;
        }
        if (spins == spin_limit) {
            (void)timeouts->fetch_add(1, asc::std::memory_order_relaxed);
            return;
        }
        if (output[40] != static_cast<int>(round ^ 0x2468ACE0U))
            (void)errors->fetch_add(1, asc::std::memory_order_relaxed);
        if ((round & 1U) != 0U)
            flag->clear(asc::std::memory_order_release);
        acknowledged->store(static_cast<int>(round), asc::std::memory_order_release);
    }
}

CANN_ASC_STL_SIMT_API void asc_stl_b022_visibility_semantics(__INT32_TYPE__* output)
{
    if (threadIdx.x != 0U)
        return;
    if (blockIdx.x == 0U) {
        publish_visibility(output);
    } else if (blockIdx.x == 1U) {
        consume_visibility(output);
    }
}
#endif

template <class OutputPointer>
CANN_ASC_STL_API int evaluate_reordering(OutputPointer output, int seed)
{
    int failures = 0;

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    namespace inputs = asc_stl_b022_runtime_inputs;
    int reordered[] = {inputs::value(output, inputs::reordered_begin) + seed,
        inputs::value(output, inputs::reordered_begin + 1) + seed,
        inputs::value(output, inputs::reordered_begin + 2) + seed,
        inputs::value(output, inputs::reordered_begin + 3) + seed,
        inputs::value(output, inputs::reordered_begin + 4) + seed};
#else
    (void)output;
    (void)seed;
    int reordered[] = {1, 2, 3, 4, 5};
#endif
    failures += asc::std::rotate(reordered, reordered + 2, reordered + 5) != reordered + 3;
    failures += reordered[0] != 3 || reordered[4] != 2;
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    int one_element_tail[] = {inputs::value(output, inputs::reordered_begin) + seed,
        inputs::value(output, inputs::reordered_begin + 1) + seed,
        inputs::value(output, inputs::reordered_begin + 2) + seed,
        inputs::value(output, inputs::reordered_begin + 3) + seed,
        inputs::value(output, inputs::reordered_begin + 4) + seed};
#else
    int one_element_tail[] = {1, 2, 3, 4, 5};
#endif
    failures += asc::std::rotate(one_element_tail, one_element_tail + 4, one_element_tail + 5) != one_element_tail + 1;
    failures += one_element_tail[0] != 5 || one_element_tail[1] != 1 || one_element_tail[4] != 4;
    failures += asc::std::shift_left(reordered, reordered + 5, 1) != reordered + 4;
    failures += asc::std::shift_right(reordered, reordered + 5, 1) != reordered + 1;
    failures += reordered[1] != 4;
    return failures;
}

template <class OutputPointer>
CANN_ASC_STL_API int evaluate_heap_transform(OutputPointer output, int seed)
{
    int failures = 0;
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    namespace inputs = asc_stl_b022_runtime_inputs;
    int heap[] = {inputs::value(output, inputs::heap_begin) + seed,
        inputs::value(output, inputs::heap_begin + 1) + seed, inputs::value(output, inputs::heap_begin + 2) + seed,
        inputs::value(output, inputs::heap_begin + 3) + seed, inputs::value(output, inputs::heap_begin + 4) + seed};
#else
    (void)output;
    (void)seed;
    int heap[] = {1, 5, 2, 4, 3};
#endif
    asc::std::make_heap(heap, heap + 5);
    asc::std::sort_heap(heap, heap + 5);
    failures += heap[0] != 1 || heap[4] != 5;
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    int mapped[5] = {seed, seed, seed, seed, seed};
#else
    int mapped[5] = {};
#endif
    failures += asc::std::transform(  // NOLINT(build/include_what_you_use)
                    heap, heap + 5, mapped, [](int value) { return value * 2; }) != mapped + 5;
    failures += mapped[0] != 2 || mapped[4] != 10;
    failures += !asc::std::all_of(mapped, mapped + 5, [](int value) { return value > 0; });
    return failures;
}

template <class OutputPointer>
CANN_ASC_STL_API void evaluate(OutputPointer output)
{
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    namespace inputs = asc_stl_b022_runtime_inputs;
    const int seed = inputs::value(output, inputs::seed_slot);
#else
    const int seed = 0;
#endif
    int failures = evaluate_reordering(output, seed);
    failures += evaluate_heap_transform(output, seed);

    asc::std::complex<float> value(3.0f, 4.0f);
    value += asc::std::complex<float>(1.0f, 1.0f);
    failures += value.real() != 4.0f || value.imag() != 5.0f;

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    // Real GlobalMemory synchronization through the public facade: fetch/CAS
    // chains, fences, an owning atomic_flag, and a counting semaphore whose
    // state lives in the caller-owned GM buffer.
    asc_stl_b022_device_semantics(output);
#endif
    output[32] = failures;
}

}  // namespace asc_stl_b022_runtime

#endif  // ASC_STL_TEST_ASC_STD_ATOMIC_RUNTIME_SEMANTICS_H
