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

#ifndef ASC_STL_TEST_TUPLE_DEVICE_CHECKS_H
#define ASC_STL_TEST_TUPLE_DEVICE_CHECKS_H

#include <asc/std/tuple>

namespace asc_stl_test_tuple {

struct digits {
    int value;
    CANN_ASC_STL_API digits(int x, int y) : value(10 * x + y)
    {}
};

CANN_ASC_STL_API int check(int seed = 7)
{
    using asc::std::swap;
    static_assert(asc::std::tuple_size_v<decltype(asc::std::tuple_cat())> == 0);
    asc::std::tuple<const int, short, int*> defaults;
    if (asc::std::get<0>(defaults) != 0 || asc::std::get<1>(defaults) != 0 || asc::std::get<2>(defaults) != nullptr)
        return 6;
    auto start = asc::std::make_tuple(2, static_cast<short>(seed));
    static_assert(asc::std::is_same_v<asc::std::tuple_element_t<1, decltype(start)>, short>);
    const auto& fixed = start;
    if (asc::std::get<int>(fixed) != 2 || asc::std::get<1>(fixed) != 7 ||
        asc::std::make_from_tuple<digits>(start).value != 27 ||
        asc::std::apply([](int a, int b) { return a - b; }, start) != -5)
        return 1;
    int x = 5, y = 6;
    auto refs = asc::std::forward_as_tuple(x, y);
    asc::std::get<0>(refs) = 11;
    asc::std::tie(asc::std::ignore, y) = start;
    if (x != 11 || y != 7)
        return 2;

    auto joined = asc::std::tuple_cat(asc::std::tuple<>(), start, asc::std::tie(x), asc::std::tuple<>());
    asc::std::get<2>(joined) = -9;
    if (x != -9 || asc::std::get<1>(joined) != 7)
        return 3;
    auto end = asc::std::make_tuple(2, static_cast<short>(8));
    if (!(start < end && start <= end && end > start && end >= start && end != start && end == end))
        return 4;
    swap(start, end);
    if (asc::std::get<1>(start) != 8 ||
        asc::std::get<short>(asc::std::move(end)) != 7)  // NOLINT(build/include_what_you_use)
        return 5;
    return 0;
}

}  // namespace asc_stl_test_tuple

#endif  // ASC_STL_TEST_TUPLE_DEVICE_CHECKS_H
