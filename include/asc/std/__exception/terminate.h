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

#ifndef CANN_ASC_STL_STD_DETAIL_EXCEPTION_TERMINATE_H
#define CANN_ASC_STL_STD_DETAIL_EXCEPTION_TERMINATE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/cassert>

#include <exception>

CANN_ASC_STL_BEGIN_NAMESPACE

// Host submission invokes the installed terminate handler. Device execution
// uses the target's fail-fast instruction path without a debug-header dependency.
#if defined(__CCE__) || defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-noreturn"
#endif

#if defined(__CCE__) || defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
CANN_ASC_STL_NORETURN __host__ CANN_ASC_STL_DETAIL_VISIBILITY_HIDDEN inline void terminate() noexcept
{
    ::std::terminate();
}

CANN_ASC_STL_NORETURN __aicore__ CANN_ASC_STL_DETAIL_VISIBILITY_HIDDEN inline void terminate() noexcept
{
#if defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
    // The supported pure-SIMT backend lowers builtin traps to an uncallable
    // abort symbol. A volatile invalid-address write emits the device fault.
    *reinterpret_cast<volatile unsigned char*>(-1) = 0;
#else
    trap();
#endif
    // BiSheng may discard even the fault when it proves that a kernel never
    // returns. Keep the fallback condition observable to its optimizer.
    volatile int __halt = 1;
    while (__halt != 0) {
    }
}
#else
CANN_ASC_STL_NORETURN CANN_ASC_STL_API void terminate() noexcept
{
    ::std::terminate();
}
#endif

#if defined(__CCE__) || defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
#pragma clang diagnostic pop
#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_EXCEPTION_TERMINATE_H
