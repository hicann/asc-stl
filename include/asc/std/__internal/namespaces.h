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

#ifndef CANN_ASC_STL_STD_DETAIL_INTERNAL_NAMESPACES_H
#define CANN_ASC_STL_STD_DETAIL_INTERNAL_NAMESPACES_H

#include <asc/__accl_config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

// ASC-STL namespace helpers. Public lookup is asc::... / asc::std::... .
// ASC-STL keeps a single non-versioned ABI layout: the namespace macros open
// plain namespaces and no inline ABI layer is introduced, matching the
// baseline CANN_ASC_STL_BEGIN_NAMESPACE convention.

// Basic namespace open/close
#define CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_NOVERSION(_NS) namespace _NS {
#define CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_NOVERSION(_NS) }
#define CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE(_NS) namespace _NS {
#define CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE(_NS) }

// Standard namespaces
#define CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_NOVERSION \
    CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_NOVERSION(asc::std)
#define CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_NOVERSION \
    CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_NOVERSION(asc::std)
#define CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE(asc::std)
#define CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE(asc::std)

// asc specific namespaces
#define CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE(asc)
#define CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE(asc)
#define CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_MR CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE(asc::mr)
#define CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_MR CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE(asc::mr)
#define CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_DEVICE CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE(asc::device)
#define CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_DEVICE CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE(asc::device)
#define CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_DEVICE_EXPERIMENTAL \
    CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE(asc::device::experimental)
#define CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_DEVICE_EXPERIMENTAL \
    CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE(asc::device::experimental)
#define CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_DRIVER CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE(asc::__driver)
#define CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_DRIVER CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE(asc::__driver)

// Namespaces related to <simd>
#define CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_SIMD CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE(asc::std::simd)
#define CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_SIMD CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE(asc::std::simd)

// Namespaces related to <ranges>
#define CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES \
    CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE(asc::std::ranges)
#define CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE(asc::std::ranges)
#define CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_VIEWS \
    CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE(asc::std::ranges::views)
#define CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_VIEWS \
    CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE(asc::std::ranges::views)

#define CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(_CPO) namespace _CPO {
#define CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO }

// Namespaces related to chrono / filesystem
#define CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_FILESYSTEM    \
    CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_NOVERSION \
    inline namespace __fs {                                    \
    namespace filesystem {
#define CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_FILESYSTEM \
    }                                                     \
    }                                                     \
    CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_NOVERSION

// Namespaces related to execution
#define CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_EXECUTION \
    CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE(asc::std::execution)
#define CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_EXECUTION \
    CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE(asc::std::execution)

#define CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_EXECUTION CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE(asc::execution)
#define CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_EXECUTION CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE(asc::execution)

#define CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_ARGUMENT CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE(asc::__argument)
#define CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_ARGUMENT CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE(asc::__argument)

// Namespace to avoid name collisions with CPOs on older compilers.
// ASC-STL only needs this workaround for MSVC's parser.
#if CANN_ASC_STL_DETAIL_COMPILER(MSVC)
#define CANN_ASC_STL_DETAIL_ACCL_BEGIN_HIDDEN_FRIEND_NAMESPACE namespace __hidden {
#define CANN_ASC_STL_DETAIL_ACCL_END_HIDDEN_FRIEND_NAMESPACE(_CLASS) \
    }                                                                \
    using __hidden::_CLASS;
#else
#define CANN_ASC_STL_DETAIL_ACCL_BEGIN_HIDDEN_FRIEND_NAMESPACE
#define CANN_ASC_STL_DETAIL_ACCL_END_HIDDEN_FRIEND_NAMESPACE(_CLASS)
#endif

// ASC-STL currently does not use architecture-dependent inline namespaces.
#define CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ARCH_DEPENDENT
#define CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ARCH_DEPENDENT

// Host standard library namespaces
#define CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_STD namespace std {
#define CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_STD }

#endif  // CANN_ASC_STL_STD_DETAIL_INTERNAL_NAMESPACES_H
