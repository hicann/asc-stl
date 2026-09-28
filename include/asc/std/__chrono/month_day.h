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

#ifndef CANN_ASC_STL_ASC_STD___CHRONO_MONTH_DAY_H
#define CANN_ASC_STL_ASC_STD___CHRONO_MONTH_DAY_H

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
#include <asc/std/__chrono/month.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace chrono {

class month_day {
public:
    CANN_ASC_STL_API constexpr month_day() = default;
    CANN_ASC_STL_API constexpr month_day(const chrono::month& month_value, const chrono::day& day_value) noexcept
        : month_(month_value), day_(day_value)
    {}
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
        if (!month_.ok() || !day_.ok())
            return false;
        constexpr unsigned lengths[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        return static_cast<unsigned>(day_) <= lengths[static_cast<unsigned>(month_) - 1];
    }

private:
    chrono::month month_{};
    chrono::day day_{};
};

class month_day_last {
public:
    CANN_ASC_STL_API explicit constexpr month_day_last(const chrono::month& month_value) noexcept : month_(month_value)
    {}
    CANN_ASC_STL_API constexpr chrono::month month() const noexcept
    {
        return month_;
    }
    CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        return month_.ok();
    }

private:
    chrono::month month_;
};

CANN_ASC_STL_API constexpr bool operator==(month_day left, month_day right) noexcept
{
    return left.month() == right.month() && left.day() == right.day();
}
CANN_ASC_STL_API constexpr bool operator!=(month_day left, month_day right) noexcept
{
    return !(left == right);
}
CANN_ASC_STL_API constexpr bool operator<(month_day left, month_day right) noexcept
{
    return left.month() < right.month() || (!(right.month() < left.month()) && left.day() < right.day());
}
CANN_ASC_STL_API constexpr bool operator>(month_day left, month_day right) noexcept
{
    return right < left;
}
CANN_ASC_STL_API constexpr bool operator<=(month_day left, month_day right) noexcept
{
    return !(right < left);
}
CANN_ASC_STL_API constexpr bool operator>=(month_day left, month_day right) noexcept
{
    return !(left < right);
}
CANN_ASC_STL_API constexpr bool operator==(month_day_last left, month_day_last right) noexcept
{
    return left.month() == right.month();
}
CANN_ASC_STL_API constexpr bool operator!=(month_day_last left, month_day_last right) noexcept
{
    return !(left == right);
}
CANN_ASC_STL_API constexpr month_day operator/(const chrono::month& month_value, const chrono::day& day_value) noexcept
{
    return month_day(month_value, day_value);
}
CANN_ASC_STL_API constexpr month_day operator/(const chrono::day& day_value, const chrono::month& month_value) noexcept
{
    return month_value / day_value;
}
CANN_ASC_STL_API constexpr month_day operator/(const chrono::month& month_value, int day_value) noexcept
{
    return month_value / chrono::day(static_cast<unsigned>(day_value));
}
CANN_ASC_STL_API constexpr month_day operator/(int month_value, const chrono::day& day_value) noexcept
{
    return chrono::month(static_cast<unsigned>(month_value)) / day_value;
}
CANN_ASC_STL_API constexpr month_day_last operator/(const chrono::month& month_value, last_spec) noexcept
{
    return month_day_last(month_value);
}
CANN_ASC_STL_API constexpr month_day_last operator/(last_spec, const chrono::month& month_value) noexcept
{
    return month_value / last;
}
CANN_ASC_STL_API constexpr month_day_last operator/(int month_value, last_spec) noexcept
{
    return chrono::month(static_cast<unsigned>(month_value)) / last;
}
CANN_ASC_STL_API constexpr month_day_last operator/(last_spec, int month_value) noexcept
{
    return chrono::month(static_cast<unsigned>(month_value)) / last;
}

}  // namespace chrono

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHRONO_MONTH_DAY_H
