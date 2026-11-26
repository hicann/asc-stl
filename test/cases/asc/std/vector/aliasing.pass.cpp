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

#include <cstdio>
#include <cstdlib>
#include <memory>
#include <new>
#include <stdexcept>
#include <vector>

#include "support/vector_aliasing_semantics.h"

namespace {

void require(bool condition, const char* message) noexcept
{
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", message);
        std::exit(EXIT_FAILURE);
    }
}

struct counters {
    int alive = 0;
    int allocations = 0;
    int deallocations = 0;
    int moves = 0;
    int copies = 0;
    int move_budget = -1;
    bool fail_copy = false;
    int fail_allocation = 0;
};

template <class T>
struct counting_allocator {
    counters* state;
    T* allocate(__SIZE_TYPE__ count)
    {
        if (state->fail_allocation == 1)
            return nullptr;
        if (state->fail_allocation == 2)
            throw std::bad_alloc();
        T* result = std::allocator<T>{}.allocate(count);
        ++state->allocations;
        return result;
    }
    void deallocate(T* pointer, __SIZE_TYPE__ count)
    {
        ++state->deallocations;
        std::allocator<T>{}.deallocate(pointer, count);
    }
};

struct observed {
    int value;
    counters* state;
    observed(int number, counters* events) : value(number), state(events)
    {
        ++state->alive;
    }
    observed(const observed& other) : value(other.value), state(other.state)
    {
        if (state->fail_copy)
            throw std::runtime_error("injected copy failure");
        ++state->copies;
        ++state->alive;
    }
    observed(observed&& other) : value(other.value), state(other.state)
    {
        if (state->move_budget == 0)
            throw std::runtime_error("injected move failure");
        if (state->move_budget > 0)
            --state->move_budget;
        other.value = -1;
        ++state->moves;
        ++state->alive;
    }
    ~observed()
    {
        --state->alive;
    }
};

using observed_vector = asc::std::vector<observed, counting_allocator<observed>>;

void check_integer_differential()
{
    asc::std::vector<int, std::allocator<int>> actual{std::allocator<int>{}};
    std::vector<int> expected;
    actual.push_back(11);
    expected.push_back(11);
    actual.push_back(22);
    expected.push_back(22);
    for (int index = 0; index < 64; ++index) {
        const __SIZE_TYPE__ source = static_cast<__SIZE_TYPE__>(index) % actual.size();
        if (index % 2 == 0) {
            actual.push_back(actual[source]);
            expected.push_back(expected[source]);
        } else {
            int& added = actual.emplace_back(actual[source]);
            expected.emplace_back(expected[source]);
            require(&added == &actual.back(), "emplace_back returned the wrong element reference");
        }
        require(actual.size() == expected.size(), "vector size differs from std::vector");
        for (__SIZE_TYPE__ element = 0; element < actual.size(); ++element)
            require(actual[element] == expected[element], "vector element differs from std::vector");
    }
}

void check_constructor_counts()
{
    counters state;
    {
        observed_vector values{counting_allocator<observed>{&state}};
        values.emplace_back(7, &state);
        require(state.moves == 0 && state.copies == 0, "initial emplacement copied or moved an element");
        values.emplace_back(9, &state);
        values.emplace_back(values[0].value, &state);
        require(values[2].value == 7 && state.alive == 3 && state.moves == 2 && state.copies == 0,
            "growth changed the aliased value or construction counts");
        observed& appended = values.emplace_back(values[1].value, &state);
        require(appended.value == 9 && &appended == &values[3], "in-capacity emplacement returned the wrong element");
        require(state.moves == 2 && state.copies == 0, "in-capacity emplacement copied or moved existing elements");
    }
    require(state.alive == 0 && state.allocations == state.deallocations, "normal growth leaked objects or storage");
}

