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

#ifndef ASC_STL_EXAMPLES_MDSPAN_MATRIX_CHECK_H
#define ASC_STL_EXAMPLES_MDSPAN_MATRIX_CHECK_H

#include <cstdio>

#include "example_types.h"

namespace example {

inline Input make_input()
{
    return {{1, 2, 3, 4, 5, 6}};
}

inline bool report(const Result& result)
{
    std::printf("row_major_sums=%d,%d column_major_sums=%d,%d\n", result.row_sums[0], result.row_sums[1],
        result.column_sums[0], result.column_sums[1]);
    std::printf("shared_storage=%d column_view=%d\n", result.storage_value, result.column_value);
    return result.row_sums[0] == 6 && result.row_sums[1] == 15 && result.column_sums[0] == 9 &&
        result.column_sums[1] == 12 && result.storage_value == 20 && result.column_value == 20;
}

}  // namespace example

#endif  // ASC_STL_EXAMPLES_MDSPAN_MATRIX_CHECK_H
