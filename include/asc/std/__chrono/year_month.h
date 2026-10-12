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

#ifndef CANN_ASC_STL_ASC_STD___CHRONO_YEAR_MONTH_H
#define CANN_ASC_STL_ASC_STD___CHRONO_YEAR_MONTH_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__chrono/duration.h>
#include <asc/std/__chrono/month.h>
#include <asc/std/__chrono/year.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace chrono {

class year_month {
    chrono::year __year_;
    chrono::month __month_;

public:
    CANN_ASC_STL_API year_month() = default;
    CANN_ASC_STL_API constexpr year_month(const chrono::year& __year, const chrono::month& __month) noexcept
        : __year_{__year}, __month_{__month}
    {}

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::year year() const noexcept
    {
        return __year_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::month month() const noexcept
    {
        return __month_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        return __year_.ok() && __month_.ok();
    }

    // arithmetics
    CANN_ASC_STL_API constexpr year_month& operator+=(const months& __months) noexcept
    {
        int __dmi = static_cast<int>(static_cast<unsigned>(__month_)) - 1 + __months.count();
        const int __years = (__dmi >= 0 ? __dmi : __dmi - 11) / 12;
        __dmi = __dmi - __years * 12 + 1;
        __year_ += years(__years);
        __month_ = chrono::month(static_cast<unsigned>(__dmi));
        return *this;
    }

    CANN_ASC_STL_API constexpr year_month& operator-=(const months& __months) noexcept
    {
        *this += -__months;
        return *this;
    }

    CANN_ASC_STL_API constexpr year_month& operator+=(const years& __years) noexcept
    {
        __year_ += __years;
        return *this;
    }

    CANN_ASC_STL_API constexpr year_month& operator-=(const years& __years) noexcept
    {
        __year_ -= __years;
        return *this;
    }

    // comparisons
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator==(
        const year_month& __lhs, const year_month& __rhs) noexcept
    {
        return __lhs.year() == __rhs.year() && __lhs.month() == __rhs.month();
    }

#if !CANN_ASC_STL_DETAIL_HAS_CXX20()
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator!=(
        const year_month& __lhs, const year_month& __rhs) noexcept
    {
        return __lhs.year() != __rhs.year() || __lhs.month() != __rhs.month();
    }
#endif  // !CANN_ASC_STL_DETAIL_HAS_CXX20()

    // Traditional relational operators (spaceship not supported)

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator<(
        const year_month& __lhs, const year_month& __rhs) noexcept
    {
        return __lhs.year() != __rhs.year() ? __lhs.year() < __rhs.year() : __lhs.month() < __rhs.month();
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator>(
        const year_month& __lhs, const year_month& __rhs) noexcept
    {
        return __rhs < __lhs;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator<=(
        const year_month& __lhs, const year_month& __rhs) noexcept
    {
        return !(__rhs < __lhs);
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator>=(
        const year_month& __lhs, const year_month& __rhs) noexcept
    {
        return !(__lhs < __rhs);
    }
};

// Cannot be hidden friends, the compiler fails to find the right operator/
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month operator/(
    const chrono::year& __year, const chrono::month& __month) noexcept
{
    return year_month{__year, __month};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month operator/(const chrono::year& __year, int __month) noexcept
{
    return year_month{__year, chrono::month(__month)};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month operator+(
    const year_month& __lhs, const months& __rhs) noexcept
{
    int __dmi = static_cast<int>(static_cast<unsigned>(__lhs.month())) - 1 + __rhs.count();
    const int __years = (__dmi >= 0 ? __dmi : __dmi - 11) / 12;
    __dmi = __dmi - __years * 12 + 1;
    return (__lhs.year() + years(__years)) / chrono::month(static_cast<unsigned>(__dmi));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month operator+(
    const months& __lhs, const year_month& __rhs) noexcept
{
    return __rhs + __lhs;
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month operator+(
    const year_month& __lhs, const years& __rhs) noexcept
{
    return (__lhs.year() + __rhs) / __lhs.month();
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month operator+(
    const years& __lhs, const year_month& __rhs) noexcept
{
    return __rhs + __lhs;
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr months operator-(
    const year_month& __lhs, const year_month& __rhs) noexcept
{
    return (__lhs.year() - __rhs.year()) +
        chrono::months(static_cast<unsigned>(__lhs.month()) - static_cast<unsigned>(__rhs.month()));
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month operator-(
    const year_month& __lhs, const months& __rhs) noexcept
{
    return __lhs + -__rhs;
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month operator-(
    const year_month& __lhs, const years& __rhs) noexcept
{
    return __lhs + -__rhs;
}

}  // namespace chrono

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHRONO_YEAR_MONTH_H
