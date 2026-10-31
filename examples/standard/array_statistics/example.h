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

#ifndef ASC_STL_EXAMPLES_ARRAY_STATISTICS_H
#define ASC_STL_EXAMPLES_ARRAY_STATISTICS_H

#include <asc/std/algorithm>
#include <asc/std/array>
#include <asc/std/numeric>

#include "example_types.h"

namespace example {

CANN_ASC_STL_API Result evaluate(const Input& input)
{
    const asc::std::array<int, 4> values{input.values[0], input.values[1], input.values[2], input.values[3]};
    const auto bounds = asc::std::minmax_element(values.begin(), values.end());
    const int sum = asc::std::accumulate(values.begin(), values.end(), 0);
    return {*bounds.first, *bounds.second, sum};
}

}  // namespace example

#endif  // ASC_STL_EXAMPLES_ARRAY_STATISTICS_H
