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

#ifndef CANN_ASC_STL_STD_DETAIL_INTERNAL_CPP_DIALECT_H
#define CANN_ASC_STL_STD_DETAIL_INTERNAL_CPP_DIALECT_H

#include <asc/__accl_config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

// Define ASC_STL compiler deprecation macro:
#if CANN_ASC_STL_DETAIL_COMPILER(MSVC)
#define ASC_STL_COMP_DEPR_IMPL(msg) \
    CANN_ASC_STL_DETAIL_PRAGMA(message(__FILE__ ":" CANN_ASC_STL_DETAIL_TO_STRING(__LINE__) ": warning: " #msg))
#else  // ^^^ MSVC ^^^ / vvv !MSVC vvv
#define ASC_STL_COMP_DEPR_IMPL(msg) CANN_ASC_STL_DETAIL_PRAGMA(GCC warning #msg)
#endif  // !CANN_ASC_STL_DETAIL_COMPILER(MSVC)

// clang-format off
#define ASC_STL_DIALECT_DEPRECATION(REQ, CUR)                                                          \
  ASC_STL_COMP_DEPR_IMPL(                                                                              \
    asc-stl requires at least REQ. CUR is deprecated but still supported. CUR support will be removed in a \
      future release. Define ASC_STL_IGNORE_DEPRECATED_CPP_DIALECT to suppress this message.)
// clang-format on

#if defined(ASC_IGNORE_DEPRECATED_CPP_DIALECT) && !defined(ASC_STL_IGNORE_DEPRECATED_CPP_DIALECT)
#define ASC_STL_IGNORE_DEPRECATED_CPP_DIALECT
#endif  // ASC_IGNORE_DEPRECATED_CPP_DIALECT

#ifndef ASC_STL_IGNORE_DEPRECATED_CPP_DIALECT
#if CANN_ASC_STL_DETAIL_STD_VER < 2017
#error asc-stl requires at least C++ 17. Define ASC_STL_IGNORE_DEPRECATED_CPP_DIALECT to suppress this message.
#endif  // CANN_ASC_STL_DETAIL_STD_VER < 2017
#endif  // ASC_STL_IGNORE_DEPRECATED_CPP_DIALECT

#endif  // CANN_ASC_STL_STD_DETAIL_INTERNAL_CPP_DIALECT_H
