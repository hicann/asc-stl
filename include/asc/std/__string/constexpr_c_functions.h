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

// Inline equivalents of the source-tree dialect gates (the master __config
// does not provide them): guarded with #ifndef so a future central definition
// wins. Hosted availability mirrors the source tree: device (AI-core)
// compilation is freestanding and must not reach the C runtime.
#ifndef CANN_ASC_STL_DETAIL_HOSTED
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#define CANN_ASC_STL_DETAIL_HOSTED() 0
#else
#define CANN_ASC_STL_DETAIL_HOSTED() 1
#endif
#endif  // CANN_ASC_STL_DETAIL_HOSTED

#ifndef CANN_ASC_STL_DETAIL_RESTRICT
#define CANN_ASC_STL_DETAIL_RESTRICT __restrict
#endif  // CANN_ASC_STL_DETAIL_RESTRICT

// Runtime fast path dispatch: constant evaluation always falls back to the
// portable constexpr loop. Prefer `if !consteval`, then the builtin probe,
// otherwise the fast path is compiled out entirely.
#ifndef CANN_ASC_STL_DETAIL_IF_NOT_CONSTEVAL_DEFAULT
#if defined(__cpp_if_consteval) && __cpp_if_consteval >= 202106L
#define CANN_ASC_STL_DETAIL_IF_NOT_CONSTEVAL_DEFAULT if !consteval
#elif CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_is_constant_evaluated)
#define CANN_ASC_STL_DETAIL_IF_NOT_CONSTEVAL_DEFAULT if (!__builtin_is_constant_evaluated())
#else
#define CANN_ASC_STL_DETAIL_IF_NOT_CONSTEVAL_DEFAULT if constexpr (false)
#endif
#endif  // CANN_ASC_STL_DETAIL_IF_NOT_CONSTEVAL_DEFAULT

#if CANN_ASC_STL_DETAIL_HOSTED()
#include <cstring>
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

CANN_ASC_STL_BEGIN_NAMESPACE

// __asc_strcpy

template <class _CharT>
CANN_ASC_STL_API constexpr _CharT* __asc_strcpy_impl_constexpr(
    _CharT* CANN_ASC_STL_DETAIL_RESTRICT __dst, const _CharT* CANN_ASC_STL_DETAIL_RESTRICT __src) noexcept
{
    _CharT* __dst_it = __dst;
    while ((*__dst_it++ = *__src++) != _CharT('\0')) {
    }
    return __dst;
}

#if CANN_ASC_STL_DETAIL_HOSTED()
template <class _CharT>
CANN_ASC_STL_HOST_API _CharT* __asc_strcpy_impl_host(
    _CharT* CANN_ASC_STL_DETAIL_RESTRICT __dst, const _CharT* CANN_ASC_STL_DETAIL_RESTRICT __src) noexcept
{
    if constexpr (sizeof(_CharT) == 1) {
        return reinterpret_cast<_CharT*>(
            __builtin_strcpy(reinterpret_cast<char*>(__dst), reinterpret_cast<const char*>(__src)));
    } else {
        return ::asc::std::__asc_strcpy_impl_constexpr(__dst, __src);
    }
}
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

template <class _CharT>
CANN_ASC_STL_API constexpr _CharT* __asc_strcpy(
    _CharT* CANN_ASC_STL_DETAIL_RESTRICT __dst, const _CharT* CANN_ASC_STL_DETAIL_RESTRICT __src) noexcept
{
    CANN_ASC_STL_DETAIL_IF_NOT_CONSTEVAL_DEFAULT
    {
#if CANN_ASC_STL_DETAIL_HOSTED() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        return ::asc::std::__asc_strcpy_impl_host(__dst, __src);
#endif
    }
    return ::asc::std::__asc_strcpy_impl_constexpr(__dst, __src);
}

// __asc_strncpy

