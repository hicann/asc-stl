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

#ifndef CANN_ASC_STL_ASC_STD___COMPLEX_COMPLEX_H
#define CANN_ASC_STL_ASC_STD___COMPLEX_COMPLEX_H

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
#include <asc/std/__cmath/isinf.h>
#include <asc/std/__cmath/isnan.h>
#include <asc/std/__cmath/sincos.h>
#include <asc/std/__complex/vector_support.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_floating_point.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_non_narrowing_convertible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/limits>

// Inline definition of the CANN_ASC_STL_DETAIL_HOSTED() gate (the __config
// does not provide it): AI-core kernel compilation has no host standard
// library and counts as freestanding, as does an explicit opt-out.
#if !defined(CANN_ASC_STL_DETAIL_HOSTED)
#if defined(CANN_ASC_STL_DETAIL_ENABLE_FREESTANDING) || defined(__CCE__)
#define CANN_ASC_STL_DETAIL_HOSTED() 0
#else
#define CANN_ASC_STL_DETAIL_HOSTED() 1
#endif
#endif  // CANN_ASC_STL_DETAIL_HOSTED

#if CANN_ASC_STL_DETAIL_HOSTED()
#include <complex>
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
struct __get_complex_impl;

// Host companions of the float __sincos in <asc/std/__cmath/sincos.h>: the
// double and long double pair evaluations exist on the Host only (the AI-core
// math surface is float precision), so complex<double> instantiations keep a
// clear "no matching function" diagnostic in device TUs.
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
CANN_ASC_STL_HOST_API __sincos_result<double> __sincos(double value) noexcept
{
    __sincos_result<double> result{};
    __builtin_sincos(value, &result.sin, &result.cos);
    return result;
}
CANN_ASC_STL_HOST_API __sincos_result<long double> __sincos(long double value) noexcept
{
    __sincos_result<long double> result{};
    __builtin_sincosl(value, &result.sin, &result.cos);
    return result;
}
#endif  // Host sincos companions

template <class T>
class alignas(__complex_alignment_v<T>) complex {
    // The delivered surface is the float specialization (complex<float>);
    // complex<double> must be rejected by this static assertion.
    static_assert(is_same_v<T, float>, "ASC-STL complex supports float only");

public:
    using value_type = T;
    CANN_ASC_STL_API constexpr complex(const T& real = T(), const T& imag = T()) noexcept : real_(real), imag_(imag)
    {}
    CANN_ASC_STL_API constexpr complex(const complex&) noexcept = default;
    CANN_ASC_STL_API constexpr complex(complex&&) noexcept = default;
    CANN_ASC_STL_API constexpr complex& operator=(const complex&) noexcept = default;
    CANN_ASC_STL_API constexpr complex& operator=(complex&&) noexcept = default;

    // Cross-type construction: implicit while the component conversion does
    // not narrow (widening stays lossless), explicit otherwise.
    template <class U, enable_if_t<__asc_internal::__is_non_narrowing_convertible<T, U>::value, int> = 0>
    CANN_ASC_STL_API constexpr complex(const complex<U>& other) noexcept : real_(other.real()), imag_(other.imag())
    {}
    template <class U,
        enable_if_t<is_constructible_v<T, U> && !__asc_internal::__is_non_narrowing_convertible<T, U>::value, int> = 0>
    CANN_ASC_STL_API explicit constexpr complex(const complex<U>& other) noexcept
        : real_(static_cast<T>(other.real())), imag_(static_cast<T>(other.imag()))
    {}

#if CANN_ASC_STL_DETAIL_HOSTED()
    // Read through the public C++ API. Reinterpreting std::complex as an
    // array would violate its aliasing.
    template <class U>
    CANN_ASC_STL_HOST_API complex(const ::std::complex<U>& other) noexcept
        : real_(static_cast<T>(other.real())), imag_(static_cast<T>(other.imag()))
    {}
    template <class U>
    CANN_ASC_STL_HOST_API complex& operator=(const ::std::complex<U>& other) noexcept
    {
        real_ = static_cast<T>(other.real());
        imag_ = static_cast<T>(other.imag());
        return *this;
    }
    CANN_ASC_STL_HOST_API operator ::std::complex<T>() const noexcept
    {
        return {real_, imag_};
    }
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

