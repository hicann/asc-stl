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

#ifndef CANN_ASC_STL_ASC_STD___MUTEX_SCOPED_LOCK_H
#define CANN_ASC_STL_ASC_STD___MUTEX_SCOPED_LOCK_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__mutex/lock_tags.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __lock_detail {
struct __scoped_defer_t {};

// Backoff for the variadic try-lock retry loop. A bare spin risks starving
// a mutex holder co-resident on the same scheduler slot, so each failed
// attempt pays a small delay before retrying. Hosted builds hint the
// processor; device builds have no scheduler to yield to and only delay.
// Device-side constraint: the retry loop can only make progress when the
// mutex holder is not co-scheduled with this thread on the same
// warp/scheduling bundle -- keep owners and waiters on distinct cores, or
// provide a Mutex whose lock() blocks.
CANN_ASC_STL_API void retry_backoff() noexcept
{
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#if defined(__x86_64__) || defined(__i386__)
    __builtin_ia32_pause();
#elif defined(__aarch64__)
    asm volatile("yield" ::: "memory");
#endif
#else
    for (int delay = 0; delay < 32; ++delay) {
        __asm__ __volatile__("" ::: "memory");
    }
#endif
}
}  // namespace __lock_detail

// Registered contract shapes are scoped_lock<> and scoped_lock<Mutex>; the
// variadic partial specialization below is a deliberate extension beyond
// that surface (same class template name, forward-compatible superset for
// multi-mutex dead-avoidance). Behavior of the extension is anchored by the
// same acquire/adopt semantics as the registered shapes.

template <class... Mutexes>
class scoped_lock;

template <>
class scoped_lock<> {
public:
    CANN_ASC_STL_API scoped_lock() noexcept = default;
    CANN_ASC_STL_API explicit scoped_lock(adopt_lock_t) noexcept
    {}

private:
    template <class...>
    friend class scoped_lock;
    CANN_ASC_STL_API explicit scoped_lock(__lock_detail::__scoped_defer_t) noexcept
    {}
    CANN_ASC_STL_API bool __try_lock_all() noexcept
    {
        return true;
    }
};

template <class Mutex>
class scoped_lock<Mutex> {
public:
    using mutex_type = Mutex;
    CANN_ASC_STL_API explicit scoped_lock(Mutex& mutex) : mutex_(mutex)
    {
        mutex_.lock();
    }
    CANN_ASC_STL_API scoped_lock(adopt_lock_t, Mutex& mutex) noexcept : mutex_(mutex)
    {}
    CANN_ASC_STL_API ~scoped_lock()
    {
        mutex_.unlock();
    }
    scoped_lock(const scoped_lock&) = delete;
    scoped_lock& operator=(const scoped_lock&) = delete;

private:
    template <class...>
    friend class scoped_lock;
    CANN_ASC_STL_API scoped_lock(__lock_detail::__scoped_defer_t, Mutex& mutex) noexcept : mutex_(mutex)
    {}
    // All three __try_lock_all shapes are noexcept on purpose: the contract
    // behind this class is the registered "explicitly non-throwing Device
    // Lockable" mutex. A Mutex::try_lock that escapes an exception here used
    // to unwind through nodes that unconditionally unlock in their
    // destructors -- including nodes that had not acquired their mutex --
    // so the misuse now fails fast via termination instead of corrupting
    // lock state during unwinding.
    CANN_ASC_STL_API bool __try_lock_all() noexcept
    {
        return mutex_.try_lock();
    }
    Mutex& mutex_;
};

template <class Mutex, class... Mutexes>
class scoped_lock<Mutex, Mutexes...> {
public:
    CANN_ASC_STL_API explicit scoped_lock(Mutex& mutex, Mutexes&... mutexes)
        : mutex_(mutex), remaining_(__lock_detail::__scoped_defer_t{}, mutexes...)
    {
        while (!__try_lock_all()) {
            __lock_detail::retry_backoff();
        }
    }
    CANN_ASC_STL_API scoped_lock(adopt_lock_t, Mutex& mutex, Mutexes&... mutexes) noexcept
        : mutex_(mutex), remaining_(adopt_lock, mutexes...)
    {}
    CANN_ASC_STL_API ~scoped_lock()
    {
        mutex_.unlock();
    }
    scoped_lock(const scoped_lock&) = delete;
    scoped_lock& operator=(const scoped_lock&) = delete;

private:
    template <class...>
    friend class scoped_lock;
    CANN_ASC_STL_API scoped_lock(__lock_detail::__scoped_defer_t, Mutex& mutex, Mutexes&... mutexes) noexcept
        : mutex_(mutex), remaining_(__lock_detail::__scoped_defer_t{}, mutexes...)
    {}
    CANN_ASC_STL_API bool __try_lock_all() noexcept
    {
        if (!mutex_.try_lock())
            return false;
        if (remaining_.__try_lock_all())
            return true;
        mutex_.unlock();
        return false;
    }
    Mutex& mutex_;
    scoped_lock<Mutexes...> remaining_;
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MUTEX_SCOPED_LOCK_H
