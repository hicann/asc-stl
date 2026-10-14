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

#ifndef CANN_ASC_STL_ASC___VERSION_PRODUCT_H
#define CANN_ASC_STL_ASC___VERSION_PRODUCT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

// Product version and exact delivered-capability macros. A capability macro is
// defined only while its complete promised contract is locally delivered. The
// public <asc/version> facade exports exactly these product roots; the
// standard feature-test vocabulary (__cpp_lib_* macros) is delivered
// separately through <asc/std/version> and is intentionally NOT aggregated
// here.
#define CANN_ASC_STL_VERSION_MAJOR 1
#define CANN_ASC_STL_VERSION_MINOR 0
#define CANN_ASC_STL_VERSION_PATCH 0
// Single source of truth: derived from the components so a bump of
// MAJOR/MINOR/PATCH can never leave the packed integer stale.
#define CANN_ASC_STL_VERSION \
    (CANN_ASC_STL_VERSION_MAJOR * 10000 + CANN_ASC_STL_VERSION_MINOR * 100 + CANN_ASC_STL_VERSION_PATCH)

// The device policy and immutable execution-requirement vocabulary are
// delivered with their complete promised contract.
#define CANN_ASC_STL_HAS_DEVICE_POLICY 1

// The two-stage producer/consumer pipeline transfer with its exact
// borrowed coordinator surface is delivered.
#define CANN_ASC_STL_HAS_PIPELINE 1

// The D-SIMT block and D-SIMD UB-range collectives are delivered through
// the public <asc/collectives> facade.
#define CANN_ASC_STL_HAS_COLLECTIVES 1

#endif  // CANN_ASC_STL_ASC___VERSION_PRODUCT_H
