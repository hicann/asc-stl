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
#ifndef CANN_ASC_STL_ASC_STD___COMPLEX_MATH_H
#define CANN_ASC_STL_ASC_STD___COMPLEX_MATH_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__cmath/abs.h>
#include <asc/std/__cmath/copysign.h>
#include <asc/std/__cmath/hypot.h>
#include <asc/std/__cmath/inverse_trigonometric_functions.h>
#include <asc/std/__cmath/isinf.h>
#include <asc/std/__cmath/isnan.h>
#include <asc/std/__cmath/signbit.h>
#include <asc/std/__cmath/sincos.h>
#include <asc/std/__cmath/trigonometric_functions.h>
#include <asc/std/__complex/complex.h>
#include <asc/std/__complex/vector_support.h>
#include <asc/std/__type_traits/is_extended_arithmetic.h>
#include <asc/std/__type_traits/is_floating_point.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/limits>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API T abs(const complex<T>& value) noexcept
{
    return ::asc::std::hypot(value.real(), value.imag());
}
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr T norm(T value) noexcept
{
    return value * value;
}
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr complex<T> conj(T value) noexcept
{
    return complex<T>(value);
}
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> proj(const complex<T>& value) noexcept
{
    if (::asc::std::isinf(value.real()) || ::asc::std::isinf(value.imag())) {
        return complex<T>(numeric_limits<T>::infinity(),  // NOLINT(build/include_what_you_use)
            ::asc::std::copysign(T(0), value.imag()));
    }
    return value;
}
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> proj(T value) noexcept
{
    return ::asc::std::isinf(value) ? complex<T>(::asc::std::fabs(value), 0) : complex<T>(value, 0);
}
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> polar(const T& radius, const T& angle = T()) noexcept
{
    // C99 契约：负半径/NaN 半径 → (NaN, NaN)；NaN 角与 Inf 角的组合按
    // isinf(radius) 区分（Inf 半径保 radius，否则 (NaN, NaN)/（radius, NaN)）。
    if (::asc::std::isnan(radius) || ::asc::std::signbit(radius)) {
        return complex<T>(numeric_limits<T>::quiet_NaN(),  // NOLINT(build/include_what_you_use)
            numeric_limits<T>::quiet_NaN());               // NOLINT(build/include_what_you_use)
    }
    if (::asc::std::isnan(angle)) {
        if (::asc::std::isinf(radius)) {
            return complex<T>(radius, angle);
        }
        return complex<T>(angle, angle);
    }
    if (::asc::std::isinf(angle)) {
        if (::asc::std::isinf(radius)) {
            return complex<T>(radius, numeric_limits<T>::quiet_NaN());  // NOLINT(build/include_what_you_use)
        }
        return complex<T>(numeric_limits<T>::quiet_NaN(),  // NOLINT(build/include_what_you_use)
            numeric_limits<T>::quiet_NaN());               // NOLINT(build/include_what_you_use)
    }
    const auto direction = ::asc::std::__sincos(angle);
    // 0 与 Inf 的乘积产生 NaN 时归零（C99 polar 定义：有限半径与 0 倍 Inf 的
    // 三角结果组合按 0 处理）。
    T x = radius * direction.cos;
    if (::asc::std::isnan(x)) {
        x = 0;
    }
    T y = radius * direction.sin;
    if (::asc::std::isnan(y)) {
        y = 0;
    }
    return complex<T>(x, y);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___COMPLEX_MATH_H
