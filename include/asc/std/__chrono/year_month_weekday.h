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

#ifndef CANN_ASC_STL_ASC_STD___CHRONO_YEAR_MONTH_WEEKDAY_H
#define CANN_ASC_STL_ASC_STD___CHRONO_YEAR_MONTH_WEEKDAY_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__chrono/calendar.h>
#include <asc/std/__chrono/day.h>
#include <asc/std/__chrono/duration.h>
#include <asc/std/__chrono/month.h>
#include <asc/std/__chrono/month_weekday.h>
#include <asc/std/__chrono/system_clock.h>
#include <asc/std/__chrono/time_point.h>
#include <asc/std/__chrono/weekday.h>
#include <asc/std/__chrono/year.h>
#include <asc/std/__chrono/year_month.h>
#include <asc/std/__chrono/year_month_day.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace chrono {

//! @brief A calendar date expressed as year, month, and the n-th
//! occurrence of a weekday (the second Tuesday of March 2024, say).
//! Converts to and from day counts by anchoring on the first of the
//! month and shifting by whole weeks.
class year_month_weekday {
    chrono::year __year_;
    chrono::month __month_;
    chrono::weekday_indexed __weekday_indexed_;

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API static constexpr year_month_weekday __from_days(days __days) noexcept
    {
        const sys_days __sysd{__days};
        const chrono::weekday __wd = chrono::weekday{__sysd};
        const year_month_day __ymd = year_month_day{__sysd};
        return year_month_weekday{__ymd.year(), __ymd.month(), __wd[(static_cast<unsigned>(__ymd.day()) - 1) / 7 + 1]};
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr days __to_days() const noexcept
    {
        const sys_days __sysd{__year_ / __month_ / 1};
        return (__sysd +
            (__weekday_indexed_.weekday() - chrono::weekday(__sysd) + days{(__weekday_indexed_.index() - 1) * 7}))
            .time_since_epoch();
    }

public:
    CANN_ASC_STL_API year_month_weekday() = default;

    CANN_ASC_STL_API constexpr year_month_weekday(const chrono::year& __year, const chrono::month& __month,
        const chrono::weekday_indexed& __weekday_indexed) noexcept
        : __year_{__year}, __month_{__month}, __weekday_indexed_{__weekday_indexed}
    {}

    CANN_ASC_STL_API constexpr year_month_weekday(const sys_days& __sysd) noexcept
        : year_month_weekday(__from_days(__sysd.time_since_epoch()))
    {}

    CANN_ASC_STL_API explicit constexpr year_month_weekday(const local_days& __locd) noexcept
        : year_month_weekday(__from_days(__locd.time_since_epoch()))
    {}

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::year year() const noexcept
    {
        return __year_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::month month() const noexcept
    {
        return __month_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::weekday weekday() const noexcept
    {
        return __weekday_indexed_.weekday();
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr unsigned index() const noexcept
    {
        return __weekday_indexed_.index();
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::weekday_indexed weekday_indexed() const noexcept
    {
        return __weekday_indexed_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr operator sys_days() const noexcept
    {
        return sys_days{__to_days()};
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API explicit constexpr operator local_days() const noexcept
    {
        return local_days{__to_days()};
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        if (!__year_.ok() || !__month_.ok() || !__weekday_indexed_.ok()) {
            return false;
        }
        if (__weekday_indexed_.index() <= 4) {
            return true;
        }
        const auto __nth_weekday_day = __weekday_indexed_.weekday() -
            chrono::weekday{static_cast<sys_days>(__year_ / __month_ / 1)} +
            days{(__weekday_indexed_.index() - 1) * 7} + days{1};
        return static_cast<unsigned>(__nth_weekday_day.count()) <=
            static_cast<unsigned>((__year_ / __month_ / last).day());
    }

    CANN_ASC_STL_API constexpr year_month_weekday& operator+=(const months& __dm) noexcept;
    CANN_ASC_STL_API constexpr year_month_weekday& operator-=(const months& __dm) noexcept;
    CANN_ASC_STL_API constexpr year_month_weekday& operator+=(const years& __dy) noexcept;
    CANN_ASC_STL_API constexpr year_month_weekday& operator-=(const years& __dy) noexcept;

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator==(
        const year_month_weekday& __lhs, const year_month_weekday& __rhs) noexcept
    {
        return __lhs.year() == __rhs.year() && __lhs.month() == __rhs.month() &&
            __lhs.weekday_indexed() == __rhs.weekday_indexed();
    }

#if !CANN_ASC_STL_DETAIL_HAS_CXX20()
    CANN_ASC_STL_NODISCARD
    CANN_ASC_STL_API friend constexpr bool operator!=(
        const year_month_weekday& __lhs, const year_month_weekday& __rhs) noexcept
    {
        return __lhs.year() != __rhs.year() || __lhs.month() != __rhs.month() ||
            __lhs.weekday_indexed() != __rhs.weekday_indexed();
    }
#endif  // !CANN_ASC_STL_DETAIL_HAS_CXX20()
};

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_weekday operator/(
    const year_month& __lhs, const weekday_indexed& __rhs) noexcept
{
    return year_month_weekday{__lhs.year(), __lhs.month(), __rhs};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_weekday operator/(
    const year& __lhs, const month_weekday& __rhs) noexcept
{
    return year_month_weekday{__lhs, __rhs.month(), __rhs.weekday_indexed()};
}

CANN_ASC_STL_API constexpr year_month_weekday operator/(int __lhs, const month_weekday& __rhs) noexcept
{
    return ::asc::std::chrono::operator/(year(__lhs), __rhs);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_weekday operator/(
    const month_weekday& __lhs, const year& __rhs) noexcept
{
    return ::asc::std::chrono::operator/(__rhs, __lhs);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_weekday operator/(
    const month_weekday& __lhs, int __rhs) noexcept
{
    return ::asc::std::chrono::operator/(year(__rhs), __lhs);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_weekday operator+(
    const year_month_weekday& __lhs, const months& __rhs) noexcept
{
    return (__lhs.year() / __lhs.month() + __rhs) / __lhs.weekday_indexed();
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_weekday operator+(
    const months& __lhs, const year_month_weekday& __rhs) noexcept
{
    return __rhs + __lhs;
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_weekday operator-(
    const year_month_weekday& __lhs, const months& __rhs) noexcept
{
    return __lhs + (-__rhs);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_weekday operator+(
    const year_month_weekday& __lhs, const years& __rhs) noexcept
{
    return year_month_weekday{__lhs.year() + __rhs, __lhs.month(), __lhs.weekday_indexed()};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_weekday operator+(
    const years& __lhs, const year_month_weekday& __rhs) noexcept
{
    return __rhs + __lhs;
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_weekday operator-(
    const year_month_weekday& __lhs, const years& __rhs) noexcept
{
    return __lhs + (-__rhs);
}

CANN_ASC_STL_API constexpr year_month_weekday& year_month_weekday::operator+=(const months& __dm) noexcept
{
    *this = *this + __dm;
    return *this;
}

CANN_ASC_STL_API constexpr year_month_weekday& year_month_weekday::operator-=(const months& __dm) noexcept
{
    *this = *this - __dm;
    return *this;
}

CANN_ASC_STL_API constexpr year_month_weekday& year_month_weekday::operator+=(const years& __dy) noexcept
{
    *this = *this + __dy;
    return *this;
}

CANN_ASC_STL_API constexpr year_month_weekday& year_month_weekday::operator-=(const years& __dy) noexcept
{
    *this = *this - __dy;
    return *this;
}

//! @brief A calendar date expressed as year, month, and the last
//! occurrence of a weekday (the last Friday of October, say). Converts
//! to a day count by starting at the month's last day and stepping back
//! the weekday distance.
class year_month_weekday_last {
    chrono::year __year_;
    chrono::month __month_;
    chrono::weekday_last __weekday_last_;

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr days __to_days() const noexcept
    {
        const sys_days __last{__year_ / __month_ / chrono::last};
        return (__last - (chrono::weekday{__last} - __weekday_last_.weekday())).time_since_epoch();
    }

public:
    CANN_ASC_STL_API constexpr year_month_weekday_last(
        const chrono::year& __year, const chrono::month& __month, const chrono::weekday_last& __weekday_last) noexcept
        : __year_{__year}, __month_{__month}, __weekday_last_{__weekday_last}
    {}

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::year year() const noexcept
    {
        return __year_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::month month() const noexcept
    {
        return __month_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::weekday weekday() const noexcept
    {
        return __weekday_last_.weekday();
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::weekday_last weekday_last() const noexcept
    {
        return __weekday_last_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr operator sys_days() const noexcept
    {
        return sys_days{__to_days()};
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API explicit constexpr operator local_days() const noexcept
    {
        return local_days{__to_days()};
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        return __year_.ok() && __month_.ok() && __weekday_last_.ok();
    }

    CANN_ASC_STL_API constexpr year_month_weekday_last& operator+=(const months& __dm) noexcept;
    CANN_ASC_STL_API constexpr year_month_weekday_last& operator-=(const months& __dm) noexcept;
    CANN_ASC_STL_API constexpr year_month_weekday_last& operator+=(const years& __dy) noexcept;
    CANN_ASC_STL_API constexpr year_month_weekday_last& operator-=(const years& __dy) noexcept;

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator==(
        const year_month_weekday_last& __lhs, const year_month_weekday_last& __rhs) noexcept
    {
        return __lhs.year() == __rhs.year() && __lhs.month() == __rhs.month() &&
            __lhs.weekday_last() == __rhs.weekday_last();
    }

#if !CANN_ASC_STL_DETAIL_HAS_CXX20()
    CANN_ASC_STL_NODISCARD
    CANN_ASC_STL_API friend constexpr bool operator!=(
        const year_month_weekday_last& __lhs, const year_month_weekday_last& __rhs) noexcept
    {
        return __lhs.year() != __rhs.year() || __lhs.month() != __rhs.month() ||
            __lhs.weekday_last() != __rhs.weekday_last();
    }
#endif  // !CANN_ASC_STL_DETAIL_HAS_CXX20()
};

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_weekday_last operator/(
    const year_month& __lhs, const weekday_last& __rhs) noexcept
{
    return year_month_weekday_last{__lhs.year(), __lhs.month(), __rhs};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_weekday_last operator/(
    const year& __lhs, const month_weekday_last& __rhs) noexcept
{
    return year_month_weekday_last{__lhs, __rhs.month(), __rhs.weekday_last()};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_weekday_last operator/(
    int __lhs, const month_weekday_last& __rhs) noexcept
{
    return ::asc::std::chrono::operator/(year(__lhs), __rhs);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_weekday_last operator/(
    const month_weekday_last& __lhs, const year& __rhs) noexcept
{
    return ::asc::std::chrono::operator/(__rhs, __lhs);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_weekday_last operator/(
    const month_weekday_last& __lhs, int __rhs) noexcept
{
    return ::asc::std::chrono::operator/(year(__rhs), __lhs);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_weekday_last operator+(
    const year_month_weekday_last& __lhs, const months& __rhs) noexcept
{
    return (__lhs.year() / __lhs.month() + __rhs) / __lhs.weekday_last();
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_weekday_last operator+(
    const months& __lhs, const year_month_weekday_last& __rhs) noexcept
{
    return __rhs + __lhs;
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_weekday_last operator-(
    const year_month_weekday_last& __lhs, const months& __rhs) noexcept
{
    return __lhs + (-__rhs);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_weekday_last operator+(
    const year_month_weekday_last& __lhs, const years& __rhs) noexcept
{
    return year_month_weekday_last{__lhs.year() + __rhs, __lhs.month(), __lhs.weekday_last()};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_weekday_last operator+(
    const years& __lhs, const year_month_weekday_last& __rhs) noexcept
{
    return __rhs + __lhs;
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_weekday_last operator-(
    const year_month_weekday_last& __lhs, const years& __rhs) noexcept
{
    return __lhs + (-__rhs);
}

CANN_ASC_STL_API constexpr year_month_weekday_last& year_month_weekday_last::operator+=(const months& __dm) noexcept
{
    *this = *this + __dm;
    return *this;
}

CANN_ASC_STL_API constexpr year_month_weekday_last& year_month_weekday_last::operator-=(const months& __dm) noexcept
{
    *this = *this - __dm;
    return *this;
}

CANN_ASC_STL_API constexpr year_month_weekday_last& year_month_weekday_last::operator+=(const years& __dy) noexcept
{
    *this = *this + __dy;
    return *this;
}

CANN_ASC_STL_API constexpr year_month_weekday_last& year_month_weekday_last::operator-=(const years& __dy) noexcept
{
    *this = *this - __dy;
    return *this;
}

}  // namespace chrono

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHRONO_YEAR_MONTH_WEEKDAY_H
