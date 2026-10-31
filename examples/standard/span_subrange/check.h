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

#ifndef ASC_STL_EXAMPLES_SPAN_SUBRANGE_CHECK_H
#define ASC_STL_EXAMPLES_SPAN_SUBRANGE_CHECK_H

#include <cstdio>

#include "example_types.h"

namespace example {

inline Input make_input()
{
    return {{10, 20, 30, 40}};
}

inline bool report(const Result& result)
{
    std::printf("buffer=%d,%d,%d,%d slice_size=%u aliases=%u empty_size=%u\n", result.values[0], result.values[1],
        result.values[2], result.values[3], result.size, result.aliases, result.empty_size);
    return result.values[0] == 10 && result.values[1] == 21 && result.values[2] == 31 && result.values[3] == 40 &&
        result.size == 2 && result.aliases == 1 && result.empty_size == 0;
}

}  // namespace example

#endif  // ASC_STL_EXAMPLES_SPAN_SUBRANGE_CHECK_H
