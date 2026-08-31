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

#ifndef CANN_ASC_STL_STD_DETAIL_INTERNAL_ATOMIC_H
#define CANN_ASC_STL_STD_DETAIL_INTERNAL_ATOMIC_H

#include <asc/__accl_config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && \
    (CANN_ASC_STL_DETAIL_COMPILER(CLANG) || CANN_ASC_STL_DETAIL_COMPILER(GCC))
#define CANN_ASC_STL_DETAIL_ACCL_ATOMIC_ALWAYS_LOCK_FREE(...) __atomic_always_lock_free(__VA_ARGS__)
#endif

// Do not infer a CANN device lock-free guarantee from object size. Device
// atomics must be selected through an architecture-specific AscendC backend;
// no generic lock-free contract is advertised in CCE mode.

// No known compiler in use requires bypassing automatic storage checks in
// atomics. The macro CANN_ASC_STL_DETAIL_ACCL_ATOMIC_UNSAFE_AUTOMATIC_STORAGE is intentionally
// not defined.

#define CANN_ASC_STL_DETAIL_ACCL_ATOMIC_FLAG_TYPE int

// Clang provides 128b atomics as a builtin
#if defined(ASC_ENABLE_EXPERIMENTAL_HOST_ATOMICS_128B)
#define CANN_ASC_STL_DETAIL_ACCL_HOST_128_ATOMICS_ENABLED() 1
#define CANN_ASC_STL_DETAIL_ACCL_HOST_128_ATOMICS_MAYBE() 0
// GCC does not provide 128b atomics, but they may be available as a library, this requires opt-in usage.
// See: https://gcc.gnu.org/onlinedocs/gcc/x86-Options.html "-mcx16" for more
#elif CANN_ASC_STL_DETAIL_COMPILER(CLANG) || CANN_ASC_STL_DETAIL_COMPILER(GCC)
#define CANN_ASC_STL_DETAIL_ACCL_HOST_128_ATOMICS_ENABLED() 0
#define CANN_ASC_STL_DETAIL_ACCL_HOST_128_ATOMICS_MAYBE() 1
#else
#define CANN_ASC_STL_DETAIL_ACCL_HOST_128_ATOMICS_ENABLED() 0
#define CANN_ASC_STL_DETAIL_ACCL_HOST_128_ATOMICS_MAYBE() 0
#endif

#endif  // CANN_ASC_STL_STD_DETAIL_INTERNAL_ATOMIC_H
