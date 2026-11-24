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

#ifndef ASC_STL_TEST_SUPPORT_ITERATOR_ADAPTORS_H
#define ASC_STL_TEST_SUPPORT_ITERATOR_ADAPTORS_H

#include <asc/iterator>
#include <asc/numeric_types>
#include <asc/std/algorithm>
#include <asc/std/array>

namespace asc_stl_iterator_test {

struct twice {
    CANN_ASC_STL_API constexpr int operator()(int value) const noexcept
    {
        return value * 2;
    }
};
struct add_pair {
    CANN_ASC_STL_API constexpr int operator()(int left, int right) const noexcept
    {
        return left + right;
    }
};
struct reverse_four {
    CANN_ASC_STL_API constexpr ::asc::std::size_t operator()(::asc::std::size_t value) const noexcept
    {
        return 3 - value;
    }
};
struct flip {
    CANN_ASC_STL_API constexpr unsigned operator()(unsigned value) const noexcept
    {
        return value ^ 0x80u;
    }
};
struct tabulate {
    int* values;
    int* calls;
    CANN_ASC_STL_API void operator()(::asc::std::ptrdiff_t index, int value)
    {
        values[index] = value;
        ++*calls;
    }
};
struct row {
    int key;
    int other;
};
struct key_of {
    CANN_ASC_STL_API constexpr int& operator()(row& value) const noexcept
    {
        return value.key;
    }
};
struct record {
    int value;
};
struct identity {
    template <class T>
    CANN_ASC_STL_API constexpr T&& operator()(T&& value) const noexcept
    {
        return ::asc::std::forward<T>(value);  // NOLINT(build/include_what_you_use)
    }
};

CANN_ASC_STL_API constexpr bool constexpr_positions()
{
    auto count = asc::make_counting_iterator(5);
    auto old = count++;
    count += 3;
    auto constant = asc::make_constant_iterator(8);
    auto sink = asc::make_discard_iterator();
    sink += 4;
    *sink = 9;
    int data[5] = {10, 20, 30, 40, 50};
    auto stride = asc::make_strided_iterator(data, 5, -2);
    auto end = stride + stride.count();
    --end;
    return *old == 5 && count[0] == 9 && count - old == 4 && constant[3] == 8 && sink.index() == 4 && *stride == 50 &&
        stride[1] == 30 && *end == 10 && end.base() == data;
}
static_assert(constexpr_positions());
using counting = asc::counting_iterator<int>;
static_assert(asc::std::is_same_v<typename counting::iterator_category, asc::std::input_iterator_tag>);
static_assert(asc::std::is_same_v<typename counting::reference, int>);
static_assert(noexcept(++asc::std::declval<counting&>()));
static_assert(noexcept(asc::std::declval<counting&>()++));
static_assert(!asc::std::is_convertible_v<asc::strided_iterator<const int*>, asc::strided_iterator<int*>>);
static_assert(asc::std::is_convertible_v<asc::strided_iterator<int*>, asc::strided_iterator<const int*>>);
#if CANN_ASC_STL_DETAIL_HAS_CXX20()
static_assert(asc::std::random_access_iterator<counting>);
static_assert(!asc::std::contiguous_iterator<counting>);
static_assert(asc::std::random_access_iterator<asc::constant_iterator<int>>);
static_assert(asc::std::random_access_iterator<asc::strided_iterator<int*>>);
static_assert(asc::std::output_iterator<asc::discard_iterator, int>);
static_assert(!asc::std::indirectly_readable<asc::discard_iterator>);
static_assert(!asc::std::random_access_iterator<asc::discard_iterator>);
using zip = asc::zip_iterator<int*, int*>;
static_assert(asc::std::random_access_iterator<zip>);
static_assert(asc::std::indirectly_writable<zip, asc::std::tuple<int, int>>);
static_assert(asc::std::permutable<zip>);
static_assert(!asc::std::indirectly_writable<asc::zip_iterator<const int*, int*>, asc::std::tuple<int, int>>);
using read_write = asc::transform_input_output_iterator<flip, flip, unsigned*>;
static_assert(asc::std::random_access_iterator<read_write>);
static_assert(asc::std::indirectly_writable<read_write, unsigned>);
static_assert(asc::std::permutable<read_write>);
#endif

CANN_ASC_STL_API int virtual_sequences()
{
    int output[6] = {};
    auto count = asc::make_counting_iterator(3);
    asc::std::copy_n(count, 6, output);
    for (int n = 0; n < 6; ++n) {
        if (output[n] != n + 3) {
            return 1;
        }
    }
    auto constant = asc::make_constant_iterator(7);
    asc::std::copy_n(constant, 6, output);
    for (int value : output) {
        if (value != 7) {
            return 2;
        }
    }
    auto narrow = asc::make_counting_iterator(static_cast<unsigned char>(254));
    auto virtual_end = narrow + 2;
    if (narrow[0] != 254 || narrow[1] != 255 || virtual_end - narrow != 2) {
        return 3;
    }
    auto backwards = asc::make_counting_iterator(2u, asc::std::ptrdiff_t{-2});
    if (*backwards != 0 || backwards[2] != 2) {
        return 4;
    }
    auto edge =
        asc::make_counting_iterator((asc::std::numeric_limits<unsigned long long>::max)(), asc::std::ptrdiff_t{-1});
    if (*edge != (asc::std::numeric_limits<unsigned long long>::max)() - 1) {
        return 5;
    }
    const auto arrow = asc::make_constant_iterator(record{19});
    if (arrow->value != 19) {
        return 6;
    }
    return 0;
}

CANN_ASC_STL_API int strided_sequences()
{
    int data[7] = {9, 100, 5, 101, 7, 102, 1};
    auto stride = asc::make_strided_iterator(data, 7, 2);
    asc::std::sort(stride, stride + stride.count());  // NOLINT(build/include_what_you_use)
    const int sorted[7] = {1, 100, 5, 101, 7, 102, 9};
    for (int n = 0; n < 7; ++n) {
        if (data[n] != sorted[n]) {
            return 10;
        }
    }
    auto reverse = asc::make_strided_iterator(data, 7, -2);
    int output[4] = {};
    asc::std::copy_n(reverse, 4, output);
    const int expected[4] = {9, 7, 5, 1};
    for (int n = 0; n < 4; ++n) {
        if (output[n] != expected[n]) {
            return 11;
        }
    }
    auto end = reverse + reverse.count();
    if (*--end != 1 || end - reverse != 3 || !(reverse < end)) {
        return 12;
    }
    auto empty = asc::make_strided_iterator(static_cast<int*>(nullptr), 0, -3);
    if (empty.count() != 0 || empty != empty + 0 || (empty + 0) - empty != 0) {
        return 13;
    }
    auto single = asc::make_strided_iterator(data, 7, (asc::std::numeric_limits<asc::std::ptrdiff_t>::lowest)());
    if (single.count() != 1 || *single != 9 || (single + 1) - single != 1) {
        return 14;
    }
    auto nondivisible = asc::make_strided_iterator(data, 6, -2);
    if (nondivisible.count() != 3 || nondivisible[0] != 102 || nondivisible[2] != 100) {
        return 15;
    }
    asc::std::reverse(stride, stride + 4);
    return data[0] == 9 && data[6] == 1 && data[1] == 100 ? 0 : 16;
}

CANN_ASC_STL_API int mapped_sequences()
{
    int data[4] = {11, 22, 33, 44};
    int indices[4] = {2, 0, 2, 1};
    auto gather = asc::make_permutation_iterator(data, indices);
    int result[4] = {};
    asc::std::copy_n(gather, 4, result);
    const int expected[4] = {33, 11, 33, 22};
    for (int n = 0; n < 4; ++n) {
        if (result[n] != expected[n]) {
            return 20;
        }
    }
    *gather = 7;
    gather[2] = 9;
    if (data[2] != 9 || gather == gather + 2 || (gather + 2) - gather != 2) {
        return 21;
    }
    auto mapped = asc::make_permutation_iterator(data, asc::make_shuffle_iterator(reverse_four{}));
    asc::std::copy_n(mapped, 4, result);
    if (result[0] != 44 || result[1] != 9 || result[2] != 22 || result[3] != 11) {
        return 22;
    }
    asc::std::ranges::iter_swap(mapped, mapped + 3);
    return data[0] == 44 && data[3] == 11 ? 0 : 23;
}

CANN_ASC_STL_API int transformed_sequences()
{
    int data[4] = {2, 3, 4, 5};
    int output[4] = {};
    auto read = asc::make_transform_iterator(data, twice{});
    auto write = asc::make_transform_output_iterator(output, twice{});
    asc::std::copy_n(read, 4, write);
    const int expected[4] = {8, 12, 16, 20};
    for (int n = 0; n < 4; ++n) {
        if (output[n] != expected[n]) {
            return 30;
        }
    }
    auto saved = *asc::make_transform_output_iterator(output, twice{});
    saved = 6;
    *write++ = 7;
    *write = 8;
    if (output[0] != 14 || output[1] != 16) {
        return 31;
    }
    int calls = 0;
    auto tab = asc::make_tabulate_output_iterator(tabulate{output, &calls});
    auto old = *tab++;
    old = 19;
    tab[2] = 29;
    if (calls != 2 || output[0] != 19 || output[3] != 29) {
        return 32;
    }
    int evaluated = 0;
    auto discard = asc::make_discard_iterator();
    *discard++ = ++evaluated;
    if (evaluated != 1 || discard.index() != 1) {
        return 33;
    }
    row rows[2] = {{3, 10}, {7, 20}};
    auto keys = asc::make_transform_iterator(rows, key_of{});
    asc::std::ranges::iter_swap(keys, keys + 1);
    return rows[0].key == 7 && rows[1].key == 3 && rows[0].other == 10 ? 0 : 34;
}

CANN_ASC_STL_API int read_write_sequences()
{
    unsigned storage[3] = {0, 0, 0};
    auto rw = asc::make_transform_input_output_iterator(storage, flip{}, flip{});
    *rw++ = 7u;
    rw[0] = 9u;
    rw[1] = 13u;
    if (storage[0] != 135u || storage[1] != 137u || storage[2] != 141u) {
        return 40;
    }
    unsigned decoded[3] = {};
    auto begin = rw - 1;
    asc::std::copy_n(begin, 3, decoded);
    if (decoded[0] != 7 || decoded[1] != 9 || decoded[2] != 13) {
        return 41;
    }
    *begin = *(begin + 1);
    if (storage[0] != 137u) {
        return 42;
    }
    asc::std::ranges::iter_swap(begin, begin + 2);
    unsigned first = *begin;
    unsigned last = begin[2];
    return first == 13 && last == 9 && storage[0] == 141 ? 0 : 43;
}

CANN_ASC_STL_API int zipped_sequences()
{
    int left[3] = {1, 2, 3};
    int right[4] = {10, 20, 30, 40};
    auto zipped = asc::make_zip_iterator(left, right);
    auto [a, b] = *zipped;
    a = 4;
    b = 14;
    if (left[0] != 4 || right[0] != 14 || (zipped + 2) - zipped != 2 || !(zipped < zipped + 2)) {
        return 50;
    }
    asc::std::tuple<int, int> values[3];
    asc::std::copy_n(zipped, 3, values);
    if (asc::std::get<0>(values[2]) != 3 || asc::std::get<1>(values[2]) != 30) {
        return 51;
    }
    *zipped = asc::std::tuple<int, int>(5, 15);
    asc::std::ranges::iter_swap(zipped, zipped + 1);
    if (left[0] != 2 || right[0] != 20 || left[1] != 5 || right[1] != 15) {
        return 52;
    }
    auto sum = asc::make_zip_transform_iterator(add_pair{}, left, right);
    int totals[3] = {};
    asc::std::copy_n(sum, 3, totals);
    if (totals[0] != 22 || totals[1] != 20 || totals[2] != 33 || right[3] != 40) {
        return 53;
    }
    int written[2] = {};
    auto output =
        asc::make_zip_iterator(asc::make_transform_output_iterator(written, twice{}), asc::make_discard_iterator());
    *output++ = asc::std::tuple<int, int>(7, 99);
    *output = asc::std::tuple<int, int>(8, 98);
    return written[0] == 14 && written[1] == 16 ? 0 : 54;
}

CANN_ASC_STL_API int packed_elements()
{
    const auto p = asc::pack_elements<asc::int4x2>(1, 7);
    asc::int4x2 packed[2] = {p, asc::from_bits<asc::int4x2>(0x23)};
    auto bytes = asc::make_strided_iterator(packed, 2);
    if (bytes.count() != 2 || asc::to_bits(*bytes) != 0x71 || asc::to_bits(bytes[1]) != 0x23) {
        return 60;
    }
    auto function = asc::make_zip_function(add_pair{});
    asc::std::array<int, 2> array{{3, 8}};
    if (function(array) != 11 || function(asc::std::pair<int, int>{4, 7}) != 11) {
        return 61;
    }
    return 0;
}

CANN_ASC_STL_API int evaluate()
{
    const int results[] = {virtual_sequences(), strided_sequences(), mapped_sequences(), transformed_sequences(),
        read_write_sequences(), zipped_sequences(), packed_elements()};
    for (int value : results) {
        if (value != 0) {
            return value;
        }
    }
    return 0;
}

// Input is supplied by Host in GM. Local is a real __ubuf__ pointer in SIMD;
// the same scalar protocol uses per-thread storage in a pure SIMT Kernel.
template <class Output, class Input, class Local>
CANN_ASC_STL_API void evaluate_spaces(Output output, Input input, Local local)
{
    output[0] = static_cast<unsigned>(evaluate());
    auto reverse = asc::make_strided_iterator(input, 5, -2);
    auto destination = asc::make_transform_output_iterator(output + 1, twice{});
    asc::std::copy_n(reverse, 3, destination);
    auto global = asc::make_strided_iterator(input, 5, 2);
    auto scratch = asc::make_strided_iterator(local, 5, -2);
    asc::std::copy_n(global, 3, asc::make_transform_output_iterator(scratch, twice{}));
    auto combined = asc::make_zip_iterator(output + 4, local);
    *combined = asc::std::tuple<unsigned, unsigned>(11, 7);
    auto ascending = asc::make_strided_iterator(local, 5, 2);
    asc::std::copy_n(ascending, 3, output + 5);
    auto rw = asc::make_transform_input_output_iterator(output + 8, flip{}, flip{});
    auto saved = *rw++;
    saved = 9u;
    output[9] = static_cast<unsigned>(saved);
    int indices[2] = {0, 0};
    auto repeated = asc::make_permutation_iterator(output + 10, indices);
    *repeated++ = 1;
    *repeated = 2;
    output[11] = static_cast<unsigned>((reverse + 3) - reverse);
    auto sums = asc::make_zip_transform_iterator(add_pair{}, input, local);
    output[12] = static_cast<unsigned>(*sums);
    auto count = asc::make_counting_iterator((asc::std::numeric_limits<unsigned>::max)() - 1);
    output[13] = count[1] == (asc::std::numeric_limits<unsigned>::max)();
    unsigned evaluated = 0;
    *asc::make_discard_iterator() = ++evaluated;
    output[14] = evaluated;
    output[15] = (reverse + 3).base() == input;
}

}  // namespace asc_stl_iterator_test

#endif  // ASC_STL_TEST_SUPPORT_ITERATOR_ADAPTORS_H
