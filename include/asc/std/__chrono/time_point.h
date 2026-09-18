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
    CANN_ASC_STL_API constexpr time_point() : value_(duration::zero())
    {}
    CANN_ASC_STL_API explicit constexpr time_point(const duration& value) : value_(value)
    {}
    template <class OtherDuration, enable_if_t<is_convertible_v<OtherDuration, duration>, int> = 0>
    CANN_ASC_STL_API constexpr time_point(const time_point<clock, OtherDuration>& other)
        : value_(other.time_since_epoch())
    {}
    CANN_ASC_STL_API constexpr duration time_since_epoch() const
    {
        return value_;
    }
    CANN_ASC_STL_API constexpr time_point& operator+=(const duration& value)
    {
        value_ += value;
        return *this;
    }
    CANN_ASC_STL_API constexpr time_point& operator-=(const duration& value)
    {
        value_ -= value;
        return *this;
    }
    CANN_ASC_STL_API constexpr time_point& operator++()
    {
        ++value_;
        return *this;
    }
    CANN_ASC_STL_API constexpr time_point operator++(int)
    {
        time_point old(*this);
        ++*this;
        return old;
    }
    CANN_ASC_STL_API constexpr time_point& operator--()
    {
        --value_;
        return *this;
    }
    CANN_ASC_STL_API constexpr time_point operator--(int)
    {
        time_point old(*this);
        --*this;
        return old;
    }
    CANN_ASC_STL_API static constexpr time_point min() noexcept
    {
        return time_point(duration::min());
    }
    CANN_ASC_STL_API static constexpr time_point max() noexcept
    {
        return time_point(duration::max());
    }

private:
    duration value_;
};
template <class ToDuration, class Clock, class Duration>
CANN_ASC_STL_API constexpr time_point<Clock, ToDuration> time_point_cast(const time_point<Clock, Duration>& value)
{
    return time_point<Clock, ToDuration>(duration_cast<ToDuration>(value.time_since_epoch()));
}
template <class Clock, class D1, class D2>
CANN_ASC_STL_API constexpr bool operator==(time_point<Clock, D1> left, time_point<Clock, D2> right)
{
    return left.time_since_epoch() == right.time_since_epoch();
}
template <class Clock, class D1, class D2>
CANN_ASC_STL_API constexpr bool operator!=(time_point<Clock, D1> left, time_point<Clock, D2> right)
{
    return !(left == right);
}
template <class Clock, class D1, class D2>
CANN_ASC_STL_API constexpr bool operator<(time_point<Clock, D1> left, time_point<Clock, D2> right)
{
    return left.time_since_epoch() < right.time_since_epoch();
}
template <class Clock, class D1, class D2>
CANN_ASC_STL_API constexpr auto operator-(time_point<Clock, D1> left,
    time_point<Clock, D2> right) -> decltype(left.time_since_epoch() - right.time_since_epoch())
{
    return left.time_since_epoch() - right.time_since_epoch();
}
template <class Clock, class Duration, class Rep, class Period>
CANN_ASC_STL_API constexpr time_point<Clock, common_type_t<Duration, duration<Rep, Period>>> operator+(
    time_point<Clock, Duration> point, duration<Rep, Period> value)
{
    using result_duration = common_type_t<Duration, duration<Rep, Period>>;
    return time_point<Clock, result_duration>(point.time_since_epoch() + value);
}
template <class ToDuration, class Clock, class Duration>
CANN_ASC_STL_API constexpr time_point<Clock, ToDuration> floor(const time_point<Clock, Duration>& value)
{
    return time_point<Clock, ToDuration>(::asc::std::chrono::floor<ToDuration>(value.time_since_epoch()));
}
template <class ToDuration, class Clock, class Duration>
CANN_ASC_STL_API constexpr time_point<Clock, ToDuration> ceil(const time_point<Clock, Duration>& value)
{
    return time_point<Clock, ToDuration>(::asc::std::chrono::ceil<ToDuration>(value.time_since_epoch()));
}
template <class ToDuration, class Clock, class Duration>
CANN_ASC_STL_API constexpr time_point<Clock, ToDuration> round(const time_point<Clock, Duration>& value)
{
    return time_point<Clock, ToDuration>(::asc::std::chrono::round<ToDuration>(value.time_since_epoch()));
}
}  // namespace chrono

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHRONO_TIME_POINT_H
