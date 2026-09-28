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

#ifndef CANN_ASC_STL_ASC_STD___CHRONO_HH_MM_SS_H
#define CANN_ASC_STL_ASC_STD___CHRONO_HH_MM_SS_H

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
#include <asc/std/ratio>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace chrono {

CANN_ASC_STL_API constexpr bool is_am(const hours& value) noexcept
{
    return value >= hours(0) && value < hours(12);
}
CANN_ASC_STL_API constexpr bool is_pm(const hours& value) noexcept
{
    return value >= hours(12) && value < hours(24);
}
CANN_ASC_STL_API constexpr hours make12(const hours& value) noexcept
{
    const long remainder = value.count() % 12;
    return hours(remainder == 0 ? 12 : remainder);
}
CANN_ASC_STL_API constexpr hours make24(const hours& value, bool pm) noexcept
{
    const long normalized = value.count() % 12;
    return hours(normalized + (pm ? 12 : 0));
}

template <long long Denominator>
struct __fractional_width {
    static constexpr unsigned value = []() constexpr {
        long long remaining = Denominator;
        unsigned twos = 0;
        unsigned fives = 0;
        while (remaining % 2 == 0) {
            remaining /= 2;
            ++twos;
        }
        while (remaining % 5 == 0) {
            remaining /= 5;
            ++fives;
        }
        const unsigned width = twos > fives ? twos : fives;
        return remaining == 1 && width <= 18 ? width : 6;
    }();
};

template <unsigned Width>
struct __power_of_ten {
    static constexpr long long value = 10 * __power_of_ten<Width - 1>::value;
};
template <>
struct __power_of_ten<0> {
    static constexpr long long value = 1;
};

template <class Duration>
class hh_mm_ss {
public:
    using duration_period = typename Duration::period;
    static constexpr unsigned fractional_width = __fractional_width<duration_period::den>::value;
    using precision = duration<long long, ratio<1, __power_of_ten<fractional_width>::value>>;

    CANN_ASC_STL_API constexpr hh_mm_ss() noexcept = default;
    CANN_ASC_STL_API explicit constexpr hh_mm_ss(Duration value) noexcept : negative_(value < Duration::zero())
    {
        precision remaining = duration_cast<precision>(negative_ ? -value : value);
        hours_ = duration_cast<chrono::hours>(remaining);
        remaining -= duration_cast<precision>(hours_);
        minutes_ = duration_cast<chrono::minutes>(remaining);
        remaining -= duration_cast<precision>(minutes_);
        seconds_ = duration_cast<chrono::seconds>(remaining);
        subseconds_ = remaining - duration_cast<precision>(seconds_);
    }
    CANN_ASC_STL_API constexpr bool is_negative() const noexcept
    {
        return negative_;
    }
    CANN_ASC_STL_API constexpr chrono::hours hours() const noexcept
    {
        return hours_;
    }
    CANN_ASC_STL_API constexpr chrono::minutes minutes() const noexcept
    {
        return minutes_;
    }
    CANN_ASC_STL_API constexpr chrono::seconds seconds() const noexcept
    {
        return seconds_;
    }
    CANN_ASC_STL_API constexpr precision subseconds() const noexcept
    {
        return subseconds_;
    }
    CANN_ASC_STL_API constexpr precision to_duration() const noexcept
    {
        const precision result = duration_cast<precision>(hours_) + duration_cast<precision>(minutes_) +
            duration_cast<precision>(seconds_) + subseconds_;
        return negative_ ? -result : result;
    }
    CANN_ASC_STL_API constexpr explicit operator precision() const noexcept
    {
        return to_duration();
    }

private:
    bool negative_{};
    chrono::hours hours_{};
    chrono::minutes minutes_{};
    chrono::seconds seconds_{};
    precision subseconds_{};
};

}  // namespace chrono

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHRONO_HH_MM_SS_H
