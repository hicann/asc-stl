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

#include <asc/std/array>
#include <asc/std/linalg>
#include <asc/std/mdspan>
#include <asc/std/span>
#include <asc/std/utility>

#include <iostream>

namespace {

namespace ast = asc::std;
using shape3 = ast::extents<int, 2, 3, ast::dynamic_extent>;
using index3 = ast::array<int, 3>;
using index2 = ast::array<int, 2>;
using interval = ast::pair<int, int>;  // NOLINT(build/include_what_you_use)

bool check_layouts()
{
    const shape3 shape(4);
    int backing[64]{};
    const ast::mdspan<int, shape3> right(backing, shape);
    const ast::mdspan<int, shape3, ast::layout_left> left(backing, shape);
    const ast::layout_stride::mapping<shape3> layout(shape, index3{23, 7, 1});
    const ast::mdspan<int, shape3, ast::layout_stride> padded(backing, layout);
    for (int i = 0; i < 64; ++i)
        backing[i] = -i - 1;
    if (right.size() != 24 || left.size() != 24 || padded.size() != 24 || padded.mapping().required_span_size() != 41 ||
        padded.is_exhaustive())
        return false;

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 4; ++k) {
                const index3 where{i, j, k};
                if (&right[where] != backing + 12 * i + 4 * j + k || &left[where] != backing + i + 2 * j + 6 * k ||
                    &padded[where] != backing + 23 * i + 7 * j + k)
                    return false;
            }
        }
    }

    const auto sliced = ast::submdspan(padded, ast::full_extent, 1, ast::strided_slice{0, 4, 2});
    if (sliced.rank() != 2 || sliced.data_handle() != backing + 7 || sliced.extent(0) != 2 || sliced.extent(1) != 2 ||
        sliced.stride(0) != 23 || sliced.stride(1) != 2 || sliced.mapping().required_span_size() != 26)
        return false;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j)
            sliced[index2{i, j}] = i * 10 + j;
    }
    for (int i = 0; i < 64; ++i) {
        int expected = -i - 1;
        for (int row = 0; row < 2; ++row) {
            for (int col = 0; col < 2; ++col) {
                if (i == 7 + 23 * row + 2 * col)
                    expected = row * 10 + col;
            }
        }
        if (backing[i] != expected)
            return false;
    }

    const auto empty = ast::submdspan(right, 0, interval{1, 1}, ast::full_extent);
    const ast::mdspan<int, shape3, ast::layout_left> zero(backing, shape3(0));
    const auto scalar = ast::submdspan(padded, 1, 2, 3);
    return empty.empty() && empty.size() == 0 && empty.mapping().required_span_size() == 0 && zero.empty() &&
        zero.mapping().required_span_size() == 0 && scalar.rank() == 0 && !scalar.empty() && scalar.size() == 1 &&
        scalar.mapping().required_span_size() == 1 && scalar.data_handle() == backing + 40;
}

bool check_view_composition()
{
    int backing[27]{};
    for (int i = 0; i < 27; ++i)
        backing[i] = i * 3 - 14;
    ast::span<int, 27> linear(backing);
    const auto middle = linear.subspan<2, 23>();
    const auto rest = middle.last(4);
    const auto bytes = ast::as_writable_bytes(middle);
    if (middle.data() != backing + 2 || rest.data() != backing + 21 || rest.size() != 4 ||
        bytes.size() != 23 * sizeof(int) || linear.first(0).data() != backing)
        return false;
    using shape = ast::extents<int, 3, 5>;
    using layout = ast::layout_stride::mapping<shape>;
    const ast::mdspan<int, shape, ast::layout_stride> matrix(middle.data(), layout(shape{}, index2{9, 1}));
    const auto transposed = ast::linalg::transposed(matrix);
    const auto scaled = ast::linalg::scaled(-2, transposed);
    if (transposed.extent(0) != 5 || transposed.extent(1) != 3 || scaled.extent(0) != 5 || scaled.extent(1) != 3)
        return false;
    for (int col = 0; col < 5; ++col) {
        for (int row = 0; row < 3; ++row) {
            const index2 coordinates{col, row};
            const int offset = 2 + 9 * row + col;
            if (&transposed[coordinates] != backing + offset || scaled[coordinates] != -2 * backing[offset])
                return false;
        }
    }
    transposed[index2{4, 2}] = 73;
    return backing[24] == 73 && scaled[index2{4, 2}] == -146 && backing[23] == 55 && backing[25] == 61;
}

}  // namespace

int main()
{
    if (!check_layouts() || !check_view_composition()) {
        std::cerr << "Layout, slice, or shared storage mismatch\n";
        return 1;
    }
    return 0;
}
