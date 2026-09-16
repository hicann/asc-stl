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

#ifndef CANN_ASC_STL_STD_DETAIL_ASC_CAPABILITIES_H
#define CANN_ASC_STL_STD_DETAIL_ASC_CAPABILITIES_H

#include <asc/std/__asc/compiler.h>
#include <asc/std/__asc/system_header.h>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

// Native Ascend AI Core capability discovery. Compilation modes and attributes
// without an Ascend counterpart intentionally have no _ASC_* shadow macros: a
// zero/no-op replacement would keep dead control flow alive without preserving
// any semantics.

// WARNING: __NPU_ARCH__ values are TOOLCHAIN-VERSION DEPENDENT and must not
// be used alone for family classification. Empirically (probed on real
// hardware with the project kernel-build flags
// `-D__DAV_C310__ --cce-aicore-arch=dav-c310-vec --cce-aicore-only
// --cce-aicore-lang`): the SAME Ascend 950 dav-c310 device reports
// __NPU_ARCH__ == 3101 under CANN 9.0.0 and __NPU_ARCH__ == 3510 under
// CANN 9.2.0 (weekly 20260730) — the earlier scale note ("3510 = 310R6,
// 5102/5161 = 950") does not hold on the shipped 9.2 toolchain, where the
// puresimt intrinsics header is itself named __clang_cce_simt_dav3510_*.
// The only stable family markers are the dedicated toolchain macros
// __DAV_C310__ / __DAV_C310_VEC__; legacy __NPU_ARCH__ values are kept only
// as a secondary fallback. The __CCE_AICORE__ macro uses a coarser scale and
// collides across chip families, so it is not usable either.
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && defined(__NPU_ARCH__)
#define CANN_ASC_STL_DETAIL_AICORE_ARCH() __NPU_ARCH__
#else
#define CANN_ASC_STL_DETAIL_AICORE_ARCH() 0
#endif

// The Ascend 950 family is the dav-c310 AI-core generation. Its kernel builds
// pass -D__DAV_C310__ (optionally __DAV_C310_VEC__); older toolchains have
// also been observed to report __NPU_ARCH__ 5102/5161 (a5/a6) or 3101 for
// the same generation. These AI cores run SIMT workloads natively: the
// compiler provides the builtin short-vector family and dim3.
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() &&            \
    (defined(__DAV_C310__) || defined(__DAV_C310_VEC__) || \
        (defined(__NPU_ARCH__) && (__NPU_ARCH__ == 5102 || __NPU_ARCH__ == 5161 || __NPU_ARCH__ == 3101)))
#define CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_950() 1
#else
#define CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_950() 0
#endif

// Legacy C310-family fallback for hypothetical non-950 dav toolchains that
// define the C310 macros without matching the 950 classification above. All
// dav-c310 builds observed so far (CANN 9.0/9.2, 950 device) classify as 950.
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && !CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_950() && \
    (defined(__DAV_C310__) || defined(__DAV_C310_VEC__))
#define CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_C310() 1
#else
#define CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_C310() 0
#endif

// CANN 9.0 exposes two different C310 compilation paths:
//
// - SIMD+SIMT mixed CCE compilation provides the complete documented X2/X4
//   short-vector family (char/short/int/long/float and unsigned variants).
// - the compiler-internal pure-SIMT path predefines only int2 and float2 from
//   that family; dim3 is supplied by the SIMT runtime wrapper. CANN 9.0 does
//   not document the pure-SIMT path as supporting the complete family.
//
// Keep the complete-family capability separate from the fine-grained types so
// a pure-SIMT build never advertises charN/int4/float4 merely because int2 is
// present. Packed half2 and bfloat16x2_t remain controlled by
// extended_data_types.h.
#if CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_950()
// The complete short-vector family (char/short/int/long/longlong/float and
// unsigned variants, X2/X4, on CANN 9.0/9.2 dav-c310
// kernel builds; double2 is NOT provided) and dim3 are compiler builtin
// types on the 950 family in both compilation modes.
#define CANN_ASC_STL_DETAIL_HAS_SIMT_VECTOR_TYPES() 1
#define CANN_ASC_STL_DETAIL_HAS_SIMT_INT2() 1
#define CANN_ASC_STL_DETAIL_HAS_SIMT_FLOAT2() 1
#define CANN_ASC_STL_DETAIL_HAS_SIMT_DIM3() 1
#elif CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_C310()
#if CANN_ASC_STL_DETAIL_PURE_SIMT_COMPILATION()
#define CANN_ASC_STL_DETAIL_HAS_SIMT_VECTOR_TYPES() 0
#define CANN_ASC_STL_DETAIL_HAS_SIMT_DIM3() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_SIMT_VECTOR_TYPES() 1
#define CANN_ASC_STL_DETAIL_HAS_SIMT_DIM3() 0
#endif
#define CANN_ASC_STL_DETAIL_HAS_SIMT_INT2() 1
#define CANN_ASC_STL_DETAIL_HAS_SIMT_FLOAT2() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_SIMT_VECTOR_TYPES() 0
#define CANN_ASC_STL_DETAIL_HAS_SIMT_INT2() 0
#define CANN_ASC_STL_DETAIL_HAS_SIMT_FLOAT2() 0
#define CANN_ASC_STL_DETAIL_HAS_SIMT_DIM3() 0
#endif

// ---------------------------------------------------------------------------
// Canonical SIMT runtime-layer capability gates (single source of truth).
// The warp-level builtins (asc_activemask & friends, declared by
// <simt_api/device_warp_functions.h>) ship only for SIMT-capable AI cores
// inside device translation units. Do NOT key them on bare __NPU_ARCH__
// tables elsewhere: those values are toolchain-version dependent (see the
// family-detection note above) — on CANN 9.2 the same 950 device reports
// __NPU_ARCH__ == 3510, which the historical 3101/5102 tables missed,
// silently disabling the whole warp layer in real-device builds.
// ---------------------------------------------------------------------------
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() &&  \
    (CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_950() || \
        (defined(__NPU_ARCH__) && (__NPU_ARCH__ == 3101 || __NPU_ARCH__ == 5102)))
#define CANN_ASC_STL_DETAIL_HAS_SIMT_WARP_FUNCTIONS() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_SIMT_WARP_FUNCTIONS() 0
#endif

// The lane-id primitive `laneid()` (declared by <simt_api/device_functions.h>)
// ships with CANN >= 9.2 only: older toolchains' header does not declare it.
// Self-contained devkit version probe, same pattern as __new/allocate.h.
#if CANN_ASC_STL_DETAIL_HAS_SIMT_WARP_FUNCTIONS()
#if defined(__has_include)
#if __has_include(<version/asc_devkit_version.h>)
#include <version/asc_devkit_version.h>
#elif __has_include(<ascendc/asc_devkit_version.h>)
#include <ascendc/asc_devkit_version.h>
#endif
#endif
#if defined(ASC_DEVKIT_VERSION_NUM) && ASC_DEVKIT_VERSION_NUM >= 90200000
#define CANN_ASC_STL_DETAIL_HAS_SIMT_LANEID() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_SIMT_LANEID() 0
#endif
#else
#define CANN_ASC_STL_DETAIL_HAS_SIMT_LANEID() 0
#endif

#endif  // CANN_ASC_STL_STD_DETAIL_ASC_CAPABILITIES_H
