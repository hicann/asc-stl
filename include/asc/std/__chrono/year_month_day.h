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
#include <asc/std/__chrono/month_day.h>
#include <asc/std/__chrono/system_clock.h>
#include <asc/std/__chrono/year_month.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace chrono {

struct __civil_date {
    int year;
    unsigned month;
    unsigned day;
};

CANN_ASC_STL_API constexpr long long __days_from_civil(
    int year_value, unsigned month_value, unsigned day_value) noexcept
{
    year_value -= month_value <= 2;
    const int era = (year_value >= 0 ? year_value : year_value - 399) / 400;
    const unsigned year_of_era = static_cast<unsigned>(year_value - era * 400);
    const unsigned adjusted_month = month_value > 2 ? month_value - 3 : month_value + 9;
    const unsigned day_of_year = (153 * adjusted_month + 2) / 5 + day_value - 1;
    const unsigned day_of_era = year_of_era * 365 + year_of_era / 4 - year_of_era / 100 + day_of_year;
    return static_cast<long long>(era) * 146097 + day_of_era - 719468;
}

CANN_ASC_STL_API constexpr __civil_date __civil_from_days(long long count) noexcept
{
    count += 719468;
    const long long era = (count >= 0 ? count : count - 146096) / 146097;
    const unsigned day_of_era = static_cast<unsigned>(count - era * 146097);
    const unsigned year_of_era = (day_of_era - day_of_era / 1460 + day_of_era / 36524 - day_of_era / 146096) / 365;
    int year_value = static_cast<int>(year_of_era) + static_cast<int>(era * 400);
    const unsigned day_of_year = day_of_era - (365 * year_of_era + year_of_era / 4 - year_of_era / 100);
    const unsigned month_prime = (5 * day_of_year + 2) / 153;
    const unsigned day_value = day_of_year - (153 * month_prime + 2) / 5 + 1;
    const unsigned month_value = month_prime < 10 ? month_prime + 3 : month_prime - 9;
    year_value += month_value <= 2;
    return {year_value, month_value, day_value};
}

class year_month_day_last;

class year_month_day {
public:
    CANN_ASC_STL_API constexpr year_month_day() = default;
    CANN_ASC_STL_API constexpr year_month_day(
        const chrono::year& year_value, const chrono::month& month_value, const chrono::day& day_value) noexcept
        : year_(year_value), month_(month_value), day_(day_value)
    {}
    CANN_ASC_STL_API constexpr year_month_day(const year_month_day_last& value) noexcept;
    CANN_ASC_STL_API constexpr year_month_day(const sys_days& value) noexcept
    {
        const __civil_date date = __civil_from_days(value.time_since_epoch().count());
        year_ = chrono::year(date.year);
        month_ = chrono::month(date.month);
        day_ = chrono::day(date.day);
    }
    CANN_ASC_STL_API explicit constexpr year_month_day(const local_days& value) noexcept
        : year_month_day(sys_days(value.time_since_epoch()))
    {}
    CANN_ASC_STL_API constexpr chrono::year year() const noexcept
    {
        return year_;
    }
    CANN_ASC_STL_API constexpr chrono::month month() const noexcept
    {
        return month_;
    }
    CANN_ASC_STL_API constexpr chrono::day day() const noexcept
    {
        return day_;
    }
    CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        if (!year_.ok() || !chrono::month_day(month_, day_).ok())
            return false;
        return month_ != February || day_ != chrono::day(29) || year_.is_leap();
    }
    CANN_ASC_STL_API constexpr year_month_day& operator+=(const months& offset) noexcept
    {
        const year_month adjusted = year_ / month_ + offset;
        year_ = adjusted.year();
        month_ = adjusted.month();
        return *this;
    }
    CANN_ASC_STL_API constexpr year_month_day& operator-=(const months& offset) noexcept
    {
        return *this += months(-offset.count());
    }
    CANN_ASC_STL_API constexpr year_month_day& operator+=(const years& offset) noexcept
    {
        year_ += offset;
        return *this;
    }
    CANN_ASC_STL_API constexpr year_month_day& operator-=(const years& offset) noexcept
    {
        return *this += years(-offset.count());
    }
    CANN_ASC_STL_API explicit constexpr operator sys_days() const noexcept
    {
        return sys_days(days(
            __days_from_civil(static_cast<int>(year_), static_cast<unsigned>(month_), static_cast<unsigned>(day_))));
    }
    CANN_ASC_STL_API explicit constexpr operator local_days() const noexcept
    {
        return local_days(days(
            __days_from_civil(static_cast<int>(year_), static_cast<unsigned>(month_), static_cast<unsigned>(day_))));
    }

