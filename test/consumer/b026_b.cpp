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
#include <asc/cmath>
#include <asc/std/bit>
#include <asc/work_queue>

int asc_stl_b026_consumer_b()
{
    // The same inline entities are defined in both translation units; the
    // ODR link check relies on the vocabulary staying constexpr/inline.
    static_assert(asc::floor_div(-7, 3) == -3);
    static_assert((asc::std::bit_width(255u) - 1) == 7);
    constexpr asc::work_chunk<unsigned long long> wide{0, 1ull << 32};
    static_assert(wide.size() == 1ull << 32);
    double sine = 1.0;
    double cosine = 1.0;
    asc::sincos(3.141592653589793 / 2.0, &sine, &cosine);
    return sine > 0.999 && cosine < 0.001 ? 0 : 1;
}
