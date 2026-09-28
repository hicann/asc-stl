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

#include <asc/std/latch>
#include <asc/std/shared_mutex>

struct shared_mutex_probe {
    int shared_count = 0;
    void lock_shared()
    {
        ++shared_count;
    }
    bool try_lock_shared()
    {
        ++shared_count;
        return true;
    }
    void unlock_shared()
    {
        --shared_count;
    }
};

int main()
{
    asc::std::latch completion(2);
    static_assert(asc::std::latch::max() > 2);
    completion.count_down();
    if (completion.try_wait())
        return 1;
    completion.arrive_and_wait();

    shared_mutex_probe mutex;
    asc::std::shared_lock<shared_mutex_probe> owner(mutex);
    asc::std::shared_lock<shared_mutex_probe> moved(static_cast<decltype(owner)&&>(owner));
    if (!moved.owns_lock() || owner.owns_lock() || mutex.shared_count != 1)
        return 2;
    moved.unlock();
    return mutex.shared_count == 0 ? 0 : 3;
}
