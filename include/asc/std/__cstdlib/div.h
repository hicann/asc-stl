/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#ifndef CANN_ASC_STL_STD_DETAIL_CSTDLIB_DIV_H
#define CANN_ASC_STL_STD_DETAIL_CSTDLIB_DIV_H

#include <asc/std/detail/__config>

#if CANN_ASC_STL_DETAIL_HOSTED()
#include <cstdlib>
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

// If available, use the host's div_t, ldiv_t, and lldiv_t types because the struct members order is
// implementation-defined.
#if CANN_ASC_STL_DETAIL_HOSTED()
using ::div_t;
using ::ldiv_t;
using ::lldiv_t;
#else   // ^^^ CANN_ASC_STL_DETAIL_HOSTED() ^^^ / vvv CANN_ASC_STL_DETAIL_FREESTANDING() vvv
struct div_t {
    int quot;
    int rem;
};

struct ldiv_t {
    long quot;
    long rem;
};

struct lldiv_t {
    long long quot;
    long long rem;
};
#endif  // CANN_ASC_STL_DETAIL_FREESTANDING()

[[nodiscard]] CANN_ASC_STL_API constexpr div_t div(int __x, int __y) noexcept
{
    div_t __result{};
    __result.quot = __x / __y;
    __result.rem = __x % __y;
    return __result;
}

[[nodiscard]] CANN_ASC_STL_API constexpr ldiv_t ldiv(long __x, long __y) noexcept
{
    ldiv_t __result{};
    __result.quot = __x / __y;
    __result.rem = __x % __y;
    return __result;
}

[[nodiscard]] CANN_ASC_STL_API constexpr ldiv_t div(long __x, long __y) noexcept
{
    return ::asc::std::ldiv(__x, __y);
}

[[nodiscard]] CANN_ASC_STL_API constexpr lldiv_t lldiv(long long __x, long long __y) noexcept
{
    lldiv_t __result{};
    __result.quot = __x / __y;
    __result.rem = __x % __y;
    return __result;
}

[[nodiscard]] CANN_ASC_STL_API constexpr lldiv_t div(long long __x, long long __y) noexcept
{
    return ::asc::std::lldiv(__x, __y);
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_CSTDLIB_DIV_H
