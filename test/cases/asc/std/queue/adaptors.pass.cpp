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
#include <asc/std/stack>

#include <deque>
#include <functional>
#include <queue>
#include <stack>
#include <type_traits>
#include <vector>

namespace {

namespace ast = asc::std;
using deque = std::deque<int>;
using priority = ast::priority_queue<int, std::vector<int>, std::less<int>>;

template <class Adapter, class Container>
constexpr bool check_types()
{
    return std::is_same_v<typename Adapter::container_type, Container> &&
        std::is_same_v<typename Adapter::const_reference, const int&> &&
        std::is_same_v<typename Adapter::reference, int&> &&
        std::is_same_v<typename Adapter::size_type, typename Container::size_type> &&
        std::is_same_v<typename Adapter::value_type, int>;
}
static_assert(check_types<ast::queue<int, deque>, deque>());
static_assert(check_types<ast::stack<int, deque>, deque>());
static_assert(check_types<priority, std::vector<int>>());
static_assert(std::is_same_v<priority::value_compare, std::less<int>>);

bool check_queue_order()
{
    ast::queue<int, deque> queue;
    ast::queue<int, deque> replacement;
    const int values[] = {-4, 7, 7, 0, -6};
    if (!queue.empty() || queue.size() != 0) {
        return false;
    }
    for (int value : values) {
        queue.emplace(value);
    }
    replacement.push(91);
    queue.swap(replacement);
    if (queue.size() != 1 || queue.front() != 91 || replacement.size() != 5) {
        return false;
    }
    for (int value : values) {
        if (replacement.empty() || replacement.front() != value) {
            return false;
        }
        replacement.pop();
    }
    return replacement.empty();
}

bool check_stack_and_heap()
{
    ast::stack<int, deque> stack;
    ast::stack<int, deque> other_stack;
    priority heap;
    priority other_heap;
    std::priority_queue<int> expected;
    const int values[] = {-5, 8, 7, 8, 0, -6};
    for (int value : values) {
        stack.emplace(value);
        heap.emplace(value);
        expected.emplace(value);
    }
    stack.swap(other_stack);
    heap.swap(other_heap);
    if (!stack.empty() || !heap.empty() || other_stack.size() != 6 || other_heap.size() != expected.size()) {
        return false;
    }
    for (int i = 5; i >= 0; --i) {
        if (other_stack.top() != values[i] || other_heap.top() != expected.top() ||
            other_heap.size() != expected.size()) {
            return false;
        }
        other_stack.pop();
        other_heap.pop();
        expected.pop();
    }
    return other_stack.empty() && other_heap.empty();
}

}  // namespace

int main()
{
    return check_queue_order() && check_stack_and_heap() ? 0 : 1;
}
