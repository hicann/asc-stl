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

#ifndef ASC_STL_TEST_CALENDAR_SEMANTICS_H
#define ASC_STL_TEST_CALENDAR_SEMANTICS_H

#include <asc/std/chrono>
#include <asc/std/limits>
#include <asc/std/type_traits>

namespace asc_stl_calendar_test {

namespace ch = asc::std::chrono;

static_assert(static_cast<unsigned>(ch::January) == 1 && static_cast<unsigned>(ch::February) == 2 &&
    static_cast<unsigned>(ch::March) == 3 && static_cast<unsigned>(ch::April) == 4 &&
    static_cast<unsigned>(ch::May) == 5 && static_cast<unsigned>(ch::June) == 6 &&
    static_cast<unsigned>(ch::July) == 7 && static_cast<unsigned>(ch::August) == 8 &&
    static_cast<unsigned>(ch::September) == 9 && static_cast<unsigned>(ch::October) == 10 &&
    static_cast<unsigned>(ch::November) == 11 && static_cast<unsigned>(ch::December) == 12);
static_assert(ch::nanoseconds::period::den == 1000000000 && ch::microseconds::period::den == 1000000);
static_assert(ch::days::period::num == 86400 && ch::weeks::period::num == 604800);
static_assert(ch::months::period::num == 2629746 && ch::years::period::num == 31556952);
static_assert(asc::std::is_same_v<ch::sys_seconds, ch::sys_time<ch::seconds>>);
static_assert(asc::std::is_same_v<ch::local_seconds, ch::local_time<ch::seconds>>);
static_assert(asc::std::is_same_v<ch::local_time<ch::seconds>::clock, ch::local_t>);
static_assert(asc::std::is_same_v<ch::sys_seconds::clock, ch::system_clock>);
static_assert(asc::std::is_same_v<ch::system_clock::rep, ch::system_clock::duration::rep>);
static_assert(asc::std::is_same_v<ch::system_clock::period, ch::system_clock::duration::period>);
static_assert(!ch::system_clock::is_steady);
static_assert(ch::treat_as_floating_point<double>::value && !ch::treat_as_floating_point<int>::value);
static_assert(asc::std::is_trivially_destructible_v<ch::month_day>);
static_assert(asc::std::is_trivially_destructible_v<ch::month_day_last>);
static_assert(asc::std::is_trivially_destructible_v<ch::month_weekday>);
static_assert(asc::std::is_trivially_destructible_v<ch::month_weekday_last>);
static_assert(asc::std::is_trivially_destructible_v<ch::weekday>);
static_assert(asc::std::is_trivially_destructible_v<ch::weekday_indexed>);
static_assert(asc::std::is_trivially_destructible_v<ch::weekday_last>);
static_assert(asc::std::is_trivially_destructible_v<ch::year_month>);
static_assert(asc::std::is_trivially_destructible_v<ch::year_month_day_last>);
static_assert(asc::std::is_trivially_destructible_v<ch::year_month_weekday>);
static_assert(asc::std::is_trivially_destructible_v<ch::year_month_weekday_last>);

CANN_ASC_STL_API constexpr bool check_durations(int delta = 0)
{
    using duration = ch::duration<int, asc::std::milli>;
    using values = ch::duration_values<int>;
    static_assert(
        asc::std::is_same_v<duration::rep, int> && duration::period::num == 1 && duration::period::den == 1000);
    if (duration::min().count() != asc::std::numeric_limits<int>::min() || values::min() != duration::min().count() ||
        duration::max().count() != asc::std::numeric_limits<int>::max() || values::max() != duration::max().count() ||
        duration::zero().count() != 0 || values::zero() != 0) {
        return false;
    }
    const int inputs[] = {-15 + delta, -1, 0, 1, 15 + delta};
    for (int input : inputs) {
        duration value{input};
        if ((+value).count() != input || (-value).count() != -input ||
            ch::abs(value).count() != (input < 0 ? -input : input)) {
            return false;
        }
        if ((value++).count() != input || value.count() != input + 1 || (--value).count() != input) {
            return false;
        }
        if ((++value).count() != input + 1 || (value--).count() != input + 1 || value.count() != input) {
            return false;
        }
        value += duration{11};
        value -= duration{5};
        value *= 3;
        value /= 2;
        const int expected = (input + 6) * 3 / 2;
        if (value.count() != expected) {
            return false;
        }
        auto scalar = value;
        scalar %= 4;
        value %= duration{5};
        if (scalar.count() != expected % 4 || value.count() != expected % 5) {
            return false;
        }
    }
    return true;
}

CANN_ASC_STL_API constexpr bool check_time_points(int delta = 0)
{
    using point = ch::time_point<ch::system_clock, ch::milliseconds>;
    static_assert(asc::std::is_same_v<point::duration, ch::milliseconds>);
    static_assert(asc::std::is_same_v<point::rep, ch::milliseconds::rep>);
    static_assert(asc::std::is_same_v<point::period, ch::milliseconds::period>);
    if (point::min().time_since_epoch() != point::duration::min() ||
        point::max().time_since_epoch() != point::duration::max()) {
        return false;
    }
    const int inputs[] = {-1999 + delta, -1000, 0, 1000, 1999 + delta};
    for (int input : inputs) {
        point moment{ch::milliseconds{input}};
        if (ch::time_point_cast<ch::seconds>(moment).time_since_epoch().count() != input / 1000) {
            return false;
        }
        if ((moment++).time_since_epoch().count() != input || (--moment).time_since_epoch().count() != input) {
            return false;
        }
        if ((++moment).time_since_epoch().count() != input + 1 || (moment--).time_since_epoch().count() != input + 1) {
            return false;
        }
        moment += ch::milliseconds{3};
        moment -= ch::milliseconds{5};
        if (moment.time_since_epoch().count() != input - 2) {
            return false;
        }
    }
    using clock_parts = ch::hh_mm_ss<ch::milliseconds>;
    static_assert(clock_parts::fractional_width == 3);
    static_assert(asc::std::is_same_v<clock_parts::precision::period, ch::milliseconds::period>);
    const clock_parts negative{ch::milliseconds{-3723004}};
    const clock_parts zero{ch::milliseconds{0}};
    return negative.is_negative() && negative.hours().count() == 1 && negative.minutes().count() == 2 &&
        negative.seconds().count() == 3 && negative.subseconds().count() == 4 &&
        negative.to_duration().count() == -3723004 && !zero.is_negative() && zero.to_duration().count() == 0;
}

CANN_ASC_STL_API constexpr bool check_calendar_arithmetic(unsigned phase = 0)
{
    ch::day first{1};
    if (static_cast<unsigned>(first--) != 1 || first.ok()) {
        return false;
    }
    if (static_cast<unsigned>(++first) != 1 || !first.ok()) {
        return false;
    }
    first += ch::days{30};
    if (static_cast<unsigned>(first++) != 31 || first.ok()) {
        return false;
    }
    first -= ch::days{3};
    if (first != ch::day{29}) {
        return false;
    }
    for (unsigned index = 0; index < 12; ++index) {
        const unsigned month = (index + phase) % 12 + 1;
        ch::month current{month};
        const ch::month next{month % 12 + 1};
        const ch::month previous{(month + 10) % 12 + 1};
        if (current++ != ch::month{month} || current != next || --current != ch::month{month}) {
            return false;
        }
        if (--current != previous || ++current != ch::month{month}) {
            return false;
        }
        current += ch::months{25};
        if (current != next) {
            return false;
        }
        current -= ch::months{26};
        if (current != previous) {
            return false;
        }
    }
    auto year = ch::year{2000};
    if (+year != year || -year != ch::year{-2000} || year++ != ch::year{2000} || --year != ch::year{2000}) {
        return false;
    }
    year += ch::years{100};
    if (year != ch::year{2100} || year.is_leap() || static_cast<int>(ch::year::min()) != -32767 ||
        static_cast<int>(ch::year::max()) != 32767) {
        return false;
    }
    ch::year_month end_of_year{ch::year{1999}, ch::December};
    end_of_year += ch::months{2};
    if (!end_of_year.ok() || end_of_year.year() != ch::year{2000} || end_of_year.month() != ch::February) {
        return false;
    }
    end_of_year -= ch::months{2};
    if (end_of_year.year() != ch::year{1999} || end_of_year.month() != ch::December) {
        return false;
    }
    const ch::month_day leap{ch::February, ch::day{29}};
    const ch::month_day impossible{ch::February, ch::day{30}};
    const ch::month_day_last final_day{ch::February};
    const ch::last_spec last_tag{};
    const auto flagged = ch::February / last_tag;
    return leap.ok() && leap.day() == ch::day{29} && leap.month() == ch::February && !impossible.ok() &&
        final_day.ok() && final_day.month() == ch::February && flagged.month() == ch::February &&
        !ch::month_day_last{ch::month{0}}.ok();
}

CANN_ASC_STL_API constexpr bool check_weekday_arithmetic(unsigned phase = 0)
{
    for (unsigned index = 0; index < 7; ++index) {
        const unsigned raw = (index + phase) % 7;
        ch::weekday day{raw};
        if (!day.ok() || day.c_encoding() != raw || day.iso_encoding() != (raw == 0 ? 7 : raw)) {
            return false;
        }
        const auto before = day++;
        if (before.c_encoding() != raw || day.c_encoding() != (raw + 1) % 7 || --day != before) {
            return false;
        }
        if (day-- != before || ++day != before) {
            return false;
        }
        day += ch::days{8};
        day -= ch::days{9};
        if (day.c_encoding() != (raw + 6) % 7) {
            return false;
        }
        day = before;
        const ch::weekday_indexed indexed{day, 2};
        const ch::weekday_last last{day};
        if (!indexed.ok() || indexed.index() != 2 || indexed.weekday() != before || !last.ok() ||
            last.weekday() != before || day[2].index() != 2 || day[ch::last].weekday() != before) {
            return false;
        }
    }
    const ch::month_weekday indexed{ch::January, ch::Thursday[1]};
    const ch::month_weekday_last last{ch::January, ch::Thursday[ch::last]};
    return ch::weekday{7} == ch::Sunday && !ch::weekday{8}.ok() && !ch::Thursday[0].ok() && !ch::Thursday[6].ok() &&
        indexed.ok() && indexed.month() == ch::January && indexed.weekday_indexed().weekday() == ch::Thursday &&
        !ch::month_weekday{ch::January, ch::Thursday[0]}.ok() && last.ok() && last.month() == ch::January &&
        last.weekday_last().weekday() == ch::Thursday &&
        !ch::month_weekday_last{ch::month{0}, ch::Thursday[ch::last]}.ok();
}

CANN_ASC_STL_API constexpr bool check_composite_dates()
{
    const auto first = ch::year_month_weekday{ch::year{1970}, ch::January, ch::Thursday[1]};
    if (!first.ok() || first.index() != 1 || first.month() != ch::January || first.weekday() != ch::Thursday ||
        first.weekday_indexed().index() != 1 || first.year() != ch::year{1970} ||
        static_cast<ch::sys_days>(first).time_since_epoch().count() != 0) {
        return false;
    }
    auto moved = first;
    moved += ch::months{1};
    if (moved.month() != ch::February || moved.index() != 1) {
        return false;
    }
    moved -= ch::months{1};
    if (static_cast<ch::sys_days>(moved).time_since_epoch().count() != 0) {
        return false;
    }
    moved = ch::year_month_weekday{ch::year{2021}, ch::February, ch::Monday[5]};
    if (moved.ok()) {
        return false;
    }

    const ch::year_month_weekday_last last{ch::year{1970}, ch::January, ch::Thursday[ch::last]};
    auto last_moved = last;
    last_moved += ch::months{1};
    if (last_moved.month() != ch::February || !last_moved.ok() || last_moved.weekday() != ch::Thursday ||
        last_moved.weekday_last().weekday() != ch::Thursday || last_moved.year() != ch::year{1970}) {
        return false;
    }
    last_moved -= ch::months{1};
    if (static_cast<ch::sys_days>(last_moved).time_since_epoch().count() != 28) {
        return false;
    }
    last_moved = last;
    if (static_cast<ch::sys_days>(last_moved).time_since_epoch().count() != 28) {
        return false;
    }

    ch::year_month_day day{ch::year{2000}, ch::February, ch::day{29}};
    day = ch::year{1969} / ch::December / ch::day{31};
    auto last_day = ch::year{2000} / ch::February / ch::last;
    last_day = ch::year{1900} / ch::February / ch::last;
    return static_cast<ch::sys_days>(day).time_since_epoch().count() == -1 && last_day.day() == ch::day{28};
}

static_assert(check_durations());
static_assert(check_time_points());
static_assert(check_calendar_arithmetic());
static_assert(check_weekday_arithmetic());
static_assert(check_composite_dates());

CANN_ASC_STL_API int evaluate(int input)
{
    if (!check_durations(input))
        return 1;
    if (!check_time_points(input))
        return 2;
    if (!check_calendar_arithmetic(static_cast<unsigned>(input)))
        return 3;
    if (!check_weekday_arithmetic(static_cast<unsigned>(input)))
        return 4;
    if (!check_composite_dates())
        return 5;

    const int offsets[] = {-146097, -1, 0, 11016};
    const int years[] = {1570, 1969, 1970, 2000};
    const unsigned months[] = {1, 12, 1, 2};
    const unsigned days[] = {1, 31, 1, 29};
    for (unsigned position = 0; position < 4; ++position) {
        const unsigned index = (position + static_cast<unsigned>(input)) % 4;
        const ch::sys_days point{ch::days{offsets[index]}};
        const ch::year_month_day date{point};
        if (!date.ok() || static_cast<int>(date.year()) != years[index] ||
            static_cast<unsigned>(date.month()) != months[index] || static_cast<unsigned>(date.day()) != days[index] ||
            static_cast<ch::sys_days>(date) != point ||
            static_cast<ch::local_days>(date).time_since_epoch().count() != offsets[index])
            return 6;
    }
    return 0;
}

}  // namespace asc_stl_calendar_test

#endif  // ASC_STL_TEST_CALENDAR_SEMANTICS_H
