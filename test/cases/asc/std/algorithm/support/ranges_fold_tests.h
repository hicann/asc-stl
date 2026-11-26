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

#ifndef ASC_STL_TEST_RANGES_FOLD_H
#define ASC_STL_TEST_RANGES_FOLD_H

#include <asc/std/algorithm>
#include <asc/std/ranges>
#include <asc/std/functional>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <memory>
#include <type_traits>
#include <vector>

namespace asc_stl_ranges_fold_test {

struct Sentinel {
    const int* end;
};
bool operator==(const int* p, Sentinel s)
{
    return p == s.end;
}
bool operator==(Sentinel s, const int* p)
{
    return p == s;
}
bool operator!=(const int* p, Sentinel s)
{
    return !(p == s);
}
bool operator!=(Sentinel s, const int* p)
{
    return !(p == s);
}
struct Widen {
    double operator()(int x, int y) const
    {
        return x + 0.5 * y;
    }
    double operator()(double x, int y) const
    {
        return x + 0.5 * y;
    }
};
struct Box {
    int value;
    Box combine(int x) &&
    {
        return {value * 10 + x};
    }
};
struct Axis {
    uint32_t code;
    int64_t dim;
};
int run()
{
    int values[] = {1, 2, 3, 4};
    auto append = [](int a, int b) { return a * 10 + b; };
    assert(asc::std::ranges::fold_left(values, 0, append) == 1234);
    assert(asc::std::ranges::fold_left(values, values, 7, append) == 7);
    assert(asc::std::ranges::fold_left(static_cast<const int*>(values), Sentinel{values + 4}, 0, append) == 1234);
    auto widened = asc::std::ranges::fold_left(values, 1, Widen{});
    static_assert(std::is_same<decltype(widened), double>::value, "result decays first invocation");
    assert(widened == 6.0);
    assert(asc::std::ranges::fold_left(values, values, 9, Widen{}) == 9.0);
    assert(asc::std::ranges::fold_left(values, Box{0}, &Box::combine).value == 1234);
    auto owned = asc::std::ranges::fold_left(values, std::make_unique<int>(0), [](std::unique_ptr<int> p, int x) {
        *p += x;
        return p;
    });
    assert(*owned == 10);
    for (int length = 0; length <= 8; ++length) {
        std::vector<Axis> axes;
        for (int i = 0; i < length; ++i)
            axes.push_back({uint32_t{1} << i, i * 3 + 1});
        for (uint32_t mask = 0; mask < 256; ++mask) {
            int64_t original = 1;
            for (const auto& axis : axes) {
                if ((axis.code & mask) != 0) {
                    const bool align = axis.code == 1 || axis.code == 8;
                    original *= align ? ((axis.dim + 7) / 8) * 8 : axis.dim;
                }
            }
            auto selected =
                axes | asc::std::ranges::views::filter([mask](const Axis& a) { return (a.code & mask) != 0; });
            auto result = asc::std::ranges::fold_left(selected, int64_t{1}, [](int64_t p, const Axis& a) {
                return p * ((a.code == 1 || a.code == 8) ? ((a.dim + 7) / 8) * 8 : a.dim);
            });
            assert(result == original);
            const auto dimensions = axes | asc::std::ranges::views::transform(&Axis::dim);
            int64_t product = 1;
            for (const auto& a : axes)
                product *= a.dim;
            assert(asc::std::ranges::fold_left(dimensions, int64_t{1}, asc::std::multiplies<int64_t>{}) == product);
        }
    }
    std::cout << "FOLD_PASS empty/order/widen/member/move/sentinel; 2304 mask cases; filter/transform products\n";
    return 0;
}
}  // namespace asc_stl_ranges_fold_test

#endif  // ASC_STL_TEST_RANGES_FOLD_H
