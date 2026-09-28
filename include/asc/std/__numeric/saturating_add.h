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

#ifndef CANN_ASC_STL_ASC_STD___NUMERIC_SATURATING_ADD_H
#define CANN_ASC_STL_ASC_STD___NUMERIC_SATURATING_ADD_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/__detail/execution_space.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__numeric/saturating_cast.h>
#include <asc/std/__type_traits/is_integer.h>
#include <asc/std/__type_traits/is_signed.h>
#include <asc/std/cstdint>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __saturating_add_detail {

// The saturation bounds are derived through the delivered saturating_cast so
// the exact limits of every supported width come from one audited conversion
// path.  Overflow itself is decided by bound comparisons only: the compared
// expressions cannot overflow for the operand signs that reach them, so no
// signed-overflow undefined behaviour exists on any path.
template <class T>
CANN_ASC_STL_API constexpr T add_maximum() noexcept
{
    return saturating_cast<T>(UINT64_MAX);
}

template <class T>
CANN_ASC_STL_API constexpr T add_minimum() noexcept
{
    return saturating_cast<T>(INT64_MIN);
}

}  // namespace __saturating_add_detail

template <class T>
CANN_ASC_STL_API constexpr T saturating_add(T left, T right) noexcept
{
    static_assert(__is_integer_v<T>, "saturating_add requires an integer type");
    if constexpr (is_signed_v<T>) {
        constexpr T maximum = __saturating_add_detail::add_maximum<T>();
        constexpr T minimum = __saturating_add_detail::add_minimum<T>();
        if (right > T(0) ? left > maximum - right : left < minimum - right) {
            return right > T(0) ? maximum : minimum;
        }
        return T(left + right);
    } else {
        const T sum = T(left + right);
        return sum < left ? T(~T(0)) : sum;
    }
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___NUMERIC_SATURATING_ADD_H
