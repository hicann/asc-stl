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

#ifndef CANN_ASC_STL_ASC_STD___FLOATING_POINT_CAST_H
#define CANN_ASC_STL_ASC_STD___FLOATING_POINT_CAST_H

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
#include <asc/std/__floating_point/storage.h>
#include <asc/std/__type_traits/always_false.h>
#include <asc/std/__type_traits/is_extended_floating_point.h>
#include <asc/std/__type_traits/is_same.h>

// 浮点格式互转 __fp_cast（单一 constexpr 模板）：
// - float/double/long double 之间：static_cast（舍入到最近偶数）；
// - 同格式（含 __asc_fp 包装与 CCE 原生标量互转）：存储位直传；
// - half/bfloat16_t（CCE 设备内建标量）：经 static_cast；
// - fp8（e4m3/e5m2/e8m0）：软件位级编解码（__detail::__fp8_encode/__fp8_decode），
//   host/device 同码、constexpr、位级精确：解码为纯位展开；编码为 RN-even
//   （e4m3/e5m2 NOSAT 语义：e4m3 溢出→NaN、e5m2 溢出→Inf；e8m0 按截断编码）。
//   double/long double 源先经 float 再编码（fp8 有效位不大于 4，双重舍入
//   风险仅在理论边界，记录于批注）；
// - fp6/fp4：无标量类型（仅打包拼写），实例化得到明确的 Unsupported 静态断言。

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __detail {

// fp8 位模式 → float（精确位展开；constexpr，host/device 同码）。
// ebits/mbits 为目标格式位宽；fn_no_inf 为 e4m3 的无 Inf 变体（exp 全 1 且
// 尾数最大 → NaN，否则为 448 尺度的最大有限值）。
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr float __fp8_decode(
    unsigned char bits, int ebits, int mbits, bool fn_no_inf) noexcept
{
    const unsigned int sign = (static_cast<unsigned int>(bits) >> (ebits + mbits)) & 1u;
    const unsigned int expf = (static_cast<unsigned int>(bits) >> mbits) & ((1u << ebits) - 1u);
    const unsigned int mant = static_cast<unsigned int>(bits) & ((1u << mbits) - 1u);
    const int bias = (1 << (ebits - 1)) - 1;

    unsigned int out = sign << 31;
    if (expf == 0) {
        if (mant == 0) {
            return ::asc::std::bit_cast<float>(out);  // ±0
        }
        // 子正规：值 = m * 2^(1-bias-mbits)。把 m 归一到最高有效位 s，再按
        // 1.f 形式组装（float 指数 = -s-bias+127，尾数对齐 23 位）。
        int s = 0;
        unsigned int m = mant;
        while ((m & (1u << (mbits - 1))) == 0) {
            m <<= 1;
            ++s;  // 每左移一次，最高有效位下标减一
        }
        const int float_exponent = static_cast<int>(mbits) - 1 - s + 1 - bias - mbits + 127;
        if (float_exponent <= 0) {
            return ::asc::std::bit_cast<float>(out);  // 深度下溢按 0
        }
        const unsigned int float_mantissa = (m & ((1u << (mbits - 1)) - 1u)) << (23 - (mbits - 1));
        return ::asc::std::bit_cast<float>(out | (static_cast<unsigned int>(float_exponent) << 23) | float_mantissa);
    }
    if (expf == (1u << ebits) - 1u) {
        if (fn_no_inf) {
            // e4m3 变体：无 Inf；尾数最大为 NaN，其余为最大有限值
            if (mant == (1u << mbits) - 1u) {
                return ::asc::std::bit_cast<float>(out | 0x7fc00000u);  // NaN
            }
            // e4m3 变体最大有限 binade：E 字段全 1 的正规尺度 2^8
            const int float_exponent = (1 << ebits) - 1 - bias + 127;
            return ::asc::std::bit_cast<float>(
                out | (static_cast<unsigned int>(float_exponent) << 23) | (mant << (23 - mbits)));
        }
        if (mant == 0) {
            return ::asc::std::bit_cast<float>(out | 0x7f800000u);  // ±Inf
        }
        return ::asc::std::bit_cast<float>(out | 0x7fc00000u);  // NaN
    }
    const int float_exponent = static_cast<int>(expf) - bias + 127;
    return ::asc::std::bit_cast<float>(
        out | (static_cast<unsigned int>(float_exponent) << 23) | (mant << (23 - mbits)));
}

// float → fp8 位模式（RN-even；NOSAT 语义）。constexpr。
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr unsigned char __fp8_encode(
    float value, int ebits, int mbits, bool fn_no_inf) noexcept
{
    const unsigned int float_bits = ::asc::std::bit_cast<unsigned int>(value);
    const unsigned int sign = (float_bits >> 31) & 1u;
    const unsigned int float_abs = float_bits & 0x7fffffffu;
    const int bias = (1 << (ebits - 1)) - 1;

    if (float_abs > 0x7f800000u) {
        // NaN：静默化（尾数置非零最小）
        return static_cast<unsigned char>((sign << (ebits + mbits)) | (((1u << ebits) - 1u) << mbits) | 1u);
    }
    if (float_abs == 0x7f800000u) {
        // Inf：e4m3 变体无 Inf → NaN；其余格式保留 Inf
        if (fn_no_inf) {
            return static_cast<unsigned char>((sign << (ebits + mbits)) | (((1u << ebits) - 1u) << mbits) | 1u);
        }
        return static_cast<unsigned char>((sign << (ebits + mbits)) | (((1u << ebits) - 1u) << mbits));
    }
    if (float_abs == 0u) {
        return static_cast<unsigned char>(sign << (ebits + mbits));
    }

    const int float_exp = static_cast<int>((float_abs >> 23) & 0xffu);
    const unsigned int float_mant = float_abs & 0x7fffffu;
    int etarget = float_exp - 127 + bias;  // 目标指数（未含尾数进位）

    // 溢出上界：e4m3 变体 E=15 与 M<=6 仍是最大有限 binade（448 尺度），
    // 仅 M==7 为 NaN；其余格式 E 全 1 为 Inf/NaN 保留。
    const int emax_field = (1 << ebits) - 1 - (fn_no_inf ? 0 : 1);
    if (etarget > emax_field) {
        if (fn_no_inf) {
            return static_cast<unsigned char>((sign << (ebits + mbits)) | (((1u << ebits) - 1u) << mbits) | 1u);
        }
        return static_cast<unsigned char>((sign << (ebits + mbits)) | (((1u << ebits) - 1u) << mbits));
    }

    if (etarget >= 1) {
        // 正规范围：有效数字（含隐含 1）RN-even 到 mbits+1 位，隐含位归
        // exponent，尾数字段 = 低 mbits 位
        const unsigned int full = (float_mant | 0x800000u) >> (23 - mbits);  // 含隐含 1 的截断
        const unsigned int rest = float_mant & ((1u << (23 - mbits)) - 1u);
        const unsigned int half = 1u << (23 - mbits - 1);
        unsigned int rounded = full;
        if (rest > half || (rest == half && (full & 1u))) {
            ++rounded;  // 进位可能推到 mbits+2 位 → 指数 +1
        }
        if (rounded >= (1u << (mbits + 1))) {
            rounded = 1u << mbits;  // 舍入进位越过最高位：隐含位右移
            ++etarget;
            if (etarget > emax_field) {
                if (fn_no_inf) {
                    return static_cast<unsigned char>((sign << (ebits + mbits)) | (((1u << ebits) - 1u) << mbits) | 1u);
                }
                return static_cast<unsigned char>((sign << (ebits + mbits)) | (((1u << ebits) - 1u) << mbits));
            }
        }
        // e4m3 变体 E=15 且 M==7 → NaN（大于 448 或经舍入落满）
        if (fn_no_inf && etarget == (1 << ebits) - 1 && rounded == (1u << mbits) - 1u) {
            return static_cast<unsigned char>((sign << (ebits + mbits)) | (((1u << ebits) - 1u) << mbits) | 1u);
        }
        return static_cast<unsigned char>((sign << (ebits + mbits)) | (static_cast<unsigned int>(etarget) << mbits) |
            (rounded & ((1u << mbits) - 1u)));
    }

    // 子正规/下溢区：指数字段 0，隐含位 0。目标步长 = 2^(1-bias-mbits)，
    // |v| 折算步数 = (0x800000|mant) 对 2^(23-e_eff+1-bias-mbits) 的商。
    const int e_eff = float_exp - 127;                    // 真实指数（< 1-bias）
    const int shift_div = 23 - e_eff + 1 - bias - mbits;  // 除数移位（>0：右移）
    if (shift_div >= 24) {
        return static_cast<unsigned char>(sign << (ebits + mbits));  // 深度下溢 → ±0
    }
    const unsigned int significand = 0x800000u | float_mant;
    unsigned int steps = significand >> shift_div;
    unsigned int rest_masked = 0u;
    unsigned int half_ulp = 0u;
    if (shift_div > 0) {
        rest_masked = significand & ((1u << shift_div) - 1u);
        half_ulp = 1u << (shift_div - 1);
    }
    if (rest_masked > half_ulp || (rest_masked == half_ulp && (steps & 1u))) {
        ++steps;  // RN-even
    }
    if (steps >= (1u << mbits)) {
        // 步数进位恰好落入最小正规
        return static_cast<unsigned char>((sign << (ebits + mbits)) | (1u << mbits));
    }
    return static_cast<unsigned char>((sign << (ebits + mbits)) | steps);
}

// e8m0 编码（纯指数格式，截断语义）：值 → 2^(floor(log2|v|))。
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr unsigned char __e8m0_encode(float value) noexcept
{
    const unsigned int float_bits = ::asc::std::bit_cast<unsigned int>(value);
    const unsigned int float_abs = float_bits & 0x7fffffffu;
    if (float_abs >= 0x7f800000u) {
        return 0xffu;  // NaN/Inf → NaN 模式
    }
    if (float_abs == 0u) {
        return 0x00u;  // 0 → 0
    }
    const int float_exp = static_cast<int>((float_abs >> 23) & 0xffu) - 127;
    // 截断：|v| ∈ [2^e, 2^(e+1))，正负号不影响量级区间，指数即 e。
    const int field = float_exp + 127;
    if (field <= 0) {
        return 0x00u;  // 深度下溢按 0
    }
    if (field >= 255) {
        return 0xffu;  // NaN 模式（e8m0 无 Inf 编码）
    }
    return static_cast<unsigned char>(field);
}

}  // namespace __detail

