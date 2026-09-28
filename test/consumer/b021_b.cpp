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

#include <asc/std/__algorithm/binary_search.h>
#include <asc/std/__algorithm/set_union.h>

int asc_stl_b021_consumer_b()
{
    int values[] = {1, 2, 4};
    int other[] = {2, 3};
    int output[5] = {};
    const auto end = asc::std::set_union(values, values + 3, other, other + 2, output);
    return asc::std::binary_search(values, values + 3, 2) && end == output + 4 ? 0 : 1;
}
