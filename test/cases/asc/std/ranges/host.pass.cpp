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

#include <asc/std/ranges>
#include <asc/std/array>
#include <asc/std/tuple>
#include <asc/std/__type_traits/is_same.h>

#include "support/repeat_piecewise_semantics.h"

struct movable_range {
    int* first;
    int* last;
    movable_range(int* begin, int* end) : first(begin), last(end)
    {}
    movable_range(const movable_range&) = delete;
    movable_range& operator=(const movable_range&) = delete;
    movable_range(movable_range&&) = default;
    movable_range& operator=(movable_range&&) = default;
    int* begin() const
    {
        return first;
    }
    int* end() const
    {
        return last;
    }
};

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
static_assert(asc::std::ranges::viewable_range<movable_range>);
static_assert(asc::std::ranges::viewable_range<movable_range&>);
#endif

struct less_than_four {
    constexpr bool operator()(int value) const
    {
        return value < 4;
    }
};
struct is_even {
    constexpr bool operator()(int value) const
    {
        return (value & 1) == 0;
    }
};
struct times_three {
    constexpr int operator()(int value) const
    {
        return value * 3;
    }
};

struct pointer_sentinel {
    int* end;
};
constexpr bool operator==(int* iterator, pointer_sentinel sentinel)
{
    return iterator == sentinel.end;
}
constexpr bool operator==(pointer_sentinel sentinel, int* iterator)
{
    return iterator == sentinel;
}
constexpr bool operator!=(int* iterator, pointer_sentinel sentinel)
{
    return !(iterator == sentinel);
}
constexpr bool operator!=(pointer_sentinel sentinel, int* iterator)
{
    return !(sentinel == iterator);
}
struct non_common_range {
    int* first;
    int* last;
    constexpr int* begin() const
    {
        return first;
    }
    constexpr pointer_sentinel end() const
    {
        return {last};
    }
};
template <class T>
constexpr bool same_type(T, T)
{
    return true;
}

