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

#ifndef CANN_ASC_STL_ASC_STD___CWCTYPE_CLASSIFICATION_H
#define CANN_ASC_STL_ASC_STD___CWCTYPE_CLASSIFICATION_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

// Implementation root for the later public <asc/std/cwctype>: the fourteen
// direct wide classification and conversion functions.  Host delegates to the
// system locale while Device implements the fixed C locale with pure range
// semantics, so WEOF and every other out-of-domain value classifies as false
// and converts unchanged.  The wint_t alias repeats the identical underlying
// type also spelled by the descriptors root; the same-type redeclaration is
// legal when the later public facade composes both roots.

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#include <cwctype>
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
using wint_t = unsigned int;
#else
using wint_t = ::std::wint_t;
#endif

CANN_ASC_STL_API int iswupper(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return value >= L'A' && value <= L'Z';
#else
    return ::std::iswupper(value);
#endif
}

CANN_ASC_STL_API int iswlower(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return value >= L'a' && value <= L'z';
#else
    return ::std::iswlower(value);
#endif
}

CANN_ASC_STL_API int iswalpha(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return iswupper(value) || iswlower(value);
#else
    return ::std::iswalpha(value);
#endif
}

CANN_ASC_STL_API int iswdigit(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return value >= L'0' && value <= L'9';
#else
    return ::std::iswdigit(value);
#endif
}

CANN_ASC_STL_API int iswxdigit(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return iswdigit(value) || (value >= L'A' && value <= L'F') || (value >= L'a' && value <= L'f');
#else
    return ::std::iswxdigit(value);
#endif
}

CANN_ASC_STL_API int iswalnum(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return iswalpha(value) || iswdigit(value);
#else
    return ::std::iswalnum(value);
#endif
}

CANN_ASC_STL_API int iswblank(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return value == L' ' || value == L'\t';
#else
    return ::std::iswblank(value);
#endif
}

CANN_ASC_STL_API int iswspace(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return value == L' ' || (value >= L'\t' && value <= L'\r');
#else
    return ::std::iswspace(value);
#endif
}

CANN_ASC_STL_API int iswcntrl(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return value < 0x20 || value == 0x7f;
#else
    return ::std::iswcntrl(value);
#endif
}

CANN_ASC_STL_API int iswprint(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return value >= 0x20 && value <= 0x7e;
#else
    return ::std::iswprint(value);
#endif
}

CANN_ASC_STL_API int iswgraph(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return value >= 0x21 && value <= 0x7e;
#else
    return ::std::iswgraph(value);
#endif
}

CANN_ASC_STL_API int iswpunct(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return iswgraph(value) && !iswalnum(value);
#else
    return ::std::iswpunct(value);
#endif
}

CANN_ASC_STL_API wint_t towlower(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return iswupper(value) ? value + (L'a' - L'A') : value;
#else
    return ::std::towlower(value);
#endif
}

CANN_ASC_STL_API wint_t towupper(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return iswlower(value) ? value - (L'a' - L'A') : value;
#else
    return ::std::towupper(value);
#endif
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CWCTYPE_CLASSIFICATION_H
