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

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/__memory/check_address.h>
#include <asc/std/cstddef>

#if CANN_ASC_STL_DETAIL_HOSTED()
#include <cstring>
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

CANN_ASC_STL_API void* memset(void* __dest, int __ch, size_t __count) noexcept
{
    CANN_ASC_STL_DETAIL_ASSERT(
        ::asc::__is_valid_address_range(__dest, __count), "memset: destination range is invalid");
#if CANN_ASC_STL_DETAIL_HOSTED()
    return ::memset(__dest, __ch, __count);
#else
    // Device TU: __builtin_memset fully inlines only when the length is a compile-time
    // constant; a runtime length lowers to an external libc memset call, and the aicore
    // link has no libc. Constant lengths use the builtin inline path; runtime lengths
    // fall back to a byte loop.
    if (__builtin_constant_p(__count)) {
        return __builtin_memset(__dest, __ch, __count);
    }
    unsigned char* __d = static_cast<unsigned char*>(__dest);
    for (size_t __i = 0; __i < __count; ++__i) {
        __d[__i] = static_cast<unsigned char>(__ch);
    }
    return __dest;
#endif
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_CSTRING_MEMSET_H
