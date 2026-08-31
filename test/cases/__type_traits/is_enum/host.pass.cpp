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

#include <asc/std/__type_traits/is_enum.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_enum] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// Enum categories exercised by the checks below
enum Enum1 : short { E1, E2, E3 = 64, E4 = 78 };
enum class Enum2 : long { C1, C2, C3 = 64, C4 = 78 };

// Additional enum types
enum Enum3 { F1, F2, F3 };
enum class Enum4 : unsigned int { G1, G2, G3 };

// Non-enum types
struct S {};
class C {};
union U {};

int main()
{
    // is_enum on enum types -> true
    expect_true("is_enum<Enum1>::value", asc::std::is_enum<Enum1>::value, true);
    expect_true("is_enum<Enum2>::value", asc::std::is_enum<Enum2>::value, true);
    expect_true("is_enum<Enum3>::value", asc::std::is_enum<Enum3>::value, true);
    expect_true("is_enum<Enum4>::value", asc::std::is_enum<Enum4>::value, true);

    // is_enum_v variable template
    expect_true("is_enum_v<Enum1>", asc::std::is_enum_v<Enum1>, true);
    expect_true("is_enum_v<Enum2>", asc::std::is_enum_v<Enum2>, true);
    expect_true("is_enum_v<Enum3>", asc::std::is_enum_v<Enum3>, true);
    expect_true("is_enum_v<Enum4>", asc::std::is_enum_v<Enum4>, true);

    // is_enum on non-enum types -> false
    expect_true("is_enum<int>::value", asc::std::is_enum<int>::value, false);
    expect_true("is_enum<short>::value", asc::std::is_enum<short>::value, false);
    expect_true("is_enum<long>::value", asc::std::is_enum<long>::value, false);
    expect_true("is_enum<float>::value", asc::std::is_enum<float>::value, false);
    expect_true("is_enum<double>::value", asc::std::is_enum<double>::value, false);
    expect_true("is_enum<bool>::value", asc::std::is_enum<bool>::value, false);
    expect_true("is_enum<char>::value", asc::std::is_enum<char>::value, false);
    expect_true("is_enum<void>::value", asc::std::is_enum<void>::value, false);
    expect_true("is_enum<S>::value", asc::std::is_enum<S>::value, false);
    expect_true("is_enum<C>::value", asc::std::is_enum<C>::value, false);
    expect_true("is_enum<U>::value", asc::std::is_enum<U>::value, false);
    expect_true("is_enum<int*>::value", asc::std::is_enum<int*>::value, false);

    // is_enum_v on non-enum types
    expect_true("is_enum_v<int>", asc::std::is_enum_v<int>, false);
    expect_true("is_enum_v<float>", asc::std::is_enum_v<float>, false);
    expect_true("is_enum_v<S>", asc::std::is_enum_v<S>, false);

    // is_enum on enum underlying types -> false
    expect_true("is_enum<short>::value (underlying of Enum1)", asc::std::is_enum<short>::value, false);
    expect_true("is_enum<long>::value (underlying of Enum2)", asc::std::is_enum<long>::value, false);

    // is_enum on enum values (should be the enum type)
    expect_true("is_enum<decltype(E1)>::value", asc::std::is_enum<decltype(E1)>::value, true);
    expect_true("is_enum<decltype(E3)>::value", asc::std::is_enum<decltype(E3)>::value, true);
    expect_true("is_enum<decltype(Enum2::C1)>::value", asc::std::is_enum<decltype(Enum2::C1)>::value, true);

    // Verify is_enum inherits from bool_constant (convertible to bool)
    expect_true("static_cast<bool>(is_enum<Enum1>{})", static_cast<bool>(asc::std::is_enum<Enum1>{}), true);
    expect_true("static_cast<bool>(is_enum<int>{})", static_cast<bool>(asc::std::is_enum<int>{}), false);

    return g_failures == 0 ? 0 : 1;
}
