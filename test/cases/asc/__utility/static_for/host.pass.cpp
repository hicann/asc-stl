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
#include <asc/__utility/static_for.h>

#include <cassert>

int main()
{
    int total = 0;
    asc::detail::static_for_count<int, 5>([&total](auto index) { total += index.value; });
    assert(total == 10);

    int collected = 0;
    asc::detail::static_for_range<int, 0, 7, 2>(
        [&collected](auto index) { collected = collected * 10 + static_cast<int>(index); });
    assert(collected == 246);

    int descending = 0;
    asc::detail::static_for_range<int, 6, 0, -2>(
        [&descending](auto index) { descending = descending * 10 + static_cast<int>(index); });
    assert(descending == 642);

    int zero_iterations = 0;
    asc::detail::static_for_range<int, 3, 3, 1>([&zero_iterations](auto) { ++zero_iterations; });
    assert(zero_iterations == 0);

    int single = 0;
    asc::detail::static_for_count<unsigned, 1>([&single](auto index) { single = static_cast<int>(index); });
    assert(single == 0);

    constexpr int constant_total = [] {
        int value = 0;
        asc::detail::static_for_count<int, 4>([&value](auto index) { value += index.value; });
        return value;
    }();
    static_assert(constant_total == 6);

    // Each call receives a lightweight integral_constant index.
    int first_index = -1;
    asc::detail::static_for_count<int, 3>([&first_index](auto index) {
        if (first_index < 0) {
            first_index = index.value;
        }
    });
    assert(first_index == 0);

    int auto_indices = 0;
    asc::detail::static_for_auto<0, 4, 2>([&auto_indices](auto index) {
        ++auto_indices;
        static_cast<void>(index);
    });
    assert(auto_indices == 2);
    return 0;
}
