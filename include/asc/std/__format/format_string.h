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

#ifndef CANN_ASC_STL_ASC_STD___FORMAT_FORMAT_STRING_H
#define CANN_ASC_STL_ASC_STD___FORMAT_FORMAT_STRING_H

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
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__format/validation.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/string_view>

#if CANN_ASC_STL_DETAIL_HAS_CXX20()

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __format_detail {
#if defined(__CCE__) && !defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
using input_pointer = const __gm__ char*;
#else
using input_pointer = const char*;
#endif
}  // namespace __format_detail

template <class CharT, class... Args>
class basic_format_string {
public:
    template <__SIZE_TYPE__ Size>
#if defined(__CCE__) && !defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
    CANN_ASC_STL_API consteval basic_format_string(const __gm__ CharT (&text)[Size]) noexcept
#else
    CANN_ASC_STL_API consteval basic_format_string(const CharT (&text)[Size]) noexcept : data_(text), size_(Size - 1)
#endif
#if defined(__CCE__) && !defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
        : data_(text), size_(Size - 1)
#endif
    {
        validate(text);
    }
    CANN_ASC_STL_API constexpr __format_detail::input_pointer data() const noexcept
    {
        return data_;
    }
    CANN_ASC_STL_API constexpr __SIZE_TYPE__ size() const noexcept
    {
        return size_;
    }

private:
    CANN_ASC_STL_API static constexpr bool escaped_field(char current, char next, bool has_following) noexcept
    {
        return (current == '{' || current == '}') && has_following && next == current;
    }
    CANN_ASC_STL_API static constexpr bool empty_field(char current, char next) noexcept
    {
        return current == '{' && next == '}';
    }
    CANN_ASC_STL_API static constexpr bool typed_field(char current, char next, char closing, bool complete) noexcept
    {
        return current == '{' && complete && next == ':' && closing == '}';
    }
    CANN_ASC_STL_API static constexpr bool numeric_presentation(char value) noexcept
    {
        return value == 'd' || value == 'x' || value == 'X' || value == 'o' || value == 'b';
    }
    template <__SIZE_TYPE__ Size>
#if defined(__CCE__) && !defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
    CANN_ASC_STL_API static constexpr void validate(const __gm__ CharT (&text)[Size]) noexcept
#else
    CANN_ASC_STL_API static constexpr void validate(const CharT (&text)[Size]) noexcept
#endif
    {
        constexpr bool numeric[] = {
            (__format_detail::is_integral<__format_detail::remove_cvref_t<Args>>::value &&
                !__format_detail::is_same<__format_detail::remove_cvref_t<Args>, bool>::value &&
                !__format_detail::is_same<__format_detail::remove_cvref_t<Args>, char>::value)...,
            false};
        __SIZE_TYPE__ field = 0;
        for (__SIZE_TYPE__ position = 0; position + 1 < Size;) {
            const char current = text[position++];
            if (escaped_field(current, text[position], position + 1 < Size)) {
                ++position;
                continue;
            }
            if (empty_field(current, text[position])) {
                if (field >= sizeof...(Args))
                    __builtin_trap();
                ++field;
                ++position;
                continue;
            }
            const bool complete = position + 2 < Size;
            const char closing = complete ? text[position + 2] : '\0';
            if (typed_field(current, text[position], closing, complete)) {
                const char presentation = text[position + 1];
                if (field >= sizeof...(Args) || !numeric[field] || !numeric_presentation(presentation)) {
                    __builtin_trap();
                }
                ++field;
                position += 3;
                continue;
            }
            if (current == '{' || current == '}')
                __builtin_trap();
        }
    }
    __format_detail::input_pointer data_;
    __SIZE_TYPE__ size_;
};
namespace __format_detail {
template <class T>
struct type_identity {
    using type = T;
};
}  // namespace __format_detail
template <class... Args>
using format_string = basic_format_string<char, typename __format_detail::type_identity<Args>::type...>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_DETAIL_HAS_CXX20()

#endif  // CANN_ASC_STL_ASC_STD___FORMAT_FORMAT_STRING_H
