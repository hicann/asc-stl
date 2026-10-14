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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_UABS_H
#define CANN_ASC_STL_ASC_STD___CMATH_UABS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__cmath/neg.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_signed.h>
#include <asc/std/__type_traits/make_unsigned.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// Unsigned-view absolute value of an integral argument. The result type is
// derived through make_unsigned, so a single definition covers every
// integral type and future additions instead of a hand-written
// specialization table; bool keeps a readable diagnostic instead of an
// incomplete-type error. The result type is deduced in the body so the
// static_assert is reached before make_unsigned<bool> substitution drops
// the candidate from the overload set.
template <class T, enable_if_t<is_integral<T>::value, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr auto __uabs(T value) noexcept
{
    static_assert(!is_same<T, bool>::value, "__uabs is not defined for bool");
    using unsigned_type = make_unsigned_t<T>;
    if constexpr (is_signed<T>::value) {
        return value < T(0) ? static_cast<unsigned_type>(__neg(value)) : static_cast<unsigned_type>(value);
    } else {
        return static_cast<unsigned_type>(value);
    }
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_UABS_H
