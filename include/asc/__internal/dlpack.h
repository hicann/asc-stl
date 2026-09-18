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

#ifndef CANN_ASC_STL_DETAIL_INTERNAL_DLPACK_H
#define CANN_ASC_STL_DETAIL_INTERNAL_DLPACK_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#if CANN_ASC_STL_DETAIL_ACCL_HAS_DLPACK()

#if __has_include(<dlpack/dlpack.h>)
#include <dlpack/dlpack.h>
#elif __has_include(<dlpack.h>)
#include <dlpack.h>
#endif

#define CANN_ASC_STL_DETAIL_ACCL_DLPACK_AT_LEAST(_MAJOR, _MINOR) \
    (DLPACK_MAJOR_VERSION > (_MAJOR) || (DLPACK_MAJOR_VERSION == (_MAJOR) && DLPACK_MINOR_VERSION >= (_MINOR)))
#define CANN_ASC_STL_DETAIL_ACCL_DLPACK_BELOW(_MAJOR, _MINOR) \
    (!CANN_ASC_STL_DETAIL_ACCL_DLPACK_AT_LEAST(_MAJOR, _MINOR))

#if DLPACK_MAJOR_VERSION != 1
#error "Unsupported DLPack version, only version 1 is currently supported"
#endif  // DLPACK_MAJOR_VERSION != 1

#endif  // CANN_ASC_STL_DETAIL_ACCL_HAS_DLPACK()

#endif  // CANN_ASC_STL_DETAIL_INTERNAL_DLPACK_H
