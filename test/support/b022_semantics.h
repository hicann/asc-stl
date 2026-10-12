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

/* Copyright 2026 湖北多样性算力应用创新研究院 */

#ifndef ASC_STL_TEST_SUPPORT_B022_SEMANTICS_H
#define ASC_STL_TEST_SUPPORT_B022_SEMANTICS_H

#include <asc/std/atomic>
#include <asc/std/ccomplex>
#include <asc/std/__algorithm/all_of.h>
#include <asc/std/__algorithm/any_of.h>
#include <asc/std/__algorithm/copy_if.h>
#include <asc/std/__algorithm/find_if.h>
#include <asc/std/__algorithm/find_if_not.h>
#include <asc/std/__algorithm/for_each.h>
#include <asc/std/__algorithm/generate.h>
#include <asc/std/__algorithm/make_heap.h>
#include <asc/std/__algorithm/is_partitioned.h>
#include <asc/std/__algorithm/none_of.h>
#include <asc/std/__algorithm/remove_copy.h>
#include <asc/std/__algorithm/remove_copy_if.h>
#include <asc/std/__algorithm/replace.h>
#include <asc/std/__algorithm/replace_copy.h>
#include <asc/std/__algorithm/replace_copy_if.h>
#include <asc/std/__algorithm/replace_if.h>
#include <asc/std/__algorithm/reverse_copy.h>
#include <asc/std/__algorithm/rotate.h>
#include <asc/std/__algorithm/shift_left.h>
#include <asc/std/__algorithm/shift_right.h>
#include <asc/std/__algorithm/sort_heap.h>
#include <asc/std/__algorithm/transform.h>
#include <asc/std/__semaphore/counting_semaphore.h>

