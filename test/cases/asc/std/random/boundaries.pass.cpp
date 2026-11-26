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

#include <random>
#include <type_traits>
#include "device_checks.h"

using integer_distribution = asc::std::uniform_int_distribution<long>;
using real_distribution = asc::std::uniform_real_distribution<float>;
static_assert(std::is_same_v<integer_distribution::param_type::distribution_type, integer_distribution> &&
    std::is_same_v<real_distribution::param_type::distribution_type, real_distribution>);
using two32 = asc::std::philox_engine<unsigned, 32, 2, 10, 0xd256d193U, 0x9e3779b9U>;
using two64 = asc::std::philox_engine<unsigned long long, 64, 2, 10, 0xd2b74407b1ce6e93ULL, 0x9e3779b97f4a7c15ULL>;

template <class E>
bool two_word_counters(typename E::result_type first, typename E::result_type second,
    typename E::result_type high_first, typename E::result_type high_second)
{
    E engine(0);
    if (engine() != first || engine() != second)
        return false;
    engine.seed(E::max());
    engine.set_counter({E::max(), E::max() - 1});
    if (engine() != high_first || engine() != high_second)
        return false;
    E wrapped(0), direct(0);
    wrapped.set_counter({E::max(), E::max()});
    wrapped.discard(2);
    if (wrapped != direct || wrapped() != direct())
        return false;
    // UINT64_MAX skipped words advance by 2^63 - 1 blocks plus the first word.
    engine.seed(0);
    engine.discard(~0ULL);
    direct.seed(0);
    if constexpr (E::word_size == 32)
        direct.set_counter({0x7fffffffU, 0xffffffffU});
    else
        direct.set_counter({0, 0x7fffffffffffffffULL});
    direct();
    return engine == direct && engine() == direct();
}

template <unsigned long long A, unsigned long long C, unsigned long long M>
bool congruential()
{
    using E = asc::std::linear_congruential_engine<unsigned long long, A, C, M>;
    using Reference = std::linear_congruential_engine<unsigned long long, A, C, M>;
    for (auto seed : {0ULL, 1ULL, M, ~0ULL}) {
        E actual(seed);
        Reference expected(seed);
        for (unsigned i = 0; i < 128; ++i) {
            if (actual() != expected())
                return false;
        }
        actual.discard(31);
        expected.discard(31);
        if (actual() != expected())
            return false;
    }
    return true;
}

int main()
{
    using slot = asc_stl_test_random::engine_workspace;
    alignas(slot) unsigned char workspace[32 * sizeof(slot)]{};
    if (!two_word_counters<two32>(0xff1dae59U, 0x6cd10df2U, 0xd50c583cU, 0x572d2794U) ||
        !two_word_counters<two64>(
            0xca00a0459843d731ULL, 0x66c24222c9a845b5ULL, 0x26710a47e5222b9bULL, 0xb150d947800b768aULL))
        return 20;
    if (!congruential<6364136223846793005ULL, 1442695040888963407ULL, 0>() ||
        !congruential<18446744073709551556ULL, 18446744073709551555ULL, 18446744073709551557ULL>())
        return 21;
    if (const int status = asc_stl_test_random::check(7, workspace))
        return status;
    for (unsigned lane = 0; lane < 32; ++lane)
        if (const int status = asc_stl_test_random::check_partition(7, workspace, lane, 32))
            return status;
    return 0;
}
