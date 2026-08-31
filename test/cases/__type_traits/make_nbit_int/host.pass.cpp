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

#include <asc/std/__type_traits/make_nbit_int.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][make_nbit_int] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][make_nbit_int] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void test_signed_make_nbit_int()
{
    // --- Signed: __make_nbit_int_t<NBits, true> ---
    expect_true(
        "is_same<__make_nbit_int_t<8, true>, int8_t>", std::is_same_v<asc::std::__make_nbit_int_t<8, true>, int8_t>);
    expect_true("is_same<__make_nbit_int_t<16, true>, int16_t>",
        std::is_same_v<asc::std::__make_nbit_int_t<16, true>, int16_t>);
    expect_true("is_same<__make_nbit_int_t<32, true>, int32_t>",
        std::is_same_v<asc::std::__make_nbit_int_t<32, true>, int32_t>);
    expect_true("is_same<__make_nbit_int_t<64, true>, int64_t>",
        std::is_same_v<asc::std::__make_nbit_int_t<64, true>, int64_t>);
}

static void test_unsigned_make_nbit_int()
{
    // --- Unsigned: __make_nbit_int_t<NBits, false> ---
    expect_true("is_same<__make_nbit_int_t<8, false>, uint8_t>",
        std::is_same_v<asc::std::__make_nbit_int_t<8, false>, uint8_t>);
    expect_true("is_same<__make_nbit_int_t<16, false>, uint16_t>",
        std::is_same_v<asc::std::__make_nbit_int_t<16, false>, uint16_t>);
    expect_true("is_same<__make_nbit_int_t<32, false>, uint32_t>",
        std::is_same_v<asc::std::__make_nbit_int_t<32, false>, uint32_t>);
    expect_true("is_same<__make_nbit_int_t<64, false>, uint64_t>",
        std::is_same_v<asc::std::__make_nbit_int_t<64, false>, uint64_t>);
}

static void test_default_issigned_true()
{
    // --- Default _IsSigned = true ---
    expect_true("is_same<__make_nbit_int_t<32>, int32_t> (default signed)",
        std::is_same_v<asc::std::__make_nbit_int_t<32>, int32_t>);
    expect_true("is_same<__make_nbit_int_t<8>, int8_t> (default signed)",
        std::is_same_v<asc::std::__make_nbit_int_t<8>, int8_t>);
}

static void test_make_nbit_uint_always()
{
    // --- __make_nbit_uint_t (always unsigned) ---
    expect_true("is_same<__make_nbit_uint_t<8>, uint8_t>", std::is_same_v<asc::std::__make_nbit_uint_t<8>, uint8_t>);
    expect_true(
        "is_same<__make_nbit_uint_t<16>, uint16_t>", std::is_same_v<asc::std::__make_nbit_uint_t<16>, uint16_t>);
    expect_true(
        "is_same<__make_nbit_uint_t<32>, uint32_t>", std::is_same_v<asc::std::__make_nbit_uint_t<32>, uint32_t>);
    expect_true(
        "is_same<__make_nbit_uint_t<64>, uint64_t>", std::is_same_v<asc::std::__make_nbit_uint_t<64>, uint64_t>);
}

static void test_sizeof()
{
    // --- sizeof checks ---
    expect_eq("sizeof(__make_nbit_int_t<8, true>)",
        (int)sizeof(asc::std::__make_nbit_int_t<8, true>),  // NOLINT(readability/casting)
        1);                                                 // NOLINT(readability/casting)
    expect_eq("sizeof(__make_nbit_int_t<16, true>)",
        (int)sizeof(asc::std::__make_nbit_int_t<16, true>),  // NOLINT(readability/casting)
        2);                                                  // NOLINT(readability/casting)
    expect_eq("sizeof(__make_nbit_int_t<32, true>)",
        (int)sizeof(asc::std::__make_nbit_int_t<32, true>),  // NOLINT(readability/casting)
        4);                                                  // NOLINT(readability/casting)
    expect_eq("sizeof(__make_nbit_int_t<64, true>)",
        (int)sizeof(asc::std::__make_nbit_int_t<64, true>),  // NOLINT(readability/casting)
        8);                                                  // NOLINT(readability/casting)
    expect_eq("sizeof(__make_nbit_uint_t<8>)",
        (int)sizeof(asc::std::__make_nbit_uint_t<8>),  // NOLINT(readability/casting)
        1);                                            // NOLINT(readability/casting)
    expect_eq("sizeof(__make_nbit_uint_t<16>)",
        (int)sizeof(asc::std::__make_nbit_uint_t<16>),  // NOLINT(readability/casting)
        2);                                             // NOLINT(readability/casting)
    expect_eq("sizeof(__make_nbit_uint_t<32>)",
        (int)sizeof(asc::std::__make_nbit_uint_t<32>),  // NOLINT(readability/casting)
        4);                                             // NOLINT(readability/casting)
    expect_eq("sizeof(__make_nbit_uint_t<64>)",
        (int)sizeof(asc::std::__make_nbit_uint_t<64>),  // NOLINT(readability/casting)
        8);                                             // NOLINT(readability/casting)
}

