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

#ifndef CANN_ASC_STL_STD_DETAIL_INTERNAL_THREAD_API_H
#define CANN_ASC_STL_STD_DETAIL_INTERNAL_THREAD_API_H

#include <asc/__accl_config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

// Thread API selection.
// In ASC SIMT device mode (language projects built with --enable-simt) the
// toolchain provides the thread primitives declared by
// <simt_api/cooperative_groups.h>, and the SIMT backend takes priority.
// Host builds and mixed CCE device compilation have no device thread API:
// host uses the external/pthread/win32 backend selected below, and mixed
// device code gets declaration-only support.
#ifndef CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_SIMT
#if !defined(__APPLE__) && !defined(_WIN32) && __has_include(<simt_api/cooperative_groups.h>)
#define CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_SIMT
#endif  // __has_include(<simt_api/cooperative_groups.h>)
#endif  // CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_SIMT

#ifndef CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_EXTERNAL
#if (CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && !defined(CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_SIMT)) || \
    defined(__EMSCRIPTEN__)
#define CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_EXTERNAL
#endif
#endif  // CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_EXTERNAL

#ifndef CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_WIN32
#if CANN_ASC_STL_DETAIL_COMPILER(MSVC) && !defined(CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_EXTERNAL) && \
    !defined(CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_SIMT)
#define CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_WIN32
#endif  // CANN_ASC_STL_DETAIL_COMPILER(MSVC) && ...
#endif  // CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_WIN32

#if !defined(CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_PTHREAD) &&  \
    !defined(CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_WIN32) &&    \
    !defined(CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_EXTERNAL) && \
    !defined(CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_SIMT)
#if defined(__GNU__) || CANN_ASC_STL_DETAIL_OS(LINUX) || CANN_ASC_STL_DETAIL_OS(APPLE) || \
    CANN_ASC_STL_DETAIL_OS(QNX) || (defined(__MINGW32__) && __has_include(<pthread.h>))
#define CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_PTHREAD
#elif defined(_WIN32)
#define CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_WIN32
#else
#define CANN_ASC_STL_DETAIL_UNSUPPORTED_THREAD_API
#endif  // CANN_ASC_STL_DETAIL_HAS_THREAD_API
#endif

#ifndef __STDCPP_THREADS__
#define __STDCPP_THREADS__ 1
#endif  // __STDCPP_THREADS__

#endif  // CANN_ASC_STL_STD_DETAIL_INTERNAL_THREAD_API_H
