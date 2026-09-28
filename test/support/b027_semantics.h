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

#ifndef ASC_STL_TEST_B027_SEMANTICS_H
#define ASC_STL_TEST_B027_SEMANTICS_H

#include <asc/std/__cuchar/fixed_c_locale.h>
#include <asc/std/__deque/block_map.h>
#include <asc/std/__deque/deque.h>
#include <asc/std/__functional/default_searcher.h>
#include <asc/std/__list/list.h>
#include <asc/std/__list/node.h>
#include <asc/std/__map/map.h>
#include <asc/std/__numeric/gcd_lcm.h>
#include <asc/std/__numeric/midpoint.h>
#include <asc/std/__tree/tree.h>
#include <asc/std/bitset>
#include <asc/std/forward_list>
#include <asc/std/inplace_vector>
#include <asc/std/list>
#include <asc/std/map>
#include <asc/std/queue>
#include <asc/std/scoped_allocator>
#include <asc/std/set>
#include <asc/std/stack>
#include <asc/std/string>
#include <asc/std/unordered_map>
#include <asc/std/unordered_set>
#include <asc/std/vector>

namespace asc_stl_b027_test {

CANN_ASC_STL_API int evaluate_core()
{
    asc::std::bitset<16> bits(0x1234u);
    if (bits.count() != 5 || !bits.any() || bits.none() || bits.all())
        return 1;
    bits <<= 4;
    if (bits.to_ulong() != 0x2340u)
        return 2;
    bits >>= 8;
    if (bits.to_ullong() != 0x23u)
        return 3;
    bits.flip();
    if (bits.count() != 13)
        return 4;
    const asc::std::bitset<16> mask(0x00ffu);
    if ((bits & mask).to_ulong() != 0xdcu)
        return 5;
    if ((bits | mask).count() != 16)
        return 6;
    if ((bits ^ mask).count() != 11)
        return 7;
    bits.reset();
    if (!bits.none())
        return 8;
    bits.set();
    if (!bits.all() || bits.size() != 16)
        return 9;

    asc::std::inplace_vector<int, 4> values;
    values.unchecked_push_back(3);
    values.unchecked_push_back(5);
    if (values.size() != 2 || values.front() != 3 || values.back() != 5)
        return 10;
    const int pattern[] = {5};
    asc::std::default_searcher<const int*> searcher(pattern, pattern + 1);
    const auto found = searcher(values.begin(), values.end());
    if (found.first != values.begin() + 1 || found.second != values.end())
        return 11;
    if (asc::std::erase(values, 5) != 1u || values.size() != 1u || values.front() != 3)
        return 17;
    values.unchecked_push_back(7);
    const auto erased = asc::std::erase_if(values, [](int value) { return value > 3; });
    if (erased != 1u || values.size() != 1u)
        return 18;
    if (asc::std::gcd(84, -30) != 6 || asc::std::lcm(21, 6) != 42)
        return 12;
    if (asc::std::midpoint(-5, 4) != -1)
        return 13;
    int pointer_values[6]{};
    if (asc::std::midpoint(pointer_values, pointer_values + 5) != pointer_values + 2)
        return 14;
    if (asc::std::midpoint(2.0f, 4.0f) != 3.0f)
        return 15;
    if (asc::std::hash<asc::std::bitset<16>>{}(mask) == asc::std::hash<asc::std::bitset<16>>{}(bits))
        return 16;
    return 0;
}

struct arena_state {
    unsigned char* storage;
    __SIZE_TYPE__ capacity;
    __SIZE_TYPE__ offset;
    int allocations;
    int deallocations;
};

template <class T>
struct arena_allocator {
    using value_type = T;
    using pointer = T*;
    using size_type = __SIZE_TYPE__;
    using difference_type = __PTRDIFF_TYPE__;
    template <class U>
    struct rebind {
        using other = arena_allocator<U>;
    };
    arena_state* state = nullptr;
    CANN_ASC_STL_API arena_allocator() = default;
    CANN_ASC_STL_API explicit arena_allocator(arena_state* value) : state(value)
    {}
    template <class U>
    CANN_ASC_STL_API arena_allocator(const arena_allocator<U>& other) : state(other.state)
    {}
    CANN_ASC_STL_API pointer allocate(size_type count)
    {
        const size_type alignment = alignof(T);
        const size_type start = (state->offset + alignment - 1) / alignment * alignment;
        if (start + count * sizeof(T) > state->capacity)
            return nullptr;
        pointer result = reinterpret_cast<pointer>(state->storage + start);
        state->offset = start + count * sizeof(T);
        ++state->allocations;
        return result;
    }
    CANN_ASC_STL_API void deallocate(pointer, size_type) noexcept
    {
        ++state->deallocations;
    }
    CANN_ASC_STL_API size_type max_size() const noexcept
    {
        return state->capacity / sizeof(T);
    }
    CANN_ASC_STL_API bool operator==(const arena_allocator& other) const noexcept
    {
        return state == other.state;
    }
};

struct less_int {
    CANN_ASC_STL_API bool operator()(int left, int right) const noexcept
    {
        return left < right;
    }
};
struct equal_int {
    CANN_ASC_STL_API bool operator()(int left, int right) const noexcept
    {
        return left == right;
    }
};
struct hash_int {
    CANN_ASC_STL_API __SIZE_TYPE__ operator()(int value) const noexcept
    {
        return static_cast<__SIZE_TYPE__>(value);
    }
};

template <class T, __SIZE_TYPE__ Capacity>
class fixed_sequence {
public:
    using value_type = T;
    using size_type = __SIZE_TYPE__;
    using reference = T&;
    using const_reference = const T&;
    CANN_ASC_STL_API fixed_sequence() = default;
    template <class Alloc>
    CANN_ASC_STL_API explicit fixed_sequence(const Alloc&) noexcept
    {}
    template <class Alloc>
    CANN_ASC_STL_API fixed_sequence(const fixed_sequence& other, const Alloc&) noexcept
    {
        for (size_type index = 0; index < other.size_; ++index)
            values_[index] = other.values_[index];
        size_ = other.size_;
    }
    template <class Alloc>
    CANN_ASC_STL_API fixed_sequence(fixed_sequence&& other, const Alloc&) noexcept
    {
        for (size_type index = 0; index < other.size_; ++index)
            values_[index] = static_cast<T&&>(other.values_[index]);
        size_ = other.size_;
    }
    CANN_ASC_STL_API bool empty() const
    {
        return size_ == 0;
    }
    CANN_ASC_STL_API size_type size() const
    {
        return size_;
    }
    CANN_ASC_STL_API reference front()
    {
        return values_[0];
    }
    CANN_ASC_STL_API const_reference front() const
    {
        return values_[0];
    }
    CANN_ASC_STL_API reference back()
    {
        return values_[size_ - 1];
    }
    CANN_ASC_STL_API const_reference back() const
    {
        return values_[size_ - 1];
    }
    CANN_ASC_STL_API reference operator[](size_type index)
    {
        return values_[index];
    }
    CANN_ASC_STL_API const_reference operator[](size_type index) const
    {
        return values_[index];
    }
    CANN_ASC_STL_API void push_back(const T& value)
    {
        values_[size_++] = value;
    }
    CANN_ASC_STL_API void push_back(T&& value)
    {
        values_[size_++] = static_cast<T&&>(value);
    }
    template <class... Args>
    CANN_ASC_STL_API reference emplace_back(Args&&... args)
    {
        values_[size_] = T(static_cast<Args&&>(args)...);
        return values_[size_++];
    }
    CANN_ASC_STL_API void pop_back()
    {
        --size_;
    }
    CANN_ASC_STL_API void pop_front()
    {
        for (size_type index = 1; index < size_; ++index)
            values_[index - 1] = values_[index];
        --size_;
    }
    CANN_ASC_STL_API void swap(fixed_sequence& other)  // NOLINT(build/include_what_you_use)
    {
        fixed_sequence temporary(*this);
        *this = other;
        other = temporary;
    }

private:
    T values_[Capacity]{};
    size_type size_ = 0;
};

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
CANN_ASC_STL_HOST_API int evaluate_host()
{
    const int core = evaluate_core();
    if (core != 0)
        return core;
    alignas(16) unsigned char storage[4096]{};
    arena_state state{storage, sizeof(storage), 0, 0, 0};
    using allocator = arena_allocator<int>;

    {
        asc::std::vector<int, allocator> values{allocator(&state)};
        values.push_back(1);
        values.emplace_back(2);
        values.reserve(8);
        if (values.size() != 2 || values[1] != 2)
            return 20;
    }
    {
        asc::std::basic_string<char, asc::std::arena_char_traits<char>, arena_allocator<char>> text(
            "asc", arena_allocator<char>(&state));
        text += "-stl";
        if (text.size() != 7 || text.back() != 'l')
            return 21;
    }
    {
        asc::std::deque<int, allocator> values{allocator(&state)};
        values.push_back(2);
        values.push_front(1);
        values.emplace_back(3);
        if (values.size() != 3 || values[0] != 1 || values.back() != 3)
            return 22;
    }
    {
        asc::std::forward_list<int, allocator> values{allocator(&state)};
        values.push_front(1);
        values.emplace_front(2);
        if (values.front() != 2)
            return 23;
    }
    {
        asc::std::list<int, allocator> values{allocator(&state)};
        values.push_back(1);
        values.push_front(0);
        values.emplace_back(2);
        if (values.size() != 3 || values.front() != 0 || values.back() != 2)
            return 24;
    }
    {
        using set_type = asc::std::set<int, less_int, allocator>;
        set_type values{allocator(&state)};
        values.insert(3);
        values.insert(1);
        values.insert(3);
        if (values.size() != 2 || *values.begin() != 1)
            return 25;
    }
    {
        using map_type = asc::std::map<int, int, less_int,  // NOLINT(build/include_what_you_use)
            arena_allocator<asc::std::__arena_pair<const int, int>>>;
        using value_type = typename map_type::value_type;
        map_type values{arena_allocator<value_type>(&state)};
        values[value_type(2, 7).first] = 7;
        if (values[2] != 7)
            return 26;
    }
    {
        using unordered_type = asc::std::unordered_set<int, hash_int, equal_int, allocator>;
        unordered_type values{allocator(&state)};
        values.insert(1);
        values.insert(9);
        values.insert(1);
        if (values.size() != 2 || values.bucket_count() != 8)
            return 27;
    }
    {
        using sequence = fixed_sequence<int, 8>;
        asc::std::stack<int, sequence> stack;
        asc::std::queue<int, sequence> queue;
        asc::std::priority_queue<int, sequence> priority;
        stack.push(4);
        queue.push(5);
        priority.push(2);
        priority.push(8);
        if (stack.top() != 4 || queue.front() != 5 || priority.top() != 8)
            return 28;
    }
    {
        using sequence = fixed_sequence<int, 8>;
        struct allocator_marker {
        } allocator;
        sequence storage{};
        asc::std::stack stack(storage);
        asc::std::queue queue(storage);
        asc::std::priority_queue priority(less_int{}, storage);
        asc::std::stack stack_with_allocator(storage, allocator);
        asc::std::queue queue_with_allocator(storage, allocator);
        asc::std::priority_queue priority_with_allocator(less_int{}, storage, allocator);
        stack.push(4);
        queue.push(5);
        priority.push(8);
        stack_with_allocator.push(6);
        queue_with_allocator.push(7);
        priority_with_allocator.push(9);
        if (stack.top() != 4 || queue.front() != 5 || priority.top() != 8 || stack_with_allocator.top() != 6 ||
            queue_with_allocator.front() != 7 || priority_with_allocator.top() != 9)
            return 31;
    }
    {
        using scoped = asc::std::scoped_allocator_adaptor<allocator>;
        scoped value{allocator(&state)};
        int* address = value.allocate(1);
        value.construct(address, 9);
        if (*address != 9)
            return 29;
        value.destroy(address);
        value.deallocate(address, 1);
    }
    if (state.allocations != state.deallocations)
        return 30;
    return 0;
}
#endif

}  // namespace asc_stl_b027_test

#endif  // ASC_STL_TEST_B027_SEMANTICS_H
