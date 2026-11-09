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

#include <asc/std/algorithm>
#include <asc/std/functional>
#include <asc/std/type_traits>
#include <algorithm>
#include <array>
#include <cassert>
#include <random>
#include <vector>
#include "support/ranges_find_tests.h"
#include "support/ranges_fold_tests.h"
#include "support/ranges_sequence_tests.h"

namespace {
struct Record {
    int value;
};
struct Even {
    constexpr bool operator()(int x) const
    {
        return x % 2 == 0;
    }
};
struct Combine {
    constexpr int operator()(int x, int y) const
    {
        return x * 3 + y;
    }
};
void check_remove_if(const std::vector<int>& input)
{
    auto expected = input;
    auto actual = input;
    auto new_end = std::remove_if(expected.begin(), expected.end(), Even{});
    int calls = 0;
    auto removed = asc::std::ranges::remove_if(actual, [&](int value) {
        ++calls;
        return Even{}(value);
    });
    assert(calls == static_cast<int>(input.size()));
    assert(removed.end() == actual.end());
    assert(removed.begin() - actual.begin() == new_end - expected.begin());
    assert(std::equal(expected.begin(), new_end, actual.begin()));
}
}  // namespace

int main()
{
    assert(asc_stl_ranges_find_test::run() == 0);
    assert(asc_stl_ranges_fold_test::run() == 0);
    assert(asc_stl_ranges_sequence_test::run() == 0);
    check_remove_if({});
    check_remove_if({2, 4, 6});
    check_remove_if({1, 3, 5});
    std::mt19937 random(83);
    for (int n = 0; n <= 32; ++n) {
        for (int trial = 0; trial < 64; ++trial) {
            std::vector<int> input(n), expected(n), actual(n), right(n / 2), binary(n);
            for (int& value : input)
                value = static_cast<int>(random() % 100) - 50;
            for (int& value : right)
                value = static_cast<int>(random() % 100) - 50;
            check_remove_if(input);
            auto end = std::copy_if(input.begin(), input.end(), expected.begin(), Even{});
            auto copied = asc::std::ranges::copy_if(input, actual.begin(), Even{});
            assert(copied.in == input.end() && copied.out - actual.begin() == end - expected.begin());
            assert(std::equal(expected.begin(), end, actual.begin()));
            end = std::remove_copy_if(input.begin(), input.end(), expected.begin(), Even{});
            auto removed = asc::std::ranges::remove_copy_if(input, actual.begin(), Even{});
            assert(removed.in == input.end() && removed.out - actual.begin() == end - expected.begin());
            assert(std::equal(expected.begin(), end, actual.begin()));
            auto result = asc::std::ranges::transform(input, right, binary.begin(), Combine{});
            assert(result.in1 == input.begin() + right.size() && result.in2 == right.end());
            assert(result.out == binary.begin() + right.size());
            for (unsigned i = 0; i < right.size(); ++i)
                assert(binary[i] == input[i] * 3 + right[i]);
        }
    }
    Record records[] = {{1}, {2}, {3}, {4}}, selected[4]{}, rejected[4]{};
    auto copied = asc::std::ranges::copy_if(records, selected, Even{}, &Record::value);
    auto removed = asc::std::ranges::remove_copy_if(records, rejected, Even{}, &Record::value);
    assert(copied.out == selected + 2 && selected[0].value == 2 && selected[1].value == 4);
    assert(removed.out == rejected + 2 && rejected[0].value == 1 && rejected[1].value == 3);
    int transformed[4]{};
    auto mapped =
        asc::std::ranges::transform(records, selected, transformed, Combine{}, &Record::value, &Record::value);
    assert(mapped.in1 == records + 4 && transformed[0] == 5 && transformed[1] == 10);
    using Temp = decltype(asc::std::ranges::copy_if(std::vector<int>{}, static_cast<int*>(nullptr), Even{}));
    static_assert(asc::std::is_same_v<decltype(Temp::in), asc::std::ranges::dangling>);
    static_assert(!asc::std::is_invocable_v<decltype(asc::std::ranges::copy_if), const int(&)[2], const int*, Even>);
    static_assert(
        !asc::std::is_invocable_v<decltype(asc::std::ranges::remove_copy_if), const int(&)[2], const int*, Even>);
}
