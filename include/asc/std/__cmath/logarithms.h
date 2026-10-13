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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_LOGARITHMS_H
#define CANN_ASC_STL_ASC_STD___CMATH_LOGARITHMS_H

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
#include <asc/std/__type_traits/is_extended_floating_point.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_same.h>

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

// C99 ilogb 特殊值契约宏（宿主 <math.h> 已包含时沿用其取值，保证与
// ::ilogb 运行时结果一致；设备 TU 无该头，给出 glibc 同款回退值）。
#ifndef FP_ILOGB0
#define FP_ILOGB0 (-2147483647 - 1)
#endif
#ifndef FP_ILOGBNAN
#define FP_ILOGBNAN 2147483647
#endif

// 纯 SIMT TU 的 half/bfloat16 硬件对数族（承 dev 真机证据链）：hlog 族
// 走专用硬件路径，其饱和模式会按 SIMT API 文档改变特殊值；头存在性经
// __has_include 探测，旧谱系工具链自动退回 float 精度中转。
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
#if defined(__has_include)
#if __has_include(<simt_api/asc_fp16.h>)
#include <simt_api/asc_fp16.h>
#define CANN_ASC_STL_DETAIL_LOG_HW_HALF 1
#endif
#if __has_include(<simt_api/asc_bf16.h>)
#include <simt_api/asc_bf16.h>
#define CANN_ASC_STL_DETAIL_LOG_HW_BF16 1
#endif
#endif
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

// 对数族三层分派（承 dev 语义、基座宏形状）：主名 float 与后缀别名经
// backend 路由——纯 SIMT TU 走 simt_api 标量库（__aicore__ 可达），其余
// 走编译器内建；double/long double/整型提升与后缀 l 别名仅宿主（向量核
// 无 double 精度，设备禁 long double）；扩展浮点经 float 精度中转并保持
// 原格式往返。

