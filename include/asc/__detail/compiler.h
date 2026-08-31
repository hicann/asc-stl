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

#ifndef CANN_ASC_STL_DETAIL_COMPILER_H
#define CANN_ASC_STL_DETAIL_COMPILER_H

#if defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
#define CANN_ASC_STL_DETAIL_COMPILER_PURE_SIMT 1
#else
#define CANN_ASC_STL_DETAIL_COMPILER_PURE_SIMT 0
#endif

#if defined(__CCE__)
#define CANN_ASC_STL_DETAIL_COMPILER_CCE 1
#else
#define CANN_ASC_STL_DETAIL_COMPILER_CCE 0
#endif

#if defined(__clang__)
#define CANN_ASC_STL_DETAIL_COMPILER_CLANG 1
#else
#define CANN_ASC_STL_DETAIL_COMPILER_CLANG 0
#endif

#if defined(__GNUC__) && !defined(__clang__)
#define CANN_ASC_STL_DETAIL_COMPILER_GCC 1
#else
#define CANN_ASC_STL_DETAIL_COMPILER_GCC 0
#endif

#if defined(_MSC_VER)
#define CANN_ASC_STL_DETAIL_COMPILER_MSVC 1
#else
#define CANN_ASC_STL_DETAIL_COMPILER_MSVC 0
#endif

#endif  // CANN_ASC_STL_DETAIL_COMPILER_H
