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

#include <chrono>
#include <cstdio>
#include <type_traits>

#include "device_checks.h"

namespace c = asc::std::chrono;
using asc::std::literals::chrono_literals::operator""h;
using asc::std::literals::chrono_literals::operator""min;
using asc::std::literals::chrono_literals::operator""s;
using asc::std::literals::chrono_literals::operator""ms;
using asc::std::literals::chrono_literals::operator""us;
using asc::std::literals::chrono_literals::operator""ns;
using asc::std::literals::chrono_literals::operator""d;
using asc::std::literals::chrono_literals::operator""y;

// The duration and calendar literals are also available directly in chrono.
static_assert(c::operator""h(2ULL).count() == 2 &&
    c::operator""min(3ULL).count() == 3 &&  // NOLINT(build/include_what_you_use)
    c::operator""s(4ULL).count() == 4 && c::operator""ms(5ULL).count() == 5 && c::operator""us(6ULL).count() == 6 &&
    c::operator""ns(7ULL).count() == 7 && c::operator""d(12ULL) == c::day(12) &&
    c::operator""y(2004ULL) == c::year(2004));

using thirds = c::duration<short, asc::std::ratio<1, 3>>;
using halves = c::duration<long, asc::std::ratio<1, 2>>;
using sixths = c::duration<long, asc::std::ratio<1, 6>>;
using combined_duration = asc::std::common_type<thirds, halves>::type;
using combined_time = asc::std::common_type<c::sys_time<thirds>, c::sys_time<halves>>::type;
static_assert(std::is_same_v<combined_duration, sixths> && std::is_same_v<combined_time, c::sys_time<sixths>>);
static_assert(c::January == c::month(1) && c::February == c::month(2) && c::March == c::month(3) &&
    c::April == c::month(4) && c::May == c::month(5) && c::June == c::month(6) && c::July == c::month(7) &&
    c::August == c::month(8) && c::September == c::month(9) && c::October == c::month(10) &&
    c::November == c::month(11) && c::December == c::month(12));
static_assert(c::Sunday.c_encoding() == 0 && c::Monday.c_encoding() == 1 && c::Tuesday.c_encoding() == 2 &&
    c::Wednesday.c_encoding() == 3 && c::Thursday.c_encoding() == 4 && c::Friday.c_encoding() == 5 &&
    c::Saturday.c_encoding() == 6);

static_assert(1h == c::hours(1) && 2min == c::seconds(120) && 3s == 3000ms && 4ms == 4000us && 5us == 5000ns);
static_assert(1.5h == 90min && 0.5min == 30s && 0.5s == 500ms && 0.5ms == 500us && 0.5us == 500ns);
static_assert(0.5ns + 0.5ns == 1ns);
#if __cplusplus >= 202002L || !defined(__clang__)
static_assert(2d == c::day(2) && 2000y == c::year(2000));
#endif
static_assert(!c::month(0).ok() && !c::month(13).ok() && !c::day(0).ok() && !c::day(32).ok());
static_assert(!c::Monday[0].ok() && !c::Monday[6].ok());
static_assert((c::year(2000) / c::February / c::last).day() == c::day(29));
static_assert((c::year(1900) / c::February / c::last).day() == c::day(28));

template <class T>
bool ordered(T a, T b)
{
    return a == a && !(a != a) && a != b && a < b && a <= b && b > a && b >= a && a <= a && a >= a;
}

template <class T, class Step>
bool adjacent(T a, T b, Step step)
{
    if (!ordered(a, b) || a + step != b || step + a != b || b - step != a || b - a != step)
        return false;
    T v = a;
    if (v++ != a || v != b || v-- != b || v != a || ++v != b || --v != a)
        return false;
    v += step;
    if (v != b)
        return false;
    v -= step;
    return v == a;
}

template <class T>
bool shift_date(T value, T next_month, T next_year)
{
    const c::months m(1);
    const c::years y(1);
    if (value + m != next_month || m + value != next_month || next_month - m != value || value + y != next_year ||
        y + value != next_year || next_year - y != value)
        return false;
    auto copy = value;
    copy += m;
    if (copy != next_month)
        return false;
    copy -= m;
    copy += y;
    if (copy != next_year)
        return false;
    copy -= y;
    return copy == value;
}

template <class T>
bool date_spellings(T day)
{
    const auto m = c::June;
    const auto y = c::year(2007);
    const auto md = m / day;
    const auto date = (y / m) / day;
    return day / m == md && 6 / day == md && day / 6 == md && y / md == date && md / y == date && 2007 / md == date &&
        md / 2007 == date && md.ok() && md.month() == m && date.month() == m && date.year() == y;
}

