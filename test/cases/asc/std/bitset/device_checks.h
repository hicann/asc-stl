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

#ifndef ASC_STL_TEST_BITSET_DEVICE_CHECKS_H
#define ASC_STL_TEST_BITSET_DEVICE_CHECKS_H

#include <asc/std/bitset>

namespace asc_stl_test_bitset {
template <unsigned N>
CANN_ASC_STL_API bool verify_shifts(unsigned first_shift, unsigned stride)
{
    asc::std::bitset<N> bits;
    for (unsigned i = 0; i < N; ++i)
        bits[i] = i % 3 == 1;
    const auto c = bits;
    for (unsigned shift = first_shift; shift <= N + 1; shift += stride) {
        const auto left = bits << shift;
        const auto right = bits >> shift;
        unsigned set = 0;
        for (unsigned i = 0; i < N; ++i) {
            if (left[i] != (i >= shift && (i - shift) % 3 == 1) || right[i] != (i + shift < N && (i + shift) % 3 == 1))
                return false;
            set += left[i] ? 1u : 0u;
        }
        if (set != left.count())
            return false;
    }
    auto all = bits;
    all.set();
    auto inverse = ~bits;
    return all.all() && all.size() == N && (c & inverse).none() && (c | inverse) == all && (c ^ all) == inverse &&
        inverse.flip() == bits && all.reset().none();
}
CANN_ASC_STL_API int check_partition(int seed, unsigned first_shift, unsigned stride)
{
    asc::std::bitset<5> small(static_cast<unsigned>(seed + 15));
    small[0] = small[1];
    small[2].flip();
    if (small.to_ulong() != 19 || small.to_ullong() != 19 || !small.any() || !~small[3])
        return 1;
    return verify_shifts<0>(first_shift, stride) && verify_shifts<1>(first_shift, stride) &&
            verify_shifts<31>(first_shift, stride) && verify_shifts<65>(first_shift, stride) ?
        0 :
        2;
}
CANN_ASC_STL_API int check(int seed = 7)
{
    return check_partition(seed, 0, 1);
}
}  // namespace asc_stl_test_bitset

#endif  // ASC_STL_TEST_BITSET_DEVICE_CHECKS_H
