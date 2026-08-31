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

#include <asc/std/__type_traits/is_trivially_assignable.h>
#include <iostream>

static int g_failures = 0;

static void expect_eq(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_trivially_assignable] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

struct Trivial {
    int a;
    float b;
};

struct NonTrivial {
    int a;
    NonTrivial& operator=(const NonTrivial& other)
    {
        a = other.a;
        return *this;
    }
};

int main()
{
    // --- Fundamental types: trivially assignable to same type ---
    expect_eq("is_trivially_assignable<int&, int>::value", asc::std::is_trivially_assignable<int&, int>::value, true);
    expect_eq("is_trivially_assignable<int&, int&>::value", asc::std::is_trivially_assignable<int&, int&>::value, true);
    expect_eq(
        "is_trivially_assignable<float&, float>::value", asc::std::is_trivially_assignable<float&, float>::value, true);
    expect_eq("is_trivially_assignable<double&, double>::value",
        asc::std::is_trivially_assignable<double&, double>::value, true);
    expect_eq(
        "is_trivially_assignable<int*&, int*>::value", asc::std::is_trivially_assignable<int*&, int*>::value, true);

    // --- Trivially assignable with implicit conversion (type mismatch but still trivial) ---
    // is_trivially_assignable<T, U> checks whether declval<T>() = declval<U>() is a trivial
    // assignment. Implicit conversions do not make the assignment non-trivial.
    expect_eq(
        "is_trivially_assignable<int&, double>::value", asc::std::is_trivially_assignable<int&, double>::value, true);
    expect_eq(
        "is_trivially_assignable<float&, int>::value", asc::std::is_trivially_assignable<float&, int>::value, true);

    // --- Not trivially assignable: const target (cannot assign to const) ---
    expect_eq("is_trivially_assignable<const int&, int>::value",
        asc::std::is_trivially_assignable<const int&, int>::value, false);

    // --- Trivial struct: trivially assignable ---
    expect_eq("is_trivially_assignable<Trivial&, Trivial>::value",
        asc::std::is_trivially_assignable<Trivial&, Trivial>::value, true);
    expect_eq("is_trivially_assignable<Trivial&, Trivial&>::value",
        asc::std::is_trivially_assignable<Trivial&, Trivial&>::value, true);

    // --- Non-trivial assignment operator: NOT trivially assignable ---
    expect_eq("is_trivially_assignable<NonTrivial&, NonTrivial>::value",
        asc::std::is_trivially_assignable<NonTrivial&, NonTrivial>::value, false);

    // --- _v variable template ---
    expect_eq("is_trivially_assignable_v<int&, int>", asc::std::is_trivially_assignable_v<int&, int>, true);
    expect_eq("is_trivially_assignable_v<int&, double>", asc::std::is_trivially_assignable_v<int&, double>, true);
    expect_eq(
        "is_trivially_assignable_v<const int&, int>", asc::std::is_trivially_assignable_v<const int&, int>, false);
    expect_eq("is_trivially_assignable_v<NonTrivial&, NonTrivial>",
        asc::std::is_trivially_assignable_v<NonTrivial&, NonTrivial>, false);

    return g_failures == 0 ? 0 : 1;
}
