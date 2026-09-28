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

#ifndef CANN_ASC_STL_ASC_STD___BARRIER_BARRIER_H
#define CANN_ASC_STL_ASC_STD___BARRIER_BARRIER_H

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
#include <asc/std/__chrono/duration.h>
#include <asc/std/atomic>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __barrier_detail {
struct __empty_completion {
    CANN_ASC_STL_HOST_SIMT_API void operator()() noexcept
    {}
};
}  // namespace __barrier_detail

template <class CompletionFunction = __barrier_detail::__empty_completion>
class barrier {
public:
    class arrival_token {
        friend class barrier;
        CANN_ASC_STL_API explicit arrival_token(__UINT64_TYPE__ phase) noexcept : phase_(phase)
        {}
        __UINT64_TYPE__ phase_ = 0;
    };

    barrier(const barrier&) = delete;
    barrier& operator=(const barrier&) = delete;

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    CANN_ASC_STL_SIMT_API static constexpr long long max() noexcept
    {
        return 9223372036854775807LL;
    }
    CANN_ASC_STL_SIMT_API explicit barrier(long long expected, CompletionFunction completion = CompletionFunction())
        : expected_(expected), remaining_(expected), completion_(static_cast<CompletionFunction&&>(completion))
    {}

    CANN_ASC_STL_SIMT_API arrival_token arrive(long long update = 1)
    {
        atomic_ref<__UINT64_TYPE__> phase(phase_);
        atomic_ref<__INT64_TYPE__> remaining(remaining_);
        const __UINT64_TYPE__ value = phase.load(memory_order_acquire);
        const __INT64_TYPE__ previous = remaining.fetch_sub(static_cast<__INT64_TYPE__>(update), memory_order_acq_rel);
        if (previous == update) {
            atomic_ref<__INT64_TYPE__> expected(expected_);
            completion_();
            remaining.store(expected.load(memory_order_relaxed), memory_order_release);
            (void)phase.fetch_add(1, memory_order_release);
        }
        return arrival_token(value);
    }
    CANN_ASC_STL_SIMT_API void wait(arrival_token&& token) const
    {
        atomic_ref<__UINT64_TYPE__> phase(const_cast<__UINT64_TYPE__&>(phase_));
        while (phase.load(memory_order_acquire) == token.phase_) {
        }
    }
    CANN_ASC_STL_SIMT_API void arrive_and_wait()
    {
        arrival_token token = arrive();
        wait(static_cast<arrival_token&&>(token));
    }
    CANN_ASC_STL_SIMT_API void arrive_and_drop()
    {
        atomic_ref<__INT64_TYPE__> expected(expected_);
        (void)expected.fetch_sub(1, memory_order_relaxed);
        (void)arrive();
    }
#elif !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    static constexpr long long max() noexcept
    {
        return 9223372036854775807LL;
    }
    explicit barrier(long long expected, CompletionFunction completion = CompletionFunction())
        : expected_(expected), remaining_(expected), completion_(static_cast<CompletionFunction&&>(completion))
    {}
    arrival_token arrive(long long update = 1)
    {
        const unsigned long long value = __atomic_load_n(&phase_, __ATOMIC_ACQUIRE);
        const long long previous = __atomic_fetch_sub(&remaining_, update, __ATOMIC_ACQ_REL);
        if (previous == update) {
            completion_();
            __atomic_store_n(&remaining_, __atomic_load_n(&expected_, __ATOMIC_RELAXED), __ATOMIC_RELEASE);
            (void)__atomic_fetch_add(&phase_, 1ULL, __ATOMIC_RELEASE);
        }
        return arrival_token(value);
    }
    void wait(arrival_token&& token) const
    {
        while (__atomic_load_n(&phase_, __ATOMIC_ACQUIRE) == token.phase_) {
        }
    }
    void arrive_and_wait()
    {
        arrival_token token = arrive();
        wait(static_cast<arrival_token&&>(token));
    }
    void arrive_and_drop()
    {
        (void)__atomic_fetch_sub(&expected_, 1, __ATOMIC_RELAXED);
        (void)arrive();
    }
#else
    explicit barrier(long long, CompletionFunction = CompletionFunction()) = delete;
#endif

private:
    __INT64_TYPE__ expected_;
    __INT64_TYPE__ remaining_;
    __UINT64_TYPE__ phase_{0};
    CompletionFunction completion_;
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___BARRIER_BARRIER_H
