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
#include <asc/std/__utility/to_underlying.h>
#include <asc/std/cstdint>

CANN_ASC_STL_BEGIN_NAMESPACE

// [charconv.syn] chars_format: when the facade <asc/std/charconv> is present
// it provides the definition uniformly (the facade guard macro serves as the
// presence flag); when this header is compiled standalone, the same
// definition is inlined behind a shared guard, shared with
// __charconv/from_chars.h to avoid redefinition.
#if !defined(CANN_ASC_STL_ASC_STD_CHARCONV) && !defined(CANN_ASC_STL_DETAIL_CHARCONV_CHARS_FORMAT_DEFINED)
#define CANN_ASC_STL_DETAIL_CHARCONV_CHARS_FORMAT_DEFINED
// The enumeration values are decoupled from the host standard library; host
// and device compilations share the same stable representation.
enum class chars_format {
    scientific = 0x1,
    fixed = 0x2,
    hex = 0x4,
    general = fixed | scientific,
};

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chars_format operator~(chars_format value) noexcept
{
    return chars_format(~::asc::std::to_underlying(value));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chars_format operator&(chars_format lhs, chars_format rhs) noexcept
{
    return chars_format(::asc::std::to_underlying(lhs) & ::asc::std::to_underlying(rhs));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chars_format operator|(chars_format lhs, chars_format rhs) noexcept
{
    return chars_format(::asc::std::to_underlying(lhs) | ::asc::std::to_underlying(rhs));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chars_format operator^(chars_format lhs, chars_format rhs) noexcept
{
    return chars_format(::asc::std::to_underlying(lhs) ^ ::asc::std::to_underlying(rhs));
}

CANN_ASC_STL_API constexpr chars_format& operator&=(chars_format& lhs, chars_format rhs) noexcept
{
    lhs = lhs & rhs;
    return lhs;
}

CANN_ASC_STL_API constexpr chars_format& operator|=(chars_format& lhs, chars_format rhs) noexcept
{
    lhs = lhs | rhs;
    return lhs;
}

CANN_ASC_STL_API constexpr chars_format& operator^=(chars_format& lhs, chars_format rhs) noexcept
{
    lhs = lhs ^ rhs;
    return lhs;
}
#endif  // !CANN_ASC_STL_ASC_STD_CHARCONV && !CANN_ASC_STL_DETAIL_CHARCONV_CHARS_FORMAT_DEFINED

namespace __charconv_detail {

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr char __to_chars_value_to_char(int value, int base) noexcept
{
    const int offset = (base < 10 || value < 10) ? '0' : ('a' - 10);
    return static_cast<char>(offset + value);
}

// Width precomputation: compares in batches of 4 digits, used by the
// direct-write path to decide value_too_large.
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr int __to_chars_int_width(T value, int base) noexcept
{
    using U = conditional_t<sizeof(T) >= sizeof(uint32_t), make_unsigned_t<T>, uint32_t>;
    auto unsigned_value = static_cast<U>(value);
    const auto unsigned_base = static_cast<U>(base);
    const auto base_2 = static_cast<U>(unsigned_base * unsigned_base);
    const auto base_3 = static_cast<U>(base_2 * unsigned_base);
    const auto base_4 = static_cast<U>(base_2 * base_2);

    int result = 0;
    while (true) {
        if (unsigned_value < unsigned_base) {
            return result + 1;
        }
        if (unsigned_value < base_2) {
            return result + 2;
        }
        if (unsigned_value < base_3) {
            return result + 3;
        }
        if (unsigned_value < base_4) {
            return result + 4;
        }
        unsigned_value = static_cast<U>(unsigned_value / base_4);
        result += 4;
    }
}

// Writes the digits backwards starting at last (the caller guarantees the
// width has been validated).
template <class T>
CANN_ASC_STL_API constexpr void __to_chars_int_generic(char* last, T value, int base) noexcept
{
    do {
        const int digit = static_cast<int>(value % base);
        *--last = __to_chars_value_to_char(digit, base);
        value = static_cast<T>(value / base);
    } while (value != 0);
}

template <class T>
CANN_ASC_STL_API constexpr to_chars_result __to_chars_integer(char* first, char* last, T value, int base) noexcept
{
    if (base < 2 || base > 36) {
        return {first, errc::invalid_argument};
    }
    if constexpr (is_signed_v<T>) {
        if (value < T{0} && first < last) {
            *first++ = '-';
        }
        return __to_chars_integer(first, last, __uabs(value), base);
    } else {
        const ptrdiff_t capacity = last - first;
        const int width = __to_chars_int_width(value, base);
        if (width > capacity) {
            return {last, errc::value_too_large};
        }
        char* new_last = first + width;
        __to_chars_int_generic(new_last, value, base);
        return {new_last, errc{}};
    }
}
}  // namespace __charconv_detail

template <class T, enable_if_t<__is_integer_v<T>, int> = 0>
CANN_ASC_STL_API constexpr to_chars_result to_chars(char* first, char* last, T value, int base = 10) noexcept
{
    return __charconv_detail::__to_chars_integer(first, last, value, base);
}
CANN_ASC_STL_API constexpr to_chars_result to_chars(char* first, char* last, char value, int base = 10) noexcept
{
    return __charconv_detail::__to_chars_integer(first, last, value, base);
}
CANN_ASC_STL_API constexpr to_chars_result to_chars(char* first, char* last, signed char value, int base = 10) noexcept
{
    return __charconv_detail::__to_chars_integer(first, last, value, base);
}
CANN_ASC_STL_API constexpr to_chars_result to_chars(
    char* first, char* last, unsigned char value, int base = 10) noexcept
{
    return __charconv_detail::__to_chars_integer(first, last, value, base);
}
to_chars_result to_chars(char*, char*, bool, int = 10) = delete;

// Floating-point formatting is a placeholder (a static_assert stub). The
// bare floating-point overload does not reference chars_format and is always
// provided; the two overloads with format/precision depend on chars_format
// and are declared only when this header is compiled standalone (facade
// absent).
#if !defined(CANN_ASC_STL_ASC_STD_CHARCONV)
template <class T, enable_if_t<is_floating_point_v<T>, int> = 0>
CANN_ASC_STL_API constexpr to_chars_result to_chars(char* first, char* last, T value, chars_format fmt) noexcept
{
    static_assert(__always_false_v<T>, "asc::std::to_chars for floating point types is not yet implemented");
    (void)first;
    (void)last;
    (void)value;
    (void)fmt;
    return {};
}

template <class T, enable_if_t<is_floating_point_v<T>, int> = 0>
CANN_ASC_STL_API constexpr to_chars_result to_chars(
    char* first, char* last, T value, chars_format fmt, int precision) noexcept
{
    static_assert(__always_false_v<T>, "asc::std::to_chars for floating point types is not yet implemented");
    (void)first;
    (void)last;
    (void)value;
    (void)fmt;
    (void)precision;
    return {};
}
#endif  // !CANN_ASC_STL_ASC_STD_CHARCONV

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHARCONV_TO_CHARS_H
