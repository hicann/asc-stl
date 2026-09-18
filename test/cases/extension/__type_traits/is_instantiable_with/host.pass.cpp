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

#include <asc/__type_traits/is_instantiable_with.h>
#include <iostream>
#include <type_traits>
#include <vector>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][is_instantiable_with] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][is_instantiable_with] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

// A template that can always be instantiated with any number of type arguments
template <class...>
struct AlwaysInstantiable {};

// A template with exactly one type parameter
template <class T>
struct OneArg {};

// A template with exactly two type parameters
template <class A, class B>
struct TwoArgs {};

// A SFINAE-friendly template that only accepts integral types
template <class T, class = std::enable_if_t<std::is_integral_v<T>>>
struct IntegralOnly {};

// Compile-time checks (non-SFINAE cases — arity mismatch is always SFINAE-safe)
static_assert(asc::__is_instantiable_with<AlwaysInstantiable, int>, "AlwaysInstantiable<int> should be instantiable");
static_assert(asc::__is_instantiable_with<AlwaysInstantiable>, "AlwaysInstantiable<> should be instantiable");
static_assert(!asc::__is_instantiable_with<OneArg, int, double>, "OneArg<int,double> should not be instantiable");
static_assert(!asc::__is_instantiable_with<TwoArgs, int>, "TwoArgs<int> should not be instantiable");
static_assert(asc::__is_instantiable_with<IntegralOnly, int>, "IntegralOnly<int> should be instantiable");
static_assert(!asc::__is_instantiable_with<IntegralOnly, double>, "IntegralOnly<double> should not be instantiable");

int main()
{
    // --- Always instantiable ---
    expect_true("is_instantiable_with<AlwaysInstantiable, int>", asc::__is_instantiable_with<AlwaysInstantiable, int>);
    expect_true("is_instantiable_with<AlwaysInstantiable, int, double, char>",
        asc::__is_instantiable_with<AlwaysInstantiable, int, double, char>);
    expect_true("is_instantiable_with<AlwaysInstantiable>", asc::__is_instantiable_with<AlwaysInstantiable>);

    // --- Fixed arity: OneArg ---
    expect_true("is_instantiable_with<OneArg, int>", asc::__is_instantiable_with<OneArg, int>);
    expect_false("is_instantiable_with<OneArg, int, double>", asc::__is_instantiable_with<OneArg, int, double>);

    // --- Fixed arity: TwoArgs ---
    expect_true("is_instantiable_with<TwoArgs, int, double>", asc::__is_instantiable_with<TwoArgs, int, double>);
    expect_false("is_instantiable_with<TwoArgs, int>", asc::__is_instantiable_with<TwoArgs, int>);
    expect_false(
        "is_instantiable_with<TwoArgs, int, double, char>", asc::__is_instantiable_with<TwoArgs, int, double, char>);

    // --- SFINAE: IntegralOnly ---
    expect_true("is_instantiable_with<IntegralOnly, int>", asc::__is_instantiable_with<IntegralOnly, int>);
    expect_true(
        "is_instantiable_with<IntegralOnly, unsigned long>", asc::__is_instantiable_with<IntegralOnly, unsigned long>);
    expect_false("is_instantiable_with<IntegralOnly, double>", asc::__is_instantiable_with<IntegralOnly, double>);
    expect_false("is_instantiable_with<IntegralOnly, void>", asc::__is_instantiable_with<IntegralOnly, void>);

    // --- Well-known template: std::vector ---
    expect_true("is_instantiable_with<std::vector, int>", asc::__is_instantiable_with<std::vector, int>);

    return g_failures == 0 ? 0 : 1;
}
