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

#ifndef ASC_STL_TEST_REPEAT_PIECEWISE_SEMANTICS_H
#define ASC_STL_TEST_REPEAT_PIECEWISE_SEMANTICS_H

#include <asc/std/ranges>
#include <asc/std/tuple>

namespace asc_stl_repeat_piecewise_test {

CANN_ASC_STL_API int evaluate()
{
    using repeat_type = asc::std::ranges::repeat_view<int, int>;
    const repeat_type empty(asc::std::piecewise_construct, asc::std::tuple<int>(7), asc::std::tuple<int>(0));
    if (empty.size() != 0 || empty.begin() != empty.end()) {
        return 101;
    }
    const repeat_type values(asc::std::piecewise_construct, asc::std::tuple<int>(11), asc::std::tuple<int>(3));
    if (values.size() != 3) {
        return 102;
    }
    int count = 0;
    int total = 0;
    for (auto iterator = values.begin(); iterator != values.end(); ++iterator) {
        total += *iterator;
        ++count;
    }
    return count == 3 && total == 33 ? 0 : 103;
}

}  // namespace asc_stl_repeat_piecewise_test

#endif  // ASC_STL_TEST_REPEAT_PIECEWISE_SEMANTICS_H
