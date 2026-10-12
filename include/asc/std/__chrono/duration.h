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
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/limits>
#include <asc/std/ratio>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace chrono {
template <class _Rep, class _Period = ratio<1>>
class duration;

template <class _Tp>
inline constexpr bool __is_asc_std_duration_v = false;

template <class _Rep, class _Period>
inline constexpr bool __is_asc_std_duration_v<duration<_Rep, _Period>> = true;

template <class _Rep, class _Period>
inline constexpr bool __is_asc_std_duration_v<const duration<_Rep, _Period>> = true;

template <class _Rep, class _Period>
inline constexpr bool __is_asc_std_duration_v<volatile duration<_Rep, _Period>> = true;

template <class _Rep, class _Period>
inline constexpr bool __is_asc_std_duration_v<const volatile duration<_Rep, _Period>> = true;

// 基座 asc/std/ratio 未提供 __is_asc_std_ratio_v，按 dev 语义内联于 chrono 作用域（等价于
// dev ratio 头中的同名 trait），用于 duration 的 static_assert 检查。
template <class _Tp>
inline constexpr bool __is_asc_std_ratio_v = false;

template <intmax_t _Num, intmax_t _Den>
inline constexpr bool __is_asc_std_ratio_v<ratio<_Num, _Den>> = true;

// 除零守卫：仅整型 rep 把 0 除数替换为 1 以避免设备侧静态检查的除零告警；
// 浮点 rep 保持标准语义（除以 0.0 得 ±inf、取模得 NaN），不做替换。
template <class _Rep>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr _Rep __safe_divisor(const _Rep& __rhs)
{
    if constexpr (is_integral_v<_Rep>) {
        return __rhs == _Rep{0} ? _Rep{1} : __rhs;
    } else {
        return __rhs;
    }
}
}  // namespace chrono

template <class Period1, class Period2>
struct __duration_period_gcd {
    static constexpr intmax_t numerator = __ratio_gcd_value<Period1::num, Period2::num>::value;
    static constexpr intmax_t denominator_gcd = __ratio_gcd_value<Period1::den, Period2::den>::value;
    using type = ratio<numerator, (Period1::den / denominator_gcd) * Period2::den>;
};

template <class _Rep1, class _Period1, class _Rep2, class _Period2>
struct common_type<chrono::duration<_Rep1, _Period1>, chrono::duration<_Rep2, _Period2>> {
    using type =
        chrono::duration<common_type_t<_Rep1, _Rep2>, typename __duration_period_gcd<_Period1, _Period2>::type>;
};