template <class To, class From>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr To __fp_cast(From value) noexcept
{
    if constexpr (is_same_v<To, From>) {
        return value;
    } else if constexpr (__is_std_fp_v<To> && __is_std_fp_v<From>) {
        return static_cast<To>(value);
    } else if constexpr (__is_fp_v<To> && __is_fp_v<From> && __fp_format_of_v<To> == __fp_format_of_v<From>) {
        // 同格式位直传（__asc_fp 包装与 CCE 原生标量互转）
        return __fp_from_storage<To>(__fp_get_storage(value));
    }
#if CANN_ASC_STL_DETAIL_HAS_FP8_E4M3()
    else if constexpr (__fp_format_of_v<From> == __fp_format::__fp8_e4m3) {
        return ::asc::std::__fp_cast<To>(::asc::std::__detail::__fp8_decode(__fp_get_storage(value), 4, 3, true));
    }
#endif  // CANN_ASC_STL_DETAIL_HAS_FP8_E4M3()
#if CANN_ASC_STL_DETAIL_HAS_FP8_E5M2()
    else if constexpr (__fp_format_of_v<From> == __fp_format::__fp8_e5m2) {
        return ::asc::std::__fp_cast<To>(::asc::std::__detail::__fp8_decode(__fp_get_storage(value), 5, 2, false));
    }
#endif  // CANN_ASC_STL_DETAIL_HAS_FP8_E5M2()
#if CANN_ASC_STL_DETAIL_HAS_FP8_E8M0()
    else if constexpr (__fp_format_of_v<From> == __fp_format::__fp8_e8m0) {
        // e8m0 无符号位：0x00 → 0，0xff → NaN，其余值 = 2^(field-127)
        const unsigned char field = __fp_get_storage(value);
        if (field == 0x00u) {
            return ::asc::std::__fp_cast<To>(0.0f);
        }
        if (field == 0xffu) {
            return ::asc::std::__fp_cast<To>(__builtin_nanf(""));
        }
        return ::asc::std::__fp_cast<To>(::asc::std::__detail::__fp8_decode(field, 8, 0, false));
    }
#endif  // CANN_ASC_STL_DETAIL_HAS_FP8_E8M0()
#if CANN_ASC_STL_DETAIL_HAS_FP8_E4M3()
    else if constexpr (__fp_format_of_v<To> == __fp_format::__fp8_e4m3) {
        return __fp_from_storage<To>(
            ::asc::std::__detail::__fp8_encode(::asc::std::__fp_cast<float>(value), 4, 3, true));
    }
#endif  // CANN_ASC_STL_DETAIL_HAS_FP8_E4M3()
#if CANN_ASC_STL_DETAIL_HAS_FP8_E5M2()
    else if constexpr (__fp_format_of_v<To> == __fp_format::__fp8_e5m2) {
        return __fp_from_storage<To>(
            ::asc::std::__detail::__fp8_encode(::asc::std::__fp_cast<float>(value), 5, 2, false));
    }
#endif  // CANN_ASC_STL_DETAIL_HAS_FP8_E5M2()
#if CANN_ASC_STL_DETAIL_HAS_FP8_E8M0()
    else if constexpr (__fp_format_of_v<To> == __fp_format::__fp8_e8m0) {
        return __fp_from_storage<To>(::asc::std::__detail::__e8m0_encode(::asc::std::__fp_cast<float>(value)));
    }
#endif  // CANN_ASC_STL_DETAIL_HAS_FP8_E8M0()
    else if constexpr (is_same_v<From, float>) {
        // float → half/bfloat16_t/long double：编译器原生转换（CCE 设备内建）
        return static_cast<To>(value);
    } else if constexpr (__is_fp_v<From> && __is_fp_v<To>) {
        // double/long double/half/bfloat16_t 的其余跨格式：经 float 轴心中转
        return ::asc::std::__fp_cast<To>(static_cast<float>(value));
    } else {
        static_assert(__always_false_v<To>, "Unsupported floating point conversion");
    }
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___FLOATING_POINT_CAST_H
