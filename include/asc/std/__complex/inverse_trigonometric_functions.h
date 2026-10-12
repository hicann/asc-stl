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

#ifndef CANN_ASC_STL_ASC_STD___COMPLEX_INVERSE_TRIGONOMETRIC_FUNCTIONS_H
#define CANN_ASC_STL_ASC_STD___COMPLEX_INVERSE_TRIGONOMETRIC_FUNCTIONS_H

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
#include <asc/std/__cmath/fma.h>
#include <asc/std/__cmath/isinf.h>
#include <asc/std/__cmath/isnan.h>
#include <asc/std/__cmath/signbit.h>
#include <asc/std/__complex/complex.h>
#include <asc/std/__complex/inverse_hyperbolic_functions.h>
#include <asc/std/__type_traits/is_extended_floating_point.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/limits>
#include <asc/std/numbers>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> asin(const complex<T>& value) noexcept
{
    const complex<T> result = ::asc::std::asinh(complex<T>(-value.imag(), value.real()));
    return {result.imag(), -result.real()};
}

// acos via the first-quadrant acosh: the angle comes from acosh's imaginary
// part, and the negative-real-axis correction adds pi back through two
// fma-friendly factors, so the real part keeps full precision instead of
// subtracting a pre-rounded pi/2 from asin's result.
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> acos(const complex<T>& value) noexcept
{
    // Get both real and imag parts >= +0.0
    const bool real_neg = ::asc::std::signbit(value.real());
    const bool imag_neg = ::asc::std::signbit(value.imag());

    const complex<T> x_first_quadrant{::asc::std::fabs(value.real()), ::asc::std::fabs(value.imag())};

    const complex<T> acosh_out = ::asc::std::acosh(x_first_quadrant);

    T ans_real = acosh_out.imag();
    T ans_imag = -acosh_out.real();

    if (real_neg) {
        // Values that multiply to an extra-accurate value of pi.
        constexpr T pi_hi = is_same_v<T, float> ? 1.866378903f : static_cast<T>(1.56226695361364598113596002804);
        constexpr T pi_lo = is_same_v<T, float> ? 1.683255553f : static_cast<T>(2.01091922627118435684678843245);
        ans_real = ::asc::std::fma(pi_hi, pi_lo, -ans_real);
    }

    if (imag_neg) {
        ans_imag = -ans_imag;
    }

    return complex<T>{ans_real, ans_imag};
}

template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> atan(const complex<T>& value) noexcept
{
    const complex<T> result = ::asc::std::atanh(complex<T>(-value.imag(), value.real()));
    return {result.imag(), -result.real()};
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___COMPLEX_INVERSE_TRIGONOMETRIC_FUNCTIONS_H
