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

#ifndef CANN_ASC_STL_ASC_STD___CSTDLIB_DIV_H
#define CANN_ASC_STL_ASC_STD___CSTDLIB_DIV_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/__detail/execution_space.h>

// Inline definition of the CANN_ASC_STL_DETAIL_HOSTED() gate (not provided
// centrally): AI-core kernel compilation has no host standard library and
// counts as freestanding, as does an explicit opt-out.
#if !defined(CANN_ASC_STL_DETAIL_HOSTED)
#if defined(CANN_ASC_STL_DETAIL_ENABLE_FREESTANDING) || defined(__CCE__)
#define CANN_ASC_STL_DETAIL_HOSTED() 0
#else
#define CANN_ASC_STL_DETAIL_HOSTED() 1
#endif
#endif  // CANN_ASC_STL_DETAIL_HOSTED

// If available, use the host's div_t, ldiv_t, and lldiv_t types because the struct members order is
// implementation-defined.
#if CANN_ASC_STL_DETAIL_HOSTED()
#include <cstdlib>

CANN_ASC_STL_BEGIN_NAMESPACE

using ::div_t;
using ::ldiv_t;
using ::lldiv_t;
#else   // ^^^ CANN_ASC_STL_DETAIL_HOSTED() ^^^ / vvv CANN_ASC_STL_DETAIL_FREESTANDING() vvv

CANN_ASC_STL_BEGIN_NAMESPACE

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

CANN_ASC_STL_API constexpr div_t div(int numerator, int denominator) noexcept
{
    div_t result{};
    const int __safe_denominator = (denominator == 0) ? 1 : denominator;
    result.quot = numerator / __safe_denominator;
    result.rem = numerator % __safe_denominator;
    return result;
}

CANN_ASC_STL_API constexpr ldiv_t ldiv(long numerator, long denominator) noexcept
{
    ldiv_t result{};
    const long __safe_denominator = (denominator == 0) ? 1 : denominator;
    result.quot = numerator / __safe_denominator;
    result.rem = numerator % __safe_denominator;
    return result;
}

CANN_ASC_STL_API constexpr ldiv_t div(long numerator, long denominator) noexcept
{
    return ::asc::std::ldiv(numerator, denominator);
}

CANN_ASC_STL_API constexpr lldiv_t lldiv(long long numerator, long long denominator) noexcept
{
    lldiv_t result{};
    const long long __safe_denominator = (denominator == 0) ? 1 : denominator;
    result.quot = numerator / __safe_denominator;
    result.rem = numerator % __safe_denominator;
    return result;
}

CANN_ASC_STL_API constexpr lldiv_t div(long long numerator, long long denominator) noexcept
{
    return ::asc::std::lldiv(numerator, denominator);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CSTDLIB_DIV_H