template <class _CharT>
CANN_ASC_STL_API constexpr _CharT* __asc_strncpy_impl_constexpr(
    _CharT* CANN_ASC_STL_DETAIL_RESTRICT __dst, const _CharT* CANN_ASC_STL_DETAIL_RESTRICT __src, size_t __n) noexcept
{
    _CharT* __dst_it = __dst;
    while (__n--) {
        if ((*__dst_it++ = *__src++) == _CharT('\0')) {
            while (__n--) {
                *__dst_it++ = _CharT('\0');
            }
            break;
        }
    }
    return __dst;
}

#if CANN_ASC_STL_DETAIL_HOSTED()
template <class _CharT>
CANN_ASC_STL_HOST_API _CharT* __asc_strncpy_impl_host(
    _CharT* CANN_ASC_STL_DETAIL_RESTRICT __dst, const _CharT* CANN_ASC_STL_DETAIL_RESTRICT __src, size_t __n) noexcept
{
    if constexpr (sizeof(_CharT) == 1) {
        return reinterpret_cast<_CharT*>(
            ::strncpy(reinterpret_cast<char*>(__dst), reinterpret_cast<const char*>(__src), __n));
    } else {
        return ::asc::std::__asc_strncpy_impl_constexpr(__dst, __src, __n);
    }
}
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

template <class _CharT>
CANN_ASC_STL_API constexpr _CharT* __asc_strncpy(
    _CharT* CANN_ASC_STL_DETAIL_RESTRICT __dst, const _CharT* CANN_ASC_STL_DETAIL_RESTRICT __src, size_t __n) noexcept
{
    CANN_ASC_STL_DETAIL_IF_NOT_CONSTEVAL_DEFAULT
    {
#if CANN_ASC_STL_DETAIL_HOSTED() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        return ::asc::std::__asc_strncpy_impl_host(__dst, __src, __n);
#endif
    }
    return ::asc::std::__asc_strncpy_impl_constexpr(__dst, __src, __n);
}

// __asc_strlen

template <class _CharT>
[[nodiscard]] CANN_ASC_STL_API constexpr size_t __asc_strlen_impl_constexpr(const _CharT* __ptr) noexcept
{
    size_t __len = 0;
    while (*__ptr++ != _CharT('\0')) {
        ++__len;
    }
    return __len;
}

#if CANN_ASC_STL_DETAIL_HOSTED()
template <class _CharT>
[[nodiscard]] CANN_ASC_STL_HOST_API size_t __asc_strlen_impl_host(const _CharT* __ptr) noexcept
{
    if constexpr (sizeof(_CharT) == 1) {
        return ::strlen(reinterpret_cast<const char*>(__ptr));
    } else {
        return ::asc::std::__asc_strlen_impl_constexpr(__ptr);
    }
}
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

template <class _CharT>
[[nodiscard]] CANN_ASC_STL_API constexpr size_t __asc_strlen(const _CharT* __ptr) noexcept
{
    CANN_ASC_STL_DETAIL_IF_NOT_CONSTEVAL_DEFAULT
    {
#if CANN_ASC_STL_DETAIL_HOSTED() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        return ::asc::std::__asc_strlen_impl_host(__ptr);
#endif
    }
    return ::asc::std::__asc_strlen_impl_constexpr(__ptr);
}

// __asc_strcmp

// Comparison follows the C semantics: characters are compared as their
// unsigned promoted representation, so the result is well defined for values
// above SCHAR_MAX.
template <class _CharT>
[[nodiscard]] CANN_ASC_STL_API constexpr int __asc_strcmp_impl_constexpr(
    const _CharT* __lhs, const _CharT* __rhs) noexcept
{
    using _UCharT = __make_nbit_uint_t<sizeof(_CharT) * CHAR_BIT>;

    bool __reached_end = false;
    while (*__lhs == *__rhs) {
        if (*__lhs == _CharT('\0')) {
            __reached_end = true;
            break;
        }

        ++__lhs;
        ++__rhs;
    }
    return __reached_end ? 0 : (static_cast<_UCharT>(*__lhs) < static_cast<_UCharT>(*__rhs)) ? -1 : 1;
}

