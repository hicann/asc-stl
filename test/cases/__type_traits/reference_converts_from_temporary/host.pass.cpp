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

#include <asc/std/__type_traits/reference_converts_from_temporary.h>
#include <iostream>

static int g_failures = 0;

static void expect_eq(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][reference_converts_from_temporary] " << expr << " = " << (got ? "true" : "false")
              << " (expected " << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
#if defined(CANN_ASC_STL_DETAIL_BUILTIN_REFERENCE_CONVERTS_FROM_TEMPORARY)
    // non-reference type -> false (no reference to bind)
    expect_eq("reference_converts_from_temporary_v<int, int>", asc::std::reference_converts_from_temporary_v<int, int>,
        false);

    // const lvalue reference binds to prvalue temporary of same type -> true
    expect_eq("reference_converts_from_temporary_v<const int&, int>",
        asc::std::reference_converts_from_temporary_v<const int&, int>, true);

    // rvalue reference binds to prvalue temporary of same type -> true
    expect_eq("reference_converts_from_temporary_v<int&&, int>",
        asc::std::reference_converts_from_temporary_v<int&&, int>, true);

    // const lvalue reference to prvalue of a different convertible type -> true
    // (int prvalue -> double conversion materializes a temporary)
    expect_eq("reference_converts_from_temporary_v<const int&, double>",
        asc::std::reference_converts_from_temporary_v<const int&, double>, true);

    // const lvalue reference binds to prvalue temporary of same type -> true
    expect_eq("reference_converts_from_temporary_v<const double&, double>",
        asc::std::reference_converts_from_temporary_v<const double&, double>, true);

    // non-const lvalue reference cannot bind to prvalue temporary -> false
    expect_eq("reference_converts_from_temporary_v<int&, int>",
        asc::std::reference_converts_from_temporary_v<int&, int>, false);

    // lvalue reference to an lvalue of the same type -> false (no temporary)
    expect_eq("reference_converts_from_temporary_v<const int&, int&>",
        asc::std::reference_converts_from_temporary_v<const int&, int&>, false);
    expect_eq("reference_converts_from_temporary_v<int&, int&>",
        asc::std::reference_converts_from_temporary_v<int&, int&>, false);
    expect_eq("reference_converts_from_temporary_v<int&&, int&>",
        asc::std::reference_converts_from_temporary_v<int&&, int&>, false);

    // const lvalue reference to an lvalue of a different convertible type -> true
    // (int& lvalue -> double conversion materializes a temporary)
    expect_eq("reference_converts_from_temporary_v<const double&, int&>",
        asc::std::reference_converts_from_temporary_v<const double&, int&>, true);

    // const lvalue reference to prvalue of a different convertible type -> true
    expect_eq("reference_converts_from_temporary_v<const long&, int>",
        asc::std::reference_converts_from_temporary_v<const long&, int>, true);

    // Also test the struct form
    expect_eq("reference_converts_from_temporary<int, int>::value",
        asc::std::reference_converts_from_temporary<int, int>::value, false);
    expect_eq("reference_converts_from_temporary<const int&, int>::value",
        asc::std::reference_converts_from_temporary<const int&, int>::value, true);
    expect_eq("reference_converts_from_temporary<int&&, int>::value",
        asc::std::reference_converts_from_temporary<int&&, int>::value, true);
#else
    // Compiler does not support the builtin — verify header compiles and
    // the trait template is declared (but cannot be instantiated without
    // triggering static_assert)
    std::cout << "[host][reference_converts_from_temporary] "
              << "CANN_ASC_STL_DETAIL_BUILTIN_REFERENCE_CONVERTS_FROM_TEMPORARY not defined; "
              << "trait requires compiler support (static_assert on instantiation)" << std::endl;
    // Verify the template names are visible without instantiating
    using asc::std::reference_converts_from_temporary;
    using asc::std::reference_converts_from_temporary_v;
    std::cout << "[host][reference_converts_from_temporary] "
              << "template names visible — header compiles OK" << std::endl;
#endif
    return g_failures == 0 ? 0 : 1;
}
