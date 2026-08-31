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

#include <asc/std/__type_traits/is_reference.h>
#include <iostream>

static int g_failures = 0;

static void expect_eq(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_reference] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // ---- is_reference ----
    expect_eq("is_reference_v<int>", asc::std::is_reference_v<int>, false);
    expect_eq("is_reference_v<int&>", asc::std::is_reference_v<int&>, true);
    expect_eq("is_reference_v<int&&>", asc::std::is_reference_v<int&&>, true);
    expect_eq("is_reference_v<void>", asc::std::is_reference_v<void>, false);
    expect_eq("is_reference_v<double>", asc::std::is_reference_v<double>, false);
    expect_eq("is_reference_v<double&>", asc::std::is_reference_v<double&>, true);
    expect_eq("is_reference_v<double&&>", asc::std::is_reference_v<double&&>, true);
    expect_eq("is_reference_v<const int&>", asc::std::is_reference_v<const int&>, true);
    expect_eq("is_reference_v<const int&&>", asc::std::is_reference_v<const int&&>, true);
    expect_eq("is_reference_v<int*>", asc::std::is_reference_v<int*>, false);
    expect_eq("is_reference_v<int*&>", asc::std::is_reference_v<int*&>, true);
    expect_eq("is_reference_v<int*&&>", asc::std::is_reference_v<int*&&>, true);

    expect_eq("is_reference<int>::value", asc::std::is_reference<int>::value, false);
    expect_eq("is_reference<int&>::value", asc::std::is_reference<int&>::value, true);
    expect_eq("is_reference<int&&>::value", asc::std::is_reference<int&&>::value, true);

    // ---- is_lvalue_reference ----
    expect_eq("is_lvalue_reference_v<int>", asc::std::is_lvalue_reference_v<int>, false);
    expect_eq("is_lvalue_reference_v<int&>", asc::std::is_lvalue_reference_v<int&>, true);
    expect_eq("is_lvalue_reference_v<int&&>", asc::std::is_lvalue_reference_v<int&&>, false);
    expect_eq("is_lvalue_reference_v<const int&>", asc::std::is_lvalue_reference_v<const int&>, true);
    expect_eq("is_lvalue_reference_v<void>", asc::std::is_lvalue_reference_v<void>, false);

    expect_eq("is_lvalue_reference<int>::value", asc::std::is_lvalue_reference<int>::value, false);
    expect_eq("is_lvalue_reference<int&>::value", asc::std::is_lvalue_reference<int&>::value, true);
    expect_eq("is_lvalue_reference<int&&>::value", asc::std::is_lvalue_reference<int&&>::value, false);

    // ---- is_rvalue_reference ----
    expect_eq("is_rvalue_reference_v<int>", asc::std::is_rvalue_reference_v<int>, false);
    expect_eq("is_rvalue_reference_v<int&>", asc::std::is_rvalue_reference_v<int&>, false);
    expect_eq("is_rvalue_reference_v<int&&>", asc::std::is_rvalue_reference_v<int&&>, true);
    expect_eq("is_rvalue_reference_v<const int&&>", asc::std::is_rvalue_reference_v<const int&&>, true);
    expect_eq("is_rvalue_reference_v<void>", asc::std::is_rvalue_reference_v<void>, false);

    expect_eq("is_rvalue_reference<int>::value", asc::std::is_rvalue_reference<int>::value, false);
    expect_eq("is_rvalue_reference<int&>::value", asc::std::is_rvalue_reference<int&>::value, false);
    expect_eq("is_rvalue_reference<int&&>::value", asc::std::is_rvalue_reference<int&&>::value, true);

    // ---- relationship: is_reference == is_lvalue_reference || is_rvalue_reference ----
    expect_eq("is_reference_v<int&> == (is_lvalue_reference_v<int&> || is_rvalue_reference_v<int&>)",
        asc::std::is_reference_v<int&>, asc::std::is_lvalue_reference_v<int&> || asc::std::is_rvalue_reference_v<int&>);
    expect_eq("is_reference_v<int&&> == (is_lvalue_reference_v<int&&> || is_rvalue_reference_v<int&&>)",
        asc::std::is_reference_v<int&&>,
        asc::std::is_lvalue_reference_v<int&&> || asc::std::is_rvalue_reference_v<int&&>);
    expect_eq("is_reference_v<int> == (is_lvalue_reference_v<int> || is_rvalue_reference_v<int>)",
        asc::std::is_reference_v<int>, asc::std::is_lvalue_reference_v<int> || asc::std::is_rvalue_reference_v<int>);

    return g_failures == 0 ? 0 : 1;
}
