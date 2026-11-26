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

#ifndef ASC_STL_TEST_SEMAPHORE_DEVICE_CHECKS_H
#define ASC_STL_TEST_SEMAPHORE_DEVICE_CHECKS_H

#include <asc/std/semaphore>
#include <asc/std/new>

namespace asc_stl_test_semaphore {
CANN_ASC_STL_HOST_SIMT_API int check(int seed, void* workspace)
{
    using counting = asc::std::counting_semaphore<7>;
    static_assert(counting::max() >= 7);
    auto* slots = static_cast<counting*>(workspace);
    ::new (static_cast<void*>(slots)) counting(0);
    if (slots->try_acquire())
        return 1;
    slots->release(seed);
    for (int i = 0; i < 7; ++i)
        if (!slots->try_acquire())
            return 2;
    if (slots->try_acquire())
        return 3;
    slots->release();
    slots->acquire();
    slots->~counting();
    using binary = asc::std::binary_semaphore;
    auto* one = static_cast<binary*>(workspace);
    ::new (static_cast<void*>(one)) binary(1);
    if (!one->try_acquire() || one->try_acquire())
        return 4;
    one->release();
    one->acquire();
    one->~binary();
    return 0;
}
}  // namespace asc_stl_test_semaphore

#endif  // ASC_STL_TEST_SEMAPHORE_DEVICE_CHECKS_H
