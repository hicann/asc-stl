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

#ifndef ASC_STL_TEST_LATCH_DEVICE_CHECKS_H
#define ASC_STL_TEST_LATCH_DEVICE_CHECKS_H

#include <asc/std/latch>
#include <asc/std/new>

namespace asc_stl_test_latch {
CANN_ASC_STL_HOST_SIMT_API int check(int seed, void* workspace)
{
    using gate = asc::std::latch;
    static_assert(gate::max() >= 7);
    auto* countdown = static_cast<gate*>(workspace);
    ::new (static_cast<void*>(countdown)) gate(seed);
    if (countdown->try_wait())
        return 1;
    countdown->count_down(5);
    if (countdown->try_wait())
        return 2;
    countdown->count_down();
    countdown->arrive_and_wait();
    countdown->wait();
    if (!countdown->try_wait())
        return 3;
    countdown->~gate();
    auto* open = static_cast<gate*>(workspace);
    ::new (static_cast<void*>(open)) gate(0);
    open->wait();
    const bool ready = open->try_wait();
    open->~gate();
    return ready ? 0 : 4;
}
}  // namespace asc_stl_test_latch

#endif  // ASC_STL_TEST_LATCH_DEVICE_CHECKS_H
