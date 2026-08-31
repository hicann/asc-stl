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

#ifndef CANN_ASC_STL_STD_DETAIL_DIALECT_H
#define CANN_ASC_STL_STD_DETAIL_DIALECT_H

#include <asc/std/__asc/compiler.h>
#include <asc/std/__asc/system_header.h>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__asc/builtin.h>
#include <asc/std/__asc/execution_space.h>
#include <asc/std/__asc/host_std_lib.h>

///////////////////////////////////////////////////////////////////////////////
// Determine the C++ standard dialect
///////////////////////////////////////////////////////////////////////////////
// CANN_ASC_STL_DETAIL_STD_CPLUSPLUS and CANN_ASC_STL_DETAIL_STD_HAS_CXX17/20/23 are defined in
// asc/std/__config. CANN_ASC_STL_DETAIL_STD_VER provides a simplified numeric version
// comparable to the upstream standard-version macro for convenience.

#if CANN_ASC_STL_DETAIL_STD_CPLUSPLUS <= 199711L
#define CANN_ASC_STL_DETAIL_STD_VER 2003
#elif CANN_ASC_STL_DETAIL_STD_CPLUSPLUS <= 201103L
#define CANN_ASC_STL_DETAIL_STD_VER 2011
#elif CANN_ASC_STL_DETAIL_STD_CPLUSPLUS <= 201402L
#define CANN_ASC_STL_DETAIL_STD_VER 2014
#elif CANN_ASC_STL_DETAIL_STD_CPLUSPLUS <= 201703L
#define CANN_ASC_STL_DETAIL_STD_VER 2017
#elif CANN_ASC_STL_DETAIL_STD_CPLUSPLUS <= 202002L
#define CANN_ASC_STL_DETAIL_STD_VER 2020
#elif CANN_ASC_STL_DETAIL_STD_CPLUSPLUS <= 202302L
#define CANN_ASC_STL_DETAIL_STD_VER 2023
#else
#define CANN_ASC_STL_DETAIL_STD_VER 2024
#endif

///////////////////////////////////////////////////////////////////////////////
// Conditionally enable constexpr per standard dialect
///////////////////////////////////////////////////////////////////////////////

#if CANN_ASC_STL_DETAIL_STD_VER >= 2020
#define CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 constexpr
#else
#define CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20
#endif

#if CANN_ASC_STL_DETAIL_STD_VER >= 2023
#define CANN_ASC_STL_DETAIL_CONSTEXPR_CXX23 constexpr
#else
#define CANN_ASC_STL_DETAIL_CONSTEXPR_CXX23
#endif

///////////////////////////////////////////////////////////////////////////////
// Detect whether we can use some language features based on standard dialect
///////////////////////////////////////////////////////////////////////////////

// concepts are only available from C++20 onwards
#if CANN_ASC_STL_DETAIL_STD_VER <= 2017 || !defined(__cpp_concepts) || __cpp_concepts < 201907L
#define CANN_ASC_STL_DETAIL_HAS_CONCEPTS() 0
#else
#define CANN_ASC_STL_DETAIL_HAS_CONCEPTS() 1
#endif

// Three way comparison is only available from C++20 onwards
#if CANN_ASC_STL_DETAIL_STD_VER <= 2017 || !defined(__cpp_impl_three_way_comparison) || \
    __cpp_impl_three_way_comparison < 201907L
#define CANN_ASC_STL_DETAIL_NO_THREE_WAY_COMPARISON
#endif

// Pack indexing (C++26 feature, with some compiler backports)
#if defined(__cpp_pack_indexing) && __cpp_pack_indexing >= 202311L
#define CANN_ASC_STL_DETAIL_HAS_PACK_INDEXING() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_PACK_INDEXING() 0
#endif

#if CANN_ASC_STL_DETAIL_STD_VER <= 2017 || !defined(__cpp_consteval) || __cpp_consteval < 201811L
#define CANN_ASC_STL_DETAIL_NO_CONSTEVAL
#define CANN_ASC_STL_DETAIL_CONSTEVAL constexpr
#else
#define CANN_ASC_STL_DETAIL_CONSTEVAL consteval
#endif

///////////////////////////////////////////////////////////////////////////////
// Conditionally use certain language features depending on availability
///////////////////////////////////////////////////////////////////////////////

// We need to treat host and device separately
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#define CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT CANN_ASC_STL_DETAIL_GLOBAL_VARIABLE constexpr
#else
#define CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT inline constexpr
#endif

#if CANN_ASC_STL_DETAIL_STD_VER >= 2020 && defined(__cpp_constinit) && __cpp_constinit >= 201907L
#define CANN_ASC_STL_DETAIL_CONSTINIT constinit
#else
#define CANN_ASC_STL_DETAIL_CONSTINIT
#endif

// Multi-dimensional subscript operator
#if defined(__cpp_multidimensional_subscript) && __cpp_multidimensional_subscript >= 202110L
#define CANN_ASC_STL_DETAIL_HAS_MULTIARG_OPERATOR_BRACKETS() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_MULTIARG_OPERATOR_BRACKETS() 0
#endif

// Static subscript operator (backported by some compilers)
#if (defined(__cpp_multidimensional_subscript) && __cpp_multidimensional_subscript >= 202211L) || \
    CANN_ASC_STL_DETAIL_COMPILER(CLANG, >=, 16) || CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 13)
