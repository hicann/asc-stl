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

#ifndef CANN_ASC_STL_STD_DETAIL_CSTRING_MEMSET_H
#define CANN_ASC_STL_STD_DETAIL_CSTRING_MEMSET_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__cstddef/types.h>
#include <asc/std/cstdint>

// No centralized assertion macro is available yet, so it is defined inline
// behind an #ifndef guard; a future centralized definition then wins.
#ifndef CANN_ASC_STL_DETAIL_ASSERT
// Always a no-op on device (no assertion mechanism); checked on host only when
// ASC_ENABLE_HOST_ASSERTIONS is explicitly enabled.
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() || !defined(ASC_ENABLE_HOST_ASSERTIONS)
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) ((void)0)
#else
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) \
    ((expression) ? static_cast<void>(0) : (__builtin_trap(), static_cast<void>(0)))
#endif
#endif  // CANN_ASC_STL_DETAIL_ASSERT

#if CANN_ASC_STL_DETAIL_HOSTED() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#include <cstring>
#endif  // CANN_ASC_STL_DETAIL_HOSTED() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __memset_detail {

// Destination-range validity check (non-null, no address wraparound), used by
// the assertion below.
CANN_ASC_STL_API bool __is_valid_address_range(const void* pointer, size_t count) noexcept
{
    if (count == 0) {
        return false;
    }
    const uintptr_t limit = (~uintptr_t{0}) - static_cast<uintptr_t>(count);
    const uintptr_t address = reinterpret_cast<uintptr_t>(pointer);
    return pointer != nullptr && address <= limit;
}

}  // namespace __memset_detail

CANN_ASC_STL_API void* memset(void* destination, int value, __SIZE_TYPE__ count) noexcept
{
    CANN_ASC_STL_DETAIL_ASSERT(
        __memset_detail::__is_valid_address_range(destination, count), "memset: destination range is invalid");
#if CANN_ASC_STL_DETAIL_HOSTED() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::memset(destination, value, count);
#else
    // Device TU: __builtin_memset fully inlines only when the length is a
    // compile-time constant; a runtime length degrades to a call to the libc
    // memset, and the aicore link has no libc. Constant lengths take the
    // builtin inline path; runtime lengths fall back to a byte loop.
    if (__builtin_constant_p(count)) {
        return __builtin_memset(destination, value, count);
    }
    unsigned char* destination_bytes = static_cast<unsigned char*>(destination);
    for (size_t index = 0; index < count; ++index) {
        destination_bytes[index] = static_cast<unsigned char>(value);
    }
    return destination;
#endif
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_CSTRING_MEMSET_H