    CANN_ASC_STL_API constexpr T real() const noexcept
    {
        return real_;
    }
    CANN_ASC_STL_API constexpr T imag() const noexcept
    {
        return imag_;
    }
    CANN_ASC_STL_API constexpr void real(T value) noexcept
    {
        real_ = value;
    }
    CANN_ASC_STL_API constexpr void imag(T value) noexcept
    {
        imag_ = value;
    }
    CANN_ASC_STL_API T real() const volatile noexcept
    {
        return real_;
    }
    CANN_ASC_STL_API T imag() const volatile noexcept
    {
        return imag_;
    }
    CANN_ASC_STL_API void real(T value) volatile noexcept
    {
        real_ = value;
    }
    CANN_ASC_STL_API void imag(T value) volatile noexcept
    {
        imag_ = value;
    }

    CANN_ASC_STL_API constexpr complex& operator=(const T& value) noexcept
    {
        real_ = value;
        imag_ = T();
        return *this;
    }
    CANN_ASC_STL_API constexpr complex& operator+=(complex rhs) noexcept
    {
        real_ += rhs.real_;
        imag_ += rhs.imag_;
        return *this;
    }
    CANN_ASC_STL_API constexpr complex& operator-=(complex rhs) noexcept
    {
        real_ -= rhs.real_;
        imag_ -= rhs.imag_;
        return *this;
    }
    // Defined after the binary operators below so that the compound forms
    // share the NaN-recovering multiply and the ratio-scaled divide.
    CANN_ASC_STL_API constexpr complex& operator*=(complex rhs) noexcept;
    CANN_ASC_STL_API constexpr complex& operator/=(complex rhs) noexcept;
    CANN_ASC_STL_API constexpr complex& operator+=(const T& value) noexcept
    {
        real_ += value;
        return *this;
    }
    CANN_ASC_STL_API constexpr complex& operator-=(const T& value) noexcept
    {
        real_ -= value;
        return *this;
    }
    CANN_ASC_STL_API constexpr complex& operator*=(const T& value) noexcept
    {
        real_ *= value;
        imag_ *= value;
        return *this;
    }
    CANN_ASC_STL_API constexpr complex& operator/=(const T& value) noexcept
    {
        const T __safe_value = (value == T{0}) ? T{1} : value;
        real_ /= __safe_value;
        imag_ /= __safe_value;
        return *this;
    }
    template <class U>
    CANN_ASC_STL_API constexpr complex& operator+=(const complex<U>& other) noexcept
    {
        real_ += other.real();
        imag_ += other.imag();
        return *this;
    }
    template <class U>
    CANN_ASC_STL_API constexpr complex& operator-=(const complex<U>& other) noexcept
    {
        real_ -= other.real();
        imag_ -= other.imag();
        return *this;
    }

private:
    template <class U>
    friend class complex;
    friend struct __get_complex_impl<T>;

    T real_;
    T imag_;
};

// Mixed-type compound assignment converts the right operand through the
// value type and reuses the robust same-type operators.
template <class T, class U>
CANN_ASC_STL_API constexpr complex<T>& operator*=(complex<T>& left, const complex<U>& right) noexcept
{
    left = left * complex<T>(static_cast<T>(right.real()), static_cast<T>(right.imag()));
    return left;
}
template <class T, class U>
CANN_ASC_STL_API constexpr complex<T>& operator/=(complex<T>& left, const complex<U>& right) noexcept
{
    left = left / complex<T>(static_cast<T>(right.real()), static_cast<T>(right.imag()));
    return left;
}

template <class T>
CANN_ASC_STL_API constexpr complex<T> operator+(const complex<T>& left, const complex<T>& right) noexcept
{
    return {left.real() + right.real(), left.imag() + right.imag()};
}
template <class T>
CANN_ASC_STL_API constexpr complex<T> operator-(const complex<T>& left, const complex<T>& right) noexcept
{
    return {left.real() - right.real(), left.imag() - right.imag()};
}

