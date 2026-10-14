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

#ifndef CANN_ASC_STL_ASC_STD___CWCTYPE_DESCRIPTORS_H
#define CANN_ASC_STL_ASC_STD___CWCTYPE_DESCRIPTORS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

// Implementation root for the later public <asc/std/cwctype>: the descriptor
// vocabulary (wctype_t/wctrans_t, wctype/wctrans) and the descriptor-driven
// queries (iswctype/towctrans).  This root shares one delivery unit with the
// classification root and therefore cannot include it; the dispatch repeats
// the fixed-C-locale range predicates through local detail helpers (the
// wide_* spelling, disjoint from the classification root's is_* cores) so
// both roots stay self-contained while contributing to the same reserved
// asc::std::detail layer used by the other C-wrapper roots.  The wint_t
// alias repeats the identical underlying type also spelled by the
// classification root, which is a legal same-type redeclaration when the
// later public facade composes both roots.

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#include <cwctype>
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
using wint_t = unsigned int;
using wctype_t = unsigned int;
using wctrans_t = unsigned int;
#else
using wint_t = ::std::wint_t;
using wctype_t = ::std::wctype_t;
using wctrans_t = ::std::wctrans_t;
#endif

#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
namespace detail {

enum : wctrans_t {
    trans_none = 0,
    trans_lower = 1,
    trans_upper = 2,
};

enum : wctype_t {
    class_none = 0,
    class_alnum = 1,
    class_alpha = 2,
    class_blank = 3,
    class_cntrl = 4,
    class_digit = 5,
    class_graph = 6,
    class_lower = 7,
    class_print = 8,
    class_punct = 9,
    class_space = 10,
    class_upper = 11,
    class_xdigit = 12,
};

CANN_ASC_STL_API bool range_in(wint_t value, wint_t low, wint_t high) noexcept
{
    return value >= low && value <= high;
}

CANN_ASC_STL_API bool wide_is_upper(wint_t value) noexcept
{
    return range_in(value, L'A', L'Z');
}

CANN_ASC_STL_API bool wide_is_lower(wint_t value) noexcept
{
    return range_in(value, L'a', L'z');
}

CANN_ASC_STL_API bool wide_is_digit(wint_t value) noexcept
{
    return range_in(value, L'0', L'9');
}

CANN_ASC_STL_API bool wide_is_alpha(wint_t value) noexcept
{
    return wide_is_upper(value) || wide_is_lower(value);
}

CANN_ASC_STL_API bool wide_is_alnum(wint_t value) noexcept
{
    return wide_is_alpha(value) || wide_is_digit(value);
}

CANN_ASC_STL_API bool wide_is_graph(wint_t value) noexcept
{
    return range_in(value, wint_t(0x21), wint_t(0x7e));
}

// Ordinary AICore places string literals in global memory, so property names
// are matched character by character instead of against string literals.
CANN_ASC_STL_API bool match_property(const char* input, char a, char b, char c, char d, char e) noexcept
{
    return input != nullptr && input[0] == a && input[1] == b && input[2] == c && input[3] == d && input[4] == e &&
        input[5] == '\0';
}

CANN_ASC_STL_API bool match_property(const char* input, char a, char b, char c, char d, char e, char f) noexcept
{
    return input != nullptr && input[0] == a && input[1] == b && input[2] == c && input[3] == d && input[4] == e &&
        input[5] == f && input[6] == '\0';
}

CANN_ASC_STL_API bool match_property(const char* input, char a, char b, char c, char d, char e, char f, char g) noexcept
{
    return input != nullptr && input[0] == a && input[1] == b && input[2] == c && input[3] == d && input[4] == e &&
        input[5] == f && input[6] == g && input[7] == '\0';
}

CANN_ASC_STL_API bool wide_matches(wint_t value, wctype_t descriptor) noexcept
{
    switch (descriptor) {
        case class_alnum:
            return wide_is_alnum(value);
        case class_alpha:
            return wide_is_alpha(value);
        case class_blank:
            return value == L' ' || value == L'\t';
        case class_cntrl:
            return value < wint_t(0x20) || value == wint_t(0x7f);
        case class_digit:
            return wide_is_digit(value);
        case class_graph:
            return wide_is_graph(value);
        case class_lower:
            return wide_is_lower(value);
        case class_print:
            return range_in(value, wint_t(0x20), wint_t(0x7e));
        case class_punct:
            return wide_is_graph(value) && !wide_is_alnum(value);
        case class_space:
            return value == L' ' || range_in(value, L'\t', L'\r');
        case class_upper:
            return wide_is_upper(value);
        case class_xdigit:
            return wide_is_digit(value) || range_in(value, L'A', L'F') || range_in(value, L'a', L'f');
        default:
            return false;
    }
}

CANN_ASC_STL_API wint_t wide_convert(wint_t value, wctrans_t descriptor) noexcept
{
    if (descriptor == trans_lower) {
        return wide_is_upper(value) ? value + (L'a' - L'A') : value;
    }
    if (descriptor == trans_upper) {
        return wide_is_lower(value) ? value - (L'a' - L'A') : value;
    }
    return value;
}

}  // namespace detail
#endif

CANN_ASC_STL_API wctype_t wctype(const char* property) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    if (property == nullptr) {
        return detail::class_none;
    }
    if (detail::match_property(property, 'a', 'l', 'n', 'u', 'm'))
        return detail::class_alnum;
    if (detail::match_property(property, 'a', 'l', 'p', 'h', 'a'))
        return detail::class_alpha;
    if (detail::match_property(property, 'b', 'l', 'a', 'n', 'k'))
        return detail::class_blank;
    if (detail::match_property(property, 'c', 'n', 't', 'r', 'l'))
        return detail::class_cntrl;
    if (detail::match_property(property, 'd', 'i', 'g', 'i', 't'))
        return detail::class_digit;
    if (detail::match_property(property, 'g', 'r', 'a', 'p', 'h'))
        return detail::class_graph;
    if (detail::match_property(property, 'l', 'o', 'w', 'e', 'r'))
        return detail::class_lower;
    if (detail::match_property(property, 'p', 'r', 'i', 'n', 't'))
        return detail::class_print;
    if (detail::match_property(property, 'p', 'u', 'n', 'c', 't'))
        return detail::class_punct;
    if (detail::match_property(property, 's', 'p', 'a', 'c', 'e'))
        return detail::class_space;
    if (detail::match_property(property, 'u', 'p', 'p', 'e', 'r'))
        return detail::class_upper;
    if (detail::match_property(property, 'x', 'd', 'i', 'g', 'i', 't'))
        return detail::class_xdigit;
    return detail::class_none;
#else
    return ::std::wctype(property);
#endif
}

CANN_ASC_STL_API int iswctype(wint_t value, wctype_t descriptor) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return detail::wide_matches(value, descriptor) ? 1 : 0;
#else
    return ::std::iswctype(value, descriptor);
#endif
}

CANN_ASC_STL_API wctrans_t wctrans(const char* property) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    if (property == nullptr) {
        return detail::trans_none;
    }
    if (detail::match_property(property, 't', 'o', 'l', 'o', 'w', 'e', 'r'))
        return detail::trans_lower;
    if (detail::match_property(property, 't', 'o', 'u', 'p', 'p', 'e', 'r'))
        return detail::trans_upper;
    return detail::trans_none;
#else
    return ::std::wctrans(property);
#endif
}

CANN_ASC_STL_API wint_t towctrans(wint_t value, wctrans_t descriptor) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return detail::wide_convert(value, descriptor);
#else
    return ::std::towctrans(value, descriptor);
#endif
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CWCTYPE_DESCRIPTORS_H
