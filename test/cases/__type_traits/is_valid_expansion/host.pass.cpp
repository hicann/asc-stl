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

#include <asc/std/__type_traits/is_valid_expansion.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_bool(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_valid_expansion] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// ---- Test templates ----

// Takes exactly one type parameter
template <class T>
struct OneType {};

// Takes exactly two type parameters
template <class A, class B>
struct TwoTypes {};

// Variadic: accepts zero or more types
template <class...>
struct Variadic {};

// SFINAE-constrained: only valid when sizeof(T) >= 4
template <class T, class = typename std::enable_if<(sizeof(T) >= 4)>::type>
struct SizeAtLeast4 {};

int main()
{
    // --- Valid expansions ---
    expect_bool("_IsValidExpansion<OneType, int>::value", asc::std::_IsValidExpansion<OneType, int>::value, true);

    expect_bool("_IsValidExpansion<TwoTypes, int, float>::value",
        asc::std::_IsValidExpansion<TwoTypes, int, float>::value, true);

    expect_bool("_IsValidExpansion<Variadic>::value", asc::std::_IsValidExpansion<Variadic>::value, true);

    expect_bool("_IsValidExpansion<Variadic, int, float, double>::value",
        asc::std::_IsValidExpansion<Variadic, int, float, double>::value, true);

    // --- Invalid expansions (wrong arity) ---
    expect_bool("_IsValidExpansion<OneType>::value", asc::std::_IsValidExpansion<OneType>::value, false);

    expect_bool("_IsValidExpansion<OneType, int, float>::value",
        asc::std::_IsValidExpansion<OneType, int, float>::value, false);

    expect_bool("_IsValidExpansion<TwoTypes, int>::value", asc::std::_IsValidExpansion<TwoTypes, int>::value, false);

    // --- SFINAE-constrained template ---
    expect_bool(
        "_IsValidExpansion<SizeAtLeast4, int>::value", asc::std::_IsValidExpansion<SizeAtLeast4, int>::value, true);

    expect_bool(
        "_IsValidExpansion<SizeAtLeast4, char>::value", asc::std::_IsValidExpansion<SizeAtLeast4, char>::value, false);

    // --- Result type checks ---
    expect_bool("is_same<_IsValidExpansion<OneType,int>, true_type>",
        std::is_same<asc::std::_IsValidExpansion<OneType, int>, asc::std::true_type>::value, true);

    expect_bool("is_same<_IsValidExpansion<OneType>, false_type>",
        std::is_same<asc::std::_IsValidExpansion<OneType>, asc::std::false_type>::value, true);

    // --- Usable in SFINAE context ---
    using CheckValid = typename std::enable_if<asc::std::_IsValidExpansion<OneType, int>::value, int>::type;
    expect_bool("enable_if on valid expansion compiles", std::is_same<CheckValid, int>::value, true);

    return g_failures == 0 ? 0 : 1;
}
