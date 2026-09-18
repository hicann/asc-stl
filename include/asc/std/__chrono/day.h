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

#ifndef CANN_ASC_STL_ASC_STD___CHRONO_DAY_H
#define CANN_ASC_STL_ASC_STD___CHRONO_DAY_H

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

CANN_ASC_STL_BEGIN_NAMESPACE

namespace chrono {
class day {
public:
    CANN_ASC_STL_API constexpr day() = default;
    CANN_ASC_STL_API explicit constexpr day(unsigned value) noexcept : value_(value)
    {}
    CANN_ASC_STL_API constexpr explicit operator unsigned() const noexcept
    {
        return value_;
    }
    CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        return value_ >= 1 && value_ <= 31;
    }
    CANN_ASC_STL_API constexpr day& operator++() noexcept
    {
        ++value_;
        return *this;
    }
    CANN_ASC_STL_API constexpr day operator++(int) noexcept
    {
        day previous(*this);
        ++*this;
        return previous;
    }
    CANN_ASC_STL_API constexpr day& operator--() noexcept
    {
        --value_;
        return *this;
    }
    CANN_ASC_STL_API constexpr day operator--(int) noexcept
    {
        day previous(*this);
        --*this;
        return previous;
    }
    CANN_ASC_STL_API constexpr day& operator+=(const days& value) noexcept
    {
        value_ = static_cast<unsigned char>(static_cast<int>(value_) + value.count());
        return *this;
    }
    CANN_ASC_STL_API constexpr day& operator-=(const days& value) noexcept
    {
        return *this += days(-value.count());
    }

private:
    unsigned char value_{};
};
CANN_ASC_STL_API constexpr bool operator==(day left, day right) noexcept
{
    return static_cast<unsigned>(left) == static_cast<unsigned>(right);
}
CANN_ASC_STL_API constexpr bool operator!=(day left, day right) noexcept
{
    return !(left == right);
}
CANN_ASC_STL_API constexpr bool operator<(day left, day right) noexcept
{
    return static_cast<unsigned>(left) < static_cast<unsigned>(right);
}
CANN_ASC_STL_API constexpr bool operator>(day left, day right) noexcept
{
    return right < left;
}
CANN_ASC_STL_API constexpr bool operator<=(day left, day right) noexcept
{
    return !(right < left);
}
CANN_ASC_STL_API constexpr bool operator>=(day left, day right) noexcept
{
    return !(left < right);
}
CANN_ASC_STL_API constexpr day operator+(day value, const days& offset) noexcept
{
    return value += offset;
}
CANN_ASC_STL_API constexpr day operator+(const days& offset, day value) noexcept
{
    return value += offset;
}
CANN_ASC_STL_API constexpr day operator-(day value, const days& offset) noexcept
{
    return value -= offset;
}
CANN_ASC_STL_API constexpr days operator-(day left, day right) noexcept
{
    return days(static_cast<int>(static_cast<unsigned>(left)) - static_cast<int>(static_cast<unsigned>(right)));
}
}  // namespace chrono

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHRONO_DAY_H
