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

#ifndef CANN_ASC_STL_STD_DETAIL_EXCEPTIONS_H
#define CANN_ASC_STL_STD_DETAIL_EXCEPTIONS_H

#include <asc/std/__asc/compiler.h>
#include <asc/std/__asc/execution_space.h>
#include <asc/std/__asc/system_header.h>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

// ---------------------------------------------------------------------------
// Exception support detection for ASC-STL
// ---------------------------------------------------------------------------
//
// CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS()
//   Evaluates to 1 if exceptions are available on the current platform,
//   0 otherwise. Decision order:
//   - ASC_DISABLE_EXCEPTIONS is a user escape hatch and forces 0;
//   - device compilation (CCE) never has exceptions;
//   - MSVC probes `_HAS_EXCEPTIONS` and `_CPPUNWIND`.
//
// CANN_ASC_STL_DETAIL_HAS_CONSTEXPR_EXCEPTIONS()
//   Evaluates to 1 if constexpr exceptions (C++26) are available,
//   0 otherwise.

#if defined(ASC_DISABLE_EXCEPTIONS)  // Escape hatch for users to manually disable exceptions
#define CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() 0
#elif CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()  // CCE device compilation has no exceptions
#define CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() 0
#elif defined(CANN_ASC_STL_DETAIL_COMPILER_MSVC)  // MSVC needs special checks for `_HAS_EXCEPTIONS` and `_CPPUNWIND`
#if defined(_HAS_EXCEPTIONS) && defined(_CPPUNWIND)
#define CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() ((_HAS_EXCEPTIONS != 0) && (_CPPUNWIND != 0))  // disabled with /EH
#else
#define CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() 0
#endif
#elif defined(__EXCEPTIONS)  // other compilers use `__EXCEPTIONS`, disabled with -fno-exceptions
#define CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() 0
#endif  // has exceptions

#if CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() && defined(__cpp_constexpr_exceptions) && __cpp_constexpr_exceptions >= 202411L
#define CANN_ASC_STL_DETAIL_HAS_CONSTEXPR_EXCEPTIONS() 1
#else  // ^^^ has constexpr exceptions ^^^ / vvv no constexpr exceptions vvv
#define CANN_ASC_STL_DETAIL_HAS_CONSTEXPR_EXCEPTIONS() 0
#endif  // ^^^ no constexpr exceptions ^^^

#endif  // CANN_ASC_STL_STD_DETAIL_EXCEPTIONS_H
