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

#ifndef CANN_ASC_STL_ASC_STD___ATOMIC_BACKEND_H
#define CANN_ASC_STL_ASC_STD___ATOMIC_BACKEND_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
#include <simt_api/device_atomic_functions.h>
#include <simt_api/device_functions.h>
#include <simt_api/device_sync_functions.h>
#endif

namespace asc {
namespace detail {

template <class T>
inline constexpr bool is_scoped_atomic_integer_v = __is_same(T, __INT32_TYPE__) || __is_same(T, __UINT32_TYPE__) ||
    __is_same(T, __INT64_TYPE__) || __is_same(T, __UINT64_TYPE__);

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()

CANN_ASC_STL_SIMT_API void atomic_compiler_barrier() noexcept
{
    asm volatile("" ::: "memory");
}

CANN_ASC_STL_SIMT_API void atomic_trap() noexcept
{
    __builtin_trap();
}

template <class T>
CANN_ASC_STL_SIMT_API T atomic_add(T* address, T value) noexcept
{
    return asc_atomic_add(address, value);
}

template <class T>
CANN_ASC_STL_SIMT_API T atomic_sub(T* address, T value) noexcept
{
    return asc_atomic_sub(address, value);
}

template <class T>
CANN_ASC_STL_SIMT_API T atomic_exchange(T* address, T value) noexcept
{
    return asc_atomic_exch(address, value);
}

template <class T>
CANN_ASC_STL_SIMT_API T atomic_compare_exchange(T* address, T expected, T desired) noexcept
{
    return asc_atomic_cas(address, expected, desired);
}

template <class T>
CANN_ASC_STL_SIMT_API T atomic_and(T* address, T value) noexcept
{
    return asc_atomic_and(address, value);
}

template <class T>
CANN_ASC_STL_SIMT_API T atomic_or(T* address, T value) noexcept
{
    return asc_atomic_or(address, value);
}

template <class T>
CANN_ASC_STL_SIMT_API T atomic_xor(T* address, T value) noexcept
{
    return asc_atomic_xor(address, value);
}

template <class T>
CANN_ASC_STL_SIMT_API T atomic_min(T* address, T value) noexcept
{
    return asc_atomic_min(address, value);
}

template <class T>
CANN_ASC_STL_SIMT_API T atomic_max(T* address, T value) noexcept
{
    return asc_atomic_max(address, value);
}

#endif

}  // namespace detail
}  // namespace asc

#endif  // CANN_ASC_STL_ASC_STD___ATOMIC_BACKEND_H
