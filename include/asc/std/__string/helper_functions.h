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

#ifndef CANN_ASC_STL_ASC_STD___STRING_HELPER_FUNCTIONS_H
#define CANN_ASC_STL_ASC_STD___STRING_HELPER_FUNCTIONS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/find.h>
#include <asc/std/__algorithm/find_end.h>
#include <asc/std/__algorithm/find_first_of.h>
#include <asc/std/__algorithm/min.h>
#include <asc/std/__cstddef/types.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__string/char_traits.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _CharT, class _SizeT, class _Traits, _SizeT __npos>
CANN_ASC_STL_API constexpr _SizeT __asc_str_find(const _CharT* __p, _SizeT __sz, _CharT __c, _SizeT __pos) noexcept
{
    if (__pos >= __sz) {
        return __npos;
    }
    const _CharT* __r = _Traits::find(__p + __pos, __sz - __pos, __c);
    if (__r == nullptr) {
        return __npos;
    }
    return static_cast<_SizeT>(__r - __p);
}

template <class _CharT, class _Traits>
CANN_ASC_STL_API constexpr const _CharT* __asc_search_substring(
    const _CharT* __first1, const _CharT* __last1, const _CharT* __first2, const _CharT* __last2)
{
    // Take advantage of knowing source and pattern lengths.
    // Stop short when source is smaller than pattern.
    const ptrdiff_t __len2 = __last2 - __first2;
    if (__len2 == 0) {
        return __first1;
    }

    ptrdiff_t __len1 = __last1 - __first1;
    if (__len1 < __len2) {
        return __last1;
    }

    // First element of __first2 is loop invariant.
    _CharT __f2 = *__first2;
    while (true) {
        __len1 = __last1 - __first1;
        // Check whether __first1 still has at least __len2 bytes.
        if (__len1 < __len2) {
            break;
        }

        // Find __f2 the first byte matching in __first1.
        __first1 = _Traits::find(__first1, __len1 - __len2 + 1, __f2);
        if (__first1 == 0) {
            break;
        }

        // It is faster to compare from the first byte of __first1 even if we
        // already know that it matches the first byte of __first2: this is because
        // __first2 is most likely aligned, as it is user's "pattern" string, and
        // __first1 + 1 is most likely not aligned, as the match is in the middle of
        // the string.
        if (_Traits::compare(__first1, __first2, __len2) == 0) {
            __last1 = __first1;
            break;
        }

        ++__first1;
    }
    return __last1;
}

template <class _CharT, class _SizeT, class _Traits, _SizeT __npos>
CANN_ASC_STL_API constexpr _SizeT __asc_str_find(
    const _CharT* __p, _SizeT __sz, const _CharT* __s, _SizeT __pos, _SizeT __n) noexcept
{
    if (__pos > __sz) {
        return __npos;
    }

    if (__n == 0)  // There is nothing to search, just return __pos.
    {
        return __pos;
    }

    const _CharT* __r = ::asc::std::__asc_search_substring<_CharT, _Traits>(__p + __pos, __p + __sz, __s, __s + __n);

    if (__r == __p + __sz) {
        return __npos;
    }
    return static_cast<_SizeT>(__r - __p);
}

template <class _CharT, class _SizeT, class _Traits, _SizeT __npos>
CANN_ASC_STL_API constexpr _SizeT __asc_str_rfind(const _CharT* __p, _SizeT __sz, _CharT __c, _SizeT __pos) noexcept
{
    if (__sz < 1) {
        return __npos;
    }
    if (__pos < __sz) {
        ++__pos;
    } else {
        __pos = __sz;
    }
    _SizeT __result = __npos;
    for (const _CharT* __ps = __p + __pos; __ps != __p;) {
        if (_Traits::eq(*--__ps, __c)) {
            __result = static_cast<_SizeT>(__ps - __p);
            break;
        }
    }
    return __result;
}

template <class _CharT, class _SizeT, class _Traits, _SizeT __npos>
CANN_ASC_STL_API constexpr _SizeT __asc_str_rfind(
    const _CharT* __p, _SizeT __sz, const _CharT* __s, _SizeT __pos, _SizeT __n) noexcept
{
    __pos = ::asc::std::min(__pos, __sz);  // NOLINT(build/include_what_you_use)
    if (__n < __sz - __pos) {
        __pos += __n;
    } else {
        __pos = __sz;
    }
    const _CharT* __r = ::asc::std::find_end(__p, __p + __pos, __s, __s + __n, _Traits::eq);
    if (__n > 0 && __r == __p + __pos) {
        return __npos;
    }
    return static_cast<_SizeT>(__r - __p);
}