#if CANN_ASC_STL_DETAIL_HOSTED()
template <class _CharT>
[[nodiscard]] CANN_ASC_STL_HOST_API int __asc_strcmp_impl_host(const _CharT* __lhs, const _CharT* __rhs) noexcept
{
    if constexpr (sizeof(_CharT) == 1) {
        return ::strcmp(reinterpret_cast<const char*>(__lhs), reinterpret_cast<const char*>(__rhs));
    } else {
        return ::asc::std::__asc_strcmp_impl_constexpr(__lhs, __rhs);
    }
}
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

template <class _CharT>
[[nodiscard]] CANN_ASC_STL_API constexpr int __asc_strcmp(const _CharT* __lhs, const _CharT* __rhs) noexcept
{
    CANN_ASC_STL_DETAIL_IF_NOT_CONSTEVAL_DEFAULT
    {
#if CANN_ASC_STL_DETAIL_HOSTED() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        return ::asc::std::__asc_strcmp_impl_host(__lhs, __rhs);
#endif
    }
    return ::asc::std::__asc_strcmp_impl_constexpr(__lhs, __rhs);
}

// __asc_strncmp

template <class _CharT>
[[nodiscard]] CANN_ASC_STL_API constexpr int __asc_strncmp_impl_constexpr(
    const _CharT* __lhs, const _CharT* __rhs, size_t __n) noexcept
{
    using _UCharT = __make_nbit_uint_t<sizeof(_CharT) * CHAR_BIT>;

    int __result = 0;
    while (__n--) {
        if (*__lhs != *__rhs) {
            __result = (static_cast<_UCharT>(*__lhs) < static_cast<_UCharT>(*__rhs)) ? -1 : 1;
            break;
        }

        if (*__lhs == _CharT('\0')) {
            break;
        }

        ++__lhs;
        ++__rhs;
    }
    return __result;
}

#if CANN_ASC_STL_DETAIL_HOSTED()
template <class _CharT>
[[nodiscard]] CANN_ASC_STL_HOST_API int __asc_strncmp_impl_host(
    const _CharT* __lhs, const _CharT* __rhs, size_t __n) noexcept
{
    if constexpr (sizeof(_CharT) == 1) {
        return ::strncmp(reinterpret_cast<const char*>(__lhs), reinterpret_cast<const char*>(__rhs), __n);
    } else {
        return ::asc::std::__asc_strncmp_impl_constexpr(__lhs, __rhs, __n);
    }
}
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

template <class _CharT>
[[nodiscard]] CANN_ASC_STL_API constexpr int __asc_strncmp(
    const _CharT* __lhs, const _CharT* __rhs, size_t __n) noexcept
{
    CANN_ASC_STL_DETAIL_IF_NOT_CONSTEVAL_DEFAULT
    {
#if CANN_ASC_STL_DETAIL_HOSTED() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        return ::asc::std::__asc_strncmp_impl_host(__lhs, __rhs, __n);
#endif
    }
    return ::asc::std::__asc_strncmp_impl_constexpr(__lhs, __rhs, __n);
}

// __asc_strchr

template <class _CharT>
[[nodiscard]] CANN_ASC_STL_API constexpr _CharT* __asc_strchr_impl_constexpr(
    _CharT* __ptr, remove_const_t<_CharT> __c) noexcept
{
    bool __reached_end = false;
    while (*__ptr != __c) {
        if (*__ptr == _CharT('\0')) {
            __reached_end = true;
            break;
        }
        ++__ptr;
    }
    return __reached_end ? nullptr : __ptr;
}

