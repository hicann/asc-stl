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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_EXPONENTIAL_FUNCTIONS_H
#define CANN_ASC_STL_ASC_STD___CMATH_EXPONENTIAL_FUNCTIONS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__cmath/backend.h>

CANN_ASC_STL_BEGIN_NAMESPACE

#define CANN_ASC_STL_DETAIL_UNARY_FLOAT(name)                                          \
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API float name(float x) noexcept     \
    {                                                                                  \
        return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(name##f, __builtin_##name##f, (x)); \
    }                                                                                  \
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API float name##f(float x) noexcept  \
    {                                                                                  \
        return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(name##f, __builtin_##name##f, (x)); \
    }
CANN_ASC_STL_DETAIL_UNARY_FLOAT(exp)
CANN_ASC_STL_DETAIL_UNARY_FLOAT(exp2)
CANN_ASC_STL_DETAIL_UNARY_FLOAT(expm1)
#undef CANN_ASC_STL_DETAIL_UNARY_FLOAT
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API float pow(float base, float exponent) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(powf, __builtin_powf, (base, exponent));
}
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API float powf(float base, float exponent) noexcept
{
    return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(powf, __builtin_powf, (base, exponent));
}
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API float frexp(float x, int* e) noexcept
{
    return __builtin_frexpf(x, e);
}
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API float frexpf(float x, int* e) noexcept
{
    return __builtin_frexpf(x, e);
}
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API float ldexp(float x, int e) noexcept
{
    return __builtin_ldexpf(x, e);
}
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API float ldexpf(float x, int e) noexcept
{
    return __builtin_ldexpf(x, e);
}
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API float modf(float x, float* i) noexcept
{
    return __builtin_modff(x, i);
}
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API float modff(float x, float* i) noexcept
{
    return __builtin_modff(x, i);
}
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API float scalbn(float x, int e) noexcept
{
    return __builtin_scalbnf(x, e);
}
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API float scalbnf(float x, int e) noexcept
{
    return __builtin_scalbnf(x, e);
}
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API float scalbln(float x, long e) noexcept
{
    return __builtin_scalblnf(x, e);
}
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API float scalblnf(float x, long e) noexcept
{
    return __builtin_scalblnf(x, e);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_EXPONENTIAL_FUNCTIONS_H