namespace chrono {
// duration_cast

template <class _ToDuration, class _Rep, class _Period, enable_if_t<__is_asc_std_duration_v<_ToDuration>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr _ToDuration duration_cast(const duration<_Rep, _Period>& __fd)
{
    using _FromDuration = duration<_Rep, _Period>;
    using _CPeriod = typename ratio_divide<_Period, typename _ToDuration::period>::type;
    if constexpr (_CPeriod::num == 1 && _CPeriod::den == 1) {
        return _ToDuration{static_cast<typename _ToDuration::rep>(__fd.count())};
    } else if constexpr (_CPeriod::num == 1 && _CPeriod::den != 1) {
        using _Ct = common_type_t<typename _ToDuration::rep, typename _FromDuration::rep, intmax_t>;
        return _ToDuration{
            static_cast<typename _ToDuration::rep>(static_cast<_Ct>(__fd.count()) / static_cast<_Ct>(_CPeriod::den))};
    } else if constexpr (_CPeriod::num != 1 && _CPeriod::den == 1) {
        using _Ct = common_type_t<typename _ToDuration::rep, typename _FromDuration::rep, intmax_t>;
        return _ToDuration{
            static_cast<typename _ToDuration::rep>(static_cast<_Ct>(__fd.count()) * static_cast<_Ct>(_CPeriod::num))};
    } else {  // _CPeriod::num != 1 && _CPeriod::den != 1
        using _Ct = common_type_t<typename _ToDuration::rep, typename _FromDuration::rep, intmax_t>;
        return _ToDuration{static_cast<typename _ToDuration::rep>(
            static_cast<_Ct>(__fd.count()) * static_cast<_Ct>(_CPeriod::num) / static_cast<_Ct>(_CPeriod::den))};
    }
}

template <class _Rep>
struct treat_as_floating_point : is_floating_point<_Rep> {};

template <class _Rep>
inline constexpr bool treat_as_floating_point_v = is_floating_point_v<_Rep>;

template <class _Rep>
struct duration_values {
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API static constexpr _Rep zero() noexcept
    {
        return _Rep{0};
    }
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API static constexpr _Rep max() noexcept
    {
        return numeric_limits<_Rep>::max();
    }
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API static constexpr _Rep min() noexcept
    {
        return numeric_limits<_Rep>::lowest();
    }
};

template <class _ToDuration, class _Rep, class _Period, enable_if_t<__is_asc_std_duration_v<_ToDuration>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr _ToDuration floor(const duration<_Rep, _Period>& __d)
{
    _ToDuration __t = asc::std::chrono::duration_cast<_ToDuration>(__d);
    if (__t > __d) {
        __t = __t - _ToDuration{1};
    }
    return __t;
}

template <class _ToDuration, class _Rep, class _Period, enable_if_t<__is_asc_std_duration_v<_ToDuration>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr _ToDuration ceil(const duration<_Rep, _Period>& __d)
{
    _ToDuration __t = asc::std::chrono::duration_cast<_ToDuration>(__d);
    if (__t < __d) {
        __t = __t + _ToDuration{1};
    }
    return __t;
}

template <class _ToDuration, class _Rep, class _Period, enable_if_t<__is_asc_std_duration_v<_ToDuration>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr _ToDuration round(const duration<_Rep, _Period>& __d)
{
    _ToDuration __lower = asc::std::chrono::floor<_ToDuration>(__d);
    _ToDuration __upper = __lower + _ToDuration{1};
    auto __lowerDiff = __d - __lower;
    auto __upperDiff = __upper - __d;
    if (__lowerDiff < __upperDiff) {
        return __lower;
    }
    if (__lowerDiff > __upperDiff) {
        return __upper;
    }
    return __lower.count() & 1 ? __upper : __lower;
}

template <class _Rep, class _Period,
    enable_if_t<numeric_limits<_Rep>::is_signed, int> = 0>  // NOLINT(build/include_what_you_use)
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr duration<_Rep, _Period> abs(duration<_Rep, _Period> __d)
{
    return __d >= __d.zero() ? +__d : -__d;
}

// duration

template <class _Rep, class _Period>
class duration {
    static_assert(!__is_asc_std_duration_v<_Rep>, "A duration representation can not be a duration");
    static_assert(__is_asc_std_ratio_v<_Period>, "Second template parameter of duration must be a std::ratio");
    static_assert(_Period::num > 0, "duration period must be positive");

    template <class _R1, class _R2>
    struct __no_overflow {
    private:
        static constexpr intmax_t __gcd_n1_n2 = __ratio_gcd_value<_R1::num, _R2::num>::value;
        static constexpr intmax_t __gcd_d1_d2 = __ratio_gcd_value<_R1::den, _R2::den>::value;
        static constexpr intmax_t __n1 = _R1::num / __gcd_n1_n2;
        static constexpr intmax_t __d1 = _R1::den / __gcd_d1_d2;
        static constexpr intmax_t __n2 = _R2::num / __gcd_n1_n2;
        static constexpr intmax_t __d2 = _R2::den / __gcd_d1_d2;
        static constexpr intmax_t max = -((intmax_t(1) << (sizeof(intmax_t) * CHAR_BIT - 1)) + 1);

        template <intmax_t _Xp, intmax_t _Yp, bool __overflow>
        struct __mul  // __overflow == false
        {
            static constexpr intmax_t value = _Xp * _Yp;
        };

        template <intmax_t _Xp, intmax_t _Yp>
        struct __mul<_Xp, _Yp, true> {
            static constexpr intmax_t value = 1;
        };

    public:
        static constexpr bool value = (__n1 <= max / __d2) && (__n2 <= max / __d1);
        using type = ratio<__mul<__n1, __d2, !value>::value, __mul<__n2, __d1, !value>::value>;
    };

public:
    using rep = _Rep;
    using period = typename _Period::type;

private:
    rep __rep_;

public:
    CANN_ASC_STL_API constexpr duration() = default;

    template <class _Rep2,
        enable_if_t<is_convertible_v<const _Rep2&, rep> &&
                (treat_as_floating_point_v<rep> || !treat_as_floating_point_v<_Rep2>),
            int> = 0>
    CANN_ASC_STL_API constexpr explicit duration(const _Rep2& __r) : __rep_(static_cast<rep>(__r))
    {}

