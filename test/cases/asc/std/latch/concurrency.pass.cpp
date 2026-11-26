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

#include <thread>

int main()
{
    asc::std::latch start(1);
    asc::std::latch ready(3);
    int results[3]{};
    std::thread workers[3];
    for (int i = 0; i < 3; ++i) {
        workers[i] = std::thread([&, i] {
            start.wait();
            results[i] = (i + 1) * 7;
            ready.count_down();
        });
    }
    const bool initially_closed = !ready.try_wait();
    start.count_down();
    ready.wait();
    const bool visible = results[0] == 7 && results[1] == 14 && results[2] == 21;
    for (auto& worker : workers)
        worker.join();
    return initially_closed && visible && ready.try_wait() ? 0 : 1;
}
