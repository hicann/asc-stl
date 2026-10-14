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

#ifndef CANN_ASC_STL_ASC_STD___MUTEX_UNIQUE_LOCK_H
#define CANN_ASC_STL_ASC_STD___MUTEX_UNIQUE_LOCK_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__exception/terminate.h>
#include <asc/std/__mutex/lock_tags.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Mutex>
class unique_lock {
public:
    using mutex_type = Mutex;

    CANN_ASC_STL_API unique_lock() noexcept = default;
    CANN_ASC_STL_API explicit unique_lock(mutex_type& mutex) : mutex_(&mutex), owns_(true)
    {
        mutex_->lock();
    }
    CANN_ASC_STL_API unique_lock(mutex_type& mutex, defer_lock_t) noexcept : mutex_(&mutex)
    {}
    CANN_ASC_STL_API unique_lock(mutex_type& mutex, try_to_lock_t) : mutex_(&mutex), owns_(mutex.try_lock())
    {}
    CANN_ASC_STL_API unique_lock(mutex_type& mutex, adopt_lock_t) noexcept : mutex_(&mutex), owns_(true)
    {}
    unique_lock(const unique_lock&) = delete;
    unique_lock& operator=(const unique_lock&) = delete;
    CANN_ASC_STL_API unique_lock(unique_lock&& other) noexcept : mutex_(other.mutex_), owns_(other.owns_)
    {
        other.mutex_ = nullptr;
        other.owns_ = false;
    }
    CANN_ASC_STL_API unique_lock& operator=(unique_lock&& other) noexcept
    {
        if (owns_)
            mutex_->unlock();
        mutex_ = other.mutex_;
        owns_ = other.owns_;
        other.mutex_ = nullptr;
        other.owns_ = false;
        return *this;
    }
    CANN_ASC_STL_API ~unique_lock()
    {
        if (owns_)
            mutex_->unlock();
    }
    CANN_ASC_STL_API void lock()
    {
        // Hosted precondition checks: the registered contract only defines
        // behavior on a valid (mutex-associated, correct ownership) state;
        // instead of dereferencing a null mutex on the default-constructed
        // state, fail fast. std hosted throws system_error here; the device
        // path stays zero-cost by compiling the checks out.
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        if (mutex_ == nullptr)
            ::asc::std::terminate();
#endif
        mutex_->lock();
        owns_ = true;
    }
    CANN_ASC_STL_API bool try_lock()
    {
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        if (mutex_ == nullptr || owns_)
            ::asc::std::terminate();
#endif
        owns_ = mutex_->try_lock();
        return owns_;
    }
    CANN_ASC_STL_API void unlock()
    {
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        if (mutex_ == nullptr || !owns_)
            ::asc::std::terminate();
#endif
        mutex_->unlock();
        owns_ = false;
    }
    CANN_ASC_STL_API void swap(unique_lock& other) noexcept  // NOLINT(build/include_what_you_use)
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
CANN_ASC_STL_API void swap(
    unique_lock<Mutex>& left, unique_lock<Mutex>& right) noexcept  // NOLINT(build/include_what_you_use)
{
    left.swap(right);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MUTEX_UNIQUE_LOCK_H
