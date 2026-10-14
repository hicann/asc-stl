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

#ifndef CANN_ASC_STL_ASC_STD___CCTYPE_CLASSIFICATION_H
#define CANN_ASC_STL_ASC_STD___CCTYPE_CLASSIFICATION_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

// Implementation root for the later public <asc/std/cctype>: Host delegates
// to the system locale while Device implements the fixed C locale with pure
// integer range semantics. The fixed-C-locale predicates live as constexpr
// detail cores so in-library constant evaluation (charconv/format parsing
// and similar) can reuse them on the host side as well, while the public
// facades keep their registered non-constexpr signatures.
//
// Out-of-domain inputs: Device classifies EOF and every other value outside
// [0, 127] as false per the fixed C locale. Host preserves the C standard
// contract instead, where a value that is neither representable as unsigned
// char nor EOF is undefined behavior -- do not extrapolate the lenient
// device behavior to host builds.

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#include <cctype>
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

namespace detail {

CANN_ASC_STL_API constexpr bool is_upper(int value) noexcept
{
    return value >= 'A' && value <= 'Z';
}

CANN_ASC_STL_API constexpr bool is_lower(int value) noexcept
{
    return value >= 'a' && value <= 'z';
}

CANN_ASC_STL_API constexpr bool is_alpha(int value) noexcept
{
    return is_upper(value) || is_lower(value);
}

CANN_ASC_STL_API constexpr bool is_digit(int value) noexcept
{
    return value >= '0' && value <= '9';
}

CANN_ASC_STL_API constexpr bool is_xdigit(int value) noexcept
{
    return is_digit(value) || (value >= 'A' && value <= 'F') || (value >= 'a' && value <= 'f');
}

CANN_ASC_STL_API constexpr bool is_alnum(int value) noexcept
{
    return is_alpha(value) || is_digit(value);
}

CANN_ASC_STL_API constexpr bool is_blank(int value) noexcept
{
    return value == ' ' || value == '\t';
}

CANN_ASC_STL_API constexpr bool is_space(int value) noexcept
{
    return value == ' ' || (value >= '\t' && value <= '\r');
}

CANN_ASC_STL_API constexpr bool is_cntrl(int value) noexcept
{
    return (value >= 0 && value < 0x20) || value == 0x7f;
}

CANN_ASC_STL_API constexpr bool is_print(int value) noexcept
{
    return value >= 0x20 && value <= 0x7e;
}

CANN_ASC_STL_API constexpr bool is_graph(int value) noexcept
{
    return value >= 0x21 && value <= 0x7e;
}

CANN_ASC_STL_API constexpr bool is_punct(int value) noexcept
{
    return is_graph(value) && !is_alnum(value);
}

CANN_ASC_STL_API constexpr int to_lower(int value) noexcept
{
    return is_upper(value) ? value + ('a' - 'A') : value;
}

CANN_ASC_STL_API constexpr int to_upper(int value) noexcept
{
    return is_lower(value) ? value - ('a' - 'A') : value;
}

}  // namespace detail

CANN_ASC_STL_API int isupper(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::is_upper(value);
#else
    return ::std::isupper(value);
#endif
}

CANN_ASC_STL_API int islower(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::is_lower(value);
#else
    return ::std::islower(value);
#endif
}

CANN_ASC_STL_API int isalpha(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::is_alpha(value);
#else
    return ::std::isalpha(value);
#endif
}

CANN_ASC_STL_API int isdigit(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::is_digit(value);
#else
    return ::std::isdigit(value);
#endif
}

CANN_ASC_STL_API int isxdigit(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::is_xdigit(value);
#else
    return ::std::isxdigit(value);
#endif
}

CANN_ASC_STL_API int isalnum(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::is_alnum(value);
#else
    return ::std::isalnum(value);
#endif
}

CANN_ASC_STL_API int isblank(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::is_blank(value);
#else
    return ::std::isblank(value);
#endif
}

CANN_ASC_STL_API int isspace(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::is_space(value);
#else
    return ::std::isspace(value);
#endif
}

CANN_ASC_STL_API int iscntrl(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::is_cntrl(value);
#else
    return ::std::iscntrl(value);
#endif
}

CANN_ASC_STL_API int isprint(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::is_print(value);
#else
    return ::std::isprint(value);
#endif
}

CANN_ASC_STL_API int isgraph(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::is_graph(value);
#else
    return ::std::isgraph(value);
#endif
}

CANN_ASC_STL_API int ispunct(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::is_punct(value);
#else
    return ::std::ispunct(value);
#endif
}

CANN_ASC_STL_API int tolower(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::to_lower(value);
#else
    return ::std::tolower(value);
#endif
}

CANN_ASC_STL_API int toupper(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::to_upper(value);
#else
    return ::std::toupper(value);
#endif
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CCTYPE_CLASSIFICATION_H
