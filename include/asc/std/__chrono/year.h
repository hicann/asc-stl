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
private:
    short __year_;

public:
    CANN_ASC_STL_API year() = default;
    CANN_ASC_STL_API explicit constexpr year(int __year) noexcept : __year_(static_cast<short>(__year))
    {}

    CANN_ASC_STL_API constexpr year& operator++() noexcept
    {
        ++__year_;
        return *this;
    }
    CANN_ASC_STL_API constexpr year operator++(int) noexcept
    {
        year __tmp = *this;
        ++__year_;
        return __tmp;
    }
    CANN_ASC_STL_API constexpr year& operator--() noexcept
    {
        --__year_;
        return *this;
    }
    CANN_ASC_STL_API constexpr year operator--(int) noexcept
    {
        year __tmp = *this;
        --__year_;
        return __tmp;
    }

    CANN_ASC_STL_API constexpr year& operator+=(const years& __dy) noexcept
    {
        __year_ = static_cast<short>(static_cast<long long>(__year_) + __dy.count());
        return *this;
    }

    CANN_ASC_STL_API constexpr year& operator-=(const years& __dy) noexcept
    {
        __year_ = static_cast<short>(static_cast<long long>(__year_) - __dy.count());
        return *this;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year operator+() const noexcept
    {
        return *this;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr year operator-() const noexcept
    {
        return year{-__year_};
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool is_leap() const noexcept
    {
        return __year_ % 4 == 0 && (__year_ % 100 != 0 || __year_ % 400 == 0);
    }

    CANN_ASC_STL_API constexpr explicit operator int() const noexcept
    {
        return __year_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool ok() const noexcept
    {
        return static_cast<int>(min()) <= __year_ && __year_ <= static_cast<int>(max());
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API static constexpr year min() noexcept
    {
        return year{-32767};
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API static constexpr year max() noexcept
    {
        return year{32767};
    }

    // arithmetics
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr year operator+(
        const year& __lhs, const years& __rhs) noexcept
    {
        return year{static_cast<int>(__lhs) + __rhs.count()};
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr year operator+(
        const years& __lhs, const year& __rhs) noexcept
    {
        return year{static_cast<int>(__rhs) + __lhs.count()};
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr year operator-(
        const year& __lhs, const years& __rhs) noexcept
    {
        return year{static_cast<int>(__lhs) - __rhs.count()};
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr years operator-(
        const year& __lhs, const year& __rhs) noexcept
    {
        return years{static_cast<int>(__lhs) - static_cast<int>(__rhs)};
    }

    // comparisons
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator==(
        const year& __lhs, const year& __rhs) noexcept
    {
        return static_cast<int>(__lhs) == static_cast<int>(__rhs);
    }

#if !CANN_ASC_STL_DETAIL_HAS_CXX20()
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator!=(
        const year& __lhs, const year& __rhs) noexcept
    {
        return static_cast<int>(__lhs) != static_cast<int>(__rhs);
    }
#endif  // !CANN_ASC_STL_DETAIL_HAS_CXX20()

    // Traditional relational operators (spaceship not supported)

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator<(
        const year& __lhs, const year& __rhs) noexcept
    {
        return static_cast<int>(__lhs) < static_cast<int>(__rhs);
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator>(
        const year& __lhs, const year& __rhs) noexcept
    {
        return static_cast<int>(__lhs) > static_cast<int>(__rhs);
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator<=(
        const year& __lhs, const year& __rhs) noexcept
    {
        return static_cast<int>(__lhs) <= static_cast<int>(__rhs);
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator>=(
        const year& __lhs, const year& __rhs) noexcept
    {
        return static_cast<int>(__lhs) >= static_cast<int>(__rhs);
    }
};
}  // namespace chrono

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHRONO_YEAR_H
