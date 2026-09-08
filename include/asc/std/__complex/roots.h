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

#ifndef CANN_ASC_STL_ASC_STD___COMPLEX_ROOTS_H
#define CANN_ASC_STL_ASC_STD___COMPLEX_ROOTS_H

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
#include <asc/std/__cmath/isinf.h>
#include <asc/std/__cmath/isnan.h>
#include <asc/std/__complex/complex.h>
#include <asc/std/__complex/math.h>
#include <asc/std/__floating_point/mask.h>
#include <asc/std/limits>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> sqrt(const complex<T>& value) noexcept
{
    if (value.real() == T{} && value.imag() == T{}) {
        return value;
    }
    const T magnitude = ::asc::std::abs(value);
    const T real_value =
        CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(sqrtf, __builtin_sqrtf, ((magnitude + value.real()) / T{2}));
    const T imag_magnitude =
        CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(sqrtf, __builtin_sqrtf, ((magnitude - value.real()) / T{2}));
    const T imag_value = ::asc::std::copysign(imag_magnitude, value.imag());
    return {real_value, imag_value};
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___COMPLEX_ROOTS_H