//! @brief 自然对数 ln(@p value)。
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float log(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(logf, __builtin_logf, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float logf(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(logf, __builtin_logf, (value));
}

//! @brief 扩展浮点（half/bfloat16/fp8 族）log：SIMT 硬件 hlog 族优先
//! （饱和模式特殊值按 SIMT API 文档），否则 float 精度中转，原格式返回。
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp log(Tp value) noexcept
{
#if defined(CANN_ASC_STL_DETAIL_LOG_HW_HALF)
    if constexpr (is_same_v<Tp, half>) {
        return ::hlog(value);
    } else  // NOLINT(readability/braces)
#endif
#if defined(CANN_ASC_STL_DETAIL_LOG_HW_BF16)
        if constexpr (is_same_v<Tp, bfloat16_t>) {
        return ::hlog(value);
    } else  // NOLINT(readability/braces)
#endif
        return static_cast<Tp>(::asc::std::log(static_cast<float>(value)));
}

//! @brief 常用对数 log10(@p value)。
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float log10(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(log10f, __builtin_log10f, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float log10f(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(log10f, __builtin_log10f, (value));
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp log10(
    Tp value) noexcept
{
#if defined(CANN_ASC_STL_DETAIL_LOG_HW_HALF)
    if constexpr (is_same_v<Tp, half>) {
        return ::hlog10(value);
    } else  // NOLINT(readability/braces)
#endif
#if defined(CANN_ASC_STL_DETAIL_LOG_HW_BF16)
        if constexpr (is_same_v<Tp, bfloat16_t>) {
        return ::hlog10(value);
    } else  // NOLINT(readability/braces)
#endif
        return static_cast<Tp>(::asc::std::log10(static_cast<float>(value)));
}

//! @brief log(1 + @p value)，@p value 接近 0 时保持精度。
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float log1p(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(log1pf, __builtin_log1pf, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float log1pf(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(log1pf, __builtin_log1pf, (value));
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp log1p(
    Tp value) noexcept
{
    return static_cast<Tp>(::asc::std::log1p(static_cast<float>(value)));
}

//! @brief 以 2 为底的对数。
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float log2(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(log2f, __builtin_log2f, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float log2f(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(log2f, __builtin_log2f, (value));
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp log2(Tp value) noexcept
{
#if defined(CANN_ASC_STL_DETAIL_LOG_HW_HALF)
    if constexpr (is_same_v<Tp, half>) {
        return ::hlog2(value);
    } else  // NOLINT(readability/braces)
#endif
#if defined(CANN_ASC_STL_DETAIL_LOG_HW_BF16)
        if constexpr (is_same_v<Tp, bfloat16_t>) {
        return ::hlog2(value);
    } else  // NOLINT(readability/braces)
#endif
        return static_cast<Tp>(::asc::std::log2(static_cast<float>(value)));
}

//! @brief @p value 的规范化指数（无偏 exponent，整型返回）。NaN 契约：
//! 设备原生 ilogbf 对 NaN 返回 ASCRT_MIN_VAL_S，此处按 C++ 契约返回
//! FP_ILOGBNAN；0 返回 FP_ILOGB0。
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR int ilogb(
    float value) noexcept
{
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    return value != value ? FP_ILOGBNAN : ::ilogbf(value);
#else
    return __builtin_ilogbf(value);
#endif
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR int ilogbf(
    float value) noexcept
{
    return ::asc::std::ilogb(value);
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR int ilogb(
    Tp value) noexcept
{
    return ::asc::std::ilogb(static_cast<float>(value));
}

//! @brief @p value 的规范化指数（浮点返回）。±0 → -inf，±inf → +inf，
//! NaN → NaN。
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float logb(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(logbf, __builtin_logbf, (value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float logbf(
    float value) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(logbf, __builtin_logbf, (value));
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp logb(Tp value) noexcept
{
    return static_cast<Tp>(::asc::std::logb(static_cast<float>(value)));
}

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// 宿主全类型面：double/long double 主名、后缀 l 别名与整型提升。整型提升
// 整型提升对齐 <cmath> 标准：整型实参提升为 double 计算并返回 double。

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double log(double value) noexcept
{
    return __builtin_log(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double log(long double value) noexcept
{
    return __builtin_logl(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double logl(long double value) noexcept
{
    return __builtin_logl(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double log(Tp value) noexcept
{
    return ::asc::std::log(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double log10(double value) noexcept
{
    return __builtin_log10(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double log10(long double value) noexcept
{
    return __builtin_log10l(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double log10l(long double value) noexcept
{
    return __builtin_log10l(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double log10(Tp value) noexcept
{
    return ::asc::std::log10(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double log1p(double value) noexcept
{
    return __builtin_log1p(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double log1p(long double value) noexcept
{
    return __builtin_log1pl(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double log1pl(long double value) noexcept
{
    return __builtin_log1pl(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double log1p(Tp value) noexcept
{
    return ::asc::std::log1p(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double log2(double value) noexcept
{
    return __builtin_log2(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double log2(long double value) noexcept
{
    return __builtin_log2l(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double log2l(long double value) noexcept
{
    return __builtin_log2l(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double log2(Tp value) noexcept
{
    return ::asc::std::log2(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr int ilogb(double value) noexcept
{
    return __builtin_ilogb(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr int ilogb(long double value) noexcept
{
    return __builtin_ilogbl(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr int ilogbl(long double value) noexcept
{
    return __builtin_ilogbl(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr int ilogb(Tp value) noexcept
{
    return ::asc::std::ilogb(static_cast<double>(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double logb(double value) noexcept
{
    return __builtin_logb(value);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double logb(long double value) noexcept
{
    return __builtin_logbl(value);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double logbl(long double value) noexcept
{
    return __builtin_logbl(value);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double logb(Tp value) noexcept
{
    return ::asc::std::logb(static_cast<double>(value));
}

#endif  // !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_LOGARITHMS_H
