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

#include <asc/std/__functional/bind.h>

#include <cassert>

int main()
{
    using asc::std::placeholders::_1;
    using asc::std::placeholders::_10;
    using asc::std::placeholders::_2;

    static_assert(asc::std::is_placeholder_v<decltype(_1)> == 1);
    static_assert(asc::std::is_placeholder_v<decltype(_10)> == 10);
    static_assert(asc::std::is_placeholder_v<int> == 0);
    static_assert(!asc::std::is_bind_expression_v<int>);
    static_assert(asc::std::is_same_v<decltype(asc::std::is_bind_expression_v<int>), const bool>);
    static_assert(!asc::std::is_bind_expression<int>::value);

    struct Summer {
        int base;
        int add(int left, int right) const
        {
            return base + left + right;
        }
    };
    Summer summer{10};
    auto bound_member = asc::std::bind(&Summer::add, &summer, _1, 100);
    assert(bound_member(5) == 115);

    auto multiply = asc::std::bind([](int left, int right) { return left * right; }, _1, _2);
    assert(multiply(6, 7) == 42);
    static_assert(asc::std::is_bind_expression_v<decltype(multiply)>);

    auto nested = asc::std::bind(
        [](int value) { return value + 1; }, asc::std::bind([](int left, int right) { return left * right; }, _1, _2));
    assert(nested(6, 7) == 43);
    static_assert(asc::std::is_bind_expression_v<decltype(nested)>);

    int shared = 1;
    asc::std::reference_wrapper<int> wrapped(shared);
    auto through_reference = asc::std::bind([](int& value) { return ++value; }, wrapped);
    assert(through_reference() == 2 && shared == 2);

    auto reorder = asc::std::bind([](int left, int right) { return left - right; }, _2, _1);
    assert(reorder(10, 3) == -7);
    const auto constant_bound = asc::std::bind([](int left, int right) { return left + right; }, 40, 2);
    assert(constant_bound() == 42);

    auto returning = asc::std::bind<long>([](int value) { return value * 1000000; }, 3);
    assert(returning() == 3000000L);
    static_assert(asc::std::is_bind_expression_v<decltype(returning)>);

    return 0;
}
