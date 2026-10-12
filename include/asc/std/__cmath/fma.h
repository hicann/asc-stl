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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_FMA_H
#define CANN_ASC_STL_ASC_STD___CMATH_FMA_H

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

// 纯 SIMT TU 的原生半精度融合乘加（承 dev 真机证据链）：9.3.0 谱系工具链经
// simt_api/asc_fp16.h 提供 __hfma（950 真机数值验证）；头存在性经
// __has_include 探测，9.2.0 谱系及宿主自动退回 float 精度中转。
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
#if defined(__has_include)
#if __has_include(<simt_api/asc_fp16.h>)
#include <simt_api/asc_fp16.h>
#define CANN_ASC_STL_DETAIL_FMA_HW_HALF 1
#endif
#endif
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

// fma 三层分派（承 dev 语义、基座宏形状）：float 主名与后缀别名经 backend
// 路由——纯 SIMT TU 走 simt_api 标量库（__aicore__ 可达，2026-09 真机酸测
// 证实其 fmaf 为单次舍入），其余走编译器内建；double/long double 主名、
// 后缀 l 别名与 mixed-type promote 仅宿主（向量核禁 double，设备禁
// long double）；扩展浮点（half/bfloat16/fp8 族）经 float 精度中转并保持
// 原格式往返，SIMT 且工具链提供 __hfma 时 half 走原生融合路径。

//! @brief 融合乘加 x*y + z（单次舍入）。
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float fma(
    float x, float y, float z) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(fmaf, __builtin_fmaf, (x, y, z));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float fmaf(
    float x, float y, float z) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(fmaf, __builtin_fmaf, (x, y, z));
}

//! @brief 扩展浮点（half/bfloat16/fp8 族）fma：SIMT 硬件 __hfma 优先（原生
//! 半精度融合），否则 float 精度中转，原格式返回。
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp fma(
    Tp x, Tp y, Tp z) noexcept
{
#if defined(CANN_ASC_STL_DETAIL_FMA_HW_HALF)
    if constexpr (is_same_v<Tp, half>) {
        return static_cast<Tp>(::__hfma(x, y, z));
    } else  // NOLINT(readability/braces)
#endif
        return static_cast<Tp>(::asc::std::fma(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)));
}

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// 宿主全类型面：double/long double 主名、后缀 l 别名、整型提升与
// mixed-type promote。冻结合同断言 decltype(fma(1, 2.0F, 3.0F)) == float：
// 整型与 float 的混合经非模板 float 重载的隐式转换解析（int→float 与
// int→double 同秩，float 重载在浮点实参上精确匹配胜出），全整型组合由
// 整型三元重载消歧并保持基座 float 精度；仅当含 double/long double 实参
// 时 promote 模板才参与并归一到公共宽度（float+double 混型否则歧义）。

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double fma(double x, double y, double z) noexcept
{
    return __builtin_fma(x, y, z);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double fma(
    long double x, long double y, long double z) noexcept
{
    return __builtin_fmal(x, y, z);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double fmal(
    long double x, long double y, long double z) noexcept
{
    return __builtin_fmal(x, y, z);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

//! @brief All-integral fma: the float-precision continuation of the
//! float-only era (base observable contract), disambiguating the mixed
//! int-to-floating conversion ranks.
template <class Tp, class Up, class Vp,
    ::asc::std::enable_if_t<is_integral_v<Tp> && is_integral_v<Up> && is_integral_v<Vp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr float fma(Tp x, Up y, Vp z) noexcept
{
    return ::asc::std::fma(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
}

//! @brief fma over three arithmetic operands including at least one double or
//! long double: all promote to the common width first.
template <class Tp, class Up, class Vp,
    ::asc::std::enable_if_t<is_arithmetic_v<Tp> && is_arithmetic_v<Up> && is_arithmetic_v<Vp> &&
            (is_same_v<Tp, double> || is_same_v<Up, double> || is_same_v<Vp, double> || is_same_v<Tp, long double> ||
                is_same_v<Up, long double> || is_same_v<Vp, long double>),
        int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr __promote_t<Tp, Up, Vp> fma(Tp x, Up y, Vp z) noexcept
{
    using result_type = __promote_t<Tp, Up, Vp>;
    return ::asc::std::fma(static_cast<result_type>(x), static_cast<result_type>(y), static_cast<result_type>(z));
}

#endif  // !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_FMA_H