int main()
{
    if (asc_stl_repeat_piecewise_test::evaluate() != 0)
        return 101;
    int values[] = {1, 2, 3, 4, 5, 6};
    auto reference = asc::std::ranges::views::all(values);
    if (reference.size() != 6 || reference.data() != values)
        return 1;
    auto dropped = values | asc::std::ranges::views::drop(2);
    if (*dropped.begin() != 3 || dropped.size() != 4)
        return 2;
    auto taken = values | asc::std::ranges::views::take(3);
    if (taken.size() != 3 || *(taken.end() - 1) != 3)
        return 3;
    auto filtered = values | asc::std::ranges::views::filter(is_even{});
    int filter_sum = 0;
    for (int value : filtered)
        filter_sum += value;
    if (filter_sum != 12)
        return 4;
    auto filtered_taken = filtered | asc::std::ranges::views::take(2);
    auto filtered_taken_iterator = filtered_taken.begin();
    if (*filtered_taken_iterator != 2 || *(++filtered_taken_iterator) != 4)
        return 28;
    auto transformed = values | asc::std::ranges::views::transform(times_three{});
    if (*transformed.begin() != 3)
        return 5;
    const auto const_transformed = values | asc::std::ranges::views::transform(times_three{});
    if (*const_transformed.begin() != 3 || const_transformed.size() != 6)
        return 26;
    auto transformed_iterator = transformed.begin();
    transformed_iterator++;
    if (*transformed_iterator != 6)
        return 29;
    auto drop_while = values | asc::std::ranges::views::drop_while(less_than_four{});
    if (*drop_while.begin() != 4)
        return 6;
    auto take_while = values | asc::std::ranges::views::take_while(less_than_four{});
    if (take_while.end() - take_while.begin() != 3)
        return 7;
    const auto const_take_while = values | asc::std::ranges::views::take_while(less_than_four{});
    if (const_take_while.end() - const_take_while.begin() != 3)
        return 27;
    auto reversed = asc::std::ranges::views::reverse(values);
    if (*reversed.begin() != 6)
        return 8;
    auto repeated = asc::std::ranges::views::repeat(7, 4);
    if (repeated.size() != 4 || repeated.begin()[3] != 7)
        return 9;
    asc::std::ranges::repeat_view<int, int> default_repeat;
    if (default_repeat.begin() != default_repeat.end() || default_repeat.size() != 0)
        return 22;
    asc::std::ranges::repeat_view<int, int> piecewise_repeat(
        asc::std::piecewise_construct, asc::std::tuple<int>(6), asc::std::tuple<int>(2));
    if (piecewise_repeat.size() != 2 || *piecewise_repeat.begin() != 6)
        return 23;
    auto iota = asc::std::ranges::views::iota(3, 8);
    if (iota.size() != 5 || iota.begin()[4] != 7)
        return 10;
    int other[] = {10, 20, 30};
    auto zipped = asc::std::ranges::views::zip(values, other);
    if (zipped.size() != 3)
        return 11;
    auto first = *zipped.begin();
    asc::std::get<0>(first) = 9;
    if (values[0] != 9 || asc::std::get<1>(first) != 10)
        return 12;
    const auto const_zipped = asc::std::ranges::views::zip(values, other);
    auto const_first = *const_zipped.begin();
    if (const_zipped.size() != 3 || asc::std::get<1>(const_first) != 10)
        return 24;
    asc::std::ranges::zip_view<asc::std::ranges::empty_view<int>, asc::std::ranges::empty_view<int>> empty_zip;
    if (empty_zip.size() != 0 || empty_zip.begin() != empty_zip.end())
        return 25;
    auto one = asc::std::ranges::views::single(42);
    if (one.front() != 42 || one.size() != 1)
        return 13;
    auto counted = asc::std::ranges::views::counted(values, 2);
    if (counted.size() != 2 || counted.begin()[1] != 2)
        return 14;
    auto owned = asc::std::ranges::views::all(asc::std::array<int, 3>{7, 8, 9});
    if (owned.empty() || owned.size() != 3 || owned.data() != owned.begin() || owned.begin()[0] != 7 ||
        owned.begin()[2] != 9)
        return 15;
    auto source_view = asc::std::ranges::views::single(42);
    auto copied_view = asc::std::ranges::views::all(source_view);
    static_assert(asc::std::is_same_v<decltype(copied_view), decltype(source_view)>);
    if (*copied_view.begin() != 42)
        return 31;
    auto moved_view = asc::std::ranges::views::all(asc::std::ranges::views::single(73));
    static_assert(asc::std::is_same_v<decltype(moved_view), decltype(source_view)>);
    if (*moved_view.begin() != 73)
        return 32;
    movable_range movable{values, values + 2};
    auto owned_movable = asc::std::ranges::views::all(static_cast<movable_range&&>(movable));
    if (*owned_movable.begin() != 9)
        return 33;
    const int constant_values[] = {4, 5};
    const auto constant_reference = asc::std::ranges::views::all(constant_values);
    if (constant_reference.data() != constant_values || *constant_reference.begin() != 4)
        return 16;
    int non_common_values[] = {2, 4, 6};
    auto common = asc::std::ranges::views::common(non_common_range{non_common_values, non_common_values + 3});
    auto common_begin = common.begin();
    auto common_end = common.end();
    if (!same_type(common_begin, common_end))
        return 17;
    int common_sum = 0;
    for (; common_begin != common_end; ++common_begin)
        common_sum += *common_begin;
    if (common_sum != 12)
        return 18;
    asc::std::ranges::subrange<int*> slice(values, values + 4);
    if (slice.size() != 4 || *slice.next(2).begin() != 3 || *slice.next(3).prev().begin() != 3)
        return 19;
    non_common_range source{non_common_values, non_common_values + 3};
    auto non_common_filtered = source | asc::std::ranges::views::filter(is_even{});
    int non_common_filtered_sum = 0;
    for (int value : non_common_filtered)
        non_common_filtered_sum += value;
    if (non_common_filtered_sum != 12)
        return 30;
    asc::std::ranges::subrange<int*, pointer_sentinel> non_common_slice(source);
    if (non_common_slice.empty() || *non_common_slice.begin() != 2)
        return 20;
    asc::std::ranges::borrowed_subrange_t<decltype((values))> borrowed_slice(values);
    if (borrowed_slice.size() != 6 || borrowed_slice.begin() != values)
        return 21;
    return 0;
}