#if CANN_ASC_STL_DETAIL_HOSTED()
template <class _CharT>
[[nodiscard]] CANN_ASC_STL_HOST_API _CharT* __asc_strchr_impl_host(_CharT* __ptr, remove_const_t<_CharT> __c) noexcept
{
    if constexpr (sizeof(_CharT) == 1) {
        using _Up = remove_const_t<_CharT>;
        return const_cast<_CharT*>(
            reinterpret_cast<_Up*>(::strchr(reinterpret_cast<char*>(const_cast<_Up*>(__ptr)), static_cast<int>(__c))));
    } else {
        return ::asc::std::__asc_strchr_impl_constexpr<_CharT>(__ptr, __c);
    }
}
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

template <class _CharT>
[[nodiscard]] CANN_ASC_STL_API constexpr _CharT* __asc_strchr(_CharT* __ptr, remove_const_t<_CharT> __c) noexcept
{
    CANN_ASC_STL_DETAIL_IF_NOT_CONSTEVAL_DEFAULT
    {
#if CANN_ASC_STL_DETAIL_HOSTED() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        return ::asc::std::__asc_strchr_impl_host<_CharT>(__ptr, __c);
#endif
    }
    return ::asc::std::__asc_strchr_impl_constexpr<_CharT>(__ptr, __c);
}

// __asc_strrchr

template <class _CharT>
[[nodiscard]] CANN_ASC_STL_API constexpr _CharT* __asc_strrchr_impl_constexpr(
    _CharT* __ptr, remove_const_t<_CharT> __c) noexcept
{
    if (__c == _CharT('\0')) {
        return __ptr + ::asc::std::__asc_strlen(__ptr);
    }

    _CharT* __last{};
    while (*__ptr != _CharT('\0')) {
        if (*__ptr == __c) {
            __last = __ptr;
        }
        ++__ptr;
    }
    return __last;
}

#if CANN_ASC_STL_DETAIL_HOSTED()
template <class _CharT>
[[nodiscard]] CANN_ASC_STL_HOST_API _CharT* __asc_strrchr_impl_host(_CharT* __ptr, remove_const_t<_CharT> __c) noexcept
{
    if constexpr (sizeof(_CharT) == 1) {
        using _Up = remove_const_t<_CharT>;
        return const_cast<_CharT*>(
            reinterpret_cast<_Up*>(::strrchr(reinterpret_cast<char*>(const_cast<_Up*>(__ptr)), static_cast<int>(__c))));
    } else {
        return ::asc::std::__asc_strrchr_impl_constexpr<_CharT>(__ptr, __c);
    }
}
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

template <class _CharT>
[[nodiscard]] CANN_ASC_STL_API constexpr _CharT* __asc_strrchr(_CharT* __ptr, remove_const_t<_CharT> __c) noexcept
{
    CANN_ASC_STL_DETAIL_IF_NOT_CONSTEVAL_DEFAULT
    {
#if CANN_ASC_STL_DETAIL_HOSTED() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        return ::asc::std::__asc_strrchr_impl_host<_CharT>(__ptr, __c);
#endif
    }
    return ::asc::std::__asc_strrchr_impl_constexpr<_CharT>(__ptr, __c);
}

// __asc_memchr

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr _Tp* __asc_memchr_impl_constexpr(
    _Tp* __ptr, remove_const_t<_Tp> __c, size_t __n) noexcept
{
    _Tp* __result = nullptr;
    while (__n--) {
        if (*__ptr == __c) {
            __result = __ptr;
            break;
        }
        ++__ptr;
    }
    return __result;
}

