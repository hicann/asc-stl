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

#include <asc/std/detail/__config>

#if CANN_ASC_STL_DETAIL_HOSTED()
#include <stdlib.h>
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

#include <asc/std/__asc/unreachable.h>

CANN_ASC_STL_DETAIL_DIAG_PUSH
CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_MSVC(4702)  // unreachable code

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_NOVERSION  // purposefully not using versioning namespace

    [[noreturn]] CANN_ASC_STL_API void
    __asc_terminate() noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    trap();
    for (;;) {
    }
#elif CANN_ASC_STL_DETAIL_HOSTED()
    ::exit(-1);
#else  // freestanding compiler path without the C runtime
    __builtin_trap();
#endif
    CANN_ASC_STL_DETAIL_UNREACHABLE();
}

[[noreturn]] CANN_ASC_STL_API void terminate() noexcept
{
    __asc_terminate();
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_NOVERSION

CANN_ASC_STL_DETAIL_DIAG_POP

#endif  // CANN_ASC_STL_STD_DETAIL_EXCEPTION_TERMINATE_H
