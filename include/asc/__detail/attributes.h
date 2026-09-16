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

#ifndef CANN_ASC_STL_DETAIL_ATTRIBUTES_H
#define CANN_ASC_STL_DETAIL_ATTRIBUTES_H

#if defined(__has_attribute)
#define CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE(attribute) __has_attribute(attribute)
#else
#define CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE(attribute) 0
#endif

#if defined(__has_cpp_attribute)
#define CANN_ASC_STL_DETAIL_HAS_CPP_ATTRIBUTE(attribute) __has_cpp_attribute(attribute)
#else
#define CANN_ASC_STL_DETAIL_HAS_CPP_ATTRIBUTE(attribute) 0
#endif

#if CANN_ASC_STL_DETAIL_HAS_CPP_ATTRIBUTE(nodiscard)
#define CANN_ASC_STL_NODISCARD [[nodiscard]]
#else
#define CANN_ASC_STL_NODISCARD
#endif

#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 202002L) || (!defined(_MSVC_LANG) && __cplusplus >= 202002L)) && \
    CANN_ASC_STL_DETAIL_HAS_CPP_ATTRIBUTE(no_unique_address)
#define CANN_ASC_STL_NO_UNIQUE_ADDRESS [[no_unique_address]]
#else
#define CANN_ASC_STL_NO_UNIQUE_ADDRESS
#endif

#if defined(__CCE__) || defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
#define CANN_ASC_STL_NORETURN
#else
#define CANN_ASC_STL_NORETURN [[noreturn]]
#endif

#if CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE(always_inline)
#define CANN_ASC_STL_DETAIL_FORCE_INLINE __attribute__((always_inline))
#else
#define CANN_ASC_STL_DETAIL_FORCE_INLINE
#endif

#if CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE(noinline)
#define CANN_ASC_STL_DETAIL_NO_INLINE __attribute__((noinline))
#else
#define CANN_ASC_STL_DETAIL_NO_INLINE
#endif

#endif  // CANN_ASC_STL_DETAIL_ATTRIBUTES_H
