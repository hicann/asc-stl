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

#ifndef ASC_STL_EXAMPLES_TUPLE_TRAITS_CHECK_H
#define ASC_STL_EXAMPLES_TUPLE_TRAITS_CHECK_H

#include <cstdio>

#include "example_types.h"

namespace example {

inline Input make_input()
{
    return {{2000000000, 2000000000, -1}, {0.5F, 1.5F, 2.0F}};
}

inline bool report(const Result& result)
{
    std::printf("integer_sum=%lld integer_count=%u\n", result.integer_sum, result.integer_count);
    std::printf("real_sum=%.1f real_count=%u\n", result.real_sum, result.real_count);
    return result.integer_sum == 3999999999LL && result.integer_count == 3 && result.real_sum == 4.0 &&
        result.real_count == 3;
}

}  // namespace example

#endif  // ASC_STL_EXAMPLES_TUPLE_TRAITS_CHECK_H
