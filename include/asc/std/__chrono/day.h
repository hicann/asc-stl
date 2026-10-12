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

// Migrated from dev __asc/visibility.h: ASC-STL keeps only the inline
// semantics for ABI hidden; base asc/__detail/visibility.h has no such macro.
#ifndef CANN_ASC_STL_DETAIL_HIDE_FROM_ABI
#define CANN_ASC_STL_DETAIL_HIDE_FROM_ABI inline
#endif

// Migrated from dev __asc/dialect.h: base asc/__config has no standard-version
// number macro, so key it on CANN_ASC_STL_DETAIL_CPLUSPLUS instead.
#ifndef CANN_ASC_STL_DETAIL_STD_VER
#if CANN_ASC_STL_DETAIL_CPLUSPLUS <= 199711L
#define CANN_ASC_STL_DETAIL_STD_VER 2003
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 201103L
#define CANN_ASC_STL_DETAIL_STD_VER 2011
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 201402L
#define CANN_ASC_STL_DETAIL_STD_VER 2014
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 201703L
#define CANN_ASC_STL_DETAIL_STD_VER 2017
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 202002L
#define CANN_ASC_STL_DETAIL_STD_VER 2020
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 202302L
#define CANN_ASC_STL_DETAIL_STD_VER 2023
#else
#define CANN_ASC_STL_DETAIL_STD_VER 2024
#endif
#endif  // CANN_ASC_STL_DETAIL_STD_VER

CANN_ASC_STL_BEGIN_NAMESPACE

namespace chrono {
class day {
private:
    unsigned char __day_;

public:
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI day() = default;
    CANN_ASC_STL_API explicit constexpr day(unsigned __day) noexcept : __day_(static_cast<unsigned char>(__day))
    {}

    CANN_ASC_STL_API constexpr day& operator++() noexcept
    {
        ++__day_;
        return *this;
    }
    CANN_ASC_STL_API constexpr day operator++(int) noexcept
    {
        day __tmp = *this;
        ++__day_;
        return __tmp;
    }
    CANN_ASC_STL_API constexpr day& operator--() noexcept
    {
        --__day_;
        return *this;
    }
    CANN_ASC_STL_API constexpr day operator--(int) noexcept
    {
        day __tmp = *this;
        --__day_;
        return __tmp;
    }

    CANN_ASC_STL_API constexpr day& operator+=(const days& __dd) noexcept
    {
        __day_ += static_cast<unsigned char>(__dd.count());
        return *this;
    }

    CANN_ASC_STL_API constexpr day& operator-=(const days& __dd) noexcept
    {
        __day_ -= static_cast<unsigned char>(__dd.count());
        return *this;
    }

    CANN_ASC_STL_API explicit constexpr operator unsigned() const noexcept
    {
        return __day_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        return __day_ >= 1 && __day_ <= 31;
    }

    // Arithmetics

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr day operator+(const day& __lhs, const days& __rhs) noexcept
    {
        return day{static_cast<unsigned>(__lhs) + static_cast<unsigned>(__rhs.count())};
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr day operator+(const days& __lhs, const day& __rhs) noexcept
    {
        return day{static_cast<unsigned>(__lhs.count()) + static_cast<unsigned>(__rhs)};
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr day operator-(const day& __lhs, const days& __rhs) noexcept
    {
        return day{static_cast<unsigned>(__lhs) - static_cast<unsigned>(__rhs.count())};
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr days operator-(const day& __lhs, const day& __rhs) noexcept
    {
        return days{static_cast<int>(static_cast<unsigned>(__lhs)) - static_cast<int>(static_cast<unsigned>(__rhs))};
    }

    // Comparisons

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator==(
        const day& __lhs, const day& __rhs) noexcept
    {
        return static_cast<unsigned>(__lhs) == static_cast<unsigned>(__rhs);
    }

#if CANN_ASC_STL_DETAIL_STD_VER <= 2017
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator!=(
        const day& __lhs, const day& __rhs) noexcept
    {
        return static_cast<unsigned>(__lhs) != static_cast<unsigned>(__rhs);
    }
#endif  // CANN_ASC_STL_DETAIL_STD_VER <= 2017

    // Traditional relational operators (spaceship not supported)

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator<(const day& __lhs, const day& __rhs) noexcept
    {
        return static_cast<unsigned>(__lhs) < static_cast<unsigned>(__rhs);
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator>(const day& __lhs, const day& __rhs) noexcept
    {
        return static_cast<unsigned>(__lhs) > static_cast<unsigned>(__rhs);
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator<=(
        const day& __lhs, const day& __rhs) noexcept
    {
        return static_cast<unsigned>(__lhs) <= static_cast<unsigned>(__rhs);
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator>=(
        const day& __lhs, const day& __rhs) noexcept
    {
        return static_cast<unsigned>(__lhs) >= static_cast<unsigned>(__rhs);
    }
};
}  // namespace chrono

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHRONO_DAY_H
