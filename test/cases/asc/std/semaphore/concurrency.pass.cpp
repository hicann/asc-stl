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

#include <asc/std/semaphore>

#include <thread>

int main()
{
    asc::std::binary_semaphore read(0), write(1);
    int slot = 0;
    std::thread producer([&] {
        for (int n = 1; n <= 100; ++n) {
            write.acquire();
            slot = n;
            read.release();
        }
    });
    bool ordered = true;
    for (int n = 1; n <= 100; ++n) {
        read.acquire();
        ordered = ordered && slot == n;
        write.release();
    }
    producer.join();
    return ordered && write.try_acquire() && !read.try_acquire() ? 0 : 1;
}
