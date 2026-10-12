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

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>

// 序言内联等价语义：基座 __config 未提供 hosted/freestanding 门（参见
// __string/constexpr_c_functions.h 的同形内联定义，#ifndef 守卫以便未来集中定义胜出）。
#ifndef CANN_ASC_STL_DETAIL_HOSTED
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#define CANN_ASC_STL_DETAIL_HOSTED() 0
#else
#define CANN_ASC_STL_DETAIL_HOSTED() 1
#endif
#endif  // CANN_ASC_STL_DETAIL_HOSTED

#ifndef CANN_ASC_STL_DETAIL_FREESTANDING
#define CANN_ASC_STL_DETAIL_FREESTANDING() !CANN_ASC_STL_DETAIL_HOSTED()
#endif  // CANN_ASC_STL_DETAIL_FREESTANDING

#if CANN_ASC_STL_DETAIL_HOSTED()
#include <stddef.h>
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

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_FREESTANDING()
// 独立/设备侧不引入 <stddef.h>：ptrdiff_t/size_t 用编译器预定义拼写；
// max_align_t 保持与全局同源（冻结合同断言 is_same_v<asc::std::max_align_t,
// ::max_align_t>，编译器自带 stddef.h 在设备侧同样可用）。
using ::max_align_t;
using ptrdiff_t = __PTRDIFF_TYPE__;
using size_t = __SIZE_TYPE__;
#else   // ^^^ CANN_ASC_STL_DETAIL_FREESTANDING() ^^^ / vvv CANN_ASC_STL_DETAIL_HOSTED() vvv
using ::max_align_t;
using ::ptrdiff_t;
using ::size_t;
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

using nullptr_t = decltype(nullptr);

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_CSTDDEF_TYPES_H