#if CANN_ASC_STL_DETAIL_HOSTED()
template <class _Tp>
[[nodiscard]] CANN_ASC_STL_HOST_API _Tp* __asc_memchr_impl_host(
    _Tp* __ptr, remove_const_t<_Tp> __c, size_t __n) noexcept
{
    if constexpr (sizeof(_Tp) == 1) {
        using _Up = remove_const_t<_Tp>;
        return const_cast<_Tp*>(reinterpret_cast<_Up*>(::memchr(const_cast<_Up*>(__ptr), static_cast<int>(__c), __n)));
    } else {
        return ::asc::std::__asc_memchr_impl_constexpr<_Tp>(__ptr, __c, __n);
    }
}
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr _Tp* __asc_memchr(_Tp* __ptr, remove_const_t<_Tp> __c, size_t __n) noexcept
{
    CANN_ASC_STL_DETAIL_IF_NOT_CONSTEVAL_DEFAULT
    {
#if CANN_ASC_STL_DETAIL_HOSTED() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        return ::asc::std::__asc_memchr_impl_host<_Tp>(__ptr, __c, __n);
#endif
    }
    return ::asc::std::__asc_memchr_impl_constexpr<_Tp>(__ptr, __c, __n);
}

// __asc_memmove

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr _Tp* __asc_memmove_impl_constexpr(
    _Tp* __dst, const _Tp* __src, size_t __n) noexcept
{
    const auto __dst_copy = __dst;

    if (__src < __dst && __dst < __src + __n) {
        __dst += __n;
        __src += __n;

        while (__n-- > 0) {
            *--__dst = *--__src;
        }
    } else {
        while (__n-- > 0) {
            *__dst++ = *__src++;
        }
    }
    return __dst_copy;
}

#if CANN_ASC_STL_DETAIL_HOSTED()
template <class _Tp>
[[nodiscard]] CANN_ASC_STL_HOST_API _Tp* __asc_memmove_impl_host(_Tp* __dst, const _Tp* __src, size_t __n) noexcept
{
    return reinterpret_cast<_Tp*>(::memmove(__dst, __src, __n * sizeof(_Tp)));
}
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

template <class _Tp>
CANN_ASC_STL_API constexpr _Tp* __asc_memmove(_Tp* __dst, const _Tp* __src, size_t __n) noexcept
{
    CANN_ASC_STL_DETAIL_IF_NOT_CONSTEVAL_DEFAULT
    {
#if (defined(__GNUC__) || defined(__clang__)) && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        return reinterpret_cast<_Tp*>(__builtin_memmove(__dst, __src, __n * sizeof(_Tp)));
#else
#if CANN_ASC_STL_DETAIL_HOSTED() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        return ::asc::std::__asc_memmove_impl_host(__dst, __src, __n);
#endif
#endif
    }
    return ::asc::std::__asc_memmove_impl_constexpr(__dst, __src, __n);
}

// __asc_memcmp

// Like strcmp, memcmp compares the unsigned representations, matching the C
// standard library contract instead of the signed character ordering.
template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr int __asc_memcmp_impl_constexpr(
    const _Tp* __lhs, const _Tp* __rhs, size_t __n) noexcept
{
    using _Up = __make_nbit_uint_t<sizeof(_Tp) * CHAR_BIT>;

    int __result = 0;
    while (__n--) {
        if (*__lhs != *__rhs) {
            __result = static_cast<_Up>(*__lhs) < static_cast<_Up>(*__rhs) ? -1 : 1;
            break;
        }
        ++__lhs;
        ++__rhs;
    }
    return __result;
}

#if CANN_ASC_STL_DETAIL_HOSTED()
template <class _Tp>
[[nodiscard]] CANN_ASC_STL_HOST_API int __asc_memcmp_impl_host(const _Tp* __lhs, const _Tp* __rhs, size_t __n) noexcept
{
    if constexpr (sizeof(_Tp) == 1) {
        return ::memcmp(__lhs, __rhs, __n);
    } else {
        return ::asc::std::__asc_memcmp_impl_constexpr(__lhs, __rhs, __n);
    }
}
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr int __asc_memcmp(const _Tp* __lhs, const _Tp* __rhs, size_t __n) noexcept
{
    CANN_ASC_STL_DETAIL_IF_NOT_CONSTEVAL_DEFAULT
    {
#if (defined(__GNUC__) || defined(__clang__)) && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        return __builtin_memcmp(__lhs, __rhs, __n * sizeof(_Tp));
#else
#if CANN_ASC_STL_DETAIL_HOSTED() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        return ::asc::std::__asc_memcmp_impl_host(__lhs, __rhs, __n);
#endif
#endif
    }
    return ::asc::std::__asc_memcmp_impl_constexpr(__lhs, __rhs, __n);
}

