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

#ifndef ASC_STL_EXAMPLES_MDSPAN_MATRIX_TYPES_H
#define ASC_STL_EXAMPLES_MDSPAN_MATRIX_TYPES_H

namespace example {
inline constexpr int kCropCaseCount = 8;
inline constexpr int kCropCapacity = 12;
struct Crop {
    int batch;
    int row_first;
    int row_last;
    int column_offset;
    int column_extent;
    int column_stride;
};
struct Input {
    int values[6];
    int padded[42];
    Crop crops[kCropCaseCount];
};
struct Result {
    int row_sums[2];
    int column_sums[2];
    int storage_value;
    int column_value;
    int cropped[kCropCaseCount * kCropCapacity];
    int crop_rows[kCropCaseCount];
    int crop_columns[kCropCaseCount];
};
}  // namespace example

#endif  // ASC_STL_EXAMPLES_MDSPAN_MATRIX_TYPES_H