    // conversions
    template <class _Rep2, class _Period2,
        enable_if_t<__no_overflow<_Period2, period>::value &&
                (treat_as_floating_point_v<rep> ||
                    (__no_overflow<_Period2, period>::type::den == 1 && !treat_as_floating_point_v<_Rep2>)),
            int> = 0>
    CANN_ASC_STL_API constexpr duration(const duration<_Rep2, _Period2>& __d)
        : __rep_(asc::std::chrono::duration_cast<duration>(__d).count())
    {}

    // observer

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr rep count() const
    {
        return __rep_;
    }

    // arithmetic

    CANN_ASC_STL_API constexpr common_type_t<duration> operator+() const
    {
        return common_type_t<duration>(*this);
    }
    CANN_ASC_STL_API constexpr common_type_t<duration> operator-() const
    {
        return common_type_t<duration>(-__rep_);
    }
    CANN_ASC_STL_API constexpr duration& operator++()
    {
        ++__rep_;
        return *this;
    }
    CANN_ASC_STL_API constexpr duration operator++(int)
    {
        return duration{__rep_++};
    }
    CANN_ASC_STL_API constexpr duration& operator--()
    {
        --__rep_;
        return *this;
    }
    CANN_ASC_STL_API constexpr duration operator--(int)
    {
        return duration{__rep_--};
    }

    CANN_ASC_STL_API constexpr duration& operator+=(const duration& __d)
    {
        __rep_ += __d.count();
        return *this;
    }
    CANN_ASC_STL_API constexpr duration& operator-=(const duration& __d)
    {
        __rep_ -= __d.count();
        return *this;
    }

    CANN_ASC_STL_API constexpr duration& operator*=(const rep& rhs)
    {
        __rep_ *= rhs;
        return *this;
    }
    CANN_ASC_STL_API constexpr duration& operator/=(const rep& rhs)
    {
        __rep_ /= __safe_divisor(rhs);
        return *this;
    }
    CANN_ASC_STL_API constexpr duration& operator%=(const rep& rhs)
    {
        __rep_ %= __safe_divisor(rhs);
        return *this;
    }
    CANN_ASC_STL_API constexpr duration& operator%=(const duration& rhs)
    {
        __rep_ %= __safe_divisor(rhs.count());
        return *this;
    }

    // special values

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API static constexpr duration zero() noexcept
    {
        return duration{duration_values<rep>::zero()};
    }
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API static constexpr duration min() noexcept
    {
        return duration{duration_values<rep>::min()};
    }
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API static constexpr duration max() noexcept
    {
        return duration{duration_values<rep>::max()};
    }

    // Comparisons

    template <class _Rep2, class _Period2>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator==(
        const duration& __lhs, const duration<_Rep2, _Period2>& __rhs)
    {
        if constexpr (is_same_v<duration, duration<_Rep2, _Period2>>) {
            return __lhs.count() == __rhs.count();
        } else {
            using _Ct = common_type_t<duration, duration<_Rep2, _Period2>>;
            return _Ct(__lhs).count() == _Ct(__rhs).count();
        }
    }

#if !CANN_ASC_STL_DETAIL_HAS_CXX20()
    template <class _Rep2, class _Period2>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator!=(
        const duration& __lhs, const duration<_Rep2, _Period2>& __rhs)
    {
        if constexpr (is_same_v<duration, duration<_Rep2, _Period2>>) {
            return __lhs.count() != __rhs.count();
        } else {
            using _Ct = common_type_t<duration, duration<_Rep2, _Period2>>;
            return _Ct(__lhs).count() != _Ct(__rhs).count();
        }
    }
#endif  // !CANN_ASC_STL_DETAIL_HAS_CXX20()

    // Traditional relational operators (spaceship not supported)

    template <class _Rep2, class _Period2>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator<(
        const duration& __lhs, const duration<_Rep2, _Period2>& __rhs)
    {
        if constexpr (is_same_v<duration, duration<_Rep2, _Period2>>) {
            return __lhs.count() < __rhs.count();
        } else {
            using _Ct = common_type_t<duration, duration<_Rep2, _Period2>>;
            return _Ct(__lhs).count() < _Ct(__rhs).count();
        }
    }