#define CANN_ASC_STL_DETAIL_HAS_STATIC_SUBSCRIPT_OPERATOR() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_STATIC_SUBSCRIPT_OPERATOR() 0
#endif

// Static call operator (backported by some compilers)
#if (defined(__cpp_static_call_operator) && __cpp_static_call_operator >= 202207L) || \
    CANN_ASC_STL_DETAIL_COMPILER(CLANG, >=, 16) || CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 13)
#define CANN_ASC_STL_DETAIL_HAS_STATIC_CALL_OPERATOR() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_STATIC_CALL_OPERATOR() 0
#endif

// if consteval support in C++20 mode
#if CANN_ASC_STL_DETAIL_STD_VER == 2020 && \
    (CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 12) || CANN_ASC_STL_DETAIL_COMPILER(CLANG))
#define CANN_ASC_STL_DETAIL_HAS_IF_CONSTEVAL_IN_CXX20() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_IF_CONSTEVAL_IN_CXX20() 0
#endif

#if (defined(__cpp_if_consteval) && __cpp_if_consteval >= 202106L) || CANN_ASC_STL_DETAIL_HAS_IF_CONSTEVAL_IN_CXX20()
#define CANN_ASC_STL_DETAIL_IF_CONSTEVAL if consteval
#define CANN_ASC_STL_DETAIL_IF_CONSTEVAL_DEFAULT CANN_ASC_STL_DETAIL_IF_CONSTEVAL
#define CANN_ASC_STL_DETAIL_IF_NOT_CONSTEVAL if !consteval
#define CANN_ASC_STL_DETAIL_IF_NOT_CONSTEVAL_DEFAULT CANN_ASC_STL_DETAIL_IF_NOT_CONSTEVAL
#elif defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTANT_EVALUATED)
#if CANN_ASC_STL_DETAIL_HOST_COMPILATION() && CANN_ASC_STL_DETAIL_COMPILER(GCC)
#define CANN_ASC_STL_DETAIL_BEGIN_IF_CONSTEVAL_SUPPRESS() \
    CANN_ASC_STL_DETAIL_DIAG_PUSH CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_GCC("-Wtautological-compare")
#define CANN_ASC_STL_DETAIL_END_IF_CONSTEVAL_SUPPRESS() CANN_ASC_STL_DETAIL_DIAG_POP
#else
#define CANN_ASC_STL_DETAIL_BEGIN_IF_CONSTEVAL_SUPPRESS()
#define CANN_ASC_STL_DETAIL_END_IF_CONSTEVAL_SUPPRESS()
#endif

#define CANN_ASC_STL_DETAIL_IF_CONSTEVAL                     \
    CANN_ASC_STL_DETAIL_BEGIN_IF_CONSTEVAL_SUPPRESS()        \
    if (CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTANT_EVALUATED()) \
    CANN_ASC_STL_DETAIL_END_IF_CONSTEVAL_SUPPRESS()
#define CANN_ASC_STL_DETAIL_IF_CONSTEVAL_DEFAULT CANN_ASC_STL_DETAIL_IF_CONSTEVAL
#define CANN_ASC_STL_DETAIL_IF_NOT_CONSTEVAL                  \
    CANN_ASC_STL_DETAIL_BEGIN_IF_CONSTEVAL_SUPPRESS()         \
    if (!CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTANT_EVALUATED()) \
    CANN_ASC_STL_DETAIL_END_IF_CONSTEVAL_SUPPRESS()
#define CANN_ASC_STL_DETAIL_IF_NOT_CONSTEVAL_DEFAULT CANN_ASC_STL_DETAIL_IF_NOT_CONSTEVAL
#else
#define CANN_ASC_STL_DETAIL_IF_CONSTEVAL if constexpr (false)
#define CANN_ASC_STL_DETAIL_IF_CONSTEVAL_DEFAULT if constexpr (true)
#define CANN_ASC_STL_DETAIL_IF_NOT_CONSTEVAL if constexpr (true)
#define CANN_ASC_STL_DETAIL_IF_NOT_CONSTEVAL_DEFAULT if constexpr (false)
#endif

#if CANN_ASC_STL_DETAIL_STD_VER >= 2020 && defined(__cpp_char8_t) && __cpp_char8_t >= 201811L
#define CANN_ASC_STL_DETAIL_HAS_CHAR8_T() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_CHAR8_T() 0
#endif

// We currently do not support any of the STL wchar facilities
#define CANN_ASC_STL_DETAIL_HAS_WCHAR_T() 0

// Long double: not available in ASC device compilation (AI Core)
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && !defined(ASC_DISABLE_LONG_DOUBLE_SUPPORT)
#define CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE() 0
#endif

// Structured bindings with pack (C++26 feature, with compiler backports)
#if (defined(__cpp_structured_bindings) && __cpp_structured_bindings >= 202411L) || \
    CANN_ASC_STL_DETAIL_COMPILER(CLANG, >=, 21) || CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 16)
#define CANN_ASC_STL_DETAIL_HAS_STRUCTURED_BINDINGS_PACK() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_STRUCTURED_BINDINGS_PACK() 0
#endif

#endif  // CANN_ASC_STL_STD_DETAIL_DIALECT_H
