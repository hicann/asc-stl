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

#include <asc/std/atomic>
#include <asc/std/ccomplex>
#include <asc/std/__algorithm/make_heap.h>
#include <asc/std/__algorithm/rotate.h>
#include <asc/std/__algorithm/shift_left.h>
#include <asc/std/__algorithm/sort_heap.h>
#include <asc/std/__semaphore/counting_semaphore.h>

int asc_stl_b022_consumer_a()
{
    static_assert(CANN_ASC_STL_ATOMIC_INT_LOCK_FREE == 2);
    static_assert(asc::std::atomic_int::is_always_lock_free);
    asc::std::atomic_int value{4};
    value.store(6, asc::std::memory_order_release);
    if (value.fetch_add(1) != 6) {
        return 1;
    }
    int data[] = {1, 2, 3, 4, 5};
    if (asc::std::rotate(data, data + 2, data + 5) != data + 3) {
        return 2;
    }
    if (asc::std::shift_left(data, data + 5, 2) != data + 3) {
        return 3;
    }
    int heap[] = {1, 3, 2};
    asc::std::make_heap(heap, heap + 3);
    asc::std::sort_heap(heap, heap + 3);
    if (heap[0] != 1) {
        return 4;
    }
    asc::std::counting_semaphore<1> semaphore(0);
    if (semaphore.try_acquire()) {
        return 5;
    }
    semaphore.release(1);
    semaphore.acquire();
    asc::std::complex<float> number(3.0f, 4.0f);
    return number.real() == 3.0f ? 0 : 6;
}
