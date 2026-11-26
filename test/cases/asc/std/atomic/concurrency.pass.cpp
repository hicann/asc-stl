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

#include <thread>

int main()
{
    asc::std::atomic<int> counter(0);
    std::thread workers[4];
    int totals[4]{};
    for (int i = 0; i < 4; ++i)
        workers[i] = std::thread([&, i] {
            for (int n = 0; n < 512; ++n)
                totals[i] += counter.fetch_add(1, asc::std::memory_order_relaxed);
        });
    for (auto& worker : workers)
        worker.join();
    const int sum = totals[0] + totals[1] + totals[2] + totals[3];
    if (counter.load() != 2048 || sum != (2047 * 2048) / 2)
        return 1;
    asc::std::atomic<int> published(0);
    int payload = 0;
    std::thread producer([&] {
        payload = 73;
        published.store(1, asc::std::memory_order_release);
    });
    while (!published.load(asc::std::memory_order_acquire))
        std::this_thread::yield();
    const int observed = payload;
    producer.join();
    return observed == 73 ? 0 : 2;
}
