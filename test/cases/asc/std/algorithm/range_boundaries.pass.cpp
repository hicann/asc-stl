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

#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>

namespace {

namespace ast = asc::std;

constexpr int kPadding = 431;
constexpr std::size_t kCapacity = 257;
using values = std::array<int, kCapacity + 1>;

struct order {
    bool descending;
    constexpr bool operator()(int left, int right) const
    {
        return descending ? left > right : left < right;
    }
};

void make_input(values& data, std::size_t count, unsigned pattern)
{
    data.fill(kPadding);
    unsigned state = 0x6D2B79F5u + pattern;
    for (std::size_t i = 0; i < count; ++i) {
        state = state * 1664525u + 1013904223u;
        if (pattern == 0)
            data[i] = static_cast<int>(i);
        else if (pattern == 1)
            data[i] = static_cast<int>(count - i);
        else if (pattern == 2)
            data[i] = 7;
        else if (pattern == 3)
            data[i] = static_cast<int>((state >> 16) % 7) - 3;
        else
            data[i] = static_cast<int>(state >> 16) - 32768;
    }
}

bool check_selection(const values& input, std::size_t count, order compare)
{
    auto expected = input;
    std::sort(expected.begin(), expected.begin() + count, compare);
    auto sorted = input;
    ast::sort(sorted.begin(), sorted.begin() + count, compare);
    if (sorted != expected)
        return false;

    const std::size_t positions[] = {0, count / 2, count == 0 ? 0 : count - 1, count};
    for (auto position : positions) {
        auto actual = input;
        ast::partial_sort(actual.begin(), actual.begin() + position, actual.begin() + count, compare);
        if (!std::equal(actual.begin(), actual.begin() + position, expected.begin()) || actual[count] != kPadding)
            return false;

        actual = input;
        ast::nth_element(actual.begin(), actual.begin() + position, actual.begin() + count, compare);
        if (position < count) {
            const auto pivot = actual[position];
            if (pivot != expected[position] ||
                !std::none_of(actual.begin(), actual.begin() + position, [&](int v) { return compare(pivot, v); }) ||
                !std::none_of(
                    actual.begin() + position, actual.begin() + count, [&](int v) { return compare(v, pivot); }))
                return false;
        }
        std::sort(actual.begin(), actual.begin() + count, compare);
        if (actual != expected)
            return false;

        values output;
        output.fill(kPadding);
        auto end = ast::partial_sort_copy(
            input.begin(), input.begin() + count, output.begin(), output.begin() + position, compare);
        if (end != output.begin() + position || output[position] != kPadding ||
            !std::equal(output.begin(), end, expected.begin()))
            return false;
    }
    return true;
}

struct row {
    int key;
    std::size_t position;

