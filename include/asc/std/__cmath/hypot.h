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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_HYPOT_H
#define CANN_ASC_STL_ASC_STD___CMATH_HYPOT_H

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

// hypot 三层分派（承 dev 语义、基座宏形状）：float 主名与后缀别名经
// backend 路由——纯 SIMT TU 走 simt_api 标量库（__aicore__ 可达），其余走
// 编译器内建；double/long double 主名、后缀 l 别名与 mixed-type promote
// 仅宿主（向量核禁 double，设备禁 long double）；扩展浮点（half/bfloat16/
// fp8 族）经 float 精度中转并保持原格式往返。三参 hypot 由两层两参复合
// （每次调用内部已做缩放，与 libstdc++ std::hypot 三参实现同构），修复
// 基座 x*x+y*y+z*z 直和在大幅值输入下的中间溢出缺陷。

//! @brief sqrt(x*x + y*y) 的无溢出实现（内部缩放，NaN/无穷契约由原生
//! hypotf 承载）。
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float hypot(
    float x, float y) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(hypotf, __builtin_hypotf, (x, y));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float hypotf(
    float x, float y) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(hypotf, __builtin_hypotf, (x, y));
}

//! @brief 三维斜边 sqrt(x*x+y*y+z*z)：两层两参复合，无中间溢出/下溢。
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float hypot(
    float x, float y, float z) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(
        hypotf, __builtin_hypotf, (CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(hypotf, __builtin_hypotf, (x, y)), z));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR float hypotf(
    float x, float y, float z) noexcept
{
    return ::asc::std::hypot(x, y, z);
}

//! @brief 扩展浮点（half/bfloat16/fp8 族）hypot：float 精度中转，原格式返回。
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp hypot(
    Tp x, Tp y) noexcept
{
    return static_cast<Tp>(::asc::std::hypot(static_cast<float>(x), static_cast<float>(y)));
}

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_CMATH_RUNTIME_CONSTEXPR Tp hypot(
    Tp x, Tp y, Tp z) noexcept
{
    return static_cast<Tp>(::asc::std::hypot(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)));
}

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// 宿主全类型面：double/long double 主名、后缀 l 别名与 mixed-type promote
// （int+float 混型经 __promote_t 归一到公共宽度，与 libstdc++ 同型）。

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double hypot(double x, double y) noexcept
{
    return __builtin_hypot(x, y);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double hypot(long double x, long double y) noexcept
{
    return __builtin_hypotl(x, y);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double hypotl(long double x, long double y) noexcept
{
    return __builtin_hypotl(x, y);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

//! @brief hypot over two arithmetic operands of different types: both promote
//! to the common width first.
template <class Tp, class Up, ::asc::std::enable_if_t<is_arithmetic_v<Tp> && is_arithmetic_v<Up>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr __promote_t<Tp, Up> hypot(Tp x, Up y) noexcept
{
    using result_type = __promote_t<Tp, Up>;
    static_assert(!(is_same_v<Tp, result_type> && is_same_v<Up, result_type>));
    return ::asc::std::hypot(static_cast<result_type>(x), static_cast<result_type>(y));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr double hypot(double x, double y, double z) noexcept
{
    return __builtin_hypot(__builtin_hypot(x, y), z);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double hypot(
    long double x, long double y, long double z) noexcept
{
    return __builtin_hypotl(__builtin_hypotl(x, y), z);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr long double hypotl(
    long double x, long double y, long double z) noexcept
{
    return ::asc::std::hypot(x, y, z);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

//! @brief hypot over three arithmetic operands of different types: all promote
//! to the common width first.
template <class Tp, class Up, class Vp,
    ::asc::std::enable_if_t<is_arithmetic_v<Tp> && is_arithmetic_v<Up> && is_arithmetic_v<Vp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr __promote_t<Tp, Up, Vp> hypot(Tp x, Up y, Vp z) noexcept
{
    using result_type = __promote_t<Tp, Up, Vp>;
    static_assert(!(is_same_v<Tp, result_type> && is_same_v<Up, result_type> && is_same_v<Vp, result_type>));
    return ::asc::std::hypot(static_cast<result_type>(x), static_cast<result_type>(y), static_cast<result_type>(z));
}

#endif  // !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_HYPOT_H
