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

#ifndef ASC_STL_TEST_ATOMIC_RUNTIME_NATIVE_OVERLOADS_H
#define ASC_STL_TEST_ATOMIC_RUNTIME_NATIVE_OVERLOADS_H

#include <asc/std/atomic>
#include <asc/std/new>
#include <asc/std/type_traits>

namespace asc_stl_native_atomic_test {

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
CANN_ASC_STL_SIMT_API int check(int* slot, int seed)
{
    namespace s = asc::std;
    using owned = s::atomic<int>;
    auto* cell = reinterpret_cast<owned*>(slot);
    ::new (static_cast<void*>(cell)) owned{};
    int failures = static_cast<int>(*cell) != 0;
    failures += (*cell = seed) != seed || static_cast<int>(*cell) != seed;
    int expected = seed - 1;
    failures += cell->compare_exchange_strong(expected, seed + 1, s::memory_order_release) || expected != seed;
    failures += !cell->compare_exchange_strong(expected, seed + 1, s::memory_order_acq_rel);
    expected = seed - 1;
    failures += cell->compare_exchange_weak(expected, seed + 2, s::memory_order_acq_rel) || expected != seed + 1;
    cell->~owned();

    ::new (static_cast<void*>(slot)) int{seed};
    using ref_type = s::atomic_ref<int>;
    static_assert(s::is_copy_constructible_v<ref_type> && !s::is_copy_assignable_v<ref_type>);
    const ref_type first(*slot);
    const ref_type second(first);
    expected = seed - 1;
    failures += second.compare_exchange_weak(expected, seed + 2, s::memory_order_release, s::memory_order_relaxed) ||
        expected != seed;
    int attempts = 0;
    while (!second.compare_exchange_weak(expected, seed + 2, s::memory_order_acq_rel) && ++attempts < 8) {
    }
    return failures + (first.load(s::memory_order_acquire) != seed + 2);
}
#endif

}  // namespace asc_stl_native_atomic_test
#endif  // ASC_STL_TEST_ATOMIC_RUNTIME_NATIVE_OVERLOADS_H
