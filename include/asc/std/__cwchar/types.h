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

#ifndef CANN_ASC_STL_STD_DETAIL_CWCHAR_TYPES_H
#define CANN_ASC_STL_STD_DETAIL_CWCHAR_TYPES_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

// The three wide-character roots share one delivery unit and therefore cannot
// carry edges among themselves: the shared vocabulary uses compiler-provided
// underlying types and idempotent macro guards so each root stays
// self-contained and the later public facade composes them without
// redefinition. The conversion state type is defined once by the
// fixed-C-locale root, the only root whose functions consume it.
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#include <cwchar>
#endif

#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#if !defined(NULL)
#define NULL nullptr
#endif
#if !defined(WCHAR_MAX)
#define WCHAR_MAX __WCHAR_MAX__
#endif
#if !defined(WCHAR_MIN)
#define WCHAR_MIN (-__WCHAR_MAX__ - 1)
#endif
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

using size_t = __SIZE_TYPE__;

#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
using wint_t = unsigned int;
#else
using wint_t = ::std::wint_t;
#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_CWCHAR_TYPES_H
