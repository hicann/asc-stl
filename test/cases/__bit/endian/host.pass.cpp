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

#include <asc/std/__bit/endian.h>
#include <iostream>

static int g_failures = 0;

static void expect_eq(const char* expr, int got, int expected)
{
    bool ok = (got == expected);
    std::cout << "[host][endian] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][endian] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][endian] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

int main()
{
    // endian::little and endian::big have distinct, known constant values
    expect_eq("static_cast<int>(endian::little)", static_cast<int>(asc::std::endian::little), 0xDEAD);
    expect_eq("static_cast<int>(endian::big)", static_cast<int>(asc::std::endian::big), 0xFACE);

    // endian::little != endian::big
    expect_true("endian::little != endian::big", asc::std::endian::little != asc::std::endian::big);

    // endian::native must be one of the three known architecture constants
    int native_val = static_cast<int>(asc::std::endian::native);
    bool native_valid = (native_val == 0xDEAD || native_val == 0xFACE || native_val == 0xBEEF);
    expect_true("endian::native is a known constant (0xDEAD/0xFACE/0xBEEF)", native_valid);

    // Platform-specific: on little-endian hosts, native == little
#if defined(__LITTLE_ENDIAN__) || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) || \
    (defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN)
    expect_true(
        "endian::native == endian::little (little-endian host)", asc::std::endian::native == asc::std::endian::little);
    expect_false(
        "endian::native != endian::big (little-endian host)", asc::std::endian::native == asc::std::endian::big);
#elif defined(__BIG_ENDIAN__) || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__) || \
    (defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN)
    expect_true("endian::native == endian::big (big-endian host)", asc::std::endian::native == asc::std::endian::big);
    expect_false(
        "endian::native != endian::little (big-endian host)", asc::std::endian::native == asc::std::endian::little);
#endif

    return g_failures == 0 ? 0 : 1;
}
