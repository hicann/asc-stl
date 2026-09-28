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

#ifndef CANN_ASC_STL_ASC_STD___NUMERIC_SATURATING_MUL_H
#define CANN_ASC_STL_ASC_STD___NUMERIC_SATURATING_MUL_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/is_integer.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
CANN_ASC_STL_API constexpr T saturating_mul(T left, T right) noexcept
{
    static_assert(__is_integer_v<T>, "saturating_mul requires an integer type");
    T result{};
#if defined(__clang__) || defined(__GNUC__)
    if (__builtin_mul_overflow(left, right, &result)) {
        if (!(T(-1) < T(0)))
            return T(~T(0));
        const bool negative = (left < T(0)) != (right < T(0));
        if (negative)
            return T(-((T(1) << (sizeof(T) * 8 - 2)) - 1 + (T(1) << (sizeof(T) * 8 - 2))) - 1);
        return T((T(1) << (sizeof(T) * 8 - 2)) - 1 + (T(1) << (sizeof(T) * 8 - 2)));
    }
    return result;
#else
    return left * right;
#endif
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___NUMERIC_SATURATING_MUL_H
