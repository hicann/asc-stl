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

#include <asc/std/stack>

#include <deque>
#include <type_traits>

#include "device_checks.h"

int main()
{
    using backing = std::deque<int>;
    using adaptor = asc::std::stack<int, backing>;
    static_assert(std::is_same_v<typename adaptor::container_type, backing>);
    static_assert(std::is_same_v<typename adaptor::reference, int&>);
    const backing source{1, 2, 3};
    adaptor copied(source);
    adaptor moved(backing{4, 5});
    adaptor empty;
    asc::std::swap(empty, copied);  // NOLINT(build/include_what_you_use)
    if (!copied.empty() || empty.size() != 3 || empty.top() != 3)
        return 1;
    moved.swap(empty);
    const adaptor& c = moved;
    const int six = 6;
    moved.push(six);
    moved.push(7);
    if (&moved.emplace(8) != &moved.top() || c.top() != 8)
        return 2;

    const int expected[] = {8, 7, 6, 3, 2, 1};
    for (int n : expected) {
        if (c.top() != n)
            return 4;
        moved.pop();
    }
    if (!moved.empty())
        return 5;
    return asc_stl_test_stack::check();
}
