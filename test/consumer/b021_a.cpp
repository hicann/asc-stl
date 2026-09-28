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

#include <asc/memory_resource>
#include <asc/std/ctime>
#include <asc/std/__chrono/year_month_day.h>

int asc_stl_b021_consumer_a()
{
    constexpr auto properties = asc::device_memory_resource::properties();
    constexpr asc::std::chrono::year_month_day date{
        asc::std::chrono::year{2024}, asc::std::chrono::February, asc::std::chrono::day{29}};
    static_assert(properties.device_accessible() && properties.maximum_alignment() == 32);
    static_assert(date.ok());
    return asc::std::difftime(9, 4) == 5.0 ? 0 : 1;
}
