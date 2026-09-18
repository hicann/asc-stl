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

#include <asc/execution>
#include <asc/launch>
#include <asc/std/__compare/ordering.h>

int asc_stl_b019_consumer_b();

int asc_stl_b019_consumer_a()
{
    constexpr asc::simt_launch_config simt{{1, 1, 1}, {1, 1, 1}, 0};
    constexpr asc::aicore_launch_config aicore{1};
    static_assert(asc::std::strong_ordering::equal == asc::std::strong_ordering::equivalent);
    return simt.grid.x == 1 && simt.block.x == 1 && aicore.blocks == 1 && asc_stl_b019_consumer_b() == 0 ? 0 : 1;
}
