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

#include <asc/std/functional>
#include <asc/std/semaphore>
#include <asc/std/__barrier/barrier.h>
#include <asc/std/__mutex/lock_guard.h>
#include <asc/std/__mutex/lock_tags.h>
#include <asc/std/__mutex/scoped_lock.h>
#include <asc/std/__mutex/try_lock.h>
#include <asc/std/__mutex/unique_lock.h>

#include <thread>

struct mutex_probe {
    bool locked = false;
    int lock_count = 0;
    int failures_before_success = 0;
    void lock()
    {
        locked = true;
        ++lock_count;
    }
    bool try_lock()
    {
        if (failures_before_success != 0) {
            --failures_before_success;
            return false;
        }
        if (locked)
            return false;
        lock();
        return true;
    }
    void unlock()
    {
        locked = false;
    }
};

int main()
{
    asc::std::counting_semaphore<4> ready(0);
    int value = 0;
    std::thread producer([&] {
        value = 42;
        ready.release();
    });
    ready.acquire();
    producer.join();

    int input = 5;
    const auto reference = asc::std::ref(input);
    asc::std::plus<int> add;
    mutex_probe first;
    mutex_probe second;
    {
        asc::std::lock_guard<mutex_probe> guard(first);
        if (!first.locked)
            return 1;
    }
    asc::std::unique_lock<mutex_probe> owner(first, asc::std::defer_lock);
    if (!owner.try_lock() || owner.release() != &first)
        return 2;
    first.unlock();
    if (asc::std::try_lock(first, second) != -1)
        return 3;
    first.unlock();
    second.unlock();
    second.failures_before_success = 1;
    const int locks_before_scoped = first.lock_count;
    {
        asc::std::scoped_lock<mutex_probe, mutex_probe> guard(first, second);
        if (!first.locked || !second.locked)
            return 4;
    }
    if (first.lock_count != locks_before_scoped + 2)
        return 5;

    asc::std::barrier phases(1);
    phases.arrive_and_wait();
    return value == 42 && reference.get() == 5 && add(3, 4) == 7 && asc::std::counting_semaphore<4>::max() >= 4 &&
            !ready.try_acquire() && !first.locked && !second.locked ?
        0 :
        6;
}
