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

#include <asc/std/deque>
#include <asc/std/forward_list>
#include <asc/std/inplace_vector>
#include <asc/std/list>

#include <cstddef>
#include <deque>
#include <forward_list>
#include <iostream>
#include <list>
#include <utility>

#include "support/counting_allocator.h"

namespace {

using asc_stl_allocation_test::allocation_counts;
using asc_stl_allocation_test::counting_allocator;

struct item {
    inline static int live = 0;
    int value;

    explicit item(int input) noexcept : value(input)
    {
        ++live;
    }
    item(const item& other) noexcept : item(other.value)
    {}
    item(item&& other) noexcept : item(other.value)
    {
        other.value = -1;
    }
    item& operator=(const item&) = default;
    item& operator=(item&& other) noexcept
    {
        value = other.value;
        other.value = -1;
        return *this;
    }
    ~item()
    {
        --live;
    }
};

using deque = asc::std::deque<item, counting_allocator<item>>;

bool compare_deque(deque& actual, const std::deque<int>& expected)
{
    if (actual.size() != expected.size() || actual.empty() != expected.empty() ||
        item::live != static_cast<int>(expected.size()))
        return false;
    auto first = actual.begin();
    auto last = actual.end();
    const auto size = static_cast<std::ptrdiff_t>(expected.size());
    if (last - first != size || first - last != -size || first + size != last || last - size != first)
        return false;
    if (expected.empty())
        return true;
    if (!(first < last) || !(last > first) || !(first <= first) || !(last >= first) ||
        actual.front().value != expected.front() || actual.back().value != expected.back())
        return false;
    for (std::ptrdiff_t i = 0; i < size; ++i) {
        if (first[i].value != expected[i] || actual[i].value != expected[i])
            return false;
    }
    return true;
}

bool check_wraparound()
{
    allocation_counts count;
    {
        deque actual{counting_allocator<item>(count)};
        std::deque<int> expected;
        for (int i = 0; i < 13; ++i) {
            actual.emplace_front(i);
            expected.emplace_front(i);
        }
        if (!compare_deque(actual, expected))
            return false;
        const auto allocations = count.allocated;
        for (int i = 0; i < 513; ++i) {
            actual.emplace_back(i * 2);
            expected.emplace_back(i * 2);
            actual.pop_front();
            expected.pop_front();
            if (!compare_deque(actual, expected))
                return false;
        }
        for (int i = 0; i < 513; ++i) {
            actual.pop_back();
            expected.pop_back();
            actual.emplace_front(-i);
            expected.emplace_front(-i);
            if (!compare_deque(actual, expected))
                return false;
        }
        if (count.allocated != allocations)
            return false;
        actual.clear();
        expected.clear();
        if (!compare_deque(actual, expected))
            return false;
        actual.emplace_front(72);
        expected.emplace_front(72);
        if (!compare_deque(actual, expected))
            return false;
    }
    return item::live == 0 && count.outstanding() == 0;
}

template <class Sequence, class Reference>
bool compare_linked(Sequence& actual, const Reference& expected)
{
    auto cursor = actual.begin();
    for (int value : expected) {
        if (cursor == actual.end() || (*cursor++).value != value)
            return false;
    }
    return cursor == actual.end() && actual.empty() == expected.empty();
}

bool check_linked()
{
    allocation_counts from, to;
    {
        using list = asc::std::list<item, counting_allocator<item>>;
        using forward = asc::std::forward_list<item, counting_allocator<item>>;
        list actual_list{counting_allocator<item>(from)};
        forward actual_forward{counting_allocator<item>(from)};
        std::list<int> expected_list;
        std::forward_list<int> expected_forward;
        for (int i = 0; i < 64; ++i) {
            actual_list.emplace_back(i);
            expected_list.emplace_back(i);
            actual_forward.emplace_front(i);
            expected_forward.emplace_front(i);
        }
        for (int i = 0; i < 12; ++i) {
            actual_list.pop_front();
            actual_list.pop_back();
            expected_list.pop_front();
            expected_list.pop_back();
            actual_forward.pop_front();
            expected_forward.pop_front();
        }

        list moved_list{counting_allocator<item>(to)};
        forward moved_forward{counting_allocator<item>(to)};
        moved_list.emplace_back(-1);
        moved_forward.emplace_front(-1);
        moved_list = std::move(actual_list);
        moved_forward = std::move(actual_forward);
        if (!actual_list.empty() || !actual_forward.empty() || to.outstanding() != 0 ||
            !compare_linked(moved_list, expected_list) || !compare_linked(moved_forward, expected_forward) ||
            item::live != 92 || from.outstanding() != 92)
            return false;
        moved_list.clear();
        moved_forward.clear();
        if (item::live != 0 || from.outstanding() != 0)
            return false;
    }
    return item::live == 0 && from.outstanding() == 0 && to.outstanding() == 0;
}

bool check_inline_capacity()
{
    {
        asc::std::inplace_vector<item, 5> source;
        for (int i = 0; i < 5; ++i)
            source.unchecked_emplace_back(i);
        item external(17);
        if (source.try_push_back(std::move(external)) || source.try_emplace_back(23) || external.value != 17 ||
            source.size() != 5 || item::live != 6)
            return false;
        auto next = source.erase(source.cbegin() + 1, source.cbegin() + 3);
        if (next != source.begin() + 1 || next->value != 3 || source.size() != 3 || item::live != 4)
            return false;
        auto copy = source;
        if (copy.size() != 3 || copy[0].value != 0 || copy[1].value != 3 || copy[2].value != 4 || item::live != 7)
            return false;
        source.clear();
        copy.swap(source);
        if (!copy.empty() || source.size() != 3 || source.back().value != 4 || item::live != 4)
            return false;
        auto moved = std::move(source);
        if (source.size() != 3 || moved.size() != 3 || moved[1].value != 3 || source[1].value != -1 || item::live != 7)
            return false;
    }
    return item::live == 0;
}

}  // namespace

int main()
{
    if (!check_wraparound()) {
        std::cerr << "Deque ring order or lifetime mismatch\n";
        return 1;
    }
    if (!check_linked()) {
        std::cerr << "Linked sequence lifetime or ownership mismatch\n";
        return 2;
    }
    if (!check_inline_capacity()) {
        std::cerr << "In-place sequence capacity or lifetime mismatch\n";
        return 3;
    }
    return 0;
}
