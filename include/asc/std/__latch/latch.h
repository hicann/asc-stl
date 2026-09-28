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

#ifndef CANN_ASC_STL_ASC_STD___LATCH_LATCH_H
#define CANN_ASC_STL_ASC_STD___LATCH_LATCH_H

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
#include <asc/std/atomic>
#include <asc/std/limits>

CANN_ASC_STL_BEGIN_NAMESPACE

class latch {
public:
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    CANN_ASC_STL_SIMT_API static constexpr long long max() noexcept
    {
        return 9223372036854775807LL;
    }
    CANN_ASC_STL_SIMT_API explicit latch(long long expected) noexcept : counter_(static_cast<__INT64_TYPE__>(expected))
    {}
    latch(const latch&) = delete;
    latch& operator=(const latch&) = delete;
    CANN_ASC_STL_SIMT_API void count_down(long long update = 1) noexcept
    {
        atomic_ref<__INT64_TYPE__> counter(counter_);
        (void)counter.fetch_sub(static_cast<__INT64_TYPE__>(update), memory_order_release);
    }
    CANN_ASC_STL_SIMT_API bool try_wait() const noexcept
    {
        atomic_ref<__INT64_TYPE__> counter(const_cast<__INT64_TYPE__&>(counter_));
        return counter.load(memory_order_acquire) == 0;
    }
    CANN_ASC_STL_SIMT_API void wait() const noexcept
    {
        while (!try_wait()) {
        }
    }
    CANN_ASC_STL_SIMT_API void arrive_and_wait(long long update = 1) noexcept
    {
        count_down(update);
        wait();
    }
#elif !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    static constexpr long long max() noexcept
    {
        return 9223372036854775807LL;
    }
    explicit latch(long long expected) noexcept : counter_(expected)
    {}
    latch(const latch&) = delete;
    latch& operator=(const latch&) = delete;
    void count_down(long long update = 1) noexcept
    {
        (void)__atomic_fetch_sub(&counter_, update, __ATOMIC_RELEASE);
    }
    bool try_wait() const noexcept
    {
        return __atomic_load_n(&counter_, __ATOMIC_ACQUIRE) == 0;
    }
    void wait() const noexcept
    {
        while (!try_wait()) {
        }
    }
    void arrive_and_wait(long long update = 1) noexcept
    {
        count_down(update);
        wait();
    }
#else
    explicit latch(long long) = delete;
#endif

private:
    __INT64_TYPE__ counter_;
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___LATCH_LATCH_H
