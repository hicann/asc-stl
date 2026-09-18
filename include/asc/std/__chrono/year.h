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

#ifndef CANN_ASC_STL_ASC_STD___CHRONO_YEAR_H
#define CANN_ASC_STL_ASC_STD___CHRONO_YEAR_H

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
#include <asc/std/limits>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace chrono {
class year {
public:
    CANN_ASC_STL_API constexpr year() = default;
    CANN_ASC_STL_API explicit constexpr year(int value) noexcept : value_(static_cast<short>(value))
    {}
    CANN_ASC_STL_API constexpr explicit operator int() const noexcept
    {
        return value_;
    }
    CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        return value_ >= -32767;
    }
    CANN_ASC_STL_API constexpr bool is_leap() const noexcept
    {
        const int value = static_cast<int>(*this);
        return value % 4 == 0 && (value % 100 != 0 || value % 400 == 0);
    }
    CANN_ASC_STL_API constexpr year operator+() const noexcept
    {
        return *this;
    }
    CANN_ASC_STL_API constexpr year operator-() const noexcept
    {
        return year(-static_cast<int>(*this));
    }
    CANN_ASC_STL_API constexpr year& operator++() noexcept
    {
        ++value_;
        return *this;
    }
    CANN_ASC_STL_API constexpr year operator++(int) noexcept
    {
        year previous(*this);
        ++*this;
        return previous;
    }
    CANN_ASC_STL_API constexpr year& operator--() noexcept
    {
        --value_;
        return *this;
    }
    CANN_ASC_STL_API constexpr year operator--(int) noexcept
    {
        year previous(*this);
        --*this;
        return previous;
    }
    CANN_ASC_STL_API constexpr year& operator+=(const years& value) noexcept
    {
        value_ = static_cast<short>(static_cast<int>(value_) + value.count());
        return *this;
    }
    CANN_ASC_STL_API constexpr year& operator-=(const years& value) noexcept
    {
        return *this += years(-value.count());
    }
    CANN_ASC_STL_API static constexpr year min() noexcept
    {
        return year(-32767);
    }
    CANN_ASC_STL_API static constexpr year max() noexcept
    {
        return year(32767);
    }

private:
    short value_{};
};
CANN_ASC_STL_API constexpr bool operator==(year left, year right) noexcept
{
    return static_cast<int>(left) == static_cast<int>(right);
}
CANN_ASC_STL_API constexpr bool operator!=(year left, year right) noexcept
{
    return !(left == right);
}
CANN_ASC_STL_API constexpr bool operator<(year left, year right) noexcept
{
    return static_cast<int>(left) < static_cast<int>(right);
}
CANN_ASC_STL_API constexpr bool operator>(year left, year right) noexcept
{
    return right < left;
}
CANN_ASC_STL_API constexpr bool operator<=(year left, year right) noexcept
{
    return !(right < left);
}
CANN_ASC_STL_API constexpr bool operator>=(year left, year right) noexcept
{
    return !(left < right);
}
CANN_ASC_STL_API constexpr year operator+(year value, const years& offset) noexcept
{
    return value += offset;
}
CANN_ASC_STL_API constexpr year operator+(const years& offset, year value) noexcept
{
    return value += offset;
}
CANN_ASC_STL_API constexpr year operator-(year value, const years& offset) noexcept
{
    return value -= offset;
}
CANN_ASC_STL_API constexpr years operator-(year left, year right) noexcept
{
    return years(static_cast<int>(left) - static_cast<int>(right));
}
}  // namespace chrono

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHRONO_YEAR_H
