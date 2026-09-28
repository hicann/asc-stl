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

#ifndef CANN_ASC_STL_STD_DETAIL_CWCHAR_ALGORITHMS_H
#define CANN_ASC_STL_STD_DETAIL_CWCHAR_ALGORITHMS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

// The eighteen non-locale wide algorithms. Host delegates to the system
// <cwchar>; Device computes directly over plain-pointer storage. Sizes spell
// the compiler-provided __SIZE_TYPE__ so the root keeps its single-edge
// closure; the type is identical to asc::std::size_t.
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#include <cwchar>
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

CANN_ASC_STL_API __SIZE_TYPE__ wcslen(const wchar_t* input) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    __SIZE_TYPE__ count = 0;
    while (input[count] != L'\0') {
        ++count;
    }
    return count;
#else
    return ::std::wcslen(input);
#endif
}

CANN_ASC_STL_API int wcscmp(const wchar_t* left, const wchar_t* right) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    while (*left != L'\0' && *left == *right) {
        ++left;
        ++right;
    }
    return *left < *right ? -1 : (*left > *right ? 1 : 0);
#else
    return ::std::wcscmp(left, right);
#endif
}

CANN_ASC_STL_API int wcsncmp(const wchar_t* left, const wchar_t* right, __SIZE_TYPE__ count) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    for (__SIZE_TYPE__ index = 0; index < count; ++index) {
        if (left[index] != right[index]) {
            return left[index] < right[index] ? -1 : 1;
        }
        if (left[index] == L'\0') {
            return 0;
        }
    }
    return 0;
#else
    return ::std::wcsncmp(left, right, count);
#endif
}

CANN_ASC_STL_API wchar_t* wcscpy(wchar_t* destination, const wchar_t* source) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    __SIZE_TYPE__ index = 0;
    do {
        destination[index] = source[index];
    } while (source[index++] != L'\0');
    return destination;
#else
    return ::std::wcscpy(destination, source);
#endif
}

CANN_ASC_STL_API wchar_t* wcsncpy(wchar_t* destination, const wchar_t* source, __SIZE_TYPE__ count) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    __SIZE_TYPE__ index = 0;
    for (; index < count && source[index] != L'\0'; ++index) {
        destination[index] = source[index];
    }
    for (; index < count; ++index) {
        destination[index] = L'\0';
    }
    return destination;
#else
    return ::std::wcsncpy(destination, source, count);
#endif
}

CANN_ASC_STL_API wchar_t* wcscat(wchar_t* destination, const wchar_t* source) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    ::asc::std::wcscpy(destination + ::asc::std::wcslen(destination), source);
    return destination;
#else
    return ::std::wcscat(destination, source);
#endif
}

CANN_ASC_STL_API wchar_t* wcsncat(wchar_t* destination, const wchar_t* source, __SIZE_TYPE__ count) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    wchar_t* output = destination + ::asc::std::wcslen(destination);
    __SIZE_TYPE__ index = 0;
    for (; index < count && source[index] != L'\0'; ++index) {
        output[index] = source[index];
    }
    output[index] = L'\0';
    return destination;
#else
    return ::std::wcsncat(destination, source, count);
#endif
}

CANN_ASC_STL_API const wchar_t* wcschr(const wchar_t* input, wchar_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    for (;; ++input) {
        if (*input == value) {
            return input;
        }
        if (*input == L'\0') {
            return nullptr;
        }
    }
#else
    return ::std::wcschr(input, value);
#endif
}

CANN_ASC_STL_API wchar_t* wcschr(wchar_t* input, wchar_t value) noexcept
{
    return const_cast<wchar_t*>(::asc::std::wcschr(static_cast<const wchar_t*>(input), value));
}

CANN_ASC_STL_API const wchar_t* wcsrchr(const wchar_t* input, wchar_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    const wchar_t* result = nullptr;
    do {
        if (*input == value) {
            result = input;
        }
    } while (*input++ != L'\0');
    return result;
#else
    return ::std::wcsrchr(input, value);
#endif
}

CANN_ASC_STL_API wchar_t* wcsrchr(wchar_t* input, wchar_t value) noexcept
{
    return const_cast<wchar_t*>(::asc::std::wcsrchr(static_cast<const wchar_t*>(input), value));
}

CANN_ASC_STL_API __SIZE_TYPE__ wcsspn(const wchar_t* input, const wchar_t* accepted) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    __SIZE_TYPE__ count = 0;
    for (; input[count] != L'\0'; ++count) {
        if (::asc::std::wcschr(accepted, input[count]) == nullptr) {
            break;
        }
    }
    return count;
