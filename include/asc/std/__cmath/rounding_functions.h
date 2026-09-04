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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_ROUNDING_FUNCTIONS_H
#define CANN_ASC_STL_ASC_STD___CMATH_ROUNDING_FUNCTIONS_H

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
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_arithmetic.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/promote.h>

CANN_ASC_STL_BEGIN_NAMESPACE

#define CANN_ASC_STL_DETAIL_ROUND_FLOAT(name, builtin_f, builtin_d, builtin_l)            \
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API float name(float value) noexcept    \
    {                                                                                     \
        if (value == 0.0F)                                                                \
            return value;                                                                 \
        return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(name##f, builtin_f, (value));          \
    }                                                                                     \
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API float name##f(float value) noexcept \
    {                                                                                     \
        if (value == 0.0F)                                                                \
            return value;                                                                 \
        return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(name##f, builtin_f, (value));          \
    }

CANN_ASC_STL_DETAIL_ROUND_FLOAT(ceil, __builtin_ceilf, __builtin_ceil, __builtin_ceill)
CANN_ASC_STL_DETAIL_ROUND_FLOAT(floor, __builtin_floorf, __builtin_floor, __builtin_floorl)
CANN_ASC_STL_DETAIL_ROUND_FLOAT(trunc, __builtin_truncf, __builtin_trunc, __builtin_truncl)
CANN_ASC_STL_DETAIL_ROUND_FLOAT(round, __builtin_roundf, __builtin_round, __builtin_roundl)
CANN_ASC_STL_DETAIL_ROUND_FLOAT(rint, __builtin_rintf, __builtin_rint, __builtin_rintl)
CANN_ASC_STL_DETAIL_ROUND_FLOAT(nearbyint, __builtin_nearbyintf, __builtin_nearbyint, __builtin_nearbyintl)

#define CANN_ASC_STL_DETAIL_ROUND_INTEGER(name, result_type, builtin_f, builtin_d, builtin_l)   \
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API result_type name(float value) noexcept    \
    {                                                                                           \
        return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(name##f, builtin_f, (value));                \
    }                                                                                           \
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API result_type name##f(float value) noexcept \
    {                                                                                           \
        return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(name##f, builtin_f, (value));                \
    }

CANN_ASC_STL_DETAIL_ROUND_INTEGER(lrint, long, __builtin_lrintf, __builtin_lrint, __builtin_lrintl)
CANN_ASC_STL_DETAIL_ROUND_INTEGER(llrint, long long, __builtin_llrintf, __builtin_llrint, __builtin_llrintl)
CANN_ASC_STL_DETAIL_ROUND_INTEGER(lround, long, __builtin_lroundf, __builtin_lround, __builtin_lroundl)
CANN_ASC_STL_DETAIL_ROUND_INTEGER(llround, long long, __builtin_llroundf, __builtin_llround, __builtin_llroundl)

#undef CANN_ASC_STL_DETAIL_ROUND_INTEGER
#undef CANN_ASC_STL_DETAIL_ROUND_FLOAT

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_ROUNDING_FUNCTIONS_H
