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

#ifndef ASC_STL_TEST_EXPECTED_DEVICE_CHECKS_H
#define ASC_STL_TEST_EXPECTED_DEVICE_CHECKS_H

#include <asc/std/expected>

namespace asc_stl_test_expected {

using result = asc::std::expected<int, short>;

struct plus_one {
    CANN_ASC_STL_API int operator()(int x) const
    {
        return x + 1;
    }
};
struct next {
    CANN_ASC_STL_API result operator()(int x) const
    {
        return result(x + 5);
    }
};
struct recover {
    CANN_ASC_STL_API result operator()(short x) const
    {
        return result(2 * x);
    }
};

template <class Item>
CANN_ASC_STL_API bool monads(Item&& item, bool good)
{
    using asc::std::forward;
    auto mapped = forward<Item>(item).transform(plus_one{});
    auto changed = forward<Item>(item).transform_error(plus_one{});
    auto chained = forward<Item>(item).and_then(next{});
    auto fallback = forward<Item>(item).or_else(recover{});
    if (good)
        return mapped == 8 && changed == 7 && chained == 12 && fallback == 7;
    return !mapped && mapped.error() == -3 && !changed && changed.error() == -2 && !chained && chained.error() == -3 &&
        fallback == -6;
}

CANN_ASC_STL_API int check(int seed = 7)
{
    using asc::std::swap;
    result value(asc::std::in_place, seed), error(asc::std::unexpect, -3);
    const result fixed_value = value, fixed_error = error;
    if (!monads(value, true) || !monads(error, false) || !monads(fixed_value, true) || !monads(fixed_error, false) ||
        !monads(asc::std::move(value), true) || !monads(asc::std::move(error), false) ||
        !monads(asc::std::move(fixed_value), true) || !monads(asc::std::move(fixed_error), false))
        return 1;
    asc::std::unexpected<short> one(static_cast<short>(-3));
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    asc::std::unexpected<short> two(static_cast<short>(4));
#else
    asc::std::unexpected<short> two(asc::std::in_place, static_cast<short>(4));
#endif
    swap(one, two);  // NOLINT(build/include_what_you_use)
    if (one.error() != 4 || two != asc::std::unexpected<int>(-3) || error != two || value == two)
        return 2;
    value.swap(error);
    if (value.has_value() || value.error_or(0) != -3 || value.value_or(18) != 18 || !error || *error != 7 ||
        error.error_or(9) != 9)
        return 3;
    error = two;
    value = 14;
    if (error != two || *value != 14 || &error.emplace(8) != error.operator->() || *error != 8)
        return 4;
    return 0;
}

}  // namespace asc_stl_test_expected

#endif  // ASC_STL_TEST_EXPECTED_DEVICE_CHECKS_H
