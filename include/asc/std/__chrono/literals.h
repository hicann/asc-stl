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

#ifndef CANN_ASC_STL_ASC_STD___CHRONO_LITERALS_H
#define CANN_ASC_STL_ASC_STD___CHRONO_LITERALS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/__detail/diagnostics.h>
#include <asc/std/__chrono/day.h>
#include <asc/std/__chrono/year.h>

CANN_ASC_STL_BEGIN_NAMESPACE

inline namespace literals {
inline namespace chrono_literals {
CANN_ASC_STL_DETAIL_DIAGNOSTIC_PUSH()
#if defined(__clang__)
CANN_ASC_STL_DETAIL_DIAGNOSTIC_IGNORE("-Wuser-defined-literals")
CANN_ASC_STL_DETAIL_DIAGNOSTIC_IGNORE("-Wreserved-user-defined-literal")
#else
CANN_ASC_STL_DETAIL_DIAGNOSTIC_IGNORE("-Wliteral-suffix")
#endif
CANN_ASC_STL_API constexpr chrono::day operator"" d(unsigned long long value) noexcept
{
    return chrono::day(static_cast<unsigned>(value));
}
CANN_ASC_STL_API constexpr chrono::year operator"" y(unsigned long long value) noexcept
{
    return chrono::year(static_cast<int>(value));
}
CANN_ASC_STL_DETAIL_DIAGNOSTIC_POP()
}  // namespace chrono_literals
}  // namespace literals

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHRONO_LITERALS_H
