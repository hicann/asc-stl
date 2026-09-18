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

#ifndef CANN_ASC_STL_ASC_STD___CHRONO_MONTH_H
#define CANN_ASC_STL_ASC_STD___CHRONO_MONTH_H

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
struct __month_constant_factory;

class month {
public:
    CANN_ASC_STL_API constexpr month() = default;
    CANN_ASC_STL_API explicit constexpr month(unsigned value) noexcept : value_(value)
    {}
    CANN_ASC_STL_API constexpr explicit operator unsigned() const noexcept
    {
        return value_;
    }
    CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        return value_ >= 1 && value_ <= 12;
    }
    CANN_ASC_STL_API constexpr month& operator++() noexcept
    {
        value_ = static_cast<unsigned char>(value_ == 12 ? 1 : value_ + 1);
        return *this;
    }
    CANN_ASC_STL_API constexpr month operator++(int) noexcept
    {
        month previous(*this);
        ++*this;
        return previous;
    }
    CANN_ASC_STL_API constexpr month& operator--() noexcept
    {
        value_ = static_cast<unsigned char>(value_ == 1 ? 12 : value_ - 1);
        return *this;
    }
    CANN_ASC_STL_API constexpr month operator--(int) noexcept
    {
        month previous(*this);
        --*this;
        return previous;
    }
    CANN_ASC_STL_API constexpr month& operator+=(const months& value) noexcept
    {
        const long long zero_based = static_cast<long long>(value_) - 1 + value.count();
        const long long reduced = zero_based >= 0 ? zero_based % 12 : 11 + (zero_based + 1) % 12;
        value_ = static_cast<unsigned char>(reduced + 1);
        return *this;
    }
    CANN_ASC_STL_API constexpr month& operator-=(const months& value) noexcept
    {
        return *this += months(-value.count());
    }

private:
    friend struct __month_constant_factory;
    constexpr month(unsigned value, int) noexcept : value_(value)
    {}
    unsigned char value_{};
};

struct __month_constant_factory {
    static constexpr month make(unsigned value) noexcept
    {
        return month(value, 0);
    }
};
CANN_ASC_STL_API constexpr bool operator==(month left, month right) noexcept
{
    return static_cast<unsigned>(left) == static_cast<unsigned>(right);
}
CANN_ASC_STL_API constexpr bool operator!=(month left, month right) noexcept
{
    return !(left == right);
}
CANN_ASC_STL_API constexpr bool operator<(month left, month right) noexcept
{
    return static_cast<unsigned>(left) < static_cast<unsigned>(right);
}
CANN_ASC_STL_API constexpr bool operator>(month left, month right) noexcept
{
    return right < left;
}
CANN_ASC_STL_API constexpr bool operator<=(month left, month right) noexcept
{
    return !(right < left);
}
CANN_ASC_STL_API constexpr bool operator>=(month left, month right) noexcept
{
    return !(left < right);
}
CANN_ASC_STL_API constexpr month operator+(month value, const months& offset) noexcept
{
    return value += offset;
}
CANN_ASC_STL_API constexpr month operator+(const months& offset, month value) noexcept
{
    return value += offset;
}
CANN_ASC_STL_API constexpr month operator-(month value, const months& offset) noexcept
{
    return value -= offset;
}
CANN_ASC_STL_API constexpr months operator-(month left, month right) noexcept
{
    const int left_value = static_cast<int>(static_cast<unsigned>(left));
    const int right_value = static_cast<int>(static_cast<unsigned>(right));
    return months((left_value - right_value + 12) % 12);
}

inline constexpr month January = __month_constant_factory::make(1);
inline constexpr month February = __month_constant_factory::make(2);
inline constexpr month March = __month_constant_factory::make(3);
inline constexpr month April = __month_constant_factory::make(4);
inline constexpr month May = __month_constant_factory::make(5);
inline constexpr month June = __month_constant_factory::make(6);
inline constexpr month July = __month_constant_factory::make(7);
inline constexpr month August = __month_constant_factory::make(8);
inline constexpr month September = __month_constant_factory::make(9);
inline constexpr month October = __month_constant_factory::make(10);
inline constexpr month November = __month_constant_factory::make(11);
inline constexpr month December = __month_constant_factory::make(12);
}  // namespace chrono

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHRONO_MONTH_H
