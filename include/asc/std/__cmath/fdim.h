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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_FDIM_H
#define CANN_ASC_STL_ASC_STD___CMATH_FDIM_H

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

CANN_ASC_STL_BEGIN_NAMESPACE

// fdim 三层分派（承 dev 语义、基座宏形状）：float 主名与后缀别名经 backend
// 路由——纯 SIMT TU 走 simt_api 标量库（__aicore__ 可达），其余走编译器内
// 建；double/long double 主名、后缀 l 别名与 mixed-type promote 仅宿主（向
// 量核禁 double，设备禁 long double）；扩展浮点（half/bfloat16/fp8 族）经
// float 精度中转并保持原格式往返。基座手写 isnan+比较路径收敛为原生
// fdimf 委托（NaN 传播与 x<=y 返 +0 契约由其承载）；dev 的同型整型重载由
// mixed-type promote 模板覆盖（int+int 与 int+long 均归一 double，消除仅
// float/double 重载并存时整型调用的歧义）。

//! @brief 正差 fdim(x, y) = x > y ? x - y : +0（任一参数 NaN 返回 NaN）。
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float fdim(
    float x, float y) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(fdimf, __builtin_fdimf, (x, y));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float fdimf(
    float x, float y) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(fdimf, __builtin_fdimf, (x, y));
}

//! @brief 扩展浮点（half/bfloat16/fp8 族）fdim：float 精度中转，原格式返回。
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp fdim(
    Tp x, Tp y) noexcept
{
    return static_cast<Tp>(::asc::std::fdim(static_cast<float>(x), static_cast<float>(y)));
}

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// 宿主全类型面：double/long double 主名、后缀 l 别名与 mixed-type promote
// （int+float 混型经 __promote_t 归一到公共宽度，与 libstdc++ 同型）。

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double fdim(double x, double y) noexcept
{
    return __builtin_fdim(x, y);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double fdim(long double x, long double y) noexcept
{
    return __builtin_fdiml(x, y);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double fdiml(long double x, long double y) noexcept
{
    return __builtin_fdiml(x, y);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

//! @brief fdim over two arithmetic operands of different types: both promote
//! to the common width first.
template <class Tp, class Up, ::asc::std::enable_if_t<is_arithmetic_v<Tp> && is_arithmetic_v<Up>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr __promote_t<Tp, Up> fdim(Tp x, Up y) noexcept
{
    using result_type = __promote_t<Tp, Up>;
    static_assert(!(is_same_v<Tp, result_type> && is_same_v<Up, result_type>));
    return ::asc::std::fdim(static_cast<result_type>(x), static_cast<result_type>(y));
}

#endif  // !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_FDIM_H
