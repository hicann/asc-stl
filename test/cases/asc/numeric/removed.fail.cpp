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

#include <asc/numeric>

#ifndef NUMERIC_REMOVED
#define NUMERIC_REMOVED 0
#endif

int main()
{
#if NUMERIC_REMOVED == 0
    auto result = asc::narrow<int>(1);
#elif NUMERIC_REMOVED == 1
    auto result = asc::narrow_cast<int>(1);
#elif NUMERIC_REMOVED == 2
    auto result = asc::saturating_add(1, 2);
#elif NUMERIC_REMOVED == 3
    auto result = asc::saturating_sub(1, 2);
#elif NUMERIC_REMOVED == 4
    auto result = asc::saturating_mul(1, 2);
#elif NUMERIC_REMOVED == 5
    auto result = asc::saturating_div(1, 2);
#elif NUMERIC_REMOVED == 6
    auto result = asc::saturating_overflow_cast<int>(1);
#elif NUMERIC_REMOVED == 7
    auto result = asc::overflow_result<int>{};
#else
    auto result = asc::add_overflow(1, 2).overflow;
#endif
    (void)result;
}
