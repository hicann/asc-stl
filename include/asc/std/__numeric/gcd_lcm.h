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

#ifndef CANN_ASC_STL_ASC_STD___NUMERIC_GCD_LCM_H
#define CANN_ASC_STL_ASC_STD___NUMERIC_GCD_LCM_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__cmath/uabs.h>
#include <asc/std/__type_traits/common_type.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_signed.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/limits>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
CANN_ASC_STL_API constexpr T __gcd_unsigned(T left, T right)
{
    while (right != 0) {
        const T remainder = left % right;
        left = right;
        right = remainder;
    }
    return left;
}

template <class T, class U>
CANN_ASC_STL_API constexpr common_type_t<T, U> gcd(T left, U right)
{
    static_assert(is_integral_v<T> && is_integral_v<U>, "gcd arguments must be integral");
    static_assert(!is_same_v<T, bool> && !is_same_v<U, bool>, "gcd arguments cannot be bool");
    using result_type = common_type_t<T, U>;
    using unsigned_type = make_unsigned_t<result_type>;
    return static_cast<result_type>(__gcd_unsigned(
        static_cast<unsigned_type>(::asc::std::__uabs(left)), static_cast<unsigned_type>(::asc::std::__uabs(right))));
}

template <class T, class U>
CANN_ASC_STL_API constexpr common_type_t<T, U> lcm(T left, U right)
{
    static_assert(is_integral_v<T> && is_integral_v<U>, "lcm arguments must be integral");
    static_assert(!is_same_v<T, bool> && !is_same_v<U, bool>, "lcm arguments cannot be bool");
    using result_type = common_type_t<T, U>;
    if (left == 0 || right == 0) {
        return 0;
    }
    return static_cast<result_type>(
        (::asc::std::__uabs(left) / ::asc::std::gcd(left, right)) * ::asc::std::__uabs(right));
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___NUMERIC_GCD_LCM_H
