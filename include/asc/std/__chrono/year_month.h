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
#include <asc/std/__chrono/month.h>
#include <asc/std/__chrono/year.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace chrono {

class year_month {
public:
    CANN_ASC_STL_API constexpr year_month() = default;
    CANN_ASC_STL_API constexpr year_month(const chrono::year& year_value, const chrono::month& month_value) noexcept
        : year_(year_value), month_(month_value)
    {}
    CANN_ASC_STL_API constexpr chrono::year year() const noexcept
    {
        return year_;
    }
    CANN_ASC_STL_API constexpr chrono::month month() const noexcept
    {
        return month_;
    }
    CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        return year_.ok() && month_.ok();
    }
    CANN_ASC_STL_API constexpr year_month& operator+=(const months& offset) noexcept
    {
        const long long total = static_cast<long long>(static_cast<int>(year_)) * 12 +
            static_cast<int>(static_cast<unsigned>(month_)) - 1 + offset.count();
        const long long quotient = total >= 0 ? total / 12 : (total - 11) / 12;
        year_ = chrono::year(static_cast<int>(quotient));
        month_ = chrono::month(static_cast<unsigned>(total - quotient * 12 + 1));
        return *this;
    }
    CANN_ASC_STL_API constexpr year_month& operator-=(const months& offset) noexcept
    {
        return *this += months(-offset.count());
    }
    CANN_ASC_STL_API constexpr year_month& operator+=(const years& offset) noexcept
    {
        year_ += offset;
        return *this;
    }
    CANN_ASC_STL_API constexpr year_month& operator-=(const years& offset) noexcept
    {
        return *this += years(-offset.count());
    }

private:
    chrono::year year_{};
    chrono::month month_{};
};

CANN_ASC_STL_API constexpr bool operator==(year_month left, year_month right) noexcept
{
    return left.year() == right.year() && left.month() == right.month();
}
CANN_ASC_STL_API constexpr bool operator!=(year_month left, year_month right) noexcept
{
    return !(left == right);
}
CANN_ASC_STL_API constexpr bool operator<(year_month left, year_month right) noexcept
{
    return left.year() < right.year() || (!(right.year() < left.year()) && left.month() < right.month());
}
CANN_ASC_STL_API constexpr bool operator>(year_month left, year_month right) noexcept
{
    return right < left;
}
CANN_ASC_STL_API constexpr bool operator<=(year_month left, year_month right) noexcept
{
    return !(right < left);
}
CANN_ASC_STL_API constexpr bool operator>=(year_month left, year_month right) noexcept
{
    return !(left < right);
}
CANN_ASC_STL_API constexpr year_month operator+(year_month value, const months& offset) noexcept
{
    return value += offset;
}
CANN_ASC_STL_API constexpr year_month operator+(const months& offset, year_month value) noexcept
{
    return value += offset;
}
CANN_ASC_STL_API constexpr year_month operator-(year_month value, const months& offset) noexcept
{
    return value -= offset;
}
CANN_ASC_STL_API constexpr months operator-(year_month left, year_month right) noexcept
{
    return months((static_cast<int>(left.year()) - static_cast<int>(right.year())) * 12 +
        static_cast<int>(static_cast<unsigned>(left.month())) - static_cast<int>(static_cast<unsigned>(right.month())));
}
CANN_ASC_STL_API constexpr year_month operator+(year_month value, const years& offset) noexcept
{
    return value += offset;
}
CANN_ASC_STL_API constexpr year_month operator+(const years& offset, year_month value) noexcept
{
    return value += offset;
}
CANN_ASC_STL_API constexpr year_month operator-(year_month value, const years& offset) noexcept
{
    return value -= offset;
}
CANN_ASC_STL_API constexpr year_month operator/(
    const chrono::year& year_value, const chrono::month& month_value) noexcept
{
    return year_month(year_value, month_value);
}
CANN_ASC_STL_API constexpr year_month operator/(const chrono::year& year_value, unsigned month_value) noexcept
{
    return year_value / chrono::month(month_value);
}

}  // namespace chrono

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHRONO_YEAR_MONTH_H
