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
private:
    chrono::month __month_;
    chrono::day __day_;

public:
    CANN_ASC_STL_API month_day() = default;
    CANN_ASC_STL_API constexpr month_day(const chrono::month& __month, const chrono::day& __day) noexcept
        : __month_{__month}, __day_{__day}
    {}

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::month month() const noexcept
    {
        return __month_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::day day() const noexcept
    {
        return __day_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        if (!__month_.ok()) {
            return false;
        }
        const unsigned __day = static_cast<unsigned>(__day_);
        if (__day < 1 || __day > 31) {
            return false;
        }
        if (__day <= 29) {
            return true;
        }
        //  Now we've got either 30 or 31
        const unsigned __month = static_cast<unsigned>(__month_);
        if (__month == 2) {
            return false;
        }
        if (__month == 4 || __month == 6 || __month == 9 || __month == 11) {
            return __day == 30;
        }
        return true;
    }

    // comparisons
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator==(
        const month_day& __lhs, const month_day& __rhs) noexcept
    {
        return __lhs.month() == __rhs.month() && __lhs.day() == __rhs.day();
    }
#if !CANN_ASC_STL_DETAIL_HAS_CXX20()
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator!=(
        const month_day& __lhs, const month_day& __rhs) noexcept
    {
        return __lhs.month() != __rhs.month() || __lhs.day() != __rhs.day();
    }
#endif  // !CANN_ASC_STL_DETAIL_HAS_CXX20()

    // Traditional relational operators (spaceship not supported)

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator<(
        const month_day& __lhs, const month_day& __rhs) noexcept
    {
        return __lhs.month() != __rhs.month() ? __lhs.month() < __rhs.month() : __lhs.day() < __rhs.day();
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator>(
        const month_day& __lhs, const month_day& __rhs) noexcept
    {
        return __rhs < __lhs;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator<=(
        const month_day& __lhs, const month_day& __rhs) noexcept
    {
        return !(__rhs < __lhs);
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator>=(
        const month_day& __lhs, const month_day& __rhs) noexcept
    {
        return !(__lhs < __rhs);
    }
};

// arithmetics
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr month_day operator/(
    const chrono::month& __lhs, const chrono::day& __rhs) noexcept
{
    return month_day{__lhs, __rhs};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr month_day operator/(
    const chrono::day& __lhs, const chrono::month& __rhs) noexcept
{
    return month_day{__rhs, __lhs};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr month_day operator/(const chrono::month& __lhs, int __rhs) noexcept
{
    return month_day{__lhs, chrono::day(__rhs)};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr month_day operator/(int __lhs, const chrono::day& __rhs) noexcept
{
    return month_day{chrono::month(__lhs), __rhs};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr month_day operator/(const chrono::day& __lhs, int __rhs) noexcept
{
    return month_day{chrono::month(__rhs), __lhs};
}

class month_day_last {
private:
    chrono::month __month_;

public:
    CANN_ASC_STL_API explicit constexpr month_day_last(const chrono::month& __month) noexcept : __month_{__month}
    {}

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::month month() const noexcept
    {
        return __month_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        return __month_.ok();
    }

    // comparisons

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator==(
        const month_day_last& __lhs, const month_day_last& __rhs) noexcept
    {
        return __lhs.month() == __rhs.month();
    }

#if !CANN_ASC_STL_DETAIL_HAS_CXX20()
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator!=(
        const month_day_last& __lhs, const month_day_last& __rhs) noexcept
    {
        return __lhs.month() != __rhs.month();
    }
#endif  // !CANN_ASC_STL_DETAIL_HAS_CXX20()

    // Traditional relational operators (spaceship not supported)

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator<(
        const month_day_last& __lhs, const month_day_last& __rhs) noexcept
    {
        return __lhs.month() < __rhs.month();
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator>(
        const month_day_last& __lhs, const month_day_last& __rhs) noexcept
    {
        return __lhs.month() > __rhs.month();
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator<=(
        const month_day_last& __lhs, const month_day_last& __rhs) noexcept
    {
        return __lhs.month() <= __rhs.month();
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator>=(
        const month_day_last& __lhs, const month_day_last& __rhs) noexcept
    {
        return __lhs.month() >= __rhs.month();
    }
};

// arithmetics
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr month_day_last operator/(
    const chrono::month& __lhs, last_spec) noexcept
{
    return month_day_last{__lhs};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr month_day_last operator/(
    last_spec, const chrono::month& __rhs) noexcept
{
    return month_day_last{__rhs};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr month_day_last operator/(int __lhs, last_spec) noexcept
{
    return month_day_last{chrono::month(__lhs)};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr month_day_last operator/(last_spec, int __rhs) noexcept
{
    return month_day_last{chrono::month(__rhs)};
}

}  // namespace chrono

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHRONO_MONTH_DAY_H
