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

#ifndef ASC_STL_TEST_RANGES_FIND_H
#define ASC_STL_TEST_RANGES_FIND_H

#include <asc/std/algorithm>
#include <asc/std/ranges>
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <type_traits>
#include <vector>

namespace asc_stl_ranges_find_test {

struct Axis {
    uint32_t code;
    int64_t dim;
};
struct End {
    Axis* value = nullptr;
    friend constexpr bool operator==(Axis* a, End b)
    {
        return a == b.value;
    }
    friend constexpr bool operator==(End a, Axis* b)
    {
        return b == a;
    }
    friend constexpr bool operator!=(Axis* a, End b)
    {
        return !(a == b);
    }
    friend constexpr bool operator!=(End a, Axis* b)
    {
        return !(a == b);
    }
};

namespace ranges = asc::std::ranges;
constexpr bool verify_constants()
{
    Axis axes[] = {{3, 4}, {1, 9}, {3, 2}, {2, 1}};
    if (ranges::find(axes, uint32_t{3}, &Axis::code) != axes || !ranges::contains(axes, int64_t{9}, &Axis::dim)) {
        return false;
    }
    if (ranges::contains(axes, int64_t{8}, &Axis::dim) ||
        ranges::find(axes, End{axes + 4}, uint32_t{9}, &Axis::code) != axes + 4) {
        return false;
    }
    auto end = ranges::sort(axes, End{axes + 4}, {}, &Axis::dim);
    return end == axes + 4 && axes[0].dim == 1 && axes[1].dim == 2 && axes[2].dim == 4 && axes[3].dim == 9;
}
static_assert(verify_constants());
static_assert(std::is_same_v<decltype(ranges::find(std::vector<int>{1}, 1)), ranges::dangling>);
static_assert(std::is_same_v<decltype(ranges::sort(std::vector<int>{1})), ranges::dangling>);

int run()
{
    std::vector<Axis> axes = {{3, 4}, {1, 9}, {3, 2}, {2, 1}};
    assert(ranges::find(axes, uint32_t{3}, &Axis::code)->dim == 4);
    assert(ranges::contains(axes, uint32_t{1}, &Axis::code));
    assert(!ranges::contains(axes, uint32_t{0}, &Axis::code));
    const auto end = ranges::sort(axes, ranges::greater{}, &Axis::dim);
    assert(end == axes.end() && axes.front().dim == 9 && axes.back().dim == 1);
    assert(std::is_sorted(axes.begin(), axes.end(), [](const auto& a, const auto& b) { return a.dim > b.dim; }));
    std::vector<int> empty;
    assert(ranges::find(empty, 0) == empty.end());
    assert(!ranges::contains(empty, 0));
    assert(ranges::sort(empty) == empty.end());
    std::vector<int> mixed = {3, 1, 3, -1, 0, 1};
    assert(ranges::sort(mixed) == mixed.end());
    assert((mixed == std::vector<int>{-1, 0, 1, 1, 3, 3}));
    return 0;
}
}  // namespace asc_stl_ranges_find_test

#endif  // ASC_STL_TEST_RANGES_FIND_H