bool calendar_operators()
{
    const c::hh_mm_ss<c::milliseconds> midnight{};
    if (midnight.to_duration() != c::milliseconds(0) || midnight.is_negative() ||
        c::weekday(c::local_days(c::days(0))) != c::Thursday)
        return false;
    if (c::day{}.ok() || c::month{}.ok() || c::month_day{}.ok() || c::year_month{}.ok() || c::month_weekday{}.ok() ||
        c::year_month_day{}.ok() || c::weekday_indexed{}.ok() || c::year_month_weekday{}.ok() ||
        static_cast<int>(c::year{}) != 0 || c::seconds{}.count() != 0 || c::weekday{}.c_encoding() != 0)
        return false;
    const c::weekday_indexed second(c::Tuesday, 2);
    const c::weekday_last last_tuesday(c::Tuesday);
    if (second != c::Tuesday[2] || last_tuesday != c::Tuesday[c::last] || !(last_tuesday == c::Tuesday[c::last]) ||
        c::June / second != second / 6 || c::June / last_tuesday != last_tuesday / 6 ||
        c::year_month_day(c::year(2000) / c::February / c::last_spec{}) != c::year(2000) / c::February / 29)
        return false;
    const c::year y(2007);
    const auto june = y / c::June, july = y / c::July, next = c::year(2008) / c::June;
    if (!adjacent(c::day(3), c::day(4), c::days(1)) || !adjacent(c::Monday, c::Tuesday, c::days(1)) ||
        !adjacent(c::June, c::July, c::months(1)) || !adjacent(y, c::year(2008), c::years(1)))
        return false;
    if (!shift_date(june, july, next) || !shift_date(june / 5, july / 5, next / 5) ||
        !shift_date(june / c::last, july / c::last, next / c::last) ||
        !shift_date(june / c::Tuesday[2], july / c::Tuesday[2], next / c::Tuesday[2]) ||
        !shift_date(june / c::Tuesday[c::last], july / c::Tuesday[c::last], next / c::Tuesday[c::last]))
        return false;
    if (!date_spellings(c::day(5)) || !date_spellings(c::last) || !date_spellings(c::Tuesday[2]) ||
        !date_spellings(c::Tuesday[c::last]))
        return false;
    if (!ordered(june, july) || !ordered(june / 5, july / 5) || !ordered(june / c::last, july / c::last) ||
        !ordered(c::June / 5, c::June / 6) || !ordered(c::June / c::last, c::July / c::last) || june != y / 6 ||
        june == july || july - june != c::months(1) || +y != y || -y != c::year(-2007))
        return false;
    return c::year::min() == c::year(-32767) && c::year::max() == c::year(32767);
}

bool duration_operators()
{
    c::seconds a(8), b(3);
    if (!ordered(b, a) || (+a).count() != 8 || (-a).count() != -8 || (a + b).count() != 11 || (a - b).count() != 5 ||
        (a * 3).count() != 24 || (3 * a).count() != 24 || (a / 2).count() != 4 || a / b != 2 || (a % 3).count() != 2 ||
        (a % b).count() != 2)
        return false;
    if (a++ != c::seconds(8) || ++a != c::seconds(10) || a-- != c::seconds(10) || --a != c::seconds(8))
        return false;
    a += b;
    a -= c::seconds(1);
    a *= 3;
    a /= 2;
    a %= 4;
    if (a.count() != 3)
        return false;
    a %= c::seconds(2);
    if (a.count() != 1 || c::seconds::min().count() != c::duration_values<c::seconds::rep>::min() ||
        c::seconds::max().count() != c::duration_values<c::seconds::rep>::max() || c::seconds::zero().count() != 0)
        return false;
    using point = c::time_point<c::system_clock, c::seconds>;
    point p(c::seconds(1));
    if (p++ != point(c::seconds(1)) || ++p != point(c::seconds(3)) || p-- != point(c::seconds(3)) ||
        --p != point(c::seconds(1)))
        return false;
    const c::time_point<c::system_clock, c::milliseconds> converted(p);
    if (converted.time_since_epoch().count() != 1000)
        return false;
    p += b;
    p -= a;
    return ordered(point{}, p) && p.time_since_epoch().count() == 3 && (p + b - a).time_since_epoch().count() == 5 &&
        point::min().time_since_epoch() == c::seconds::min() && point::max().time_since_epoch() == c::seconds::max();
}

bool gregorian_cycle()
{
    // 1600-01-01 is Saturday, 135140 days before 1970-01-01. Advance
    // one day at a time using Gregorian leap rules, independent of calendar conversion.
    int serial = -135140;
    unsigned dow = 6;
    const unsigned month_lengths[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for (int year = 1600; year < 2400; ++year) {
        const bool leap = year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
        if (c::year(year).is_leap() != leap)
            return false;
        for (unsigned month = 1; month <= 12; ++month) {
            const auto ym = c::year(year) / c::month(month);
            const unsigned length = month_lengths[month - 1] + (month == 2 && leap);
            if (static_cast<unsigned>((ym / c::last).day()) != length || (ym / c::day(length + 1)).ok())
                return false;
            for (unsigned day = 1; day <= length; ++day, ++serial, dow = (dow + 1) % 7) {
                auto date = ym / c::day(day);
                const c::sys_days expected{c::days(serial)};
                if (!date.ok() || c::sys_days(date) != expected || c::year_month_day(expected) != date ||
                    c::year_month_day(c::local_days(c::days(serial))) != date ||
                    c::weekday(expected).c_encoding() != dow || c::weekday(expected).iso_encoding() != (dow ? dow : 7))
                    return false;
                const auto indexed = ym / c::weekday(dow)[(day + 6) / 7];
                if (!indexed.ok() || c::sys_days(indexed) != expected || c::year_month_weekday(expected) != indexed)
                    return false;
                if (day + 7 > length && c::sys_days(ym / c::weekday(dow)[c::last]) != expected)
                    return false;
            }
        }
    }
    return true;
}

int main()
{
    if (const int error = asc_stl_test_chrono::check())
        return error;
    if (!calendar_operators() || !duration_operators())
        return 11;
    if (!gregorian_cycle()) {
        std::fprintf(stderr, "Gregorian date conversion mismatch\n");
        return 9;
    }
    for (int count = -10002; count <= 10002; ++count) {
        const auto a = c::milliseconds(count);
        const auto b = std::chrono::milliseconds(count);
        if (c::round<c::seconds>(a).count() != std::chrono::round<std::chrono::seconds>(b).count() ||
            c::floor<c::seconds>(a).count() != std::chrono::floor<std::chrono::seconds>(b).count() ||
            c::ceil<c::seconds>(a).count() != std::chrono::ceil<std::chrono::seconds>(b).count())
            return 10;
    }
    return 0;
}
