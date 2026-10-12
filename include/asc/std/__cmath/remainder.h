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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_REMAINDER_H
#define CANN_ASC_STL_ASC_STD___CMATH_REMAINDER_H

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

// remainder/remquo/nextafter 三层分派（承 dev 语义、基座宏形状）：float 主名
// 与后缀别名经 backend 路由——纯 SIMT TU 走 simt_api 标量库（__aicore__ 可
// 达），其余走编译器内建；double/long double 主名、后缀 l 别名与
// mixed-type promote 仅宿主（向量核禁 double，设备禁 long double）；扩展
// 浮点（half/bfloat16/fp8 族）经 float 精度中转并保持原格式往返。
// remquo 全族维持仅 float 精度：冻结合同断言 decltype(remquo(1.0L, 2.0L,
// int*)) == float——加 double/long double 重载会使该调用歧义（两种浮点
// 转换同秩）。nextafter 族为基座全树唯一定义点（dev 挪往 rounding 侧未随
// 迁），此处按 dev 全家谱语义就地扩展。

//! @brief IEEE 余数 x - n*y（n 取最接近商，半值取偶）：|result| <= |y|/2，
//! 符号随 x*y。
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float remainder(
    float x, float y) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(remainderf, __builtin_remainderf, (x, y));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float remainderf(
    float x, float y) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(remainderf, __builtin_remainderf, (x, y));
}

//! @brief 扩展浮点（half/bfloat16/fp8 族）remainder：float 精度中转，原格式返回。
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp remainder(
    Tp x, Tp y) noexcept
{
    return static_cast<Tp>(::asc::std::remainder(static_cast<float>(x), static_cast<float>(y)));
}

//! @brief 同 remainder，另将 n 对 2^3 的余数（商的低 3 位，符号随 x/y）写入
//! @p quotient。返回 IEEE 余数。
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float remquo(
    float x, float y, int* quotient) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(remquof, __builtin_remquof, (x, y, quotient));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float remquof(
    float x, float y, int* quotient) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(remquof, __builtin_remquof, (x, y, quotient));
}

//! @brief 扩展浮点 remquo：float 精度中转，原格式返回。
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp remquo(
    Tp x, Tp y, int* quotient) noexcept
{
    return static_cast<Tp>(::asc::std::remquo(static_cast<float>(x), static_cast<float>(y), quotient));
}

//! @brief 朝 @p y 方向的下一个可表示值（x == y 时返回 x）。
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float nextafter(
    float x, float y) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(nextafterf, __builtin_nextafterf, (x, y));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float nextafterf(
    float x, float y) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(nextafterf, __builtin_nextafterf, (x, y));
}

//! @brief 扩展浮点 nextafter：float 精度中转，原格式返回。
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp nextafter(
    Tp x, Tp y) noexcept
{
    return static_cast<Tp>(::asc::std::nextafter(static_cast<float>(x), static_cast<float>(y)));
}

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// 宿主全类型面：double/long double 主名、后缀 l 别名与 mixed-type promote
// （int+float 混型经 __promote_t 归一到公共宽度，与 libstdc++ 同型）。

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double remainder(double x, double y) noexcept
{
    return __builtin_remainder(x, y);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double remainder(long double x, long double y) noexcept
{
    return __builtin_remainderl(x, y);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double remainderl(long double x, long double y) noexcept
{
    return __builtin_remainderl(x, y);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

//! @brief remainder over two arithmetic operands of different types: both
//! promote to the common width first.
template <class Tp, class Up, ::asc::std::enable_if_t<is_arithmetic_v<Tp> && is_arithmetic_v<Up>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr __promote_t<Tp, Up> remainder(Tp x, Up y) noexcept
{
    using result_type = __promote_t<Tp, Up>;
    static_assert(!(is_same_v<Tp, result_type> && is_same_v<Up, result_type>));
    return ::asc::std::remainder(static_cast<result_type>(x), static_cast<result_type>(y));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double nextafter(double x, double y) noexcept
{
    return __builtin_nextafter(x, y);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double nextafter(long double x, long double y) noexcept
{
    return __builtin_nextafterl(x, y);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double nextafterl(long double x, long double y) noexcept
{
    return __builtin_nextafterl(x, y);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

//! @brief nextafter over two arithmetic operands of different types: both
//! promote to the common width first.
template <class Tp, class Up, ::asc::std::enable_if_t<is_arithmetic_v<Tp> && is_arithmetic_v<Up>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr __promote_t<Tp, Up> nextafter(Tp x, Up y) noexcept
{
    using result_type = __promote_t<Tp, Up>;
    static_assert(!(is_same_v<Tp, result_type> && is_same_v<Up, result_type>));
    return ::asc::std::nextafter(static_cast<result_type>(x), static_cast<result_type>(y));
}

#endif  // !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_REMAINDER_H
