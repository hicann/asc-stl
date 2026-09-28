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

#ifndef CANN_ASC_STL_ASC_STD___CINTTYPES_INTEGER_INTMAX_H
#define CANN_ASC_STL_ASC_STD___CINTTYPES_INTEGER_INTMAX_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

namespace detail {

// Pure-integer intmax vocabulary owned by this native path: the absolute
// value, division and remainder helpers avoid any floating-point or runtime
// dependency so they stay valid in every execution space.  INT64_MIN keeps
// its two's-complement identity; intmax_abs reports the sentinel pair so
// callers can reject it as a domain error instead of wrapping.
CANN_ASC_STL_API constexpr __INT64_TYPE__ intmax_max() noexcept
{
    return static_cast<__INT64_TYPE__>(~static_cast<__UINT64_TYPE__>(0) >> 1);
}

CANN_ASC_STL_API constexpr __INT64_TYPE__ intmax_min() noexcept
{
    return ~intmax_max();
}

CANN_ASC_STL_API constexpr __INT64_TYPE__ intmax_abs(__INT64_TYPE__ value) noexcept
{
    return value < 0 ? -value : value;
}

CANN_ASC_STL_API constexpr bool intmax_abs_representable(__INT64_TYPE__ value) noexcept
{
    return value != intmax_min();
}

}  // namespace detail

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CINTTYPES_INTEGER_INTMAX_H
