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

#ifndef CANN_ASC_STL_ASC_STD___CHRONO_WEEKDAY_H
#define CANN_ASC_STL_ASC_STD___CHRONO_WEEKDAY_H

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
#include <asc/std/__chrono/system_clock.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace chrono {

class weekday_indexed;
class weekday_last;
struct __weekday_constant_factory;

class weekday {
public:
    CANN_ASC_STL_API constexpr weekday() = default;
    CANN_ASC_STL_API explicit constexpr weekday(unsigned value) noexcept : value_(value == 7 ? 0 : value)
    {}
    CANN_ASC_STL_API constexpr weekday(const sys_days& value) noexcept
        : value_(from_days(value.time_since_epoch().count()))
    {}
    CANN_ASC_STL_API explicit constexpr weekday(const local_days& value) noexcept
        : value_(from_days(value.time_since_epoch().count()))
    {}
    CANN_ASC_STL_API constexpr unsigned c_encoding() const noexcept
    {
        return value_;
    }
    CANN_ASC_STL_API constexpr unsigned iso_encoding() const noexcept
    {
        return value_ == 0 ? 7 : value_;
    }
    CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        return value_ <= 6;
    }
    CANN_ASC_STL_API constexpr weekday& operator++() noexcept
    {
        return *this += days(1);
    }
    CANN_ASC_STL_API constexpr weekday operator++(int) noexcept
    {
        weekday previous(*this);
        ++*this;
        return previous;
    }
    CANN_ASC_STL_API constexpr weekday& operator--() noexcept
    {
        return *this -= days(1);
    }
    CANN_ASC_STL_API constexpr weekday operator--(int) noexcept
    {
        weekday previous(*this);
        --*this;
        return previous;
    }
    CANN_ASC_STL_API constexpr weekday& operator+=(const days& offset) noexcept
    {
        const int total = static_cast<int>(value_) + offset.count();
        value_ = static_cast<unsigned char>(total >= 0 ? total % 7 : 6 + (total + 1) % 7);
        return *this;
    }
    CANN_ASC_STL_API constexpr weekday& operator-=(const days& offset) noexcept
    {
        return *this += days(-offset.count());
    }
    CANN_ASC_STL_API constexpr weekday_indexed operator[](unsigned index) const noexcept;
    CANN_ASC_STL_API constexpr weekday_last operator[](last_spec) const noexcept;

private:
    friend struct __weekday_constant_factory;
    constexpr weekday(unsigned value, int) noexcept : value_(value == 7 ? 0 : value)
    {}
    CANN_ASC_STL_API static constexpr unsigned char from_days(long long count) noexcept
    {
        const long long value = count + 4;
        return static_cast<unsigned char>(value >= 0 ? value % 7 : 6 + (value + 1) % 7);
    }
    unsigned char value_{};
};

struct __weekday_constant_factory {
    static constexpr weekday make(unsigned value) noexcept
    {
        return weekday(value, 0);
    }
};

class weekday_indexed {
public:
    CANN_ASC_STL_API constexpr weekday_indexed() = default;
    CANN_ASC_STL_API constexpr weekday_indexed(const chrono::weekday& weekday_value, unsigned index) noexcept
        : weekday_(weekday_value), index_(index)
    {}
    CANN_ASC_STL_API constexpr chrono::weekday weekday() const noexcept
    {
        return weekday_;
    }
    CANN_ASC_STL_API constexpr unsigned index() const noexcept
    {
        return index_;
    }
    CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        return weekday_.ok() && index_ >= 1 && index_ <= 5;
    }

private:
    chrono::weekday weekday_{};
    unsigned char index_{};
};

class weekday_last {
public:
    CANN_ASC_STL_API explicit constexpr weekday_last(const chrono::weekday& weekday_value) noexcept
        : weekday_(weekday_value)
    {}
    CANN_ASC_STL_API constexpr chrono::weekday weekday() const noexcept
    {
        return weekday_;
    }
    CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        return weekday_.ok();
    }

private:
    chrono::weekday weekday_;
};

CANN_ASC_STL_API constexpr weekday_indexed weekday::operator[](unsigned index) const noexcept
{
    return weekday_indexed(*this, index);
}
CANN_ASC_STL_API constexpr weekday_last weekday::operator[](last_spec) const noexcept
{
    return weekday_last(*this);
}
CANN_ASC_STL_API constexpr bool operator==(weekday left, weekday right) noexcept
{
    return left.c_encoding() == right.c_encoding();
}
CANN_ASC_STL_API constexpr bool operator!=(weekday left, weekday right) noexcept
{
    return !(left == right);
}
CANN_ASC_STL_API constexpr bool operator==(weekday_indexed left, weekday_indexed right) noexcept
{
    return left.weekday() == right.weekday() && left.index() == right.index();
}
CANN_ASC_STL_API constexpr bool operator!=(weekday_indexed left, weekday_indexed right) noexcept
{
    return !(left == right);
}
CANN_ASC_STL_API constexpr bool operator==(weekday_last left, weekday_last right) noexcept
{
    return left.weekday() == right.weekday();
}
CANN_ASC_STL_API constexpr bool operator!=(weekday_last left, weekday_last right) noexcept
{
    return !(left == right);
}
CANN_ASC_STL_API constexpr weekday operator+(weekday value, const days& offset) noexcept
{
    return value += offset;
}
CANN_ASC_STL_API constexpr weekday operator+(const days& offset, weekday value) noexcept
{
    return value += offset;
}
CANN_ASC_STL_API constexpr weekday operator-(weekday value, const days& offset) noexcept
{
    return value -= offset;
}
CANN_ASC_STL_API constexpr days operator-(weekday left, weekday right) noexcept
{
    return days((static_cast<int>(left.c_encoding()) - static_cast<int>(right.c_encoding()) + 7) % 7);
}

inline constexpr weekday Sunday = __weekday_constant_factory::make(0);
inline constexpr weekday Monday = __weekday_constant_factory::make(1);
inline constexpr weekday Tuesday = __weekday_constant_factory::make(2);
inline constexpr weekday Wednesday = __weekday_constant_factory::make(3);
inline constexpr weekday Thursday = __weekday_constant_factory::make(4);
inline constexpr weekday Friday = __weekday_constant_factory::make(5);
inline constexpr weekday Saturday = __weekday_constant_factory::make(6);

}  // namespace chrono

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHRONO_WEEKDAY_H
