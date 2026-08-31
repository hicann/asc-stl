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

#ifndef CANN_ASC_STL_STD_DETAIL_EXTENDED_DATA_TYPES_H
#define CANN_ASC_STL_STD_DETAIL_EXTENDED_DATA_TYPES_H

#include <asc/std/__asc/compiler.h>
#include <asc/std/__asc/system_header.h>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__asc/architecture.h>
#include <asc/std/__asc/asc_capabilities.h>
#include <asc/std/__asc/asc_toolkit.h>
#include <asc/std/__asc/diagnostic.h>
#include <asc/std/__asc/os.h>
#include <asc/std/__asc/preprocessor.h>

// ---------------------------------------------------------------------------
// Extended data type feature detection macros
// ---------------------------------------------------------------------------
// All macros default to 0 (unsupported). Sections below conditionally enable
// them based on platform, compiler, and device compilation mode.
//
// AscendC provides the extended scalar/vector types this layer detects:
//   half, half2, bfloat16_t, bfloat16x2_t, float8_e4m3_t, float8_e5m2_t,
//   float8_e4m3x2_t, float8_e5m2x2_t, float4_e2m1x2_t.  When a scalar fp4
//   storage type is unavailable, use the packed float4_e2m1x2_t form.
//
// Formats with no Ascend scalar/vector equivalent are always unavailable:
//   fp8x4 packing, fp6 (all widths), fp4x4 packing.

#define CANN_ASC_STL_DETAIL_HAS_INT128() 0
#define CANN_ASC_STL_DETAIL_HAS_HALF() 0
#define CANN_ASC_STL_DETAIL_HAS_HALF2() 0
#define CANN_ASC_STL_DETAIL_HAS_BFLOAT16() 0
#define CANN_ASC_STL_DETAIL_HAS_BFLOAT16X2() 0
#define CANN_ASC_STL_DETAIL_HAS_FP8_E4M3() 0
#define CANN_ASC_STL_DETAIL_HAS_FP8_E5M2() 0
#define CANN_ASC_STL_DETAIL_HAS_FP8_E4M3X2() 0
#define CANN_ASC_STL_DETAIL_HAS_FP8_E5M2X2() 0
#define CANN_ASC_STL_DETAIL_HAS_FP8_E8M0() 0
#define CANN_ASC_STL_DETAIL_HAS_FP4_E2M1X2() 0
#define CANN_ASC_STL_DETAIL_HAS_FLOAT128() 0

#define CANN_ASC_STL_DETAIL_HAS_FP16() CANN_ASC_STL_DETAIL_HAS_HALF()
#define CANN_ASC_STL_DETAIL_HAS_BF16() CANN_ASC_STL_DETAIL_HAS_BFLOAT16()
#define CANN_ASC_STL_DETAIL_HAS_FP8() (CANN_ASC_STL_DETAIL_HAS_FP8_E4M3() || CANN_ASC_STL_DETAIL_HAS_FP8_E5M2())
#define CANN_ASC_STL_DETAIL_HAS_FP4() CANN_ASC_STL_DETAIL_HAS_FP4_E2M1X2()
#define CANN_ASC_STL_DETAIL_HAS_FP8_E8M0X2() 0
#define CANN_ASC_STL_DETAIL_HAS_FP8_E8M0X4() 0
#define CANN_ASC_STL_DETAIL_HAS_FP8_E4M3X4() 0
#define CANN_ASC_STL_DETAIL_HAS_FP8_E5M2X4() 0
#define CANN_ASC_STL_DETAIL_HAS_FP6_E2M3() 0
#define CANN_ASC_STL_DETAIL_HAS_FP6_E3M2() 0
#define CANN_ASC_STL_DETAIL_HAS_FP6_E2M3X2() 0
#define CANN_ASC_STL_DETAIL_HAS_FP6_E3M2X2() 0
#define CANN_ASC_STL_DETAIL_HAS_FP6_E2M3X4() 0
#define CANN_ASC_STL_DETAIL_HAS_FP6_E3M2X4() 0
#define CANN_ASC_STL_DETAIL_HAS_FP4_E2M1() 0
#define CANN_ASC_STL_DETAIL_HAS_FP4_E2M1X4() 0

// ---------------------------------------------------------------------------
// __int128 detection
// ---------------------------------------------------------------------------

#if !defined(ASC_DISABLE_INT128_SUPPORT) && CANN_ASC_STL_DETAIL_OS(LINUX) && defined(__SIZEOF_INT128__)
#undef CANN_ASC_STL_DETAIL_HAS_INT128
#define CANN_ASC_STL_DETAIL_HAS_INT128() 1
#endif

