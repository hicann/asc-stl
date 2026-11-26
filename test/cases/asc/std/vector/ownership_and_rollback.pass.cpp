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

#include <asc/std/vector>

#include <iostream>
#include <new>
#include <utility>

#include "support/counting_allocator.h"

namespace {

using asc_stl_allocation_test::allocation_counts;
using asc_stl_allocation_test::counting_allocator;

struct move_failure {};

struct element {
    inline static int live = 0;
    inline static int moves_before_failure = -1;

    explicit element(int input) noexcept : value(input)
    {
        ++live;
    }

    element(const element& other) noexcept : element(other.value)
    {}

    element(element&& other) : value(other.value)
    {
        if (moves_before_failure == 0)
            throw move_failure{};
        if (moves_before_failure > 0)
            --moves_before_failure;
        other.value = -1;
        ++live;
    }

    ~element()
    {
        --live;
    }

    int value;
};

using vector = asc::std::vector<element, counting_allocator<element>>;

bool check_allocation_failure()
{
    allocation_counts counts;
    {
        vector data{counting_allocator<element>(counts)};
        data.reserve(2);
        data.emplace_back(3);
        data.emplace_back(5);
        const auto* original = data.data();
        const auto capacity = data.capacity();
        counts.fail_next = true;
        try {
            data.reserve(capacity + 5);
            return false;
        } catch (const std::bad_alloc&) {
            if (data.data() != original || data.capacity() != capacity || data.size() != 2 || data[0].value != 3 ||
                data[1].value != 5 || element::live != 2)
                return false;
        }
        counts.fail_next = true;
        try {
            data.push_back(data.front());
            return false;
        } catch (const std::bad_alloc&) {
            if (data.data() != original || data.size() != 2 || data[0].value != 3 || data[1].value != 5 ||
                counts.outstanding() != 1)
                return false;
        }
        data.push_back(data.back());
        if (data.size() != 3 || data.back().value != 5 || element::live != 3)
            return false;
    }
    return counts.outstanding() == 0 && element::live == 0;
}

bool check_element_failure(bool grow)
{
    allocation_counts old_counts, new_counts;
    {
        vector data{counting_allocator<element>(old_counts)};
        data.reserve(3);
        data.emplace_back(11);
        data.emplace_back(17);
        data.emplace_back(23);
        const auto* original = data.data();
        const auto capacity = data.capacity();
        element::moves_before_failure = 1;
        bool threw = false;
        try {
            if (grow)
                data.emplace_back(data.back().value);
            else
                data.reserve(capacity + 1);
        } catch (const move_failure&) {
            threw = true;
        }
        element::moves_before_failure = -1;
        // The first source element has moved from. The old vector still owns
        // every source element and the spare allocation has been released.
        if (!threw || data.data() != original || data.capacity() != capacity || data.size() != 3 ||
            data[0].value != -1 || data[1].value != 17 || data[2].value != 23 || element::live != 3 ||
            old_counts.outstanding() != 1)
            return false;

        vector moved{counting_allocator<element>(new_counts)};
        moved.emplace_back(99);
        moved = std::move(data);
        if (!data.empty() || moved.data() != original || moved.size() != 3 || moved.back().value != 23 ||
            new_counts.outstanding() != 0 || element::live != 3)
            return false;
        data.emplace_back(42);
        moved.clear();
        if (element::live != 1 || !moved.empty() || data.front().value != 42)
            return false;
    }
    return old_counts.outstanding() == 0 && new_counts.outstanding() == 0 && element::live == 0;
}

}  // namespace

int main()
{
    if (!check_allocation_failure() || !check_element_failure(false) || !check_element_failure(true)) {
        std::cerr << "Vector ownership or rollback mismatch\n";
        return 1;
    }
    return 0;
}
