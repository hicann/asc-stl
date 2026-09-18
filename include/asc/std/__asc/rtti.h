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

#ifndef CANN_ASC_STL_STD_DETAIL_RTTI_H
#define CANN_ASC_STL_STD_DETAIL_RTTI_H

#include <asc/std/__asc/compiler.h>
#include <asc/std/__asc/system_header.h>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__asc/builtin.h>

// NOTE: some compilers support the `typeid` feature but not the `dynamic_cast`
// feature. This is why we have separate macros for each.

#ifndef CANN_ASC_STL_DETAIL_NO_RTTI
#if defined(ASC_DISABLE_RTTI)  // Escape hatch for users to manually disable RTTI
#define CANN_ASC_STL_DETAIL_NO_RTTI
#elif CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#define CANN_ASC_STL_DETAIL_NO_RTTI  // No RTTI in ASC device code
#elif CANN_ASC_STL_DETAIL_COMPILER(MSVC)
#if _CPPRTTI == 0
#define CANN_ASC_STL_DETAIL_NO_RTTI
#endif
#elif CANN_ASC_STL_DETAIL_COMPILER(CLANG)
#if !CANN_ASC_STL_DETAIL_HAS_FEATURE(cxx_rtti)
#define CANN_ASC_STL_DETAIL_NO_RTTI
#endif
#else
#if __GXX_RTTI == 0 && __cpp_rtti == 0
#define CANN_ASC_STL_DETAIL_NO_RTTI
#endif
#endif
#endif  // !CANN_ASC_STL_DETAIL_NO_RTTI

#ifndef CANN_ASC_STL_DETAIL_NO_TYPEID
#if defined(ASC_DISABLE_RTTI)  // ASC_DISABLE_RTTI disables typeid also
#define CANN_ASC_STL_DETAIL_NO_TYPEID
#elif CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#define CANN_ASC_STL_DETAIL_NO_TYPEID  // No typeid in ASC device code
#elif CANN_ASC_STL_DETAIL_COMPILER(MSVC)
// No-op, MSVC always supports typeid even when RTTI is disabled
#elif CANN_ASC_STL_DETAIL_COMPILER(CLANG)
#if !CANN_ASC_STL_DETAIL_HAS_FEATURE(cxx_rtti)
#define CANN_ASC_STL_DETAIL_NO_TYPEID
#endif
#else
#if __GXX_RTTI == 0 && __cpp_rtti == 0
#define CANN_ASC_STL_DETAIL_NO_TYPEID
#endif
#endif
#endif  // !CANN_ASC_STL_DETAIL_NO_TYPEID

#endif  // CANN_ASC_STL_STD_DETAIL_RTTI_H
