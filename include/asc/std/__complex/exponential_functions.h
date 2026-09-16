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

#ifndef CANN_ASC_STL_ASC_STD___COMPLEX_EXPONENTIAL_FUNCTIONS_H
#define CANN_ASC_STL_ASC_STD___COMPLEX_EXPONENTIAL_FUNCTIONS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__cmath/copysign.h>
#include <asc/std/__cmath/isfinite.h>
#include <asc/std/__cmath/isinf.h>
#include <asc/std/__cmath/isnan.h>
#include <asc/std/__cmath/sincos.h>
#include <asc/std/__cmath/trigonometric_functions.h>
#include <asc/std/__complex/complex.h>
#include <asc/std/__complex/logarithms.h>
#include <asc/std/__complex/vector_support.h>
#include <asc/std/__type_traits/common_type.h>
#include <asc/std/limits>
#include <asc/std/numbers>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> exp(const complex<T>& value) noexcept
{
    const T scale = CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(expf, __builtin_expf, (value.real()));
    const auto angle = ::asc::std::__sincos(value.imag());
    return {scale * angle.cos, scale * angle.sin};
}
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> pow(
    const complex<T>& base, const complex<T>& exponent) noexcept
{
    return ::asc::std::exp(exponent * ::asc::std::log(base));
}
template <class T, class U>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<common_type_t<T, U>> pow(
    const complex<T>& base, const U& exponent) noexcept
{
    using R = common_type_t<T, U>;
    return ::asc::std::pow(complex<R>(base.real(), base.imag()), complex<R>(static_cast<R>(exponent)));
}
template <class T, class U>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<common_type_t<T, U>> pow(
    const T& base, const complex<U>& exponent) noexcept
{
    using R = common_type_t<T, U>;
    return ::asc::std::pow(complex<R>(static_cast<R>(base)), complex<R>(exponent.real(), exponent.imag()));
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___COMPLEX_EXPONENTIAL_FUNCTIONS_H
