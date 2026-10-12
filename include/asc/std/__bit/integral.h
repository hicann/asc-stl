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

#ifndef CANN_ASC_STL_ASC_STD___BIT_INTEGRAL_H
#define CANN_ASC_STL_ASC_STD___BIT_INTEGRAL_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/__detail/builtin.h>
#include <asc/std/__algorithm/max.h>
#include <asc/std/__bit/countl.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/is_unsigned_integer.h>
#include <asc/std/cstdint>
#include <asc/std/limits>

// 基座 __config 未提供 dev 的 CANN_ASC_STL_DETAIL_ASSUME / ASSERT（dev 定义
// 于 asc/std/__asc/attributes.h、__asc/assert.h）：内联其语义的最小等价，
// #ifndef 守卫以免与未来基座定义冲突。
#ifndef CANN_ASC_STL_DETAIL_ASSUME
#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_assume)
#define CANN_ASC_STL_DETAIL_ASSUME(...) __builtin_assume(__VA_ARGS__)
#else
#define CANN_ASC_STL_DETAIL_ASSUME(...) ((void)sizeof(!(__VA_ARGS__)))
#endif
#endif  // CANN_ASC_STL_DETAIL_ASSUME
#ifndef CANN_ASC_STL_DETAIL_ASSERT
// 设备侧无断言机制恒为 no-op；宿主侧仅在显式开启 ASC_ENABLE_HOST_ASSERTIONS
// 时检查（与 dev __asc/assert.h 的开关语义一致）。
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() || !defined(ASC_ENABLE_HOST_ASSERTIONS)
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) ((void)0)
#else
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) \
    ((expression) ? static_cast<void>(0) : (__builtin_trap(), static_cast<void>(0)))
#endif
#endif  // CANN_ASC_STL_DETAIL_ASSERT

CANN_ASC_STL_BEGIN_NAMESPACE

//! @brief 向下取整的 log2：最高置位的位置。
//!
//! 2026-08-31 晟腾 950 真机实验：源侧 PTX `bfind`/`shl` 快速路径无 ASC 对应
//! 内在指令，而 `countl_zero` 已在真机验证（builtin clz 统一三路），故
//! host/device/constexpr 统一为 `digits - 1 - countl_zero` 单一表达式；
//! @p __t 为 0 时结果为 -1（按无符号回绕参与上层运算，与源侧约定一致）。
template <class _Tp>
CANN_ASC_STL_API constexpr uint32_t __bit_log2(_Tp __t) noexcept
{
    return static_cast<uint32_t>(numeric_limits<_Tp>::digits - 1) - static_cast<uint32_t>(::asc::std::countl_zero(__t));
}

//! @brief 表示 @p value 所需的最小位数；@p value 为 0 时结果为 0。
//!
//! @p value 为 0 时 __bit_log2 回绕为 0xFFFFFFFF，加一得 0。
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr __unsigned_integer_result_t<T, int> bit_width(T value) noexcept
{
    auto __ret = ::asc::std::__bit_log2(value) + 1;
    CANN_ASC_STL_DETAIL_ASSUME(__ret <= numeric_limits<T>::digits);
    return static_cast<int>(__ret);
}

//! @brief 不小于 @p value 的最小 2 的幂。
//!
//! 950 真机实验：超宽移位（`1u << 32` 等）实测结果为 0（与源侧 PTX 语义
//! 一致），但 CCE 会给出 -Wshift-count-overflow 警告（C++ 标准为未定义
//! 行为）。因此不迁源侧 `max(1, shl)` 的移位技巧，统一用显式三目守卫，
//! 把 0/1 的结果落在常量分支上。
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr __unsigned_integer_result_t<T, T> bit_ceil(T value) noexcept
{
    using _Up = _If<(sizeof(T) <= 4), uint32_t, T>;
    CANN_ASC_STL_DETAIL_ASSERT(
        value <= numeric_limits<T>::max() / 2, "bit_ceil overflow");  // NOLINT(build/include_what_you_use)
    // value == 0 时 value - 1 全 1，bit_width 给出位宽，常量分支返回 1
    const auto __width = static_cast<uint32_t>(::asc::std::bit_width(static_cast<_Up>(value) - 1));
    const auto __ret = static_cast<T>(value <= 1 ? _Up{1} : _Up{1} << __width);
    CANN_ASC_STL_DETAIL_ASSUME(__ret >= value);
    return __ret;
}

//! @brief 不大于 @p value 的最大 2 的幂；@p value 为 0 时结果为 0。
//!
//! 同 bit_ceil：0 的情形落在常量分支，不依赖超宽移位语义。
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr __unsigned_integer_result_t<T, T> bit_floor(T value) noexcept
{
    using _Up = _If<(sizeof(T) <= 4), uint32_t, T>;
    const auto __log2 = ::asc::std::__bit_log2(static_cast<_Up>(value));
    const auto __ret = static_cast<T>(value == 0 ? _Up{0} : _Up{1} << __log2);
    CANN_ASC_STL_DETAIL_ASSUME(__ret >= value / 2 && __ret <= value);
    return __ret;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___BIT_INTEGRAL_H
