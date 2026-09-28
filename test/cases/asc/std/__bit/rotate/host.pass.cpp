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

#include <asc/std/__bit/rotate.h>

#include <cassert>
#include <climits>
#include <cstdint>
#include <limits>

int main()
{
    constexpr std::uint8_t value8 = 0x1Eu;
    static_assert(asc::std::rotl(value8, 1) == 0x3Cu);
    static_assert(asc::std::rotr(value8, 1) == 0x0Fu);
    static_assert(asc::std::rotl(value8, 0) == 0x1Eu);
    static_assert(asc::std::rotl(value8, 8) == 0x1Eu);
    static_assert(asc::std::rotl(value8, 9) == 0x3Cu);
    static_assert(asc::std::rotl(value8, -1) == asc::std::rotr(value8, 1));
    static_assert(asc::std::rotr(value8, -1) == asc::std::rotl(value8, 1));
    static_assert(asc::std::rotl(value8, -8) == value8);
    static_assert(asc::std::rotr(value8, -17) == asc::std::rotl(value8, 1));
    static_assert(asc::std::rotl(value8, INT_MIN) == value8);
    static_assert(asc::std::rotr(value8, INT_MIN) == value8);
    static_assert(asc::std::rotl(value8, INT_MAX) == asc::std::rotr(value8, 1));

    constexpr std::uint32_t value32 = 0x0000FFFFu;
    static_assert(asc::std::rotl(value32, 16) == 0xFFFF0000u);
    static_assert(asc::std::rotr(value32, 16) == 0xFFFF0000u);
    static_assert(asc::std::rotl(value32, 1) == 0x0001FFFEu);
    static_assert(asc::std::rotr(value32, 1) == 0x80007FFFu);
    static_assert(asc::std::rotl(value32, -33) == asc::std::rotr(value32, 1));
    static_assert(asc::std::rotr(value32, -65) == asc::std::rotl(value32, 1));

    constexpr std::uint64_t value64 = 0x00000000FFFFFFFFull;
    static_assert(asc::std::rotl(value64, 32) == 0xFFFFFFFF00000000ull);
    static_assert(asc::std::rotr(value64, 32) == 0xFFFFFFFF00000000ull);
    static_assert(
        asc::std::rotl(std::numeric_limits<std::uint64_t>::max(), 37) == std::numeric_limits<std::uint64_t>::max());
    static_assert(
        asc::std::rotr(std::numeric_limits<std::uint64_t>::max(), 41) == std::numeric_limits<std::uint64_t>::max());

    // Repeated single-step rotations compose into any effective count.
    std::uint16_t accumulated = 0x0001u;
    for (int step = 0; step < 16; ++step) {
        accumulated = asc::std::rotl(accumulated, 1);
    }
    assert(accumulated == 0x0001u);
    return 0;
}
