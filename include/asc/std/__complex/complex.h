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
#include <asc/std/__type_traits/is_same.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
struct __get_complex_impl;

template <class T>
class complex {
    static_assert(is_same_v<T, float>, "ASC-STL complex supports float only");

public:
    using value_type = T;
    CANN_ASC_STL_API constexpr complex(T real = T(), T imag = T()) noexcept : real_(real), imag_(imag)
    {}
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
    CANN_ASC_STL_API constexpr complex& operator*=(complex rhs) noexcept
    {
        const T r = real_ * rhs.real_ - imag_ * rhs.imag_;
        imag_ = real_ * rhs.imag_ + imag_ * rhs.real_;
        real_ = r;
        return *this;
    }
    CANN_ASC_STL_API constexpr complex& operator/=(complex rhs) noexcept
    {
        const T d = rhs.real_ * rhs.real_ + rhs.imag_ * rhs.imag_;
        const T r = (real_ * rhs.real_ + imag_ * rhs.imag_) / d;
        imag_ = (imag_ * rhs.real_ - real_ * rhs.imag_) / d;
        real_ = r;
        return *this;
    }

private:
    friend struct __get_complex_impl<T>;

    T real_;
    T imag_;
};
template <class T>
CANN_ASC_STL_API constexpr complex<T> operator+(complex<T> lhs, complex<T> rhs) noexcept
{
    return lhs += rhs;
}
template <class T>
CANN_ASC_STL_API constexpr complex<T> operator-(complex<T> lhs, complex<T> rhs) noexcept
{
    return lhs -= rhs;
}
template <class T>
CANN_ASC_STL_API constexpr complex<T> operator*(complex<T> lhs, complex<T> rhs) noexcept
{
    return lhs *= rhs;
}
template <class T>
CANN_ASC_STL_API constexpr complex<T> operator/(complex<T> lhs, complex<T> rhs) noexcept
{
    return lhs /= rhs;
}
template <class T>
CANN_ASC_STL_API constexpr bool operator==(complex<T> lhs, complex<T> rhs) noexcept
{
    return lhs.real() == rhs.real() && lhs.imag() == rhs.imag();
}
template <class T>
CANN_ASC_STL_API constexpr bool operator!=(complex<T> lhs, complex<T> rhs) noexcept
{
    return !(lhs == rhs);
}
template <class T>
CANN_ASC_STL_API constexpr T real(complex<T> value) noexcept
{
    return value.real();
}
template <class T>
CANN_ASC_STL_API constexpr T imag(complex<T> value) noexcept
{
    return value.imag();
}
template <class T>
CANN_ASC_STL_API constexpr T norm(complex<T> value) noexcept
{
    return value.real() * value.real() + value.imag() * value.imag();
}
template <class T>
CANN_ASC_STL_API constexpr complex<T> conj(complex<T> value) noexcept
{
    return complex<T>(value.real(), -value.imag());
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___COMPLEX_COMPLEX_H
