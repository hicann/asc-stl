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

#ifndef ASC_STL_TEST_CHRONO_DEVICE_CHECKS_H
#define ASC_STL_TEST_CHRONO_DEVICE_CHECKS_H

#include <asc/std/chrono>

namespace asc_stl_test_chrono {
CANN_ASC_STL_API int check(int seed = 7)
{
    namespace c = ::asc::std::chrono;
    const c::milliseconds tie{-500 * seed};
    if (c::floor<c::seconds>(tie).count() != -4 || c::ceil<c::seconds>(tie).count() != -3 ||
        c::round<c::seconds>(tie).count() != -4 || c::round<c::seconds>(tie + c::seconds(1)).count() != -2 ||
        c::duration_cast<c::seconds>(tie).count() != -3 || c::abs(tie).count() != 3500)
        return 1;
    c::time_point<c::system_clock, c::milliseconds> t(tie);
    if (c::time_point_cast<c::seconds>(t).time_since_epoch().count() != -3 ||
        c::floor<c::seconds>(t).time_since_epoch().count() != -4 ||
        c::ceil<c::seconds>(t).time_since_epoch().count() != -3 ||
        c::round<c::seconds>(t).time_since_epoch().count() != -4 || (c::seconds(3) + t - t).count() != 3000)
        return 2;
    t += c::seconds(5);
    if ((t++).time_since_epoch().count() != 1500 || (--t).time_since_epoch().count() != 1500)
        return 3;
    const c::hh_mm_ss<c::milliseconds> hms(c::milliseconds(-3723000 - seed));
    if (!hms.is_negative() || hms.hours().count() != 1 || hms.minutes().count() != 2 || hms.seconds().count() != 3 ||
        hms.subseconds().count() != seed || hms.to_duration().count() != -3723007 || hms.fractional_width != 3)
        return 4;
    for (int i = 0; i < 24; ++i) {
        c::hours hour(i);
        if (c::is_am(hour) != (i < 12) || c::is_pm(hour) != (i >= 12) ||
            c::make12(hour).count() != ((i % 12) ? i % 12 : 12) || c::make24(c::make12(hour), i >= 12) != hour)
            return 5;
    }
    const c::year y(1993 + seed);
    const c::year_month_day leap = y / c::February / 29;
    if (!leap.ok() || !y.is_leap() || (c::year(1900) / c::February / 29).ok() ||
        c::sys_days(leap).time_since_epoch().count() != 11016 || c::weekday(c::sys_days(leap)) != c::Tuesday ||
        c::year_month_day(c::local_days(leap)) != leap)
        return 6;
    const auto last_fri = y / c::February / c::Friday[c::last];
    const auto second_sun = y / c::February / c::Sunday[2];
    if (!second_sun.ok() || !last_fri.ok() || c::year_month_day(c::sys_days(second_sun)).day() != c::day(13) ||
        c::year_month_day(c::sys_days(last_fri)).day() != c::day(25))
        return 7;
    if ((c::December + c::months(1)) != c::January || (c::Sunday - c::days(1)) != c::Saturday ||
        (c::January - c::December) != c::months(1) || (c::Sunday - c::Saturday) != c::days(1))
        return 8;
    return 0;
}
}  // namespace asc_stl_test_chrono

#endif  // ASC_STL_TEST_CHRONO_DEVICE_CHECKS_H
