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

#ifndef CANN_ASC_STL_DETAIL_BUILTIN_H
#define CANN_ASC_STL_DETAIL_BUILTIN_H

#if defined(__has_builtin)
#define CANN_ASC_STL_DETAIL_HAS_BUILTIN(builtin) __has_builtin(builtin)
#else
#define CANN_ASC_STL_DETAIL_HAS_BUILTIN(builtin) 0
#endif

// Portable trap. All compiler builtins used by the library must be routed
// through this module, never called bare at the use site (bare calls break
// the MSVC syntax-compatibility story promised by the other detail headers).
// MSVC has no __builtin_trap; __fastfail is its intrinsic equivalent and a
// plain abort() is the last-resort hosted fallback.
#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_trap) || defined(__GNUC__) || defined(__clang__)
#define CANN_ASC_STL_DETAIL_BUILTIN_TRAP() __builtin_trap()
#elif defined(_MSC_VER)
#include <intrin.h>
#define CANN_ASC_STL_DETAIL_BUILTIN_TRAP() __fastfail(0)
#else
extern "C" void abort();
#define CANN_ASC_STL_DETAIL_BUILTIN_TRAP() abort()
#endif

// A violated precondition need not report a Device error. In particular, CCE
// can lower a trap to an unavailable Host abort symbol. This marker retains
// rejection during constant evaluation without adding that runtime call.
#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_unreachable) || defined(__GNUC__) || defined(__clang__)
#define CANN_ASC_STL_DETAIL_BUILTIN_ASSUME_UNREACHABLE() __builtin_unreachable()
#elif defined(_MSC_VER)
#define CANN_ASC_STL_DETAIL_BUILTIN_ASSUME_UNREACHABLE() __assume(0)
#else
#define CANN_ASC_STL_DETAIL_BUILTIN_ASSUME_UNREACHABLE() CANN_ASC_STL_DETAIL_BUILTIN_TRAP()
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_trap) || defined(__GNUC__)
#define CANN_ASC_STL_DETAIL_BUILTIN_UNREACHABLE() \
    do {                                          \
        CANN_ASC_STL_DETAIL_BUILTIN_TRAP();       \
        __builtin_unreachable();                  \
    } while (false)
#else
// Placeholder fallback only: on targets without a trap builtin the marker
// degrades to a spin loop. Production backends (GCC/Clang/CCE) all take the
// trap branch above; treat this arm as a syntax-compatibility stub, not as
// an observable failure strategy - an AI Core kernel reaching it would hang
// its core instead of reporting a fault.
#define CANN_ASC_STL_DETAIL_BUILTIN_UNREACHABLE() \
    do {                                          \
        for (;;) {                                \
        }                                         \
    } while (false)
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_FILE) || defined(__GNUC__)
#define CANN_ASC_STL_DETAIL_BUILTIN_FILE() __builtin_FILE()
#else
#define CANN_ASC_STL_DETAIL_BUILTIN_FILE() __FILE__
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_FUNCTION) || defined(__GNUC__)
#define CANN_ASC_STL_DETAIL_BUILTIN_FUNCTION() __builtin_FUNCTION()
#else
#define CANN_ASC_STL_DETAIL_BUILTIN_FUNCTION() ""
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_LINE) || defined(__GNUC__)
#define CANN_ASC_STL_DETAIL_BUILTIN_LINE() __builtin_LINE()
#else
#define CANN_ASC_STL_DETAIL_BUILTIN_LINE() __LINE__
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_COLUMN)
#define CANN_ASC_STL_DETAIL_BUILTIN_COLUMN() __builtin_COLUMN()
#else
#define CANN_ASC_STL_DETAIL_BUILTIN_COLUMN() 0
#endif

#endif  // CANN_ASC_STL_DETAIL_BUILTIN_H
