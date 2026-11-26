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

#ifndef ASC_STL_TEST_CHRONO_CALENDAR_CONVERSIONS_H
#define ASC_STL_TEST_CHRONO_CALENDAR_CONVERSIONS_H

#include <asc/std/chrono>

namespace asc_stl_chrono_conversions {
namespace c = asc::std::chrono;

template <class Calendar>
CANN_ASC_STL_API constexpr bool at_epoch_offset(const Calendar& date, long long expected)
{
    const c::sys_days system_day = date;
    const auto local_day = static_cast<c::local_days>(date);
    return system_day.time_since_epoch().count() == expected && local_day.time_since_epoch().count() == expected;
}

CANN_ASC_STL_API constexpr bool calendar_dates()
{
    const c::year epoch(1970);
    const auto january = epoch / c::January;
    return static_cast<int>(c::year(-17)) == -17 && static_cast<unsigned>(c::day(31)) == 31 &&
        static_cast<unsigned>(c::December) == 12 && at_epoch_offset(c::year(1969) / c::December / 31, -1) &&
        at_epoch_offset(epoch / c::February / c::last, 58) && at_epoch_offset(january / c::Thursday[1], 0) &&
        at_epoch_offset(january / c::Thursday[c::last], 28);
}

CANN_ASC_STL_API constexpr bool clock_precision(int milliseconds)
{
    using clock = c::hh_mm_ss<c::milliseconds>;
    const clock value{c::milliseconds(milliseconds)};
    return static_cast<clock::precision>(value).count() == milliseconds;
}

static_assert(calendar_dates());
static_assert(clock_precision(-3723004) && clock_precision(0) && clock_precision(3723004));

}  // namespace asc_stl_chrono_conversions
#endif  // ASC_STL_TEST_CHRONO_CALENDAR_CONVERSIONS_H