namespace asc_stl_b022_test {

struct greater_than {
    int bound;
    CANN_ASC_STL_API constexpr bool operator()(int value) const
    {
        return value > bound;
    }
};

struct counting_false_predicate {
    int* calls;
    CANN_ASC_STL_API constexpr bool operator()(int) const
    {
        ++*calls;
        return false;
    }
};

struct counting_functor {
    int calls;
    CANN_ASC_STL_API constexpr counting_functor() : calls(0)
    {}
    CANN_ASC_STL_API constexpr void operator()(int)  // NOLINT(readability/casting)
    {
        ++calls;
    }
};

struct generator {
    int base;
    CANN_ASC_STL_API constexpr int operator()()
    {
        return base++;
    }
};

CANN_ASC_STL_API constexpr int evaluate_predicate_algorithms()
{
    int failures = 0;
    const int data[] = {1, 2, 3, 4};
    failures += !asc::std::all_of(data, data + 4, greater_than{0});
    failures += asc::std::all_of(data, data + 4, greater_than{1});
    failures += !asc::std::all_of(data, data, greater_than{0});
    failures += !asc::std::any_of(data, data + 4, greater_than{3});
    failures += asc::std::any_of(data, data, greater_than{3});
    failures += !asc::std::none_of(data, data + 4, greater_than{9});
    failures += asc::std::none_of(data, data + 4, greater_than{2});

    failures += asc::std::find_if(data, data + 4, greater_than{2}) != data + 2;
    failures += asc::std::find_if(data, data + 4, greater_than{9}) != data + 4;
    failures += asc::std::find_if_not(data, data + 4, greater_than{1}) != data;
    failures += asc::std::find_if_not(data, data + 4, greater_than{0}) != data + 4;

    const counting_functor visited = asc::std::for_each(data, data + 4, counting_functor{});
    failures += visited.calls != 4;

    const int partitioned[] = {8, 9, 1, 2};
    const int mixed[] = {1, 8, 2, 9};
    failures += !asc::std::is_partitioned(partitioned, partitioned + 4, greater_than{4});
    failures += asc::std::is_partitioned(mixed, mixed + 4, greater_than{4});
    failures += !asc::std::is_partitioned(partitioned, partitioned, greater_than{4});
    int partition_calls = 0;
    const int one_false = 0;
    failures += !asc::std::is_partitioned(&one_false, &one_false + 1, counting_false_predicate{&partition_calls});
    failures += partition_calls != 1;

    int copied[4] = {};
    failures += asc::std::copy_if(data, data + 4, copied, greater_than{2}) != copied + 2;
    failures += copied[0] != 3 || copied[1] != 4;
    failures += asc::std::copy_if(data, data, copied, greater_than{0}) != copied;

    int replaced[6] = {};
    const int source[] = {1, 2, 3, 2, 5};
    int working[] = {1, 2, 3, 2, 5};
    asc::std::replace(working, working, 2, 9);
    failures += working[1] != 2;
    asc::std::replace(working, working + 5, 2, 9);
    failures += working[0] != 1 || working[1] != 9 || working[3] != 9;
    asc::std::replace_if(working, working + 5, greater_than{8}, 0);
    failures += working[1] != 0 || working[3] != 0 || working[4] != 5;

    failures += asc::std::replace_copy(source, source + 5, replaced, 2, 7) != replaced + 5;
    failures += replaced[0] != 1 || replaced[1] != 7 || replaced[3] != 7 || replaced[4] != 5;
    failures += asc::std::replace_copy_if(source, source + 5, replaced, greater_than{4}, 0) != replaced + 5;
    failures += replaced[4] != 0 || replaced[2] != 3;

    int removed[5] = {};
    failures += asc::std::remove_copy(source, source + 5, removed, 2) != removed + 3;
    failures += removed[0] != 1 || removed[1] != 3 || removed[2] != 5;
    failures += asc::std::remove_copy_if(source, source + 5, removed, greater_than{2}) != removed + 3;
    failures += removed[0] != 1 || removed[1] != 2 || removed[2] != 2;

    const int to_reverse[] = {1, 2, 3, 4};
    int reversed[4] = {};
    failures += asc::std::reverse_copy(to_reverse, to_reverse + 4, reversed) != reversed + 4;
    failures += reversed[0] != 4 || reversed[3] != 1;
    failures += asc::std::reverse_copy(to_reverse, to_reverse, reversed) != reversed;

    int generated[3] = {};
    asc::std::generate(generated, generated + 3, generator{10});
    failures += generated[0] != 10 || generated[1] != 11 || generated[2] != 12;
    asc::std::generate(generated, generated, generator{0});

    int transformed[4] = {};
    failures += asc::std::transform(  // NOLINT(build/include_what_you_use)
                    to_reverse, to_reverse + 4, transformed, [](int value) { return value + 1; }) != transformed + 4;
    failures += transformed[0] != 2 || transformed[3] != 5;
    const int addends[] = {10, 20, 30, 40};
    failures +=
        asc::std::transform(to_reverse, to_reverse + 4, addends, transformed,  // NOLINT(build/include_what_you_use)
            [](int left, int right) { return left + right; }) != transformed + 4;
    failures += transformed[0] != 11 || transformed[3] != 44;
    return failures;
}

CANN_ASC_STL_API constexpr int evaluate_reordering_algorithms()
{
    int failures = 0;
    int rotated[] = {1, 2, 3, 4, 5};
    failures += asc::std::rotate(rotated, rotated + 2, rotated + 5) != rotated + 3;
    failures += rotated[0] != 3 || rotated[1] != 4 || rotated[2] != 5 || rotated[3] != 1 || rotated[4] != 2;
    failures += asc::std::rotate(rotated, rotated, rotated + 5) != rotated + 5;
    failures += asc::std::rotate(rotated, rotated + 5, rotated + 5) != rotated;
    int pair[] = {1, 2};
    failures += asc::std::rotate(pair, pair + 1, pair + 2) != pair + 1;
    failures += pair[0] != 2 || pair[1] != 1;
    int one_element_tail[] = {1, 2, 3, 4, 5};
    failures += asc::std::rotate(one_element_tail, one_element_tail + 4, one_element_tail + 5) != one_element_tail + 1;
    failures += one_element_tail[0] != 5 || one_element_tail[1] != 1 || one_element_tail[2] != 2 ||
        one_element_tail[3] != 3 || one_element_tail[4] != 4;
    int one_element_head[] = {1, 2, 3, 4, 5, 6};
    failures += asc::std::rotate(one_element_head, one_element_head + 1, one_element_head + 6) != one_element_head + 5;
    failures += one_element_head[0] != 2 || one_element_head[1] != 3 || one_element_head[2] != 4 ||
        one_element_head[3] != 5 || one_element_head[4] != 6 || one_element_head[5] != 1;

    int shifted[] = {1, 2, 3, 4, 5};
    failures += asc::std::shift_left(shifted, shifted + 5, 2) != shifted + 3;
    failures += shifted[0] != 3 || shifted[1] != 4 || shifted[2] != 5;
    failures += asc::std::shift_left(shifted, shifted + 5, 0) != shifted + 5;
    failures += asc::std::shift_left(shifted, shifted + 5, 9) != shifted;

    int right[] = {1, 2, 3, 4, 5};
    failures += asc::std::shift_right(right, right + 5, 2) != right + 2;
    failures += right[2] != 1 || right[3] != 2 || right[4] != 3;
    failures += asc::std::shift_right(right, right + 5, 0) != right;
    failures += asc::std::shift_right(right, right + 5, 9) != right + 5;

    int heap[] = {1, 5, 2, 4, 3};
    asc::std::make_heap(heap, heap + 5);
    asc::std::sort_heap(heap, heap + 5);
    failures += heap[0] != 1 || heap[1] != 2 || heap[2] != 3 || heap[3] != 4 || heap[4] != 5;
    int descending[] = {1, 3, 2};
    const auto descending_order = [](int left, int right) { return left > right; };
    asc::std::make_heap(descending, descending + 3, descending_order);
    asc::std::sort_heap(descending, descending + 3, descending_order);
    failures += descending[0] != 3 || descending[1] != 2 || descending[2] != 1;
    asc::std::sort_heap(heap, heap);
    return failures;
}

CANN_ASC_STL_API constexpr int evaluate_ccomplex()
{
    int failures = 0;
    asc::std::complex<float> value(3.0f, 4.0f);
    failures += value.real() != 3.0f || value.imag() != 4.0f;
    value += asc::std::complex<float>(1.0f, 1.0f);
    failures += value.real() != 4.0f || value.imag() != 5.0f;
    const asc::std::complex<float> summed = value + asc::std::complex<float>(1.0f, -1.0f);
    failures += summed.real() != 5.0f || summed.imag() != 4.0f;
    failures += !(value == asc::std::complex<float>(4.0f, 5.0f));
    return failures;
}

CANN_ASC_STL_API int evaluate_atomic()
{
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    int failures = 0;
    asc::std::atomic_int value{7};
    failures += !value.is_lock_free();
    failures += value.load() != 7;
    failures += value.load(asc::std::memory_order_acquire) != 7;
    value.store(9);
    failures += value.load() != 9;
    value.store(11, asc::std::memory_order_release);
    failures += value.exchange(4) != 11;
    int expected = 4;
    failures += !value.compare_exchange_strong(expected, 6, asc::std::memory_order_acq_rel);
    expected = 5;
    failures += value.compare_exchange_strong(expected, 8, asc::std::memory_order_seq_cst) || expected != 6;
    failures += value.fetch_add(3) != 6;
    failures += value.fetch_sub(2) != 9;
    failures += value.fetch_and(12) != 7;
    failures += value.fetch_or(8) != 4;
    failures += value.fetch_xor(1) != 12;
    failures += value.load() != 13;
    failures += asc::std::atomic_load(&value) != 13;
    asc::std::atomic_store(&value, 2);
    failures += asc::std::atomic_exchange(&value, 5) != 2;
    expected = 5;
    failures += !asc::std::atomic_compare_exchange_strong(&value, &expected, 6);
    failures += asc::std::atomic_fetch_add(&value, 4) != 6;
    failures += asc::std::atomic_fetch_sub_explicit(&value, 1, asc::std::memory_order_relaxed) != 10;
    failures += asc::std::atomic_is_lock_free(&value) != 1;
    asc::std::atomic_init(&value, 1);
    failures += value.load() != 1;

    asc::std::atomic<char> narrow{3};
    failures += narrow.fetch_add(1) != 3 || narrow.load() != 4;
    asc::std::atomic<unsigned short> wide{65535};
    failures += wide.fetch_add(1) != 65535 || wide.load() != 0;
    asc::std::atomic_bool flag_value{true};
    failures += !flag_value.load();
    failures += !flag_value.exchange(false);

    asc::std::atomic<long long> counter{1};
    failures += counter.fetch_add(2) != 1 || counter.load() != 3;
    int referenced = 10;
    asc::std::atomic_ref<int> reference(referenced);
    failures += reference.fetch_sub(1) != 10 || reference.load() != 9;

    asc::std::atomic_flag flag = CANN_ASC_STL_ATOMIC_FLAG_INIT;
    failures += flag.test_and_set();
    failures += !flag.test();
    failures += !flag.test_and_set();
    flag.clear();
    failures += flag.test();
    failures += asc::std::atomic_flag_test_and_set(&flag);
    asc::std::atomic_flag_clear_explicit(&flag, asc::std::memory_order_release);
    failures += asc::std::atomic_flag_test(&flag);

    asc::std::atomic_thread_fence(asc::std::memory_order_relaxed);
    asc::std::atomic_thread_fence(asc::std::memory_order_release);
    failures += asc::std::kill_dependency(3) != 3;
    asc::std::atomic_int initialized CANN_ASC_STL_ATOMIC_VAR_INIT(5);
    failures += initialized.load() != 5;
    return failures;
#else
    // Device atomic objects must live in GlobalMemory; see evaluate_device_atomic.
    return 0;
#endif
}

CANN_ASC_STL_API int evaluate_semaphore()
{
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    int failures = 0;
    failures += asc::std::counting_semaphore<4>::max() != 4;
    asc::std::counting_semaphore<2> semaphore(0);
    failures += semaphore.try_acquire();
    semaphore.release(2);
    failures += !semaphore.try_acquire();
    failures += !semaphore.try_acquire();
    failures += semaphore.try_acquire();
    semaphore.release();
    semaphore.acquire();
    failures += semaphore.try_acquire();
    asc::std::counting_semaphore<1> binary(1);
    failures += !binary.try_acquire();
    failures += binary.try_acquire();
    binary.release(1);
    binary.acquire();
    failures += binary.try_acquire();
    return failures;
#else
    // Device semaphore state must live in GlobalMemory; see evaluate_device_atomic.
    return 0;
#endif
}

CANN_ASC_STL_API int evaluate_all()
{
    int failures = (evaluate_predicate_algorithms() != 0 ? 1 : 0) | (evaluate_reordering_algorithms() != 0 ? 2 : 0) |
        (evaluate_ccomplex() != 0 ? 4 : 0);
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    failures |= (evaluate_atomic() != 0 ? 8 : 0) | (evaluate_semaphore() != 0 ? 16 : 0);
#endif
    return failures;
}

CANN_ASC_STL_API constexpr int evaluate_reordering_only()
{
    return evaluate_reordering_algorithms() != 0 ? 2 : 0;
}

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
// Ascend SIMT atomics only operate on GlobalMemory storage, so every Device
// object below is placed in caller-owned GM positions of the output buffer.
template <class OutputPointer>
CANN_ASC_STL_SIMT_API void evaluate_device_atomic(OutputPointer output)
{
    int failures = 0;

    auto* shared = reinterpret_cast<asc::std::atomic<__INT32_TYPE__>*>(&output[0]);
    shared->store(0, asc::std::memory_order_relaxed);
    failures += shared->fetch_add(3, asc::std::memory_order_acq_rel) != 0;
    failures += shared->fetch_add(4, asc::std::memory_order_relaxed) != 3;
    __INT32_TYPE__ expected = 7;
    failures +=
        !shared->compare_exchange_strong(expected, 10, asc::std::memory_order_acq_rel, asc::std::memory_order_acquire);
    failures += shared->load(asc::std::memory_order_acquire) != 10;
    failures += shared->exchange(4, asc::std::memory_order_release) != 10;
    failures += asc::std::atomic_exchange(shared, 6) != 4;
    failures += asc::std::atomic_load_explicit(shared, asc::std::memory_order_acquire) != 6;
    asc::std::atomic_init(shared, 1);
    failures += asc::std::atomic_fetch_add(shared, 5) != 1;

    auto* narrow = reinterpret_cast<asc::std::atomic<__UINT16_TYPE__>*>(&output[8]);
    narrow->store(65535, asc::std::memory_order_relaxed);
    failures += narrow->fetch_add(1, asc::std::memory_order_release) != 65535;
    failures += narrow->load(asc::std::memory_order_relaxed) != 0;

    auto* flag = reinterpret_cast<asc::std::atomic_flag*>(&output[16]);
    flag->clear(asc::std::memory_order_relaxed);
    failures += flag->test_and_set(asc::std::memory_order_acq_rel);
    failures += !flag->test(asc::std::memory_order_acquire);
    failures += !flag->test_and_set(asc::std::memory_order_acq_rel);
    asc::std::atomic_flag_clear(flag);
    failures += asc::std::atomic_flag_test(flag);

    asc::std::atomic_thread_fence(asc::std::memory_order_relaxed);
    asc::std::atomic_thread_fence(asc::std::memory_order_release);
    failures += asc::std::kill_dependency(3) != 3;

    *reinterpret_cast<__INT64_TYPE__*>(&output[24]) = 0;
    auto& semaphore = *reinterpret_cast<asc::std::counting_semaphore<2>*>(&output[24]);
    semaphore.release(2);
    failures += !semaphore.try_acquire();
    failures += !semaphore.try_acquire();
    failures += semaphore.try_acquire();
    semaphore.release(1);
    semaphore.acquire();
    failures += semaphore.try_acquire();
    failures += asc::std::counting_semaphore<1>::max() != 1;
    output[31] = failures;
}
#endif

}  // namespace asc_stl_b022_test

#endif  // ASC_STL_TEST_SUPPORT_B022_SEMANTICS_H
