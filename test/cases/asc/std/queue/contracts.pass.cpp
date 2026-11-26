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

#include <asc/std/queue>

#include <deque>
#include <functional>
#include <type_traits>
#include <vector>

#include "device_checks.h"

struct priority_order {
    bool minimum_first = false;
    bool operator()(int left, int right) const
    {
        return minimum_first ? left > right : left < right;
    }
};

int main()
{
    using backing = std::deque<int>;
    using adaptor = asc::std::queue<int, backing>;
    static_assert(std::is_same_v<typename adaptor::container_type, backing>);
    static_assert(std::is_same_v<typename adaptor::reference, int&>);
    const backing source{1, 2, 3};
    adaptor copied(source);
    adaptor moved(backing{4, 5});
    adaptor empty;
    asc::std::swap(empty, copied);  // NOLINT(build/include_what_you_use)
    if (!copied.empty() || empty.size() != 3 || empty.front() != 1)
        return 1;
    moved.swap(empty);
    const adaptor& c = moved;
    const int six = 6;
    moved.push(six);
    moved.push(7);
    if (&moved.emplace(8) != &moved.back() || c.front() != 1)
        return 2;
    if (c.back() != 8 || moved.front() != 1)
        return 3;
    const int expected[] = {1, 2, 3, 6, 7, 8};
    for (int n : expected) {
        if (c.front() != n)
            return 4;
        moved.pop();
    }
    if (!moved.empty())
        return 5;

    using heap = asc::std::priority_queue<int, std::vector<int>, std::greater<int>>;
    const std::vector<int> seed{3, -4, 3, 2};
    heap q(std::greater<int>{}, seed);
    heap spare(std::greater<int>{});
    heap default_heap;
    q.push(six);
    q.push(-9);
    q.emplace(3);
    asc::std::swap(q, spare);  // NOLINT(build/include_what_you_use)
    default_heap.swap(spare);
    const int sorted[] = {-9, -4, 2, 3, 3, 3, 6};
    if (!q.empty() || !spare.empty() || default_heap.size() != 7)
        return 6;
    for (int n : sorted) {
        if (default_heap.top() != n)
            return 7;
        default_heap.pop();
    }
    if (!default_heap.empty())
        return 8;
    using configurable_heap = asc::std::priority_queue<int, std::vector<int>, priority_order>;
    configurable_heap maximum;
    configurable_heap minimum(priority_order{true});
    for (int value : {4, 1}) {
        maximum.push(value);
        minimum.push(value);
    }
    if (maximum.top() != 4 || minimum.top() != 1)
        return 9;
    return asc_stl_test_queue::check();
}