static void test_signedness()
{
    // --- signedness checks ---
    expect_true("is_signed<__make_nbit_int_t<32, true>>", std::is_signed_v<asc::std::__make_nbit_int_t<32, true>>);
    expect_true(
        "is_unsigned<__make_nbit_int_t<32, false>>", std::is_unsigned_v<asc::std::__make_nbit_int_t<32, false>>);
    expect_true("is_unsigned<__make_nbit_uint_t<32>>", std::is_unsigned_v<asc::std::__make_nbit_uint_t<32>>);
}

static void test_bit_available()
{
    // --- 128-bit if available ---
#if CANN_ASC_STL_DETAIL_HAS_INT128()
    expect_true("is_same<__make_nbit_int_t<128, true>, __int128_t>",
        std::is_same_v<asc::std::__make_nbit_int_t<128, true>, __int128_t>);
    expect_true("is_same<__make_nbit_int_t<128, false>, __uint128_t>",
        std::is_same_v<asc::std::__make_nbit_int_t<128, false>, __uint128_t>);
    expect_true("is_same<__make_nbit_uint_t<128>, __uint128_t>",
        std::is_same_v<asc::std::__make_nbit_uint_t<128>, __uint128_t>);
    expect_eq("sizeof(__make_nbit_int_t<128, true>)",
        (int)sizeof(asc::std::__make_nbit_int_t<128, true>),  // NOLINT(readability/casting)
        16);                                                  // NOLINT(readability/casting)
    expect_eq("sizeof(__make_nbit_uint_t<128>)",
        (int)sizeof(asc::std::__make_nbit_uint_t<128>),  // NOLINT(readability/casting)
        16);                                             // NOLINT(readability/casting)
#endif
}

static void test_make_nbit_int_impl()
{
    // --- __make_nbit_int_impl returns correct default-constructed value ---
    {
        auto v8 = asc::std::__make_nbit_int_impl<8, true>();
        auto v16 = asc::std::__make_nbit_int_impl<16, true>();
        auto v32 = asc::std::__make_nbit_int_impl<32, true>();
        auto v64 = asc::std::__make_nbit_int_impl<64, true>();
        expect_eq("__make_nbit_int_impl<8,true>()", (int)v8, 0);    // NOLINT(readability/casting)
        expect_eq("__make_nbit_int_impl<16,true>()", (int)v16, 0);  // NOLINT(readability/casting)
        expect_eq("__make_nbit_int_impl<32,true>()", (int)v32, 0);  // NOLINT(readability/casting)
        expect_eq("__make_nbit_int_impl<64,true>()", (int)v64, 0);  // NOLINT(readability/casting)

        auto u8 = asc::std::__make_nbit_int_impl<8, false>();
        auto u16 = asc::std::__make_nbit_int_impl<16, false>();
        auto u32 = asc::std::__make_nbit_int_impl<32, false>();
        auto u64 = asc::std::__make_nbit_int_impl<64, false>();
        expect_eq("__make_nbit_int_impl<8,false>()", (int)u8, 0);    // NOLINT(readability/casting)
        expect_eq("__make_nbit_int_impl<16,false>()", (int)u16, 0);  // NOLINT(readability/casting)
        expect_eq("__make_nbit_int_impl<32,false>()", (int)u32, 0);  // NOLINT(readability/casting)
        expect_eq("__make_nbit_int_impl<64,false>()", (int)u64, 0);  // NOLINT(readability/casting)
    }
}

int main()
{
    test_signed_make_nbit_int();
    test_unsigned_make_nbit_int();
    test_default_issigned_true();
    test_make_nbit_uint_always();
    test_sizeof();
    test_signedness();
    test_bit_available();
    test_make_nbit_int_impl();

    return g_failures == 0 ? 0 : 1;
}
