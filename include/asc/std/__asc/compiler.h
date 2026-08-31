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

#ifndef CANN_ASC_STL_STD_DETAIL_COMPILER_H
#define CANN_ASC_STL_STD_DETAIL_COMPILER_H

#include <asc/std/__config>
#include <asc/std/__asc/preprocessor.h>

// ---------------------------------------------------------------------------
// Version comparison utilities
// ---------------------------------------------------------------------------
// Simplified version comparison framework for ASC-STL.
// CANN_ASC_STL_DETAIL_PP_* metaprogramming helpers are available in preprocessor.h, but
// compiler and toolkit version checks stay on direct macro expansion so these
// foundational probes remain easy to audit and do not depend on larger PP loops.
//
// Usage:
//   CANN_ASC_STL_DETAIL_COMPILER(CCE)               - is the CCE compiler version valid?
//   CANN_ASC_STL_DETAIL_COMPILER(CCE, >=, 1, 2)     - is CCE version >= 1.2?
//   CANN_ASC_STL_DETAIL_COMPILER(CLANG, >=, 14)     - is Clang major version >= 14?

#define CANN_ASC_STL_DETAIL_VERSION_MAJOR_(_MAJOR, _MINOR) _MAJOR
#define CANN_ASC_STL_DETAIL_VERSION_MINOR_(_MAJOR, _MINOR) _MINOR
#define CANN_ASC_STL_DETAIL_VERSION_MAJOR(_PAIR) CANN_ASC_STL_DETAIL_VERSION_MAJOR_ _PAIR
#define CANN_ASC_STL_DETAIL_VERSION_MINOR(_PAIR) CANN_ASC_STL_DETAIL_VERSION_MINOR_ _PAIR
#define CANN_ASC_STL_DETAIL_VERSION_INVALID() (-1, -1)
#define CANN_ASC_STL_DETAIL_MAKE_VERSION(_PAIR) \
    (CANN_ASC_STL_DETAIL_VERSION_MAJOR(_PAIR) * 100 + CANN_ASC_STL_DETAIL_VERSION_MINOR(_PAIR))
#define CANN_ASC_STL_DETAIL_VERSION_IS_INVALID(_PAIR) \
    (CANN_ASC_STL_DETAIL_VERSION_MAJOR(_PAIR) ==      \
        CANN_ASC_STL_DETAIL_VERSION_MAJOR(CANN_ASC_STL_DETAIL_VERSION_INVALID()))

#define CANN_ASC_STL_DETAIL_VERSION_COMPARE_1(_PREFIX, _VER) (!CANN_ASC_STL_DETAIL_VERSION_IS_INVALID(_VER()))
#define CANN_ASC_STL_DETAIL_VERSION_COMPARE_3(_PREFIX, _VER, _OP, _MAJOR) \
    (!CANN_ASC_STL_DETAIL_VERSION_IS_INVALID(_VER()) && (CANN_ASC_STL_DETAIL_VERSION_MAJOR(_VER()) _OP _MAJOR))
#define CANN_ASC_STL_DETAIL_VERSION_COMPARE_4(_PREFIX, _VER, _OP, _MAJOR, _MINOR) \
    (!CANN_ASC_STL_DETAIL_VERSION_IS_INVALID(_VER()) &&                           \
        (CANN_ASC_STL_DETAIL_MAKE_VERSION(_VER()) _OP CANN_ASC_STL_DETAIL_MAKE_VERSION((_MAJOR, _MINOR))))

#define CANN_ASC_STL_DETAIL_VERSION_SELECT_COUNT(_ARG1, _ARG2, _ARG3, _ARG4, _ARG5, ...) _ARG5
#define CANN_ASC_STL_DETAIL_VERSION_SELECT2(_ARGS) CANN_ASC_STL_DETAIL_VERSION_SELECT_COUNT _ARGS
#define CANN_ASC_STL_DETAIL_VERSION_SELECT(...)                                                   \
    CANN_ASC_STL_DETAIL_VERSION_SELECT2((__VA_ARGS__, CANN_ASC_STL_DETAIL_VERSION_COMPARE_4,      \
        CANN_ASC_STL_DETAIL_VERSION_COMPARE_3, CANN_ASC_STL_DETAIL_VERSION_COMPARE_BAD_ARG_COUNT, \
        CANN_ASC_STL_DETAIL_VERSION_COMPARE_1, CANN_ASC_STL_DETAIL_VERSION_COMPARE_BAD_ARG_COUNT))
