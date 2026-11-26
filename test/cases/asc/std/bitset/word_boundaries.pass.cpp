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

#include <asc/std/bitset>

#include <bitset>
#include <cstddef>
#include <iostream>

namespace {

template <std::size_t N>
bool equals(const asc::std::bitset<N>& actual, const std::bitset<N>& expected)
{
    if (actual.size() != expected.size() || actual.count() != expected.count() || actual.all() != expected.all() ||
        actual.any() != expected.any() || actual.none() != expected.none())
        return false;
    for (std::size_t i = 0; i < N; ++i) {
        if (actual[i] != expected[i])
            return false;
    }
    return true;
}

template <std::size_t N>
bool check_pattern(std::size_t phase)
{
    asc::std::bitset<N> left, right;
    std::bitset<N> expected_left, expected_right;
    for (std::size_t i = 0; i < N; ++i) {
        left[i] = expected_left[i] = (i + phase) % 7 < 3;
        right[i] = expected_right[i] = (3 * i + phase) % 11 < 6;
    }
    if (!equals(left, expected_left) || !equals(~left, ~expected_left) ||
        !equals(left & right, expected_left & expected_right) ||
        !equals(left | right, expected_left | expected_right) || !equals(left ^ right, expected_left ^ expected_right))
        return false;

    const std::size_t shifts[] = {0, 1, 31, 63, 64, 65, 127, 128, N, N + 1};
    for (const auto count : shifts) {
        auto moved = left;
        auto expected = expected_left;
        moved <<= count;
        expected <<= count;
        if (!equals(moved, expected) || !equals(left << count, expected))
            return false;
        moved = left;
        expected = expected_left;
        moved >>= count;
        expected >>= count;
        if (!equals(moved, expected) || !equals(left >> count, expected))
            return false;
    }
    if constexpr (N != 0) {
        const auto offset = (31 + phase) % N;
        auto bit = left[offset];
        if (~bit != !expected_left[offset])
            return false;
        bit.flip();
        expected_left[offset].flip();
        left[N - 1] = left[offset];
        expected_left[N - 1] = expected_left[offset];
        if (!equals(left, expected_left))
            return false;
    }
    left.set();
    expected_left.set();
    if (!equals(left, expected_left))
        return false;
    left.flip();
    expected_left.flip();
    if (!equals(left, expected_left))
        return false;
    right.reset();
    return right.none() && left == right && !(left != right);
}

template <std::size_t N>
bool check_size()
{
    for (std::size_t phase = 0; phase < 9; ++phase) {
        if (!check_pattern<N>(phase)) {
            std::cerr << "Bitset mismatch for size " << N << " and pattern " << phase << '\n';
            return false;
        }
    }
    constexpr unsigned long long seed = 0x8000000000000001ULL;
    return equals(asc::std::bitset<N>(seed), std::bitset<N>(seed));
}

}  // namespace

int main()
{
    return check_size<0>() && check_size<1>() && check_size<7>() && check_size<31>() && check_size<32>() &&
            check_size<63>() && check_size<64>() && check_size<65>() && check_size<127>() && check_size<128>() &&
            check_size<129>() ?
        0 :
        1;
}
