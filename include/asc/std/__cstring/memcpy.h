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

#ifndef CANN_ASC_STL_STD_DETAIL_CSTRING_MEMCPY_H
#define CANN_ASC_STL_STD_DETAIL_CSTRING_MEMCPY_H

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
// 同形内联，#ifndef 守卫以免与未来集中定义冲突。
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

namespace __memcpy_detail {

// 源/目的地址范围合法性（非空且地址不回绕）与区间重叠探测，供断言使用。
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

CANN_ASC_STL_API bool __are_ptrs_overlapping(const void* left, const void* right, size_t count) noexcept
{
    const uintptr_t lhs = reinterpret_cast<uintptr_t>(left);
    const uintptr_t rhs = reinterpret_cast<uintptr_t>(right);
    return lhs < rhs + count && rhs < lhs + count;
}

}  // namespace __memcpy_detail

// 旧编译器仍会触发与宿主 memcpy 的名字冲突（仅在宿主侧有 ::memcpy 可引）。
#if CANN_ASC_STL_DETAIL_HOSTED() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && defined(__GNUC__) && \
    !defined(__clang__) && __GNUC__ <= 9

using ::memcpy;

#else  // ^^^ GCC <= 9 宿主 ^^^ / vvv 其余编译器与设备 TU vvv

// 模板参数用于避免外部代码不带命名空间限定调用 memcpy 时的名字二义性：
// 函数模板在重载决议中优先级低于非模板函数。
template <int = 0>
CANN_ASC_STL_API void* memcpy(void* destination, const void* source, __SIZE_TYPE__ count) noexcept
{
    CANN_ASC_STL_DETAIL_ASSERT(
        __memcpy_detail::__is_valid_address_range(source, count), "memcpy: source range is invalid");
    CANN_ASC_STL_DETAIL_ASSERT(
        __memcpy_detail::__is_valid_address_range(destination, count), "memcpy: destination range is invalid");
    CANN_ASC_STL_DETAIL_ASSERT(
        !__memcpy_detail::__are_ptrs_overlapping(source, destination, count), "memcpy: source and destination overlap");
#if CANN_ASC_STL_DETAIL_HOSTED() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::memcpy(destination, source, count);
#else
    // 设备 TU：__builtin_memcpy 仅在长度为编译期常量时完全内联；运行期长度会
    // 降低为对外部 libc memcpy 的调用，而 aicore 链接没有 libc。常量长度走
    // 内建内联路径；运行期长度回退为字节循环（memcpy 的不重叠契约下等价）。
    if (__builtin_constant_p(count)) {
        return __builtin_memcpy(destination, source, count);
    }
    unsigned char* destination_bytes = static_cast<unsigned char*>(destination);
    const unsigned char* source_bytes = static_cast<const unsigned char*>(source);
    for (size_t index = 0; index < count; ++index) {
        destination_bytes[index] = source_bytes[index];
    }
    return destination;
#endif
}

#endif  // GCC <= 9 宿主

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_CSTRING_MEMCPY_H