#define CANN_ASC_STL_DETAIL_VERSION_COMPARE(_PREFIX, ...) \
    CANN_ASC_STL_DETAIL_VERSION_SELECT(__VA_ARGS__)(_PREFIX, __VA_ARGS__)

// ---------------------------------------------------------------------------
// Host compiler detection
// ---------------------------------------------------------------------------
// Note: CANN_ASC_STL_DETAIL_COMPILER_CCE, CANN_ASC_STL_DETAIL_COMPILER_CLANG, CANN_ASC_STL_DETAIL_COMPILER_GCC, and
// CANN_ASC_STL_DETAIL_COMPILER_MSVC are defined as flags (value 1) in asc/std/__config.
// The version macros below use a _VERSION_ infix to avoid naming collisions
// with those object-like flag macros.

#define CANN_ASC_STL_DETAIL_COMPILER_MAKE_VERSION(_MAJOR, _MINOR) ((_MAJOR) * 100 + (_MINOR))
#define CANN_ASC_STL_DETAIL_COMPILER(...) \
    CANN_ASC_STL_DETAIL_VERSION_COMPARE(  \
        CANN_ASC_STL_DETAIL_COMPILER_VERSION_, CANN_ASC_STL_DETAIL_COMPILER_VERSION_##__VA_ARGS__)

// Default: all compiler versions are invalid until detected
#define CANN_ASC_STL_DETAIL_COMPILER_VERSION_CCE() CANN_ASC_STL_DETAIL_VERSION_INVALID()
#define CANN_ASC_STL_DETAIL_COMPILER_VERSION_CLANG() CANN_ASC_STL_DETAIL_VERSION_INVALID()
#define CANN_ASC_STL_DETAIL_COMPILER_VERSION_GCC() CANN_ASC_STL_DETAIL_VERSION_INVALID()
#define CANN_ASC_STL_DETAIL_COMPILER_VERSION_MSVC() CANN_ASC_STL_DETAIL_VERSION_INVALID()

// Determine the host compiler and its version
#if defined(__CCE__) || defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
// Ascend CCE compiler
// CCE does not expose a stable public version macro across all supported
// toolchains. Projects that need an exact CCE version comparison may define
// CANN_ASC_STL_DETAIL_CCE_VERSION_MAJOR/CANN_ASC_STL_DETAIL_CCE_VERSION_MINOR before including ASC-STL.
#if !defined(CANN_ASC_STL_DETAIL_CCE_VERSION_MAJOR)
#define CANN_ASC_STL_DETAIL_CCE_VERSION_MAJOR 0
#endif
#if !defined(CANN_ASC_STL_DETAIL_CCE_VERSION_MINOR)
#define CANN_ASC_STL_DETAIL_CCE_VERSION_MINOR 0
#endif
#undef CANN_ASC_STL_DETAIL_COMPILER_VERSION_CCE
#define CANN_ASC_STL_DETAIL_COMPILER_VERSION_CCE() \
    (CANN_ASC_STL_DETAIL_CCE_VERSION_MAJOR, CANN_ASC_STL_DETAIL_CCE_VERSION_MINOR)
#elif defined(__clang__)
#undef CANN_ASC_STL_DETAIL_COMPILER_VERSION_CLANG
#define CANN_ASC_STL_DETAIL_COMPILER_VERSION_CLANG() (__clang_major__, __clang_minor__)
#elif defined(__GNUC__)
#undef CANN_ASC_STL_DETAIL_COMPILER_VERSION_GCC
#define CANN_ASC_STL_DETAIL_COMPILER_VERSION_GCC() (__GNUC__, __GNUC_MINOR__)
#elif defined(_MSC_VER)
#undef CANN_ASC_STL_DETAIL_COMPILER_VERSION_MSVC
#define CANN_ASC_STL_DETAIL_COMPILER_VERSION_MSVC() (_MSC_VER / 100, _MSC_VER % 100)
#endif

// ---------------------------------------------------------------------------
// ASC compilation mode detection
// ---------------------------------------------------------------------------
// In the ASC programming model, CCE is the compiler for AI Core device code.
// CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() indicates whether we are compiling for the
// ASC device (AI Core). CANN_ASC_STL_DETAIL_HOST_COMPILATION() indicates host-side compilation.
// Note: This is a simplification; CCE may also compile host-side launch code,
// but ASC-STL is primarily used in device kernels.

#if defined(CANN_ASC_STL_DETAIL_COMPILER_PURE_SIMT)
#define CANN_ASC_STL_DETAIL_PURE_SIMT_COMPILATION() 1
#else
#define CANN_ASC_STL_DETAIL_PURE_SIMT_COMPILATION() 0
#endif

#if defined(CANN_ASC_STL_DETAIL_COMPILER_CCE)
#define CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() 1
#else
#define CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() 0
#endif

#if !defined(CANN_ASC_STL_DETAIL_COMPILER_CCE)
#define CANN_ASC_STL_DETAIL_HOST_COMPILATION() 1
#else
#define CANN_ASC_STL_DETAIL_HOST_COMPILATION() 0
#endif

// ---------------------------------------------------------------------------
// Pragma utilities
// ---------------------------------------------------------------------------

// Unroll pragmas
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#define CANN_ASC_STL_DETAIL_PRAGMA_UNROLL(_N) CANN_ASC_STL_DETAIL_PRAGMA(unroll _N)
#define CANN_ASC_STL_DETAIL_PRAGMA_UNROLL_FULL() CANN_ASC_STL_DETAIL_PRAGMA(unroll)
#elif defined(CANN_ASC_STL_DETAIL_COMPILER_CLANG)
#define CANN_ASC_STL_DETAIL_PRAGMA_UNROLL(_N) CANN_ASC_STL_DETAIL_PRAGMA(unroll _N)
#define CANN_ASC_STL_DETAIL_PRAGMA_UNROLL_FULL() CANN_ASC_STL_DETAIL_PRAGMA(unroll)
#elif defined(CANN_ASC_STL_DETAIL_COMPILER_GCC) && CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 8)
#define CANN_ASC_STL_DETAIL_PRAGMA_UNROLL(_N) CANN_ASC_STL_DETAIL_PRAGMA(GCC unroll _N)
#define CANN_ASC_STL_DETAIL_PRAGMA_UNROLL_FULL() CANN_ASC_STL_DETAIL_PRAGMA_UNROLL(65534)
#elif defined(CANN_ASC_STL_DETAIL_COMPILER_MSVC)
#define CANN_ASC_STL_DETAIL_PRAGMA_UNROLL(_N)
#define CANN_ASC_STL_DETAIL_PRAGMA_UNROLL_FULL()
#else
#define CANN_ASC_STL_DETAIL_PRAGMA_UNROLL(_N)
#define CANN_ASC_STL_DETAIL_PRAGMA_UNROLL_FULL()
#endif

#define CANN_ASC_STL_DETAIL_PRAGMA_NOUNROLL() CANN_ASC_STL_DETAIL_PRAGMA_UNROLL(1)

// Warning emission
#if defined(CANN_ASC_STL_DETAIL_COMPILER_MSVC)
#define CANN_ASC_STL_DETAIL_WARNING(_MSG) \
    CANN_ASC_STL_DETAIL_PRAGMA(message(__FILE__ ":" CANN_ASC_STL_DETAIL_TO_STRING(__LINE__) ": warning: " _MSG))
#else
#define CANN_ASC_STL_DETAIL_WARNING(_MSG) CANN_ASC_STL_DETAIL_PRAGMA(GCC warning _MSG)
#endif

// ---------------------------------------------------------------------------
// Freestanding environment detection
// ---------------------------------------------------------------------------
// CCE (AI Core kernel compilation) is treated as freestanding since it has
// no access to the host standard library.

#if defined(CANN_ASC_STL_DETAIL_ENABLE_FREESTANDING) || defined(CANN_ASC_STL_DETAIL_COMPILER_CCE)
#define CANN_ASC_STL_DETAIL_FREESTANDING() 1
#define CANN_ASC_STL_DETAIL_HOSTED() 0
#define CANN_ASC_STL_DETAIL_NO_TYPEID
#else
#define CANN_ASC_STL_DETAIL_FREESTANDING() 0
#define CANN_ASC_STL_DETAIL_HOSTED() 1
#endif

#endif  // CANN_ASC_STL_STD_DETAIL_COMPILER_H