    template <class _Rep2, class _Period2>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator>(
        const duration& __lhs, const duration<_Rep2, _Period2>& __rhs)
    {
        return __rhs < __lhs;
    }

    template <class _Rep2, class _Period2>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator<=(
        const duration& __lhs, const duration<_Rep2, _Period2>& __rhs)
    {
        return !(__rhs < __lhs);
    }

    template <class _Rep2, class _Period2>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr bool operator>=(
        const duration& __lhs, const duration<_Rep2, _Period2>& __rhs)
    {
        return !(__lhs < __rhs);
    }

    // Arithmetic

    template <class _Rep2, class _Period2>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr common_type_t<duration, duration<_Rep2, _Period2>>
    operator+(const duration& __lhs, const duration<_Rep2, _Period2>& __rhs)
    {
        using _Cd = common_type_t<duration, duration<_Rep2, _Period2>>;
        return _Cd(_Cd(__lhs).count() + _Cd(__rhs).count());
    }

    template <class _Rep2, class _Period2>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr common_type_t<duration, duration<_Rep2, _Period2>>
    operator-(const duration& __lhs, const duration<_Rep2, _Period2>& __rhs)
    {
        using _Cd = common_type_t<duration, duration<_Rep2, _Period2>>;
        return _Cd(_Cd(__lhs).count() - _Cd(__rhs).count());
    }

    template <class _Rep2, enable_if_t<is_convertible_v<const _Rep2, common_type_t<_Rep, _Rep2>>, int> = 0>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr duration<common_type_t<_Rep, _Rep2>, _Period> operator*(
        const duration& __d, const _Rep2& __s)
    {
        using _Cr = common_type_t<_Rep, _Rep2>;
        using _Cd = duration<_Cr, _Period>;
        return _Cd(_Cd(__d).count() * static_cast<_Cr>(__s));
    }

    template <class _Rep2, enable_if_t<is_convertible_v<const _Rep2&, common_type_t<_Rep, _Rep2>>, int> = 0>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr duration<common_type_t<_Rep, _Rep2>, _Period> operator*(
        const _Rep2& __s, const duration& __d)
    {
        using _Cr = common_type_t<_Rep, _Rep2>;
        using _Cd = duration<_Cr, _Period>;
        return _Cd(_Cd(__d).count() * static_cast<_Cr>(__s));
    }

    template <class _Rep2,
        enable_if_t<!__is_asc_std_duration_v<_Rep2> && is_convertible_v<const _Rep2&, common_type_t<_Rep, _Rep2>>,
            int> = 0>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr duration<common_type_t<_Rep, _Rep2>, _Period> operator/(
        const duration& __d, const _Rep2& __s)
    {
        using _Cr = common_type_t<_Rep, _Rep2>;
        using _Cd = duration<_Cr, _Period>;
        return _Cd(_Cd(__d).count() / __safe_divisor(static_cast<_Cr>(__s)));
    }

    template <class _Rep2, class _Period2>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr common_type_t<_Rep, _Rep2> operator/(
        const duration& __lhs, const duration<_Rep2, _Period2>& __rhs)
    {
        using _Ct = common_type_t<duration, duration<_Rep2, _Period2>>;
        return _Ct(__lhs).count() / __safe_divisor(_Ct(__rhs).count());
    }

    template <class _Rep2,
        enable_if_t<!__is_asc_std_duration_v<_Rep2> && is_convertible_v<const _Rep2&, common_type_t<_Rep, _Rep2>>,
            int> = 0>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr duration<common_type_t<_Rep, _Rep2>, _Period> operator%(
        const duration& __d, const _Rep2& __s)
    {
        using _Cr = common_type_t<_Rep, _Rep2>;
        using _Cd = duration<_Cr, _Period>;
        return _Cd(_Cd(__d).count() % __safe_divisor(static_cast<_Cr>(__s)));
    }

    template <class _Rep2, class _Period2>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API friend constexpr common_type_t<duration, duration<_Rep2, _Period2>>
    operator%(const duration& __lhs, const duration<_Rep2, _Period2>& __rhs)
    {
        using _Cr = common_type_t<_Rep, _Rep2>;
        using _Cd = common_type_t<duration, duration<_Rep2, _Period2>>;
        return _Cd(static_cast<_Cr>(_Cd(__lhs).count()) % __safe_divisor(static_cast<_Cr>(_Cd(__rhs).count())));
    }
};

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
