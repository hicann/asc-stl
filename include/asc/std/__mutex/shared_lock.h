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

#ifndef CANN_ASC_STL_ASC_STD___MUTEX_SHARED_LOCK_H
#define CANN_ASC_STL_ASC_STD___MUTEX_SHARED_LOCK_H

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

template <class Mutex>
class shared_lock {
public:
    using mutex_type = Mutex;

    CANN_ASC_STL_API shared_lock() noexcept = default;
    CANN_ASC_STL_API explicit shared_lock(mutex_type& mutex) : mutex_(&mutex), owns_(true)
    {
        mutex_->lock_shared();
    }
    CANN_ASC_STL_API shared_lock(mutex_type& mutex, defer_lock_t) noexcept : mutex_(&mutex)
    {}
    CANN_ASC_STL_API shared_lock(mutex_type& mutex, try_to_lock_t) : mutex_(&mutex), owns_(mutex.try_lock_shared())
    {}
    CANN_ASC_STL_API shared_lock(mutex_type& mutex, adopt_lock_t) noexcept : mutex_(&mutex), owns_(true)
    {}
    shared_lock(const shared_lock&) = delete;
    shared_lock& operator=(const shared_lock&) = delete;
    CANN_ASC_STL_API shared_lock(shared_lock&& other) noexcept : mutex_(other.mutex_), owns_(other.owns_)
    {
        other.mutex_ = nullptr;
        other.owns_ = false;
    }
    CANN_ASC_STL_API shared_lock& operator=(shared_lock&& other) noexcept
    {
        if (owns_)
            mutex_->unlock_shared();
        mutex_ = other.mutex_;
        owns_ = other.owns_;
        other.mutex_ = nullptr;
        other.owns_ = false;
        return *this;
    }
    CANN_ASC_STL_API ~shared_lock()
    {
        if (owns_)
            mutex_->unlock_shared();
    }
    CANN_ASC_STL_API void lock()
    {
        mutex_->lock_shared();
        owns_ = true;
    }
    CANN_ASC_STL_API bool try_lock()
    {
        owns_ = mutex_->try_lock_shared();
        return owns_;
    }
    CANN_ASC_STL_API void unlock()
    {
        mutex_->unlock_shared();
        owns_ = false;
    }
    CANN_ASC_STL_API void swap(  // NOLINT(build/include_what_you_use)
        shared_lock& other) noexcept
    {
        mutex_type* mutex = mutex_;
        const bool owns = owns_;
        mutex_ = other.mutex_;
        owns_ = other.owns_;
        other.mutex_ = mutex;
        other.owns_ = owns;
    }
    CANN_ASC_STL_API mutex_type* release() noexcept
    {
        mutex_type* value = mutex_;
        mutex_ = nullptr;
        owns_ = false;
        return value;
    }
    CANN_ASC_STL_API mutex_type* mutex() const noexcept
    {
        return mutex_;
    }
    CANN_ASC_STL_API bool owns_lock() const noexcept
    {
        return owns_;
    }
    CANN_ASC_STL_API explicit operator bool() const noexcept
    {
        return owns_;
    }

private:
    mutex_type* mutex_ = nullptr;
    bool owns_ = false;
};

template <class Mutex>
CANN_ASC_STL_API void swap(  // NOLINT(build/include_what_you_use)
    shared_lock<Mutex>& left, shared_lock<Mutex>& right) noexcept
{
    left.swap(right);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MUTEX_SHARED_LOCK_H
