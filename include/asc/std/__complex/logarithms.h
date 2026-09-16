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

#ifndef CANN_ASC_STL_ASC_STD___COMPLEX_LOGARITHMS_H
#define CANN_ASC_STL_ASC_STD___COMPLEX_LOGARITHMS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__complex/arg.h>
#include <asc/std/__complex/complex.h>
#include <asc/std/__complex/math.h>
#include <asc/std/__floating_point/fp.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/numbers>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> log(const complex<T>& value) noexcept
{
    return {
        CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(logf, __builtin_logf, (::asc::std::abs(value))), ::asc::std::arg(value)};
}
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> log10(const complex<T>& value) noexcept
{
    const complex<T> result = ::asc::std::log(value);
    const T divisor = static_cast<T>(2.302585092994045684F);
    return {result.real() / divisor, result.imag() / divisor};
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___COMPLEX_LOGARITHMS_H
