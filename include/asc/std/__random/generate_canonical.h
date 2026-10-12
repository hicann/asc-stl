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

#ifndef CANN_ASC_STL_ASC_STD___RANDOM_GENERATE_CANONICAL_H
#define CANN_ASC_STL_ASC_STD___RANDOM_GENERATE_CANONICAL_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__bit/integral.h>
#include <asc/std/__limits/numeric_limits.h>
#include <asc/std/__random/is_valid.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/cstdint>

CANN_ASC_STL_BEGIN_NAMESPACE

//! @brief 把 URNG 抽取值安全转换为 float。
//!
//! dav-c310 AI Core 标量 uint32→float 转换在位 31 置位时按 int32 符号
//! 扩展（编译期常量折叠不受影响，仅运行期值受影响）。这里把无符号
//! 32 位值拆成 24 位高段与 8 位低段两次安全转换后重组；该分解与直接
//! IEEE 转换逐位等价（2e6 样本含舍入边界暴力验证 0 差异），host 语义
//! 不变，设备路径得到正确结果。
template <class Draw>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr float __asc_random_draw_to_float(Draw draw) noexcept
{
    const uint32_t value = static_cast<uint32_t>(draw);
    return static_cast<float>(static_cast<float>(value >> 8)) * 256.0f + static_cast<float>(value & 0xFFu);
}

//! @brief 按目标实数类型分派抽取值转换：float 且无符号 32 位以内走
//! 安全分解，其余（host double、更宽引擎值）保持直接转换。
template <class RealType, class Draw>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr RealType __asc_random_draw_to_real(Draw draw) noexcept
{
    if constexpr (is_same_v<RealType, float> && __asc_random_is_valid_uinttype<Draw> && sizeof(Draw) <= 4) {
        return ::asc::std::__asc_random_draw_to_float(draw);
    } else {
        return static_cast<RealType>(draw);
    }
}

//! @brief 产品契约限定 generate_canonical 仅交付 float 结果（"float
//! result with delivered URBGs"，负向用例 double_excluded.fail 固化该
//! 边界）：主模板刻意不完整，RealType != float 时实例化即非良构。
template <class RealType>
struct __generate_canonical_result;

template <>
struct __generate_canonical_result<float> {
    using type = float;
};

//! @brief 由均匀随机数发生器生成 [0, 1) 内给定精度的 canonical 浮点值。
//!
//! 迭代次数由目标精度与引擎值域对数（__bit_log2，950 真机验证的位设施）
//! 共同决定；纯算术路径无平台依赖，host 与 AI-core 统一。
template <class RealType, size_t Bits, class UniformRandomBitGenerator>
CANN_ASC_STL_API constexpr typename __generate_canonical_result<RealType>::type generate_canonical(
    UniformRandomBitGenerator& generator) noexcept
{
    constexpr size_t digits =
        static_cast<size_t>(numeric_limits<RealType>::digits);  // NOLINT(build/include_what_you_use)
    const size_t requested = Bits < digits ? Bits : digits;
    const size_t log_range = static_cast<size_t>(
        ::asc::std::__bit_log2<uint64_t>(generator.max() - generator.min() + static_cast<uint64_t>(1)));
    const size_t draws = requested / log_range + (requested % log_range != 0) + (requested == 0);
    const RealType range = static_cast<RealType>(generator.max() - generator.min()) + RealType(1);
    RealType scale = range;
    RealType sum = ::asc::std::__asc_random_draw_to_real<RealType>(generator() - generator.min());
    for (size_t index = 1; index < draws; ++index, scale *= range) {
        sum += ::asc::std::__asc_random_draw_to_real<RealType>(generator() - generator.min()) * scale;
    }
    const RealType result = sum / scale;
    return result < RealType(1) ? result : RealType(1) - static_cast<RealType>(__FLT_EPSILON__) / RealType(2);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANDOM_GENERATE_CANONICAL_H
