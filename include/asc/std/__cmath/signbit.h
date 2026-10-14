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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_SIGNBIT_H
#define CANN_ASC_STL_ASC_STD___CMATH_SIGNBIT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__floating_point/fp.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_extended_arithmetic.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/limits>
#include <limits>

CANN_ASC_STL_BEGIN_NAMESPACE

//! @brief Reports whether @p x is negative.
//!
//! Unsigned types have no sign and report false. Signed integral types
//! compare against zero. Floating-point types inspect the sign bit
//! through their storage representation — bit-exact with the reference
//! semantics, so negative zero and NaNs carrying a set sign bit report
//! true, and no floating-point arithmetic is involved on any path.
//! Formats beyond the delivered storage vocabulary (x87 fp80 / binary128
//! native long double) classify through the compiler's bit-exact signbit
//! builtin, which reads the same sign bit.
template <class Tp, ::asc::std::enable_if_t<__is_extended_arithmetic_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool signbit(Tp x) noexcept
{
    if constexpr (is_integral_v<Tp>) {
        if constexpr (numeric_limits<Tp>::is_signed) {
            return x < 0;
        } else {
            return false;
        }
    } else if constexpr (__fp_format_of_v<Tp> == __fp_format::__binary16 ||  // NOLINT(readability/braces)
        __fp_format_of_v<Tp> == __fp_format::__bfloat16 || __fp_format_of_v<Tp> == __fp_format::__binary32 ||
        __fp_format_of_v<Tp> == __fp_format::__binary64) {
        return (::asc::std::__fp_get_storage(x) & __fp_sign_mask_of_v<Tp>) != 0;
    } else {
        return __builtin_signbit(x);
    }
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_SIGNBIT_H
