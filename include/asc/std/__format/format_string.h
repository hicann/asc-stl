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
#include <asc/std/__format/validation.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/type_identity.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __format_detail {
#if defined(__CCE__) && !defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
using input_pointer = const __gm__ char*;
#else
using input_pointer = const char*;
#endif

// Parameter view of a compile-time format literal. The vector-core __gm__
// address space qualifier lives on the alias, so the constructor and the
// validator below spell a single signature in every execution space instead
// of piecing the member initializer list together across #if branches.
#if defined(__CCE__) && !defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
template <class CharT, __SIZE_TYPE__ Size>
using input_array = const __gm__ CharT (&)[Size];
#else
template <class CharT, __SIZE_TYPE__ Size>
using input_array = const CharT (&)[Size];
#endif
}  // namespace __format_detail

#if CANN_ASC_STL_DETAIL_HAS_CONSTEVAL()

// Registered subset: basic_format_string<char, Args...>. The assertion moves
// wide-character instantiation failures to the class itself with a
// product-level message instead of a deep member-initialization mismatch.
template <class CharT, class... Args>
class basic_format_string {
    static_assert(is_same<CharT, char>::value,
        "ASC-STL format strings support char only; wchar_t is not part of the registered subset");

public:
    template <__SIZE_TYPE__ Size>
    CANN_ASC_STL_API consteval basic_format_string(__format_detail::input_array<CharT, Size> text) noexcept
        : data_(text), size_(Size - 1)
    {
        validate(text);
    }

    // Extension members of the ASC subset: std::basic_format_string names
    // this access get(); data()/size() are the wiring the fixed-buffer
    // renderer consumes and are kept as the in-library face of the stored
    // literal.
    CANN_ASC_STL_API constexpr __format_detail::input_pointer data() const noexcept
    {
        return data_;
    }
    CANN_ASC_STL_API constexpr __SIZE_TYPE__ size() const noexcept
    {
        return size_;
    }

private:
    CANN_ASC_STL_API static constexpr bool escaped_field(char current, char next) noexcept
    {
        return (current == '{' || current == '}') && next == current;
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
    CANN_ASC_STL_API static constexpr void validate(__format_detail::input_array<CharT, Size> text) noexcept
    {
        constexpr bool numeric[] = {__format_detail::is_format_integer<Args>::value..., false};
        __SIZE_TYPE__ field = 0;
        for (__SIZE_TYPE__ position = 0; position + 1 < Size;) {
            const char current = text[position++];
            // text[position] is at worst the NUL terminator of the literal
            // (the loop guard keeps position <= Size - 1), which never
            // matches a brace, so no extra reachability check is needed.
            if (escaped_field(current, text[position])) {
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
template <class... Args>
using format_string = basic_format_string<char, type_identity_t<Args>...>;

#endif  // CANN_ASC_STL_DETAIL_HAS_CONSTEVAL()

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___FORMAT_FORMAT_STRING_H