void check_appended_constructor_failure()
{
    counters state;
    {
        observed_vector values{counting_allocator<observed>{&state}};
        values.emplace_back(7, &state);
        values.emplace_back(9, &state);
        const auto address = values.data();
        const auto capacity = values.capacity();
        state.fail_copy = true;
        try {
            values.push_back(values[0]);
            require(false, "appended copy construction did not throw");
        } catch (const std::runtime_error&) {
            require(values.size() == 2 && values.capacity() == capacity && values.data() == address,
                "failed appended construction changed vector storage or size");
            require(values[0].value == 7 && values[1].value == 9 && state.alive == 2 && state.moves == 0,
                "failed appended construction changed existing elements or construction counts");
            require(state.allocations == state.deallocations + 1,
                "failed appended construction leaked replacement storage");
        }
        state.fail_copy = false;
        values.push_back(values[1]);
        require(values.size() == 3 && values.back().value == 9, "vector could not append after a constructor failure");
    }
    require(state.alive == 0 && state.allocations == state.deallocations,
        "constructor-failure test leaked objects or storage");
}

void check_relocation_failure()
{
    counters state;
    {
        observed_vector values{counting_allocator<observed>{&state}};
        values.emplace_back(7, &state);
        values.emplace_back(9, &state);
        const auto address = values.data();
        const auto capacity = values.capacity();
        state.move_budget = 1;
        try {
            values.push_back(values[1]);
            require(false, "element relocation did not throw");
        } catch (const std::runtime_error&) {
            require(values.size() == 2 && values.capacity() == capacity && values.data() == address,
                "failed relocation changed vector storage or size");
            require(state.alive == 2 && state.allocations == state.deallocations + 1,
                "failed relocation leaked replacement objects or storage");
        }
        // A throwing move may leave original elements moved from, but they
        // remain owned, destructible and available for clearing/reuse.
        state.move_budget = -1;
        values.clear();
        values.emplace_back(31, &state);
        require(
            values.size() == 1 && values.front().value == 31, "vector could not be reused after relocation failure");
    }
    require(state.alive == 0 && state.allocations == state.deallocations,
        "relocation-failure test leaked objects or storage");
}

void check_pop_back_lifetime()
{
    counters state;
    {
        observed_vector values{counting_allocator<observed>{&state}};
        values.reserve(2);
        values.emplace_back(17, &state);
        values.emplace_back(29, &state);
        const auto capacity = values.capacity();
        const auto address = values.data();
        const auto allocations = state.allocations;
        require(values.get_allocator().state == &state, "vector lost its allocator state");

        values.pop_back();
        require(values.size() == 1 && values.end() == values.begin() + 1 && values.back().value == 17,
            "pop_back removed the wrong element or did not advance the end");
        require(state.alive == 1 && values.data() == address && values.capacity() == capacity &&
                state.allocations == allocations && state.deallocations == 0,
            "pop_back did not destroy exactly one object or released storage");

        values.pop_back();
        require(values.empty() && values.begin() == values.end() && state.alive == 0,
            "pop_back did not transition the last element to an empty vector");
        require(values.data() == address && values.capacity() == capacity && state.deallocations == 0,
            "pop_back released the last element's storage");
        values.emplace_back(41, &state);
        require(values.back().value == 41 && state.alive == 1 && state.allocations == allocations,
            "vector could not reuse capacity after becoming empty");
    }
    require(state.alive == 0 && state.allocations == state.deallocations, "pop_back leaked objects or storage");
}

void check_allocation_failure(int mode)
{
    counters state;
    {
        observed_vector values{counting_allocator<observed>{&state}};
        values.emplace_back(7, &state);
        values.emplace_back(9, &state);
        const auto address = values.data();
        const auto capacity = values.capacity();
        state.fail_allocation = mode;
        try {
            values.emplace_back(values[0].value, &state);
            require(false, "allocation failure did not throw std::bad_alloc");
        } catch (const std::bad_alloc&) {
            require(values.size() == 2 && values.capacity() == capacity && values.data() == address,
                "allocation failure changed vector storage or size");
            require(values[0].value == 7 && values[1].value == 9 && state.alive == 2,
                "allocation failure changed existing elements or lifetimes");
            require(state.moves == 0 && state.copies == 0, "allocation failure copied or moved an element");
        }
    }
    require(state.alive == 0 && state.allocations == state.deallocations,
        "allocation-failure test leaked objects or storage");
}

}  // namespace

int main()
{
    check_integer_differential();
    const int alias_result = asc_stl_vector_aliasing_test::evaluate();
    require(alias_result == 0, "shared vector aliasing semantics failed");
    check_constructor_counts();
    check_pop_back_lifetime();
    check_appended_constructor_failure();
    check_relocation_failure();
    check_allocation_failure(1);
    check_allocation_failure(2);
}
