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

#ifndef ASC_STL_EXAMPLES_MDSPAN_MATRIX_H
#define ASC_STL_EXAMPLES_MDSPAN_MATRIX_H

#include <asc/std/array>
#include <asc/std/mdspan>
#include <asc/std/span>
#include <asc/std/utility>

#include "example_types.h"

namespace example {

CANN_ASC_STL_API Result evaluate(const Input& input)
{
    asc::std::array<int, 6> storage{
        input.values[0], input.values[1], input.values[2], input.values[3], input.values[4], input.values[5]};
    using shape = asc::std::extents<asc::std::size_t, 2, 3>;
    asc::std::mdspan<int, shape, asc::std::layout_right> row_major(storage.data());
    asc::std::mdspan<int, shape, asc::std::layout_left> column_major(storage.data());
    Result result{};
    for (asc::std::size_t row = 0; row < 2; ++row) {
        for (asc::std::size_t column = 0; column < 3; ++column) {
            result.row_sums[row] += row_major(row, column);
            result.column_sums[row] += column_major(row, column);
        }
    }
    row_major(0, 1) = 20;
    result.storage_value = storage[1];
    result.column_value = column_major(1, 0);
    // The source has row and batch padding. Slicing preserves those strides.
    using batch_shape = asc::std::extents<int, 2, 3, 4>;
    const asc::std::array<int, 3> strides{24, 7, 1};
    const asc::std::layout_stride::mapping<batch_shape> mapping(batch_shape{}, strides);
    asc::std::mdspan<const int, batch_shape, asc::std::layout_stride> batches(input.padded, mapping);
    asc::std::span<int> all_outputs(result.cropped);
    for (int trial = 0; trial < kCropCaseCount; ++trial) {
        const auto& spec = input.crops[trial];
        auto crop = asc::std::submdspan(batches, spec.batch, asc::std::pair<int, int>{spec.row_first, spec.row_last},
            asc::std::strided_slice<int, int, int>{spec.column_offset, spec.column_extent, spec.column_stride});
        auto output_storage = all_outputs.subspan(trial * kCropCapacity, kCropCapacity);
        for (auto& value : output_storage)
            value = -9999;
        result.crop_rows[trial] = crop.extent(0);
        result.crop_columns[trial] = crop.extent(1);
        asc::std::mdspan<int, asc::std::dextents<int, 2>> transposed(
            output_storage.data(), crop.extent(1), crop.extent(0));
        for (int row = 0; row < crop.extent(0); ++row) {
            for (int column = 0; column < crop.extent(1); ++column)
                transposed(column, row) = crop(row, column);
        }
    }
    return result;
}

}  // namespace example

#endif  // ASC_STL_EXAMPLES_MDSPAN_MATRIX_H
