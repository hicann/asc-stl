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

#ifndef CANN_ASC_STL_ASC_STD___MUTEX_LOCK_GUARD_H
#define CANN_ASC_STL_ASC_STD___MUTEX_LOCK_GUARD_H

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
class lock_guard {
public:
    using mutex_type = Mutex;

    CANN_ASC_STL_API explicit lock_guard(mutex_type& mutex) : mutex_(mutex)
    {
        mutex_.lock();
    }
    CANN_ASC_STL_API lock_guard(mutex_type& mutex, adopt_lock_t) noexcept : mutex_(mutex)
    {}
    CANN_ASC_STL_API ~lock_guard()
    {
        mutex_.unlock();
    }
    lock_guard(const lock_guard&) = delete;
    lock_guard& operator=(const lock_guard&) = delete;

private:
    mutex_type& mutex_;
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MUTEX_LOCK_GUARD_H
