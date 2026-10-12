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
#include <asc/std/__chrono/duration.h>
#include <asc/std/__chrono/system_clock.h>
#include <asc/std/__chrono/time_point.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace chrono {

class weekday_indexed;
class weekday_last;
struct __weekday_constant_factory;

class weekday {
private:
    unsigned char __weekday_;

    // https://howardhinnant.github.io/date_algorithms.html#weekday_from_days
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API static constexpr unsigned char __weekday_from_days(int __days) noexcept
    {
        return static_cast<unsigned char>(
            static_cast<unsigned>(__days >= -4 ? (__days + 4) % 7 : (__days + 5) % 7 + 6));
    }

public:
    CANN_ASC_STL_API weekday() = default;
    CANN_ASC_STL_API explicit constexpr weekday(unsigned __weekday) noexcept
        : __weekday_(static_cast<unsigned char>(__weekday == 7 ? 0 : __weekday))
    {}
    CANN_ASC_STL_API constexpr weekday(const sys_days& __sysd) noexcept
        : __weekday_(__weekday_from_days(__sysd.time_since_epoch().count()))
    {}
    CANN_ASC_STL_API explicit constexpr weekday(const local_days& __locd) noexcept
        : __weekday_(__weekday_from_days(__locd.time_since_epoch().count()))
    {}

    CANN_ASC_STL_API constexpr weekday& operator++() noexcept
    {
        __weekday_ = (__weekday_ == 6 ? 0 : __weekday_ + 1);
        return *this;
    }
    CANN_ASC_STL_API constexpr weekday operator++(int) noexcept
    {
        weekday __tmp = *this;
        ++(*this);
        return __tmp;
    }
    CANN_ASC_STL_API constexpr weekday& operator--() noexcept
    {
        __weekday_ = (__weekday_ == 0 ? 6 : __weekday_ - 1);
        return *this;
    }
    CANN_ASC_STL_API constexpr weekday operator--(int) noexcept
    {
        weekday __tmp = *this;
        --(*this);
        return __tmp;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr unsigned c_encoding() const noexcept
    {
        return __weekday_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr unsigned iso_encoding() const noexcept
    {
        return __weekday_ == 0u ? 7 : __weekday_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        return __weekday_ <= 6;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr weekday_indexed operator[](unsigned __index) const noexcept;
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr weekday_last operator[](last_spec) const noexcept;

    // arithmetics
    CANN_ASC_STL_API constexpr weekday& operator+=(const days& __dd) noexcept
    {
        *this = *this + __dd;
        return *this;
    }

    CANN_ASC_STL_API constexpr weekday& operator-=(const days& __dd) noexcept
    {
        *this = *this - __dd;
        return *this;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr days operator-(
        const weekday& __lhs, const weekday& __rhs) noexcept
    {
        const int __wdu = static_cast<int>(__lhs.c_encoding()) - static_cast<int>(__rhs.c_encoding());
        const int __wk = (__wdu >= 0 ? __wdu : __wdu - 6) / 7;
        return days{__wdu - __wk * 7};
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr weekday operator+(
        const weekday& __lhs, const days& __rhs) noexcept
    {
        auto const __mu = static_cast<long long>(__lhs.c_encoding()) + __rhs.count();
        auto const __yr = (__mu >= 0 ? __mu : __mu - 6) / 7;
        return weekday{static_cast<unsigned>(__mu - __yr * 7)};
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr weekday operator+(
        const days& __lhs, const weekday& __rhs) noexcept
    {
        return __rhs + __lhs;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr weekday operator-(
        const weekday& __lhs, const days& __rhs) noexcept
    {
        return __lhs + -__rhs;
    }

    // comparisons
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator==(
        const weekday& __lhs, const weekday& __rhs) noexcept
    {
        return __lhs.c_encoding() == __rhs.c_encoding();
    }

#if !CANN_ASC_STL_DETAIL_HAS_CXX20()
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator!=(
        const weekday& __lhs, const weekday& __rhs) noexcept
    {
        return __lhs.c_encoding() != __rhs.c_encoding();
    }
#endif  // !CANN_ASC_STL_DETAIL_HAS_CXX20()

    // Traditional relational operators (spaceship not supported)

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator<(
        const weekday& __lhs, const weekday& __rhs) noexcept
    {
        return __lhs.c_encoding() < __rhs.c_encoding();
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator>(
        const weekday& __lhs, const weekday& __rhs) noexcept
    {
        return __lhs.c_encoding() > __rhs.c_encoding();
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator<=(
        const weekday& __lhs, const weekday& __rhs) noexcept
    {
        return __lhs.c_encoding() <= __rhs.c_encoding();
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator>=(
        const weekday& __lhs, const weekday& __rhs) noexcept
    {
        return __lhs.c_encoding() >= __rhs.c_encoding();
    }

private:
    friend struct __weekday_constant_factory;
    constexpr weekday(unsigned __weekday, int) noexcept
        : __weekday_(static_cast<unsigned char>(__weekday == 7 ? 0 : __weekday))
    {}
};

class weekday_indexed {
private:
    chrono::weekday __weekday_;
    unsigned char __idx_;

public:
    CANN_ASC_STL_API weekday_indexed() = default;
    CANN_ASC_STL_API constexpr weekday_indexed(const chrono::weekday& __weekday, unsigned __idx) noexcept
        : __weekday_{__weekday}, __idx_(static_cast<unsigned char>(__idx))
    {}

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::weekday weekday() const noexcept
    {
        return __weekday_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr unsigned index() const noexcept
    {
        return __idx_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        return __weekday_.ok() && __idx_ >= 1 && __idx_ <= 5;
    }

    // comparisons
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator==(
        const weekday_indexed& __lhs, const weekday_indexed& __rhs) noexcept
    {
        return __lhs.weekday() == __rhs.weekday() && __lhs.index() == __rhs.index();
    }

#if !CANN_ASC_STL_DETAIL_HAS_CXX20()
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator!=(
        const weekday_indexed& __lhs, const weekday_indexed& __rhs) noexcept
    {
        return __lhs.weekday() != __rhs.weekday() || __lhs.index() != __rhs.index();
    }
#endif  // !CANN_ASC_STL_DETAIL_HAS_CXX20()
};

class weekday_last {
private:
    chrono::weekday __weekday_;

public:
    CANN_ASC_STL_API explicit constexpr weekday_last(const chrono::weekday& __weekday) noexcept : __weekday_{__weekday}
    {}

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::weekday weekday() const noexcept
    {
        return __weekday_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        return __weekday_.ok();
    }

    // comparisons
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator==(
        const weekday_last& __lhs, const weekday_last& __rhs) noexcept
    {
        return __lhs.weekday() == __rhs.weekday();
    }

#if !CANN_ASC_STL_DETAIL_HAS_CXX20()
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator!=(
        const weekday_last& __lhs, const weekday_last& __rhs) noexcept
    {
        return __lhs.weekday() != __rhs.weekday();
    }
#endif  // !CANN_ASC_STL_DETAIL_HAS_CXX20()
};

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr weekday_indexed weekday::operator[](unsigned __index) const noexcept
{
    return weekday_indexed{*this, __index};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr weekday_last weekday::operator[](last_spec) const noexcept
{
    return weekday_last{*this};
}

struct __weekday_constant_factory {
    static constexpr weekday make(unsigned value) noexcept
    {
        return weekday(value, 0);
    }
};

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
