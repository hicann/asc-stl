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

#ifndef CANN_ASC_STL_STD_DETAIL_ASC_TOOLKIT_H
#define CANN_ASC_STL_STD_DETAIL_ASC_TOOLKIT_H

#include <asc/std/__asc/compiler.h>
#include <asc/std/__asc/system_header.h>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

// CANN does not predefine a universal version macro, so actively consume its
// official public version headers when they are on the include path. Project-
// level overrides remain useful for deliberately minimal/freestanding builds.
//
// Supported version inputs (first match wins):
//   ASC_CANN_VERSION_MAJOR / ASC_CANN_VERSION_MINOR (project override)
//   ASCEND_CANN_VERSION_MAJOR / ASCEND_CANN_VERSION_MINOR (project override)
//   CANN_VERSION_MAJOR / CANN_VERSION_MINOR (project override)
//   ASC_DEVKIT_MAJOR / ASC_DEVKIT_MINOR (version/asc_devkit_version.h)
//   CANN_MAJOR / CANN_MINOR (version/cann_version.h)

#if __has_include(<version/asc_devkit_version.h>)
#include <version/asc_devkit_version.h>
#elif __has_include(<ascendc/asc_devkit_version.h>)
#include <ascendc/asc_devkit_version.h>
#elif __has_include(<asc_devkit_version.h>)
#include <asc_devkit_version.h>
#endif

#if __has_include(<version/cann_version.h>)
#include <version/cann_version.h>
#endif

#if defined(ASC_CANN_VERSION_MAJOR) && defined(ASC_CANN_VERSION_MINOR)
#define CANN_ASC_STL_DETAIL_CANN_VERSION() (ASC_CANN_VERSION_MAJOR, ASC_CANN_VERSION_MINOR)
#elif defined(ASCEND_CANN_VERSION_MAJOR) && defined(ASCEND_CANN_VERSION_MINOR)
#define CANN_ASC_STL_DETAIL_CANN_VERSION() (ASCEND_CANN_VERSION_MAJOR, ASCEND_CANN_VERSION_MINOR)
#elif defined(CANN_VERSION_MAJOR) && defined(CANN_VERSION_MINOR)
#define CANN_ASC_STL_DETAIL_CANN_VERSION() (CANN_VERSION_MAJOR, CANN_VERSION_MINOR)
#elif defined(ASC_DEVKIT_MAJOR) && defined(ASC_DEVKIT_MINOR)
#define CANN_ASC_STL_DETAIL_CANN_VERSION() (ASC_DEVKIT_MAJOR, ASC_DEVKIT_MINOR)
#elif defined(CANN_MAJOR) && defined(CANN_MINOR)
#define CANN_ASC_STL_DETAIL_CANN_VERSION() (CANN_MAJOR, CANN_MINOR)
#else
#define CANN_ASC_STL_DETAIL_CANN_VERSION() CANN_ASC_STL_DETAIL_VERSION_INVALID()
#endif

#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() || __has_include(<acl/acl.h>) || __has_include(<kernel_operator.h>) \
  || !CANN_ASC_STL_DETAIL_VERSION_IS_INVALID(CANN_ASC_STL_DETAIL_CANN_VERSION())
#define CANN_ASC_STL_DETAIL_HAS_CANN() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_CANN() 0
#endif

#define CANN_ASC_STL_DETAIL_CANN() CANN_ASC_STL_DETAIL_CANN_VERSION()
#define CANN_ASC_STL_DETAIL_CANN_MAKE_VERSION(_MAJOR, _MINOR) ((_MAJOR) * 100 + (_MINOR))
#define CANN_ASC_STL_DETAIL_CANN_BELOW(...) \
    CANN_ASC_STL_DETAIL_VERSION_COMPARE(CANN_ASC_STL_DETAIL_CANN_, CANN_ASC_STL_DETAIL_CANN, <, __VA_ARGS__)
#define CANN_ASC_STL_DETAIL_CANN_AT_LEAST(...) \
    CANN_ASC_STL_DETAIL_VERSION_COMPARE(CANN_ASC_STL_DETAIL_CANN_, CANN_ASC_STL_DETAIL_CANN, >=, __VA_ARGS__)

// Short aliases for code that treats the Ascend software stack as the ASC
// toolkit rather than naming CANN directly.
#define CANN_ASC_STL_DETAIL_HAS_TOOLKIT() CANN_ASC_STL_DETAIL_HAS_CANN()
#define CANN_ASC_STL_DETAIL_TOOLKIT() CANN_ASC_STL_DETAIL_CANN()
#define CANN_ASC_STL_DETAIL_TOOLKIT_BELOW(...) CANN_ASC_STL_DETAIL_CANN_BELOW(__VA_ARGS__)
#define CANN_ASC_STL_DETAIL_TOOLKIT_AT_LEAST(...) CANN_ASC_STL_DETAIL_CANN_AT_LEAST(__VA_ARGS__)

#endif  // CANN_ASC_STL_STD_DETAIL_ASC_TOOLKIT_H
