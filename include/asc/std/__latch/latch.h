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
#include <asc/__detail/execution_space.h>
#include <asc/std/__atomic/atomic_ref.h>
#include <asc/std/cstddef>
#include <asc/std/limits>

// Inline equivalent of the dev assertion gate for the two count_down
// contracts: AI-core compilation has no assertion mechanism (device asserts
// are no-ops), and host asserts are opt-in through ASC_ENABLE_HOST_ASSERTIONS.
#if !defined(CANN_ASC_STL_DETAIL_LATCH_ASSERT)
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && defined(ASC_ENABLE_HOST_ASSERTIONS)
#include <cassert>
#define CANN_ASC_STL_DETAIL_LATCH_ASSERT(expression, message) assert(((void)(message), static_cast<bool>(expression)))
#else
#define CANN_ASC_STL_DETAIL_LATCH_ASSERT(expression, message) ((void)0)
#endif
#endif  // CANN_ASC_STL_DETAIL_LATCH_ASSERT

CANN_ASC_STL_BEGIN_NAMESPACE

class latch {
public:
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    CANN_ASC_STL_SIMT_API static constexpr ptrdiff_t max() noexcept
    {
        return numeric_limits<ptrdiff_t>::max();
    }
    CANN_ASC_STL_SIMT_API constexpr explicit latch(ptrdiff_t expected) noexcept : counter_(expected)
    {}
    latch(const latch&) = delete;
    latch& operator=(const latch&) = delete;
    CANN_ASC_STL_SIMT_API void count_down(ptrdiff_t update = 1) noexcept
    {
        CANN_ASC_STL_DETAIL_LATCH_ASSERT(update > 0, "latch count_down update must be positive");
        atomic_ref<ptrdiff_t> counter(counter_);
        const ptrdiff_t old = counter.fetch_sub(update, memory_order_release);
        (void)old;  // 诊断占位，值仅用于原子语义验证
        CANN_ASC_STL_DETAIL_LATCH_ASSERT(old >= update, "latch count_down exceeds remaining count");
    }
    CANN_ASC_STL_SIMT_API bool try_wait() const noexcept
    {
        atomic_ref<ptrdiff_t> counter(const_cast<ptrdiff_t&>(counter_));
        return counter.load(memory_order_acquire) == 0;
    }
    CANN_ASC_STL_SIMT_API void wait() const noexcept
    {
        // The blocking count_.wait() of the dev implementation rides on the
        // scoped-atomic notify/wait vocabulary, which this tree does not
        // provide; polling try_wait() is the equivalent wait-until-zero loop.
        while (!try_wait()) {
        }
    }
    CANN_ASC_STL_SIMT_API void arrive_and_wait(ptrdiff_t update = 1) noexcept
    {
        count_down(update);
        wait();
    }
#elif !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    static constexpr ptrdiff_t max() noexcept
    {
        return numeric_limits<ptrdiff_t>::max();  // NOLINT(build/include_what_you_use)
    }
    constexpr explicit latch(ptrdiff_t expected) noexcept : counter_(expected)
    {}
    latch(const latch&) = delete;
    latch& operator=(const latch&) = delete;
    void count_down(ptrdiff_t update = 1) noexcept
    {
        CANN_ASC_STL_DETAIL_LATCH_ASSERT(update > 0, "latch count_down update must be positive");
        const ptrdiff_t old [[maybe_unused]] = __atomic_fetch_sub(&counter_, update, __ATOMIC_RELEASE);
        CANN_ASC_STL_DETAIL_LATCH_ASSERT(old >= update, "latch count_down exceeds remaining count");
    }
    bool try_wait() const noexcept
    {
        return __atomic_load_n(&counter_, __ATOMIC_ACQUIRE) == 0;
    }
    void wait() const noexcept
    {
        // Polling form of the dev blocking wait (no notify/wait vocabulary
        // on the host path of this tree): wait until the count reaches zero.
        while (!try_wait()) {
        }
    }
    void arrive_and_wait(ptrdiff_t update = 1) noexcept
    {
        count_down(update);
        wait();
    }
#else
    explicit latch(ptrdiff_t) = delete;
#endif

private:
    ptrdiff_t counter_;
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___LATCH_LATCH_H
