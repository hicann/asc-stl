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

#ifndef ASC_STL_TEST_RANGES_SEQUENCE_H
#define ASC_STL_TEST_RANGES_SEQUENCE_H

#include <asc/std/algorithm>
#include <asc/std/iterator>
#include <asc/std/functional>
#include <asc/std/ranges>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <random>
#include <type_traits>
#include <vector>

namespace asc_stl_ranges_sequence_test {

struct Sentinel {
    int* p;
};
bool operator==(int* p, Sentinel s)
{
    return p == s.p;
}
bool operator==(Sentinel s, int* p)
{
    return p == s;
}
bool operator!=(int* p, Sentinel s)
{
    return !(p == s);
}
bool operator!=(Sentinel s, int* p)
{
    return !(p == s);
}
struct Item {
    int value;
};
struct Even {
    constexpr bool operator()(int x) const
    {
        return x % 2 == 0;
    }
};
constexpr bool constexpr_probe()
{
    int in[] = {1, 2, 3, 4}, out[4]{};
    const auto copied = asc::std::ranges::copy(in, out);
    if (copied.in != in + 4 || copied.out != out + 4)
        return false;
    if (asc::std::ranges::fill(out, 6) != out + 4 || out[3] != 6)
        return false;
    const auto mapped = asc::std::ranges::transform(in, out, [](int x) { return x * 2; });
    if (mapped.out != out + 4 || out[3] != 8)
        return false;
    int yes[4]{}, no[4]{};
    auto part = asc::std::ranges::partition_copy(in, yes, no, Even{});
    if (part.out1 != yes + 2 || part.out2 != no + 2 || yes[0] != 2 || no[1] != 3)
        return false;
    auto tail = asc::std::ranges::remove_if(in, Even{});
    return tail.begin() == in + 2 && tail.end() == in + 4 && in[1] == 3;
}
static_assert(constexpr_probe(), "constexpr sequence semantics");
using CopyTemp = decltype(asc::std::ranges::copy(std::vector<int>{}, static_cast<int*>(nullptr)));
static_assert(std::is_same<decltype(CopyTemp::in), asc::std::ranges::dangling>::value,
    "no dangling iterator from owning temporary");
static_assert(
    std::is_same<decltype(asc::std::ranges::remove_if(std::vector<int>{}, Even{})), asc::std::ranges::dangling>::value,
    "remove temporary is dangling");
static_assert(!std::is_invocable<decltype(asc::std::ranges::copy), const int (&)[2], const int*>::value,
    "reject const destination");
static_assert(!std::is_invocable<decltype(asc::std::ranges::remove_if), const int (&)[2], Even>::value,
    "reject immutable removal");

int run()
{
    assert(constexpr_probe());
    std::mt19937 rng(20261105);
    for (int trial = 0; trial < 2000; ++trial) {
        int n = trial % 33;
        std::vector<int> src(n), expected(n), actual(n), yes(n), no(n), refyes(n), refno(n);
        for (int& x : src)
            x = static_cast<int>(rng() % 100) - 50;
        auto* first = src.data();
        auto* last = n ? first + n : first;
        auto end = asc::std::ranges::copy(first, Sentinel{last}, actual.data());
        assert(actual == src && end.in == last);
        if (n)
            assert(end.out == actual.data() + n);
        auto fill = asc::std::ranges::fill(actual, 17);
        assert(std::all_of(actual.begin(), actual.end(), [](int x) { return x == 17; }));
        assert(fill == actual.end());
        auto op = [](int x) { return x * x - 3; };
        std::transform(src.begin(), src.end(), expected.begin(), op);
        asc::std::ranges::transform(src, actual.data(), op);
        assert(actual == expected);
        auto ref = std::partition_copy(src.begin(), src.end(), refyes.begin(), refno.begin(), Even{});
        auto part = asc::std::ranges::partition_copy(first, Sentinel{last}, yes.data(), no.data(), Even{});
        const auto ny = ref.first - refyes.begin(), nn = ref.second - refno.begin();
        assert(std::equal(refyes.begin(), ref.first, yes.begin()) && std::equal(refno.begin(), ref.second, no.begin()));
        if (n)
            assert(part.out1 == yes.data() + ny && part.out2 == no.data() + nn);
        actual = expected = src;
        auto refend = std::remove_if(expected.begin(), expected.end(), Even{});
        int calls = 0;
        auto removed = asc::std::ranges::remove_if(actual, [&](int x) {
            ++calls;
            return Even{}(x);
        });
        assert(calls == n && removed.end() == actual.end());
        assert(removed.begin() - actual.begin() == refend - expected.begin());
        assert(std::equal(expected.begin(), refend, actual.begin()));
    }
    Item input[] = {{5}, {2}, {7}, {4}};
    int projected[4]{};
    auto mapped = asc::std::ranges::transform(input, projected, asc::std::identity{}, &Item::value);
    assert(mapped.in == input + 4 && projected[2] == 7);
    Item yes[4], no[4];
    auto part = asc::std::ranges::partition_copy(input, yes, no, Even{}, &Item::value);
    assert(part.out1 == yes + 2 && yes[0].value == 2 && no[1].value == 7);
    auto removed = asc::std::ranges::remove_if(input, Even{}, &Item::value);
    assert(removed.begin() == input + 2 && input[1].value == 7);
    std::unique_ptr<int> owned[4];
    for (int i = 0; i < 4; ++i)
        owned[i] = std::make_unique<int>(i);
    auto moved = asc::std::ranges::remove_if(owned, [](const auto& p) { return *p % 2 == 0; });
    assert(moved.begin() == owned + 2 && *owned[0] == 1 && *owned[1] == 3);
    int empty[1] = {9};
    assert(asc::std::ranges::copy(empty, empty, empty).out == empty);
    assert(asc::std::ranges::fill(empty, empty, 1) == empty && empty[0] == 9);
    asc::std::ranges::in_out_result<int*, int*> r{empty, empty};
    asc::std::ranges::in_out_result<const int*, const int*> converted = r;
    assert(converted.in == empty);
#if __cplusplus >= 202002L
    std::vector<int> inserted;
    asc::std::ranges::copy(projected, asc::std::back_inserter(inserted));
    assert(inserted == std::vector<int>({5, 2, 7, 4}));
    std::vector<int> odds, evens;
    asc::std::ranges::partition_copy(projected, asc::std::back_inserter(evens), asc::std::back_inserter(odds), Even{});
    assert(evens == std::vector<int>({2, 4}) && odds == std::vector<int>({5, 7}));
#endif
    std::cout << "SEQUENCE_PASS 2000 randomized cases; "
                 "constexpr/sentinel/projection/stability/move/dangling/constraints/results\n";
    return 0;
}
}  // namespace asc_stl_ranges_sequence_test

#endif  // ASC_STL_TEST_RANGES_SEQUENCE_H
