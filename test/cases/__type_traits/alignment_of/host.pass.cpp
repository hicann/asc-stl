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

#include <asc/std/__type_traits/alignment_of.h>
#include <iostream>
#include <cstddef>

static int g_failures = 0;

static void expect_eq(const char* expr, std::size_t got, std::size_t expected)
{
    bool ok = (got == expected);
    std::cout << "[host][alignment_of] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // --- Basic types: ::value vs alignof ---
    expect_eq("alignment_of<char>::value", asc::std::alignment_of<char>::value, alignof(char));
    expect_eq("alignment_of<short>::value", asc::std::alignment_of<short>::value, alignof(short));
    expect_eq("alignment_of<int>::value", asc::std::alignment_of<int>::value, alignof(int));
    expect_eq("alignment_of<long>::value", asc::std::alignment_of<long>::value, alignof(long));
    expect_eq("alignment_of<float>::value", asc::std::alignment_of<float>::value, alignof(float));
    expect_eq("alignment_of<double>::value", asc::std::alignment_of<double>::value, alignof(double));
    expect_eq("alignment_of<long long>::value", asc::std::alignment_of<long long>::value, alignof(long long));

    // --- _v variable template ---
    expect_eq("alignment_of_v<char>", asc::std::alignment_of_v<char>, alignof(char));
    expect_eq("alignment_of_v<int>", asc::std::alignment_of_v<int>, alignof(int));
    expect_eq("alignment_of_v<double>", asc::std::alignment_of_v<double>, alignof(double));
    expect_eq("alignment_of_v<long long>", asc::std::alignment_of_v<long long>, alignof(long long));

    // --- Pointer type ---
    expect_eq("alignment_of<int*>::value", asc::std::alignment_of<int*>::value, alignof(int*));

    // --- Custom aligned structs (hardcoded expected) ---
    struct alignas(16) Aligned16 {
        char data[16];
    };
    struct alignas(32) Aligned32 {
        char data[32];
    };
    struct alignas(1) Packed1 {
        char c;
    };

    expect_eq("alignment_of<Aligned16>::value", asc::std::alignment_of<Aligned16>::value, 16u);
    expect_eq("alignment_of<Aligned32>::value", asc::std::alignment_of<Aligned32>::value, 32u);
    expect_eq("alignment_of<Packed1>::value", asc::std::alignment_of<Packed1>::value, 1u);
    expect_eq("alignment_of_v<Aligned16>", asc::std::alignment_of_v<Aligned16>, 16u);
    expect_eq("alignment_of_v<Aligned32>", asc::std::alignment_of_v<Aligned32>, 32u);

    // --- integral_constant interface: operator() and implicit conversion ---
    auto ic = asc::std::alignment_of<int>{};
    expect_eq("alignment_of<int>{}()", static_cast<std::size_t>(ic()), alignof(int));
    expect_eq("static_cast<size_t>(alignment_of<int>{})", static_cast<std::size_t>(asc::std::alignment_of<int>{}),
        alignof(int));

    // --- char8_t / char16_t / char32_t if available (C++11+) ---
    expect_eq("alignment_of<char16_t>::value", asc::std::alignment_of<char16_t>::value, alignof(char16_t));
    expect_eq("alignment_of<char32_t>::value", asc::std::alignment_of<char32_t>::value, alignof(char32_t));

    return g_failures == 0 ? 0 : 1;
}
