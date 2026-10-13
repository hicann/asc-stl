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

#ifndef ASC_STL_TEST_MDSPAN_SLICE_REGRESSION_H
#define ASC_STL_TEST_MDSPAN_SLICE_REGRESSION_H

#include <asc/std/mdspan>
#include <asc/std/utility>

namespace asc_stl_mdspan_slice_test {

CANN_ASC_STL_API bool evaluate()
{
    using extents_type = asc::std::extents<int, 2, 3>;
    int values[6] = {1, 2, 3, 4, 5, 6};
    asc::std::mdspan<int, extents_type> view(values);
    const auto row = asc::std::submdspan(view, 1, asc::std::full_extent);
    const auto column = asc::std::submdspan(view, asc::std::full_extent, 1);
    const auto range = asc::std::submdspan(view, asc::std::full_extent, asc::std::pair<int, int>{1, 3});
    const auto all = asc::std::submdspan(view, asc::std::full_extent, asc::std::full_extent);
    const auto element = asc::std::submdspan(view, 1, 2);
    const auto stepped =
        asc::std::submdspan(view, asc::std::full_extent, asc::std::strided_slice<int, int, int>{0, 3, 2});
    const auto empty = asc::std::submdspan_mapping(view.mapping(), 0, asc::std::pair<int, int>{3, 3});
    asc::std::mdspan<int, extents_type, asc::std::layout_left> left_view(values);
    const auto left_column = asc::std::submdspan(left_view, asc::std::full_extent, 1);
    const auto left_row = asc::std::submdspan(left_view, 1, asc::std::full_extent);
    return row.extent(0) == 3 && row(0) == 4 && row(2) == 6 && column.extent(0) == 2 && column(0) == 2 &&
        column(1) == 5 && range.extent(0) == 2 && range.extent(1) == 2 && range(0, 0) == 2 && range(1, 1) == 6 &&
        all(1, 2) == 6 && element() == 6 && column.mapping() == column.mapping() && stepped.extent(1) == 2 &&
        stepped(1, 1) == 6 && empty.mapping.extents().extent(0) == 0 && empty.offset == 6 && left_column(0) == 3 &&
        left_column(1) == 4 && left_row(0) == 2 && left_row(2) == 6;
}

}  // namespace asc_stl_mdspan_slice_test

#endif  // ASC_STL_TEST_MDSPAN_SLICE_REGRESSION_H
