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

#ifndef ASC_STL_TEST_VARIANT_DEVICE_CHECKS_H
#define ASC_STL_TEST_VARIANT_DEVICE_CHECKS_H

#include <asc/std/variant>

namespace asc_stl_test_variant {

struct sum {
    template <class... T>
    CANN_ASC_STL_API int operator()(T... value) const
    {
        return (static_cast<int>(value) + ...);
    }
};

CANN_ASC_STL_API int check(int seed = 7)
{
    using asc::std::swap;
    using choice = asc::std::variant<int, short>;
    static_assert(asc::std::variant_size_v<choice> == 2 &&
        asc::std::is_same_v<asc::std::variant_alternative_t<1, choice>, short>);
    choice first(seed - 3), second(asc::std::in_place_index<1>, static_cast<short>(-2));
    choice* no_value = nullptr;
    if (asc::std::get_if<int>(no_value) || asc::std::get_if<1>(&first) || !asc::std::holds_alternative<short>(second) ||
        first.index() != 0 || second.valueless_by_exception() || asc::std::get<0>(first) != 4 ||
        asc::std::get<short>(second) != -2)
        return 1;
    if (asc::std::visit(sum{}, first) != 4 || asc::std::visit(sum{}, first, second) != 2 ||
        asc::std::visit(sum{}, second, first, second) != 0 || asc::std::visit<long>(sum{}, second, first) != 2)
        return 2;
    if (!(first < second && first <= second && second > first && second >= first && first != second))
        return 3;
    swap(first, second);
    const auto copy = second;
    if (first.index() != 1 || asc::std::get_if<short>(&first) != &asc::std::get<1>(first) ||
        !asc::std::get_if<int>(&copy) || asc::std::get<int>(copy) != 4 || second != copy ||
        asc::std::hash<choice>{}(second) != asc::std::hash<choice>{}(copy))
        return 4;
    auto& stored = first.emplace<int>(12);
    if (&asc::std::get<0>(first) != &stored || asc::std::visit(sum{}, first) != 12)
        return 5;
    first.emplace<1>(static_cast<short>(3));
    return asc::std::get<1>(asc::std::move(first)) == 3 ? 0 : 6;  // NOLINT(build/include_what_you_use)
}

}  // namespace asc_stl_test_variant

#endif  // ASC_STL_TEST_VARIANT_DEVICE_CHECKS_H
