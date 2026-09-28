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

#include <asc/std/map>

#include "../../../../support/b028_allocator.h"
CANN_ASC_STL_HOST_SIMT_API void test_excluded_surface()
{
    unsigned char storage[512]{};
    asc_stl_b028_test::arena_state state{storage, sizeof(storage), 0, 0, 0};
    using pair_type = asc::std::__arena_pair<const int, int>;
    using allocator_type = asc_stl_b028_test::arena_allocator<pair_type>;
    using map_type =
        asc::std::map<int, int, asc_stl_b028_test::less_int, allocator_type>;  // NOLINT(build/include_what_you_use)
    map_type values{asc_stl_b028_test::arena_allocator<pair_type>(&state)};
    values.erase(1);
}
