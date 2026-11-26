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

#ifndef ASC_STL_TEST_COMPLEX_DEVICE_CHECKS_H
#define ASC_STL_TEST_COMPLEX_DEVICE_CHECKS_H

#include <asc/std/complex>

namespace asc_stl_test_complex {
CANN_ASC_STL_API bool near_principal(float actual, float expected)
{
    // Allow twelve binary32 epsilons for the elementary operations in the principal-value formula.
    const float scale = ::asc::std::fabs(expected) > 1.0F ? ::asc::std::fabs(expected) : 1.0F;
    return ::asc::std::fabs(actual - expected) <= 12 * ::asc::std::numeric_limits<float>::epsilon() * scale;
}

CANN_ASC_STL_API bool near_parts(const ::asc::std::complex<float>& actual, float real, float imag)
{
    return near_principal(actual.real(), real) && near_principal(actual.imag(), imag);
}

// Keep each principal-value evaluation shared by the interior and branch-cut probes.
CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE bool asinh_near(float x, float y, float real, float imag)
{
    return near_parts(::asc::std::asinh(::asc::std::complex<float>(x, y)), real, imag);
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE bool acosh_near(float x, float y, float real, float imag)
{
    return near_parts(::asc::std::acosh(::asc::std::complex<float>(x, y)), real, imag);
}

CANN_ASC_STL_API int check_inverse_hyperbolic(float two)
{
    // The expected principal values are rounded from independent binary64 evaluations.
    const float half = two * 0.25F;
    if (!asinh_near(half, 1.0F, 0.732857676F, 0.895907481F) || !acosh_near(half, 1.0F, 0.926133031F, 1.22135726F))
        return 10;
    const float minus_three = -1.5F * two;
    if (!asinh_near(minus_three, two, -1.98338703F, 0.570652784F) ||
        !acosh_near(minus_three, two, 1.96863793F, 2.53545483F))
        return 11;
    if (!asinh_near(0.0F, two, 1.31695790F, 1.57079633F) || !asinh_near(-0.0F, two, -1.31695790F, 1.57079633F))
        return 12;
    if (!acosh_near(-0.75F * two, 0.0F, 0.962423650F, 3.14159265F) ||
        !acosh_near(-0.75F * two, -0.0F, 0.962423650F, -3.14159265F))
        return 13;
    return 0;
}

CANN_ASC_STL_API int check(int seed = 7)
{
    namespace s = ::asc::std;
    using z = s::complex<float>;
    const float two = static_cast<float>(seed - 5);
    const z a(two, -1), b(1, two);
    if (a + b != z(3, 1) || a - b != z(1, -3) || a * b != z(4, 3) || a / b != z(0, -1))
        return 1;
    if (+a != a || -a != z(-2, 1) || a + two != z(4, -1) || two + a != z(4, -1) || a - two != z(0, -1) ||
        two - a != z(0, 1) || a * two != z(4, -2) || two * a != z(4, -2) || a / two != z(1, -0.5F) ||
        two / z(0, two) != z(0, -1))
        return 2;
    const float ten = 5 * two;
    if (ten / z(2 * two, two) != z(2, -1) || ten / z(-two, 2 * two) != z(-1, -2))
        return 15;
    // Both Smith branches overflow an intermediate sum although the quotient is finite.
    const float large = 0x1.8p127F;
    const z equal_scale = z(large, large) / z(two * 0.5F, 1.0F);
    const z imag_scale = z(large, large) / z(two * 0.25F, 1.0F);
    if (equal_scale != z(large, 0) || !near_principal(imag_scale.real() / large, 1.2F) ||
        !near_principal(imag_scale.imag() / large, -0.4F))
        return 16;
    z value{};
    value = a;
    value += b;
    value -= b;
    value *= b;
    if (value != z(4, 3))
        return 17;
    value /= b;
    if (value != a)
        return 3;
    value = two;
    value += two;
    value -= two;
    value *= two;
    value /= two;
    if (!(value == two) || !(two == value) || two != value || value != two || s::real(value) != two ||
        s::imag(value) != 0 || s::real(two) != two || s::imag(two) != 0)
        return 4;
    value.real(-two);
    value.imag(two);
    volatile z vol;
    vol.real(two);
    vol.imag(-two);
    if (vol.real() != two || vol.imag() != -two || value != z(-2, 2))
        return 5;
    s::get<0>(value) = two;
    const z frozen = value;
    if (s::get<1>(frozen) != two || s::get<0>(z(two, 4)) != two || s::get<1>(static_cast<const z&&>(frozen)) != two)
        return 6;
    if (s::conj(a) != z(2, 1) || s::conj(two) != z(2, 0) || s::norm(a) != 5 || s::norm(two) != 4 ||
        s::polar(two) != z(2, 0) || s::polar(two, 0.0F) != z(2, 0) || s::abs(z(3, 4)) != 5 || s::arg(z(1, 0)) != 0 ||
        s::arg(two) != 0 || s::proj(two) != z(2, 0))
        return 7;
    const float pi = 0x1.921fb6p+1F;
    const float infinity = s::numeric_limits<float>::infinity();
    if (s::signbit(s::arg(two)) || s::signbit(s::arg(0.0F)) || s::arg(0.0F) != 0.0F || s::arg(infinity) != 0.0F ||
        s::signbit(s::arg(infinity)) || s::arg(-two) != pi || s::arg(-0.0F) != pi || s::arg(-infinity) != pi ||
        !s::isnan(s::arg(s::numeric_limits<float>::quiet_NaN())))
        return 14;
    const z reflected = s::proj(z(-s::numeric_limits<float>::infinity(), -two));
    if (!s::isinf(reflected.real()) || s::signbit(reflected.real()) || reflected.imag() != 0 ||
        !s::signbit(reflected.imag()))
        return 8;
    const z upper = s::sqrt(z(-4.0F, 0.0F)), lower = s::sqrt(z(-4.0F, -0.0F));
    if (upper != z(0, 2) || lower != z(0, -2))
        return 9;
    return check_inverse_hyperbolic(two);
}
}  // namespace asc_stl_test_complex

#endif  // ASC_STL_TEST_COMPLEX_DEVICE_CHECKS_H
