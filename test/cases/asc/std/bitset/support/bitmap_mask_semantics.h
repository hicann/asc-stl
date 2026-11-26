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

#ifndef ASC_STL_TEST_SUPPORT_BITMAP_MASK_SEMANTICS_H
#define ASC_STL_TEST_SUPPORT_BITMAP_MASK_SEMANTICS_H

#include <asc/std/bit>
#include <asc/std/bitset>

namespace asc_stl_bitmap_mask_test {
CANN_ASC_STL_API constexpr int evaluate(unsigned long long packed = ~0ULL)
{
    asc::std::bitset<0> empty(packed);
    if (empty.to_ullong() != 0 || empty.to_ulong() != 0 || empty.count() != 0 || !empty.none() || !empty.all()) {
        return 1;
    }
    empty.set().flip().reset();
    empty <<= static_cast<asc::std::size_t>(-1);
    empty >>= 0;
    if (empty.to_ullong() != 0 || (~empty).to_ullong() != 0 || (empty | empty).to_ulong() != 0) {
        return 2;
    }
    asc::std::bitset<65> peaks;
    peaks[0] = true;
    peaks[63] = true;
    peaks[64] = true;
    const auto neighbors = (peaks << 1) | (peaks >> 1);
    if (neighbors.count() != 4 || !neighbors[1] || !neighbors[62] || !neighbors[63] || !neighbors[64]) {
        return 3;
    }
    auto mask = peaks;
    mask.set();
    if (mask.count() != 65 || !mask.all() || mask.flip().any() || (peaks << 65).any() || (peaks >> 66).any()) {
        return 4;
    }
    const asc::std::bitset<33> tail(~0ULL);
    const auto word = tail.to_ullong();
    if (word != (1ULL << 33) - 1 || asc::std::popcount(word) != 33 || asc::std::countl_zero(word) != 31 ||
        asc::std::countr_zero(word) != 0 || asc::std::countr_zero(0ULL) != 64) {
        return 5;
    }
    return 0;
}
}  // namespace asc_stl_bitmap_mask_test

#endif  // ASC_STL_TEST_SUPPORT_BITMAP_MASK_SEMANTICS_H
