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
private:
    friend struct __month_constant_factory;

    constexpr month(unsigned __value, int) noexcept : __month_(__value)
    {}
    // Zero-initialized: a default-constructed month deterministically yields ok() == false, avoiding the
    // undefined behavior of reading an uninitialized unsigned value
    unsigned char __month_{};

    CANN_ASC_STL_API constexpr void __add_clamped(long long __add) noexcept
    {
        const auto __mu = static_cast<long long>(static_cast<unsigned>(__month_)) + (__add - 1);
        const auto __yr = (__mu >= 0 ? __mu : __mu - 11) / 12;
        __month_ = static_cast<unsigned char>(__mu - __yr * 12 + 1);
    }

public:
    CANN_ASC_STL_API constexpr month() = default;
    CANN_ASC_STL_API explicit constexpr month(unsigned __month) noexcept : __month_(static_cast<unsigned char>(__month))
    {}
    CANN_ASC_STL_API constexpr month& operator++() noexcept
    {
        __add_clamped(1);
        return *this;
    }
    CANN_ASC_STL_API constexpr month operator++(int) noexcept
    {
        month __tmp = *this;
        __add_clamped(1);
        return __tmp;
    }
    CANN_ASC_STL_API constexpr month& operator--() noexcept
    {
        __add_clamped(-1);
        return *this;
    }
    CANN_ASC_STL_API constexpr month operator--(int) noexcept
    {
        month __tmp = *this;
        __add_clamped(-1);
        return __tmp;
    }

    CANN_ASC_STL_API constexpr month& operator+=(const months& __dm) noexcept
    {
        __add_clamped(__dm.count());
        return *this;
    }

    CANN_ASC_STL_API constexpr month& operator-=(const months& __dm) noexcept
    {
        __add_clamped(-__dm.count());
        return *this;
    }

    CANN_ASC_STL_API explicit constexpr operator unsigned() const noexcept
    {
        return __month_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        return __month_ >= 1 && __month_ <= 12;
    }

    // Arithmetics

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr month operator+(
        const month& __lhs, const months& __rhs) noexcept
    {
        month __ret{__lhs};
        __ret.__add_clamped(__rhs.count());
        return __ret;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr month operator+(
        const months& __lhs, const month& __rhs) noexcept
    {
        month __ret{__rhs};
        __ret.__add_clamped(__lhs.count());
        return __ret;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr month operator-(
        const month& __lhs, const months& __rhs) noexcept
    {
        month __ret{__lhs};
        __ret.__add_clamped(-__rhs.count());
        return __ret;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr months operator-(
        const month& __lhs, const month& __rhs) noexcept
    {
        auto const __dm = static_cast<unsigned>(__lhs) - static_cast<unsigned>(__rhs);
        return months(__dm <= 11 ? __dm : __dm + 12);
    }

    // Comparisons
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator==(
        const month& __lhs, const month& __rhs) noexcept
    {
        return static_cast<unsigned>(__lhs) == static_cast<unsigned>(__rhs);
    }

#if !CANN_ASC_STL_DETAIL_HAS_CXX20()
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator!=(
        const month& __lhs, const month& __rhs) noexcept
    {
        return static_cast<unsigned>(__lhs) != static_cast<unsigned>(__rhs);
    }
#endif  // !CANN_ASC_STL_DETAIL_HAS_CXX20()

    // Traditional relational operators (spaceship not supported)

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator<(
        const month& __lhs, const month& __rhs) noexcept
    {
        return static_cast<unsigned>(__lhs) < static_cast<unsigned>(__rhs);
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator>(
        const month& __lhs, const month& __rhs) noexcept
    {
        return static_cast<unsigned>(__lhs) > static_cast<unsigned>(__rhs);
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator<=(
        const month& __lhs, const month& __rhs) noexcept
    {
        return static_cast<unsigned>(__lhs) <= static_cast<unsigned>(__rhs);
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator>=(
        const month& __lhs, const month& __rhs) noexcept
    {
        return static_cast<unsigned>(__lhs) >= static_cast<unsigned>(__rhs);
    }
};

struct __month_constant_factory {
    static constexpr month make(unsigned __value) noexcept
    {
        return month(__value, 0);
    }
};

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
