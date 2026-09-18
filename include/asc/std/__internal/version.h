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

#ifndef CANN_ASC_STL_STD_DETAIL_INTERNAL_VERSION_H
#define CANN_ASC_STL_STD_DETAIL_INTERNAL_VERSION_H

#include <asc/__accl_config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__asc/version.h>  // IWYU pragma: export

#define CANN_ASC_STL_DETAIL_ACCL_API_VERSION CANN_ASC_STL_ACCL_VERSION
#define CANN_ASC_STL_DETAIL_ACCL_API_VERSION_MAJOR CANN_ASC_STL_ACCL_MAJOR_VERSION
#define CANN_ASC_STL_DETAIL_ACCL_API_VERSION_MINOR CANN_ASC_STL_ACCL_MINOR_VERSION
#define CANN_ASC_STL_DETAIL_ACCL_API_VERSION_PATCH CANN_ASC_STL_ACCL_PATCH_VERSION

#if defined(ASC_IGNORE_DEPRECATED_ABI) && !defined(ASC_STL_IGNORE_DEPRECATED_ABI)
#define ASC_STL_IGNORE_DEPRECATED_ABI
#endif  // ASC_IGNORE_DEPRECATED_ABI

#ifndef CANN_ASC_STL_DETAIL_ACCL_ABI_VERSION_LATEST
#define CANN_ASC_STL_DETAIL_ACCL_ABI_VERSION_LATEST 4
#endif

#ifdef CANN_ASC_STL_DETAIL_ACCL_ABI_VERSION
#if CANN_ASC_STL_DETAIL_ACCL_ABI_VERSION != 4
#error Unsupported asc-stl ABI version requested. Only version 4 is allowed.
#endif
#else
#define CANN_ASC_STL_DETAIL_ACCL_ABI_VERSION CANN_ASC_STL_DETAIL_ACCL_ABI_VERSION_LATEST
#endif

#if (CANN_ASC_STL_DETAIL_ACCL_ABI_VERSION < 4) && !defined(ASC_STL_IGNORE_DEPRECATED_ABI)
#error "asc-stl ABIs older than version 4 are deprecated, define ASC_STL_IGNORE_DEPRECATED_ABI to ignore"
#endif

#ifdef CANN_ASC_STL_DETAIL_ACCL_PIPELINE_ASSUMED_ABI_VERSION
#if CANN_ASC_STL_DETAIL_ACCL_PIPELINE_ASSUMED_ABI_VERSION != CANN_ASC_STL_DETAIL_ACCL_ABI_VERSION
#error asc_pipeline.h assumed a different ABI version; include an asc-stl header before it, or upgrade.
#endif
#endif

#endif  // CANN_ASC_STL_STD_DETAIL_INTERNAL_VERSION_H
