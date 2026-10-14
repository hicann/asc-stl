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

#ifndef CANN_ASC_STL_DETAIL_EXECUTION_SPACE_H
#define CANN_ASC_STL_DETAIL_EXECUTION_SPACE_H

// Design decision (do not "fix"): under CCE the whole translation unit is
// treated as a device compilation (DEVICE_COMPILATION() == 1) even for its
// host-qualified functions, so host fast paths gated on
// `!DEVICE_COMPILATION()` never activate inside a CCE unit - the frozen
// hosted/device double gate degrades to its safe single gate there. This is
// deliberate: a mixed-SIMD unit may lower any function to AI Core code, and
// letting host-only symbols (host libc, acl runtime calls) leak into it is
// the failure mode this conservative reading prevents. Host fast paths
// activate only in pure host compilers (GCC/Clang/MSVC).

#if defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
#define CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() 1
#define CANN_ASC_STL_DETAIL_SIMT_COMPILATION() 1
#define CANN_ASC_STL_DETAIL_SIMD_COMPILATION() 0
#define CANN_ASC_STL_HOST
#define CANN_ASC_STL_DEVICE __aicore__
#define CANN_ASC_STL_HOST_DEVICE __aicore__
#define CANN_ASC_STL_SIMT_DEVICE __aicore__
#define CANN_ASC_STL_HOST_SIMT_DEVICE __aicore__
#elif defined(__CCE__)
#define CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() 1
#define CANN_ASC_STL_DETAIL_SIMT_COMPILATION() 0
#define CANN_ASC_STL_DETAIL_SIMD_COMPILATION() 1
#define CANN_ASC_STL_HOST __host__
#define CANN_ASC_STL_DEVICE __aicore__
#define CANN_ASC_STL_HOST_DEVICE __host__ __aicore__
#define CANN_ASC_STL_SIMT_DEVICE
#define CANN_ASC_STL_HOST_SIMT_DEVICE __host__
#else
#define CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() 0
#define CANN_ASC_STL_DETAIL_SIMT_COMPILATION() 0
#define CANN_ASC_STL_DETAIL_SIMD_COMPILATION() 0
#define CANN_ASC_STL_HOST
#define CANN_ASC_STL_DEVICE
#define CANN_ASC_STL_HOST_DEVICE
#define CANN_ASC_STL_SIMT_DEVICE
#define CANN_ASC_STL_HOST_SIMT_DEVICE
#endif

#endif  // CANN_ASC_STL_DETAIL_EXECUTION_SPACE_H
