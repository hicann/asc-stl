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

#include <asc/std/__bit/blsr.h>
#include <iostream>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][blsr] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // unsigned overload – basic cases
    expect_eq("__accl_blsr(0u)", asc::std::__accl_blsr(0u), 0u);
    expect_eq("__accl_blsr(1u)", asc::std::__accl_blsr(1u), 0u);
    expect_eq("__accl_blsr(2u)", asc::std::__accl_blsr(2u), 0u);
    expect_eq("__accl_blsr(3u)", asc::std::__accl_blsr(3u), 2u);
    expect_eq("__accl_blsr(4u)", asc::std::__accl_blsr(4u), 0u);
    expect_eq("__accl_blsr(5u)", asc::std::__accl_blsr(5u), 4u);
    expect_eq("__accl_blsr(6u)", asc::std::__accl_blsr(6u), 4u);
    expect_eq("__accl_blsr(7u)", asc::std::__accl_blsr(7u), 6u);
    expect_eq("__accl_blsr(8u)", asc::std::__accl_blsr(8u), 0u);
    expect_eq("__accl_blsr(12u)", asc::std::__accl_blsr(12u), 8u);
    expect_eq("__accl_blsr(255u)", asc::std::__accl_blsr(255u), 254u);
    expect_eq("__accl_blsr(256u)", asc::std::__accl_blsr(256u), 0u);

    // unsigned overload – edge cases
    expect_eq("__accl_blsr(0x80000000u)", asc::std::__accl_blsr(0x80000000u), 0u);
    expect_eq("__accl_blsr(0xFFFFFFFFu)", asc::std::__accl_blsr(0xFFFFFFFFu), 0xFFFFFFFEu);

    // unsigned long overload
    expect_eq("__accl_blsr(1024ul)", asc::std::__accl_blsr(1024ul), 0ul);
    expect_eq("__accl_blsr(1023ul)", asc::std::__accl_blsr(1023ul), 1022ul);
    expect_eq("__accl_blsr(0x80000000ul)", asc::std::__accl_blsr(0x80000000ul), 0ul);

    // unsigned long long overload
    expect_eq("__accl_blsr(0xFFFFFFFFull)", asc::std::__accl_blsr(0xFFFFFFFFull), 0xFFFFFFFEull);
    expect_eq("__accl_blsr(0x100000000ull)", asc::std::__accl_blsr(0x100000000ull), 0ull);
    expect_eq("__accl_blsr(0x8000000000000000ull)", asc::std::__accl_blsr(0x8000000000000000ull), 0ull);
    expect_eq(
        "__accl_blsr(0xFFFFFFFFFFFFFFFFull)", asc::std::__accl_blsr(0xFFFFFFFFFFFFFFFFull), 0xFFFFFFFFFFFFFFFEull);

    return g_failures == 0 ? 0 : 1;
}
