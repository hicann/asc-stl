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

#ifndef CANN_ASC_STL_ASC_STD___CHRONO_YEAR_MONTH_DAY_H
#define CANN_ASC_STL_ASC_STD___CHRONO_YEAR_MONTH_DAY_H

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
#include <asc/std/__chrono/month_day.h>
#include <asc/std/__chrono/system_clock.h>
#include <asc/std/__chrono/time_point.h>
#include <asc/std/__chrono/year.h>
#include <asc/std/__chrono/year_month.h>
#include <asc/std/limits>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace chrono {

class year_month_day_last;

//! @brief A calendar date: year, month, day. Converts to and from a
//! count of days since the epoch through the civil-calendar era
//! algorithm (400-year cycles, March-based month numbering), valid
//! proleptically over the whole representable range.
class year_month_day {
private:
    chrono::year __year_;
    chrono::month __month_;
    chrono::day __day_;

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr days __to_days() const noexcept
    {
        static_assert(asc::std::numeric_limits<unsigned>::digits >= 18);
        static_assert(asc::std::numeric_limits<int>::digits >= 20);

        auto constexpr __Feb = February;
        const int __yr = static_cast<int>(__year_) - (__month_ <= __Feb);
        const unsigned __mth = static_cast<unsigned>(__month_);
        const unsigned __day = static_cast<unsigned>(__day_);

        const int __era = (__yr >= 0 ? __yr : __yr - 399) / 400;
        const unsigned __yoe = static_cast<unsigned>(__yr - __era * 400);  // [0, 399]
        const unsigned __doy = static_cast<unsigned>(
            (153 * (__mth + static_cast<unsigned>(__mth > 2 ? -3 : 9)) + 2) / 5 + __day - 1);  // [0, 365]
        const unsigned __doe = __yoe * 365 + __yoe / 4 - __yoe / 100 + __doy;                  // [0, 146096]
        return days{__era * 146097 + static_cast<int>(__doe) - 719468};
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API static constexpr year_month_day __from_days(days __d) noexcept
    {
        static_assert(asc::std::numeric_limits<unsigned>::digits >= 18);
        static_assert(asc::std::numeric_limits<int>::digits >= 20);
        const int __z = __d.count() + 719468;
        const int __era = (__z >= 0 ? __z : __z - 146096) / 146097;
        const unsigned __doe = static_cast<unsigned>(__z - __era * 146097);                    // [0, 146096]
        const unsigned __yoe = (__doe - __doe / 1460 + __doe / 36524 - __doe / 146096) / 365;  // [0, 399]
        const int __yr = static_cast<int>(__yoe) + __era * 400;
        const unsigned __doy = __doe - (365 * __yoe + __yoe / 4 - __yoe / 100);   // [0, 365]
        const unsigned __mp = (5 * __doy + 2) / 153;                              // [0, 11]
        const unsigned __day = __doy - (153 * __mp + 2) / 5 + 1;                  // [1, 31]
        const unsigned __mth = __mp + static_cast<unsigned>(__mp < 10 ? 3 : -9);  // [1, 12]
        return year_month_day{chrono::year{__yr + (__mth <= 2)}, chrono::month{__mth}, chrono::day{__day}};
    }

public:
    CANN_ASC_STL_API year_month_day() = default;

    CANN_ASC_STL_API constexpr year_month_day(
        const chrono::year& __year, const chrono::month& __month, const chrono::day& __day) noexcept
        : __year_{__year}, __month_{__month}, __day_{__day}
    {}

    CANN_ASC_STL_API constexpr year_month_day(const year_month_day_last& __ymdl) noexcept;

    CANN_ASC_STL_API constexpr year_month_day(const sys_days& __sysd) noexcept
        : year_month_day(__from_days(__sysd.time_since_epoch()))
    {}

    CANN_ASC_STL_API explicit constexpr year_month_day(const local_days& __locd) noexcept
        : year_month_day(__from_days(__locd.time_since_epoch()))
    {}

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::year year() const noexcept
    {
        return __year_;
    }
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::month month() const noexcept
    {
        return __month_;
    }
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::day day() const noexcept
    {
        return __day_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr operator sys_days() const noexcept
    {
        return sys_days{__to_days()};
    }
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API explicit constexpr operator local_days() const noexcept
    {
        return local_days{__to_days()};
    }

    CANN_ASC_STL_API constexpr bool ok() const noexcept;

    CANN_ASC_STL_API constexpr year_month_day& operator+=(const months& __dm) noexcept;
    CANN_ASC_STL_API constexpr year_month_day& operator-=(const months& __dm) noexcept;
    CANN_ASC_STL_API constexpr year_month_day& operator+=(const years& __dy) noexcept;
    CANN_ASC_STL_API constexpr year_month_day& operator-=(const years& __dy) noexcept;

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator==(
        const year_month_day& __lhs, const year_month_day& __rhs) noexcept
    {
        return __lhs.year() == __rhs.year() && __lhs.month() == __rhs.month() && __lhs.day() == __rhs.day();
    }

#if !CANN_ASC_STL_DETAIL_HAS_CXX20()
    CANN_ASC_STL_NODISCARD
    CANN_ASC_STL_API friend constexpr bool operator!=(const year_month_day& __lhs, const year_month_day& __rhs) noexcept
    {
        return __lhs.year() != __rhs.year() || __lhs.month() != __rhs.month() || __lhs.day() != __rhs.day();
    }
#endif  // !CANN_ASC_STL_DETAIL_HAS_CXX20()

    CANN_ASC_STL_NODISCARD
    CANN_ASC_STL_API friend constexpr bool operator<(const year_month_day& __lhs, const year_month_day& __rhs) noexcept
    {
        if (__lhs.year() < __rhs.year()) {
            return true;
        }
        if (__lhs.year() > __rhs.year()) {
            return false;
        }
        if (__lhs.month() < __rhs.month()) {
            return true;
        }
        if (__lhs.month() > __rhs.month()) {
            return false;
        }
        return __lhs.day() < __rhs.day();
    }

    CANN_ASC_STL_NODISCARD
    CANN_ASC_STL_API friend constexpr bool operator>(const year_month_day& __lhs, const year_month_day& __rhs) noexcept
    {
        return __rhs < __lhs;
    }

    CANN_ASC_STL_NODISCARD
    CANN_ASC_STL_API friend constexpr bool operator<=(const year_month_day& __lhs, const year_month_day& __rhs) noexcept
    {
        return !(__rhs < __lhs);
    }

    CANN_ASC_STL_NODISCARD
    CANN_ASC_STL_API friend constexpr bool operator>=(const year_month_day& __lhs, const year_month_day& __rhs) noexcept
    {
        return !(__lhs < __rhs);
    }
};

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_day operator/(
    const year_month& __lhs, const day& __rhs) noexcept
{
    return year_month_day{__lhs.year(), __lhs.month(), __rhs};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_day operator/(const year_month& __lhs, int __rhs) noexcept
{
    return year_month_day{__lhs.year(), __lhs.month(), chrono::day(__rhs)};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_day operator/(
    const year& __lhs, const month_day& __rhs) noexcept
{
    return __lhs / __rhs.month() / __rhs.day();
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_day operator/(int __lhs, const month_day& __rhs) noexcept
{
    return ::asc::std::chrono::operator/(year(__lhs), __rhs);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_day operator/(
    const month_day& __lhs, const year& __rhs) noexcept
{
    return ::asc::std::chrono::operator/(__rhs, __lhs);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_day operator/(const month_day& __lhs, int __rhs) noexcept
{
    return ::asc::std::chrono::operator/(year(__rhs), __lhs);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_day operator+(
    const year_month_day& __lhs, const months& __rhs) noexcept
{
    return (__lhs.year() / __lhs.month() + __rhs) / __lhs.day();
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_day operator+(
    const months& __lhs, const year_month_day& __rhs) noexcept
{
    return __rhs + __lhs;
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_day operator-(
    const year_month_day& __lhs, const months& __rhs) noexcept
{
    return __lhs + -__rhs;
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_day operator+(
    const year_month_day& __lhs, const years& __rhs) noexcept
{
    return (__lhs.year() + __rhs) / __lhs.month() / __lhs.day();
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_day operator+(
    const years& __lhs, const year_month_day& __rhs) noexcept
{
    return __rhs + __lhs;
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_day operator-(
    const year_month_day& __lhs, const years& __rhs) noexcept
{
    return __lhs + -__rhs;
}

CANN_ASC_STL_API constexpr year_month_day& year_month_day::operator+=(const months& __dm) noexcept
{
    *this = *this + __dm;
    return *this;
}

CANN_ASC_STL_API constexpr year_month_day& year_month_day::operator-=(const months& __dm) noexcept
{
    *this = *this - __dm;
    return *this;
}

CANN_ASC_STL_API constexpr year_month_day& year_month_day::operator+=(const years& __dy) noexcept
{
    *this = *this + __dy;
    return *this;
}

CANN_ASC_STL_API constexpr year_month_day& year_month_day::operator-=(const years& __dy) noexcept
{
    *this = *this - __dy;
    return *this;
}

//! @brief A calendar date pinned to the last day of its month. The day
//! is derived on demand from the month table, with February yielding 29
//! in leap years.
class year_month_day_last {
private:
    chrono::year __year_;
    chrono::month_day_last __month_day_last_;

public:
    CANN_ASC_STL_API constexpr year_month_day_last(
        const chrono::year& __year, const chrono::month_day_last& __month_day_last) noexcept
        : __year_{__year}, __month_day_last_{__month_day_last}
    {}

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::year year() const noexcept
    {
        return __year_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::month month() const noexcept
    {
        return __month_day_last_.month();
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::month_day_last month_day_last() const noexcept
    {
        return __month_day_last_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::day day() const noexcept
    {
        constexpr chrono::day __days_per_month_[] = {chrono::day{31}, chrono::day{28}, chrono::day{31}, chrono::day{30},
            chrono::day{31}, chrono::day{30}, chrono::day{31}, chrono::day{31}, chrono::day{30}, chrono::day{31},
            chrono::day{30}, chrono::day{31}};

        auto constexpr __Feb = February;
        return month() != __Feb || !__year_.is_leap() ? __days_per_month_[static_cast<unsigned>(month()) - 1] :
                                                        chrono::day{29};
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr operator sys_days() const noexcept
    {
        return sys_days{year() / month() / day()};
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API explicit constexpr operator local_days() const noexcept
    {
        return local_days{year() / month() / day()};
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        return __year_.ok() && __month_day_last_.ok();
    }

    CANN_ASC_STL_API constexpr year_month_day_last& operator+=(const months& __month_) noexcept;
    CANN_ASC_STL_API constexpr year_month_day_last& operator-=(const months& __month_) noexcept;
    CANN_ASC_STL_API constexpr year_month_day_last& operator+=(const years& __year_) noexcept;
    CANN_ASC_STL_API constexpr year_month_day_last& operator-=(const years& __year_) noexcept;

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator==(
        const year_month_day_last& __lhs, const year_month_day_last& __rhs) noexcept
    {
        return __lhs.year() == __rhs.year() && __lhs.month_day_last() == __rhs.month_day_last();
    }

#if !CANN_ASC_STL_DETAIL_HAS_CXX20()
    CANN_ASC_STL_NODISCARD
    CANN_ASC_STL_API friend constexpr bool operator!=(
        const year_month_day_last& __lhs, const year_month_day_last& __rhs) noexcept
    {
        return __lhs.year() != __rhs.year() || __lhs.month_day_last() != __rhs.month_day_last();
    }
#endif  // !CANN_ASC_STL_DETAIL_HAS_CXX20()

    CANN_ASC_STL_NODISCARD
    CANN_ASC_STL_API friend constexpr bool operator<(
        const year_month_day_last& __lhs, const year_month_day_last& __rhs) noexcept
    {
        if (__lhs.year() < __rhs.year()) {
            return true;
        }
        if (__lhs.year() > __rhs.year()) {
            return false;
        }
        return __lhs.month_day_last() < __rhs.month_day_last();
    }

    CANN_ASC_STL_NODISCARD
    CANN_ASC_STL_API friend constexpr bool operator>(
        const year_month_day_last& __lhs, const year_month_day_last& __rhs) noexcept
    {
        return __rhs < __lhs;
    }

    CANN_ASC_STL_NODISCARD
    CANN_ASC_STL_API friend constexpr bool operator<=(
        const year_month_day_last& __lhs, const year_month_day_last& __rhs) noexcept
    {
        return !(__rhs < __lhs);
    }

    CANN_ASC_STL_NODISCARD
    CANN_ASC_STL_API friend constexpr bool operator>=(
        const year_month_day_last& __lhs, const year_month_day_last& __rhs) noexcept
    {
        return !(__lhs < __rhs);
    }
};

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_day_last operator/(
    const year_month& __lhs, last_spec) noexcept
{
    return year_month_day_last{__lhs.year(), month_day_last{__lhs.month()}};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_day_last operator/(
    const year& __lhs, const month_day_last& __rhs) noexcept
{
    return year_month_day_last{__lhs, __rhs};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_day_last operator/(
    int __lhs, const month_day_last& __rhs) noexcept
{
    return year_month_day_last{year{__lhs}, __rhs};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_day_last operator/(
    const month_day_last& __lhs, const year& __rhs) noexcept
{
    return ::asc::std::chrono::operator/(__rhs, __lhs);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_day_last operator/(
    const month_day_last& __lhs, int __rhs) noexcept
{
    return ::asc::std::chrono::operator/(year{__rhs}, __lhs);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_day_last operator+(
    const year_month_day_last& __lhs, const months& __rhs) noexcept
{
    return (__lhs.year() / __lhs.month() + __rhs) / last;
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_day_last operator+(
    const months& __lhs, const year_month_day_last& __rhs) noexcept
{
    return __rhs + __lhs;
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_day_last operator-(
    const year_month_day_last& __lhs, const months& __rhs) noexcept
{
    return __lhs + (-__rhs);
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_day_last operator+(
    const year_month_day_last& __lhs, const years& __rhs) noexcept
{
    return year_month_day_last{__lhs.year() + __rhs, __lhs.month_day_last()};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_day_last operator+(
    const years& __lhs, const year_month_day_last& __rhs) noexcept
{
    return __rhs + __lhs;
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year_month_day_last operator-(
    const year_month_day_last& __lhs, const years& __rhs) noexcept
{
    return __lhs + (-__rhs);
}

CANN_ASC_STL_API constexpr year_month_day_last& year_month_day_last::operator+=(const months& __dm) noexcept
{
    *this = *this + __dm;
    return *this;
}

CANN_ASC_STL_API constexpr year_month_day_last& year_month_day_last::operator-=(const months& __dm) noexcept
{
    *this = *this - __dm;
    return *this;
}

CANN_ASC_STL_API constexpr year_month_day_last& year_month_day_last::operator+=(const years& __dy) noexcept
{
    *this = *this + __dy;
    return *this;
}

CANN_ASC_STL_API constexpr year_month_day_last& year_month_day_last::operator-=(const years& __dy) noexcept
{
    *this = *this - __dy;
    return *this;
}

CANN_ASC_STL_API constexpr year_month_day::year_month_day(const year_month_day_last& __ymdl) noexcept
    : year_month_day{__ymdl.year(), __ymdl.month(), __ymdl.day()}
{}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool year_month_day::ok() const noexcept
{
    if (!__year_.ok() || !__month_.ok()) {
        return false;
    }
    return chrono::day{1} <= __day_ && __day_ <= (__year_ / __month_ / last).day();
}

}  // namespace chrono

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHRONO_YEAR_MONTH_DAY_H
