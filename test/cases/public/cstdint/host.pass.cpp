/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#include <asc/std/cstdint>
#include <iostream>
#include <type_traits>
#include <cstdint>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][cstdint] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

template <typename A, typename B>
static void expect_same(const char* expr)
{
    bool ok = std::is_same<A, B>::value;
    std::cout << "[host][cstdint] " << expr << " " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void test_fixed_width_integer_type()
{
    // --- Verify fixed-width integer type aliases ---
    expect_same<asc::std::int8_t, ::int8_t>("int8_t == ::int8_t");
    expect_same<asc::std::int16_t, ::int16_t>("int16_t == ::int16_t");
    expect_same<asc::std::int32_t, ::int32_t>("int32_t == ::int32_t");
    expect_same<asc::std::int64_t, ::int64_t>("int64_t == ::int64_t");
    expect_same<asc::std::uint8_t, ::uint8_t>("uint8_t == ::uint8_t");
    expect_same<asc::std::uint16_t, ::uint16_t>("uint16_t == ::uint16_t");
    expect_same<asc::std::uint32_t, ::uint32_t>("uint32_t == ::uint32_t");
    expect_same<asc::std::uint64_t, ::uint64_t>("uint64_t == ::uint64_t");
}

static void test_int_fast_uint_fast()
{
    // --- Verify int_fast*_t / uint_fast*_t aliases ---
    expect_same<asc::std::int_fast8_t, ::int_fast8_t>("int_fast8_t == ::int_fast8_t");
    expect_same<asc::std::int_fast16_t, ::int_fast16_t>("int_fast16_t == ::int_fast16_t");
    expect_same<asc::std::int_fast32_t, ::int_fast32_t>("int_fast32_t == ::int_fast32_t");
    expect_same<asc::std::int_fast64_t, ::int_fast64_t>("int_fast64_t == ::int_fast64_t");
    expect_same<asc::std::uint_fast8_t, ::uint_fast8_t>("uint_fast8_t == ::uint_fast8_t");
    expect_same<asc::std::uint_fast16_t, ::uint_fast16_t>("uint_fast16_t == ::uint_fast16_t");
    expect_same<asc::std::uint_fast32_t, ::uint_fast32_t>("uint_fast32_t == ::uint_fast32_t");
    expect_same<asc::std::uint_fast64_t, ::uint_fast64_t>("uint_fast64_t == ::uint_fast64_t");
}

static void test_int_least_uint_least()
{
    // --- Verify int_least*_t / uint_least*_t aliases ---
    expect_same<asc::std::int_least8_t, ::int_least8_t>("int_least8_t == ::int_least8_t");
    expect_same<asc::std::int_least16_t, ::int_least16_t>("int_least16_t == ::int_least16_t");
    expect_same<asc::std::int_least32_t, ::int_least32_t>("int_least32_t == ::int_least32_t");
    expect_same<asc::std::int_least64_t, ::int_least64_t>("int_least64_t == ::int_least64_t");
    expect_same<asc::std::uint_least8_t, ::uint_least8_t>("uint_least8_t == ::uint_least8_t");
    expect_same<asc::std::uint_least16_t, ::uint_least16_t>("uint_least16_t == ::uint_least16_t");
    expect_same<asc::std::uint_least32_t, ::uint_least32_t>("uint_least32_t == ::uint_least32_t");
    expect_same<asc::std::uint_least64_t, ::uint_least64_t>("uint_least64_t == ::uint_least64_t");
}

static void test_pointer_sized_max_integer()
{
    // --- Verify pointer-sized and max integer aliases ---
    expect_same<asc::std::intptr_t, ::intptr_t>("intptr_t == ::intptr_t");
    expect_same<asc::std::uintptr_t, ::uintptr_t>("uintptr_t == ::uintptr_t");
    expect_same<asc::std::intmax_t, ::intmax_t>("intmax_t == ::intmax_t");
    expect_same<asc::std::uintmax_t, ::uintmax_t>("uintmax_t == ::uintmax_t");
}

static void test_sizes_fixed_width_types()
{
    // --- Verify sizes of fixed-width types ---
    expect_eq("sizeof(int8_t)", (int)sizeof(asc::std::int8_t), 1);      // NOLINT(readability/casting)
    expect_eq("sizeof(int16_t)", (int)sizeof(asc::std::int16_t), 2);    // NOLINT(readability/casting)
    expect_eq("sizeof(int32_t)", (int)sizeof(asc::std::int32_t), 4);    // NOLINT(readability/casting)
    expect_eq("sizeof(int64_t)", (int)sizeof(asc::std::int64_t), 8);    // NOLINT(readability/casting)
    expect_eq("sizeof(uint8_t)", (int)sizeof(asc::std::uint8_t), 1);    // NOLINT(readability/casting)
    expect_eq("sizeof(uint16_t)", (int)sizeof(asc::std::uint16_t), 2);  // NOLINT(readability/casting)
    expect_eq("sizeof(uint32_t)", (int)sizeof(asc::std::uint32_t), 4);  // NOLINT(readability/casting)
    expect_eq("sizeof(uint64_t)", (int)sizeof(asc::std::uint64_t), 8);  // NOLINT(readability/casting)
}

static void test_asc_intmax_asc_uintmax()
{
    // --- Verify __asc_intmax_t / __asc_uintmax_t ---
#if CANN_ASC_STL_DETAIL_HAS_INT128()
    expect_same<asc::std::__asc_intmax_t, __int128_t>("__asc_intmax_t == __int128_t");
    expect_same<asc::std::__asc_uintmax_t, __uint128_t>("__asc_uintmax_t == __uint128_t");
#else
    expect_same<asc::std::__asc_intmax_t, long long>("__asc_intmax_t == long long");
    expect_same<asc::std::__asc_uintmax_t, unsigned long long>("__asc_uintmax_t == unsigned long long");
#endif
}

static void test_exposed_types_usable_ordinary()
{
    // --- Verify the exposed types are usable in ordinary computations ---
    // bit_reverse / bitfield / bitmask tests use unsigned types
    {
        asc::std::uint8_t u8 = 0b11001001;
        asc::std::uint16_t u16 = 0xFFFF;
        asc::std::uint32_t u32 = 0xDEADBEEFu;
        asc::std::uint64_t u64 = 0xFFFFFFFFFFFFFFFFULL;

        expect_eq("uint8_t value", (int)u8, 0b11001001);  // NOLINT(readability/casting)
        expect_eq("uint16_t value", (int)u16, 0xFFFF);    // NOLINT(readability/casting)
        expect_eq("uint32_t value", (unsigned)u32, 0xDEADBEEFu);
        expect_eq("uint64_t value", (unsigned long long)u64, 0xFFFFFFFFFFFFFFFFULL);
    }
}

static void test_fast_modulo_division_uses()
{
    // fast_modulo_division test uses signed types
    {
        asc::std::int8_t s8 = -1;
        asc::std::int16_t s16 = -1000;
        asc::std::int32_t s32 = -1000000;
        asc::std::int64_t s64 = -1000000000000LL;

        expect_eq("int8_t value", (int)s8, -1);       // NOLINT(readability/casting)
        expect_eq("int16_t value", (int)s16, -1000);  // NOLINT(readability/casting)
        expect_eq("int32_t value", s32, -1000000);
        expect_eq("int64_t value", (long long)s64, -1000000000000LL);
    }
}

static void test_uintmax_uintptr_usable()
{
    // Verify uintmax_t and uintptr_t are usable
    {
        asc::std::uintmax_t umax = 0xFFFFFFFFFFFFFFFFULL;
        expect_eq("uintmax_t value", (unsigned long long)umax, 0xFFFFFFFFFFFFFFFFULL);

        int x = 42;
        asc::std::uintptr_t uptr = reinterpret_cast<asc::std::uintptr_t>(&x);
        expect_eq("uintptr_t nonzero", (uptr != 0) ? 1 : 0, 1);
    }
}

int main()
{
    test_fixed_width_integer_type();
    test_int_fast_uint_fast();
    test_int_least_uint_least();
    test_pointer_sized_max_integer();
    test_sizes_fixed_width_types();
    test_asc_intmax_asc_uintmax();
    test_exposed_types_usable_ordinary();
    test_fast_modulo_division_uses();
    test_uintmax_uintptr_usable();

    return g_failures == 0 ? 0 : 1;
}
