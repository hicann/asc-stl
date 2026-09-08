/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#ifndef CANN_ASC_STL_ASC_STD___CHRONO_DURATION_H
#define CANN_ASC_STL_ASC_STD___CHRONO_DURATION_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/common_type.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_floating_point.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/limits>
#include <asc/std/ratio>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace chrono {
template <class Rep, class Period>
class duration;
}  // namespace chrono

template <class Period1, class Period2>
struct __duration_period_gcd {
    static constexpr intmax_t numerator = __ratio_gcd_value<Period1::num, Period2::num>::value;
    static constexpr intmax_t denominator_gcd = __ratio_gcd_value<Period1::den, Period2::den>::value;
    using type = ratio<numerator, (Period1::den / denominator_gcd) * Period2::den>;
};

template <class Rep1, class Period1, class Rep2, class Period2>
struct common_type<chrono::duration<Rep1, Period1>, chrono::duration<Rep2, Period2>> {
    using type = chrono::duration<common_type_t<Rep1, Rep2>, typename __duration_period_gcd<Period1, Period2>::type>;
};

namespace chrono {

template <class Rep>
struct treat_as_floating_point : is_floating_point<Rep> {};
template <class Rep>
inline constexpr bool treat_as_floating_point_v = treat_as_floating_point<Rep>::value;
template <class ToDuration, class Rep, class Period>
CANN_ASC_STL_API constexpr ToDuration duration_cast(const duration<Rep, Period>& value);
template <class Rep>
struct duration_values {
    CANN_ASC_STL_API static constexpr Rep zero() noexcept
    {
        return Rep(0);
    }
    CANN_ASC_STL_API static constexpr Rep min() noexcept
    {
        return numeric_limits<Rep>::lowest();
    }
    CANN_ASC_STL_API static constexpr Rep max() noexcept
    {
        return numeric_limits<Rep>::max();  // NOLINT(build/include_what_you_use)
    }
};

template <class Rep, class Period = ratio<1>>
class duration {
public:
    using rep = Rep;
    using period = typename Period::type;
    CANN_ASC_STL_API constexpr duration() = default;
    template <class Rep2, enable_if_t<is_convertible_v<const Rep2&, Rep>, int> = 0>
    CANN_ASC_STL_API constexpr explicit duration(const Rep2& value) : value_(value)
    {}
    template <class Rep2, class Period2>
    CANN_ASC_STL_API constexpr duration(const duration<Rep2, Period2>& other)
        : value_(duration_cast<duration>(other).count())
    {}
    CANN_ASC_STL_API constexpr rep count() const
    {
        return value_;
    }
    CANN_ASC_STL_API constexpr common_type_t<duration> operator+() const
    {
        return *this;
    }
    CANN_ASC_STL_API constexpr common_type_t<duration> operator-() const
    {
        return duration(-value_);
    }
    CANN_ASC_STL_API constexpr duration& operator++()
    {
        ++value_;
        return *this;
    }
    CANN_ASC_STL_API constexpr duration operator++(int)
    {
        duration old(*this);
        ++value_;
        return old;
    }
    CANN_ASC_STL_API constexpr duration& operator--()
    {
        --value_;
        return *this;
    }
    CANN_ASC_STL_API constexpr duration operator--(int)
    {
        duration old(*this);
        --value_;
        return old;
    }
    CANN_ASC_STL_API constexpr duration& operator+=(const duration& other)
    {
        value_ += other.value_;
        return *this;
    }
    CANN_ASC_STL_API constexpr duration& operator-=(const duration& other)
    {
        value_ -= other.value_;
        return *this;
    }
    CANN_ASC_STL_API constexpr duration& operator*=(const rep& scalar)
    {
        value_ *= scalar;
        return *this;
    }
    CANN_ASC_STL_API constexpr duration& operator/=(const rep& scalar)
    {
        value_ /= scalar;
        return *this;
    }
    CANN_ASC_STL_API constexpr duration& operator%=(const rep& scalar)
    {
        value_ %= scalar;
        return *this;
    }
    CANN_ASC_STL_API constexpr duration& operator%=(const duration& other)
    {
        value_ %= other.value_;
        return *this;
    }
    CANN_ASC_STL_API static constexpr duration zero() noexcept
    {
        return duration(duration_values<rep>::zero());
    }
    CANN_ASC_STL_API static constexpr duration min() noexcept
    {
        return duration(duration_values<rep>::min());
    }
    CANN_ASC_STL_API static constexpr duration max() noexcept
    {
        return duration(duration_values<rep>::max());
    }

private:
    Rep value_{};
};

template <class ToDuration, class Rep, class Period>
CANN_ASC_STL_API constexpr ToDuration duration_cast(const duration<Rep, Period>& value)
{
    using factor = ratio_divide<Period, typename ToDuration::period>;
    using common_rep = common_type_t<typename ToDuration::rep, Rep, long long>;
    return ToDuration(static_cast<typename ToDuration::rep>(static_cast<common_rep>(value.count()) *
        static_cast<common_rep>(factor::num) / static_cast<common_rep>(factor::den)));
}
template <class Rep1, class Period1, class Rep2, class Period2>
CANN_ASC_STL_API constexpr common_type_t<duration<Rep1, Period1>, duration<Rep2, Period2>> operator+(
    duration<Rep1, Period1> left, duration<Rep2, Period2> right)
{
    using result_type = common_type_t<duration<Rep1, Period1>, duration<Rep2, Period2>>;
    return result_type(result_type(left).count() + result_type(right).count());
}
template <class Rep1, class Period1, class Rep2, class Period2>
CANN_ASC_STL_API constexpr common_type_t<duration<Rep1, Period1>, duration<Rep2, Period2>> operator-(
    duration<Rep1, Period1> left, duration<Rep2, Period2> right)
{
    using result_type = common_type_t<duration<Rep1, Period1>, duration<Rep2, Period2>>;
    return result_type(result_type(left).count() - result_type(right).count());
}
template <class Rep1, class Period1, class Rep2, class Period2>
CANN_ASC_STL_API constexpr bool operator==(duration<Rep1, Period1> left, duration<Rep2, Period2> right)
{
    using common_duration = common_type_t<duration<Rep1, Period1>, duration<Rep2, Period2>>;
    return common_duration(left).count() == common_duration(right).count();
}
template <class Rep1, class Period1, class Rep2, class Period2>
CANN_ASC_STL_API constexpr bool operator!=(duration<Rep1, Period1> left, duration<Rep2, Period2> right)
{
    return !(left == right);
}
template <class Rep1, class Period1, class Rep2, class Period2>
CANN_ASC_STL_API constexpr bool operator<(duration<Rep1, Period1> left, duration<Rep2, Period2> right)
{
    using common_duration = common_type_t<duration<Rep1, Period1>, duration<Rep2, Period2>>;
    return common_duration(left).count() < common_duration(right).count();
}
template <class Rep1, class Period1, class Rep2, class Period2>
CANN_ASC_STL_API constexpr bool operator>(duration<Rep1, Period1> left, duration<Rep2, Period2> right)
{
    return right < left;
}
template <class Rep1, class Period1, class Rep2, class Period2>
CANN_ASC_STL_API constexpr bool operator<=(duration<Rep1, Period1> left, duration<Rep2, Period2> right)
{
    return !(right < left);
}
template <class Rep1, class Period1, class Rep2, class Period2>
CANN_ASC_STL_API constexpr bool operator>=(duration<Rep1, Period1> left, duration<Rep2, Period2> right)
{
    return !(left < right);
}
template <class Rep, class Period>
CANN_ASC_STL_API constexpr duration<Rep, Period> abs(duration<Rep, Period> value)
{
    return value.count() < 0 ? -value : value;
}
template <class ToDuration, class Rep, class Period>
CANN_ASC_STL_API constexpr ToDuration floor(const duration<Rep, Period>& value)
{
    ToDuration result = duration_cast<ToDuration>(value);
    return result > value ? result - ToDuration(1) : result;
}
template <class ToDuration, class Rep, class Period>
CANN_ASC_STL_API constexpr ToDuration ceil(const duration<Rep, Period>& value)
{
    ToDuration result = duration_cast<ToDuration>(value);
    return result < value ? result + ToDuration(1) : result;
}
template <class ToDuration, class Rep, class Period>
CANN_ASC_STL_API constexpr ToDuration round(const duration<Rep, Period>& value)
{
    const ToDuration lower = floor<ToDuration>(value);
    const ToDuration upper = lower + ToDuration(1);
    const auto lower_difference = value - lower;
    const auto upper_difference = upper - value;
    if (lower_difference < upper_difference) {
        return lower;
    }
    if (upper_difference < lower_difference) {
        return upper;
    }
    return lower.count() % 2 == 0 ? lower : upper;
}

using nanoseconds = duration<long long, nano>;
using microseconds = duration<long long, micro>;
using milliseconds = duration<long long, milli>;
using seconds = duration<long long>;
using minutes = duration<long, ratio<60>>;
using hours = duration<long, ratio<3600>>;
using days = duration<int, ratio_multiply<ratio<24>, hours::period>>;
using weeks = duration<int, ratio_multiply<ratio<7>, days::period>>;
using years = duration<int, ratio_multiply<ratio<146097, 400>, days::period>>;
using months = duration<int, ratio_divide<years::period, ratio<12>>>;

}  // namespace chrono

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHRONO_DURATION_H
