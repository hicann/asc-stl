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

#ifndef ASC_STL_TEST_SHARED_MUTEX_DEVICE_CHECKS_H
#define ASC_STL_TEST_SHARED_MUTEX_DEVICE_CHECKS_H

#include <asc/std/shared_mutex>

namespace asc_stl_test_shared_mutex {
struct counter {
    bool held = false;
    int failures = 0;
    int releases = 0;
    CANN_ASC_STL_API void lock_shared() noexcept
    {
        held = true;
    }
    CANN_ASC_STL_API bool try_lock_shared() noexcept
    {
        if (failures > 0) {
            --failures;
            return false;
        }
        if (held)
            return false;
        held = true;
        return true;
    }
    CANN_ASC_STL_API void unlock_shared() noexcept
    {
        held = false;
        ++releases;
    }
};

CANN_ASC_STL_API int check(int seed = 7)
{
    using lock = asc::std::shared_lock<counter>;
    counter a, b;
    a.failures = seed - 6;
    lock empty;
    lock deferred(b, asc::std::defer_lock);
    if (empty.owns_lock() || empty.mutex() != nullptr || deferred || deferred.mutex() != &b)
        return 1;
    {
        lock attempted(a, asc::std::try_to_lock);
        if (attempted || attempted.mutex() != &a || !attempted.try_lock())
            return 2;
        attempted.unlock();
        attempted.lock();
        deferred.lock();
        deferred = static_cast<lock&&>(attempted);
        if (b.held || b.releases != 1 || !a.held || !deferred || attempted.mutex() != nullptr)
            return 3;
        lock moved(static_cast<lock&&>(deferred));
        asc::std::swap(empty, moved);  // NOLINT(build/include_what_you_use)
        if (moved.owns_lock() || empty.release() != &a || !a.held || empty.mutex() != nullptr)
            return 4;
        lock adopted(a, asc::std::adopt_lock);
        lock direct(b);
        direct.swap(adopted);
        if (direct.mutex() != &a || adopted.mutex() != &b)
            return 5;
    }

    return !a.held && !b.held ? 0 : 13;
}
}  // namespace asc_stl_test_shared_mutex

#endif  // ASC_STL_TEST_SHARED_MUTEX_DEVICE_CHECKS_H
