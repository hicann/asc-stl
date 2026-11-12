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

#ifndef CANN_ASC_STL_STD_DETAIL_UNREACHABLE_H
#define CANN_ASC_STL_STD_DETAIL_UNREACHABLE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>

// The following macros are not provided by the library config; define minimal
// equivalents here, #ifndef-guarded to yield to any future central definition.
#ifndef CANN_ASC_STL_DETAIL_ASSERT
// The device side has no assertion mechanism, so this is always a no-op; on
// the host it checks only when ASC_ENABLE_HOST_ASSERTIONS is explicitly enabled.
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() || !defined(ASC_ENABLE_HOST_ASSERTIONS)
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) ((void)0)
#else
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) \
    ((expression) ? static_cast<void>(0) : (__builtin_trap(), static_cast<void>(0)))
#endif
#endif  // CANN_ASC_STL_DETAIL_ASSERT

#ifndef CANN_ASC_STL_DETAIL_UNREACHABLE
#define CANN_ASC_STL_DETAIL_UNREACHABLE() __builtin_unreachable()
#endif  // CANN_ASC_STL_DETAIL_UNREACHABLE

CANN_ASC_STL_BEGIN_NAMESPACE

CANN_ASC_STL_NORETURN CANN_ASC_STL_API void unreachable() noexcept
{
    CANN_ASC_STL_DETAIL_ASSERT(false, "unreachable");
    CANN_ASC_STL_DETAIL_UNREACHABLE();
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_UNREACHABLE_H