// Partial-products multiply with C99-style NaN recovery: when both result
// components are NaN and any operand is infinite, the operands are folded to
// signed units and the product is scaled back through infinity so that
// (inf, y) * z and friends keep their signed infinite components.
template <class T>
CANN_ASC_STL_API constexpr complex<T> operator*(const complex<T>& left, const complex<T>& right) noexcept
{
    T a = left.real(), b = left.imag(), c = right.real(), d = right.imag();
    const auto parts = ::asc::std::__complex_calculate_partials(a, b, c, d);
    T x = parts.__ac - parts.__bd;
    T y = parts.__ad + parts.__bc;
    if (::asc::std::isnan(x) && ::asc::std::isnan(y)) {
        bool recover = false;
        if (::asc::std::isinf(a) || ::asc::std::isinf(b)) {
            a = ::asc::std::copysign(::asc::std::isinf(a) ? T(1) : T(0), a);
            b = ::asc::std::copysign(::asc::std::isinf(b) ? T(1) : T(0), b);
            if (::asc::std::isnan(c)) {
                c = ::asc::std::copysign(T(0), c);
            }
            if (::asc::std::isnan(d)) {
                d = ::asc::std::copysign(T(0), d);
            }
            recover = true;
        }
        if (::asc::std::isinf(c) || ::asc::std::isinf(d)) {
            c = ::asc::std::copysign(::asc::std::isinf(c) ? T(1) : T(0), c);
            d = ::asc::std::copysign(::asc::std::isinf(d) ? T(1) : T(0), d);
            if (::asc::std::isnan(a)) {
                a = ::asc::std::copysign(T(0), a);
            }
            if (::asc::std::isnan(b)) {
                b = ::asc::std::copysign(T(0), b);
            }
            recover = true;
        }
        if (!recover &&
            (::asc::std::isinf(parts.__ac) || ::asc::std::isinf(parts.__bd) || ::asc::std::isinf(parts.__ad) ||
                ::asc::std::isinf(parts.__bc))) {
            if (::asc::std::isnan(a)) {
                a = ::asc::std::copysign(T(0), a);
            }
            if (::asc::std::isnan(b)) {
                b = ::asc::std::copysign(T(0), b);
            }
            if (::asc::std::isnan(c)) {
                c = ::asc::std::copysign(T(0), c);
            }
            if (::asc::std::isnan(d)) {
                d = ::asc::std::copysign(T(0), d);
            }
            recover = true;
        }
        if (recover) {
            const auto recovered = ::asc::std::__complex_calculate_partials(a, b, c, d);
            x = numeric_limits<T>::infinity() *
                (recovered.__ac - recovered.__bd);  // NOLINT(build/include_what_you_use)
            y = numeric_limits<T>::infinity() *
                (recovered.__ad + recovered.__bc);  // NOLINT(build/include_what_you_use)
        }
    }
    return {x, y};
}

// Smith's ratio scaling: dividing by the larger-magnitude component first
// avoids forming c*c + d*d (which overflows for finite large operands) and
// keeps the infinite/zero divisor special values exact.
template <class T>
CANN_ASC_STL_API constexpr complex<T> operator/(const complex<T>& left, const complex<T>& right) noexcept
{
    const T a = left.real(), b = left.imag(), c = right.real(), d = right.imag();
    if (c == T(0) && d == T(0)) {
        const T inf = numeric_limits<T>::infinity();  // NOLINT(build/include_what_you_use)
        return {::asc::std::copysign(inf, c) * a, ::asc::std::copysign(inf, c) * b};
    }
    if (::asc::std::isinf(c) || ::asc::std::isinf(d)) {
        const T cr = ::asc::std::isinf(c) ? ::asc::std::copysign(T(1), c) : T(0);
        const T dr = ::asc::std::isinf(d) ? ::asc::std::copysign(T(1), d) : T(0);
        return {T(0) * (a * cr + b * dr), T(0) * (b * cr - a * dr)};
    }
    if (::asc::std::fabs(c) >= ::asc::std::fabs(d)) {
        const T r = d / c;
        const T ac = a / c;
        const T bc = b / c;
        const T den = T(1) + r * r;
        return {(ac + bc * r) / den, (bc - ac * r) / den};
    }
    const T r = c / d;
    const T ad = a / d;
    const T bd = b / d;
    const T den = T(1) + r * r;
    return {(ad * r + bd) / den, (bd * r - ad) / den};
}

template <class T>
CANN_ASC_STL_API constexpr complex<T>& complex<T>::operator*=(complex rhs) noexcept
{
    *this = *this * rhs;
    return *this;
}
template <class T>
CANN_ASC_STL_API constexpr complex<T>& complex<T>::operator/=(complex rhs) noexcept
{
    *this = *this / rhs;
    return *this;
}

