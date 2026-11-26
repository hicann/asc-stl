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

#ifndef ASC_STL_TEST_OPTIONAL_DEVICE_CHECKS_H
#define ASC_STL_TEST_OPTIONAL_DEVICE_CHECKS_H

#include <asc/std/optional>

namespace asc_stl_test_optional {

template <class Left, class Right>
CANN_ASC_STL_API bool ordered(const Left& left, const Right& right, int cmp)
{
    return (left == right) == (cmp == 0) && (left != right) == (cmp != 0) && (left < right) == (cmp < 0) &&
        (left <= right) == (cmp <= 0) && (left > right) == (cmp > 0) && (left >= right) == (cmp >= 0);
}

CANN_ASC_STL_API int check(int seed = 7)
{
    using asc::std::swap;
    asc::std::optional<int> empty(asc::std::nullopt);
    auto some = asc::std::make_optional(3 - seed);
    const asc::std::optional<int> same(-4);
    if (!ordered(empty, asc::std::nullopt, 0) || !ordered(asc::std::nullopt, empty, 0) ||
        !ordered(some, asc::std::nullopt, 1) || !ordered(asc::std::nullopt, some, -1) || !ordered(empty, some, -1) ||
        !ordered(some, same, 0) || !ordered(some, 3, -1) || !ordered(3, some, 1) || !ordered(-4, same, 0) ||
        !ordered(empty, -100, -1))
        return 1;

    swap(empty, some);
    if (!empty || *empty != -4 || some.has_value() ||
        asc::std::move(some).value_or(17) != 17 ||  // NOLINT(build/include_what_you_use)
        asc::std::hash<asc::std::optional<int>>{}(some) != 0 ||
        asc::std::hash<asc::std::optional<int>>{}(empty) != asc::std::hash<int>{}(-4))
        return 2;
    const asc::std::optional<short> small(static_cast<short>(-8));
    asc::std::optional<int> converted(small);
    converted = asc::std::nullopt;
    converted = small;
    if (converted.value_or(0) != -8 || &converted.emplace(6) != converted.operator->() || *converted != 6)
        return 3;
    int x = 11;
    asc::std::optional<int&> ref(x);
    *ref = -1;
    if (x != -1 || &*ref != &x)
        return 4;
    ref = asc::std::nullopt;
    return ref.has_value() ? 5 : 0;
}

}  // namespace asc_stl_test_optional

#endif  // ASC_STL_TEST_OPTIONAL_DEVICE_CHECKS_H
