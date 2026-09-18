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

#ifndef CANN_ASC_STL_STD_DETAIL_CHARCONV_CHARS_FORMAT_H
#define CANN_ASC_STL_STD_DETAIL_CHARCONV_CHARS_FORMAT_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__utility/to_underlying.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

enum class chars_format {
    // Keep these values independent of the host standard library so hosted and
    // CCE/freestanding compilations share one stable representation.
    scientific = 0x1,
    fixed = 0x2,
    hex = 0x4,
    general = fixed | scientific,
};

[[nodiscard]] CANN_ASC_STL_API constexpr chars_format operator~(chars_format __v) noexcept
{
    return chars_format(~asc::std::to_underlying(__v));
}

[[nodiscard]] CANN_ASC_STL_API constexpr chars_format operator&(chars_format __lhs, chars_format __rhs) noexcept
{
    return chars_format(asc::std::to_underlying(__lhs) & asc::std::to_underlying(__rhs));
}

[[nodiscard]] CANN_ASC_STL_API constexpr chars_format operator|(chars_format __lhs, chars_format __rhs) noexcept
{
    return chars_format(asc::std::to_underlying(__lhs) | asc::std::to_underlying(__rhs));
}

[[nodiscard]] CANN_ASC_STL_API constexpr chars_format operator^(chars_format __lhs, chars_format __rhs) noexcept
{
    return chars_format(asc::std::to_underlying(__lhs) ^ asc::std::to_underlying(__rhs));
}

CANN_ASC_STL_API constexpr chars_format& operator&=(chars_format& __lhs, chars_format __rhs) noexcept
{
    __lhs = __lhs & __rhs;
    return __lhs;
}

CANN_ASC_STL_API constexpr chars_format& operator|=(chars_format& __lhs, chars_format __rhs) noexcept
{
    __lhs = __lhs | __rhs;
    return __lhs;
}

CANN_ASC_STL_API constexpr chars_format& operator^=(chars_format& __lhs, chars_format __rhs) noexcept
{
    __lhs = __lhs ^ __rhs;
    return __lhs;
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_CHARCONV_CHARS_FORMAT_H
