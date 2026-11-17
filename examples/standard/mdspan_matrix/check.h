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
    Input input{{1, 2, 3, 4, 5, 6}, {},
        {{0, 0, 3, 0, 4, 1}, {1, 1, 3, 0, 4, 2}, {0, 0, 2, 1, 3, 2}, {1, 0, 3, 2, 2, 5}, {1, 3, 3, 4, 0, 1},
            {1, 0, 3, 4, 0, 2}, {0, 1, 1, 0, 4, 1}, {1, 0, 3, 0, 1, 1}}};
    for (auto& value : input.padded)
        value = -1234;
    for (int batch = 0; batch < 2; ++batch) {
        for (int row = 0; row < 3; ++row) {
            for (int column = 0; column < 4; ++column)
                input.padded[batch * 24 + row * 7 + column] = batch * 100 + row * 10 + column;
        }
    }
    return input;
}

inline bool report(const Result& result)
{
    std::printf("row_major_sums=%d,%d column_major_sums=%d,%d\n", result.row_sums[0], result.row_sums[1],
        result.column_sums[0], result.column_sums[1]);
    std::printf("shared_storage=%d column_view=%d\n", result.storage_value, result.column_value);
    // Independent oracle: enumerate source coordinates, without views or slicing.
    const Input input = make_input();
    bool crops_passed = true;
    int checked = 0;
    for (int trial = 0; trial < kCropCaseCount; ++trial) {
        const auto& spec = input.crops[trial];
        int expected[kCropCapacity];
        for (auto& value : expected)
            value = -9999;
        int count = 0;
        int columns = 0;
        for (int column = spec.column_offset; column < spec.column_offset + spec.column_extent;
             column += spec.column_stride) {
            ++columns;
            for (int row = spec.row_first; row < spec.row_last; ++row)
                expected[count++] = input.padded[spec.batch * 24 + row * 7 + column];
        }
        for (int index = 0; index < kCropCapacity; ++index)
            crops_passed = result.cropped[trial * kCropCapacity + index] == expected[index] && crops_passed;
        crops_passed = result.crop_rows[trial] == spec.row_last - spec.row_first &&
            result.crop_columns[trial] == columns && crops_passed;
        checked += count;
    }
    std::printf("padded_crop_transpose_cases=%d elements=%d guards=%s\n", kCropCaseCount, checked,
        crops_passed ? "PASS" : "FAIL");
    return crops_passed && result.row_sums[0] == 6 && result.row_sums[1] == 15 && result.column_sums[0] == 9 &&
        result.column_sums[1] == 12 && result.storage_value == 20 && result.column_value == 20;
}

}  // namespace example

#endif  // ASC_STL_EXAMPLES_MDSPAN_MATRIX_CHECK_H
