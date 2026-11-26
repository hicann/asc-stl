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

#ifndef ASC_STL_TEST_STANDARD_NUMERIC_SEMANTICS_H
#define ASC_STL_TEST_STANDARD_NUMERIC_SEMANTICS_H

#include <asc/std/bit>
#include <asc/std/functional>
#include <asc/std/limits>
#include <asc/std/numeric>
#include <asc/std/random>

namespace asc_stl_standard_numeric_test {

namespace ast = asc::std;

struct twice {
    CANN_ASC_STL_API int operator()(int value) const
    {
        return value * 2;
    }
};

CANN_ASC_STL_API int evaluate_numeric(int seed)
{
    const int input[] = {seed, seed + 1, seed + 2, seed + 3};
    const int weights[] = {1, 0, 1, 0};
    int differences[4]{}, exclusive[4]{}, inclusive[4]{}, transformed[4]{};
    const auto* const end = input + 4;
    if (ast::adjacent_difference(input, end, differences) != differences + 4 ||
        ast::exclusive_scan(input, end, exclusive, 3) != exclusive + 4 ||
        ast::inclusive_scan(input, end, inclusive) != inclusive + 4 ||
        ast::transform_inclusive_scan(input, end, transformed, ast::plus<int>{}, twice{}, 5) != transformed + 4)
        return 1;
    int sum = 0;
    for (int i = 0; i < 4; ++i) {
        const int previous = sum;
        sum += input[i];
        if (differences[i] != (i == 0 ? seed : 1) || exclusive[i] != previous + 3 || inclusive[i] != sum ||
            transformed[i] != 2 * sum + 5)
            return 2;
    }
    if (ast::inner_product(input, end, weights, 7) != 2 * seed + 9 || ast::reduce(input, end, 5) != sum + 5 ||
        ast::transform_reduce(input, end, 5, ast::plus<int>{}, twice{}) != 2 * sum + 5)
        return 3;

    const int smallest = ast::numeric_limits<int>::min();
    const int largest = ast::numeric_limits<int>::max();
    if (ast::saturating_sub(smallest + seed, seed + 1) != smallest ||
        ast::saturating_sub(largest - seed, -seed - 1) != largest || ast::saturating_sub(seed, 1) != seed - 1)
        return 4;

    const int bit = seed % 8 + 1;
    const unsigned power = 1u << bit;
    const int failures = (ast::bit_ceil(power) != power ? 1 : 0) | (ast::bit_ceil(power + 1) != 2 * power ? 2 : 0) |
        (ast::bit_floor(power + 1) != power ? 4 : 0) | (ast::bit_width(power) != bit + 1 ? 8 : 0) |
        (!ast::has_single_bit(power) ? 16 : 0) | (ast::has_single_bit(power + 1) ? 32 : 0) |
        (ast::has_single_bit(0u) ? 64 : 0) | (ast::rotl(1u, bit) != power ? 128 : 0) |
        (ast::rotr(power, bit) != 1u ? 256 : 0) | (ast::rotl(power, -bit) != 1u ? 512 : 0) |
        (ast::rotr(1u, -bit) != power ? 1024 : 0);
    if (failures != 0)
        return 16 + failures;
    return 0;
}

CANN_ASC_STL_API int evaluate_random(int seed)
{
    using engine = ast::linear_congruential_engine<unsigned, 13, 17, 127>;
    engine generator(static_cast<unsigned>(seed));
    unsigned expected = static_cast<unsigned>(seed) % 127;
    for (int i = 0; i < 16; ++i) {
        expected = (13 * expected + 17) % 127;
        if (generator() != expected)
            return 1;
    }
    generator.discard(5);
    for (int i = 0; i < 6; ++i)
        expected = (13 * expected + 17) % 127;
    if (generator() != expected || engine::min() != 0 || engine::max() != 126)
        return 2;

    ast::minstd_rand draw(static_cast<unsigned>(seed));
    ast::uniform_int_distribution<int> integers(seed, seed);
    if (integers(draw) != seed || integers.min() != seed || integers.max() != seed)
        return 3;
    integers.param(typename decltype(integers)::param_type(-seed, seed + 3));
    const auto parameters = integers.param();
    integers.reset();
    if (integers.a() != -seed || integers.b() != seed + 3 || parameters.a() != -seed || parameters.b() != seed + 3)
        return 4;
    for (int i = 0; i < 16; ++i) {
        const int value = integers(draw);
        if (value < -seed || value > seed + 3)
            return 5;
    }
    ast::uniform_real_distribution<float> real(-2.0f, 4.0f);
    const auto bounds = real.param();
    const typename decltype(real)::param_type other(-2.0f, 5.0f);
    const ast::uniform_real_distribution<float> same_distribution(bounds);
    if (!(real == same_distribution) || real != same_distribution || bounds == other || !(bounds != other) ||
        real.min() != -2.0f || real.max() != 4.0f || bounds.a() != -2.0f || bounds.b() != 4.0f)
        return 6;
    for (int i = 0; i < 16; ++i) {
        const float value = real(draw);
        if (!(value >= -2.0f && value < 4.0f))
            return 7;
    }
    return 0;
}

}  // namespace asc_stl_standard_numeric_test

#endif  // ASC_STL_TEST_STANDARD_NUMERIC_SEMANTICS_H
