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

#ifndef CANN_ASC_STL_STD_DETAIL_VISIBILITY_H
#define CANN_ASC_STL_STD_DETAIL_VISIBILITY_H

#include <asc/std/__asc/compiler.h>
#include <asc/std/__asc/system_header.h>

#include <asc/std/__asc/attributes.h>
#include <asc/std/__asc/asc_capabilities.h>
#include <asc/std/__asc/execution_space.h>

// ---------------------------------------------------------------------------
// Visibility macros
// ---------------------------------------------------------------------------
// ASC-STL does not define ELF/DLL visibility control macros.
// The following macros are intentionally not defined:
//   CANN_ASC_STL_DETAIL_VISIBILITY_HIDDEN, CANN_ASC_STL_DETAIL_VISIBILITY_DEFAULT,
//   CANN_ASC_STL_DETAIL_VISIBILITY_EXPORT, CANN_ASC_STL_DETAIL_TYPE_VISIBILITY_DEFAULT,
//   CANN_ASC_STL_DETAIL_TYPE_VISIBILITY_HIDDEN

// ---------------------------------------------------------------------------
// Force inline
// ---------------------------------------------------------------------------
// Bisheng CCE is a clang frontend and supports the GNU always_inline
// attribute; it is applied for clang, gcc and CCE builds. MSVC uses its own
// __forceinline spelling.
#if defined(_MSC_VER) && !defined(__clang__)
#define CANN_ASC_STL_DETAIL_FORCEINLINE __forceinline
#elif defined(__clang__) || defined(__GNUC__)
#define CANN_ASC_STL_DETAIL_FORCEINLINE inline __attribute__((always_inline))
#else
#define CANN_ASC_STL_DETAIL_FORCEINLINE inline
#endif

// CANN_ASC_STL_DETAIL_FORCEINLINE_LAMBDA and CANN_ASC_STL_DETAIL_EXCLUDE_FROM_EXPLICIT_INSTANTIATION are
// intentionally not defined.

// ---------------------------------------------------------------------------
// ABI hidden
// ---------------------------------------------------------------------------
// ASC-STL keeps only the inline semantics for ABI hidden.
#define CANN_ASC_STL_DETAIL_HIDE_FROM_ABI inline

// ---------------------------------------------------------------------------
// Kernel attributes
// ---------------------------------------------------------------------------
// CANN_ASC_STL_DETAIL_KERNEL_ATTRIBUTES is not generated as a compatibility macro.
// ASC kernel launch shape is described by the build/run harness, not by
// function attributes.

// ---------------------------------------------------------------------------
// API decoration macros
// ---------------------------------------------------------------------------
// The API macro family expresses the call-space intent of a declaration.
// ELF/DLL visibility attributes are intentionally not applied, while
// execution-space annotations are mapped through execution_space.h:
//   - host APIs: no annotation, because host execution is the C++ default;
//   - device APIs: __aicore__ when compiling with CCE, empty on host;
//   - host/device APIs: CANN_ASC_STL_HOST_DEVICE, which lowers to the dual
//     [host, aicore] annotation in mixed-mode CCE (CANN's
//     ASCENDC_HOST_AICORE spelling) and to the host/device attribute pair in
//     pure-SIMT mode.
// ASC has no separate tile execution space; no tile compatibility API is
// exported.

#define CANN_ASC_STL_API CANN_ASC_STL_HOST_DEVICE inline
#define CANN_ASC_STL_DETAIL_HOST_DEVICE_API CANN_ASC_STL_HOST_DEVICE inline
#define CANN_ASC_STL_HOST_API CANN_ASC_STL_HOST inline
#define CANN_ASC_STL_DEVICE_API CANN_ASC_STL_DEVICE inline

// ---------------------------------------------------------------------------
// Nodebug API
// ---------------------------------------------------------------------------
// Debug/visibility attributes are not retained in ASC-STL; only device inline
// semantics are preserved.

#define CANN_ASC_STL_DETAIL_NODEBUG_API CANN_ASC_STL_API CANN_ASC_STL_DETAIL_ARTIFICIAL CANN_ASC_STL_DETAIL_NODEBUG
#define CANN_ASC_STL_DETAIL_NODEBUG_HOST_API \
    CANN_ASC_STL_HOST_API CANN_ASC_STL_DETAIL_ARTIFICIAL CANN_ASC_STL_DETAIL_NODEBUG
#define CANN_ASC_STL_DETAIL_NODEBUG_DEVICE_API \
    CANN_ASC_STL_DEVICE_API CANN_ASC_STL_DETAIL_ARTIFICIAL CANN_ASC_STL_DETAIL_NODEBUG

// ---------------------------------------------------------------------------
// Trivial API
// ---------------------------------------------------------------------------
// Force-inline/debug attributes are consolidated to ASC device inline.

#define CANN_ASC_STL_DETAIL_TRIVIAL_API \
    CANN_ASC_STL_HOST_DEVICE CANN_ASC_STL_DETAIL_ARTIFICIAL CANN_ASC_STL_DETAIL_NODEBUG CANN_ASC_STL_DETAIL_FORCEINLINE
#define CANN_ASC_STL_DETAIL_TRIVIAL_HOST_API \
    CANN_ASC_STL_HOST CANN_ASC_STL_DETAIL_ARTIFICIAL CANN_ASC_STL_DETAIL_NODEBUG CANN_ASC_STL_DETAIL_FORCEINLINE
#define CANN_ASC_STL_DETAIL_TRIVIAL_DEVICE_API \
    CANN_ASC_STL_DEVICE CANN_ASC_STL_DETAIL_ARTIFICIAL CANN_ASC_STL_DETAIL_NODEBUG CANN_ASC_STL_DETAIL_FORCEINLINE

// ---------------------------------------------------------------------------
// Public API
// ---------------------------------------------------------------------------
// Public visibility attributes are not retained in ASC-STL; only device inline
// semantics are preserved.

#define CANN_ASC_STL_DETAIL_PUBLIC_API CANN_ASC_STL_DETAIL_HOST_DEVICE_API
#define CANN_ASC_STL_DETAIL_PUBLIC_HOST_API CANN_ASC_STL_HOST_API
#define CANN_ASC_STL_DETAIL_PUBLIC_DEVICE_API CANN_ASC_STL_DEVICE_API

#endif  // CANN_ASC_STL_STD_DETAIL_VISIBILITY_H
