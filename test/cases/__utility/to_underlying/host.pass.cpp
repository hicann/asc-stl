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

#include <asc/std/__utility/to_underlying.h>
#include <iostream>

static int g_failures = 0;

template <typename T, typename U>
static void expect_eq(const char* expr, T got, U expected)
{
    bool ok = (got == expected);
    std::cout << "[host][to_underlying] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

enum Color : unsigned { Red = 0, Green = 1, Blue = 2 };
enum class Status : int { Active = 10, Inactive = 20, Pending = -5 };
enum SmallEnum : unsigned char { SA = 0, SB = 255 };

int main()
{
    // Basic unscoped enum
    expect_eq("to_underlying(Red)", asc::std::to_underlying(Red), 0u);
    expect_eq("to_underlying(Green)", asc::std::to_underlying(Green), 1u);
    expect_eq("to_underlying(Blue)", asc::std::to_underlying(Blue), 2u);

    // Scoped enum with explicit underlying type (int)
    expect_eq("to_underlying(Status::Active)", asc::std::to_underlying(Status::Active), 10);
    expect_eq("to_underlying(Status::Inactive)", asc::std::to_underlying(Status::Inactive), 20);
    expect_eq("to_underlying(Status::Pending)", asc::std::to_underlying(Status::Pending), -5);

    // Enum with unsigned char underlying type
    expect_eq("to_underlying(SA)", static_cast<int>(asc::std::to_underlying(SA)), 0);
    expect_eq("to_underlying(SB)", static_cast<int>(asc::std::to_underlying(SB)), 255);

    // Value not explicitly named in enum (valid enum value via cast)
    Color c = static_cast<Color>(42);
    expect_eq("to_underlying(static_cast<Color>(42))", asc::std::to_underlying(c), 42u);

    // Constexpr context
    constexpr unsigned ce = asc::std::to_underlying(Green);
    expect_eq("constexpr to_underlying(Green)", ce, 1u);

    return g_failures == 0 ? 0 : 1;
}
