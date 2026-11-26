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

#ifndef ASC_STL_TEST_BIT_DEVICE_CHECKS_H
#define ASC_STL_TEST_BIT_DEVICE_CHECKS_H

#include <asc/std/bit>

namespace asc_stl_test_bit {
CANN_ASC_STL_API int check(int seed = 7)
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    // Include empty, full, alternating, and runs at either end of a byte.
    const unsigned patterns[] = {0, 255, 1, 2, 3, 127, 128, 129, 192, 254, 85, 170};
    for (unsigned offset = 0; offset < sizeof(patterns) / sizeof(*patterns); ++offset) {
        const unsigned x = patterns[(offset + static_cast<unsigned>(seed)) % (sizeof(patterns) / sizeof(*patterns))];
#else
    for (unsigned offset = 0; offset < 256; ++offset) {
        const unsigned x = (offset + static_cast<unsigned>(seed)) & 255u;
#endif
        const auto byte = static_cast<unsigned char>(x);
        int population = 0, leading = 0, trailing = 0, leading_ones = 0, trailing_ones = 0;
        for (unsigned bit = 0; bit < 8; ++bit)
            population += (x >> bit) & 1u;
        while (leading < 8 && !(x & (128u >> leading)))
            ++leading;
        while (trailing < 8 && !(x & (1u << trailing)))
            ++trailing;
        while (leading_ones < 8 && (x & (128u >> leading_ones)))
            ++leading_ones;
        while (trailing_ones < 8 && (x & (1u << trailing_ones)))
            ++trailing_ones;
        if (::asc::std::countl_zero(byte) != leading || ::asc::std::countr_zero(byte) != trailing ||
            ::asc::std::countl_one(byte) != leading_ones || ::asc::std::countr_one(byte) != trailing_ones ||
            ::asc::std::popcount(byte) != population || ::asc::std::has_single_bit(byte) != (population == 1) ||
            ::asc::std::bit_width(byte) != 8 - leading)
            return 1;
        unsigned floor = x ? 1u << (7 - leading) : 0;
        unsigned ceil = x < 2 ? 1 : floor << (floor != x);
        if (::asc::std::bit_floor(byte) != floor || (ceil <= 255 && ::asc::std::bit_ceil(byte) != ceil))
            return 2;
        for (int n = -8; n <= 8; ++n) {
            const unsigned s = static_cast<unsigned>(n) & 7;
            const unsigned left = ((x << s) | (x >> (8 - s))) & 255u;
            const unsigned right = ((x >> s) | (x << (8 - s))) & 255u;
            if (::asc::std::rotl(byte, n) != left || ::asc::std::rotr(byte, n) != right)
                return 3;
        }
    }
    if (::asc::std::byteswap(0x01020304U) != 0x04030201U ||
        ::asc::std::byteswap(0xff007f0123456789ULL) != 0x89674523017f00ffULL ||
        ::asc::std::bit_cast<unsigned>(-0.0F) != 0x80000000u)
        return 4;
    return 0;
}
}  // namespace asc_stl_test_bit

#endif  // ASC_STL_TEST_BIT_DEVICE_CHECKS_H
