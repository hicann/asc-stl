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

#ifndef ASC_STL_TEST_CSTDDEF_DEVICE_CHECKS_H
#define ASC_STL_TEST_CSTDDEF_DEVICE_CHECKS_H

#include <asc/std/cstddef>

namespace asc_stl_test_cstddef {

CANN_ASC_STL_API int check(int seed = 7)
{
    using asc::std::byte;
    using asc::std::to_integer;
    const unsigned n = static_cast<unsigned>(seed) & 255U;
    const auto input = static_cast<byte>(n);
    for (unsigned shift = 0; shift < 8; ++shift) {
        byte value = input;
        value <<= shift;
        if (to_integer<unsigned>(value) != ((n << shift) & 255U) || value != (input << shift))
            return 1;
        value = input;
        value >>= shift;
        if (to_integer<unsigned>(value) != (n >> shift) || value != (input >> shift))
            return 2;
    }
    const byte mask{0xa5};
    auto v = input;
    v |= mask;
    if (v != (input | mask) || to_integer<unsigned>(v) != (n | 0xa5U))
        return 3;
    v &= mask;
    if (v != mask || to_integer<unsigned>(input & mask) != (n & 0xa5U))
        return 4;
    v ^= input;
    return v != (mask ^ input) || to_integer<unsigned>(~input) != ((~n) & 255U);
}

}  // namespace asc_stl_test_cstddef

#endif  // ASC_STL_TEST_CSTDDEF_DEVICE_CHECKS_H
