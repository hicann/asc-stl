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

#ifndef CANN_ASC_STL_STD_DETAIL_UNREACHABLE_H
#define CANN_ASC_STL_STD_DETAIL_UNREACHABLE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>

// 基座未提供下列宏（合入源树定义于 assert/unreachable 支撑头）：内联其语义的
// 最小等价，#ifndef 守卫以免与未来基座定义冲突。
#ifndef CANN_ASC_STL_DETAIL_ASSERT
// 设备侧无断言机制恒为 no-op；宿主侧仅在显式开启 ASC_ENABLE_HOST_ASSERTIONS 时检查。
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() || !defined(ASC_ENABLE_HOST_ASSERTIONS)
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) ((void)0)
#else
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) \
    ((expression) ? static_cast<void>(0) : (__builtin_trap(), static_cast<void>(0)))
#endif
#endif  // CANN_ASC_STL_DETAIL_ASSERT

#ifndef CANN_ASC_STL_DETAIL_UNREACHABLE
#define CANN_ASC_STL_DETAIL_UNREACHABLE() __builtin_unreachable()
#endif  // CANN_ASC_STL_DETAIL_UNREACHABLE

CANN_ASC_STL_BEGIN_NAMESPACE

CANN_ASC_STL_NORETURN CANN_ASC_STL_API void unreachable()
{
    CANN_ASC_STL_DETAIL_ASSERT(false, "unreachable");
    CANN_ASC_STL_DETAIL_UNREACHABLE();
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_UNREACHABLE_H
