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

#ifndef CANN_ASC_STL_STD_DETAIL_OS_H
#define CANN_ASC_STL_STD_DETAIL_OS_H

// ---------------------------------------------------------------------------
// Host operating system detection
// ---------------------------------------------------------------------------
// This header provides macros to determine the host operating system:
//
// CANN_ASC_STL_DETAIL_OS(WINDOWS)
// CANN_ASC_STL_DETAIL_OS(LINUX)
// CANN_ASC_STL_DETAIL_OS(ANDROID)
// CANN_ASC_STL_DETAIL_OS(QNX)
// CANN_ASC_STL_DETAIL_OS(APPLE)

#if defined(_WIN32) || defined(_WIN64)
#define CANN_ASC_STL_DETAIL_OS_WINDOWS_() 1
#else
#define CANN_ASC_STL_DETAIL_OS_WINDOWS_() 0
#endif

#if defined(__linux__) || defined(__LP64__)
#define CANN_ASC_STL_DETAIL_OS_LINUX_() 1
#else
#define CANN_ASC_STL_DETAIL_OS_LINUX_() 0
#endif

#if defined(__ANDROID__)
#define CANN_ASC_STL_DETAIL_OS_ANDROID_() 1
#else
#define CANN_ASC_STL_DETAIL_OS_ANDROID_() 0
#endif

#if defined(__QNX__) || defined(__QNXNTO__)
#define CANN_ASC_STL_DETAIL_OS_QNX_() 1
#else
#define CANN_ASC_STL_DETAIL_OS_QNX_() 0
#endif

#if defined(__APPLE__) || defined(__APPLE_CC__)
#define CANN_ASC_STL_DETAIL_OS_APPLE_() 1
#else
#define CANN_ASC_STL_DETAIL_OS_APPLE_() 0
#endif

#define CANN_ASC_STL_DETAIL_OS(...) CANN_ASC_STL_DETAIL_OS_##__VA_ARGS__##_()

//! @def ASC_OS(os)
//!
//! @brief Detect the current operating system.
//!
//! @param os The name of the operating system to test.
//!
//! Available values for `os` include:
//!
//! - ``WINDOWS``: Windows, either in 32-bit or 64-bit mode.
//! - ``LINUX``: Any kind of Linux installation.
//! - ``ANDROID``: Android operating system.
//! - ``QNX``: QNX real-time operating system.
//! - ``APPLE``: macOS (Intel or Apple Silicon).
//!
//! @return 1 if the specified OS is being compiled for, 0 otherwise.
#define ASC_OS(__os__) CANN_ASC_STL_DETAIL_OS_##__os__##_()

#endif  // CANN_ASC_STL_STD_DETAIL_OS_H