private:
    chrono::year year_{};
    chrono::month month_{};
    chrono::day day_{};
};

class year_month_day_last {
public:
    CANN_ASC_STL_API constexpr year_month_day_last(
        const chrono::year& year_value, const chrono::month_day_last& month_day_value) noexcept
        : year_(year_value), month_day_(month_day_value)
    {}
    CANN_ASC_STL_API constexpr chrono::year year() const noexcept
    {
        return year_;
    }
    CANN_ASC_STL_API constexpr chrono::month month() const noexcept
    {
        return month_day_.month();
    }
    CANN_ASC_STL_API constexpr chrono::month_day_last month_day_last() const noexcept
    {
        return month_day_;
    }
    CANN_ASC_STL_API constexpr chrono::day day() const noexcept
    {
        constexpr unsigned lengths[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        const unsigned month_value = static_cast<unsigned>(month());
        return chrono::day(lengths[month_value - 1] + (month_value == 2 && year_.is_leap()));
    }
    CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        return year_.ok() && month_day_.ok();
    }
    CANN_ASC_STL_API constexpr year_month_day_last& operator+=(const months& offset) noexcept
    {
        const year_month adjusted = year_ / month() + offset;
        year_ = adjusted.year();
        month_day_ = chrono::month_day_last(adjusted.month());
        return *this;
    }
    CANN_ASC_STL_API constexpr year_month_day_last& operator-=(const months& offset) noexcept
    {
        return *this += months(-offset.count());
    }
    CANN_ASC_STL_API constexpr year_month_day_last& operator+=(const years& offset) noexcept
    {
        year_ += offset;
        return *this;
    }
    CANN_ASC_STL_API constexpr year_month_day_last& operator-=(const years& offset) noexcept
    {
        return *this += years(-offset.count());
    }
    CANN_ASC_STL_API explicit constexpr operator sys_days() const noexcept
    {
        return static_cast<sys_days>(year_month_day(*this));
    }
    CANN_ASC_STL_API explicit constexpr operator local_days() const noexcept
    {
        return local_days(static_cast<sys_days>(*this).time_since_epoch());
    }

private:
    chrono::year year_;
    chrono::month_day_last month_day_;
};

CANN_ASC_STL_API constexpr year_month_day::year_month_day(const year_month_day_last& value) noexcept
    : year_(value.year()), month_(value.month()), day_(value.day())
{}

