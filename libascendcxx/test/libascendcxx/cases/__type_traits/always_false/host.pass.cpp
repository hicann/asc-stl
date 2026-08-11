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

#include <asc/std/__type_traits/always_false.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][always_false] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][always_false] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

struct Incomplete;

template <typename... Ts>
constexpr bool dependent_always_false()
{
    return asc::std::__always_false_v<Ts...>;
}

int main()
{
    // Basic: always false regardless of type argument
    expect_false("__always_false_v<int>", asc::std::__always_false_v<int>);
    expect_false("__always_false_v<double>", asc::std::__always_false_v<double>);
    expect_false("__always_false_v<void>", asc::std::__always_false_v<void>);
    expect_false("__always_false_v<char>", asc::std::__always_false_v<char>);

    // Variadic: multiple type arguments
    expect_false("__always_false_v<int, double>", asc::std::__always_false_v<int, double>);
    expect_false("__always_false_v<int, double, char>", asc::std::__always_false_v<int, double, char>);

    // Empty pack
    expect_false("__always_false_v<>", asc::std::__always_false_v<>);

    // cv-qualified types
    expect_false("__always_false_v<const int>", asc::std::__always_false_v<const int>);
    expect_false("__always_false_v<volatile int>", asc::std::__always_false_v<volatile int>);
    expect_false("__always_false_v<const volatile int>", asc::std::__always_false_v<const volatile int>);

    // Reference and pointer types
    expect_false("__always_false_v<int&>", asc::std::__always_false_v<int&>);
    expect_false("__always_false_v<int*>", asc::std::__always_false_v<int*>);
    expect_false("__always_false_v<const int*>", asc::std::__always_false_v<const int*>);

    // Array and incomplete types
    expect_false("__always_false_v<int[3]>", asc::std::__always_false_v<int[3]>);
    expect_false("__always_false_v<Incomplete>", asc::std::__always_false_v<Incomplete>);

    // Compile-time and dependent-template usage
    static_assert(!asc::std::__always_false_v<int>, "should be false");
    static_assert(!asc::std::__always_false_v<int, double, char>, "should be false");
    static_assert(!asc::std::__always_false_v<>, "should be false");
    static_assert(!asc::std::__always_false_v<Incomplete>, "should accept incomplete types");
    static_assert(!dependent_always_false<int>(), "dependent instantiation should be false");
    static_assert(!dependent_always_false<Incomplete, int>(), "dependent pack should be false");

    // Cross-check: value should equal false literal
    expect_true("__always_false_v<int> == false", asc::std::__always_false_v<int> == false);
    expect_true("__always_false_v<int,double> == false", asc::std::__always_false_v<int, double> == false);
    expect_true("dependent_always_false<Incomplete>() == false", !dependent_always_false<Incomplete>());

    return g_failures == 0 ? 0 : 1;
}
