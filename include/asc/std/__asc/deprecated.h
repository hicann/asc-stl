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

#ifndef CANN_ASC_STL_STD_DETAIL_DEPRECATED_H
#define CANN_ASC_STL_STD_DETAIL_DEPRECATED_H

#include <asc/std/__asc/attributes.h>
#include <asc/std/__asc/compiler.h>
#include <asc/std/__asc/dialect.h>
#include <asc/std/__asc/system_header.h>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#if defined(ASC_IGNORE_DEPRECATED_CPP_DIALECT)
#if !defined(ASC_IGNORE_DEPRECATED_CPP_14)
#define ASC_IGNORE_DEPRECATED_CPP_14
#endif
#endif  // suppress all c++14 dialect deprecation warnings
#if defined(ASC_IGNORE_DEPRECATED_CPP_DIALECT) || defined(ASC_IGNORE_DEPRECATED_CPP_14)
#if !defined(ASC_IGNORE_DEPRECATED_CPP_11)
#define ASC_IGNORE_DEPRECATED_CPP_11
#endif
#endif  // suppress all c++11 dialect deprecation warnings
#if defined(ASC_IGNORE_DEPRECATED_COMPILER) || defined(ASC_IGNORE_DEPRECATED_CPP_DIALECT) || \
    defined(ASC_IGNORE_DEPRECATED_CPP_14) || defined(ASC_IGNORE_DEPRECATED_CPP_11)
#if !defined(ASC_IGNORE_DEPRECATED_COMPILER)
#define ASC_IGNORE_DEPRECATED_COMPILER
#endif
#endif  // suppress all compiler deprecation warnings

#if defined(ASC_IGNORE_DEPRECATED_API)
#define ASC_DEPRECATED
#define ASC_DEPRECATED_BECAUSE(MSG)
#elif CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE(deprecated)
#define ASC_DEPRECATED __attribute__((deprecated))
#define ASC_DEPRECATED_BECAUSE(MSG) __attribute__((deprecated(MSG)))
#else  // ^^^ attribute deprecated ^^^ / vvv standard deprecated attribute vvv
#define ASC_DEPRECATED [[deprecated]]
#define ASC_DEPRECATED_BECAUSE(MSG) [[deprecated(MSG)]]
#endif  // ^^^ standard deprecated attribute ^^^

#if CANN_ASC_STL_DETAIL_STD_VER >= 2020
#define CANN_ASC_STL_DETAIL_DEPRECATED_IN_CXX20 ASC_DEPRECATED
#else  // ^^^ CANN_ASC_STL_DETAIL_STD_VER >= 2020 ^^^ / vvv CANN_ASC_STL_DETAIL_STD_VER < 2020 vvv
#define CANN_ASC_STL_DETAIL_DEPRECATED_IN_CXX20
#endif  // ^^^ CANN_ASC_STL_DETAIL_STD_VER < 2020 ^^^

#if CANN_ASC_STL_DETAIL_STD_VER >= 2023
#define CANN_ASC_STL_DETAIL_DEPRECATED_IN_CXX23 ASC_DEPRECATED
#else  // ^^^ CANN_ASC_STL_DETAIL_STD_VER >= 2023 ^^^ / vvv CANN_ASC_STL_DETAIL_STD_VER < 2023 vvv
#define CANN_ASC_STL_DETAIL_DEPRECATED_IN_CXX23
#endif  // ^^^ CANN_ASC_STL_DETAIL_STD_VER < 2023 ^^^

#endif  // CANN_ASC_STL_STD_DETAIL_DEPRECATED_H
