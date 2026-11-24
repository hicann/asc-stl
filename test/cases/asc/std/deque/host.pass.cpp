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

#include <asc/memory>
#include <asc/std/deque>
#include <asc/std/queue>
#include <asc/std/stack>

#include <stdexcept>

template <bool NoThrow>
struct AdaptorSwapProbe {
    using value_type = int;
    using size_type = unsigned;
    using reference = int&;
    using const_reference = const int&;
    void swap(AdaptorSwapProbe&) noexcept(NoThrow)
    {}  // NOLINT(build/include_what_you_use)
};

template <bool NoThrow>
using ProbeQueue = asc::std::queue<int, AdaptorSwapProbe<NoThrow>>;
template <bool NoThrow>
using ProbeStack = asc::std::stack<int, AdaptorSwapProbe<NoThrow>>;
static_assert(noexcept(asc::std::declval<ProbeQueue<true>&>().swap(asc::std::declval<ProbeQueue<true>&>())));
static_assert(!noexcept(asc::std::declval<ProbeQueue<false>&>().swap(asc::std::declval<ProbeQueue<false>&>())));
static_assert(noexcept(asc::std::declval<ProbeStack<true>&>().swap(asc::std::declval<ProbeStack<true>&>())));
static_assert(!noexcept(asc::std::declval<ProbeStack<false>&>().swap(asc::std::declval<ProbeStack<false>&>())));

template <class T>
class fixed_sequence {
public:
    using value_type = T;
    using size_type = unsigned long;
    using reference = T&;
    using const_reference = const T&;

    bool empty() const
    {
        return size_ == 0;
    }
    size_type size() const
    {
        return size_;
    }
    reference front()
    {
        return values_[0];
    }
    const_reference front() const
    {
        return values_[0];
    }
    reference back()
    {
        return values_[size_ - 1];
    }
    const_reference back() const
    {
        return values_[size_ - 1];
    }
    reference operator[](size_type index)
    {
        return values_[index];
    }
    const_reference operator[](size_type index) const
    {
        return values_[index];
    }
    void push_back(const T& value)
    {
        values_[size_++] = value;
    }
    void push_back(T&& value)
    {
        values_[size_++] = static_cast<T&&>(value);
    }
    template <class... Args>
    reference emplace_back(Args&&... args)
    {
        values_[size_] = T(static_cast<Args&&>(args)...);
        return values_[size_++];
    }
    void pop_front()
    {
        for (size_type index = 1; index < size_; ++index)
            values_[index - 1] = values_[index];
        --size_;
    }
    void pop_back()
    {
        --size_;
    }
    void swap(fixed_sequence& other)  // NOLINT(build/include_what_you_use)
    {
        fixed_sequence temporary = *this;
        *this = other;
        other = temporary;
    }

private:
    T values_[16]{};
    size_type size_ = 0;
};

struct DequeElement {
    int value;
    int* live;

    DequeElement(int v, int& count) : value(v), live(&count)
    {
        ++*live;
    }
    DequeElement(const DequeElement&) = delete;
    DequeElement& operator=(const DequeElement&) = delete;
    ~DequeElement()
    {
        --*live;
    }
};

bool test_deque_slot_reuse(bool insert_front, int& live)
{
    constexpr int capacity = 16;
    alignas(32) unsigned char storage[512]{};
    asc::monotonic_arena arena(storage, sizeof(storage));
    asc::std::deque<DequeElement, asc::arena_allocator<DequeElement>> values{asc::arena_allocator<DequeElement>{arena}};
    auto append = [&](int key) -> DequeElement& {
        return insert_front ? values.emplace_front(key, live) : values.emplace_back(key, live);
    };

    DequeElement& first = append(0);
    for (int key = 1; key < capacity; ++key)
        append(key);
    if (&first != &(insert_front ? values.back() : values.front()))
        return false;
    for (int side = 0; side < 2; ++side) {
        try {
            if (side == 0)
                values.emplace_front(99, live);
            else
                values.emplace_back(99, live);
            return false;
        } catch (const std::length_error&) {
        }
    }
    const auto allocated = arena.used();
    for (int key = capacity; key < 5 * capacity; ++key) {
        DequeElement* retained = &values[capacity / 2];
        if (insert_front)
            values.pop_back();
        else
            values.pop_front();
        append(key);
        if (retained != &values[insert_front ? capacity / 2 + 1 : capacity / 2 - 1])
            return false;
        auto begin = values.begin();
        auto end = values.end();
        if (live != capacity || values.size() != capacity || end - begin != capacity || begin - end != -capacity ||
            !(begin < end) || begin + capacity != end || end - capacity != begin || allocated != arena.used())
            return false;
        const auto& view = values;
        for (int pos = 0; pos < capacity; ++pos) {
            const int expected = insert_front ? key - pos : key + pos + 1 - capacity;
            if (view[pos].value != expected || begin[pos].value != expected)
                return false;
        }
    }
    values.clear();
    if (!values.empty() || live != 0)
        return false;
    append(42);
    return values.front().value == 42;
}

int main()
{
    int live = 0;
    try {
        if (!test_deque_slot_reuse(false, live) || live != 0 || !test_deque_slot_reuse(true, live) || live != 0)
            return 6;
    } catch (const std::length_error&) {
        return 7;
    }
    unsigned char storage[2048]{};
    asc::monotonic_arena arena(storage, sizeof(storage));
    asc::std::deque<int, asc::arena_allocator<int>> values{asc::arena_allocator<int>(arena)};
    values.push_back(2);
    values.push_front(1);
    values.emplace_back(3);
    if (values.size() != 3 || values[0] != 1 || values[2] != 3)
        return 1;
    values.pop_front();
    values.pop_back();

    asc::std::queue<int, fixed_sequence<int>> queue;
    queue.push(4);
    queue.emplace(5);
    if (queue.front() != 4 || queue.back() != 5)
        return 2;
    queue.pop();
    asc::std::priority_queue<int, fixed_sequence<int>> priority;
    priority.push(3);
    priority.push(8);
    priority.push(5);
    if (priority.top() != 8)
        return 3;
    priority.pop();
    return values.front() == 2 && queue.front() == 5 && priority.top() == 5 ? 0 : 4;
}
