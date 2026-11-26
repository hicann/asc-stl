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

#ifndef ASC_STL_TEST_RANDOM_DEVICE_CHECKS_H
#define ASC_STL_TEST_RANDOM_DEVICE_CHECKS_H

#include <asc/std/random>
#include <asc/std/new>

namespace asc_stl_test_random {
struct fixed_draw {
    using result_type = unsigned;
    unsigned next;
    unsigned calls = 0;
    CANN_ASC_STL_API static constexpr unsigned min()
    {
        return 0;
    }
    CANN_ASC_STL_API static constexpr unsigned max()
    {
        return 0xffffffffu;
    }
    CANN_ASC_STL_API unsigned operator()()
    {
        ++calls;
        return next;
    }
};

template <class Engine>
struct engine_fixture {
    Engine stream{0}, jump, stepped;
};

union engine_workspace {
    engine_fixture<::asc::std::philox4x32> words32;
    engine_fixture<::asc::std::philox4x64> words64;
};

inline constexpr unsigned last_offset = 9;

template <class Engine>
CANN_ASC_STL_API bool philox_words(void* workspace, unsigned first_offset, unsigned stride)
{
    auto* states = ::new (workspace) engine_fixture<Engine>{};
    Engine& stream = states->stream;
    Engine& jump = states->jump;
    Engine& stepped = states->stepped;
    if (first_offset == 0) {
        // Published Philox4x32-10 / Philox4x64-10 zero-key, zero-counter vectors.
        if constexpr (Engine::word_size == 32) {
            if (stream() != 0x6627e8d5u || stream() != 0xe169c58du || stream() != 0xbc57ac4cu ||
                stream() != 0x9b00dbd8u)
                return false;
        } else {
            if (stream() != 0x16554d9eca36314cULL || stream() != 0xdb20fe9d672d0fdcULL ||
                stream() != 0xd7e772cee186176bULL || stream() != 0x7e68b68aec7ba23bULL)
                return false;
        }
    }
    for (unsigned offset = first_offset; offset <= last_offset; offset += stride) {
        jump.seed(0);
        jump.discard(offset);
        stepped.seed(0);
        for (unsigned i = 0; i < offset; ++i)
            stepped();
        if (jump != stepped || jump() != stepped())
            return false;
    }
    if (first_offset != 0)
        return true;
    stepped.seed(0);
    stepped.set_counter({0, 0, 0, 1});
    return stepped == stream && stepped() == stream();
}

CANN_ASC_STL_API bool philox_engines(void* workspace, unsigned first_offset, unsigned stride)
{
    namespace s = ::asc::std;
    auto* slot = static_cast<unsigned char*>(workspace) + first_offset * sizeof(engine_workspace);
    return philox_words<s::philox4x32>(slot, first_offset, stride) &&
        philox_words<s::philox4x64>(slot, first_offset, stride);
}

CANN_ASC_STL_API int check_partition(int input, void* workspace, unsigned first_offset, unsigned stride)
{
    if (first_offset > last_offset)
        return 0;
    if (first_offset != 0)
        return philox_engines(workspace, first_offset, stride) ? 0 : 5;
    namespace s = ::asc::std;
    using lcg = s::linear_congruential_engine<unsigned, 5, 3, 17>;
    fixed_draw seed{static_cast<unsigned>(input + 27)};
    lcg first(seed), other(0);
    if (seed.calls != 1 || first != other || lcg::min() != 0 || lcg::max() != 16 || lcg::multiplier != 5 ||
        lcg::increment != 3 || lcg::modulus != 17 || lcg::default_seed != 1)
        return 1;
    first.discard(8);
    unsigned state = 0;
    for (int i = 0; i < 9; ++i)
        state = (5 * state + 3) % 17;
    if (first() != state)
        return 2;
    first.seed(seed);
    other.seed(17);
    if (!(first == other) || seed.calls != 2)
        return 3;
    s::minstd_rand engine(0);
    s::minstd_rand0 rand0(0);
    if (engine() != 48271 || rand0() != 16807)
        return 4;
    if (!philox_engines(workspace, first_offset, stride))
        return 5;
    if (s::philox4x32::word_size != 32 || s::philox4x32::word_count != 4 || s::philox4x32::round_count != 10 ||
        s::philox4x32::multipliers[0] != 0xcd9e8d57U || s::philox4x32::round_consts[0] != 0x9e3779b9U ||
        s::philox4x32::min() != 0 || s::philox4x32::max() != 0xffffffffu)
        return 6;

    using integer = s::uniform_int_distribution<int>;
    integer di(-2, 2);
    const integer defaults;
    if (defaults.a() != 0 || defaults.b() != s::numeric_limits<int>::max())
        return 16;
    const integer::param_type fixed(13, 13);
    integer alternate(di.param());
    if (!(di == alternate) || alternate.min() != -2 || alternate.max() != 2 || fixed.a() != 13 || fixed.b() != 13)
        return 7;
    alternate.param(fixed);
    alternate.reset();
    if (alternate == di || !(alternate != di) || di.param() == fixed || !(di.param() != fixed) ||
        !(alternate.param() == fixed) || di.a() != -2 || di.b() != 2 || alternate(engine) != 13 ||
        di(engine, fixed) != 13)
        return 8;
    unsigned mask = 0;
    for (int i = 0; i < 128; ++i) {
        const int value = di(engine);
        if (value < -2 || value > 2)
            return 9;
        mask |= 1u << (value + 2);
    }
    if (mask != 31)
        return 10;

    fixed_draw bits{0};
    if (s::generate_canonical<float, 0>(bits) != 0 || bits.calls != 1)
        return 11;
    bits.next = 0xffffffffu;
    if (s::generate_canonical<float, 24>(bits) != 0x1.fffffep-1F)
        return 12;
    using real = s::uniform_real_distribution<float>;
    const real::param_type p(-3.0F, 1.0F);
    real u;
    real v(p);
    if (u == v || !(u != v) || p.a() != -3.0F || p.b() != 1.0F || u.min() != 0.0F || u.max() != 1.0F)
        return 13;
    u.param(p);
    v.reset();
    if (!(u.param() == p) || u.param() != p || !(u == v) || u.a() != -3.0F || u.b() != 1.0F)
        return 14;
    bits.next = 0x80000000u;
    if (u(bits) != -1.0F || real(2.0F, 6.0F)(bits) != 4.0F || u(bits, real::param_type()) != 0.5F)
        return 15;
    return 0;
}

CANN_ASC_STL_API int check(int input, void* workspace)
{
    return check_partition(input, workspace, 0, 1);
}
}  // namespace asc_stl_test_random

#endif  // ASC_STL_TEST_RANDOM_DEVICE_CHECKS_H