template <class _CharT, class _SizeT, class _Traits, _SizeT __npos>
CANN_ASC_STL_API constexpr _SizeT __asc_str_find_first_of(
    const _CharT* __p, _SizeT __sz, const _CharT* __s, _SizeT __pos, _SizeT __n) noexcept
{
    if (__pos >= __sz || __n == 0) {
        return __npos;
    }
    const _CharT* __r = ::asc::std::find_first_of(__p + __pos, __p + __sz, __s, __s + __n, _Traits::eq);
    if (__r == __p + __sz) {
        return __npos;
    }
    return static_cast<_SizeT>(__r - __p);
}

template <class _CharT, class _SizeT, class _Traits, _SizeT __npos>
CANN_ASC_STL_API constexpr _SizeT __asc_str_find_last_of(
    const _CharT* __p, _SizeT __sz, const _CharT* __s, _SizeT __pos, _SizeT __n) noexcept
{
    if (__n == 0) {
        return __npos;
    }
    if (__pos < __sz) {
        ++__pos;
    } else {
        __pos = __sz;
    }
    _SizeT __result = __npos;
    for (const _CharT* __ps = __p + __pos; __ps != __p;) {
        if (_Traits::find(__s, __n, *--__ps) != nullptr) {
            __result = static_cast<_SizeT>(__ps - __p);
            break;
        }
    }
    return __result;
}

template <class _CharT, class _SizeT, class _Traits, _SizeT __npos>
CANN_ASC_STL_API constexpr _SizeT __asc_str_find_first_not_of(
    const _CharT* __p, _SizeT __sz, const _CharT* __s, _SizeT __pos, _SizeT __n) noexcept
{
    if (__pos >= __sz) {
        return __npos;
    }
    const _CharT* __pe = __p + __sz;
    _SizeT __result = __npos;
    for (const _CharT* __ps = __p + __pos; __ps != __pe; ++__ps) {
        if (_Traits::find(__s, __n, *__ps) == nullptr) {
            __result = static_cast<_SizeT>(__ps - __p);
            break;
        }
    }
    return __result;
}

template <class _CharT, class _SizeT, class _Traits, _SizeT __npos>
CANN_ASC_STL_API constexpr _SizeT __asc_str_find_first_not_of(
    const _CharT* __p, _SizeT __sz, _CharT __c, _SizeT __pos) noexcept
{
    _SizeT __result = __npos;
    if (__pos < __sz) {
        const _CharT* __pe = __p + __sz;
        for (const _CharT* __ps = __p + __pos; __ps != __pe; ++__ps) {
            if (!_Traits::eq(*__ps, __c)) {
                __result = static_cast<_SizeT>(__ps - __p);
                break;
            }
        }
    }
    return __result;
}

template <class _CharT, class _SizeT, class _Traits, _SizeT __npos>
CANN_ASC_STL_API constexpr _SizeT __asc_str_find_last_not_of(
    const _CharT* __p, _SizeT __sz, const _CharT* __s, _SizeT __pos, _SizeT __n) noexcept
{
    if (__pos < __sz) {
        ++__pos;
    } else {
        __pos = __sz;
    }

    _SizeT __result = __npos;
    for (const _CharT* __ps = __p + __pos; __ps != __p;) {
        if (_Traits::find(__s, __n, *--__ps) == nullptr) {
            __result = static_cast<_SizeT>(__ps - __p);
            break;
        }
    }
    return __result;
}

template <class _CharT, class _SizeT, class _Traits, _SizeT __npos>
CANN_ASC_STL_API constexpr _SizeT __asc_str_find_last_not_of(
    const _CharT* __p, _SizeT __sz, _CharT __c, _SizeT __pos) noexcept
{
    if (__pos < __sz) {
        ++__pos;
    } else {
        __pos = __sz;
    }
    _SizeT __result = __npos;
    for (const _CharT* __ps = __p + __pos; __ps != __p;) {
        if (!_Traits::eq(*--__ps, __c)) {
            __result = static_cast<_SizeT>(__ps - __p);
            break;
        }
    }
    return __result;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___STRING_HELPER_FUNCTIONS_H
