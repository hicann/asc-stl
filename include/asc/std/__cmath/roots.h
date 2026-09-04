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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_ROOTS_H
#define CANN_ASC_STL_ASC_STD___CMATH_ROOTS_H

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
#include <asc/std/__type_traits/is_integral.h>

CANN_ASC_STL_BEGIN_NAMESPACE

#define CANN_ASC_STL_DETAIL_ROOT(name, builtin_f, builtin_d, builtin_l)                   \
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API float name(float value) noexcept    \
    {                                                                                     \
        return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(name##f, builtin_f, (value));          \
    }                                                                                     \
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API float name##f(float value) noexcept \
    {                                                                                     \
        return CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(name##f, builtin_f, (value));          \
    }

CANN_ASC_STL_DETAIL_ROOT(sqrt, __builtin_sqrtf, __builtin_sqrt, __builtin_sqrtl)
CANN_ASC_STL_DETAIL_ROOT(cbrt, __builtin_cbrtf, __builtin_cbrt, __builtin_cbrtl)

#undef CANN_ASC_STL_DETAIL_ROOT

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_ROOTS_H
