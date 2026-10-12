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

#ifndef CANN_ASC_STL_ASC_STD___CHRONO_MONTH_WEEKDAY_H
#define CANN_ASC_STL_ASC_STD___CHRONO_MONTH_WEEKDAY_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__chrono/month.h>
#include <asc/std/__chrono/weekday.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace chrono {

class month_weekday {
private:
    chrono::month __month_;
    chrono::weekday_indexed __weekday_indexed_;

public:
    CANN_ASC_STL_API month_weekday() = default;
    CANN_ASC_STL_API constexpr month_weekday(
        const chrono::month& __month, const chrono::weekday_indexed& __weekday_indexed) noexcept
        : __month_{__month}, __weekday_indexed_{__weekday_indexed}
    {}

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::month month() const noexcept
    {
        return __month_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::weekday_indexed weekday_indexed() const noexcept
    {
        return __weekday_indexed_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        return __month_.ok() && __weekday_indexed_.ok();
    }

    // comparisons
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator==(
        const month_weekday& __lhs, const month_weekday& __rhs) noexcept
    {
        return __lhs.month() == __rhs.month() && __lhs.weekday_indexed() == __rhs.weekday_indexed();
    }

#if !CANN_ASC_STL_DETAIL_HAS_CXX20()
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator!=(
        const month_weekday& __lhs, const month_weekday& __rhs) noexcept
    {
        return __lhs.month() != __rhs.month() || __lhs.weekday_indexed() != __rhs.weekday_indexed();
    }
#endif  // !CANN_ASC_STL_DETAIL_HAS_CXX20()
};

// arithmetics
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr month_weekday operator/(
    const chrono::month& __lhs, const chrono::weekday_indexed& __rhs) noexcept
{
    return month_weekday{__lhs, __rhs};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr month_weekday operator/(
    int __lhs, const chrono::weekday_indexed& __rhs) noexcept
{
    return month_weekday{chrono::month(__lhs), __rhs};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr month_weekday operator/(
    const chrono::weekday_indexed& __lhs, const chrono::month& __rhs) noexcept
{
    return month_weekday{__rhs, __lhs};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr month_weekday operator/(
    const chrono::weekday_indexed& __lhs, int __rhs) noexcept
{
    return month_weekday{chrono::month(__rhs), __lhs};
}

class month_weekday_last {
private:
    chrono::month __month_;
    chrono::weekday_last __weekday_last_;

public:
    CANN_ASC_STL_API constexpr month_weekday_last(
        const chrono::month& __month, const chrono::weekday_last& __weekday_last) noexcept
        : __month_{__month}, __weekday_last_{__weekday_last}
    {}

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::month month() const noexcept
    {
        return __month_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::weekday_last weekday_last() const noexcept
    {
        return __weekday_last_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        return __month_.ok() && __weekday_last_.ok();
    }

    // comparisons
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator==(
        const month_weekday_last& __lhs, const month_weekday_last& __rhs) noexcept
    {
        return __lhs.month() == __rhs.month() && __lhs.weekday_last() == __rhs.weekday_last();
    }

#if !CANN_ASC_STL_DETAIL_HAS_CXX20()
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator!=(
        const month_weekday_last& __lhs, const month_weekday_last& __rhs) noexcept
    {
        return __lhs.month() != __rhs.month() || __lhs.weekday_last() != __rhs.weekday_last();
    }
#endif  // !CANN_ASC_STL_DETAIL_HAS_CXX20()
};

// arithmetics
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr month_weekday_last operator/(
    const chrono::month& __lhs, const chrono::weekday_last& __rhs) noexcept
{
    return month_weekday_last{__lhs, __rhs};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr month_weekday_last operator/(
    int __lhs, const chrono::weekday_last& __rhs) noexcept
{
    return month_weekday_last{chrono::month(__lhs), __rhs};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr month_weekday_last operator/(
    const chrono::weekday_last& __lhs, const chrono::month& __rhs) noexcept
{
    return month_weekday_last{__rhs, __lhs};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr month_weekday_last operator/(
    const chrono::weekday_last& __lhs, int __rhs) noexcept
{
    return month_weekday_last{chrono::month(__rhs), __lhs};
}

}  // namespace chrono

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHRONO_MONTH_WEEKDAY_H
