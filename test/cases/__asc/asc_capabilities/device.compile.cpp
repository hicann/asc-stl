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
#include <asc/std/__asc/asc_capabilities.h>

// Lock the per-architecture capability values advertised by this header so a
// toolchain regression cannot silently flip device code onto degraded paths.
#if defined(__NPU_ARCH__) && (__NPU_ARCH__ == 5102 || __NPU_ARCH__ == 5161)
static_assert(CANN_ASC_STL_DETAIL_AICORE_ARCH() == __NPU_ARCH__, "950 family must report its __NPU_ARCH__ value");
static_assert(CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_950() == 1, "950 family must be detected");
static_assert(CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_C310() == 0, "950 family must not be misread as C310");
static_assert(CANN_ASC_STL_DETAIL_HAS_SIMT_VECTOR_TYPES() == 1, "950 family provides the short-vector family");
static_assert(CANN_ASC_STL_DETAIL_HAS_SIMT_INT2() == 1, "int2 is a builtin type on the 950 family");
static_assert(CANN_ASC_STL_DETAIL_HAS_SIMT_FLOAT2() == 1, "float2 is a builtin type on the 950 family");
static_assert(CANN_ASC_STL_DETAIL_HAS_SIMT_DIM3() == 1, "dim3 is a builtin type on the 950 family");
#elif defined(__DAV_C310__) || defined(__DAV_C310_VEC__)
// The dav-c310 toolchain macros identify the Ascend 950 dav-c310 generation. Real
// hardware probes show the same device reports __NPU_ARCH__ 3101 under CANN 9.0 and
// 3510 under CANN 9.2, so __NPU_ARCH__ is not a stable family key; the dedicated
// toolchain macros are. The legacy C310 classification remains only as a fallback for
// hypothetical non-950 dav toolchains.
static_assert(CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_950() == 1, "dav-c310 toolchain macros identify the 950 family");
static_assert(
    CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_C310() == 0, "dav-c310 (950) must not be misread as the legacy C310 family");
static_assert(CANN_ASC_STL_DETAIL_HAS_SIMT_VECTOR_TYPES() == 1, "the 950 family provides the short-vector family");
static_assert(CANN_ASC_STL_DETAIL_HAS_SIMT_INT2() == 1, "int2 is a builtin type on the 950 family");
static_assert(CANN_ASC_STL_DETAIL_HAS_SIMT_FLOAT2() == 1, "float2 is a builtin type on the 950 family");
static_assert(CANN_ASC_STL_DETAIL_HAS_SIMT_DIM3() == 1, "dim3 is a builtin type on the 950 family");
#endif

extern "C" __global__ __aicore__ void asc_stl_asc_capabilities_device_kernel()
{
    // Compilation of this kernel is the assertion: the capability macros above
    // are preprocessor-level contracts and need no runtime probe.
}
