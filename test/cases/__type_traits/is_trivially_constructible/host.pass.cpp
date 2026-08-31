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

#include <asc/std/__type_traits/is_trivially_constructible.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_trivially_constructible] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

struct TrivialStruct {
    int a;
    float b;
};

struct NonTrivialStruct {
    int a;
    NonTrivialStruct() : a(42)
    {}
    NonTrivialStruct(int x) : a(x)  // NOLINT(runtime/explicit)
    {}
};

struct DefaultedStruct {
    int a;
    DefaultedStruct() = default;
};

int main()
{
    // Default construction - trivial scalar types
    expect_true("is_trivially_constructible_v<int>", asc::std::is_trivially_constructible_v<int>, true);
    expect_true("is_trivially_constructible_v<float>", asc::std::is_trivially_constructible_v<float>, true);
    expect_true("is_trivially_constructible_v<double>", asc::std::is_trivially_constructible_v<double>, true);
    expect_true(
        "is_trivially_constructible_v<TrivialStruct>", asc::std::is_trivially_constructible_v<TrivialStruct>, true);
    expect_true(
        "is_trivially_constructible_v<DefaultedStruct>", asc::std::is_trivially_constructible_v<DefaultedStruct>, true);

    // Default construction - non-trivial types
    expect_true("is_trivially_constructible_v<NonTrivialStruct>",
        asc::std::is_trivially_constructible_v<NonTrivialStruct>, false);

    // Construction with arguments - trivial
    expect_true("is_trivially_constructible_v<int, int>", asc::std::is_trivially_constructible_v<int, int>, true);
    expect_true("is_trivially_constructible_v<int, double>", asc::std::is_trivially_constructible_v<int, double>, true);
    expect_true("is_trivially_constructible_v<float, int>", asc::std::is_trivially_constructible_v<float, int>, true);

    // Aggregate types are NOT constructible via parentheses with multiple args (C++17):
    // TrivialStruct(int, float) looks for a constructor, not aggregate init.
    expect_true("is_trivially_constructible_v<TrivialStruct, int, float>",
        asc::std::is_trivially_constructible_v<TrivialStruct, int, float>, false);

    // Construction with arguments - not constructible or non-trivial
    expect_true("is_trivially_constructible_v<int, const char*>",
        asc::std::is_trivially_constructible_v<int, const char*>, false);
    expect_true("is_trivially_constructible_v<NonTrivialStruct, int>",
        asc::std::is_trivially_constructible_v<NonTrivialStruct, int>, false);

    // ::value member (struct form)
    expect_true("is_trivially_constructible<int>::value", asc::std::is_trivially_constructible<int>::value, true);
    expect_true("is_trivially_constructible<NonTrivialStruct>::value",
        asc::std::is_trivially_constructible<NonTrivialStruct>::value, false);
    expect_true(
        "is_trivially_constructible<int, int>::value", asc::std::is_trivially_constructible<int, int>::value, true);
    expect_true("is_trivially_constructible<int, const char*>::value",
        asc::std::is_trivially_constructible<int, const char*>::value, false);

    // Inherits from bool_constant (true_type / false_type)
    expect_true("is_base_of<true_type, is_trivially_constructible<int>>",
        std::is_base_of_v<asc::std::true_type, asc::std::is_trivially_constructible<int>>, true);
    expect_true("is_base_of<false_type, is_trivially_constructible<NonTrivialStruct>>",
        std::is_base_of_v<asc::std::false_type, asc::std::is_trivially_constructible<NonTrivialStruct>>, true);

    return g_failures == 0 ? 0 : 1;
}
