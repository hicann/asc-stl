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

#ifndef CANN_ASC_STL_STD_DETAIL_CSTRING_MEMSET_H
#define CANN_ASC_STL_STD_DETAIL_CSTRING_MEMSET_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__cstddef/types.h>
#include <asc/std/cstdint>

// 基座未提供断言宏（合入源树由方言层集中定义）：按 __mdspan/empty_base.h 的
// 同形内联，#ifndef 守卫以便与未来集中定义冲突时集中定义胜出。
#ifndef CANN_ASC_STL_DETAIL_ASSERT
// 设备侧无断言机制恒为 no-op；宿主侧仅在显式开启 ASC_ENABLE_HOST_ASSERTIONS 时检查。
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() || !defined(ASC_ENABLE_HOST_ASSERTIONS)
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) ((void)0)
#else
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) \
    ((expression) ? static_cast<void>(0) : (__builtin_trap(), static_cast<void>(0)))
#endif
#endif  // CANN_ASC_STL_DETAIL_ASSERT

#if CANN_ASC_STL_DETAIL_HOSTED() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#include <cstring>
#endif  // CANN_ASC_STL_DETAIL_HOSTED() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __memset_detail {

// 目的地址范围合法性（非空且地址不回绕）探测，供断言使用。
// 合入源树位于顶层 __memory/check_address.h，基座无该头，内联于此。
CANN_ASC_STL_API bool __is_valid_address_range(const void* pointer, size_t count) noexcept
{
    if (count == 0) {
        return false;
    }
    const uintptr_t limit = (~uintptr_t{0}) - static_cast<uintptr_t>(count);
    const uintptr_t address = reinterpret_cast<uintptr_t>(pointer);
    return pointer != nullptr && address <= limit;
}

}  // namespace __memset_detail

CANN_ASC_STL_API void* memset(void* destination, int value, __SIZE_TYPE__ count) noexcept
{
    CANN_ASC_STL_DETAIL_ASSERT(
        __memset_detail::__is_valid_address_range(destination, count), "memset: destination range is invalid");
#if CANN_ASC_STL_DETAIL_HOSTED() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::memset(destination, value, count);
#else
    // 设备 TU：__builtin_memset 仅在长度为编译期常量时完全内联；运行期长度会
    // 降低为对外部 libc memset 的调用，而 aicore 链接没有 libc。常量长度走
    // 内建内联路径；运行期长度回退为字节循环。
    if (__builtin_constant_p(count)) {
        return __builtin_memset(destination, value, count);
    }
    unsigned char* destination_bytes = static_cast<unsigned char*>(destination);
    for (size_t index = 0; index < count; ++index) {
        destination_bytes[index] = static_cast<unsigned char>(value);
    }
    return destination;
#endif
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_CSTRING_MEMSET_H
