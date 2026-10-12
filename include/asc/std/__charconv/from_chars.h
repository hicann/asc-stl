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

#ifndef CANN_ASC_STL_ASC_STD___CHARCONV_FROM_CHARS_H
#define CANN_ASC_STL_ASC_STD___CHARCONV_FROM_CHARS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__charconv/from_chars_result.h>
#include <asc/std/__cmath/neg.h>
#include <asc/std/__cmath/uabs.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__cstddef/types.h>
#include <asc/std/__limits/numeric_limits.h>
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

// [charconv.syn] chars_format：门面 <asc/std/charconv> 在场时由门面统一提供（门面守卫宏作为
// 在场标志）；本头独立编译时经共享守卫内联同一份定义，两个 __charconv 子头共用，避免重定义。
#if !defined(CANN_ASC_STL_ASC_STD_CHARCONV) && !defined(CANN_ASC_STL_DETAIL_CHARCONV_CHARS_FORMAT_DEFINED)
#define CANN_ASC_STL_DETAIL_CHARCONV_CHARS_FORMAT_DEFINED
// 枚举值与宿主标准库解耦，宿主与设备编译共享同一稳定表示。
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

CANN_ASC_STL_API constexpr int __from_chars_digit_value(char character) noexcept
{
    if (character >= '0' && character <= '9') {
        return character - '0';
    }
    if (character >= 'a' && character <= 'z') {
        return character - 'a' + 10;
    }
    if (character >= 'A' && character <= 'Z') {
        return character - 'A' + 10;
    }
    return -1;
}

// Integer-only parse following the standard from_chars contract: no leading
// whitespace, no '+' sign, an optional '-' only for signed types, the longest
// digit pattern of the requested base, and unchanged value with
// result_out_of_range on overflow.  The accumulation uses the unsigned
// counterpart so no signed-overflow undefined behaviour can occur.
template <class T>
CANN_ASC_STL_API constexpr from_chars_result __from_chars_integer(
    const char* first, const char* last, T& value, int base) noexcept
{
    static_assert(__is_integer_v<T> || is_same_v<T, char>,
        "from_chars requires an integer type");  // NOLINT(build/include_what_you_use)
    if (base < 2 || base > 36) {
        return {first, errc::invalid_argument};
    }
    using U = make_unsigned_t<T>;
    const char* cursor = first;
    bool negative = false;
    if (cursor != last && *cursor == '-') {
        if (!is_signed_v<T>) {
            return {first, errc::invalid_argument};
        }
        negative = true;
        ++cursor;
    }
    // NOLINTNEXTLINE(build/include_what_you_use)
    const U limit = negative ? __uabs(numeric_limits<T>::min()) : static_cast<U>(numeric_limits<T>::max());
    U accumulator = 0;
    bool out_of_range = false;
    const char* digits_end = cursor;
    for (; digits_end != last; ++digits_end) {
        const int digit = __from_chars_digit_value(*digits_end);
        if (digit < 0 || digit >= base) {
            break;
        }
        if (!out_of_range) {
            if (accumulator > (limit - static_cast<U>(digit)) / static_cast<U>(base)) {
                out_of_range = true;
            } else {
                accumulator = static_cast<U>(accumulator * static_cast<U>(base) + static_cast<U>(digit));
            }
        }
    }
    if (digits_end == cursor) {
        return {first, errc::invalid_argument};
    }
    if (out_of_range) {
        return {digits_end, errc::result_out_of_range};
    }
    value = negative ? static_cast<T>(__neg(accumulator)) : static_cast<T>(accumulator);
    return {digits_end, static_cast<errc>(0)};
}

}  // namespace __charconv_detail

template <class T, enable_if_t<__is_integer_v<T>, int> = 0>
CANN_ASC_STL_API constexpr from_chars_result from_chars(
    const char* first, const char* last, T& value, int base = 10) noexcept
{
    return __charconv_detail::__from_chars_integer(first, last, value, base);
}
CANN_ASC_STL_API constexpr from_chars_result from_chars(
    const char* first, const char* last, char& value, int base = 10) noexcept
{
    return __charconv_detail::__from_chars_integer(first, last, value, base);
}
CANN_ASC_STL_API constexpr from_chars_result from_chars(
    const char* first, const char* last, signed char& value, int base = 10) noexcept
{
    return __charconv_detail::__from_chars_integer(first, last, value, base);
}
CANN_ASC_STL_API constexpr from_chars_result from_chars(
    const char* first, const char* last, unsigned char& value, int base = 10) noexcept
{
    return __charconv_detail::__from_chars_integer(first, last, value, base);
}

// 浮点解析为占位实现（与源实现一致的 static_assert 桩）：依赖上面的 chars_format，
// 仅在本头独立编译（门面不在场）时声明；经 <asc/std/charconv> 使用时浮点重载暂不提供。
#if !defined(CANN_ASC_STL_ASC_STD_CHARCONV)
template <class T, enable_if_t<is_floating_point_v<T>, int> = 0>
CANN_ASC_STL_API constexpr from_chars_result from_chars(
    const char* first, const char* last, T& value, chars_format fmt = chars_format::general) noexcept
{
    static_assert(__always_false_v<T>, "asc::std::from_chars for floating point types is not yet implemented");
    (void)first;
    (void)last;
    (void)value;
    (void)fmt;
    return {};
}
#endif  // !CANN_ASC_STL_ASC_STD_CHARCONV

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHARCONV_FROM_CHARS_H
