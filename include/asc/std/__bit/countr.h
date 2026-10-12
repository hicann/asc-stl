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

#ifndef CANN_ASC_STL_ASC_STD___BIT_COUNTR_H
#define CANN_ASC_STL_ASC_STD___BIT_COUNTR_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__bit/bit_cast.h>
#include <asc/std/__bit/countl.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__cstddef/types.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_unsigned_integer.h>
#include <asc/std/cstdint>
#include <asc/std/limits>

// 基座 __config 未提供 dev 的 CANN_ASC_STL_DETAIL_ASSUME / PRAGMA_UNROLL_FULL
// （dev 定义于 asc/std/__asc/attributes.h、__asc/compiler.h）：内联其语义的
// 最小等价，#ifndef 守卫以免与未来基座定义冲突。
#ifndef CANN_ASC_STL_DETAIL_ASSUME
#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_assume)
#define CANN_ASC_STL_DETAIL_ASSUME(...) __builtin_assume(__VA_ARGS__)
#else
#define CANN_ASC_STL_DETAIL_ASSUME(...) ((void)sizeof(!(__VA_ARGS__)))
#endif
#endif  // CANN_ASC_STL_DETAIL_ASSUME
#ifndef CANN_ASC_STL_DETAIL_PRAGMA_UNROLL_FULL
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() || defined(__clang__)
#define CANN_ASC_STL_DETAIL_PRAGMA_UNROLL_FULL() _Pragma("unroll")
#elif defined(__GNUC__) && __GNUC__ >= 8
#define CANN_ASC_STL_DETAIL_PRAGMA_UNROLL_FULL() _Pragma("GCC unroll 65534")
#else
#define CANN_ASC_STL_DETAIL_PRAGMA_UNROLL_FULL()
#endif
#endif  // CANN_ASC_STL_DETAIL_PRAGMA_UNROLL_FULL

CANN_ASC_STL_BEGIN_NAMESPACE

//! @brief 尾随零计数的核心实现。
//!
//! 2026-09-01 实验结论：950 真机（CANN 9.2）上 __builtin_ctz/ctzll 可用且
//! 正确，但本地 CANN 9.0.0 的 dav 向量核后端把 ctz（尤其 64 位）lower 到
//! 浮点转换路径（fp_to_uint）而无法 select。为保证跨 CANN 版本一致，统一
//! 采用「取最低置位 + 前导零」恒等式：v != 0 时 v & (-v) == 2^k（k 为尾随
//! 零个数），故 countr = digits - 1 - countl_zero(v & -v)；所用原语
//! （取负、按位与、已迁移并双端验证的 countl_zero）在两侧后端均可靠。
template <typename _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr int __countr_zero_impl(_Tp __v) noexcept
{
    static_assert(is_same_v<_Tp, uint32_t> || is_same_v<_Tp, uint64_t>);
    if (__v == 0) {
        return static_cast<int>(numeric_limits<_Tp>::digits);
    }
    constexpr int __digits = numeric_limits<_Tp>::digits;
    const _Tp __lowest = __v & static_cast<_Tp>(-__v);
    return static_cast<int>(__digits - 1 - ::asc::std::countl_zero(__lowest));
}

//! @brief 计算 @p value 的二进制尾随零个数；@p value 为 0 时返回类型位宽。
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr __unsigned_integer_result_t<T, int> countr_zero(T value) noexcept
{
    int __count{};
    if constexpr (sizeof(T) <= sizeof(uint64_t)) {
        using _Sp = _If<(sizeof(T) <= sizeof(uint32_t)), uint32_t, uint64_t>;
        __count = (value != 0) ? ::asc::std::__countr_zero_impl(static_cast<_Sp>(value)) :
                                 static_cast<int>(numeric_limits<T>::digits);
    } else {
        // 超过 64 位的类型自低位块起扫描（尾随零语义）
        CANN_ASC_STL_DETAIL_PRAGMA_UNROLL_FULL()
        for (__SIZE_TYPE__ __index = 0; __index < sizeof(T) / sizeof(uint64_t); ++__index) {
            const auto __value64 = static_cast<uint64_t>(value);
            if (__value64 != 0) {
                __count += ::asc::std::countr_zero(__value64);
                break;
            }
            __count += numeric_limits<uint64_t>::digits;
            value >>= numeric_limits<uint64_t>::digits;
        }
    }
    CANN_ASC_STL_DETAIL_ASSUME(
        __count >= 0 && __count <= numeric_limits<T>::digits);  // NOLINT(build/include_what_you_use)
    return __count;
}

//! @brief 计算 @p value 的二进制尾随一个数（按取反后尾随零计数）。
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr __unsigned_integer_result_t<T, int> countr_one(T value) noexcept
{
    return ::asc::std::countr_zero(static_cast<T>(~value));
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___BIT_COUNTR_H
