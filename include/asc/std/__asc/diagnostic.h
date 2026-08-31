/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#ifndef CANN_ASC_STL_STD_DETAIL_DIAGNOSTIC_H
#define CANN_ASC_STL_STD_DETAIL_DIAGNOSTIC_H

#include <asc/std/__asc/compiler.h>
#include <asc/std/__asc/system_header.h>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

// ---------------------------------------------------------------------------
// Core diagnostic macros (CANN_ASC_STL_DETAIL_DIAG_PUSH, CANN_ASC_STL_DETAIL_DIAG_POP, CANN_ASC_STL_DETAIL_PRAGMA,
// CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_CLANG, CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_GCC,
// CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_MSVC, CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_CCE) are defined in asc/std/__config
// (included transitively via compiler.h). This header provides higher-level diagnostic convenience macros.
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// Convenient shortcuts to silence common warnings
// ---------------------------------------------------------------------------

#if defined(CANN_ASC_STL_DETAIL_COMPILER_CLANG)
#define CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_PUSH        \
    CANN_ASC_STL_DETAIL_DIAG_PUSH                           \
    CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_CLANG("-Wdeprecated") \
    CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_CLANG("-Wdeprecated-declarations")
#define CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_POP CANN_ASC_STL_DETAIL_DIAG_POP
#elif defined(CANN_ASC_STL_DETAIL_COMPILER_GCC)
#define CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_PUSH      \
    CANN_ASC_STL_DETAIL_DIAG_PUSH                         \
    CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_GCC("-Wdeprecated") \
    CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_GCC("-Wdeprecated-declarations")
#define CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_POP CANN_ASC_STL_DETAIL_DIAG_POP
#elif defined(CANN_ASC_STL_DETAIL_COMPILER_MSVC)
#define CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_PUSH \
    CANN_ASC_STL_DETAIL_DIAG_PUSH                    \
    CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_MSVC(4996)
#define CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_POP CANN_ASC_STL_DETAIL_DIAG_POP
#elif defined(CANN_ASC_STL_DETAIL_COMPILER_CCE)
// Bisheng CCE is a clang frontend: the clang diagnostic pragmas apply.
#define CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_PUSH      \
    CANN_ASC_STL_DETAIL_DIAG_PUSH                         \
    CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_CCE("-Wdeprecated") \
    CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_CCE("-Wdeprecated-declarations")
#define CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_POP CANN_ASC_STL_DETAIL_DIAG_POP
#else
#define CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_PUSH
#define CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_POP
#endif

// ---------------------------------------------------------------------------
// MSVC pragma warning control
// ---------------------------------------------------------------------------

#if defined(CANN_ASC_STL_DETAIL_COMPILER_MSVC)
#define CANN_ASC_STL_DETAIL_HAS_PRAGMA_MSVC_WARNING
#if !defined(CANN_ASC_STL_DETAIL_STD_DISABLE_PRAGMA_MSVC_WARNING)
#define CANN_ASC_STL_DETAIL_USE_PRAGMA_MSVC_WARNING
#endif  // !CANN_ASC_STL_DETAIL_STD_DISABLE_PRAGMA_MSVC_WARNING
#endif  // CANN_ASC_STL_DETAIL_COMPILER_MSVC

#endif  // CANN_ASC_STL_STD_DETAIL_DIAGNOSTIC_H
