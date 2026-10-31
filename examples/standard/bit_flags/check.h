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

#ifndef ASC_STL_EXAMPLES_BIT_FLAGS_CHECK_H
#define ASC_STL_EXAMPLES_BIT_FLAGS_CHECK_H

#include <cstdio>

#include "example_types.h"

namespace example {

inline Input make_input()
{
    return {5U, 32U, 4U};
}

inline bool report(const Result& result)
{
    std::printf("enabled=%u final=%u active=%d width=%d single=%u zero_count=%d\n", result.enabled, result.final_flags,
        result.active, result.width, result.single, result.zero_count);
    return result.enabled == 37 && result.final_flags == 33 && result.active == 2 && result.width == 6 &&
        result.single == 1 && result.zero_count == 0;
}

}  // namespace example

#endif  // ASC_STL_EXAMPLES_BIT_FLAGS_CHECK_H