// ---------------------------------------------------------------------------
// ASC device extended data types
// ---------------------------------------------------------------------------
// half and bfloat16_t are baseline CCE scalar types. Packed FP8/FP4 and x2
// spellings are advertised only for compiler targets whose builtin type set
// has been verified to provide them: the C310 family (packed spellings in
// mixed-mode builds) and the Ascend 950 family (compiler a5/a6 generation,
// both compilation modes). Merely compiling with CCE is not sufficient
// evidence for the newer formats on other targets.

#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#undef CANN_ASC_STL_DETAIL_HAS_HALF
#define CANN_ASC_STL_DETAIL_HAS_HALF() 1
#undef CANN_ASC_STL_DETAIL_HAS_BFLOAT16
#define CANN_ASC_STL_DETAIL_HAS_BFLOAT16() 1
#endif

// Packed half2 and bfloat16x2_t are provided by the C310 family in both
// compilation modes and by the 950 family (compiler a5/a6 generation) as
// builtin types in mixed and pure-SIMT compilation alike.
#if CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_950() || CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_C310()
#undef CANN_ASC_STL_DETAIL_HAS_HALF2
#define CANN_ASC_STL_DETAIL_HAS_HALF2() 1
#undef CANN_ASC_STL_DETAIL_HAS_BFLOAT16X2
#define CANN_ASC_STL_DETAIL_HAS_BFLOAT16X2() 1
#endif

// The FP8 spellings (e4m3, e5m2, e8m0), their x2 packs and float4_e2m1x2_t
// are builtin types on the 950 family in both compilation modes; the C310
// family provides them in mixed-mode builds only.
#if CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_950() || \
    (CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_C310() && !CANN_ASC_STL_DETAIL_PURE_SIMT_COMPILATION())
#undef CANN_ASC_STL_DETAIL_HAS_FP8_E4M3
#define CANN_ASC_STL_DETAIL_HAS_FP8_E4M3() 1
#undef CANN_ASC_STL_DETAIL_HAS_FP8_E5M2
#define CANN_ASC_STL_DETAIL_HAS_FP8_E5M2() 1
#undef CANN_ASC_STL_DETAIL_HAS_FP8_E4M3X2
#define CANN_ASC_STL_DETAIL_HAS_FP8_E4M3X2() 1
#undef CANN_ASC_STL_DETAIL_HAS_FP8_E5M2X2
#define CANN_ASC_STL_DETAIL_HAS_FP8_E5M2X2() 1
#undef CANN_ASC_STL_DETAIL_HAS_FP8_E8M0
#define CANN_ASC_STL_DETAIL_HAS_FP8_E8M0() 1
#undef CANN_ASC_STL_DETAIL_HAS_FP4_E2M1X2
#define CANN_ASC_STL_DETAIL_HAS_FP4_E2M1X2() 1
#endif  // CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_950() || (CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_C310() &&
        // !CANN_ASC_STL_DETAIL_PURE_SIMT_COMPILATION())

// ---------------------------------------------------------------------------
// __float128 detection
// ---------------------------------------------------------------------------

#if !defined(ASC_DISABLE_FLOAT128_SUPPORT) && CANN_ASC_STL_DETAIL_HAS_INT128() && CANN_ASC_STL_DETAIL_OS(LINUX) && \
    !CANN_ASC_STL_DETAIL_ARCH(ARM64)
// Detect host compiler support
#if defined(__SIZEOF_FLOAT128__) || defined(__FLOAT128__)
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// __float128 is only supported on host compilation in ASC-STL.
// CCE device compilation does not support __float128.
#undef CANN_ASC_STL_DETAIL_HAS_FLOAT128
#define CANN_ASC_STL_DETAIL_HAS_FLOAT128() 1
#endif  // !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#endif  // Host compiler support
#endif  // !ASC_DISABLE_FLOAT128_SUPPORT && CANN_ASC_STL_DETAIL_HAS_INT128() && CANN_ASC_STL_DETAIL_OS(LINUX) &&
        // !CANN_ASC_STL_DETAIL_ARCH(ARM64)

// GCC does not allow q/Q floating point literals when __STRICT_ANSI__ is defined.
// They may be allowed by -fext-numeric-literals, but there is no way to detect it
// in the preprocessor. The user is required to define ASC_GCC_HAS_EXTENDED_NUMERIC_LITERALS
// in this case. Otherwise, we disable the __float128 support.
#if CANN_ASC_STL_DETAIL_HAS_FLOAT128() && CANN_ASC_STL_DETAIL_COMPILER(GCC) && defined(__STRICT_ANSI__) && \
    !defined(ASC_GCC_HAS_EXTENDED_NUMERIC_LITERALS)
#undef CANN_ASC_STL_DETAIL_HAS_FLOAT128
#define CANN_ASC_STL_DETAIL_HAS_FLOAT128() 0
#endif  // CANN_ASC_STL_DETAIL_HAS_FLOAT128()

#endif  // CANN_ASC_STL_STD_DETAIL_EXTENDED_DATA_TYPES_H
