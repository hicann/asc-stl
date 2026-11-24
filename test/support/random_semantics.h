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

#ifndef ASC_STL_TEST_RANDOM_SEMANTICS_H
#define ASC_STL_TEST_RANDOM_SEMANTICS_H

#include <asc/random>
#include <asc/std/random>
#include <asc/std/type_traits>

namespace asc_stl_random_test {

using engine = asc::pcg64;
using word = asc::std::uint64_t;

static_assert(asc::std::is_same_v<engine::result_type, word>);
static_assert(engine::min() == 0 && engine::max() == 18446744073709551615ULL);
static_assert(noexcept(engine()) && noexcept(engine(0)));
static_assert(noexcept(engine{}.seed()) && noexcept(engine{}()));
static_assert(noexcept(engine{}.discard(~0ULL)));
static_assert(asc::std::is_nothrow_copy_constructible_v<engine>);
static_assert(asc::std::is_nothrow_copy_assignable_v<engine>);
static_assert(!asc::std::is_convertible_v<word, engine>);

CANN_ASC_STL_API constexpr bool state_contracts()
{
    engine a;
    engine b(engine::default_seed);
    if (a != b || a() != 0xcf7dbe684e0c4045ULL)
        return false;
    b.discard(1);
    if (a != b)
        return false;
    engine copy(a);  // NOLINT(build/include_what_you_use)
    if (copy() != 0x15642875dfe1e67cULL)
        return false;
    copy = b;
    if (copy != a)
        return false;
    copy.discard(0);
    if (copy != a)
        return false;
    a.seed();
    if (a != engine() || a() != 0xcf7dbe684e0c4045ULL)
        return false;
    a.seed(0);
    if (a() != 0x01070196e695f8f1ULL)
        return false;
    a.seed(~word{0});
    if (a() != 0x3b17d015242767f3ULL)
        return false;
    a.seed(42);
    if (a() != 0x287472e87ff5705aULL)
        return false;
    a.seed(42);
    b.seed(42);
    a.discard(127);
    for (unsigned i = 0; i != 127; ++i)
        (void)b();
    return a == b && !(a != b);
}

CANN_ASC_STL_API constexpr bool large_discard()
{
    engine a(42), b(42);
    a.discard(~0ULL);
    b.discard(1ULL << 63);
    b.discard((1ULL << 63) - 1);
    return a == b;
}

static_assert(state_contracts());
static_assert(large_discard());

CANN_ASC_STL_API bool composition(word seed)
{
    engine source(seed);
    asc::std::uniform_int_distribution<int> integers(-17, 29);
    asc::std::uniform_int_distribution<word> whole;
    asc::std::uniform_real_distribution<float> real(0.0F, 1.0F);
    const int integer = integers(source);
    engine copied(source);
    const word raw = copied();
    const word full = whole(source);
    const float unit = real(source);
    const float canonical = asc::std::generate_canonical<float, 24>(source);
    return integer >= -17 && integer <= 29 && full == raw && unit >= 0.0F && unit < 1.0F && canonical >= 0.0F &&
        canonical < 1.0F;
}

CANN_ASC_STL_API bool short_discard(word seed, unsigned count)
{
    engine advanced(seed), stepped(seed);
    advanced.discard(count);
    for (unsigned i = 0; i != count; ++i)
        (void)stepped();
    return advanced == stepped;
}

}  // namespace asc_stl_random_test

#endif  // ASC_STL_TEST_RANDOM_SEMANTICS_H
