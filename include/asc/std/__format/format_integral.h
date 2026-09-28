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

#ifndef CANN_ASC_STL_ASC_STD___FORMAT_FORMAT_INTEGRAL_H
#define CANN_ASC_STL_ASC_STD___FORMAT_FORMAT_INTEGRAL_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__charconv/to_chars.h>
#include <asc/std/__cmath/uabs.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/always_false.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_signed.h>
#include <asc/std/__type_traits/make_nbit_int.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/__utility/cmp.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/to_underlying.h>
#include <asc/std/climits>

#if CANN_ASC_STL_DETAIL_HAS_CXX20()

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __format_detail {
template <class T>
CANN_ASC_STL_API constexpr __SIZE_TYPE__ integral_digits(char* output, T value, unsigned int base, bool upper) noexcept
{
    using unsigned_type = make_unsigned_t<T>;
    unsigned_type magnitude = static_cast<unsigned_type>(value);
    bool negative = false;
    if constexpr (is_signed_v<T>) {
        negative = value < 0;
        if (negative) {
            magnitude = unsigned_type{0} - magnitude;
        }
    }
    char reverse[64]{};
    __SIZE_TYPE__ count = 0;
    do {
        const unsigned int digit = static_cast<unsigned int>(magnitude % base);
        reverse[count++] = static_cast<char>(digit < 10 ? '0' + digit : (upper ? 'A' : 'a') + digit - 10);
        magnitude = static_cast<unsigned_type>(magnitude / base);
    } while (magnitude != 0);
    __SIZE_TYPE__ written = 0;
    if (negative) {
        output[written++] = '-';
    }
    while (count != 0) {
        output[written++] = reverse[--count];
    }
    return written;
}
}  // namespace __format_detail

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_DETAIL_HAS_CXX20()

#endif  // CANN_ASC_STL_ASC_STD___FORMAT_FORMAT_INTEGRAL_H
