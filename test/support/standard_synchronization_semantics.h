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

#ifndef ASC_STL_TEST_STANDARD_SYNCHRONIZATION_SEMANTICS_H
#define ASC_STL_TEST_STANDARD_SYNCHRONIZATION_SEMANTICS_H

#include <asc/std/atomic>
#include <asc/std/barrier>
#include <asc/std/latch>
#include <asc/std/new>
#include <asc/std/semaphore>

namespace asc_stl_standard_synchronization_test {

namespace ast = asc::std;

struct atomic_storage {
    alignas(ast::atomic<unsigned>) unsigned char word[sizeof(ast::atomic<unsigned>)];
    alignas(ast::atomic_flag) unsigned char flag[sizeof(ast::atomic_flag)];
    alignas(ast::counting_semaphore<2>) unsigned char permits[sizeof(ast::counting_semaphore<2>)];
    alignas(ast::barrier<>) unsigned char barrier[sizeof(ast::barrier<>)];
    alignas(ast::latch) unsigned char latch[sizeof(ast::latch)];
};

CANN_ASC_STL_HOST_SIMT_API int evaluate_rmw(atomic_storage& storage, unsigned seed)
{
    auto* word = ::new (static_cast<void*>(storage.word)) ast::atomic<unsigned>(seed);
    const auto relaxed = ast::memory_order_relaxed;
    const auto acquire = ast::memory_order_acquire;
    const auto release = ast::memory_order_release;
    if (!word->is_lock_free() || !ast::atomic_is_lock_free(word) || ast::atomic_load(word) != seed)
        return 1;
    ast::atomic_store(word, 12u);
    if (word->load(acquire) != 12 || ast::atomic_exchange_explicit(word, 7u, release) != 12)
        return 2;
    unsigned expected = 5;
    if (word->compare_exchange_weak(expected, 11u, ast::memory_order_acq_rel, acquire) || expected != 7)
        return 3;
    if (!ast::atomic_compare_exchange_strong(word, &expected, 11u))
        return 4;
    expected = 12;
    if (ast::atomic_compare_exchange_weak(word, &expected, 15u) || expected != 11)
        return 5;
    if (!ast::atomic_compare_exchange_strong_explicit(word, &expected, 12u, ast::memory_order_acq_rel, acquire))
        return 6;
    expected = 1;
    if (ast::atomic_compare_exchange_weak_explicit(word, &expected, 5u, ast::memory_order_acq_rel, acquire) ||
        expected != 12)
        return 7;

    if (word->fetch_add(3u, relaxed) != 12 || word->fetch_sub(2u, relaxed) != 15 ||
        word->fetch_and(6u, relaxed) != 13 || word->fetch_or(8u, relaxed) != 4 || word->fetch_xor(2u, relaxed) != 12 ||
        word->load() != 14)
        return 8;
    if (ast::atomic_fetch_add_explicit(word, 2u, relaxed) != 14 || ast::atomic_fetch_sub(word, 5u) != 16 ||
        ast::atomic_fetch_sub_explicit(word, 1u, relaxed) != 11 || ast::atomic_fetch_and(word, 15u) != 10 ||
        ast::atomic_fetch_and_explicit(word, 2u, relaxed) != 10 || ast::atomic_fetch_or(word, 4u) != 2 ||
        ast::atomic_fetch_or_explicit(word, 1u, relaxed) != 6 || ast::atomic_fetch_xor(word, 2u) != 7 ||
        ast::atomic_fetch_xor_explicit(word, 1u, relaxed) != 5 || word->load() != 4)
        return 9;

    ast::atomic_store_explicit(word, seed, release);
    if (word->exchange(2u) != seed)
        return 10;
    auto* flag = ::new (static_cast<void*>(storage.flag)) ast::atomic_flag{};
    if (flag->test_and_set(acquire) || !flag->test() || !flag->test_and_set())
        return 11;
    flag->clear(release);
    if (flag->test(relaxed))
        return 12;
    return 0;
}

CANN_ASC_STL_HOST_SIMT_API int evaluate_phases(atomic_storage& storage)
{
    auto& permits = *::new (static_cast<void*>(storage.permits)) ast::counting_semaphore<2>(0);
    if (permits.try_acquire())
        return 1;
    permits.release(2);
    if (!permits.try_acquire())
        return 2;
    permits.acquire();
    if (permits.try_acquire())
        return 3;

    auto& barrier = *::new (static_cast<void*>(storage.barrier)) ast::barrier<>(2);
    auto first = barrier.arrive();
    barrier.arrive_and_drop();
    barrier.wait(static_cast<decltype(first)&&>(first));
    barrier.arrive_and_wait();  // Remaining participation count is one.
    if (barrier.max() < 2)
        return 4;

    auto& latch = *::new (static_cast<void*>(storage.latch)) ast::latch(2);
    if (latch.try_wait() || latch.max() < 2)
        return 5;
    latch.count_down();
    if (latch.try_wait())
        return 6;
    latch.arrive_and_wait();
    latch.wait();
    return latch.try_wait() ? 0 : 7;
}

}  // namespace asc_stl_standard_synchronization_test

#endif  // ASC_STL_TEST_STANDARD_SYNCHRONIZATION_SEMANTICS_H
