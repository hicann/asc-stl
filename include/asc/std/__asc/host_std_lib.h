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

#ifndef CANN_ASC_STL_STD_DETAIL_HOST_STD_LIB_H
#define CANN_ASC_STL_STD_DETAIL_HOST_STD_LIB_H

#include <asc/std/__asc/compiler.h>
#include <asc/std/__asc/preprocessor.h>
#include <asc/std/__asc/system_header.h>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

// The header provides the following macros to determine the host standard
// library and its version:
//
// CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBSTDCXX)          - is libstdc++ version valid?
// CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBCXX)             - is libc++ version valid?
// CANN_ASC_STL_DETAIL_HOST_STD_LIB(STL)                - is MSVC STL version valid?
// CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBSTDCXX, >=, 12)  - is libstdc++ major >= 12?
// CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBCXX, >=, 16, 0)  - is libc++ version >= 16.0?
// CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()               - is any host std lib available?

#define CANN_ASC_STL_DETAIL_HOST_STD_LIB_LIBSTDCXX() CANN_ASC_STL_DETAIL_VERSION_INVALID()
#define CANN_ASC_STL_DETAIL_HOST_STD_LIB_LIBCXX() CANN_ASC_STL_DETAIL_VERSION_INVALID()
#define CANN_ASC_STL_DETAIL_HOST_STD_LIB_STL() CANN_ASC_STL_DETAIL_VERSION_INVALID()

// include a minimal header
#if __has_include(<version>)
#include <version>
#elif __has_include(<ciso646>)
#include <ciso646>
#endif  // ^^^ __has_include(<ciso646>) ^^^

#define CANN_ASC_STL_DETAIL_HOST_STD_LIB_MAKE_VERSION(_MAJOR, _MINOR) ((_MAJOR) * 100 + (_MINOR))
#define CANN_ASC_STL_DETAIL_HOST_STD_LIB(...) \
    CANN_ASC_STL_DETAIL_VERSION_COMPARE(      \
        CANN_ASC_STL_DETAIL_HOST_STD_LIB_, CANN_ASC_STL_DETAIL_HOST_STD_LIB_##__VA_ARGS__)

#if CANN_ASC_STL_DETAIL_HOSTED()
#if defined(_MSVC_STL_VERSION)
#undef CANN_ASC_STL_DETAIL_HOST_STD_LIB_STL
#define CANN_ASC_STL_DETAIL_HOST_STD_LIB_STL() (_MSVC_STL_VERSION, 0)
#elif defined(__GLIBCXX__)
#undef CANN_ASC_STL_DETAIL_HOST_STD_LIB_LIBSTDCXX
#define CANN_ASC_STL_DETAIL_HOST_STD_LIB_LIBSTDCXX() (_GLIBCXX_RELEASE, 0)
#elif defined(_LIBCPP_VERSION)
#undef CANN_ASC_STL_DETAIL_HOST_STD_LIB_LIBCXX
// since llvm-16, the version scheme has been changed from MMppp to MMmmpp
#if _LIBCPP_VERSION / 10000 < 2
#define CANN_ASC_STL_DETAIL_HOST_STD_LIB_LIBCXX() (_LIBCPP_VERSION / 1000, 0)
#else
#define CANN_ASC_STL_DETAIL_HOST_STD_LIB_LIBCXX() (_LIBCPP_VERSION / 10000, (_LIBCPP_VERSION / 100) % 100)
#endif
#endif  // ^^^ _LIBCPP_VERSION ^^^
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

#define CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()                                                  \
    (CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBSTDCXX) || CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBCXX) || \
        CANN_ASC_STL_DETAIL_HOST_STD_LIB(STL))

#endif  // CANN_ASC_STL_STD_DETAIL_HOST_STD_LIB_H
