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

#ifndef CANN_ASC_STL_STD_DETAIL_SYSTEM_HEADER_H
#define CANN_ASC_STL_STD_DETAIL_SYSTEM_HEADER_H

#include <asc/std/__asc/compiler.h>
#include <asc/std/__asc/is_non_narrowing_convertible.h>  // IWYU pragma: export

// Headers that are included by user code can produce noisy diagnostics from
// compiler-specific implementation details.  Including this header and
// expanding CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER at the top of a header file marks the
// remainder of that file as a system header on compilers that support the
// pragma, suppressing such diagnostics.  Bisheng CCE is a clang frontend and
// accepts the clang system-header pragma.
#if CANN_ASC_STL_DETAIL_COMPILER(GCC)
#define CANN_ASC_STL_DETAIL_FORCE_SYSTEM_HEADER_GCC
#elif CANN_ASC_STL_DETAIL_COMPILER(CLANG)
#define CANN_ASC_STL_DETAIL_FORCE_SYSTEM_HEADER_CLANG
#elif CANN_ASC_STL_DETAIL_COMPILER(MSVC)
#define CANN_ASC_STL_DETAIL_FORCE_SYSTEM_HEADER_MSVC
#endif

#if !defined(CANN_ASC_STL_DETAIL_NO_SYSTEM_HEADER) &&                                                        \
    !(CANN_ASC_STL_DETAIL_COMPILER(MSVC) && defined(CANN_ASC_STL_DETAIL_STD_DISABLE_PRAGMA_MSVC_WARNING)) && \
    !defined(CANN_ASC_STL_DETAIL_STD_DISABLE_PRAGMA_GCC_SYSTEM_HEADER)
#if CANN_ASC_STL_DETAIL_COMPILER(GCC)
#define CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC
#elif CANN_ASC_STL_DETAIL_COMPILER(CLANG)
#define CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG
#elif CANN_ASC_STL_DETAIL_COMPILER(CCE)
#define CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CCE
#elif CANN_ASC_STL_DETAIL_COMPILER(MSVC)
#define CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC
#endif
#endif

// Expands to the compiler's system-header pragma when implicit system-header
// treatment is enabled, and to nothing otherwise.  Expand once near the top of
// each header file; the pragma applies to the remainder of the expanding file.
#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#define CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER _Pragma("GCC system_header")
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#define CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER _Pragma("clang system_header")
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CCE)
#define CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER _Pragma("clang system_header")
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#define CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER _Pragma("system_header")
#else
#define CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER
#endif

#endif  // CANN_ASC_STL_STD_DETAIL_SYSTEM_HEADER_H
