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

#ifndef ASC_STL_TEST_RANGES_DEVICE_CHECKS_H
#define ASC_STL_TEST_RANGES_DEVICE_CHECKS_H

#include <asc/std/ranges>

#include "views_checks.h"

namespace asc_stl_test_ranges {
struct even {
    CANN_ASC_STL_API bool operator()(int n) const
    {
        return n % 2 == 0;
    }
};
struct square {
    CANN_ASC_STL_API int operator()(int n) const
    {
        return n * n;
    }
};
CANN_ASC_STL_API int check(int seed = 7)
{
    if (int result = check_views(seed))
        return 20 + result;
    int raw[] = {-3, -2, -1, seed - 7, 1, 2, 3};
    for (int size = 0; size <= 7; ++size) {
        auto source = asc::std::ranges::views::counted(raw + 0, size);
        for (int cut = 0; cut <= 8; ++cut) {
            const int used = cut < size ? cut : size;
            auto head = source | asc::std::ranges::views::take(cut);
            auto tail = source | asc::std::ranges::views::drop(cut);
            if (head.size() != static_cast<unsigned>(used) || tail.size() != static_cast<unsigned>(size - used))
                return 1;
            auto transformed = tail | asc::std::ranges::views::reverse | asc::std::ranges::views::filter(even{}) |
                asc::std::ranges::views::transform(square{});
            int expected_index = size;
            for (int value : transformed) {
                while (expected_index > used && raw[expected_index - 1] % 2 != 0)
                    --expected_index;
                if (expected_index == used)
                    return 2;
                --expected_index;
                if (value != raw[expected_index] * raw[expected_index])
                    return 3;
            }
            while (expected_index > used)
                if (raw[--expected_index] % 2 == 0)
                    return 4;
            auto zipped = asc::std::ranges::views::zip(head, tail);
            unsigned pairs = 0;
            for (auto pair : zipped) {
                if (asc::std::get<0>(pair) != raw[pairs] || asc::std::get<1>(pair) != raw[used + pairs])
                    return 5;
                ++pairs;
            }
            if (pairs != zipped.size() || pairs != static_cast<unsigned>(used < size - used ? used : size - used))
                return 6;
        }
    }
    return 0;
}
}  // namespace asc_stl_test_ranges

#endif  // ASC_STL_TEST_RANGES_DEVICE_CHECKS_H
