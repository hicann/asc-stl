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

#include <asc/std/__numeric/saturating_add.h>
#include <asc/std/__numeric/saturating_sub.h>

#include <cassert>
#include <cstdint>
#include <limits>

int main()
{
    // saturating_add clamps at both ends without signed-overflow UB.
    assert(asc::std::saturating_add(1, 2) == 3);
    assert(asc::std::saturating_add(std::numeric_limits<int>::max(), 1) == std::numeric_limits<int>::max());
    assert(asc::std::saturating_add(std::numeric_limits<int>::max(), std::numeric_limits<int>::max()) ==
        std::numeric_limits<int>::max());
    assert(asc::std::saturating_add(std::numeric_limits<int>::min(), -1) == std::numeric_limits<int>::min());
    assert(asc::std::saturating_add(-1, 1) == 0);
    assert(asc::std::saturating_add(std::numeric_limits<std::int8_t>::max(), std::int8_t{1}) == std::int8_t{127});
    assert(asc::std::saturating_add(std::numeric_limits<std::int64_t>::max(), std::int64_t{1}) ==
        std::numeric_limits<std::int64_t>::max());
    assert(asc::std::saturating_add(std::numeric_limits<std::uint32_t>::max(), 1u) ==
        std::numeric_limits<std::uint32_t>::max());
    assert(asc::std::saturating_add(0u, 0u) == 0u);

    // saturating_sub clamps at both ends.
    assert(asc::std::saturating_sub(3, 1) == 2);
    assert(asc::std::saturating_sub(std::numeric_limits<int>::min(), 1) == std::numeric_limits<int>::min());
    assert(asc::std::saturating_sub(std::numeric_limits<int>::max(), -1) == std::numeric_limits<int>::max());
    assert(asc::std::saturating_sub(std::numeric_limits<std::int64_t>::min(), std::int64_t{1}) ==
        std::numeric_limits<std::int64_t>::min());
    assert(asc::std::saturating_sub(0u, 1u) == 0u);
    assert(asc::std::saturating_sub(7u, 3u) == 4u);
    assert(asc::std::saturating_sub(std::numeric_limits<std::int8_t>::min(), std::int8_t{1}) == std::int8_t{-128});

    static_assert(asc::std::saturating_add(std::numeric_limits<int>::max(), 1) == std::numeric_limits<int>::max());
    static_assert(asc::std::saturating_sub(std::numeric_limits<int>::min(), 1) == std::numeric_limits<int>::min());
    return 0;
}
