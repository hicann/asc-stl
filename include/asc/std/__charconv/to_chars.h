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

#ifndef CANN_ASC_STL_ASC_STD___CHARCONV_TO_CHARS_H
#define CANN_ASC_STL_ASC_STD___CHARCONV_TO_CHARS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__charconv/to_chars_result.h>
#include <asc/std/__cmath/uabs.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__cstddef/types.h>
#include <asc/std/__type_traits/always_false.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/is_floating_point.h>
#include <asc/std/__type_traits/is_integer.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_signed.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/cstdint>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __charconv_detail {
template <class T>
CANN_ASC_STL_API to_chars_result __to_chars_integer(char* first, char* last, T value, int base) noexcept
{
    if (base < 2 || base > 36) {
        return {first, errc::invalid_argument};
    }
    using U = make_unsigned_t<T>;
    const bool negative = is_signed_v<T> && value < 0;
    U magnitude = negative ? U(0) - static_cast<U>(value) : static_cast<U>(value);
    char buffer[sizeof(U) * 8 + 1];
    char* output = buffer + sizeof(buffer);
    do {
        const unsigned int digit = static_cast<unsigned int>(magnitude % static_cast<U>(base));
        *--output = static_cast<char>(digit < 10 ? '0' + digit : 'a' + digit - 10);
        magnitude /= static_cast<U>(base);
    } while (magnitude != 0);
    if (negative) {
        *--output = '-';
    }
    const size_t length = static_cast<size_t>(buffer + sizeof(buffer) - output);
    if (static_cast<size_t>(last - first) < length) {
        return {last, errc::value_too_large};
    }
    for (size_t index = 0; index < length; ++index) {
        first[index] = output[index];
    }
    return {first + length, static_cast<errc>(0)};
}
}  // namespace __charconv_detail

template <class T, enable_if_t<__is_integer_v<T>, int> = 0>
CANN_ASC_STL_API to_chars_result to_chars(char* first, char* last, T value, int base = 10) noexcept
{
    return __charconv_detail::__to_chars_integer(first, last, value, base);
}
CANN_ASC_STL_API to_chars_result to_chars(char* first, char* last, char value, int base = 10) noexcept
{
    return __charconv_detail::__to_chars_integer(first, last, value, base);
}
CANN_ASC_STL_API to_chars_result to_chars(char* first, char* last, signed char value, int base = 10) noexcept
{
    return __charconv_detail::__to_chars_integer(first, last, value, base);
}
CANN_ASC_STL_API to_chars_result to_chars(char* first, char* last, unsigned char value, int base = 10) noexcept
{
    return __charconv_detail::__to_chars_integer(first, last, value, base);
}
to_chars_result to_chars(char*, char*, bool, int = 10) = delete;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHARCONV_TO_CHARS_H
