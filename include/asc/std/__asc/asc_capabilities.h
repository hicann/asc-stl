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

// The architecture identifier uses the __NPU_ARCH__ scale exclusively (e.g.
// 3002 = 910B family, 3510 = 310R6 family, 5102/5161 = 950 family). The
// __CCE_AICORE__ macro uses a coarser scale and collides across chip families
// (it reports 310 for both the C310 family and the 310R6 family), so it is not
// a usable architecture identifier.
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && defined(__NPU_ARCH__)
#define CANN_ASC_STL_DETAIL_AICORE_ARCH() __NPU_ARCH__
#else
#define CANN_ASC_STL_DETAIL_AICORE_ARCH() 0
#endif

// The C310 family is identified by its dedicated toolchain macros.
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && (defined(__DAV_C310__) || defined(__DAV_C310_VEC__))
#define CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_C310() 1
#else
#define CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_C310() 0
#endif

// The Ascend 950 family is the compiler's a5/a6 generation (__NPU_ARCH__ 5102
// and 5161). These AI cores run SIMT workloads natively: the compiler provides
// the builtin short-vector family and dim3 in both compilation modes, and the
// CANN SIMT runtime layer gates its warp support on these same values.
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && defined(__NPU_ARCH__) && (__NPU_ARCH__ == 5102 || __NPU_ARCH__ == 5161)
#define CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_950() 1
#else
#define CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_950() 0
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
// The complete short-vector family (char/short/int/long/float and unsigned
// variants) and dim3 are compiler builtin types on the 950 family in both
// compilation modes.
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

#endif  // CANN_ASC_STL_STD_DETAIL_ASC_CAPABILITIES_H
