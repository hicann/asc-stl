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
#include <climits>
#include <type_traits>
#include <utility>

template <std::size_t N, class = void>
struct accepts_ulong_width_one : std::false_type {};
template <std::size_t N>
struct accepts_ulong_width_one<N, std::void_t<decltype(std::declval<asc::std::bitset<N>>().template to_ulong<1>())>>
    : std::true_type {};
template <std::size_t N, class = void>
struct accepts_ullong_width_one : std::false_type {};
template <std::size_t N>
struct accepts_ullong_width_one<N, std::void_t<decltype(std::declval<asc::std::bitset<N>>().template to_ullong<1>())>>
    : std::true_type {};

static_assert(accepts_ulong_width_one<sizeof(unsigned long) * CHAR_BIT>::value);
static_assert(accepts_ullong_width_one<sizeof(unsigned long long) * CHAR_BIT>::value);
static_assert(!accepts_ulong_width_one<sizeof(unsigned long) * CHAR_BIT + 1>::value);
static_assert(!accepts_ullong_width_one<sizeof(unsigned long long) * CHAR_BIT + 1>::value);

template <std::size_t N>
bool compare(unsigned long long seed)
{
    asc::std::bitset<N> a(seed);
    std::bitset<N> b(seed);
    for (std::size_t shift = 0; shift <= N + 1; ++shift) {
        const auto left = a << shift;
        const auto right = a >> shift;
        const auto expected_left = b << shift;
        const auto expected_right = b >> shift;
        if (left.count() != expected_left.count() || right.count() != expected_right.count())
            return false;
        for (std::size_t i = 0; i < N; ++i) {
            if (left[i] != expected_left[i] || right[i] != expected_right[i])
                return false;
        }
        if constexpr (N <= sizeof(unsigned long long) * CHAR_BIT) {
            if (left.to_ullong() != expected_left.to_ullong() || right.to_ullong() != expected_right.to_ullong())
                return false;
        }
        if constexpr (N <= sizeof(unsigned long) * CHAR_BIT) {
            if (left.to_ulong() != expected_left.to_ulong() || right.to_ulong() != expected_right.to_ulong())
                return false;
        }
    }
    return true;
}

int main()
{
    const unsigned long long seeds[] = {0, 1, 0x8000000180000001ULL, ~0ULL};
    for (auto seed : seeds) {
        if (!compare<0>(seed) || !compare<1>(seed) || !compare<63>(seed) || !compare<64>(seed) || !compare<65>(seed) ||
            !compare<129>(seed))
            return 1;
    }
    return 0;
}