#else
    return ::std::wcsspn(input, accepted);
#endif
}

CANN_ASC_STL_API __SIZE_TYPE__ wcscspn(const wchar_t* input, const wchar_t* rejected) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    __SIZE_TYPE__ count = 0;
    for (; input[count] != L'\0'; ++count) {
        if (::asc::std::wcschr(rejected, input[count]) != nullptr) {
            break;
        }
    }
    return count;
#else
    return ::std::wcscspn(input, rejected);
#endif
}

CANN_ASC_STL_API const wchar_t* wcspbrk(const wchar_t* input, const wchar_t* accepted) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    for (; *input != L'\0'; ++input) {
        if (::asc::std::wcschr(accepted, *input) != nullptr) {
            return input;
        }
    }
    return nullptr;
#else
    return ::std::wcspbrk(input, accepted);
#endif
}

CANN_ASC_STL_API wchar_t* wcspbrk(wchar_t* input, const wchar_t* accepted) noexcept
{
    return const_cast<wchar_t*>(::asc::std::wcspbrk(static_cast<const wchar_t*>(input), accepted));
}

CANN_ASC_STL_API const wchar_t* wcsstr(const wchar_t* input, const wchar_t* needle) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    if (*needle == L'\0') {
        return input;
    }
    const __SIZE_TYPE__ length = ::asc::std::wcslen(needle);
    for (; *input != L'\0'; ++input) {
        if (::asc::std::wcsncmp(input, needle, length) == 0) {
            return input;
        }
    }
    return nullptr;
#else
    return ::std::wcsstr(input, needle);
#endif
}

CANN_ASC_STL_API wchar_t* wcsstr(wchar_t* input, const wchar_t* needle) noexcept
{
    return const_cast<wchar_t*>(::asc::std::wcsstr(static_cast<const wchar_t*>(input), needle));
}

CANN_ASC_STL_API const wchar_t* wmemchr(const wchar_t* input, wchar_t value, __SIZE_TYPE__ count) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    for (__SIZE_TYPE__ index = 0; index < count; ++index) {
        if (input[index] == value) {
            return input + index;
        }
    }
    return nullptr;
#else
    return ::std::wmemchr(input, value, count);
#endif
}

CANN_ASC_STL_API wchar_t* wmemchr(wchar_t* input, wchar_t value, __SIZE_TYPE__ count) noexcept
{
    return const_cast<wchar_t*>(::asc::std::wmemchr(static_cast<const wchar_t*>(input), value, count));
}

CANN_ASC_STL_API wchar_t* wmemcpy(wchar_t* destination, const wchar_t* source, __SIZE_TYPE__ count) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    for (__SIZE_TYPE__ index = 0; index < count; ++index) {
        destination[index] = source[index];
    }
    return destination;
#else
    return ::std::wmemcpy(destination, source, count);
#endif
}

CANN_ASC_STL_API wchar_t* wmemmove(wchar_t* destination, const wchar_t* source, __SIZE_TYPE__ count) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    const auto destination_address = reinterpret_cast<__UINTPTR_TYPE__>(destination);
    const auto source_address = reinterpret_cast<__UINTPTR_TYPE__>(source);
    if (destination_address < source_address) {
        for (__SIZE_TYPE__ index = 0; index < count; ++index) {
            destination[index] = source[index];
        }
    } else if (destination_address > source_address) {
        for (__SIZE_TYPE__ index = count; index != 0; --index) {
            destination[index - 1] = source[index - 1];
        }
    }
    return destination;
#else
    return ::std::wmemmove(destination, source, count);
#endif
}

CANN_ASC_STL_API int wmemcmp(const wchar_t* left, const wchar_t* right, __SIZE_TYPE__ count) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    for (__SIZE_TYPE__ index = 0; index < count; ++index) {
        if (left[index] != right[index]) {
            return left[index] < right[index] ? -1 : 1;
        }
    }
    return 0;
#else
    return ::std::wmemcmp(left, right, count);
#endif
}

CANN_ASC_STL_API wchar_t* wmemset(wchar_t* destination, wchar_t value, __SIZE_TYPE__ count) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    for (__SIZE_TYPE__ index = 0; index < count; ++index) {
        destination[index] = value;
    }
    return destination;
#else
    return ::std::wmemset(destination, value, count);
#endif
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_CWCHAR_ALGORITHMS_H
