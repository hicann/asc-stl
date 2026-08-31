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

#include <asc/std/climits>
#include <iostream>

// Every macro is consumed directly by the assertions below; an undefined
// macro would fail compilation at its use site, so no separate preprocessor
// definedness ladder is needed.

static int g_failures = 0;

static void expect_ll(const char* name, long long got, long long expected)
{
    const bool ok = (got == expected);
    std::cout << "[host][climits] " << name << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_ull(const char* name, unsigned long long got, unsigned long long expected)
{
    const bool ok = (got == expected);
    std::cout << "[host][climits] " << name << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

static void test_bit_width_of_byte()
{
    expect_ll("CHAR_BIT", CHAR_BIT, 8);
}

static void test_signed_char_limits()
{
    expect_ll("SCHAR_MIN", SCHAR_MIN, -128);
    expect_ll("SCHAR_MAX", SCHAR_MAX, 127);
    expect_ull("UCHAR_MAX", UCHAR_MAX, 255ULL);
}

static void test_plain_char_limits()
{
    // The signedness of plain char is implementation-defined; branch on the
    // comparison result of '\xff'.
    if ('\xff' > 0) {
        expect_ll("CHAR_MIN", CHAR_MIN, 0);
        expect_ll("CHAR_MAX", CHAR_MAX, 255);
    } else {
        expect_ll("CHAR_MIN", CHAR_MIN, -128);
        expect_ll("CHAR_MAX", CHAR_MAX, 127);
    }
}

static void test_short_limits()
{
    expect_ll("SHRT_MIN", SHRT_MIN, -32768);
    expect_ll("SHRT_MAX", SHRT_MAX, 32767);
    expect_ull("USHRT_MAX", USHRT_MAX, 65535ULL);
}

static void test_int_limits()
{
    expect_ll("INT_MIN", INT_MIN, -2147483647LL - 1);
    expect_ll("INT_MAX", INT_MAX, 2147483647LL);
    expect_ull("UINT_MAX", UINT_MAX, 4294967295ULL);
}

static void test_long_limits()
{
    // The width of long varies across platforms; branch on sizeof(long).
    if (sizeof(long) == 8) {
        expect_ll("LONG_MIN", LONG_MIN, -9223372036854775807LL - 1);
        expect_ll("LONG_MAX", LONG_MAX, 9223372036854775807LL);
        expect_ull("ULONG_MAX", ULONG_MAX, 18446744073709551615ULL);
    } else {
        expect_ll("LONG_MIN", LONG_MIN, -2147483647LL - 1);
        expect_ll("LONG_MAX", LONG_MAX, 2147483647LL);
        expect_ull("ULONG_MAX", ULONG_MAX, 4294967295ULL);
    }
}

static void test_long_long_limits()
{
    expect_ll("LLONG_MIN", LLONG_MIN, -9223372036854775807LL - 1);
    expect_ll("LLONG_MAX", LLONG_MAX, 9223372036854775807LL);
    expect_ull("ULLONG_MAX", ULLONG_MAX, 18446744073709551615ULL);
}

int main()
{
    test_bit_width_of_byte();
    test_signed_char_limits();
    test_plain_char_limits();
    test_short_limits();
    test_int_limits();
    test_long_limits();
    test_long_long_limits();

    return g_failures == 0 ? 0 : 1;
}
