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

#include <asc/std/__cstdlib/abs.h>
#include <iostream>
#include <climits>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][abs] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // abs(int)
    expect_eq("abs(0)", asc::std::abs(0), 0);
    expect_eq("abs(1)", asc::std::abs(1), 1);
    expect_eq("abs(-1)", asc::std::abs(-1), 1);
    expect_eq("abs(42)", asc::std::abs(42), 42);
    expect_eq("abs(-42)", asc::std::abs(-42), 42);
    expect_eq("abs(2147483647)", asc::std::abs(2147483647), 2147483647);
    expect_eq("abs(-2147483647)", asc::std::abs(-2147483647), 2147483647);

    // labs(long)
    expect_eq("labs(0L)", asc::std::labs(0L), 0L);
    expect_eq("labs(1L)", asc::std::labs(1L), 1L);
    expect_eq("labs(-1L)", asc::std::labs(-1L), 1L);
    expect_eq("labs(100000L)", asc::std::labs(100000L), 100000L);
    expect_eq("labs(-100000L)", asc::std::labs(-100000L), 100000L);

    // abs(long) — overload dispatches to labs
    expect_eq("abs(0L)", asc::std::abs(0L), 0L);
    expect_eq("abs(-123L)", asc::std::abs(-123L), 123L);
    expect_eq("abs(456L)", asc::std::abs(456L), 456L);

    // llabs(long long)
    expect_eq("llabs(0LL)", asc::std::llabs(0LL), 0LL);
    expect_eq("llabs(1LL)", asc::std::llabs(1LL), 1LL);
    expect_eq("llabs(-1LL)", asc::std::llabs(-1LL), 1LL);
    expect_eq("llabs(9999999999LL)", asc::std::llabs(9999999999LL), 9999999999LL);
    expect_eq("llabs(-9999999999LL)", asc::std::llabs(-9999999999LL), 9999999999LL);

    // abs(long long) — overload dispatches to llabs
    expect_eq("abs(0LL)", asc::std::abs(0LL), 0LL);
    expect_eq("abs(-777LL)", asc::std::abs(-777LL), 777LL);
    expect_eq("abs(888LL)", asc::std::abs(888LL), 888LL);

    // constexpr context
    static_assert(asc::std::abs(-5) == 5, "constexpr abs(-5) == 5");
    static_assert(asc::std::abs(5) == 5, "constexpr abs(5) == 5");
    static_assert(asc::std::labs(-100L) == 100L, "constexpr labs(-100L) == 100L");
    static_assert(asc::std::llabs(-1000LL) == 1000LL, "constexpr llabs(-1000LL) == 1000LL");

    return g_failures == 0 ? 0 : 1;
}
