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

#ifndef CANN_ASC_STL_STD_DETAIL_CSTDDEF_TYPES_H
#define CANN_ASC_STL_STD_DETAIL_CSTDDEF_TYPES_H

#include <asc/std/detail/__config>

#if CANN_ASC_STL_DETAIL_HOSTED()
#include <cstddef>
#else  // ^^^ CANN_ASC_STL_DETAIL_HOSTED() ^^^ / vvv CANN_ASC_STL_DETAIL_FREESTANDING() vvv
#if !defined(offsetof)
#if defined(__GNUC__) || defined(__clang__) || defined(__CCE__)
#define offsetof(type, member) __builtin_offsetof(type, member)
#else
#define offsetof(type, member) \
    ((__SIZE_TYPE__)((char*)&(((type*)0)->member) - (char*)0))  // NOLINT(readability/casting,runtime/casting)
#endif
#endif  // !offsetof
#endif  // CANN_ASC_STL_DETAIL_FREESTANDING()

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_FREESTANDING()
using max_align_t = long double;
using ptrdiff_t = __PTRDIFF_TYPE__;
using size_t = __SIZE_TYPE__;
#else   // ^^^ CANN_ASC_STL_DETAIL_FREESTANDING() ^^^ / vvv CANN_ASC_STL_DETAIL_HOSTED() vvv
// Re-use the compiler's <stddef.h> max_align_t where possible.
using ::max_align_t;
using ::ptrdiff_t;
using ::size_t;
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

using nullptr_t = decltype(nullptr);

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_CSTDDEF_TYPES_H