CANN_ASC_STL_API constexpr bool operator==(year_month_day left, year_month_day right) noexcept
{
    return left.year() == right.year() && left.month() == right.month() && left.day() == right.day();
}
CANN_ASC_STL_API constexpr bool operator!=(year_month_day left, year_month_day right) noexcept
{
    return !(left == right);
}
CANN_ASC_STL_API constexpr bool operator<(year_month_day left, year_month_day right) noexcept
{
    if (left.year() != right.year())
        return left.year() < right.year();
    if (left.month() != right.month())
        return left.month() < right.month();
    return left.day() < right.day();
}
CANN_ASC_STL_API constexpr bool operator>(year_month_day left, year_month_day right) noexcept
{
    return right < left;
}
CANN_ASC_STL_API constexpr bool operator<=(year_month_day left, year_month_day right) noexcept
{
    return !(right < left);
}
CANN_ASC_STL_API constexpr bool operator>=(year_month_day left, year_month_day right) noexcept
{
    return !(left < right);
}
CANN_ASC_STL_API constexpr bool operator==(year_month_day_last left, year_month_day_last right) noexcept
{
    return left.year() == right.year() && left.month_day_last() == right.month_day_last();
}
CANN_ASC_STL_API constexpr bool operator!=(year_month_day_last left, year_month_day_last right) noexcept
{
    return !(left == right);
}
CANN_ASC_STL_API constexpr bool operator<(year_month_day_last left, year_month_day_last right) noexcept
{
    return left.year() < right.year() || (!(right.year() < left.year()) && left.month() < right.month());
}
CANN_ASC_STL_API constexpr bool operator>(year_month_day_last left, year_month_day_last right) noexcept
{
    return right < left;
}
CANN_ASC_STL_API constexpr bool operator<=(year_month_day_last left, year_month_day_last right) noexcept
{
    return !(right < left);
}
CANN_ASC_STL_API constexpr bool operator>=(year_month_day_last left, year_month_day_last right) noexcept
{
    return !(left < right);
}
CANN_ASC_STL_API constexpr year_month_day operator+(year_month_day value, const months& offset) noexcept
{
    return value += offset;
}
CANN_ASC_STL_API constexpr year_month_day operator+(const months& offset, year_month_day value) noexcept
{
    return value += offset;
}
CANN_ASC_STL_API constexpr year_month_day operator-(year_month_day value, const months& offset) noexcept
{
    return value -= offset;
}
CANN_ASC_STL_API constexpr year_month_day operator+(year_month_day value, const years& offset) noexcept
{
    return value += offset;
}
CANN_ASC_STL_API constexpr year_month_day operator+(const years& offset, year_month_day value) noexcept
{
    return value += offset;
}
CANN_ASC_STL_API constexpr year_month_day operator-(year_month_day value, const years& offset) noexcept
{
    return value -= offset;
}
CANN_ASC_STL_API constexpr year_month_day_last operator+(year_month_day_last value, const months& offset) noexcept
{
    return value += offset;
}
CANN_ASC_STL_API constexpr year_month_day_last operator-(year_month_day_last value, const months& offset) noexcept
{
    return value -= offset;
}
CANN_ASC_STL_API constexpr year_month_day_last operator+(year_month_day_last value, const years& offset) noexcept
{
    return value += offset;
}
CANN_ASC_STL_API constexpr year_month_day_last operator-(year_month_day_last value, const years& offset) noexcept
{
    return value -= offset;
}
CANN_ASC_STL_API constexpr year_month_day operator/(const year_month& value, const chrono::day& day_value) noexcept
{
    return year_month_day(value.year(), value.month(), day_value);
}
CANN_ASC_STL_API constexpr year_month_day operator/(const year_month& value, int day_value) noexcept
{
    return value / chrono::day(static_cast<unsigned>(day_value));
}
CANN_ASC_STL_API constexpr year_month_day operator/(const chrono::year& year_value, const month_day& value) noexcept
{
    return year_month_day(year_value, value.month(), value.day());
}
CANN_ASC_STL_API constexpr year_month_day operator/(const month_day& value, const chrono::year& year_value) noexcept
{
    return year_value / value;
}
CANN_ASC_STL_API constexpr year_month_day operator/(int year_value, const month_day& value) noexcept
{
    return chrono::year(year_value) / value;
}
CANN_ASC_STL_API constexpr year_month_day operator/(const month_day& value, int year_value) noexcept
{
    return chrono::year(year_value) / value;
}
CANN_ASC_STL_API constexpr year_month_day_last operator/(
    const chrono::year& year_value, const chrono::month_day_last& value) noexcept
{
    return year_month_day_last(year_value, value);
}
CANN_ASC_STL_API constexpr year_month_day_last operator/(
    const chrono::month_day_last& value, const chrono::year& year_value) noexcept
{
    return year_value / value;
}
CANN_ASC_STL_API constexpr year_month_day_last operator/(int year_value, const chrono::month_day_last& value) noexcept
{
    return chrono::year(year_value) / value;
}
CANN_ASC_STL_API constexpr year_month_day_last operator/(const chrono::month_day_last& value, int year_value) noexcept
{
    return chrono::year(year_value) / value;
}

}  // namespace chrono

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHRONO_YEAR_MONTH_DAY_H
