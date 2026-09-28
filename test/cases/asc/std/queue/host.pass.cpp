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
#include <memory>
#include <type_traits>
#include <vector>

int main()
{
    std::allocator<int> allocator;
    std::deque<int> deque{1, 2, 3};
    asc::std::queue queue(deque, allocator);
    static_assert(std::is_same_v<decltype(queue), asc::std::queue<int, std::deque<int>>>);
    asc::std::queue<int, std::deque<int>> from_allocator(allocator);
    asc::std::queue<int, std::deque<int>> from_copy(queue, allocator);
    asc::std::queue<int, std::deque<int>> from_move(static_cast<decltype(queue)&&>(queue), allocator);
    std::vector<int> vector{1, 3, 2};
    asc::std::priority_queue priority(std::less<int>{}, vector, allocator);
    static_assert(std::is_same_v<decltype(priority), asc::std::priority_queue<int, std::vector<int>, std::less<int>>>);
    asc::std::priority_queue<int, std::vector<int>, std::less<int>> from_range(
        vector.begin(), vector.end(), std::less<int>{}, vector);
    asc::std::priority_queue<int, std::vector<int>, std::less<int>> from_priority_copy(priority, allocator);
    return from_allocator.empty() && from_copy.front() == 1 && from_move.front() == 1 && priority.top() == 3 &&
            from_range.top() == 3 && from_priority_copy.top() == 3 ?
        0 :
        1;
}
