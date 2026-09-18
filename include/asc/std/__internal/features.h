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

#ifndef CANN_ASC_STL_STD_DETAIL_INTERNAL_FEATURES_H
#define CANN_ASC_STL_STD_DETAIL_INTERNAL_FEATURES_H

#include <asc/__accl_config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

// Language and standard library feature detection

#define CANN_ASC_STL_DETAIL_ACCL_HAS_CXX20_CHRONO_LITERALS() \
    (!CANN_ASC_STL_DETAIL_COMPILER(CLANG) || CANN_ASC_STL_DETAIL_STD_VER >= 2020)
#define CANN_ASC_STL_DETAIL_ACCL_HAS_MONOTONIC_CLOCK() 0
#define CANN_ASC_STL_DETAIL_ACCL_HAS_SPACESHIP_OPERATOR() 0

#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() || !defined(__cpp_aligned_new) || __cpp_aligned_new < 201606
#define CANN_ASC_STL_DETAIL_ACCL_HAS_ALIGNED_ALLOCATION() 0
#else
#define CANN_ASC_STL_DETAIL_ACCL_HAS_ALIGNED_ALLOCATION() 1
#endif  // !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && __cpp_aligned_new >= 201606

// We need `is_constant_evaluated` for clang and gcc. MSVC also needs extensive rework
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#define CANN_ASC_STL_DETAIL_ACCL_HAS_CONSTEXPR_COMPLEX_OPERATIONS() 0
#elif !defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTANT_EVALUATED)
#define CANN_ASC_STL_DETAIL_ACCL_HAS_CONSTEXPR_COMPLEX_OPERATIONS() 0
#elif CANN_ASC_STL_DETAIL_COMPILER(MSVC)
#define CANN_ASC_STL_DETAIL_ACCL_HAS_CONSTEXPR_COMPLEX_OPERATIONS() 0
#else
#define CANN_ASC_STL_DETAIL_ACCL_HAS_CONSTEXPR_COMPLEX_OPERATIONS() 1
#endif

#if CANN_ASC_STL_DETAIL_ACCL_HAS_CONSTEXPR_COMPLEX_OPERATIONS()
#define CANN_ASC_STL_DETAIL_ACCL_CONSTEXPR_COMPLEX constexpr
#else
#define CANN_ASC_STL_DETAIL_ACCL_CONSTEXPR_COMPLEX
#endif  // !CANN_ASC_STL_DETAIL_ACCL_HAS_CONSTEXPR_COMPLEX_OPERATIONS()

#ifndef CANN_ASC_STL_DETAIL_ACCL_HAS_NO_INCOMPLETE_RANGES
#define CANN_ASC_STL_DETAIL_ACCL_HAS_NO_INCOMPLETE_RANGES
#endif  // CANN_ASC_STL_DETAIL_ACCL_HAS_NO_INCOMPLETE_RANGES

// ASC FP16/BF16 support is detected via CANN_ASC_STL_DETAIL_HAS_FP16() and CANN_ASC_STL_DETAIL_HAS_BF16()
// in asc/std/__asc/extended_data_types.h (included through __accl_config).

#if CANN_ASC_STL_DETAIL_COMPILER(MSVC)
#define CANN_ASC_STL_DETAIL_ACCL_ALIGNAS_TYPE(x) alignas(x)
#define CANN_ASC_STL_DETAIL_ACCL_ALIGNAS(x) __declspec(align(x))
#elif CANN_ASC_STL_DETAIL_HAS_FEATURE(cxx_alignas)
#define CANN_ASC_STL_DETAIL_ACCL_ALIGNAS_TYPE(x) alignas(x)
#define CANN_ASC_STL_DETAIL_ACCL_ALIGNAS(x) alignas(x)
#else
#define CANN_ASC_STL_DETAIL_ACCL_ALIGNAS_TYPE(x) __attribute__((__aligned__(alignof(x))))
#define CANN_ASC_STL_DETAIL_ACCL_ALIGNAS(x) __attribute__((__aligned__(x)))
#endif  // !CANN_ASC_STL_DETAIL_COMPILER(MSVC) && !CANN_ASC_STL_DETAIL_HAS_FEATURE(cxx_alignas)

// Enable removed C++17 features
#if defined(CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_FEATURES)
#define CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_BINDERS
#endif  // CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_FEATURES

#ifndef ASC_DISABLE_ADDITIONAL_DIAGNOSTICS
#define CANN_ASC_STL_DETAIL_ACCL_DIAGNOSE_WARNING(_COND, _MSG) CANN_ASC_STL_DETAIL_DIAGNOSE_IF(_COND, _MSG, "warning")
#define CANN_ASC_STL_DETAIL_ACCL_DIAGNOSE_ERROR(_COND, _MSG) CANN_ASC_STL_DETAIL_DIAGNOSE_IF(_COND, _MSG, "error")
#else
#define CANN_ASC_STL_DETAIL_ACCL_DIAGNOSE_WARNING(_COND, _MSG)
#define CANN_ASC_STL_DETAIL_ACCL_DIAGNOSE_ERROR(_COND, _MSG)
#endif

// SIMD F32x2 intrinsics — no ASC equivalent
#define CANN_ASC_STL_DETAIL_ACCL_HAS_SIMD_F32X2_INTRINSICS() 0
#define CANN_ASC_STL_DETAIL_ACCL_HAS_SIMD_F32X2() 0

// Third party libraries

#if defined(__has_include)
#if (__has_include(<dlpack/dlpack.h>) || __has_include(<dlpack.h>)) && \
     !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && !defined(ASC_DISABLE_DLPACK)
#define CANN_ASC_STL_DETAIL_ACCL_HAS_DLPACK() 1
#else  // ^^^ has dlpack ^^^ / vvv no dlpack vvv
#define CANN_ASC_STL_DETAIL_ACCL_HAS_DLPACK() 0
#endif  // ^^^ no dlpack ^^^
#else
#define CANN_ASC_STL_DETAIL_ACCL_HAS_DLPACK() 0
#endif  // !defined(__has_include)

#endif  // CANN_ASC_STL_STD_DETAIL_INTERNAL_FEATURES_H
