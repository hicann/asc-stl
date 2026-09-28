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

#include <asc/cmath>

#include <cassert>
#include <cstdint>
#include <limits>

int main()
{
    // ceil_div: positive operands round towards positive infinity.
    assert(asc::ceil_div(7, 3) == 3);
    assert(asc::ceil_div(6, 3) == 2);
    assert(asc::ceil_div(0, 5) == 0);
    assert(asc::ceil_div(1, 5) == 1);
    assert(asc::ceil_div(7u, 2u) == 4u);
    assert(asc::ceil_div(std::uint64_t{0xFFFFFFFFFFFFFFF5ull}, std::uint64_t{10ull}) ==
        std::uint64_t{0x1999999999999999ull});
    assert(asc::ceil_div(std::numeric_limits<std::int64_t>::max(), std::int64_t{1}) ==
        std::numeric_limits<std::int64_t>::max());

    // Enumerations mix with integers through their underlying value.
    enum Color : unsigned int { RED = 7 };
    enum Level : int { LOW = 3 };
    assert(asc::ceil_div(RED, LOW) == 3);
    assert(asc::ceil_div(7, LOW) == 3);
    assert(asc::ceil_div(RED, 3) == 3);

    // floor_div: truncation rounds towards negative infinity.
    assert(asc::floor_div(7, 3) == 2);
    assert(asc::floor_div(-7, 3) == -3);
    assert(asc::floor_div(6, 3) == 2);
    assert(asc::floor_div(-6, 3) == -2);
    assert(asc::floor_div(std::int64_t{-1}, std::int64_t{1}) == std::int64_t{-1});
    assert(asc::floor_div(7u, 3u) == 2u);

    // round_up: smallest multiple of b not below a.
    assert(asc::round_up(7, 3) == 9);
    assert(asc::round_up(6, 3) == 6);
    assert(asc::round_up(0, 4) == 0);
    assert(asc::round_up(1, 4) == 4);
    assert(asc::round_up(std::uint64_t{1000}, std::uint64_t{256}) == std::uint64_t{1024});

    // integer_log2: floor of the base-2 logarithm.
    assert(asc::integer_log2(1) == 0);
    assert(asc::integer_log2(2) == 1);
    assert(asc::integer_log2(3) == 1);
    assert(asc::integer_log2(4) == 2);
    assert(asc::integer_log2(255) == 7);
    assert(asc::integer_log2(std::uint64_t{1ull << 63}) == 63);
    assert(asc::integer_log2(std::numeric_limits<std::uint32_t>::max()) == 31);

    // integer_sqrt: the largest r with r * r <= value.
    assert(asc::integer_sqrt(0) == 0);
    assert(asc::integer_sqrt(1) == 1);
    assert(asc::integer_sqrt(3) == 1);
    assert(asc::integer_sqrt(4) == 2);
    assert(asc::integer_sqrt(24) == 4);
    assert(asc::integer_sqrt(25) == 5);
    const std::uint64_t root = asc::integer_sqrt(std::numeric_limits<std::uint64_t>::max());
    assert(root == 0xFFFFFFFFull);
    assert(root * root <= std::numeric_limits<std::uint64_t>::max());

    // integer_pow: base raised to a non-negative exponent.
    assert(asc::integer_pow(2, 10) == 1024);
    assert(asc::integer_pow(3, 0) == 1);
    assert(asc::integer_pow(0, 0) == 1);
    assert(asc::integer_pow(5u, 3u) == 125u);
    assert(asc::integer_pow(std::int64_t{-2}, 3) == -8);
    assert(asc::integer_pow(std::int64_t{-2}, 4) == 16);
    static_assert(asc::integer_pow<int>(50000, 1) == 50000);

    // mul_hi: high half of the unsigned product, no __int128 involved.
    assert(asc::mul_hi(std::uint32_t{0xFFFFFFFFu}, std::uint32_t{0xFFFFFFFFu}) == std::uint32_t{0xFFFFFFFEu});
    assert(asc::mul_hi(std::uint32_t{0xFFFFFFFFu}, std::uint32_t{1u}) == 0u);
    assert(asc::mul_hi(std::uint64_t{0xFFFFFFFFFFFFFFFFull}, std::uint64_t{0xFFFFFFFFFFFFFFFFull}) ==
        std::uint64_t{0xFFFFFFFFFFFFFFFEull});
    assert(asc::mul_hi(std::uint64_t{0x100000000ull}, std::uint64_t{0x100000000ull}) == std::uint64_t{1ull});
    assert(asc::mul_hi(std::uint8_t{0xFFu}, std::uint8_t{0xFFu}) == std::uint8_t{0xFEu});

    // sincos writes both results through output pointers on Host.
    float sine_f = 0.0f;
    float cosine_f = 0.0f;
    asc::sincos(0.0f, &sine_f, &cosine_f);
    assert(sine_f == 0.0f && cosine_f == 1.0f);
    asc::sincos(3.14159265f / 2.0f, &sine_f, &cosine_f);
    assert(sine_f > 0.999f && sine_f < 1.001f);
    assert(cosine_f > -0.001f && cosine_f < 0.001f);

    double sine_d = 0.0;
    double cosine_d = 0.0;
    asc::sincos(1.0, &sine_d, &cosine_d);
    assert(sine_d > 0.841 && sine_d < 0.842);
    assert(cosine_d > 0.540 && cosine_d < 0.541);

    long double sine_l = 0.0L;
    long double cosine_l = 0.0L;
    asc::sincos(0.5L, &sine_l, &cosine_l);
    assert(sine_l > 0.479L && sine_l < 0.480L);
    assert(cosine_l > 0.877L && cosine_l < 0.878L);

    // The integer convenience overload converts through double on Host only.
    double sine_i = 0.0;
    double cosine_i = 0.0;
    asc::sincos(1, &sine_i, &cosine_i);
    assert(sine_i > 0.841 && sine_i < 0.842);
    assert(cosine_i > 0.540 && cosine_i < 0.541);

    // Every integer tool stays a constant expression.
    static_assert(asc::ceil_div(7, 3) == 3);
    static_assert(asc::floor_div(-7, 3) == -3);
    static_assert(asc::round_up(7, 4) == 8);
    static_assert(asc::integer_log2(255) == 7);
    static_assert(asc::integer_sqrt(24) == 4);
    static_assert(asc::integer_pow(2, 10) == 1024);
    static_assert(asc::mul_hi(std::uint8_t{0xFF}, std::uint8_t{0xFF}) == std::uint8_t{0xFE});
    return 0;
}
