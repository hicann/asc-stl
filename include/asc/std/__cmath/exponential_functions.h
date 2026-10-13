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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_EXPONENTIAL_FUNCTIONS_H
#define CANN_ASC_STL_ASC_STD___CMATH_EXPONENTIAL_FUNCTIONS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/__detail/execution_space.h>
#include <asc/std/__cmath/backend.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_arithmetic.h>
#include <asc/std/__type_traits/is_extended_floating_point.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/promote.h>
#include <asc/std/__type_traits/is_constant_evaluated.h>

// Inline equivalent of the dev CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE() gate
// (the master config does not provide it): long double is host-only — AI-core
// compilation does not support long double.
#if !defined(CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE)
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && !defined(ASC_DISABLE_LONG_DOUBLE_SUPPORT)
#define CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE() 0
#endif
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE

CANN_ASC_STL_BEGIN_NAMESPACE

// 指数/缩放族三层分派（承 dev 语义、基座宏形状）：主名 float 与后缀别名
// 经 backend 路由——纯 SIMT TU 走 simt_api 标量库（__aicore__ 可达，含
// 指针出参 frexpf 形态；expf/exp2f 冲刷次正规输入输出），其余走编译器内
// 建；double/long double/整型提升与后缀 l 别名仅宿主（向量核无 double 精
// 度，设备禁 long double）；扩展浮点经 float 精度中转并保持原格式往返。

// 对齐 dev 的指数族扩展浮点集合：仅 half/bfloat16（fp8 标量转换路径在该
// 编译器不可用，暴露重载会宣告编译期即失败的调用）。
template <class Tp>
inline constexpr bool __expo_supported_extended_v = false;
#if CANN_ASC_STL_DETAIL_HAS_HALF()
template <>
inline constexpr bool __expo_supported_extended_v<half> = true;
#endif
#if CANN_ASC_STL_DETAIL_HAS_BFLOAT16()
template <>
inline constexpr bool __expo_supported_extended_v<bfloat16_t> = true;
#endif

