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
#ifndef CANN_ASC_STL_ASC_STD___COMPLEX_ARG_H
#define CANN_ASC_STL_ASC_STD___COMPLEX_ARG_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__cmath/inverse_trigonometric_functions.h>
#include <asc/std/__complex/complex.h>
#include <asc/std/__type_traits/is_integral.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API T arg(const complex<T>& value) noexcept
{
    return ::asc::std::atan2(value.imag(), value.real());
}
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API float arg(float value) noexcept
{
    return ::asc::std::atan2(0.0F, value);
}
CANN_ASC_STL_API double arg(double) = delete;
CANN_ASC_STL_API long double arg(long double) = delete;
template <class T>
CANN_ASC_STL_API double arg(T) = delete;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___COMPLEX_ARG_H
