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

#ifndef ASC_STL_W08_RUNTIME_SEMANTICS_H
#define ASC_STL_W08_RUNTIME_SEMANTICS_H

#include <asc/memory>
#include <asc/iterator>
#include <asc/mdspan>
#include <asc/std/__new/nonallocating_new.h>
#include <asc/std/barrier>
#include <asc/std/chrono>
#include <asc/std/deque>
#include <asc/std/forward_list>
#include <asc/std/functional>
#include <asc/std/latch>
#include <asc/std/map>
#include <asc/std/memory>
#include <asc/std/mutex>
#include <asc/std/queue>
#include <asc/std/scoped_allocator>
#include <asc/std/semaphore>
#include <asc/std/shared_mutex>
#include <asc/std/set>
#include <asc/std/stack>
#include <asc/std/string>
#include <asc/std/unordered_map>
#include <asc/std/unordered_set>
#include <asc/std/variant>
#include <asc/std/vector>
#include <asc/tensor_copy>

#include "../../../../support/b028_allocator.h"
#include "../../../../support/tensor_descriptor_boundaries.h"
#include "../../../../support/w09_w10_semantics.h"
#include "../../../../support/w11_w12_semantics.h"
#include "../../../../support/v1_algorithm_semantics.h"

namespace asc_stl_w08_runtime {

#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <class ResultPointer>
CANN_ASC_STL_API unsigned int evaluate_single_thread(asc::monotonic_arena& arena, ResultPointer result);
#endif

#if CANN_ASC_STL_DETAIL_SIMD_COMPILATION()
template <class ResultPointer, class InputPointer>
CANN_ASC_STL_DEVICE_API void evaluate_simd(ResultPointer result, InputPointer input)
{
    __ubuf__ unsigned int stage[24];
    const unsigned int extents[2] = {3, 5};
    const unsigned int source_strides[2] = {8, 1};
    const unsigned int destination_strides[2] = {8, 1};
    const unsigned int left_padding[2] = {0, 1};
    const unsigned int right_padding[2] = {0, 2};
    const auto descriptor =
        asc::make_tensor_copy_descriptor<2>(extents, source_strides, destination_strides, left_padding, right_padding);
    const auto pipeline = asc::make_pipeline(0, 1);
    unsigned int failures =
        asc::tensor_load_async(pipeline, 0, asc::ub_span<unsigned int>(stage, 24),
            asc::gm_span<const unsigned int>(input, 24), descriptor, 0u) != asc::tensor_copy_status::success;
    pipeline.consumer_wait(0);
    pipeline.wait();
    for (unsigned int index = 0; index < 24; ++index)
        result[index] = stage[index];

    const unsigned int zero_extent[2] = {3, 0};
    const auto invalid = asc::make_tensor_copy_descriptor<2>(
        zero_extent, source_strides, destination_strides, left_padding, right_padding);
    failures += asc::tensor_load_async(pipeline, 0, asc::ub_span<unsigned int>(stage, 24),
                    asc::gm_span<const unsigned int>(input, 24), invalid, 0u) != asc::tensor_copy_status::zero_extent;
    failures +=
        asc::tensor_load_async(pipeline, 1, asc::ub_span<unsigned int>(stage, 24),
            asc::gm_span<const unsigned int>(input, 24), descriptor, 0u) != asc::tensor_copy_status::invalid_stage;
    failures +=
        asc::tensor_load_async(pipeline, 0, asc::ub_span<unsigned int>(stage, 24),
            asc::gm_span<const unsigned int>(input, 1), descriptor, 0u) != asc::tensor_copy_status::insufficient_source;
    unsigned char storage[1024]{};
    asc::monotonic_arena arena(storage, sizeof(storage));
    failures += evaluate_single_thread(arena, result);
    result[31] = failures;
    result[60] = failures;
}
#endif

#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
struct mutex_probe {
    bool locked = false;
    CANN_ASC_STL_API void lock()
    {
        locked = true;
    }
    CANN_ASC_STL_API bool try_lock()
    {
        if (locked)
            return false;
        locked = true;
        return true;
    }
    CANN_ASC_STL_API void unlock()
    {
        locked = false;
    }
    CANN_ASC_STL_API void lock_shared()
    {
        lock();
    }
    CANN_ASC_STL_API bool try_lock_shared()
    {
        return try_lock();
    }
    CANN_ASC_STL_API void unlock_shared()
    {
        unlock();
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

template <class T>
class fixed_sequence {
public:
    using value_type = T;
    using size_type = __SIZE_TYPE__;
    using reference = T&;
    using const_reference = const T&;
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
    CANN_ASC_STL_API void pop_front()
    {
        for (size_type index = 1; index < size_; ++index)
            values_[index - 1] = values_[index];
        --size_;
    }
    CANN_ASC_STL_API void pop_back()
    {
        --size_;
    }
    CANN_ASC_STL_API void swap(fixed_sequence& other)  // NOLINT(build/include_what_you_use)
    {
        fixed_sequence temporary = *this;
        *this = other;
        other = temporary;
    }

private:
    T values_[8]{};
    size_type size_ = 0;
};

template <class ResultPointer>
CANN_ASC_STL_API unsigned int evaluate_single_thread(asc::monotonic_arena& arena, ResultPointer result)
{
    unsigned int failures = 0;
    failures += asc::std::plus<int>{}(2, 3) != 5;
    mutex_probe first;
    mutex_probe second;
    {
        asc::std::lock_guard<mutex_probe> guard(first);
        failures += !first.locked;
    }
    {
        asc::std::scoped_lock<mutex_probe, mutex_probe> guard(first, second);
        failures += !first.locked || !second.locked;
    }
    asc::std::unique_lock<mutex_probe> unique(first, asc::std::defer_lock);
    failures += !unique.try_lock();
    unique.unlock();
    asc::std::shared_lock<mutex_probe> shared(first);
    failures += !shared.owns_lock();
    shared.unlock();
    asc::std::queue<int, fixed_sequence<int>> queue;
    queue.push(4);
    queue.emplace(7);
    failures += queue.front() != 4 || queue.back() != 7;
    queue.pop();
    failures += queue.front() != 7;
    asc::std::priority_queue<int, fixed_sequence<int>> priority;
    priority.push(2);
    priority.push(9);
    priority.push(4);
    failures += priority.top() != 9;
    priority.pop();
    failures += priority.top() != 4;
    asc::std::deque<int, asc::arena_allocator<int>> deque{asc::arena_allocator<int>(arena)};
    deque.push_back(5);
    deque.push_front(3);
    deque.emplace_back(8);
    failures += deque.size() != 3 || deque.front() != 3 || deque.back() != 8 || deque[1] != 5;
    deque.pop_front();
    deque.pop_back();
    failures += deque.front() != 5;

    asc::std::vector<int, asc::arena_allocator<int>> vector{asc::arena_allocator<int>(arena)};
    vector.push_back(2);
    vector.emplace_back(4);
    failures += vector.size() != 2 || vector.front() != 2 || vector.back() != 4;
    asc::std::basic_string<char, asc::std::arena_char_traits<char>, asc::arena_allocator<char>> text{
        asc::arena_allocator<char>(arena)};
    text += 'a';
    text += 's';
    text += 'c';
    text += '-';
    text += 's';
    text += 't';
    text += 'l';
    failures += text.size() != 7 || text.back() != 'l';

    auto counting = asc::make_counting_iterator(3);
    failures += *counting != 3 || counting[4] != 7;
    auto strided = asc::make_strided_iterator(result, 2);
    failures += strided.base() != result || strided.stride() != 2;
    using extents_type = asc::std::extents<__SIZE_TYPE__, 2, asc::std::dynamic_extent>;
    const extents_type extents(3);
    asc::std::layout_right::mapping<extents_type> mapping(extents);
    failures += mapping(1, 2) != 5 || mapping.required_span_size() != 6;
    asc::gm_mdspan<unsigned int, extents_type> view(result + 96, extents);
    asc::std::array<__SIZE_TYPE__, 2> indices{0, 2};
    view[indices] = 17;
    failures += result[98] != 17 || view.extent(1) != 3;
    asc::steps<2> stride_values(3, 1);
    asc::layout_stride_relaxed::mapping<extents_type, asc::steps<2>> relaxed(extents, stride_values, 0);
    failures += relaxed(1, 2) != 5 || relaxed.required_span_size() != 6;
    asc::std::variant<int, unsigned int> variant(asc::std::in_place_index<0>, 9);
    failures += !asc::std::holds_alternative<int>(variant) || *asc::std::get_if<int>(&variant) != 9;
    asc::std::chrono::duration<int> duration(7);
    failures += duration.count() != 7;
    alignas(16) unsigned char aligned_storage[32]{};
    void* aligned_pointer = aligned_storage + 1;
    __SIZE_TYPE__ aligned_space = 31;
    failures += asc::std::align(8, 8, aligned_pointer, aligned_space) == nullptr;
    failures += asc_stl_w09_w10_test::evaluate_iterator() != 0;
    failures += asc_stl_v1_algorithm_test::evaluate() != 0;
    volatile unsigned int descriptor_maximum = ~0u;
    failures += asc_stl_tensor_descriptor_test::evaluate(descriptor_maximum);
    failures += asc_stl_w09_w10_test::evaluate_alignment_chrono() != 0;
    failures += asc_stl_w09_w10_test::evaluate_memory_variant() != 0;
    failures += asc_stl_w09_w10_test::evaluate_mutex() != 0;
    failures += asc_stl_w09_w10_test::evaluate_mdspan() != 0;
    failures += asc_stl_w09_w10_test::evaluate_extension_mdspan() != 0;
#if !CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    failures += asc_stl_w11_w12_test::evaluate(result) != 0;
#endif

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    asc_stl_b028_test::arena_state node_state{reinterpret_cast<unsigned char*>(result + 128), 1536, 0, 0, 0};
    using node_allocator = asc_stl_b028_test::arena_allocator<int>;
    asc::std::forward_list<int, node_allocator> forward{node_allocator(&node_state)};
    forward.push_front(3);
    forward.emplace_front(2);
    failures += forward.front() != 2;
    asc::std::set<int, less_int, node_allocator> set{node_allocator(&node_state)};
    set.insert(4);
    set.insert(1);
    failures += set.size() != 2 || *set.begin() != 1;
    using pair_type = asc::std::__arena_pair<const int, int>;
    using pair_allocator = asc_stl_b028_test::arena_allocator<pair_type>;
    asc::std::unordered_map<int, int, hash_int, equal_int, pair_allocator> map{pair_allocator(&node_state)};
    map[pair_type(2, 0).first] = 8;
    failures += map.size() != 1 || map.find(2)->second != 8;
    asc::std::unordered_set<int, hash_int, equal_int, node_allocator> unordered{node_allocator(&node_state)};
    unordered.insert(3);
    unordered.insert(3);
    failures += unordered.size() != 1;
#endif
    return failures;
}

#endif

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
template <class ResultPointer>
CANN_ASC_STL_SIMT_API void evaluate_simt(ResultPointer result, unsigned int thread_count)
{
    auto& semaphore = *reinterpret_cast<asc::std::counting_semaphore<1024>*>(&result[8]);
    auto& completion = *reinterpret_cast<asc::std::latch*>(&result[12]);
    auto& phases = *reinterpret_cast<asc::std::barrier<>*>(&result[16]);
    if (threadIdx.x == 0) {
        ::new (static_cast<void*>(&result[16])) asc::std::barrier<>(thread_count);
        semaphore.release(2);
        bool acquired = semaphore.try_acquire() && semaphore.try_acquire() && !semaphore.try_acquire();
        semaphore.release();
        semaphore.acquire();
        acquired = acquired && !semaphore.try_acquire();
        result[3] = acquired ? 0u : 1u;
    }
    asc_syncthreads();
    auto token = phases.arrive();
    asc_syncthreads();
    phases.wait(static_cast<decltype(token)&&>(token));
    completion.count_down();
    asc_syncthreads();
#if defined(ASC_STL_W08_HARDWARE)
    completion.wait();
#else
    const bool ready = completion.try_wait();
    asc::std::atomic_ref<__UINT32_TYPE__> failures(result[3]);
    (void)failures.fetch_add(ready ? 0u : 1u, asc::std::memory_order_relaxed);
#endif
    asc::std::atomic_ref<__UINT32_TYPE__> completed(result[0]);
    (void)completed.fetch_add(1, asc::std::memory_order_relaxed);
    asc_syncthreads();
    if (threadIdx.x == 0) {
        result[480] = asc_stl_w11_w12_test::evaluate_sort();
        result[481] = asc_stl_w11_w12_test::evaluate_nth_and_stable();
        result[482] = asc_stl_w11_w12_test::evaluate_foundation();
        result[483] = asc_stl_w11_w12_test::evaluate_ranges_and_vocabulary();
        result[1] = completed.load(asc::std::memory_order_acquire) == thread_count && result[3] == 0 ? 0u : 1u;
        asc::monotonic_arena arena(reinterpret_cast<unsigned char*>(&result[32]), 896);
        result[2] = evaluate_single_thread(arena, result);
        unsigned int w11_w12_failures = 0;
        for (unsigned int group = 0; group < thread_count; ++group)
            w11_w12_failures += result[480 + group];
        result[61] = w11_w12_failures;
        result[2] += w11_w12_failures != 0;
    }
}
#endif

}  // namespace asc_stl_w08_runtime

#endif  // ASC_STL_W08_RUNTIME_SEMANTICS_H
