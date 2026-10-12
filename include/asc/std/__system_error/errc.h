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

#ifndef CANN_ASC_STL_ASC_STD___SYSTEM_ERROR_ERRC_H
#define CANN_ASC_STL_ASC_STD___SYSTEM_ERROR_ERRC_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>

// 序言内联等价语义：基座 __config 未提供 hosted 门与 OS 探测宏（#ifndef 守卫，
// 参见 __string/constexpr_c_functions.h 的同形内联定义方式）。
#ifndef CANN_ASC_STL_DETAIL_HOSTED
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#define CANN_ASC_STL_DETAIL_HOSTED() 0
#else
#define CANN_ASC_STL_DETAIL_HOSTED() 1
#endif
#endif  // CANN_ASC_STL_DETAIL_HOSTED

#ifndef CANN_ASC_STL_DETAIL_OS_WINDOWS_
#if defined(_WIN32) || defined(_WIN64)
#define CANN_ASC_STL_DETAIL_OS_WINDOWS_() 1
#else
#define CANN_ASC_STL_DETAIL_OS_WINDOWS_() 0
#endif
#endif  // CANN_ASC_STL_DETAIL_OS_WINDOWS_

#ifndef CANN_ASC_STL_DETAIL_OS
#define CANN_ASC_STL_DETAIL_OS(...) CANN_ASC_STL_DETAIL_OS_##__VA_ARGS__##_()
#endif  // CANN_ASC_STL_DETAIL_OS

#if CANN_ASC_STL_DETAIL_HOSTED() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#include <system_error>
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

// 防重块与 __system_error/lightweight_error.h 共享同一守卫宏：
// 先到者定型 errc（hosted 下为 ::std::errc 别名，独立侧为三值 enum），
// 后到者整体跳过，保证任意包含顺序下均可编译。
#ifndef CANN_ASC_STL_DETAIL_ERRC_DEFINED
#define CANN_ASC_STL_DETAIL_ERRC_DEFINED
#if CANN_ASC_STL_DETAIL_HOSTED() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// Hosted 构建直接复用宿主 errc（全集枚举值，与 ::std 错误码互操作）。
using ::std::errc;
#else  // ^^^ hosted ^^^ / vvv freestanding vvv
// 独立/设备侧保留上游式三值 errc；value_too_large 按 OS 取 errno 语义值。
enum class errc {
    invalid_argument = 22,
    result_out_of_range = 34,
#if CANN_ASC_STL_DETAIL_OS(WINDOWS)
    value_too_large = 132,
#else
    value_too_large = 75,
#endif
};
#endif  // CANN_ASC_STL_DETAIL_HOSTED()
#endif  // CANN_ASC_STL_DETAIL_ERRC_DEFINED

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___SYSTEM_ERROR_ERRC_H
