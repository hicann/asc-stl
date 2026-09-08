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

int asc_stl_b016_consumer_a()
{
    constexpr auto dimensions = asc::make_hierarchy(asc::grid_dims<2, 3>(), asc::block_dims<8, 4>());
    static_assert(dimensions.count(asc::grid) == 6);
    static_assert(dimensions.count(asc::block) == 32);
    constexpr asc::std::chrono::seconds second(1);
    static_assert(second == asc::std::chrono::milliseconds(1000));
    const auto values = asc::std::make_tuple(2, 3);
    return asc::std::get<0>(values) + asc::std::get<1>(values) == 5 && asc_stl_b016_consumer_b() == 0 ? 0 : 1;
}
