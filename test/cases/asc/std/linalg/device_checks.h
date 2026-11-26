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

#ifndef ASC_STL_TEST_LINALG_DEVICE_CHECKS_H
#define ASC_STL_TEST_LINALG_DEVICE_CHECKS_H

#include <asc/std/linalg>

namespace asc_stl_test_linalg {
CANN_ASC_STL_API int check(int seed = 7)
{
    namespace s = ::asc::std;
    namespace l = ::asc::std::linalg;
    using shape = s::extents<int, 2, 3>;
    using transposed_shape = s::extents<int, 3, 2>;
    using z = s::complex<float>;
    z cells[6];
    for (int i = 0; i < 6; ++i)
        cells[i] = z(static_cast<float>(seed + i), static_cast<float>(i - 2));
    s::mdspan<z, shape> matrix(cells, shape{});
    const auto transposed = l::conjugate_transposed(matrix);
    const auto restored = l::conjugate_transposed(transposed);
    const auto scaled = l::scaled(-2.0F, transposed);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            const int index = i * 3 + j;
            const z expected(static_cast<float>(seed + index), static_cast<float>(2 - index));
            if (transposed.mapping()(j, i) != index || transposed.accessor().access(cells, index) != expected ||
                scaled.accessor().access(cells, index) != z(-2 * expected.real(), -2 * expected.imag()) ||
                restored.accessor().access(cells, restored.mapping()(i, j)) != cells[index] ||
                scaled.accessor().offset(cells, index) != cells + index ||
                transposed.accessor().offset(cells, index) != cells + index)
                return 1;
        }
    }
    if (scaled.accessor().scaling_factor() != -2.0F ||
        scaled.accessor().nested_accessor().access(cells, 0) != z(7, 2) ||
        transposed.accessor().nested_accessor().access(cells, 0) != z(7, -2) || l::conj_if_needed(17) != 17 ||
        l::conj_if_needed(z(5, 3)) != z(5, -3))
        return 2;
    const s::layout_right::mapping<shape> original(shape{});
    using mapped = l::layout_transpose<s::layout_right>::mapping<transposed_shape>;
    const mapped mapping(original);
    if (mapping.extents().extent(0) != 3 || mapping.extents().extent(1) != 2 || mapping.stride(0) != 1 ||
        mapping.stride(1) != 3 || mapping.required_span_size() != 6 || mapping(2, 1) != 5 ||
        mapping.nested_mapping()(1, 2) != 5 || !mapping.is_unique() || !mapping.is_exhaustive() ||
        !mapping.is_strided() || !mapped::is_always_unique() || !mapped::is_always_exhaustive() ||
        !mapped::is_always_strided() || mapping != mapped(original))
        return 3;
    using dynamic = s::dextents<int, 2>;
    const dynamic empty(0, 3);
    const s::mdspan<z, dynamic> no_rows(cells, empty);
    const auto no_columns = l::transposed(no_rows);
    if (no_columns.extent(0) != 3 || no_columns.extent(1) != 0 || no_columns.size() != 0)
        return 4;
    const s::layout_right::mapping<dynamic> runtime_original(dynamic(2, 3));
    const l::layout_transpose<s::layout_right>::mapping<dynamic> runtime_mapping(runtime_original);
    if (!(runtime_mapping == mapping) || mapping != runtime_mapping)
        return 5;
    return 0;
}
}  // namespace asc_stl_test_linalg

#endif  // ASC_STL_TEST_LINALG_DEVICE_CHECKS_H
