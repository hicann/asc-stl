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

#ifndef CANN_ASC_STL_ASC_STD___MUTEX_TRY_LOCK_H
#define CANN_ASC_STL_ASC_STD___MUTEX_TRY_LOCK_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __lock_detail {

template <class Mutex>
CANN_ASC_STL_API int __try_lock_impl(int index, Mutex& mutex)
{
    // The base case must report its own index: returning a constant 0 here
    // mislabeled every failure past the second mutex.
    return mutex.try_lock() ? -1 : index;
}

template <class Mutex, class... Mutexes>
CANN_ASC_STL_API int __try_lock_impl(int index, Mutex& mutex, Mutexes&... mutexes)
{
    if (!mutex.try_lock())
        return index;
    const int result = __try_lock_impl(index + 1, mutexes...);
    if (result != -1)
        mutex.unlock();
    return result;
}

}  // namespace __lock_detail

template <class... Mutexes>
CANN_ASC_STL_API int try_lock(Mutexes&... mutexes)
{
    // The registered semantics cover "two or more" explicitly non-throwing
    // Device Lockable mutexes (std::try_lock likewise has no single-mutex
    // overload); a lone mutex goes through Mutex::try_lock directly.
    static_assert(sizeof...(Mutexes) >= 2, "asc::std::try_lock requires two or more mutexes");
    return __lock_detail::__try_lock_impl(0, mutexes...);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MUTEX_TRY_LOCK_H
