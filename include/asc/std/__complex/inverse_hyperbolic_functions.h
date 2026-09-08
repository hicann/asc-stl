/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#ifndef CANN_ASC_STL_ASC_STD___COMPLEX_INVERSE_HYPERBOLIC_FUNCTIONS_H
#define CANN_ASC_STL_ASC_STD___COMPLEX_INVERSE_HYPERBOLIC_FUNCTIONS_H

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
#include <asc/std/__cmath/trigonometric_functions.h>
#include <asc/std/__complex/complex.h>
#include <asc/std/__complex/exponential_functions.h>
#include <asc/std/__complex/logarithms.h>
#include <asc/std/__complex/roots.h>
#include <asc/std/limits>
#include <asc/std/numbers>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> asinh(const complex<T>& value) noexcept
{
    return ::asc::std::log(value + ::asc::std::sqrt(value * value + complex<T>(T{1})));
}
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> acosh(const complex<T>& value) noexcept
{
    return ::asc::std::log(
        value + ::asc::std::sqrt(value + complex<T>(T{1})) * ::asc::std::sqrt(value - complex<T>(T{1})));
}
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> atanh(const complex<T>& value) noexcept
{
    const complex<T> difference = ::asc::std::log(complex<T>(T{1}) + value) - ::asc::std::log(complex<T>(T{1}) - value);
    return {difference.real() / T{2}, difference.imag() / T{2}};
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___COMPLEX_INVERSE_HYPERBOLIC_FUNCTIONS_H
