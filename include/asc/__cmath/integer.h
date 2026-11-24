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

#ifndef CANN_ASC_STL_ASC___CMATH_INTEGER_H
#define CANN_ASC_STL_ASC___CMATH_INTEGER_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_constant_evaluated.h>
#include <asc/std/__type_traits/is_signed.h>
#include <asc/std/__type_traits/is_unsigned.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/limits>

namespace asc::detail {

template <class T>
inline constexpr bool cmath_integer_v =
    (::asc::std::is_same_v<T, signed char> || ::asc::std::is_same_v<T, unsigned char> ||
        ::asc::std::is_same_v<T, short> || ::asc::std::is_same_v<T, unsigned short> || ::asc::std::is_same_v<T, int> ||
        ::asc::std::is_same_v<T, unsigned int> || ::asc::std::is_same_v<T, long> ||
        ::asc::std::is_same_v<T, unsigned long> || ::asc::std::is_same_v<T, long long> ||
        ::asc::std::is_same_v<T, unsigned long long>) &&
    (::asc::std::numeric_limits<T>::digits + ::asc::std::is_signed_v<T> <= 64);

template <class T>
using cmath_integer_t = ::asc::std::enable_if_t<cmath_integer_v<T>, int>;

// A violated precondition is not a core constant expression. No runtime
// termination behavior is promised (Device trap may require unavailable abort).
// Runtime validity is the caller's contract, not a generated error-handling path.
CANN_ASC_STL_API constexpr void cmath_require(bool condition) noexcept
{
    if (::asc::std::__default_is_constant_evaluated() && !condition) {
        __builtin_unreachable();
    }
}

template <class T>
CANN_ASC_STL_API constexpr void cmath_division_domain(T a, T b) noexcept
{
    cmath_require(b != T{0});
    if constexpr (::asc::std::is_signed_v<T>) {
        if (a == ::asc::std::numeric_limits<T>::min() && b == T{-1}) {
            cmath_require(a >= -::asc::std::numeric_limits<T>::max());
        }
    }
}

template <class T>
CANN_ASC_STL_API constexpr T cmath_product(T a, T b) noexcept
{
    // Final representability is a runtime precondition. Checking it here is
    // only needed to reject invalid constant expressions; valid runtime powers
    // need no extra 64-bit divisions beyond their actual multiplications.
    if (::asc::std::__default_is_constant_evaluated()) {
        constexpr T highest = ::asc::std::numeric_limits<T>::max();
        if constexpr (::asc::std::is_signed_v<T>) {
            constexpr T lowest = ::asc::std::numeric_limits<T>::min();
            if (a > 0 && b > 0)
                cmath_require(a <= highest / b);
            if (a > 0 && b < 0)
                cmath_require(b >= lowest / a);
            if (a < 0 && b > 0)
                cmath_require(a >= lowest / b);
            if (a < 0 && b < 0)
                cmath_require(a >= highest / b);
        } else if (b != 0) {
            cmath_require(a <= highest / b);
        }
    }
    return static_cast<T>(a * b);
}

}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___CMATH_INTEGER_H
