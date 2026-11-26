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

#include <asc/std/barrier>

#include <thread>

int main()
{
    constexpr int phases = 64;
    int published[2]{};
    int readback[2]{};
    int completions = 0;
    auto completed = [&]() noexcept { ++completions; };
    asc::std::barrier<decltype(completed)> gate(2, completed);
    auto worker = [&](int rank) {
        for (int round = 0; round < phases; ++round) {
            published[rank] = round + rank;
            gate.arrive_and_wait();
            readback[rank] += published[1 - rank];
            // Both reads finish before either participant reuses its slot.
            gate.arrive_and_wait();
        }
    };
    std::thread other(worker, 1);
    worker(0);
    other.join();
    return completions == 2 * phases && readback[0] == phases * (phases + 1) / 2 &&
            readback[1] == phases * (phases - 1) / 2 ?
        0 :
        1;
}
