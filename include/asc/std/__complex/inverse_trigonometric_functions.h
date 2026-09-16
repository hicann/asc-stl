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
#include <asc/std/limits>
#include <asc/std/numbers>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> asin(const complex<T>& value) noexcept
{
    const complex<T> result = ::asc::std::asinh(complex<T>(-value.imag(), value.real()));
    return {result.imag(), -result.real()};
}
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> acos(const complex<T>& value) noexcept
{
    const complex<T> result = ::asc::std::asin(value);
    return {static_cast<T>(1.570796326794896619F) - result.real(), -result.imag()};
}
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> atan(const complex<T>& value) noexcept
{
    const complex<T> result = ::asc::std::atanh(complex<T>(-value.imag(), value.real()));
    return {result.imag(), -result.real()};
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___COMPLEX_INVERSE_TRIGONOMETRIC_FUNCTIONS_H
