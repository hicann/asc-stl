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

#include <asc/std/__type_traits/reference_constructs_from_temporary.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][reference_constructs_from_temporary] " << expr << " = " << (got ? "true" : "false")
              << " (expected " << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // const lvalue reference binds to temporary of same type -> true
    expect_eq("reference_constructs_from_temporary<const int&, int>::value",
        asc::std::reference_constructs_from_temporary<const int&, int>::value, true);
    expect_eq("reference_constructs_from_temporary_v<const int&, int>",
        asc::std::reference_constructs_from_temporary_v<const int&, int>, true);

    // non-const lvalue reference cannot bind to temporary -> false
    expect_eq("reference_constructs_from_temporary<int&, int>::value",
        asc::std::reference_constructs_from_temporary<int&, int>::value, false);
    expect_eq("reference_constructs_from_temporary_v<int&, int>",
        asc::std::reference_constructs_from_temporary_v<int&, int>, false);

    // rvalue reference binds to temporary of same type -> true
    expect_eq("reference_constructs_from_temporary<int&&, int>::value",
        asc::std::reference_constructs_from_temporary<int&&, int>::value, true);
    expect_eq("reference_constructs_from_temporary_v<int&&, int>",
        asc::std::reference_constructs_from_temporary_v<int&&, int>, true);

    // lvalue reference to non-temporary (lvalue of same type) -> false
    expect_eq("reference_constructs_from_temporary<const int&, int&>::value",
        asc::std::reference_constructs_from_temporary<const int&, int&>::value, false);
    expect_eq("reference_constructs_from_temporary<int&, int&>::value",
        asc::std::reference_constructs_from_temporary<int&, int&>::value, false);
    expect_eq("reference_constructs_from_temporary<int&&, int&>::value",
        asc::std::reference_constructs_from_temporary<int&&, int&>::value, false);

    // const lvalue reference to a different convertible type temporary -> true
    expect_eq("reference_constructs_from_temporary_v<const double&, int>",
        asc::std::reference_constructs_from_temporary_v<const double&, int>, true);

    // const lvalue reference to an lvalue of a different convertible type -> true
    // U = int& is an lvalue of type int; binding const double& to it requires int->double
    // conversion, which materializes a temporary double that the reference binds to.
    expect_eq("reference_constructs_from_temporary_v<const double&, int&>",
        asc::std::reference_constructs_from_temporary_v<const double&, int&>, true);

    // non-reference type -> false (no reference to construct)
    expect_eq("reference_constructs_from_temporary_v<int, int>",
        asc::std::reference_constructs_from_temporary_v<int, int>, false);

    // const lvalue reference to prvalue of long -> true (convertible temporary)
    expect_eq("reference_constructs_from_temporary_v<const long&, int>",
        asc::std::reference_constructs_from_temporary_v<const long&, int>, true);

    return g_failures == 0 ? 0 : 1;
}
