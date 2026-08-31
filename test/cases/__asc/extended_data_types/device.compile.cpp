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

#include "kernel_operator.h"  // NOLINT(build/include_order): defines AscendC attributes.

// NOLINTNEXTLINE(build/include_order): kernel_operator.h must define attributes first.
#include <asc/std/__asc/extended_data_types.h>

// Lock the extended data type values advertised for the Ascend 950 family;
// the compiler declares these builtin types in both compilation modes.
#if defined(__NPU_ARCH__) && (__NPU_ARCH__ == 5102 || __NPU_ARCH__ == 5161)
static_assert(CANN_ASC_STL_DETAIL_HAS_HALF() == 1, "half is a baseline CCE scalar type");
static_assert(CANN_ASC_STL_DETAIL_HAS_BFLOAT16() == 1, "bfloat16_t is a baseline CCE scalar type");
static_assert(CANN_ASC_STL_DETAIL_HAS_HALF2() == 1, "half2 is a builtin type on the 950 family");
static_assert(CANN_ASC_STL_DETAIL_HAS_BFLOAT16X2() == 1, "bfloat16x2_t is a builtin type on the 950 family");
static_assert(CANN_ASC_STL_DETAIL_HAS_FP8_E4M3() == 1, "float8_e4m3_t is a builtin type on the 950 family");
static_assert(CANN_ASC_STL_DETAIL_HAS_FP8_E5M2() == 1, "float8_e5m2_t is a builtin type on the 950 family");
static_assert(CANN_ASC_STL_DETAIL_HAS_FP8_E4M3X2() == 1, "float8_e4m3x2_t is a builtin type on the 950 family");
static_assert(CANN_ASC_STL_DETAIL_HAS_FP8_E5M2X2() == 1, "float8_e5m2x2_t is a builtin type on the 950 family");
static_assert(CANN_ASC_STL_DETAIL_HAS_FP8_E8M0() == 1, "float8_e8m0_t is a builtin type on the 950 family");
static_assert(CANN_ASC_STL_DETAIL_HAS_FP4_E2M1X2() == 1, "float4_e2m1x2_t is a builtin type on the 950 family");
#elif defined(__DAV_C310__) || defined(__DAV_C310_VEC__)
static_assert(CANN_ASC_STL_DETAIL_HAS_HALF() == 1, "half is a baseline CCE scalar type");
static_assert(CANN_ASC_STL_DETAIL_HAS_BFLOAT16() == 1, "bfloat16_t is a baseline CCE scalar type");
static_assert(CANN_ASC_STL_DETAIL_HAS_HALF2() == 1, "half2 is provided for the C310 family");
static_assert(CANN_ASC_STL_DETAIL_HAS_BFLOAT16X2() == 1, "bfloat16x2_t is provided for the C310 family");
#endif

extern "C" __global__ __aicore__ void asc_stl_extended_data_types_device_kernel()
{
    // Compilation of this kernel is the assertion: the detection macros above
    // are preprocessor-level contracts and need no runtime probe.
}
