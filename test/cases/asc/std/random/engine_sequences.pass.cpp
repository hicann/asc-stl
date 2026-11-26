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

#include <asc/std/array>
#include <asc/std/random>

#include <iostream>
#include <limits>
#include <random>

namespace {

namespace ast = asc::std;

template <class Actual, class Reference>
bool compare_engines()
{
    using word = typename Actual::result_type;
    const word seeds[] = {0, 1, 401, Actual::modulus - 1, Actual::modulus, std::numeric_limits<word>::max()};
    for (word seed : seeds) {
        Actual actual(seed);
        Reference expected(seed);
        const unsigned steps[] = {0, 1, 31, 512, 1024};
        for (auto discard_count : steps) {
            actual.discard(discard_count);
            expected.discard(discard_count);
            for (int i = 0; i < 129; ++i) {
                if (actual() != expected())
                    return false;
            }
        }
        actual.seed(Actual::default_seed);
        expected.seed();
        if (actual() != expected() || Actual::min() != Reference::min() || Actual::max() != Reference::max())
            return false;
    }
    return true;
}

template <class Engine>
bool check_philox_discard()
{
    using word = typename Engine::result_type;
    using counter = ast::array<word, Engine::word_count>;
    const word max = Engine::max();
    const counter starts[] = {{0, 0, 0, 0}, {0, 0, 0, max - 1}, {0, 0, max, max}, {max, max, max, max}};
    const unsigned counts[] = {0, 1, 3, 4, 5, 7, 8, 9, 101, 256, 513};
    Engine actual(13), sequential(13);
    for (const auto& start : starts) {
        for (unsigned first = 0; first < Engine::word_count; ++first) {
            for (auto count : counts) {
                actual.set_counter(start);
                sequential.set_counter(start);
                for (unsigned i = 0; i < first; ++i) {
                    if (actual() != sequential())
                        return false;
                }
                actual.discard(count);
                for (unsigned i = 0; i < count; ++i)
                    (void)sequential();
                if (actual != sequential)
                    return false;
                for (int i = 0; i < 9; ++i) {
                    if (actual() != sequential())
                        return false;
                }
            }
        }
    }

    // 2^32 blocks advance the second least significant word of a 32-bit counter.
    const auto blocks = 1ULL << 32;
    const counter after = Engine::word_size == 32 ? counter{0, 0, 1, 0} : counter{0, 0, 0, static_cast<word>(blocks)};
    actual.set_counter({0, 0, 0, 0});
    actual.discard(blocks * Engine::word_count + 3);
    sequential.set_counter(after);
    for (int i = 0; i < 3; ++i)
        (void)sequential();
    return actual == sequential && actual() == sequential();
}

}  // namespace

int main()
{
    using word = ast::uint_fast64_t;
    using overflow_lcg = ast::linear_congruential_engine<word, 18446744073709551521ULL, 18446744073709551427ULL,
        18446744073709551557ULL>;
    using reference_lcg = std::linear_congruential_engine<word, 18446744073709551521ULL, 18446744073709551427ULL,
        18446744073709551557ULL>;
    if (!compare_engines<ast::minstd_rand0, std::minstd_rand0>() ||
        !compare_engines<ast::minstd_rand, std::minstd_rand>() || !compare_engines<overflow_lcg, reference_lcg>()) {
        std::cerr << "Linear congruential sequence differs from the native standard library\n";
        return 1;
    }
    if (!check_philox_discard<ast::philox4x32>() || !check_philox_discard<ast::philox4x64>()) {
        std::cerr << "Philox discard reached an unexpected counter or position\n";
        return 2;
    }
    return 0;
}
