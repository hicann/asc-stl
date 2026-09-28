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

int main()
{
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
