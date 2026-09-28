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

#ifndef CANN_ASC_STL_STD_DETAIL_CWCHAR_FIXED_C_LOCALE_H
#define CANN_ASC_STL_STD_DETAIL_CWCHAR_FIXED_C_LOCALE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

// Collation, explicit-state tokenization and the fixed-C-locale conversion
// set. Host delegates to the system <cwchar>; Device implements the stateless
// single-byte C locale with pure integer and character semantics. This root
// owns the one definition of the conversion state type because only its
// functions consume it; the wint_t alias repeats the identical underlying
// type also spelled by the types root, which is a legal same-type alias
// redeclaration when the later public facade composes both roots.
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#include <cwchar>
#endif

#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#if !defined(WEOF)
#define WEOF (static_cast<asc::std::wint_t>(-1))
#endif
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
using wint_t = unsigned int;
#ifndef CANN_ASC_STL_DETAIL_MBSTATE_T_DEFINED
#define CANN_ASC_STL_DETAIL_MBSTATE_T_DEFINED
struct mbstate_t {
    unsigned int state = 0;
};
#endif
#else
using wint_t = ::std::wint_t;
#ifndef CANN_ASC_STL_DETAIL_MBSTATE_T_DEFINED
#define CANN_ASC_STL_DETAIL_MBSTATE_T_DEFINED
using mbstate_t = ::std::mbstate_t;
#endif
#endif

namespace detail {

inline constexpr wint_t wide_eof = static_cast<wint_t>(-1);
inline constexpr __SIZE_TYPE__ conversion_error = static_cast<__SIZE_TYPE__>(-1);
inline constexpr __SIZE_TYPE__ conversion_incomplete = static_cast<__SIZE_TYPE__>(-2);

CANN_ASC_STL_API bool is_delimiter(wchar_t value, const wchar_t* delimiters) noexcept
{
    const wchar_t* current = delimiters;
    for (; *current != L'\0'; ++current) {
        if (*current == value) {
            return true;
        }
    }
    return false;
}

}  // namespace detail

CANN_ASC_STL_API int wcscoll(const wchar_t* left, const wchar_t* right) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    while (*left != L'\0' && *left == *right) {
        ++left;
        ++right;
    }
    return *left < *right ? -1 : (*left > *right ? 1 : 0);
#else
    return ::std::wcscoll(left, right);
#endif
}

CANN_ASC_STL_API __SIZE_TYPE__ wcsxfrm(wchar_t* destination, const wchar_t* source, __SIZE_TYPE__ count) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    __SIZE_TYPE__ length = 0;
    while (source[length] != L'\0') {
        ++length;
    }
    if (destination != nullptr && length < count) {
        for (__SIZE_TYPE__ index = 0; index < length + 1; ++index) {
            destination[index] = source[index];
        }
    }
    return length;
#else
    return ::std::wcsxfrm(destination, source, count);
#endif
}

CANN_ASC_STL_API wchar_t* wcstok(wchar_t* input, const wchar_t* delimiters, wchar_t** state) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    wchar_t* current = input == nullptr ? *state : input;
    if (current == nullptr) {
        return nullptr;
    }
    while (*current != L'\0' && detail::is_delimiter(*current, delimiters)) {
        ++current;
    }
    if (*current == L'\0') {
        *state = current;
        return nullptr;
    }
    wchar_t* token = current;
    while (*current != L'\0' && !detail::is_delimiter(*current, delimiters)) {
        ++current;
    }
    if (*current == L'\0') {
        *state = current;
    } else {
        *current = L'\0';
        *state = current + 1;
    }
    return token;
#else
    return ::std::wcstok(input, delimiters, state);
#endif
}

CANN_ASC_STL_API wint_t btowc(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    if (value < 0 || value > 0x7f) {
        return detail::wide_eof;
    }
    return static_cast<wint_t>(static_cast<unsigned char>(value));
#else
    return ::std::btowc(value);
#endif
}

CANN_ASC_STL_API int wctob(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return value <= 0x7f ? static_cast<int>(value) : -1;
#else
    return ::std::wctob(value);
#endif
}

CANN_ASC_STL_API int mbsinit(const mbstate_t* state) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return state == nullptr || state->state == 0;
#else
    return ::std::mbsinit(state);
#endif
}

CANN_ASC_STL_API __SIZE_TYPE__ mbrtowc(
    wchar_t* output, const char* input, __SIZE_TYPE__ count, mbstate_t* state) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    (void)state;
    if (input == nullptr) {
        return 0;
    }
    if (count == 0) {
        return detail::conversion_incomplete;
    }
    const unsigned char value = static_cast<unsigned char>(*input);
    if (value > 0x7f) {
        return detail::conversion_error;
    }
    if (output != nullptr) {
        *output = static_cast<wchar_t>(value);
    }
    return value == 0 ? 0 : 1;
#else
    return ::std::mbrtowc(output, input, count, state);
#endif
}

CANN_ASC_STL_API __SIZE_TYPE__ mbrlen(const char* input, __SIZE_TYPE__ count, mbstate_t* state) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::mbrtowc(nullptr, input, count, state);
#else
    return ::std::mbrlen(input, count, state);
#endif
}

CANN_ASC_STL_API __SIZE_TYPE__ wcrtomb(char* output, wchar_t input, mbstate_t* state) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    (void)state;
    if (output == nullptr) {
        return 1;
    }
    if (input < 0 || static_cast<unsigned long>(input) > 0x7f) {
        return detail::conversion_error;
    }
    *output = static_cast<char>(input);
    return 1;
#else
    return ::std::wcrtomb(output, input, state);
#endif
}

CANN_ASC_STL_API __SIZE_TYPE__ mbsrtowcs(
    wchar_t* destination, const char** source, __SIZE_TYPE__ count, mbstate_t* state) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    (void)state;
    const char* current = *source;
    __SIZE_TYPE__ converted = 0;
    if (destination == nullptr) {
        while (current[converted] != '\0') {
            if (static_cast<unsigned char>(current[converted]) > 0x7f) {
                return detail::conversion_error;
            }
            ++converted;
        }
        return converted;
    }
    while (converted < count) {
        const unsigned char value = static_cast<unsigned char>(*current);
        if (value > 0x7f) {
            *source = current;
            return detail::conversion_error;
        }
        destination[converted] = static_cast<wchar_t>(value);
        if (value == 0) {
            *source = nullptr;
            return converted;
        }
        ++converted;
        ++current;
    }
    *source = current;
    return converted;
#else
    return ::std::mbsrtowcs(destination, source, count, state);
#endif
}

CANN_ASC_STL_API __SIZE_TYPE__ wcsrtombs(
    char* destination, const wchar_t** source, __SIZE_TYPE__ count, mbstate_t* state) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    (void)state;
    const wchar_t* current = *source;
    __SIZE_TYPE__ converted = 0;
    if (destination == nullptr) {
        while (current[converted] != L'\0') {
            if (current[converted] < 0 || static_cast<unsigned long>(current[converted]) > 0x7f) {
                return detail::conversion_error;
            }
            ++converted;
        }
        return converted;
    }
    while (converted < count) {
        const wchar_t value = *current;
        if (value < 0 || static_cast<unsigned long>(value) > 0x7f) {
            *source = current;
            return detail::conversion_error;
        }
        destination[converted] = static_cast<char>(value);
        if (value == L'\0') {
            *source = nullptr;
            return converted;
        }
        ++converted;
        ++current;
    }
    *source = current;
    return converted;
#else
    return ::std::wcsrtombs(destination, source, count, state);
#endif
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_CWCHAR_FIXED_C_LOCALE_H
