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

#include <asc/std/__asc/architecture.h>
#include <iostream>

static int g_failures = 0;

static void expect_eq(const char* expr, int got, int expected)
{
    bool ok = (got == expected);
    std::cout << "[host][architecture] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // --- Architecture detection ---
    int arm64 = CANN_ASC_STL_DETAIL_ARCH(ARM64);
    int x86_64 = CANN_ASC_STL_DETAIL_ARCH(X86_64);

    // Both must be 0 or 1
    expect_eq("CANN_ASC_STL_DETAIL_ARCH(ARM64) in {0,1}", (arm64 == 0 || arm64 == 1) ? 1 : 0, 1);
    expect_eq("CANN_ASC_STL_DETAIL_ARCH(X86_64) in {0,1}", (x86_64 == 0 || x86_64 == 1) ? 1 : 0, 1);

    // Exactly one should be 1 on standard hosts
    expect_eq("CANN_ASC_STL_DETAIL_ARCH(ARM64)+CANN_ASC_STL_DETAIL_ARCH(X86_64)==1", arm64 + x86_64, 1);

    // Platform-specific expected values
#if defined(__x86_64__) || defined(__amd64__) || (defined(_M_X64) && !defined(_M_ARM64EC))
    expect_eq("CANN_ASC_STL_DETAIL_ARCH(X86_64) on x86_64 host", x86_64, 1);
    expect_eq("CANN_ASC_STL_DETAIL_ARCH(ARM64) on x86_64 host", arm64, 0);
#elif defined(__aarch64__) || defined(_M_ARM64)
    expect_eq("CANN_ASC_STL_DETAIL_ARCH(ARM64) on aarch64 host", arm64, 1);
    expect_eq("CANN_ASC_STL_DETAIL_ARCH(X86_64) on aarch64 host", x86_64, 0);
#endif

    // --- Endianness constants ---
    // NOLINTNEXTLINE(readability/casting)
    expect_eq("CANN_ASC_STL_DETAIL_ENDIAN_LITTLE()", (int)CANN_ASC_STL_DETAIL_ENDIAN_LITTLE(), 0xDEAD);
    // NOLINTNEXTLINE(readability/casting)
    expect_eq("CANN_ASC_STL_DETAIL_ENDIAN_BIG()", (int)CANN_ASC_STL_DETAIL_ENDIAN_BIG(), 0xFACE);
    // NOLINTNEXTLINE(readability/casting)
    expect_eq("CANN_ASC_STL_DETAIL_ENDIAN_PDP()", (int)CANN_ASC_STL_DETAIL_ENDIAN_PDP(), 0xBEEF);

    // Native endianness must be one of the three known constants
    int native = (int)CANN_ASC_STL_DETAIL_ENDIAN_NATIVE();  // NOLINT(readability/casting)
    bool native_valid = (native == 0xDEAD || native == 0xFACE || native == 0xBEEF);
    expect_eq("CANN_ASC_STL_DETAIL_ENDIAN_NATIVE() is valid constant", native_valid ? 1 : 0, 1);

    // CANN_ASC_STL_DETAIL_ENDIAN(NAME) returns 0 or 1
    int endian_little = CANN_ASC_STL_DETAIL_ENDIAN(LITTLE);
    int endian_big = CANN_ASC_STL_DETAIL_ENDIAN(BIG);
    expect_eq("CANN_ASC_STL_DETAIL_ENDIAN(LITTLE) in {0,1}", (endian_little == 0 || endian_little == 1) ? 1 : 0, 1);
    expect_eq("CANN_ASC_STL_DETAIL_ENDIAN(BIG) in {0,1}", (endian_big == 0 || endian_big == 1) ? 1 : 0, 1);

    // On little-endian hosts (most common for Ascend/aarch64 and x86_64)
#if defined(__LITTLE_ENDIAN__) || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
    expect_eq("CANN_ASC_STL_DETAIL_ENDIAN(LITTLE) on little-endian host", endian_little, 1);
    expect_eq("CANN_ASC_STL_DETAIL_ENDIAN(BIG) on little-endian host", endian_big, 0);
#endif

    // CANN_ASC_STL_DETAIL_ENDIAN(LITTLE) and CANN_ASC_STL_DETAIL_ENDIAN(BIG) should be mutually exclusive
    expect_eq("CANN_ASC_STL_DETAIL_ENDIAN(LITTLE)+CANN_ASC_STL_DETAIL_ENDIAN(BIG)<=1", endian_little + endian_big, 1);

    return g_failures == 0 ? 0 : 1;
}
