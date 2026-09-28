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

#include <asc/algorithm>
#include <asc/std/__algorithm/remove.h>
#include <asc/std/__numeric/saturating_mul.h>

int asc_stl_b023_consumer_a()
{
    int values[] = {1, 2, 1, 3};
    int* end = asc::std::remove(values, values + 4, 1);
    return end == values + 2 && values[0] == 2 && values[1] == 3 &&
            asc::std::saturating_mul<int>(100000, 100000) == 2147483647 ?
        0 :
        1;
}
