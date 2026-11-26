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

#include <asc/std/random>

#include <limits>
#include <type_traits>

namespace {

namespace ast = asc::std;
using engine32 = ast::philox4x32;
using engine64 = ast::philox4x64;
using word = engine32::result_type;
static_assert(std::is_unsigned_v<word>);

static_assert(std::is_same_v<ast::minstd_rand::result_type, asc::std::uint_fast32_t>);
static_assert(engine32::word_size == 32 && engine64::word_size == 64);
static_assert(engine32::word_count == 4 && engine64::word_count == 4);
static_assert(engine32::round_count == 10 && engine64::round_count == 10);
static_assert(engine32::multipliers[0] == 3449720151U && engine32::multipliers[1] == 3528531795U);
static_assert(engine32::round_consts[0] == 2654435769U && engine32::round_consts[1] == 3144134277U);
static_assert(engine32::min() == 0 && engine32::max() == 0xffffffffULL);
static_assert(engine64::min() == 0 && engine64::max() == std::numeric_limits<engine64::result_type>::max());

template <class Engine>
bool check_seed_and_equality()
{
    Engine default_engine;
    Engine explicitly_seeded(Engine::default_seed);
    if (!(default_engine == explicitly_seeded) || default_engine != explicitly_seeded) {
        return false;
    }
    const typename Engine::result_type seeds[] = {0, 1, 7, 123456};
    for (auto seed : seeds) {
        default_engine.seed(seed);
        explicitly_seeded = Engine(seed);
        if (!(default_engine == explicitly_seeded)) {
            return false;
        }
        for (int counter = 0; counter < 17; ++counter) {
            if (default_engine() != explicitly_seeded() || default_engine != explicitly_seeded) {
                return false;
            }
        }
        default_engine.discard(4);
        if (!(default_engine != explicitly_seeded)) {
            return false;
        }
    }
    return true;
}

bool check_integral_distribution()
{
    using distribution = ast::uniform_int_distribution<int>;
    static_assert(std::is_same_v<distribution::result_type, int>);
    distribution values(-11, 7);
    const distribution::param_type defaults(-11, 7);
    engine32 engine(211);
    if (values.a() != -11 || values.b() != 7 || values.min() != -11 || values.max() != 7 ||
        values.param().a() != defaults.a() || values.param().b() != defaults.b()) {
        return false;
    }
    bool negative = false;
    bool positive = false;
    for (int i = 0; i < 256; ++i) {
        const int sampled = values(engine);
        if (sampled < -11 || sampled > 7 || values(engine, distribution::param_type(4, 4)) != 4) {
            return false;
        }
        negative = negative || sampled < 0;
        positive = positive || sampled > 0;
    }
    values.param(distribution::param_type(17, 19));
    const engine32 saved = engine;
    const int before = values(engine);
    engine = saved;
    values.reset();
    const int after = values(engine);
    return negative && positive && values.min() == 17 && values.max() == 19 && values.param().a() == 17 &&
        before >= 17 && before <= 19 && after == before;
}

bool check_real_distribution()
{
    using distribution = ast::uniform_real_distribution<float>;
    static_assert(std::is_same_v<distribution::result_type, float>);
    const distribution::param_type range(-3.0F, 5.0F);
    const distribution::param_type same(-3.0F, 5.0F);
    const distribution::param_type other(-3.0F, 6.0F);
    if (range.a() != -3.0F || range.b() != 5.0F || !(range == same) || range != same || !(range != other)) {
        return false;
    }
    distribution values(range);
    distribution different(other);
    if (values.min() != -3.0F || values.max() != 5.0F || values == different || !(values != different)) {
        return false;
    }
    different.param(same);
    if (!(values == different) || values != different) {
        return false;
    }
    engine32 generator(107);
    engine32 copy = generator;
    for (int i = 0; i < 128; ++i) {
        const auto sampled = values(generator);
        if (sampled < -3.0F || sampled >= 5.0F || sampled != different(copy)) {
            return false;
        }
    }
    return true;
}

}  // namespace

int main()
{
    return check_seed_and_equality<engine32>() && check_seed_and_equality<engine64>() &&
            check_integral_distribution() && check_real_distribution() ?
        0 :
        1;
}
