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

#ifndef CANN_ASC_STL_ASC_STD___CUCHAR_FIXED_C_LOCALE_H
#define CANN_ASC_STL_ASC_STD___CUCHAR_FIXED_C_LOCALE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

// Implementation root for the later public <asc/std/cuchar>: the character
// conversion family (mbstate_t vocabulary, c16rtomb/c32rtomb/c8rtomb and
// mbrtoc16/mbrtoc32/mbrtoc8). Host delegates to the system <cuchar>;
// Device computes the locale-independent C execution character set with
// pure integer semantics, so no host locale state crosses the device
// boundary.
//
// Device error reporting: conversion failures return (size_t)-1 only;
// errno is deliberately not maintained on device (no EILSEQ store), which
// matches the registered cerrno device contract where errno itself does
// not cross the device boundary.
//
// Documented deviation in the device mbrtoc32/mbrtoc16/mbrtoc8 null-input
// path: the C11 mbrtoc32 clause makes mbrtoc32(pwc, NULL, n, ps) equivalent
// to mbrtoc32(NULL, "", 1, ps), i.e. the destination is also treated as
// null and must not be written. The device branch deliberately keeps
// writing U'\0' (with the state reset and the 0 return) because the base
// runtime semantic suite locks that behavior; the write is bounded to this
// branch.

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#include <cuchar>
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

using size_t = __SIZE_TYPE__;

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
using ::std::c16rtomb;
using ::std::c32rtomb;
using ::std::mbrtoc16;
using ::std::mbrtoc32;
#ifndef CANN_ASC_STL_DETAIL_MBSTATE_T_DEFINED
#define CANN_ASC_STL_DETAIL_MBSTATE_T_DEFINED
using ::std::mbstate_t;
#endif
#if CANN_ASC_STL_DETAIL_HAS_CHAR8_T()
// Host conversion requires the actual system declarations and implementation.
// A library major version cannot describe vendor backports or the configured C
// library. The Host environment preflight verifies compilation, linking and use.
using ::std::c8rtomb;
using ::std::mbrtoc8;
#endif
#else
#ifndef CANN_ASC_STL_DETAIL_MBSTATE_T_DEFINED
#define CANN_ASC_STL_DETAIL_MBSTATE_T_DEFINED
struct mbstate_t {
    unsigned int state = 0;
};
#endif

CANN_ASC_STL_API __SIZE_TYPE__ c32rtomb(char* output, char32_t value, mbstate_t*) noexcept
{
    if (value <= 0x7f) {
        if (output != nullptr) {
            output[0] = static_cast<char>(value);
        }
        return 1;
    }
    return static_cast<__SIZE_TYPE__>(-1);
}

CANN_ASC_STL_API __SIZE_TYPE__ c16rtomb(char* output, char16_t value, mbstate_t* state) noexcept
{
    return ::asc::std::c32rtomb(output, static_cast<char32_t>(value), state);
}

CANN_ASC_STL_API __SIZE_TYPE__ mbrtoc32(
    char32_t* output, const char* input, __SIZE_TYPE__ count, mbstate_t* state) noexcept
{
    if (input == nullptr) {
        if (state != nullptr) {
            state->state = 0;
        }
        if (output != nullptr) {
            *output = U'\0';
        }
        return 0;
    }
    if (count == 0) {
        return static_cast<__SIZE_TYPE__>(-2);
    }
    const unsigned char first = static_cast<unsigned char>(input[0]);
    if (first > 0x7f) {
        return static_cast<__SIZE_TYPE__>(-1);
    }
    if (output != nullptr) {
        *output = static_cast<char32_t>(first);
    }
    return first == 0 ? 0 : 1;
}

CANN_ASC_STL_API __SIZE_TYPE__ mbrtoc16(
    char16_t* output, const char* input, __SIZE_TYPE__ count, mbstate_t* state) noexcept
{
    char32_t value = 0;
    const __SIZE_TYPE__ result = ::asc::std::mbrtoc32(output == nullptr ? nullptr : &value, input, count, state);
    if (output != nullptr && result != static_cast<__SIZE_TYPE__>(-1) && result != static_cast<__SIZE_TYPE__>(-2)) {
        *output = static_cast<char16_t>(value);
    }
    return result;
}

#if CANN_ASC_STL_DETAIL_HAS_CHAR8_T()
CANN_ASC_STL_API __SIZE_TYPE__ c8rtomb(char* output, char8_t value, mbstate_t*) noexcept
{
    if (value <= static_cast<char8_t>(0x7f)) {
        if (output != nullptr) {
            output[0] = static_cast<char>(value);
        }
        return 1;
    }
    return static_cast<__SIZE_TYPE__>(-1);
}

CANN_ASC_STL_API __SIZE_TYPE__ mbrtoc8(
    char8_t* output, const char* input, __SIZE_TYPE__ count, mbstate_t* state) noexcept
{
    char32_t value = 0;
    const __SIZE_TYPE__ result = ::asc::std::mbrtoc32(output == nullptr ? nullptr : &value, input, count, state);
    if (output != nullptr && result != static_cast<__SIZE_TYPE__>(-1) && result != static_cast<__SIZE_TYPE__>(-2)) {
        *output = static_cast<char8_t>(value);
    }
    return result;
}
#endif
#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CUCHAR_FIXED_C_LOCALE_H
