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

#ifndef CANN_ASC_STL_STD_DETAIL_ARCHITECTURE_H
#define CANN_ASC_STL_STD_DETAIL_ARCHITECTURE_H

#include <asc/std/__asc/compiler.h>
#include <asc/std/__asc/preprocessor.h>

// The header provides the following macros to determine the host architecture:
//
// CANN_ASC_STL_DETAIL_ARCH(ARM64)     ARM64
// CANN_ASC_STL_DETAIL_ARCH(X86_64)    X86 64 bit

// Determine the host architecture

// Arm 64-bit
#if (defined(__aarch64__) || defined(_M_ARM64) || defined(_M_ARM64EC) /*emulation*/)
#define CANN_ASC_STL_DETAIL_ARCH_ARM64_() 1
#else
#define CANN_ASC_STL_DETAIL_ARCH_ARM64_() 0
#endif

// X86 64-bit

// _M_X64 is defined even if we are compiling in Arm64 emulation mode
#if (defined(_M_X64) && !defined(_M_ARM64EC)) || defined(__amd64__) || defined(__x86_64__)
#define CANN_ASC_STL_DETAIL_ARCH_X86_64_() 1
#else
#define CANN_ASC_STL_DETAIL_ARCH_X86_64_() 0
#endif

#define CANN_ASC_STL_DETAIL_ARCH(...) CANN_ASC_STL_DETAIL_ARCH_##__VA_ARGS__##_()

// Determine the endianness

#define CANN_ASC_STL_DETAIL_ENDIAN_LITTLE() 0xDEAD
#define CANN_ASC_STL_DETAIL_ENDIAN_BIG() 0xFACE
#define CANN_ASC_STL_DETAIL_ENDIAN_PDP() 0xBEEF

#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() ||                                                                      \
    (CANN_ASC_STL_DETAIL_COMPILER(MSVC) && (CANN_ASC_STL_DETAIL_ARCH(X86_64) || CANN_ASC_STL_DETAIL_ARCH(ARM64))) || \
    __LITTLE_ENDIAN__
#define CANN_ASC_STL_DETAIL_ENDIAN_NATIVE() CANN_ASC_STL_DETAIL_ENDIAN_LITTLE()
#elif __BIG_ENDIAN__
#define CANN_ASC_STL_DETAIL_ENDIAN_NATIVE() CANN_ASC_STL_DETAIL_ENDIAN_BIG()
#elif defined(__BYTE_ORDER__)
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define CANN_ASC_STL_DETAIL_ENDIAN_NATIVE() CANN_ASC_STL_DETAIL_ENDIAN_LITTLE()
#elif __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__
#define CANN_ASC_STL_DETAIL_ENDIAN_NATIVE() CANN_ASC_STL_DETAIL_ENDIAN_PDP()
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define CANN_ASC_STL_DETAIL_ENDIAN_NATIVE() CANN_ASC_STL_DETAIL_ENDIAN_BIG()
#endif  // __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#elif __has_include(<endian.h>)
#include <endian.h>
#if __BYTE_ORDER == __LITTLE_ENDIAN
#define CANN_ASC_STL_DETAIL_ENDIAN_NATIVE() CANN_ASC_STL_DETAIL_ENDIAN_LITTLE()
#elif __BYTE_ORDER == __PDP_ENDIAN
#define CANN_ASC_STL_DETAIL_ENDIAN_NATIVE() CANN_ASC_STL_DETAIL_ENDIAN_PDP()
#elif __BYTE_ORDER == __BIG_ENDIAN
#define CANN_ASC_STL_DETAIL_ENDIAN_NATIVE() CANN_ASC_STL_DETAIL_ENDIAN_BIG()
#endif  // __BYTE_ORDER == __BIG_ENDIAN
#endif  // ^^^ has endian.h ^^^

#if !defined(CANN_ASC_STL_DETAIL_ENDIAN_NATIVE)
CANN_ASC_STL_DETAIL_WARNING("failed to determine the endianness of the host architecture, defaulting to little-endian")
#define CANN_ASC_STL_DETAIL_ENDIAN_NATIVE() CANN_ASC_STL_DETAIL_ENDIAN_LITTLE()
#endif  // !CANN_ASC_STL_DETAIL_ENDIAN_NATIVE

#define CANN_ASC_STL_DETAIL_ENDIAN(_NAME) (CANN_ASC_STL_DETAIL_ENDIAN_NATIVE() == CANN_ASC_STL_DETAIL_ENDIAN_##_NAME())

#endif  // CANN_ASC_STL_STD_DETAIL_ARCHITECTURE_H
