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

#include <asc/std/ctime>
#include <ctime>
#include <limits>
#include <type_traits>
#include "device_checks.h"

static_assert(std::is_same_v<asc::std::clock_t, std::clock_t>);
static_assert(std::is_same_v<asc::std::time_t, std::time_t>);
static_assert(std::is_same_v<asc::std::size_t, std::size_t>);
static_assert(std::is_same_v<asc::std::timespec, std::timespec>);
static_assert(CLOCKS_PER_SEC > 0);

int main()
{
    using T = asc::std::time_t;
    constexpr T low = std::numeric_limits<T>::lowest();
    constexpr T high = std::numeric_limits<T>::max();
    static_assert(asc::std::difftime(high, high - 1) == 1 && asc::std::difftime(low, low + 1) == -1);
    if (asc::std::difftime(high, low) != std::difftime(high, low) ||
        asc::std::difftime(low, high) != std::difftime(low, high))
        return 1;
    asc::std::timespec value{};
    if (asc::std::timespec_get(&value, TIME_UTC) != TIME_UTC || value.tv_nsec < 0 || value.tv_nsec >= 1000000000L)
        return 2;
    T stored{};
    const T current = asc::std::time(&stored);
    return asc_stl_test_ctime::check() || current != stored || current == static_cast<T>(-1) ||
        asc::std::clock() == static_cast<asc::std::clock_t>(-1);
}
