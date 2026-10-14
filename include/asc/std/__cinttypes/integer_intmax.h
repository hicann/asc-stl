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

// Implementation root for the later public <asc/std/cinttypes>: the intmax
// vocabulary (intmax_t/uintmax_t/imaxdiv_t plus imaxabs/imaxdiv) and its
// helpers live here so the facade stays a pure forwarding unit. The
// arithmetic is pure integer with no runtime dependency, so it stays valid
// in every execution space. INTMAX_MIN keeps its two's-complement identity:
// intmax_abs reports the sentinel pair and intmax_abs_representable lets
// callers reject the minimum as a domain error instead of wrapping.

CANN_ASC_STL_BEGIN_NAMESPACE

namespace detail {

CANN_ASC_STL_API constexpr __INTMAX_TYPE__ intmax_max() noexcept
{
    return static_cast<__INTMAX_TYPE__>(~static_cast<__UINTMAX_TYPE__>(0) >> 1);
}

CANN_ASC_STL_API constexpr __INTMAX_TYPE__ intmax_min() noexcept
{
    return ~intmax_max();
}

CANN_ASC_STL_API constexpr __INTMAX_TYPE__ intmax_abs(__INTMAX_TYPE__ value) noexcept
{
    return value < 0 ? -value : value;
}

CANN_ASC_STL_API constexpr bool intmax_abs_representable(__INTMAX_TYPE__ value) noexcept
{
    return value != intmax_min();
}

}  // namespace detail

using intmax_t = __INTMAX_TYPE__;
using uintmax_t = __UINTMAX_TYPE__;
struct imaxdiv_t {
    intmax_t quot;
    intmax_t rem;
};
CANN_ASC_STL_API constexpr intmax_t imaxabs(intmax_t value) noexcept
{
    return ::asc::std::detail::intmax_abs(value);
}
CANN_ASC_STL_API constexpr imaxdiv_t imaxdiv(intmax_t numerator, intmax_t denominator) noexcept
{
    // 除零守卫：零除数替换为 1（与 __chrono/__safe_divisor 同例，避免设备侧
    // 静态检查的除零告警），此时 quot = numerator、rem = 0。
    const intmax_t divisor = denominator == intmax_t(0) ? intmax_t(1) : denominator;
    return {numerator / divisor, numerator % divisor};
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CINTTYPES_INTEGER_INTMAX_H
