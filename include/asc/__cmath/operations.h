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

#ifndef CANN_ASC_STL_ASC___CMATH_OPERATIONS_H
#define CANN_ASC_STL_ASC___CMATH_OPERATIONS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

namespace asc::detail {

// Extension math backend vocabulary shared by the later public <asc/cmath>
// operations: the classification and sign primitives are expressed through
// compiler builtins so Host, D-SIMD and D-SIMT share one spelling.  The
// delivered float math itself is owned by the standard __cmath backend.
CANN_ASC_STL_API constexpr bool math_is_nan(float value) noexcept
{
    return __builtin_isnan(value);
}

CANN_ASC_STL_API constexpr bool math_is_inf(float value) noexcept
{
    return __builtin_isinf(value);
}

CANN_ASC_STL_API bool math_sign_bit(float value) noexcept
{
    return __builtin_signbit(value);
}

CANN_ASC_STL_API constexpr float math_quiet_nan() noexcept
{
    return __builtin_nanf("");
}

CANN_ASC_STL_API constexpr float math_infinity() noexcept
{
    return __builtin_huge_valf();
}

// A zero input returns the input unchanged so the standard signed-zero
// contract survives backend dispatch.
CANN_ASC_STL_API constexpr float math_round_preserve_zero(float value) noexcept
{
    if (value == 0.0f || math_is_nan(value) || math_is_inf(value)) {
        return value;
    }
    return value > 0.0f ? __builtin_floorf(value) : -__builtin_floorf(-value);
}

}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___CMATH_OPERATIONS_H
