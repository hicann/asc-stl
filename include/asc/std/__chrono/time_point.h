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

#ifndef CANN_ASC_STL_ASC_STD___CHRONO_TIME_POINT_H
#define CANN_ASC_STL_ASC_STD___CHRONO_TIME_POINT_H

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
#include <asc/std/__type_traits/common_type.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/limits>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace chrono {
template <class Clock, class Duration = typename Clock::duration>
class time_point {
public:
    using clock = Clock;
    using duration = Duration;
    using rep = typename duration::rep;
    using period = typename duration::period;

private:
    duration __d_;

public:
    CANN_ASC_STL_API constexpr time_point() : __d_(duration::zero())
    {}
    CANN_ASC_STL_API constexpr explicit time_point(const duration& __d) : __d_(__d)
    {}

    // conversions
    template <class OtherDuration, enable_if_t<is_convertible_v<OtherDuration, duration>, int> = 0>
    CANN_ASC_STL_API constexpr time_point(const time_point<clock, OtherDuration>& __t) : __d_(__t.time_since_epoch())
    {}

    // observer
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr duration time_since_epoch() const
    {
        return __d_;
    }

    // operations
    CANN_ASC_STL_API constexpr time_point& operator++()
    {
        ++__d_;
        return *this;
    }
    CANN_ASC_STL_API constexpr time_point operator++(int)
    {
        return time_point{__d_++};
    }
    CANN_ASC_STL_API constexpr time_point& operator--()
    {
        --__d_;
        return *this;
    }
    CANN_ASC_STL_API constexpr time_point operator--(int)
    {
        return time_point{__d_--};
    }

    // arithmetic
    CANN_ASC_STL_API constexpr time_point& operator+=(const duration& __d)
    {
        __d_ += __d;
        return *this;
    }
    CANN_ASC_STL_API constexpr time_point& operator-=(const duration& __d)
    {
        __d_ -= __d;
        return *this;
    }

    // special values
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API static constexpr time_point min() noexcept
    {
        return time_point(duration::min());
    }
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API static constexpr time_point max() noexcept
    {
        return time_point(duration::max());
    }

    // arithmetics
    template <class Rep2, class Period2>
    CANN_ASC_STL_NODISCARD
        CANN_ASC_STL_API friend constexpr time_point<Clock, common_type_t<Duration, chrono::duration<Rep2, Period2>>>
        operator+(const time_point& __lhs, const chrono::duration<Rep2, Period2>& __rhs)
    {
        using result_duration = common_type_t<Duration, chrono::duration<Rep2, Period2>>;
        return time_point<Clock, result_duration>{__lhs.time_since_epoch() + __rhs};
    }

    template <class Rep2, class Period2>
    CANN_ASC_STL_NODISCARD
        CANN_ASC_STL_API friend constexpr time_point<Clock, common_type_t<Duration, chrono::duration<Rep2, Period2>>>
        operator+(const chrono::duration<Rep2, Period2>& __lhs, const time_point& __rhs)
    {
        using result_duration = common_type_t<Duration, chrono::duration<Rep2, Period2>>;
        return time_point<Clock, result_duration>{__lhs + __rhs.time_since_epoch()};
    }

    template <class Rep2, class Period2>
    CANN_ASC_STL_NODISCARD
        CANN_ASC_STL_API friend constexpr time_point<Clock, common_type_t<Duration, chrono::duration<Rep2, Period2>>>
        operator-(const time_point& __lhs, const chrono::duration<Rep2, Period2>& __rhs)
    {
        using result_duration = common_type_t<Duration, chrono::duration<Rep2, Period2>>;
        return time_point<Clock, result_duration>{__lhs.time_since_epoch() - __rhs};
    }

    template <class Duration2>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr common_type_t<Duration, Duration2> operator-(
        const time_point& __lhs, const time_point<Clock, Duration2>& __rhs)
    {
        return __lhs.time_since_epoch() - __rhs.time_since_epoch();
    }

    // comparisons
    template <class Duration2>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator==(
        const time_point& __lhs, const time_point<Clock, Duration2>& __rhs)
    {
        return __lhs.time_since_epoch() == __rhs.time_since_epoch();
    }

#if !CANN_ASC_STL_DETAIL_HAS_CXX20()
    template <class Duration2>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator!=(
        const time_point& __lhs, const time_point<Clock, Duration2>& __rhs)
    {
        return __lhs.time_since_epoch() != __rhs.time_since_epoch();
    }
#endif  // !CANN_ASC_STL_DETAIL_HAS_CXX20()

    // Traditional relational operators (spaceship not supported)

    template <class Duration2>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator<(
        const time_point& __lhs, const time_point<Clock, Duration2>& __rhs)
    {
        return __lhs.time_since_epoch() < __rhs.time_since_epoch();
    }

    template <class Duration2>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator>(
        const time_point& __lhs, const time_point<Clock, Duration2>& __rhs)
    {
        return __lhs.time_since_epoch() > __rhs.time_since_epoch();
    }

    template <class Duration2>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator<=(
        const time_point& __lhs, const time_point<Clock, Duration2>& __rhs)
    {
        return __lhs.time_since_epoch() <= __rhs.time_since_epoch();
    }

    template <class Duration2>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator>=(
        const time_point& __lhs, const time_point<Clock, Duration2>& __rhs)
    {
        return __lhs.time_since_epoch() >= __rhs.time_since_epoch();
    }
};
}  // namespace chrono

template <class Clock, class Duration1, class Duration2>
struct common_type<chrono::time_point<Clock, Duration1>, chrono::time_point<Clock, Duration2>> {
    using type = chrono::time_point<Clock, typename common_type<Duration1, Duration2>::type>;
};

namespace chrono {
template <class ToDuration, class Clock, class Duration>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr time_point<Clock, ToDuration> time_point_cast(
    const time_point<Clock, Duration>& __t)
{
    return time_point<Clock, ToDuration>(duration_cast<ToDuration>(__t.time_since_epoch()));
}

template <class ToDuration, class Clock, class Duration>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr time_point<Clock, ToDuration> floor(
    const time_point<Clock, Duration>& __t)
{
    return time_point<Clock, ToDuration>{chrono::floor<ToDuration>(__t.time_since_epoch())};
}

template <class ToDuration, class Clock, class Duration>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr time_point<Clock, ToDuration> ceil(
    const time_point<Clock, Duration>& __t)
{
    return time_point<Clock, ToDuration>{chrono::ceil<ToDuration>(__t.time_since_epoch())};
}

template <class ToDuration, class Clock, class Duration>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr time_point<Clock, ToDuration> round(
    const time_point<Clock, Duration>& __t)
{
    return time_point<Clock, ToDuration>{chrono::round<ToDuration>(__t.time_since_epoch())};
}
}  // namespace chrono

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHRONO_TIME_POINT_H
