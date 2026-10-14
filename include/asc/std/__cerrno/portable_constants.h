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

#ifndef CANN_ASC_STL_ASC_STD___CERRNO_PORTABLE_CONSTANTS_H
#define CANN_ASC_STL_ASC_STD___CERRNO_PORTABLE_CONSTANTS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#include <cerrno>
#else
// Frozen product ABI on device: EDOM/EILSEQ/ERANGE are the fixed constants
// 33/84/34 (registered errno contract; note these are the glibc values --
// MSVC spells EILSEQ 42 and macOS 92). A toolchain that predefined one of
// them with a different value would silently steal the #ifndef guards and
// drift off the frozen ABI, so a conflicting predefinition is a hard error.
#if defined(EDOM) && EDOM != 33
#error "predefined EDOM conflicts with the frozen ASC-STL device ABI value 33"
#endif
#if defined(EILSEQ) && EILSEQ != 84
#error "predefined EILSEQ conflicts with the frozen ASC-STL device ABI value 84"
#endif
#if defined(ERANGE) && ERANGE != 34
#error "predefined ERANGE conflicts with the frozen ASC-STL device ABI value 34"
#endif
#ifndef EDOM
#define EDOM 33
#endif
#ifndef EILSEQ
#define EILSEQ 84
#endif
#ifndef ERANGE
#define ERANGE 34
#endif
#endif

#endif  // CANN_ASC_STL_ASC_STD___CERRNO_PORTABLE_CONSTANTS_H
