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

#ifndef ASC_STL_TEST_STANDARD_CONTAINER_SEMANTICS_H
#define ASC_STL_TEST_STANDARD_CONTAINER_SEMANTICS_H

#include <asc/std/deque>
#include <asc/std/forward_list>
#include <asc/std/queue>
#include <asc/std/scoped_allocator>
#include <asc/std/set>
#include <asc/std/stack>
#include <asc/std/unordered_map>
#include <asc/std/unordered_set>
#include <asc/std/utility>
#include <asc/std/vector>

#include "support/b027_semantics.h"
#include "support/fixed_sequence.h"

namespace asc_stl_standard_container_test {

namespace ast = asc::std;
using asc_stl_b027_test::arena_allocator;
using asc_stl_b027_test::arena_state;
using asc_stl_b027_test::equal_int;
using asc_stl_b027_test::less_int;
using int_allocator = arena_allocator<int>;

struct constant_hash {
    CANN_ASC_STL_API __SIZE_TYPE__ operator()(int) const noexcept
    {
        return 0;
    }
};

CANN_ASC_STL_HOST_SIMT_API int evaluate_sequences(arena_state& state, int seed)
{
    const int_allocator allocator(&state);
    ast::vector<int, int_allocator> vector(allocator);
    ast::deque<int, int_allocator> deque(allocator);
    ast::forward_list<int, int_allocator> linked(allocator);
    for (int i = 0; i < 5; ++i) {
        vector.push_back(seed + i);
        deque.push_back(seed + i);
        linked.push_front(seed + i);
    }
    const auto capacity = vector.capacity();
    if (!(vector.get_allocator() == allocator) || vector.data()[4] != seed + 4 || capacity < 5 ||
        vector.end() - vector.begin() != 5 || vector.empty())
        return 1;
    vector.pop_back();
    ast::vector<int, int_allocator> moved(allocator);
    moved = ast::move(vector);
    if (moved.size() != 4 || moved.back() != seed + 3)
        return 2;
    moved.clear();
    if (!moved.empty() || moved.begin() != moved.end() || moved.capacity() < 4)
        return 3;
    if (deque.begin() == deque.end() || deque.empty())
        return 4;
    deque.clear();
    if (!deque.empty() || deque.begin() != deque.end())
        return 5;
    linked.pop_front();
    ast::forward_list<int, int_allocator> other(allocator);
    other = ast::move(linked);
    if (other.empty() || other.front() != seed + 3 || other.begin() == other.end())
        return 6;
    other.clear();
    return !other.empty() || other.begin() != other.end() ? 7 : 0;
}

CANN_ASC_STL_HOST_SIMT_API int evaluate_ordered_set(arena_state& state, int seed)
{
    const int_allocator allocator(&state);
    using tree = ast::set<int, less_int, int_allocator>;
    tree ordered{less_int{}, allocator};
    tree replacement{less_int{}, allocator};
    const int first = seed + 2;
    const int second = seed;
    const int third = seed + 1;
    if (!ordered.insert(first).second || !ordered.insert(second).second || !ordered.insert(third).second)
        return 1;
    if (ordered.insert(third).second)
        return 2;
    replacement = ast::move(ordered);
    const auto found = replacement.find(seed + 1);
    if (replacement.empty() || *replacement.begin() != seed || found == replacement.end() || *found != seed + 1 ||
        replacement.find(seed - 1) != replacement.end())
        return 3;
    replacement.clear();
    return replacement.empty() && replacement.begin() == replacement.end() ? 0 : 4;
}

CANN_ASC_STL_HOST_SIMT_API int evaluate_unordered_set(arena_state& state, int seed)
{
    const int_allocator allocator(&state);
    using set_type = ast::unordered_set<int, constant_hash, equal_int, int_allocator>;
    set_type hashed(allocator);
    set_type replacement(allocator);
    if (!hashed.insert(seed).second || !hashed.insert(seed + 1).second || !hashed.insert(seed + 2).second)
        return 1;
    if (hashed.insert(seed + 1).second)
        return 2;
    replacement = ast::move(hashed);
    const auto found = replacement.find(seed + 1);
    if (replacement.empty() || found == replacement.end() || *found != seed + 1 ||
        replacement.find(seed - 1) != replacement.end())
        return 3;
    replacement.clear();
    return replacement.empty() && replacement.begin() == replacement.end() ? 0 : 4;
}

CANN_ASC_STL_HOST_SIMT_API int evaluate_unordered_map(arena_state& state, int seed)
{
    using pair = ast::__arena_pair<const int, int>;
    using pair_allocator = arena_allocator<pair>;
    using map_type = ast::unordered_map<int, int, constant_hash, equal_int, pair_allocator>;
    const pair_allocator allocator(&state);
    map_type mapped(allocator);
    map_type replacement(allocator);
    mapped[seed] = 0;
    mapped[seed + 1] = 7;
    mapped[seed + 2] = 14;
    replacement = ast::move(mapped);
    const auto found = replacement.find(seed + 1);
    if (replacement.empty() || found == replacement.end() || found->second != 7 ||
        replacement.find(seed - 1) != replacement.end())
        return 1;
    replacement.clear();
    return replacement.empty() && replacement.begin() == replacement.end() ? 0 : 2;
}

CANN_ASC_STL_HOST_SIMT_API int evaluate_scoped_allocator(arena_state& state)
{
    ast::scoped_allocator_adaptor<int_allocator> scoped{int_allocator(&state)};
    ast::scoped_allocator_adaptor<int_allocator> copied(scoped);
    if (scoped != copied || !(scoped == copied) || scoped.outer_allocator().state != &state ||
        scoped.inner_allocator().outer_allocator().state != &state || scoped.max_size() != state.capacity / sizeof(int))
        return 3;
    copied = scoped;
    return copied.outer_allocator().state == &state ? 0 : 4;
}

CANN_ASC_STL_API int evaluate_adaptors(int seed)
{
    using sequence = asc_stl_test::fixed_sequence<int, 8>;
    ast::queue<int, sequence> queue, other_queue;
    ast::stack<int, sequence> stack, other_stack;
    ast::priority_queue<int, sequence, less_int> priority, other_priority;
    if (!queue.empty() || !stack.empty() || !priority.empty())
        return 1;
    queue.push(seed);
    queue.emplace(seed + 1);
    stack.push(seed);
    stack.emplace(seed + 1);
    priority.push(seed);
    priority.emplace(seed + 1);
    queue.swap(other_queue);
    stack.swap(other_stack);
    priority.swap(other_priority);
    if (!queue.empty() || !stack.empty() || !priority.empty() || other_queue.size() != 2 ||
        other_queue.front() != seed || other_stack.size() != 2 || other_stack.top() != seed + 1 ||
        other_priority.size() != 2 || other_priority.top() != seed + 1)
        return 2;
    other_stack.pop();
    return other_stack.size() == 1 && other_stack.top() == seed ? 0 : 3;
}

}  // namespace asc_stl_standard_container_test

#endif  // ASC_STL_TEST_STANDARD_CONTAINER_SEMANTICS_H
