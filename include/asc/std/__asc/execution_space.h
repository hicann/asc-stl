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

#ifndef CANN_ASC_STL_STD_DETAIL_EXECUTION_SPACE_H
#define CANN_ASC_STL_STD_DETAIL_EXECUTION_SPACE_H

#include <asc/std/__asc/compiler.h>
#include <asc/std/__asc/system_header.h>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

// ---------------------------------------------------------------------------
// Execution space annotations
// ---------------------------------------------------------------------------
// In the ASC (Ascend) programming model:
//   - __aicore__ marks functions callable from AI Core kernels in AscendC;
//   - Host execution is the default (no annotation needed)
//
// Mixed-mode CCE compilation provides the dual [host, aicore] annotation
// (CANN's ASCENDC_HOST_AICORE spelling) for declarations callable from both
// sides of a single translation unit. Pure-SIMT mode instead uses the
// CUDA-style host/device attribute pair: there __host__ and __aicore__ are
// predefined as the host and device attribute spellings respectively.

#if defined(CANN_ASC_STL_DETAIL_COMPILER_CCE)
#define CANN_ASC_STL_HOST
#define CANN_ASC_STL_DEVICE __aicore__
#ifndef CANN_ASC_STL_HOST_DEVICE
#if defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
#define CANN_ASC_STL_HOST_DEVICE __host__ __aicore__
#else
#define CANN_ASC_STL_HOST_DEVICE [ host, aicore ]
#endif
#endif
#else  // ^^^ CANN_ASC_STL_DETAIL_COMPILER_CCE ^^^ / vvv !CANN_ASC_STL_DETAIL_COMPILER_CCE vvv
#define CANN_ASC_STL_HOST
#define CANN_ASC_STL_DEVICE
#ifndef CANN_ASC_STL_HOST_DEVICE
#define CANN_ASC_STL_HOST_DEVICE
#endif
#endif  // !CANN_ASC_STL_DETAIL_COMPILER_CCE

// Global variable annotation for device-side global variables.
// In ASC, global variables in device code do not require special annotation.
#define CANN_ASC_STL_DETAIL_GLOBAL_VARIABLE

// Target constexpr - ASC supports constexpr in device code
#define CANN_ASC_STL_DETAIL_TARGET_CONSTEXPR constexpr

// ---------------------------------------------------------------------------
// Known ASC architecture lists
// ---------------------------------------------------------------------------

//! @brief Numeric Ascend architecture families supported by this ASC-STL version.
//! Lettered product SKUs are intentionally not listed here because this macro is
//! used as a token list by downstream preprocessor code.
#define CANN_ASC_STL_DETAIL_KNOWN_ASC_ARCH_LIST 310, 320, 910, 950

//! @brief Numeric architectures with architecture-specific ASC-STL handling.
#define CANN_ASC_STL_DETAIL_KNOWN_ASC_ARCH_SPECIFIC_LIST 910

#endif  // CANN_ASC_STL_STD_DETAIL_EXECUTION_SPACE_H
