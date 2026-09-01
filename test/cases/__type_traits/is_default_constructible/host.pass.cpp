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

#include <asc/std/__type_traits/is_default_constructible.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][is_default_constructible] " << expr << " = " << (cond ? "true" : "false")
              << " (expected true) " << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][is_default_constructible] " << expr << " = " << (cond ? "true" : "false")
              << " (expected false) " << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

// Test types
struct DefaultConstructible {
    int x;
};

struct WithDefaultCtor {
    int x;
    WithDefaultCtor() : x(42)
    {}
};

struct NoDefaultCtor {
    int x;
    NoDefaultCtor(int v) : x(v)  // NOLINT(runtime/explicit)
    {}
};

struct DeletedDefaultCtor {
    DeletedDefaultCtor() = delete;
    DeletedDefaultCtor([[maybe_unused]] int value)  // NOLINT(runtime/explicit)
    {}
};

int main()
{
    // Basic types
    expect_true("is_default_constructible_v<int>", asc::std::is_default_constructible_v<int>);
    expect_true("is_default_constructible_v<double>", asc::std::is_default_constructible_v<double>);
    expect_true("is_default_constructible_v<float>", asc::std::is_default_constructible_v<float>);
    expect_true("is_default_constructible_v<char>", asc::std::is_default_constructible_v<char>);
    expect_true("is_default_constructible_v<bool>", asc::std::is_default_constructible_v<bool>);
    expect_true("is_default_constructible_v<long>", asc::std::is_default_constructible_v<long>);
    expect_true("is_default_constructible_v<unsigned>", asc::std::is_default_constructible_v<unsigned>);

    // Pointer types
    expect_true("is_default_constructible_v<int*>", asc::std::is_default_constructible_v<int*>);
    expect_true("is_default_constructible_v<void*>", asc::std::is_default_constructible_v<void*>);

    // void is not default constructible
    expect_false("is_default_constructible_v<void>", asc::std::is_default_constructible_v<void>);

    // References are not default constructible
    expect_false("is_default_constructible_v<int&>", asc::std::is_default_constructible_v<int&>);
    expect_false("is_default_constructible_v<int&&>", asc::std::is_default_constructible_v<int&&>);

    // User-defined types
    expect_true(
        "is_default_constructible_v<DefaultConstructible>", asc::std::is_default_constructible_v<DefaultConstructible>);
    expect_true("is_default_constructible_v<WithDefaultCtor>", asc::std::is_default_constructible_v<WithDefaultCtor>);
    expect_false("is_default_constructible_v<NoDefaultCtor>", asc::std::is_default_constructible_v<NoDefaultCtor>);
    expect_false(
        "is_default_constructible_v<DeletedDefaultCtor>", asc::std::is_default_constructible_v<DeletedDefaultCtor>);

    // Arrays
    expect_true("is_default_constructible_v<int[5]>", asc::std::is_default_constructible_v<int[5]>);
    expect_false("is_default_constructible_v<int[]>", asc::std::is_default_constructible_v<int[]>);

    // const-qualified types
    expect_true("is_default_constructible_v<const int>", asc::std::is_default_constructible_v<const int>);

    // The struct form (::value)
    expect_true("is_default_constructible<int>::value", asc::std::is_default_constructible<int>::value);
    expect_false("is_default_constructible<void>::value", asc::std::is_default_constructible<void>::value);
    expect_false(
        "is_default_constructible<NoDefaultCtor>::value", asc::std::is_default_constructible<NoDefaultCtor>::value);

    // Enum
    enum Color { Red, Green, Blue };
    expect_true("is_default_constructible_v<Color>", asc::std::is_default_constructible_v<Color>);

    // Union
    union U {
        int a;
        double b;
    };
    expect_true("is_default_constructible_v<U>", asc::std::is_default_constructible_v<U>);

    return g_failures == 0 ? 0 : 1;
}
