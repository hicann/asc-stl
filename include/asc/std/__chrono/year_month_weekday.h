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

class year_month_weekday_last;

class year_month_weekday {
public:
    CANN_ASC_STL_API constexpr year_month_weekday() = default;
    CANN_ASC_STL_API constexpr year_month_weekday(const year_month_weekday&) = default;
    CANN_ASC_STL_API constexpr year_month_weekday(year_month_weekday&&) noexcept = default;
    CANN_ASC_STL_API constexpr year_month_weekday& operator=(const year_month_weekday&) = default;
    CANN_ASC_STL_API constexpr year_month_weekday& operator=(year_month_weekday&&) noexcept = default;
    CANN_ASC_STL_API constexpr year_month_weekday(const chrono::year& year_value, const chrono::month& month_value,
        const chrono::weekday_indexed& weekday_indexed_value) noexcept
        : year_(year_value), month_(month_value), weekday_indexed_(weekday_indexed_value)
    {}
    CANN_ASC_STL_API constexpr year_month_weekday(const sys_days& value) noexcept
        : year_month_weekday(__from_days(value.time_since_epoch()))
    {}
    CANN_ASC_STL_API explicit constexpr year_month_weekday(const local_days& value) noexcept
        : year_month_weekday(__from_days(value.time_since_epoch()))
    {}
    CANN_ASC_STL_API ~year_month_weekday() noexcept = default;

    CANN_ASC_STL_API constexpr chrono::year year() const noexcept
    {
        return year_;
    }
    CANN_ASC_STL_API constexpr chrono::month month() const noexcept
    {
        return month_;
    }
    CANN_ASC_STL_API constexpr chrono::weekday weekday() const noexcept
    {
        return weekday_indexed_.weekday();
    }
    CANN_ASC_STL_API constexpr unsigned index() const noexcept
    {
        return weekday_indexed_.index();
    }
    CANN_ASC_STL_API constexpr chrono::weekday_indexed weekday_indexed() const noexcept
    {
        return weekday_indexed_;
    }
    CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        if (!year_.ok() || !month_.ok() || !weekday_indexed_.ok()) {
            return false;
        }
        if (weekday_indexed_.index() <= 4) {
            return true;
        }
        const sys_days first_of_month(year_ / month_ / chrono::day(1u));
        const days nth_weekday_offset =
            weekday_indexed_.weekday() - chrono::weekday(first_of_month) + days((weekday_indexed_.index() - 1) * 7);
        const year_month_day_last last_day(year_, month_ / chrono::last);
        return static_cast<unsigned>(nth_weekday_offset.count() + 1) <= static_cast<unsigned>(last_day.day());
    }

    CANN_ASC_STL_API constexpr year_month_weekday& operator+=(const months& offset) noexcept
    {
        const year_month shifted = year_month(year_, month_) + offset;
        year_ = shifted.year();
        month_ = shifted.month();
        return *this;
    }
    CANN_ASC_STL_API constexpr year_month_weekday& operator-=(const months& offset) noexcept
    {
        return *this += -offset;
    }
    CANN_ASC_STL_API constexpr year_month_weekday& operator+=(const years& offset) noexcept
    {
        year_ += offset;
        return *this;
    }
    CANN_ASC_STL_API constexpr year_month_weekday& operator-=(const years& offset) noexcept
    {
        return *this += -offset;
    }

private:
    CANN_ASC_STL_API static constexpr year_month_weekday __from_days(days value) noexcept
    {
        const sys_days sysd(value);
        const chrono::weekday weekday_value(sysd);
        const year_month_day ymd(sysd);
        return year_month_weekday(
            ymd.year(), ymd.month(), weekday_value[(static_cast<unsigned>(ymd.day()) - 1u) / 7u + 1u]);
    }

    chrono::year year_;
    chrono::month month_;
    chrono::weekday_indexed weekday_indexed_;
};

class year_month_weekday_last {
public:
    CANN_ASC_STL_API constexpr year_month_weekday_last(const chrono::year& year_value, const chrono::month& month_value,
        const chrono::weekday_last& weekday_last_value) noexcept
        : year_(year_value), month_(month_value), weekday_last_(weekday_last_value)
    {}
    CANN_ASC_STL_API constexpr year_month_weekday_last(const year_month_weekday_last&) = default;
    CANN_ASC_STL_API constexpr year_month_weekday_last(year_month_weekday_last&&) noexcept = default;
    CANN_ASC_STL_API constexpr year_month_weekday_last& operator=(const year_month_weekday_last&) = default;
    CANN_ASC_STL_API constexpr year_month_weekday_last& operator=(year_month_weekday_last&&) noexcept = default;
    CANN_ASC_STL_API ~year_month_weekday_last() noexcept = default;

    CANN_ASC_STL_API constexpr chrono::year year() const noexcept
    {
        return year_;
    }
    CANN_ASC_STL_API constexpr chrono::month month() const noexcept
    {
        return month_;
    }
    CANN_ASC_STL_API constexpr chrono::weekday weekday() const noexcept
    {
        return weekday_last_.weekday();
    }
    CANN_ASC_STL_API constexpr chrono::weekday_last weekday_last() const noexcept
    {
        return weekday_last_;
    }
    CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        return year_.ok() && month_.ok() && weekday_last_.ok();
    }

    CANN_ASC_STL_API constexpr year_month_weekday_last& operator+=(const months& offset) noexcept
    {
        const year_month shifted = year_month(year_, month_) + offset;
        year_ = shifted.year();
        month_ = shifted.month();
        return *this;
    }
    CANN_ASC_STL_API constexpr year_month_weekday_last& operator-=(const months& offset) noexcept
    {
        return *this += -offset;
    }
    CANN_ASC_STL_API constexpr year_month_weekday_last& operator+=(const years& offset) noexcept
    {
        year_ += offset;
        return *this;
    }
    CANN_ASC_STL_API constexpr year_month_weekday_last& operator-=(const years& offset) noexcept
    {
        return *this += -offset;
    }

private:
    chrono::year year_;
    chrono::month month_;
    chrono::weekday_last weekday_last_;
};

}  // namespace chrono

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHRONO_YEAR_MONTH_WEEKDAY_H