//! @brief 自然指数 e^@p value。
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float exp(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(expf, __builtin_expf, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float expf(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(expf, __builtin_expf, (value));
}

//! @brief 扩展浮点（half/bfloat16）exp：float 精度中转，原格式返回。
template <class Tp, ::asc::std::enable_if_t<__expo_supported_extended_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp exp(Tp value) noexcept
{
    return static_cast<Tp>(::asc::std::exp(static_cast<float>(value)));
}

//! @brief 2 的 @p value 次幂。
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float exp2(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(exp2f, __builtin_exp2f, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float exp2f(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(exp2f, __builtin_exp2f, (value));
}

template <class Tp, ::asc::std::enable_if_t<__expo_supported_extended_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp exp2(Tp value) noexcept
{
    return static_cast<Tp>(::asc::std::exp2(static_cast<float>(value)));
}

//! @brief e^@p value - 1，@p value 接近 0 时保持精度。
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float expm1(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(expm1f, __builtin_expm1f, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float expm1f(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(expm1f, __builtin_expm1f, (value));
}

template <class Tp, ::asc::std::enable_if_t<__expo_supported_extended_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp expm1(
    Tp value) noexcept
{
    return static_cast<Tp>(::asc::std::expm1(static_cast<float>(value)));
}

//! @brief 分解为尾数（[0.5, 1) 或 0）与以 2 为底的指数（经 @p exponent 出参）。
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float frexp(
    float value, int* exponent) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(frexpf, __builtin_frexpf, (value, exponent));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float frexpf(
    float value, int* exponent) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(frexpf, __builtin_frexpf, (value, exponent));
}

template <class Tp, ::asc::std::enable_if_t<__expo_supported_extended_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp frexp(
    Tp value, int* exponent) noexcept
{
    return static_cast<Tp>(::asc::std::frexp(static_cast<float>(value), exponent));
}

//! @brief @p value * 2^@p exponent（逆 frexp）。
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float ldexp(
    float value, int exponent) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(ldexpf, __builtin_ldexpf, (value, exponent));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float ldexpf(
    float value, int exponent) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(ldexpf, __builtin_ldexpf, (value, exponent));
}

template <class Tp, ::asc::std::enable_if_t<__expo_supported_extended_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp ldexp(
    Tp value, int exponent) noexcept
{
    return static_cast<Tp>(::asc::std::ldexp(static_cast<float>(value), exponent));
}

//! @brief 以 float 拆分整数与小数部分（整数部分经 @p integer_part 出参，
//! 与 @p value 同符号）。
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float modf(
    float value, float* integer_part) noexcept
{
    return __builtin_modff(value, integer_part);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float modff(
    float value, float* integer_part) noexcept
{
    return __builtin_modff(value, integer_part);
}

//! @brief @p value * FLT_RADIX^@p exponent（FLT_RADIX = 2）。
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float scalbn(
    float value, int exponent) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(scalbnf, __builtin_scalbnf, (value, exponent));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float scalbnf(
    float value, int exponent) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(scalbnf, __builtin_scalbnf, (value, exponent));
}

template <class Tp, ::asc::std::enable_if_t<__expo_supported_extended_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp scalbn(
    Tp value, int exponent) noexcept
{
    return static_cast<Tp>(::asc::std::scalbn(static_cast<float>(value), exponent));
}

//! @brief 同 scalbn，指数为 long。
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float scalbln(
    float value, long exponent) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(scalblnf, __builtin_scalblnf, (value, exponent));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float scalblnf(
    float value, long exponent) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(scalblnf, __builtin_scalblnf, (value, exponent));
}

template <class Tp, ::asc::std::enable_if_t<__expo_supported_extended_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp scalbln(
    Tp value, long exponent) noexcept
{
    return static_cast<Tp>(::asc::std::scalbln(static_cast<float>(value), exponent));
}

//! @brief @p base 的 @p exponent 次幂。
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float pow(
    float base, float exponent) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(powf, __builtin_powf, (base, exponent));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float powf(
    float base, float exponent) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(powf, __builtin_powf, (base, exponent));
}

template <class Tp, ::asc::std::enable_if_t<__expo_supported_extended_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp pow(
    Tp base, Tp exponent) noexcept
{
    return static_cast<Tp>(::asc::std::pow(static_cast<float>(base), static_cast<float>(exponent)));
}

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// 宿主全类型面：double/long double 主名、后缀 l 别名与整型提升。整型提升
// 整型提升对齐 <cmath> 标准：整型实参提升为 double 计算并返回 double。

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double exp(double value) noexcept
{
    return __builtin_exp(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double exp(long double value) noexcept
{
    return __builtin_expl(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double expl(long double value) noexcept
{
    return __builtin_expl(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double exp(Tp value) noexcept
{
    return ::asc::std::exp(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double exp2(double value) noexcept
{
    return __builtin_exp2(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double exp2(long double value) noexcept
{
    return __builtin_exp2l(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double exp2l(long double value) noexcept
{
    return __builtin_exp2l(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double exp2(Tp value) noexcept
{
    return ::asc::std::exp2(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double expm1(double value) noexcept
{
    return __builtin_expm1(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double expm1(long double value) noexcept
{
    return __builtin_expm1l(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double expm1l(long double value) noexcept
{
    return __builtin_expm1l(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double expm1(Tp value) noexcept
{
    return ::asc::std::expm1(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double frexp(double value, int* exponent) noexcept
{
    return __builtin_frexp(value, exponent);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double frexp(long double value, int* exponent) noexcept
{
    return __builtin_frexpl(value, exponent);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double frexpl(long double value, int* exponent) noexcept
{
    return __builtin_frexpl(value, exponent);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double frexp(Tp value, int* exponent) noexcept
{
    return ::asc::std::frexp(static_cast<double>(value), exponent);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double ldexp(double value, int exponent) noexcept
{
    return __builtin_ldexp(value, exponent);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double ldexp(long double value, int exponent) noexcept
{
    return __builtin_ldexpl(value, exponent);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double ldexpl(long double value, int exponent) noexcept
{
    return __builtin_ldexpl(value, exponent);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double ldexp(Tp value, int exponent) noexcept
{
    return ::asc::std::ldexp(static_cast<double>(value), exponent);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double scalbn(double value, int exponent) noexcept
{
    return __builtin_scalbn(value, exponent);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double scalbn(long double value, int exponent) noexcept
{
    return __builtin_scalbnl(value, exponent);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double scalbnl(long double value, int exponent) noexcept
{
    return __builtin_scalbnl(value, exponent);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double scalbn(Tp value, int exponent) noexcept
{
    return ::asc::std::scalbn(static_cast<double>(value), exponent);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double scalbln(double value, long exponent) noexcept
{
    return __builtin_scalbln(value, exponent);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double scalbln(long double value, long exponent) noexcept
{
    return __builtin_scalblnl(value, exponent);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double scalblnl(long double value, long exponent) noexcept
{
    return __builtin_scalblnl(value, exponent);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double scalbln(Tp value, long exponent) noexcept
{
    return ::asc::std::scalbln(static_cast<double>(value), exponent);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double pow(double base, double exponent) noexcept
{
    return __builtin_pow(base, exponent);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double pow(long double base, long double exponent) noexcept
{
    return __builtin_powl(base, exponent);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double powl(long double base, long double exponent) noexcept
{
    return __builtin_powl(base, exponent);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

//! @brief pow over two arithmetic operands of different types: both promote
//! to the common width first.
template <class Tp, class Up, ::asc::std::enable_if_t<is_arithmetic_v<Tp> && is_arithmetic_v<Up>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr __promote_t<Tp, Up> pow(Tp base, Up exponent) noexcept
{
    using result_type = __promote_t<Tp, Up>;
    static_assert(!(is_same_v<Tp, result_type> && is_same_v<Up, result_type>));
    return ::asc::std::pow(static_cast<result_type>(base), static_cast<result_type>(exponent));
}

#endif  // !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

//! @brief 常量求值安全的 scalbn（dev 同源 __constexpr_scalbn 语义，供复数
//! 除法等内部件使用）：常量上下文用平方求幂循环（覆盖 INT_MIN 全幅无符号
//! 量，上游参考版本循环每非零指数漏一个基数因子，此处修正）；运行时分派回
//! scalbn（设备硬件 / 宿主 libm）。
template <class Tp>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp __constexpr_scalbn(
    Tp value, int exponent) noexcept
{
    if (::asc::std::is_constant_evaluated()) {
        if (value == Tp(0) || exponent == 0 || value != value)
            return value;
        const bool negative = exponent < 0;
        unsigned int magnitude =
            negative ? static_cast<unsigned int>(-(exponent + 1)) + 1U : static_cast<unsigned int>(exponent);
        // 在册浮点格式（binary16/32/64、bfloat16）基数均为 2，直用字面
        // 量，避免设备 TU 的 limits 特化依赖。
        Tp multiplier = negative ? Tp(1) / Tp(2) : Tp(2);
        while (magnitude != 0) {
            if ((magnitude & 1U) != 0U)
                value *= multiplier;
            magnitude >>= 1U;
            if (magnitude != 0)
                multiplier *= multiplier;
        }
        return value;
    }
    return ::asc::std::scalbn(value, exponent);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_EXPONENTIAL_FUNCTIONS_H
