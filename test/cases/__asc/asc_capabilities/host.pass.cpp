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

#include <asc/std/__asc/asc_capabilities.h>

#if defined(CANN_ASC_STL_DETAIL_PTX_ARCH) || defined(CANN_ASC_STL_DETAIL_HAS_PDL) ||           \
    defined(CANN_ASC_STL_DETAIL_HAS_RDC) || defined(CANN_ASC_STL_DETAIL_HAS_EWP) ||            \
    defined(CANN_ASC_STL_DETAIL_HAS_DEVICE_RUNTIME) || defined(CANN_ASC_STL_DETAIL_HAS_CDP) || \
    defined(CANN_ASC_STL_DETAIL_LAUNCH_BOUNDS) || defined(CANN_ASC_STL_DETAIL_BLOCK_SIZE)
#error "CUDA capability shadows must not be exported by ASC-STL"
#endif

static_assert(CANN_ASC_STL_DETAIL_AICORE_ARCH() == 0, "host compilation has no AI Core architecture");
static_assert(CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_C310() == 0, "host compilation is not C310");
static_assert(CANN_ASC_STL_DETAIL_HAS_SIMT_VECTOR_TYPES() == 0, "host compilation has no SIMT vector builtins");
static_assert(CANN_ASC_STL_DETAIL_HAS_SIMT_INT2() == 0, "host compilation has no CCE int2 builtin");
static_assert(CANN_ASC_STL_DETAIL_HAS_SIMT_FLOAT2() == 0, "host compilation has no CCE float2 builtin");
static_assert(CANN_ASC_STL_DETAIL_HAS_SIMT_DIM3() == 0, "host compilation has no CCE dim3 runtime type");

int main()
{
    return 0;
}
