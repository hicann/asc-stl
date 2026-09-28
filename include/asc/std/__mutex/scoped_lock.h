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

#ifndef CANN_ASC_STL_DETAIL_LOCK_TAG_VOCABULARY
#define CANN_ASC_STL_DETAIL_LOCK_TAG_VOCABULARY

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __lock_detail {
template <int Value>
struct __lock_tag {};
}  // namespace __lock_detail

using defer_lock_t = __lock_detail::__lock_tag<0>;
using try_to_lock_t = __lock_detail::__lock_tag<1>;
using adopt_lock_t = __lock_detail::__lock_tag<2>;
inline constexpr defer_lock_t defer_lock{};
inline constexpr try_to_lock_t try_to_lock{};
inline constexpr adopt_lock_t adopt_lock{};

CANN_ASC_STL_END_NAMESPACE

#endif

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __lock_detail {
struct __scoped_defer_t {};
}  // namespace __lock_detail

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
    CANN_ASC_STL_API bool __try_lock_all()
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
    CANN_ASC_STL_API bool __try_lock_all()
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