// __asc_memcpy

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr _Tp* __asc_memcpy_impl_constexpr(
    _Tp* CANN_ASC_STL_DETAIL_RESTRICT __dst, const _Tp* CANN_ASC_STL_DETAIL_RESTRICT __src, size_t __n) noexcept
{
    const auto __dst_copy = __dst;

    while (__n--) {
        *__dst++ = *__src++;
    }
    return __dst_copy;
}

#if CANN_ASC_STL_DETAIL_HOSTED()
template <class _Tp>
[[nodiscard]] CANN_ASC_STL_HOST_API _Tp* __asc_memcpy_impl_host(
    _Tp* CANN_ASC_STL_DETAIL_RESTRICT __dst, const _Tp* CANN_ASC_STL_DETAIL_RESTRICT __src, size_t __n) noexcept
{
    return reinterpret_cast<_Tp*>(::memcpy(__dst, __src, __n * sizeof(_Tp)));
}
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

template <class _Tp>
CANN_ASC_STL_API constexpr _Tp* __asc_memcpy(
    _Tp* CANN_ASC_STL_DETAIL_RESTRICT __dst, const _Tp* CANN_ASC_STL_DETAIL_RESTRICT __src, size_t __n) noexcept
{
    CANN_ASC_STL_DETAIL_IF_NOT_CONSTEVAL_DEFAULT
    {
#if CANN_ASC_STL_DETAIL_HOSTED() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        return ::asc::std::__asc_memcpy_impl_host(__dst, __src, __n);
#endif
    }
    return ::asc::std::__asc_memcpy_impl_constexpr(__dst, __src, __n);
}

// __asc_memset

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr _Tp* __asc_memset_impl_constexpr(_Tp* __ptr, _Tp __c, size_t __n) noexcept
{
    const auto __ptr_copy = __ptr;

    while (__n--) {
        *__ptr++ = __c;
    }
    return __ptr_copy;
}

#if CANN_ASC_STL_DETAIL_HOSTED()
template <class _Tp>
[[nodiscard]] CANN_ASC_STL_HOST_API _Tp* __asc_memset_impl_host(_Tp* __ptr, _Tp __c, size_t __n) noexcept
{
    if constexpr (sizeof(_Tp) == 1) {
        return reinterpret_cast<_Tp*>(::memset(__ptr, static_cast<int>(__c), __n));
    } else {
        return ::asc::std::__asc_memset_impl_constexpr(__ptr, __c, __n);
    }
}
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

template <class _Tp>
CANN_ASC_STL_API constexpr _Tp* __asc_memset(_Tp* __ptr, _Tp __c, size_t __n) noexcept
{
    // Byte-wise fill is only equivalent to the element-wise loop for
    // one-byte element types; wider elements keep the portable loop.
    CANN_ASC_STL_DETAIL_IF_NOT_CONSTEVAL_DEFAULT
    {
#if (defined(__GNUC__) || defined(__clang__)) && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        if constexpr (sizeof(_Tp) == 1) {
            return reinterpret_cast<_Tp*>(__builtin_memset(__ptr, static_cast<int>(__c), __n));
        }
#elif CANN_ASC_STL_DETAIL_HOSTED()
        return ::asc::std::__asc_memset_impl_host(__ptr, __c, __n);
#endif
    }
    return ::asc::std::__asc_memset_impl_constexpr(__ptr, __c, __n);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___STRING_CONSTEXPR_C_FUNCTIONS_H
