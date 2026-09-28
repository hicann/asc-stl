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
public:
    CANN_ASC_STL_API constexpr month_weekday() = default;
    CANN_ASC_STL_API constexpr month_weekday(
        const chrono::month& month_value, const chrono::weekday_indexed& weekday_value) noexcept
        : month_(month_value), weekday_(weekday_value)
    {}
    CANN_ASC_STL_API constexpr chrono::month month() const noexcept
    {
        return month_;
    }
    CANN_ASC_STL_API constexpr chrono::weekday_indexed weekday_indexed() const noexcept
    {
        return weekday_;
    }
    CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        return month_.ok() && weekday_.ok();
    }

private:
    chrono::month month_{};
    chrono::weekday_indexed weekday_{};
};

class month_weekday_last {
public:
    CANN_ASC_STL_API constexpr month_weekday_last(
        const chrono::month& month_value, const chrono::weekday_last& weekday_value) noexcept
        : month_(month_value), weekday_(weekday_value)
    {}
    CANN_ASC_STL_API constexpr chrono::month month() const noexcept
    {
        return month_;
    }
    CANN_ASC_STL_API constexpr chrono::weekday_last weekday_last() const noexcept
    {
        return weekday_;
    }
    CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        return month_.ok() && weekday_.ok();
    }

private:
    chrono::month month_;
    chrono::weekday_last weekday_;
};

CANN_ASC_STL_API constexpr bool operator==(month_weekday left, month_weekday right) noexcept
{
    return left.month() == right.month() && left.weekday_indexed() == right.weekday_indexed();
}
CANN_ASC_STL_API constexpr bool operator!=(month_weekday left, month_weekday right) noexcept
{
    return !(left == right);
}
CANN_ASC_STL_API constexpr bool operator==(month_weekday_last left, month_weekday_last right) noexcept
{
    return left.month() == right.month() && left.weekday_last() == right.weekday_last();
}
CANN_ASC_STL_API constexpr bool operator!=(month_weekday_last left, month_weekday_last right) noexcept
{
    return !(left == right);
}
CANN_ASC_STL_API constexpr month_weekday operator/(
    const chrono::month& month_value, const chrono::weekday_indexed& weekday_value) noexcept
{
    return month_weekday(month_value, weekday_value);
}
CANN_ASC_STL_API constexpr month_weekday operator/(
    const chrono::weekday_indexed& weekday_value, const chrono::month& month_value) noexcept
{
    return month_value / weekday_value;
}
CANN_ASC_STL_API constexpr month_weekday operator/(
    int month_value, const chrono::weekday_indexed& weekday_value) noexcept
{
    return chrono::month(static_cast<unsigned>(month_value)) / weekday_value;
}
CANN_ASC_STL_API constexpr month_weekday operator/(
    const chrono::weekday_indexed& weekday_value, int month_value) noexcept
{
    return chrono::month(static_cast<unsigned>(month_value)) / weekday_value;
}
CANN_ASC_STL_API constexpr month_weekday_last operator/(
    const chrono::month& month_value, const chrono::weekday_last& weekday_value) noexcept
{
    return month_weekday_last(month_value, weekday_value);
}
CANN_ASC_STL_API constexpr month_weekday_last operator/(
    const chrono::weekday_last& weekday_value, const chrono::month& month_value) noexcept
{
    return month_value / weekday_value;
}
CANN_ASC_STL_API constexpr month_weekday_last operator/(
    int month_value, const chrono::weekday_last& weekday_value) noexcept
{
    return chrono::month(static_cast<unsigned>(month_value)) / weekday_value;
}
CANN_ASC_STL_API constexpr month_weekday_last operator/(
    const chrono::weekday_last& weekday_value, int month_value) noexcept
{
    return chrono::month(static_cast<unsigned>(month_value)) / weekday_value;
}

}  // namespace chrono

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHRONO_MONTH_WEEKDAY_H
