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

#ifndef CANN_ASC_STL_ASC_STD___SEMAPHORE_COUNTING_SEMAPHORE_H
#define CANN_ASC_STL_ASC_STD___SEMAPHORE_COUNTING_SEMAPHORE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__atomic/atomic_ref.h>
#include <asc/std/climits>
#include <asc/std/cstddef>
#include <asc/std/cstdint>

CANN_ASC_STL_BEGIN_NAMESPACE

// Untimed counting and binary semaphore over the standard atomic backend.
// Device waiters must belong to a participant set whose execution model
// guarantees forward progress; oversubscribed ordinary grids and timed waits
// are outside this contract.
template <ptrdiff_t least_max_value = INT_MAX>
class counting_semaphore {
    static_assert(least_max_value >= 0, "asc::std::counting_semaphore requires a nonnegative least maximum");

public:
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    CANN_ASC_STL_SIMT_API static constexpr long long max() noexcept
    {
        return least_max_value;
    }

    CANN_ASC_STL_SIMT_API explicit counting_semaphore(long long initial) noexcept : count_(initial)
    {}

    counting_semaphore(const counting_semaphore&) = delete;
    counting_semaphore& operator=(const counting_semaphore&) = delete;

    CANN_ASC_STL_SIMT_API void release(long long update = 1) noexcept
    {
        ::asc::std::atomic_ref<__INT64_TYPE__> counter(count_);
        (void)counter.fetch_add(static_cast<__INT64_TYPE__>(update), memory_order_release);
    }

    CANN_ASC_STL_SIMT_API bool try_acquire() noexcept
    {
        ::asc::std::atomic_ref<__INT64_TYPE__> counter(count_);
        __INT64_TYPE__ expected = counter.load(memory_order_relaxed);
        while (expected > 0) {
            if (counter.compare_exchange_strong(expected, expected - 1, memory_order_acquire, memory_order_acquire)) {
                return true;
            }
        }
        return false;
    }

    CANN_ASC_STL_SIMT_API void acquire() noexcept
    {
        while (!try_acquire()) {
        }
    }
#elif !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    static constexpr long long max() noexcept
    {
        return least_max_value;
    }

    explicit counting_semaphore(long long initial = 0) noexcept : count_(initial)
    {}

    counting_semaphore(const counting_semaphore&) = delete;
    counting_semaphore& operator=(const counting_semaphore&) = delete;

    void release(long long update = 1) noexcept
    {
        __atomic_fetch_add(&count_, static_cast<__INT64_TYPE__>(update), __ATOMIC_RELEASE);
    }

    bool try_acquire() noexcept
    {
        __INT64_TYPE__ expected = __atomic_load_n(&count_, __ATOMIC_RELAXED);
        while (expected > 0) {
            if (__atomic_compare_exchange_n(
                    &count_, &expected, expected - 1, false, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)) {
                return true;
            }
        }
        return false;
    }

    void acquire() noexcept
    {
        while (!try_acquire()) {
        }
    }
#else
    counting_semaphore() = delete;
    explicit counting_semaphore(long long) = delete;
#endif

private:
    __INT64_TYPE__ count_;
};

// [thread.semaphore.binary]: alias for a counting semaphore with a maximum count of 1.
using binary_semaphore = counting_semaphore<1>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___SEMAPHORE_COUNTING_SEMAPHORE_H
