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
// direct wide classification and conversion functions.  Host delegates to
// the system locale while Device implements the fixed C locale with pure
// range semantics.  The fixed-C-locale predicates live as constexpr detail
// cores so in-library constant evaluation can reuse them on the host side
// as well, while the public facades keep their registered signatures; the
// cores deliberately coexist as wint_t overloads with the narrow-character
// cores of the __cctype root.
//
// Out-of-domain inputs: Device classifies WEOF and every other value
// outside the portable source range as false and converts it unchanged.
// Host preserves the C standard contract instead, where a wint_t value not
// representable as a wchar_t nor equal to WEOF is undefined behavior.
// The wint_t alias repeats the identical underlying type also spelled by
// the descriptors root; the same-type redeclaration is legal when the
// later public facade composes both roots.

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#include <cwctype>
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
using wint_t = unsigned int;
#else
using wint_t = ::std::wint_t;
#endif

namespace detail {

CANN_ASC_STL_API constexpr bool is_upper(wint_t value) noexcept
{
    return value >= L'A' && value <= L'Z';
}

CANN_ASC_STL_API constexpr bool is_lower(wint_t value) noexcept
{
    return value >= L'a' && value <= L'z';
}

CANN_ASC_STL_API constexpr bool is_alpha(wint_t value) noexcept
{
    return is_upper(value) || is_lower(value);
}

CANN_ASC_STL_API constexpr bool is_digit(wint_t value) noexcept
{
    return value >= L'0' && value <= L'9';
}

CANN_ASC_STL_API constexpr bool is_xdigit(wint_t value) noexcept
{
    return is_digit(value) || (value >= L'A' && value <= L'F') || (value >= L'a' && value <= L'f');
}

CANN_ASC_STL_API constexpr bool is_alnum(wint_t value) noexcept
{
    return is_alpha(value) || is_digit(value);
}

CANN_ASC_STL_API constexpr bool is_blank(wint_t value) noexcept
{
    return value == L' ' || value == L'\t';
}

CANN_ASC_STL_API constexpr bool is_space(wint_t value) noexcept
{
    return value == L' ' || (value >= L'\t' && value <= L'\r');
}

CANN_ASC_STL_API constexpr bool is_cntrl(wint_t value) noexcept
{
    return value < wint_t(0x20) || value == wint_t(0x7f);
}

CANN_ASC_STL_API constexpr bool is_print(wint_t value) noexcept
{
    return value >= wint_t(0x20) && value <= wint_t(0x7e);
}

CANN_ASC_STL_API constexpr bool is_graph(wint_t value) noexcept
{
    return value >= wint_t(0x21) && value <= wint_t(0x7e);
}

CANN_ASC_STL_API constexpr bool is_punct(wint_t value) noexcept
{
    return is_graph(value) && !is_alnum(value);
}

CANN_ASC_STL_API constexpr wint_t to_lower(wint_t value) noexcept
{
    return is_upper(value) ? value + (L'a' - L'A') : value;
}

CANN_ASC_STL_API constexpr wint_t to_upper(wint_t value) noexcept
{
    return is_lower(value) ? value - (L'a' - L'A') : value;
}

}  // namespace detail

#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// WEOF is all bits set in the unsigned device wint_t, so it must fall
// outside every classification range; pinned statically so future range
// edits cannot silently break the documented out-of-domain contract.
static_assert(!(detail::is_upper(static_cast<wint_t>(-1)) || detail::is_lower(static_cast<wint_t>(-1)) ||
                  detail::is_alpha(static_cast<wint_t>(-1)) || detail::is_digit(static_cast<wint_t>(-1)) ||
                  detail::is_xdigit(static_cast<wint_t>(-1)) || detail::is_alnum(static_cast<wint_t>(-1)) ||
                  detail::is_blank(static_cast<wint_t>(-1)) || detail::is_space(static_cast<wint_t>(-1)) ||
                  detail::is_cntrl(static_cast<wint_t>(-1)) || detail::is_print(static_cast<wint_t>(-1)) ||
                  detail::is_graph(static_cast<wint_t>(-1)) || detail::is_punct(static_cast<wint_t>(-1))),
    "WEOF must not satisfy any wide classification predicate");
#endif

CANN_ASC_STL_API int iswupper(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::is_upper(value);
#else
    return ::std::iswupper(value);
#endif
}

CANN_ASC_STL_API int iswlower(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::is_lower(value);
#else
    return ::std::iswlower(value);
#endif
}

CANN_ASC_STL_API int iswalpha(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::is_alpha(value);
#else
    return ::std::iswalpha(value);
#endif
}

CANN_ASC_STL_API int iswdigit(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::is_digit(value);
#else
    return ::std::iswdigit(value);
#endif
}

CANN_ASC_STL_API int iswxdigit(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::is_xdigit(value);
#else
    return ::std::iswxdigit(value);
#endif
}

CANN_ASC_STL_API int iswalnum(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::is_alnum(value);
#else
    return ::std::iswalnum(value);
#endif
}

CANN_ASC_STL_API int iswblank(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::is_blank(value);
#else
    return ::std::iswblank(value);
#endif
}

CANN_ASC_STL_API int iswspace(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::is_space(value);
#else
    return ::std::iswspace(value);
#endif
}

CANN_ASC_STL_API int iswcntrl(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::is_cntrl(value);
#else
    return ::std::iswcntrl(value);
#endif
}

CANN_ASC_STL_API int iswprint(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::is_print(value);
#else
    return ::std::iswprint(value);
#endif
}

CANN_ASC_STL_API int iswgraph(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::is_graph(value);
#else
    return ::std::iswgraph(value);
#endif
}

CANN_ASC_STL_API int iswpunct(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::is_punct(value);
#else
    return ::std::iswpunct(value);
#endif
}

CANN_ASC_STL_API wint_t towlower(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::to_lower(value);
#else
    return ::std::towlower(value);
#endif
}

CANN_ASC_STL_API wint_t towupper(wint_t value) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return ::asc::std::detail::to_upper(value);
#else
    return ::std::towupper(value);
#endif
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CWCTYPE_CLASSIFICATION_H
