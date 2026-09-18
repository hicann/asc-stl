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

#include <asc/std/__type_traits/is_trivially_default_constructible.h>
#include <iostream>

static int g_failures = 0;

static void expect_eq(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_trivially_default_constructible] " << expr << " = " << (got ? "true" : "false")
              << " (expected " << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// Trivially default constructible types
struct TrivialStruct {
    int a;
    float b;
};

struct TrivialDerived : TrivialStruct {
    double c;
};

enum TrivialEnum { E_A, E_B, E_C };

// Non-trivially default constructible types
struct NonTrivialStruct {
    int a;
    NonTrivialStruct() : a(42)
    {}
};

struct HasNonTrivialMember {
    NonTrivialStruct m;
};

int main()
{
    // Basic scalar types - trivially default constructible
    expect_eq("is_trivially_default_constructible_v<int>", asc::std::is_trivially_default_constructible_v<int>, true);
    expect_eq(
        "is_trivially_default_constructible_v<float>", asc::std::is_trivially_default_constructible_v<float>, true);
    expect_eq(
        "is_trivially_default_constructible_v<double>", asc::std::is_trivially_default_constructible_v<double>, true);
    expect_eq("is_trivially_default_constructible_v<char>", asc::std::is_trivially_default_constructible_v<char>, true);
    expect_eq("is_trivially_default_constructible_v<bool>", asc::std::is_trivially_default_constructible_v<bool>, true);
    expect_eq("is_trivially_default_constructible_v<long>", asc::std::is_trivially_default_constructible_v<long>, true);
    expect_eq("is_trivially_default_constructible_v<unsigned>",
        asc::std::is_trivially_default_constructible_v<unsigned>, true);

    // Pointer types - trivially default constructible
    expect_eq("is_trivially_default_constructible_v<int*>", asc::std::is_trivially_default_constructible_v<int*>, true);

    // Enum types - trivially default constructible
    expect_eq("is_trivially_default_constructible_v<TrivialEnum>",
        asc::std::is_trivially_default_constructible_v<TrivialEnum>, true);

    // Trivial structs
    expect_eq("is_trivially_default_constructible_v<TrivialStruct>",
        asc::std::is_trivially_default_constructible_v<TrivialStruct>, true);
    expect_eq("is_trivially_default_constructible_v<TrivialDerived>",
        asc::std::is_trivially_default_constructible_v<TrivialDerived>, true);

    // Array of trivial types
    expect_eq(
        "is_trivially_default_constructible_v<int[5]>", asc::std::is_trivially_default_constructible_v<int[5]>, true);
    expect_eq("is_trivially_default_constructible_v<float[10]>",
        asc::std::is_trivially_default_constructible_v<float[10]>, true);

    // Non-trivially default constructible types
    expect_eq("is_trivially_default_constructible_v<NonTrivialStruct>",
        asc::std::is_trivially_default_constructible_v<NonTrivialStruct>, false);
    expect_eq("is_trivially_default_constructible_v<HasNonTrivialMember>",
        asc::std::is_trivially_default_constructible_v<HasNonTrivialMember>, false);

    // Using the struct form (::value) in addition to _v
    expect_eq("is_trivially_default_constructible<int>::value",
        asc::std::is_trivially_default_constructible<int>::value, true);
    expect_eq("is_trivially_default_constructible<NonTrivialStruct>::value",
        asc::std::is_trivially_default_constructible<NonTrivialStruct>::value, false);
    expect_eq("is_trivially_default_constructible<TrivialStruct>::value",
        asc::std::is_trivially_default_constructible<TrivialStruct>::value, true);
    expect_eq("is_trivially_default_constructible<HasNonTrivialMember>::value",
        asc::std::is_trivially_default_constructible<HasNonTrivialMember>::value, false);

    return g_failures == 0 ? 0 : 1;
}
