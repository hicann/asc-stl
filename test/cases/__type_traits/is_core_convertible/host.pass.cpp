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

#include <asc/std/__type_traits/is_core_convertible.h>
#include <iostream>
#include <string>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][is_core_convertible] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][is_core_convertible] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

// Custom types for testing
struct A {};
struct B {};
struct C {};
struct D {
    D(const C&)  // NOLINT(runtime/explicit)
    {}
};

struct Immovable {
    Immovable() = default;
    Immovable(const Immovable&) = delete;
    Immovable(Immovable&&) = delete;
};

int main()
{
    // Basic arithmetic conversions
    expect_true("__is_core_convertible<int, double>::value", asc::std::__is_core_convertible<int, double>::value);
    expect_true("__is_core_convertible<double, int>::value", asc::std::__is_core_convertible<double, int>::value);
    expect_true(
        "__is_core_convertible<int, unsigned int>::value", asc::std::__is_core_convertible<int, unsigned int>::value);
    expect_true("__is_core_convertible<char, int>::value", asc::std::__is_core_convertible<char, int>::value);
    expect_true("__is_core_convertible<float, double>::value", asc::std::__is_core_convertible<float, double>::value);

    // void cases — explicitly mentioned in header comments
    expect_false("__is_core_convertible<void, void>::value", asc::std::__is_core_convertible<void, void>::value);
    expect_false("__is_core_convertible<int, void>::value", asc::std::__is_core_convertible<int, void>::value);
    expect_false("__is_core_convertible<void, int>::value", asc::std::__is_core_convertible<void, int>::value);

    // Pointer conversions
    expect_true("__is_core_convertible<int*, void*>::value", asc::std::__is_core_convertible<int*, void*>::value);
    expect_false("__is_core_convertible<void*, int*>::value", asc::std::__is_core_convertible<void*, int*>::value);

    // Custom types: no conversion path
    expect_false("__is_core_convertible<A, B>::value", asc::std::__is_core_convertible<A, B>::value);

    // Custom types: converting constructor
    expect_true("__is_core_convertible<C, D>::value", asc::std::__is_core_convertible<C, D>::value);

    // Same type is always core convertible (except void)
    expect_true("__is_core_convertible<int, int>::value", asc::std::__is_core_convertible<int, int>::value);

    // Immovable type to itself — true in C++17+ (function call convertibility)
    expect_true("__is_core_convertible<Immovable, Immovable>::value",
        asc::std::__is_core_convertible<Immovable, Immovable>::value);

    // string conversions
    expect_true("__is_core_convertible<const char*, std::string>::value",
        asc::std::__is_core_convertible<const char*, std::string>::value);
    expect_false("__is_core_convertible<std::string, const char*>::value",
        asc::std::__is_core_convertible<std::string, const char*>::value);

    return g_failures == 0 ? 0 : 1;
}
