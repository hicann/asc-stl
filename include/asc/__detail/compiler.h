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

#ifndef CANN_ASC_STL_DETAIL_COMPILER_H
#define CANN_ASC_STL_DETAIL_COMPILER_H

// Compiler identity is additive, not exclusive: more than one of the flags
// below can be 1 at the same time. The legal combinations and the checking
// order downstream code should assume:
//
//   pure SIMT wrapper  -> PURE_SIMT=1, CLANG=1, GNUC=1 (clang frontend)
//   CCE (mixed SIMD)   -> CCE=1, CLANG=1, GNUC=1 (BiSheng is clang-based)
//   plain Clang        -> CLANG=1, GNUC=1
//   GCC                -> GCC=1 only (GCC is defined to exclude clang)
//   MSVC               -> MSVC=1 only
//
// GCC=1 therefore does NOT mean "not clang"; guard clang-specific behavior
// on COMPILER_CLANG and check it before checking GNUC wherever clang and
// real GCC differ (see diagnostics.h for an order-sensitive consumer). CCE
// and PURE_SIMT are checked first when they imply the device compilation
// environment.

#if defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
#define CANN_ASC_STL_DETAIL_COMPILER_PURE_SIMT 1
#else
#define CANN_ASC_STL_DETAIL_COMPILER_PURE_SIMT 0
#endif

#if defined(__CCE__)
#define CANN_ASC_STL_DETAIL_COMPILER_CCE 1
#else
#define CANN_ASC_STL_DETAIL_COMPILER_CCE 0
#endif

#if defined(__clang__)
#define CANN_ASC_STL_DETAIL_COMPILER_CLANG 1
#else
#define CANN_ASC_STL_DETAIL_COMPILER_CLANG 0
#endif

#if defined(__GNUC__) && !defined(__clang__)
#define CANN_ASC_STL_DETAIL_COMPILER_GCC 1
#else
#define CANN_ASC_STL_DETAIL_COMPILER_GCC 0
#endif

#if defined(_MSC_VER)
#define CANN_ASC_STL_DETAIL_COMPILER_MSVC 1
#else
#define CANN_ASC_STL_DETAIL_COMPILER_MSVC 0
#endif

// ---------------------------------------------------------------------------
// Freestanding environment detection
// ---------------------------------------------------------------------------
// CCE (AI Core kernel compilation) is treated as freestanding since it has
// no access to the host standard library. CANN_ASC_STL_DETAIL_ENABLE_FREESTANDING
// lets a hosted build opt into the same stripped-down vocabulary; freestanding
// builds additionally lose typeid support.

// 纯 SIMT 设备编译（--enable-simt）下本工具链不定义 __CCE__，仅定义
// __NPU_COMPILER_INTERNAL_PURE_SIMT__（与 execution_space.h 的设备检测一致），
// 补入同一标记，保证设备侧（含 SIMT）一律判为 freestanding。
#if defined(CANN_ASC_STL_DETAIL_ENABLE_FREESTANDING) || CANN_ASC_STL_DETAIL_COMPILER_CCE || \
    defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
#define CANN_ASC_STL_DETAIL_FREESTANDING() 1
#define CANN_ASC_STL_DETAIL_HOSTED() 0
#define CANN_ASC_STL_DETAIL_NO_TYPEID
#else
#define CANN_ASC_STL_DETAIL_FREESTANDING() 0
#define CANN_ASC_STL_DETAIL_HOSTED() 1
#endif

// ---------------------------------------------------------------------------
// Device heap allocation capability
// ---------------------------------------------------------------------------
// CCE mixed-SIMD (aicore-lang) rejects general operator new/delete in AI Core
// code (experimentally confirmed, 2026-09-09). The CANN pure-SIMT wrapper
// mode lowers device new to dpp_alloc/dpp_dealloc calls; CANN 9.2 declares
// the symbols in __clang_dpp_runtime_wrapper.h but does not yet ship a
// library implementation. The compilation path and self-provided pool
// allocator both work on real 950 hardware (heap new/delete for arrays and
// class objects verified 2026-09-09). Gate allocation-dependent paths on this
// capability rather than on HOSTED alone.
#if CANN_ASC_STL_DETAIL_COMPILER_CCE && __has_include("simt_api/cooperative_groups.h") && !defined(__APPLE__)
#define CANN_ASC_STL_DETAIL_HAS_DEVICE_HEAP() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_DEVICE_HEAP() 0
#endif

#endif  // CANN_ASC_STL_DETAIL_COMPILER_H
