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

#ifndef ASC_STL_TEST_STANDARD_VIEW_SEMANTICS_H
#define ASC_STL_TEST_STANDARD_VIEW_SEMANTICS_H

#include <asc/std/array>
#include <asc/std/linalg>
#include <asc/std/mdspan>
#include <asc/std/ranges>
#include <asc/std/span>

namespace asc_stl_standard_view_test {

namespace ast = asc::std;
namespace rg = asc::std::ranges;

struct below {
    int limit;

    CANN_ASC_STL_API bool operator()(int value) const
    {
        return value < limit;
    }
};

struct twice {
    CANN_ASC_STL_API int operator()(int value) const
    {
        return value * 2;
    }
};

CANN_ASC_STL_API int evaluate_ranges(int seed)
{
    ast::array<int, 5> input{seed, seed + 1, seed + 2, seed + 3, seed + 4};
    rg::ref_view<decltype(input)> ref(input);
    if (ref.empty() || ref.size() != 5 || ref.data() != input.data() || &ref.base() != &input)
        return 1;
    const auto& constant = input;
    if (rg::cbegin(input) != constant.begin() || rg::cend(input) != constant.end() ||
        rg::cdata(input) != constant.data() || *rg::crbegin(input) != seed + 4 ||
        rg::crend(input) - rg::crbegin(input) != 5)
        return 2;
    const int counts[] = {0, 1, seed % 5, 5, 9};
    for (const int count : counts) {
        const int limited = count < 5 ? count : 5;
        rg::take_view<decltype(ref)> prefix(ref, count);
        rg::drop_view<decltype(ref)> suffix(ref, count);
        if (prefix.begin() != input.begin() || prefix.end() != input.begin() + limited ||
            suffix.begin() != input.begin() + limited || suffix.end() != input.end() ||
            prefix.size() != static_cast<unsigned>(limited) || suffix.size() != static_cast<unsigned>(5 - limited) ||
            prefix.base().data() != input.data() || suffix.base().data() != input.data())
            return 3;
    }
    for (int count = 0; count <= 5; ++count) {
        const below predicate{seed + count};
        rg::take_while_view<decltype(ref), below> taken(ref, predicate);
        rg::drop_while_view<decltype(ref), below> dropped(ref, predicate);
        if (rg::distance(taken.begin(), taken.end()) != count || dropped.begin() != input.begin() + count ||
            dropped.end() != input.end() || taken.base().data() != input.data() ||
            dropped.base().data() != input.data() || taken.pred().limit != predicate.limit ||
            dropped.pred().limit != predicate.limit)
            return 4;
        rg::filter_view<decltype(ref), below> filtered(ref, predicate);
        if (rg::distance(filtered) != count || filtered.pred().limit != predicate.limit ||
            filtered.base().data() != input.data())
            return 5;
    }
    rg::transform_view<decltype(ref), twice> transformed(ref, twice{});
    rg::reverse_view<decltype(ref)> reversed(ref);
    if (transformed.size() != 5 || *transformed.begin() != seed * 2 || transformed.begin()[4] != (seed + 4) * 2 ||
        transformed.end() - transformed.begin() != 5 || transformed.base().data() != input.data() ||
        reversed.size() != 5 || *reversed.begin() != seed + 4 || reversed.begin()[4] != seed ||
        reversed.end() - reversed.begin() != 5 || reversed.base().data() != input.data())
        return 6;

    rg::empty_view<int> empty;
    rg::single_view<int> single(seed);
    rg::owning_view<decltype(input)> owning(ast::move(input));
    if (!empty.empty() || empty.data() != nullptr || empty.begin() != empty.end() || empty.size() != 0 ||
        single.size() != 1 || single.data() != single.begin() || *single.begin() != seed ||
        single.end() - single.begin() != 1 || owning.empty() || owning.size() != 5 ||
        owning.data() != owning.base().data() || owning.end() - owning.begin() != 5)
        return 7;
    owning = rg::owning_view<decltype(input)>(decltype(input){0, 1, 2, 3, seed});
    if (*owning.begin() != 0 || owning.base()[4] != seed)
        return 8;

    rg::subrange<int*> whole(input.begin(), input.end(), 5);
    if (whole.empty() || whole.size() != 5 || whole.begin() != input.begin() || whole.end() != input.end() ||
        !rg::subrange<int*>{input.begin(), input.begin()}.empty())
        return 9;
    return 0;
}

CANN_ASC_STL_API int evaluate_layouts(int seed)
{
    int storage[12]{};
    ast::span<int> view(storage);
    auto slice = view.subspan(1, 3);
    auto bytes = ast::as_writable_bytes(slice);
    if (slice.size() != 3 || slice.data() != storage + 1 || bytes.size() != 3 * sizeof(int) ||
        ast::as_bytes(slice).size() != bytes.size())
        return 1;
    slice[0] = seed;
    for (ast::size_t index = 0; index < sizeof(int); ++index)
        bytes[index] = ast::byte{0};
    if (storage[1] != 0)
        return 6;
    alignas(16) int values[12]{};
    using extents = ast::dextents<ast::size_t, 2>;
    using mapping = ast::layout_stride::mapping<extents>;
    using array = ast::array<ast::size_t, 2>;
    const extents dimensions(2, 3);
    const mapping padded(dimensions, array{5, 1});
    ast::mdspan<int, extents, ast::layout_stride> matrix(values, padded);
    if (!matrix.is_strided() || !matrix.is_unique() || matrix.is_exhaustive() ||
        matrix.mapping().required_span_size() != 8 || matrix.stride(0) != 5 || matrix.stride(1) != 1 ||
        matrix.extent(0) != 2 || matrix.extent(1) != 3 || matrix.size() != 6 || matrix.empty() ||
        matrix.data_handle() != values || matrix.extents() != dimensions)
        return 2;
    matrix[array{1, 2}] = seed;
    const auto row = ast::submdspan(matrix, 1, ast::full_extent);
    if (row.data_handle() != values + 5 || row.stride(0) != 1 || row.mapping()(2) != 2)
        return 64 + 4 * static_cast<int>(row.stride(0)) + static_cast<int>(row.data_handle() - values);
    const int row_failures = (row[2] != seed ? 1 : 0) | (values[7] != seed ? 2 : 0) | (values[4] != 0 ? 4 : 0) |
        (row.extent(0) != 3 ? 8 : 0);
    if (row_failures != 0)
        return 16 + row_failures;
    if (matrix.accessor().access(values, 7) != seed || matrix.accessor().offset(values, 5) != values + 5)
        return 5;
    const auto transposed = ast::linalg::transposed(matrix);
    const auto scaled = ast::linalg::scaled(3, transposed);
    if (transposed.extent(0) != 3 || transposed.extent(1) != 2 || transposed[array{2, 1}] != seed ||
        scaled[array{2, 1}] != seed * 3 || scaled[array{0, 0}] != 0)
        return 4;
    const auto stripe = ast::submdspan(matrix, ast::full_extent, ast::strided_slice{0, 3, 2});
    if (stripe.size() != 4 || stripe.extent(1) != 2 || stripe.stride(0) != 5 || stripe.stride(1) != 2 ||
        stripe.mapping().required_span_size() != 8 || stripe[array{1, 1}] != seed)
        return 7;
    alignas(16) volatile int writable_storage[8]{};
    const ast::mdspan<volatile int, extents, ast::layout_stride> writable(writable_storage, padded);
    const auto writable_stripe = ast::submdspan(writable, ast::full_extent, ast::strided_slice{0, 3, 2});
    if (&writable_stripe[array{0, 1}] != writable_storage + 2)
        return 8;
    writable_stripe[array{0, 1}] = seed + 1;
    if (writable_storage[2] != seed + 1 || writable_storage[3] != 0 || writable_stripe[array{0, 1}] != seed + 1)
        return 9;
    return 0;
}

}  // namespace asc_stl_standard_view_test

#endif  // ASC_STL_TEST_STANDARD_VIEW_SEMANTICS_H