    friend bool operator==(const row& left, const row& right)
    {
        return left.key == right.key && left.position == right.position;
    }
};

bool check_stability(const values& keys, std::size_t count)
{
    constexpr auto compare = [](const row& left, const row& right) { return left.key < right.key; };
    constexpr auto predicate = [](const row& value) { return value.key % 2 == 0; };
    std::array<row, kCapacity + 1> source{};
    for (std::size_t i = 0; i <= count; ++i)
        source[i] = {keys[i], i};

    auto expected = source;
    auto actual = source;
    std::stable_sort(expected.begin(), expected.begin() + count, compare);
    ast::stable_sort(actual.begin(), actual.begin() + count, compare);
    if (actual != expected)
        return false;
    expected = source;
    actual = source;
    const auto expected_mid = std::stable_partition(expected.begin(), expected.begin() + count, predicate);
    const auto actual_mid = ast::stable_partition(actual.begin(), actual.begin() + count, predicate);
    if (actual != expected || actual_mid - actual.begin() != expected_mid - expected.begin())
        return false;

    const std::size_t boundaries[] = {0, count / 3, 2 * count / 3, count};
    for (auto middle : boundaries) {
        expected = source;
        std::stable_sort(expected.begin(), expected.begin() + middle, compare);
        std::stable_sort(expected.begin() + middle, expected.begin() + count, compare);
        actual = expected;
        std::inplace_merge(expected.begin(), expected.begin() + middle, expected.begin() + count, compare);
        ast::inplace_merge(actual.begin(), actual.begin() + middle, actual.begin() + count, compare);
        if (actual != expected)
            return false;
    }
    return true;
}

template <class Actual, class Reference>
bool check_set_output(Actual implementation, Reference oracle, const values& left, std::size_t length,
    const values& right, std::size_t other_length, order compare)
{
    std::array<int, 2 * kCapacity + 2> actual, expected;
    actual.fill(kPadding);
    expected.fill(kPadding);
    const auto* actual_end = implementation(
        left.begin(), left.begin() + length, right.begin(), right.begin() + other_length, actual.begin(), compare);
    const auto* expected_end = oracle(
        left.begin(), left.begin() + length, right.begin(), right.begin() + other_length, expected.begin(), compare);
    return actual == expected && actual_end - actual.begin() == expected_end - expected.begin();
}

bool check_sorted_ranges(values left, std::size_t count, values right, std::size_t other_length, order compare)
{
    std::sort(left.begin(), left.begin() + count, compare);
    std::sort(right.begin(), right.begin() + other_length, compare);
    const auto end = left.begin() + count;
    const auto other_end = right.begin() + other_length;
    const int queries[] = {-9, -3, -2, 0, 1, 3, 6, 900};
    for (auto query : queries) {
        const auto expected = std::equal_range(left.cbegin(), left.cbegin() + count, query, compare);
        const auto actual = ast::equal_range(left.cbegin(), left.cbegin() + count, query, compare);
        if (actual.first != expected.first || actual.second != expected.second ||
            ast::binary_search(left.begin(), end, query, compare) != (expected.first != expected.second) ||
            ast::lower_bound(left.begin(), end, query, compare) != expected.first ||
            ast::upper_bound(left.begin(), end, query, compare) != expected.second)
            return false;
    }
    if (ast::includes(left.begin(), end, right.begin(), other_end, compare) !=
        std::includes(left.begin(), end, right.begin(), other_end, compare))
        return false;
    const auto check = [&](auto implementation, auto oracle) {
        return check_set_output(implementation, oracle, left, count, right, other_length, compare);
    };
    return check([](auto... args) { return ast::merge(args...); }, [](auto... args) { return std::merge(args...); }) &&
        check([](auto... args) { return ast::set_union(args...); },
            [](auto... args) { return std::set_union(args...); }) &&
        check([](auto... args) { return ast::set_intersection(args...); },
            [](auto... args) { return std::set_intersection(args...); }) &&
        check([](auto... args) { return ast::set_difference(args...); },
            [](auto... args) { return std::set_difference(args...); }) &&
        check([](auto... args) { return ast::set_symmetric_difference(args...); },
            [](auto... args) { return std::set_symmetric_difference(args...); });
}

}  // namespace

int main()
{
    const std::size_t lengths[] = {0, 1, 2, 3, 15, 23, 24, 25, 63, 64, 65, 127, 128, 129, 256, 257};
    values left{}, right{};
    for (const auto count : lengths) {
        for (unsigned pattern = 0; pattern < 6; ++pattern) {
            make_input(left, count, pattern);
            make_input(right, count / 2, (pattern + 1) % 6);
            if (!check_selection(left, count, {false}) || !check_selection(left, count, {true}) ||
                !check_stability(left, count) || !check_sorted_ranges(left, count, right, count / 2, {false}) ||
                !check_sorted_ranges(left, count, right, count / 2, {true})) {
                std::cerr << "Algorithm result mismatch for length " << count << " and pattern " << pattern << '\n';
                return 1;
            }
        }
    }
    return 0;
}
