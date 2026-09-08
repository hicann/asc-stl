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

#include <asc/hierarchy>
#include <asc/std/__chrono/duration.h>
#include <asc/std/tuple>

#include "core_consumers.h"

int asc_stl_b016_consumer_b()
{
    constexpr auto launch = asc::get_launch_dimensions(asc::make_hierarchy(asc::grid_dims<4>(), asc::block_dims<16>()));
    static_assert(launch.grid == asc::extent3d{4, 1, 1});
    static_assert(
        asc::std::chrono::floor<asc::std::chrono::seconds>(asc::std::chrono::milliseconds(1999)).count() == 1);
    const asc::std::tuple<int> value(7);
    return asc::std::get<0>(value) == 7 ? 0 : 1;
}
