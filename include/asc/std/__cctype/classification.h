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
// integer range semantics, so EOF and every other out-of-domain input
// classifies as false.

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#include <cctype>
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

CANN_ASC_STL_API int isupper(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return value >= 'A' && value <= 'Z';
#else
    return ::std::isupper(value);
#endif
}

CANN_ASC_STL_API int islower(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return value >= 'a' && value <= 'z';
#else
    return ::std::islower(value);
#endif
}

CANN_ASC_STL_API int isalpha(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return isupper(value) || islower(value);
#else
    return ::std::isalpha(value);
#endif
}

CANN_ASC_STL_API int isdigit(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return value >= '0' && value <= '9';
#else
    return ::std::isdigit(value);
#endif
}

CANN_ASC_STL_API int isxdigit(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return isdigit(value) || (value >= 'A' && value <= 'F') || (value >= 'a' && value <= 'f');
#else
    return ::std::isxdigit(value);
#endif
}

CANN_ASC_STL_API int isalnum(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return isalpha(value) || isdigit(value);
#else
    return ::std::isalnum(value);
#endif
}

CANN_ASC_STL_API int isblank(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return value == ' ' || value == '\t';
#else
    return ::std::isblank(value);
#endif
}

CANN_ASC_STL_API int isspace(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return value == ' ' || (value >= '\t' && value <= '\r');
#else
    return ::std::isspace(value);
#endif
}

CANN_ASC_STL_API int iscntrl(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return (value >= 0 && value < 0x20) || value == 0x7f;
#else
    return ::std::iscntrl(value);
#endif
}

CANN_ASC_STL_API int isprint(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return value >= 0x20 && value <= 0x7e;
#else
    return ::std::isprint(value);
#endif
}

CANN_ASC_STL_API int isgraph(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return value >= 0x21 && value <= 0x7e;
#else
    return ::std::isgraph(value);
#endif
}

CANN_ASC_STL_API int ispunct(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return isgraph(value) && !isalnum(value);
#else
    return ::std::ispunct(value);
#endif
}

CANN_ASC_STL_API int tolower(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return isupper(value) ? value + ('a' - 'A') : value;
#else
    return ::std::tolower(value);
#endif
}

CANN_ASC_STL_API int toupper(int value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return islower(value) ? value - ('a' - 'A') : value;
#else
    return ::std::toupper(value);
#endif
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CCTYPE_CLASSIFICATION_H
