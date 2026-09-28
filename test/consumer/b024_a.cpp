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

#include <asc/pipeline>
#include <asc/std/__chrono/year_month_weekday.h>
#include <asc/std/__inplace_vector/inplace_vector.h>
#include <asc/std/__random/linear_congruential_engine.h>

int asc_stl_b024_consumer_a()
{
    asc::std::minstd_rand0 engine;
    const bool deterministic = engine() == 16807u && engine() == 282475249u;
    asc::std::inplace_vector<int, 3> values;
    const auto inserted = values.try_push_back(4);
    const asc::std::chrono::year_month_weekday first_monday(
        asc::std::chrono::year(2026), asc::std::chrono::January, asc::std::chrono::Monday[1]);
    // asc/pipeline itself is D-SIMD-only; the installed consumer verifies the
    // public entry parses on Host while its coordinator surface stays absent.
    return deterministic && inserted.has_value() && *inserted == 4 && first_monday.ok() ? 0 : 1;
}
