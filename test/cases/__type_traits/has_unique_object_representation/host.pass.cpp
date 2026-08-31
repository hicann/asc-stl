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

#include <asc/std/__type_traits/has_unique_object_representation.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][has_unique_object_representation] " << expr << " = " << (cond ? "true" : "false")
              << " (expected true) " << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][has_unique_object_representation] " << expr << " = " << (cond ? "true" : "false")
              << " (expected false) " << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

// Types expected to have unique object representations
struct NoPadding {
    int a;
    int b;
};

// Types expected NOT to have unique object representations (has padding)
struct WithPadding {
    char c;
    int i;
};

// Type with virtual function (not trivially copyable)
struct WithVTable {
    virtual ~WithVTable()
    {}
    int x;
};

enum Color { Red, Green, Blue };

int main()
{
    // Basic integral types - should be true
    expect_true("has_unique_object_representations_v<char>", asc::std::has_unique_object_representations_v<char>);
    expect_true("has_unique_object_representations_v<bool>", asc::std::has_unique_object_representations_v<bool>);
    expect_true("has_unique_object_representations_v<int>", asc::std::has_unique_object_representations_v<int>);
    expect_true("has_unique_object_representations_v<unsigned long>",
        asc::std::has_unique_object_representations_v<unsigned long>);

    // Floating-point types - should be false
    // (e.g. +0.0 and -0.0 are equal but have different bit patterns)
    expect_false("has_unique_object_representations_v<float>", asc::std::has_unique_object_representations_v<float>);
    expect_false("has_unique_object_representations_v<double>", asc::std::has_unique_object_representations_v<double>);

    // Pointer types - should be true
    expect_true("has_unique_object_representations_v<int*>", asc::std::has_unique_object_representations_v<int*>);

    // Struct without padding - should be true
    expect_true(
        "has_unique_object_representations_v<NoPadding>", asc::std::has_unique_object_representations_v<NoPadding>);

    // Struct with padding - should be false
    expect_false(
        "has_unique_object_representations_v<WithPadding>", asc::std::has_unique_object_representations_v<WithPadding>);

    // Type with vtable - should be false
    expect_false(
        "has_unique_object_representations_v<WithVTable>", asc::std::has_unique_object_representations_v<WithVTable>);

    // void - should be false
    expect_false("has_unique_object_representations_v<void>", asc::std::has_unique_object_representations_v<void>);

    // CV qualifications should be stripped
    expect_true(
        "has_unique_object_representations_v<const int>", asc::std::has_unique_object_representations_v<const int>);
    expect_true("has_unique_object_representations_v<volatile int>",
        asc::std::has_unique_object_representations_v<volatile int>);
    expect_true("has_unique_object_representations_v<const volatile int>",
        asc::std::has_unique_object_representations_v<const volatile int>);

    // Array types - extents should be removed
    expect_true("has_unique_object_representations_v<int[3]>", asc::std::has_unique_object_representations_v<int[3]>);
    expect_true(
        "has_unique_object_representations_v<int[2][3]>", asc::std::has_unique_object_representations_v<int[2][3]>);
    expect_false("has_unique_object_representations_v<WithPadding[3]>",
        asc::std::has_unique_object_representations_v<WithPadding[3]>);

    // Struct form (has_unique_object_representations<T>)
    expect_true(
        "has_unique_object_representations<int>::value", asc::std::has_unique_object_representations<int>::value);
    expect_false("has_unique_object_representations<WithPadding>::value",
        asc::std::has_unique_object_representations<WithPadding>::value);

    // Struct form inherits from bool_constant - convertible to bool
    expect_true("bool(has_unique_object_representations<int>)",
        bool(asc::std::has_unique_object_representations<int>{}));  // NOLINT(readability/casting)
    expect_false("bool(has_unique_object_representations<WithPadding>)",
        bool(asc::std::has_unique_object_representations<WithPadding>{}));  // NOLINT(readability/casting)

    // Enum types - should be true
    expect_true("has_unique_object_representations_v<Color>", asc::std::has_unique_object_representations_v<Color>);

    return g_failures == 0 ? 0 : 1;
}
