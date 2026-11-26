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

#include <asc/std/ranges>
#include "support/cxx17_access_semantics.h"

constexpr bool subrange_elements()
{
    int values[] = {1, 2};
    const asc::std::ranges::subrange view(values, values + 2);
    using R = asc::std::ranges::subrange<int*>;
    return asc::std::get<0>(view) == values && asc::std::get<1>(view) == values + 2 &&
        asc::std::get<0>(R(values, values + 1)) == values && asc::std::get<1>(R(values, values + 1)) == values + 1;
}
static_assert(subrange_elements());

int main()
{
    return asc_stl_cxx17_access_test::evaluate();
}
