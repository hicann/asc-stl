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

#include "device_checks.h"

int main()
{
    using mutex = asc_stl_test_mutex::counter;
    mutex a, b;
    a.lock();
    {
        asc::std::scoped_lock<mutex> one(asc::std::adopt_lock, a);
        if (!a.held)
            return 20;
    }
    a.lock();
    b.lock();
    {
        asc::std::scoped_lock<mutex, mutex> both(asc::std::adopt_lock, a, b);
        if (!a.held || !b.held)
            return 21;
    }
    if (a.held || b.held || a.releases != 2 || b.releases != 1)
        return 22;
    return asc_stl_test_mutex::check(7);
}
