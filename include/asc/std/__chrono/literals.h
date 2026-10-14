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
#include <asc/std/__chrono/duration.h>
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
// duration literals [time.duration.literals]
CANN_ASC_STL_API constexpr chrono::hours operator"" h(unsigned long long value) noexcept
{
    return chrono::hours(static_cast<chrono::hours::rep>(value));
}

CANN_ASC_STL_API constexpr chrono::duration<double, ratio<3600, 1>> operator"" h(long double value) noexcept
{
    return chrono::duration<double, ratio<3600, 1>>(value);
}

CANN_ASC_STL_API constexpr chrono::minutes operator"" min(  // NOLINT(build/include_what_you_use)
    unsigned long long value) noexcept
{
    return chrono::minutes(static_cast<chrono::minutes::rep>(value));
}

CANN_ASC_STL_API constexpr chrono::duration<double, ratio<60, 1>> operator"" min(  // NOLINT(build/include_what_you_use)
    long double value) noexcept
{
    return chrono::duration<double, ratio<60, 1>>(value);
}

CANN_ASC_STL_API constexpr chrono::seconds operator"" s(unsigned long long value) noexcept
{
    return chrono::seconds(static_cast<chrono::seconds::rep>(value));
}

CANN_ASC_STL_API constexpr chrono::duration<double> operator"" s(long double value) noexcept
{
    return chrono::duration<double>(value);
}

CANN_ASC_STL_API constexpr chrono::milliseconds operator"" ms(unsigned long long value) noexcept
{
    return chrono::milliseconds(static_cast<chrono::milliseconds::rep>(value));
}

CANN_ASC_STL_API constexpr chrono::duration<double, milli> operator"" ms(long double value) noexcept
{
    return chrono::duration<double, milli>(value);
}

CANN_ASC_STL_API constexpr chrono::microseconds operator"" us(unsigned long long value) noexcept
{
    return chrono::microseconds(static_cast<chrono::microseconds::rep>(value));
}

CANN_ASC_STL_API constexpr chrono::duration<double, micro> operator"" us(long double value) noexcept
{
    return chrono::duration<double, micro>(value);
}

CANN_ASC_STL_API constexpr chrono::nanoseconds operator"" ns(unsigned long long value) noexcept
{
    return chrono::nanoseconds(static_cast<chrono::nanoseconds::rep>(value));
}

CANN_ASC_STL_API constexpr chrono::duration<double, nano> operator"" ns(long double value) noexcept
{
    return chrono::duration<double, nano>(value);
}

// calendar literals [time.calendar.literals]
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

namespace chrono {
// Hoist the literals into namespace chrono, matching the visibility shape of standard std::chrono
using literals::chrono_literals::operator"" h;
using literals::chrono_literals::operator"" min;
using literals::chrono_literals::operator"" s;
using literals::chrono_literals::operator"" ms;
using literals::chrono_literals::operator"" us;
using literals::chrono_literals::operator"" ns;
using literals::chrono_literals::operator"" d;
using literals::chrono_literals::operator"" y;
}  // namespace chrono

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHRONO_LITERALS_H
