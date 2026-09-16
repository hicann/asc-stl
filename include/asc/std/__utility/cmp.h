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

#ifndef CANN_ASC_STL_ASC_STD___UTILITY_CMP_H
#define CANN_ASC_STL_ASC_STD___UTILITY_CMP_H

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
#include <asc/std/__type_traits/disjunction.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_integer.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_signed.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>
#include <asc/std/limits>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T, class U>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool cmp_equal(T left, U right) noexcept
{
    static_assert(__is_integer_v<T> && __is_integer_v<U>, "cmp_equal requires integer types");
    if constexpr (is_signed_v<T> == is_signed_v<U>) {
        return left == right;
    } else if constexpr (is_signed_v<T>) {
        return left >= 0 && make_unsigned_t<T>(left) == right;
    } else {
        return right >= 0 && left == make_unsigned_t<U>(right);
    }
}
template <class T, class U>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool cmp_not_equal(T left, U right) noexcept
{
    return !::asc::std::cmp_equal(left, right);
}
template <class T, class U>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool cmp_less(T left, U right) noexcept
{
    static_assert(__is_integer_v<T> && __is_integer_v<U>, "cmp_less requires integer types");
    if constexpr (is_signed_v<T> == is_signed_v<U>) {
        return left < right;
    } else if constexpr (is_signed_v<T>) {
        return left < 0 || make_unsigned_t<T>(left) < right;
    } else {
        return right >= 0 && left < make_unsigned_t<U>(right);
    }
}
template <class T, class U>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool cmp_greater(T left, U right) noexcept
{
    return ::asc::std::cmp_less(right, left);
}
template <class T, class U>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool cmp_less_equal(T left, U right) noexcept
{
    return !::asc::std::cmp_greater(left, right);
}
template <class T, class U>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool cmp_greater_equal(T left, U right) noexcept
{
    return !::asc::std::cmp_less(left, right);
}
template <class T, class U>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool in_range(U value) noexcept
{
    return ::asc::std::cmp_greater_equal(  // NOLINT(build/include_what_you_use)
               value, numeric_limits<T>::min()) &&
        ::asc::std::cmp_less_equal(            // NOLINT(build/include_what_you_use)
            value, numeric_limits<T>::max());  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___UTILITY_CMP_H
