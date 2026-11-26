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

#ifndef ASC_STL_TEST_MDSPAN_DEVICE_CHECKS_H
#define ASC_STL_TEST_MDSPAN_DEVICE_CHECKS_H

#include <asc/std/mdspan>

#include "layout_checks.h"

namespace asc_stl_test_mdspan {
CANN_ASC_STL_API int check(int seed = 7)
{
    if (int result = check_layout(seed))
        return 20 + result;
    using shape = asc::std::dextents<int, 2>;
    int storage[32]{};
    for (int rows = 0; rows <= 3; ++rows) {
        for (int cols = 0; cols <= 4; ++cols) {
            shape ext(rows, cols);
            asc::std::mdspan<int, shape, asc::std::layout_left> left(storage, ext);
            asc::std::mdspan<int, shape> right(storage, rows, cols);
            asc::std::array<int, 2> strides{{7, 1}};
            asc::std::layout_stride::mapping<shape> mapping(ext, strides);
            asc::std::mdspan<int, shape, asc::std::layout_stride> padded(storage, mapping);
            if (right.rank() != 2 || right.rank_dynamic() != 2 || right.extents() != ext ||
                right.size() != static_cast<unsigned>(rows * cols) || right.empty() != (rows * cols == 0) ||
                !left.is_unique() || !right.is_exhaustive() || !padded.is_strided() || padded.stride(0) != 7 ||
                padded.mapping().required_span_size() != (rows && cols ? (rows - 1) * 7 + cols : 0))
                return 1;
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    asc::std::array<int, 2> indices{{i, j}};
                    asc::std::span<int, 2> span(indices);
                    if (&left(i, j) != storage + j * rows + i || &right[indices] != storage + i * cols + j ||
                        &padded[span] != storage + i * 7 + j ||
                        &padded.accessor().access(padded.data_handle(), i * 7 + j) != &padded(i, j))
                        return 2;
                }
            }
            if (rows && cols) {
                auto column = asc::std::submdspan(padded, asc::std::full_extent, cols - 1);
                column(rows - 1) = seed + 12;
                if (storage[(rows - 1) * 7 + cols - 1] != 19 || column.extent(0) != rows)
                    return 3;
            }
        }
    }
    asc::std::mdspan<int, asc::std::extents<int>> scalar(storage);
    return scalar.size() == 1 && !scalar.empty() && &scalar() == storage ? 0 : 4;
}
}  // namespace asc_stl_test_mdspan

#endif  // ASC_STL_TEST_MDSPAN_DEVICE_CHECKS_H
