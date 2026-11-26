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

#ifndef ASC_STL_TEST_STACK_DEVICE_CHECKS_H
#define ASC_STL_TEST_STACK_DEVICE_CHECKS_H

#include <asc/std/stack>
#include "../../../../support/fixed_sequence.h"

namespace asc_stl_test_stack {
CANN_ASC_STL_API int check(int seed = 7)
{
    using sequence = asc_stl_test::fixed_sequence<int, 8>;
    using adaptor = asc::std::stack<int, sequence>;
    sequence input;
    input.push_back(seed - 2);
    input.push_back(2);
    adaptor values(input);
    adaptor spare;
    values.swap(spare);
    if (!values.empty() || spare.size() != 2 || spare.top() != 2)
        return 1;
    spare.pop();
    if (spare.top() != seed - 2)
        return 2;

    return 0;
}
}  // namespace asc_stl_test_stack

#endif  // ASC_STL_TEST_STACK_DEVICE_CHECKS_H