// Scalar mixed arithmetic.
template <class T>
CANN_ASC_STL_API constexpr complex<T> operator+(const complex<T>& left, const T& right) noexcept
{
    return {left.real() + right, left.imag()};
}
template <class T>
CANN_ASC_STL_API constexpr complex<T> operator+(const T& left, const complex<T>& right) noexcept
{
    return right + left;
}
template <class T>
CANN_ASC_STL_API constexpr complex<T> operator-(const complex<T>& left, const T& right) noexcept
{
    return {left.real() - right, left.imag()};
}
template <class T>
CANN_ASC_STL_API constexpr complex<T> operator-(const T& left, const complex<T>& right) noexcept
{
    return {left - right.real(), -right.imag()};
}
template <class T>
CANN_ASC_STL_API constexpr complex<T> operator*(const complex<T>& left, const T& right) noexcept
{
    return {left.real() * right, left.imag() * right};
}
template <class T>
CANN_ASC_STL_API constexpr complex<T> operator*(const T& left, const complex<T>& right) noexcept
{
    return right * left;
}
template <class T>
CANN_ASC_STL_API constexpr complex<T> operator/(const complex<T>& left, const T& right) noexcept
{
    return {left.real() / right, left.imag() / right};
}
template <class T>
CANN_ASC_STL_API constexpr complex<T> operator/(const T& left, const complex<T>& right) noexcept
{
    return complex<T>(left) / right;
}
template <class T>
CANN_ASC_STL_API constexpr complex<T> operator+(const complex<T>& value) noexcept
{
    return value;
}
template <class T>
CANN_ASC_STL_API constexpr complex<T> operator-(const complex<T>& value) noexcept
{
    return {-value.real(), -value.imag()};
}

template <class T>
CANN_ASC_STL_API constexpr bool operator==(const complex<T>& left, const complex<T>& right) noexcept
{
    return left.real() == right.real() && left.imag() == right.imag();
}
template <class T>
CANN_ASC_STL_API constexpr bool operator==(const complex<T>& left, const T& right) noexcept
{
    return left.real() == right && left.imag() == T(0);
}
template <class T>
CANN_ASC_STL_API constexpr bool operator!=(const complex<T>& left, const complex<T>& right) noexcept
{
    return !(left == right);
}
#if __cplusplus <= 201703L
template <class T>
CANN_ASC_STL_API constexpr bool operator==(const T& left, const complex<T>& right) noexcept
{
    return right == left;
}
template <class T>
CANN_ASC_STL_API constexpr bool operator!=(const complex<T>& left, const T& right) noexcept
{
    return !(left == right);
}
template <class T>
CANN_ASC_STL_API constexpr bool operator!=(const T& left, const complex<T>& right) noexcept
{
    return !(right == left);
}
#endif

template <class T>
CANN_ASC_STL_API constexpr T real(const complex<T>& value) noexcept
{
    return value.real();
}
template <class T>
CANN_ASC_STL_API constexpr T imag(const complex<T>& value) noexcept
{
    return value.imag();
}
// Scalar overloads keep the C++ interface shape: integral arguments promote
// to double, floating-point arguments keep their own type.
template <class T, enable_if_t<is_integral_v<T>, int> = 0>
CANN_ASC_STL_API constexpr double real(T value) noexcept
{
    return static_cast<double>(value);
}
template <class T, enable_if_t<is_floating_point_v<T>, int> = 0>
CANN_ASC_STL_API constexpr T real(T value) noexcept
{
    return value;
}
template <class T, enable_if_t<is_integral_v<T>, int> = 0>
CANN_ASC_STL_API constexpr double imag(T) noexcept
{
    return 0;
}
template <class T, enable_if_t<is_floating_point_v<T>, int> = 0>
CANN_ASC_STL_API constexpr T imag(T value) noexcept
{
    return T(0);
}

template <class T>
CANN_ASC_STL_API constexpr T norm(const complex<T>& value) noexcept
{
    return value.real() * value.real() + value.imag() * value.imag();
}
template <class T>
CANN_ASC_STL_API constexpr complex<T> conj(const complex<T>& value) noexcept
{
    return complex<T>(value.real(), -value.imag());
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___COMPLEX_COMPLEX_H
