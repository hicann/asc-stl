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

#ifndef ASC_STL_TEST_ATOMIC_DEVICE_CHECKS_H
#define ASC_STL_TEST_ATOMIC_DEVICE_CHECKS_H

#include <asc/std/atomic>
#include <asc/std/new>

namespace asc_stl_test_atomic {
CANN_ASC_STL_HOST_SIMT_API int check(int seed, void* workspace)
{
    namespace s = asc::std;
    using cell = s::atomic<int>;
    auto* c = static_cast<cell*>(workspace);
    ::new (static_cast<void*>(c)) cell(seed);
    if (!s::atomic_is_lock_free(c) || s::atomic_load(c) != 7 || s::kill_dependency(seed) != 7)
        return 1;
    s::atomic_init(c, 1);
    s::atomic_store(c, 9);
    s::atomic_store_explicit(c, 11, s::memory_order_release);
    if (s::atomic_load_explicit(c, s::memory_order_acquire) != 11 || s::atomic_exchange(c, 3) != 11 ||
        s::atomic_exchange_explicit(c, 0, s::memory_order_relaxed) != 3)
        return 2;
    int expected = 4;
    if (s::atomic_compare_exchange_strong(c, &expected, 5) || expected != 0 ||
        !s::atomic_compare_exchange_strong_explicit(c, &expected, 5, s::memory_order_release, s::memory_order_relaxed))
        return 3;
    expected = 3;
    if (s::atomic_compare_exchange_weak(c, &expected, 1) || expected != 5)
        return 4;
    while (!s::atomic_compare_exchange_weak_explicit(c, &expected, 1, s::memory_order_acq_rel, s::memory_order_acquire))
        if (expected != 5)
            return 5;
    if (s::atomic_fetch_add(c, 3) != 1 || s::atomic_fetch_add_explicit(c, 5, s::memory_order_relaxed) != 4 ||
        s::atomic_fetch_sub(c, 3) != 9 || s::atomic_fetch_sub_explicit(c, 4, s::memory_order_seq_cst) != 6 ||
        s::atomic_fetch_or(c, 12) != 2 || s::atomic_fetch_or_explicit(c, 1, s::memory_order_relaxed) != 14 ||
        s::atomic_fetch_and(c, 7) != 15 || s::atomic_fetch_and_explicit(c, 3, s::memory_order_relaxed) != 7 ||
        s::atomic_fetch_xor(c, 2) != 3 || s::atomic_fetch_xor_explicit(c, 7, s::memory_order_relaxed) != 1 ||
        s::atomic_load(c) != 6)
        return 6;
    c->~cell();
    using flag = s::atomic_flag;
    auto* f = static_cast<flag*>(workspace);
    ::new (static_cast<void*>(f)) flag{};
    s::atomic_flag_clear(f);
    if (s::atomic_flag_test(f) || s::atomic_flag_test_and_set(f) ||
        !s::atomic_flag_test_and_set_explicit(f, s::memory_order_acquire) ||
        !s::atomic_flag_test_explicit(f, s::memory_order_relaxed))
        return 7;
    s::atomic_flag_clear_explicit(f, s::memory_order_release);
    if (s::atomic_flag_test(f))
        return 8;
    f->~flag();
    using word = unsigned;
    auto* w = static_cast<word*>(workspace);
    ::new (static_cast<void*>(w)) word(7);
    {
        s::atomic_ref<word> ref(*w);
        const s::atomic_ref<word> alias(ref);
        if (!alias.is_lock_free() || alias.load(s::memory_order_consume) != 7 ||
            alias.exchange(3, s::memory_order_acq_rel) != 7 || alias.fetch_and(1) != 3 || alias.fetch_or(6) != 1 ||
            alias.fetch_xor(2) != 7 || alias.fetch_add(1) != 5 || alias.fetch_sub(2) != 6)
            return 9;
        word previous = 11;
        if (alias.compare_exchange_strong(previous, 0, s::memory_order_acq_rel) || previous != 4)
            return 10;
        alias.store(2, s::memory_order_release);
        if ((alias = 17) != 17 || ref.load() != 17)
            return 11;
    }
    s::atomic_thread_fence(s::memory_order_relaxed);
    s::atomic_thread_fence(s::memory_order_release);
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    s::atomic_thread_fence(s::memory_order_consume);
    s::atomic_thread_fence(s::memory_order_acquire);
    s::atomic_thread_fence(s::memory_order_acq_rel);
    s::atomic_thread_fence(s::memory_order_seq_cst);
#endif
    const bool updated = *w == 17;
    w->~word();
    return updated ? 0 : 12;
}
}  // namespace asc_stl_test_atomic

#endif  // ASC_STL_TEST_ATOMIC_DEVICE_CHECKS_H
