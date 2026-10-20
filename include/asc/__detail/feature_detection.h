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

#ifndef CANN_ASC_STL_DETAIL_FEATURE_DETECTION_H
#define CANN_ASC_STL_DETAIL_FEATURE_DETECTION_H

#if defined(_MSVC_LANG)
#define CANN_ASC_STL_DETAIL_CPLUSPLUS _MSVC_LANG
#else
#define CANN_ASC_STL_DETAIL_CPLUSPLUS __cplusplus
#endif

#define CANN_ASC_STL_DETAIL_HAS_CXX17() (CANN_ASC_STL_DETAIL_CPLUSPLUS >= 201703L)
#define CANN_ASC_STL_DETAIL_HAS_CXX20() (CANN_ASC_STL_DETAIL_CPLUSPLUS >= 202002L)
#define CANN_ASC_STL_DETAIL_HAS_CXX23() (CANN_ASC_STL_DETAIL_CPLUSPLUS >= 202302L)

// Numeric standard-version ladder, mirroring the __cplusplus checkpoints
// (199711L -> 2003, 201103L -> 2011, ..., 202302L -> 2023, newer -> 2024).
// Guarded so a surrounding build that already established a value for it is
// never redefined; numeric comparisons against CANN_ASC_STL_DETAIL_STD_VER
// are the preferred spelling for dialect ladders, keeping the boolean
// HAS_CXX*() gates for feature code.
#ifndef CANN_ASC_STL_DETAIL_STD_VER
#if CANN_ASC_STL_DETAIL_CPLUSPLUS <= 199711L
#define CANN_ASC_STL_DETAIL_STD_VER 2003
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 201103L
#define CANN_ASC_STL_DETAIL_STD_VER 2011
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 201402L
#define CANN_ASC_STL_DETAIL_STD_VER 2014
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 201703L
#define CANN_ASC_STL_DETAIL_STD_VER 2017
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 202002L
#define CANN_ASC_STL_DETAIL_STD_VER 2020
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 202302L
#define CANN_ASC_STL_DETAIL_STD_VER 2023
#else
#define CANN_ASC_STL_DETAIL_STD_VER 2024
#endif
#endif  // CANN_ASC_STL_DETAIL_STD_VER

#if CANN_ASC_STL_DETAIL_HAS_CXX20() && defined(__cpp_concepts) && __cpp_concepts >= 201907L
#define CANN_ASC_STL_DETAIL_HAS_CONCEPTS() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_CONCEPTS() 0
#endif

#if CANN_ASC_STL_DETAIL_HAS_CXX20() && defined(__cpp_char8_t) && __cpp_char8_t >= 201811L
#define CANN_ASC_STL_DETAIL_HAS_CHAR8_T() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_CHAR8_T() 0
#endif

#if CANN_ASC_STL_DETAIL_HAS_CXX20() && defined(__cpp_impl_three_way_comparison) && \
    __cpp_impl_three_way_comparison >= 201907L
#define CANN_ASC_STL_DETAIL_HAS_THREE_WAY_COMPARISON() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_THREE_WAY_COMPARISON() 0
#endif

#if CANN_ASC_STL_DETAIL_HAS_CXX20() && defined(__cpp_consteval) && __cpp_consteval >= 201811L
#define CANN_ASC_STL_DETAIL_HAS_CONSTEVAL() 1
#elif CANN_ASC_STL_DETAIL_HAS_CXX20() && defined(__BISHENG_CCEC__) && defined(__is_identifier)
// BiSheng CCE 15 enforces immediate-function semantics but omits the standard
// feature macro. Its keyword probe covers that verified compiler path without
// enabling consteval for ordinary Clang or inventing a standard feature macro.
#if !__is_identifier(consteval)
#define CANN_ASC_STL_DETAIL_HAS_CONSTEVAL() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_CONSTEVAL() 0
#endif
#else
#define CANN_ASC_STL_DETAIL_HAS_CONSTEVAL() 0
#endif

#if CANN_ASC_STL_DETAIL_CPLUSPLUS > 202002L && defined(__cpp_multidimensional_subscript) && \
    __cpp_multidimensional_subscript >= 202110L
#define CANN_ASC_STL_DETAIL_HAS_MULTIDIMENSIONAL_SUBSCRIPT() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_MULTIDIMENSIONAL_SUBSCRIPT() 0
#endif

#endif  // CANN_ASC_STL_DETAIL_FEATURE_DETECTION_H
