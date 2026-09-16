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

#ifndef CANN_ASC_STL_ASC_STD___STRING_CONSTEXPR_C_FUNCTIONS_H
#define CANN_ASC_STL_ASC_STD___STRING_CONSTEXPR_C_FUNCTIONS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__cstddef/types.h>
#include <asc/std/__type_traits/make_nbit_int.h>
#include <asc/std/__type_traits/remove_const.h>
#include <asc/std/climits>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Character>
CANN_ASC_STL_API constexpr Character* __asc_strcpy(Character* destination, const Character* source) noexcept
{
    Character* result = destination;
    while ((*destination++ = *source++) != Character{}) {
    }
    return result;
}

template <class Character>
CANN_ASC_STL_API constexpr Character* __asc_strncpy(
    Character* destination, const Character* source, __SIZE_TYPE__ count) noexcept
{
    Character* result = destination;
    __SIZE_TYPE__ index = 0;
    for (; index < count && source[index] != Character{}; ++index) {
        destination[index] = source[index];
    }
    for (; index < count; ++index) {
        destination[index] = Character{};
    }
    return result;
}

template <class Character>
CANN_ASC_STL_API constexpr __SIZE_TYPE__ __asc_strlen(const Character* value) noexcept
{
    __SIZE_TYPE__ result = 0;
    while (value[result] != Character{}) {
        ++result;
    }
    return result;
}

template <class Character>
CANN_ASC_STL_API constexpr int __asc_strcmp(const Character* left, const Character* right) noexcept
{
    while (*left != Character{} && *left == *right) {
        ++left;
        ++right;
    }
    return *left < *right ? -1 : (*right < *left ? 1 : 0);
}

template <class Character>
CANN_ASC_STL_API constexpr int __asc_strncmp(
    const Character* left, const Character* right, __SIZE_TYPE__ count) noexcept
{
    for (__SIZE_TYPE__ index = 0; index < count; ++index) {
        if (left[index] != right[index] || left[index] == Character{}) {
            return left[index] < right[index] ? -1 : (right[index] < left[index] ? 1 : 0);
        }
    }
    return 0;
}

template <class Character>
CANN_ASC_STL_API constexpr Character* __asc_strchr(Character* value, remove_const_t<Character> character) noexcept
{
    for (;; ++value) {
        if (*value == character) {
            return value;
        }
        if (*value == Character{}) {
            return nullptr;
        }
    }
}

template <class Character>
CANN_ASC_STL_API constexpr Character* __asc_strrchr(Character* value, remove_const_t<Character> character) noexcept
{
    Character* result = nullptr;
    for (;; ++value) {
        if (*value == character) {
            result = value;
        }
        if (*value == Character{}) {
            return result;
        }
    }
}

template <class T>
CANN_ASC_STL_API constexpr T* __asc_memchr(T* value, remove_const_t<T> character, __SIZE_TYPE__ count) noexcept
{
    for (__SIZE_TYPE__ index = 0; index < count; ++index) {
        if (value[index] == character) {
            return value + index;
        }
    }
    return nullptr;
}

template <class T>
CANN_ASC_STL_API constexpr T* __asc_memmove(T* destination, const T* source, __SIZE_TYPE__ count) noexcept
{
    if (destination < source) {
        for (__SIZE_TYPE__ index = 0; index < count; ++index) {
            destination[index] = source[index];
        }
    } else if (destination > source) {
        for (__SIZE_TYPE__ index = count; index != 0; --index) {
            destination[index - 1] = source[index - 1];
        }
    }
    return destination;
}

template <class T>
CANN_ASC_STL_API constexpr int __asc_memcmp(const T* left, const T* right, __SIZE_TYPE__ count) noexcept
{
    for (__SIZE_TYPE__ index = 0; index < count; ++index) {
        if (left[index] != right[index]) {
            return left[index] < right[index] ? -1 : 1;
        }
    }
    return 0;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___STRING_CONSTEXPR_C_FUNCTIONS_H
