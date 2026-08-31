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

#include <asc/std/__type_traits/is_one_of.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][is_one_of] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][is_one_of] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

int main()
{
    // Basic: type is one of the listed types
    expect_true("is_one_of_v<int, int>", asc::std::__is_one_of_v<int, int>);
    expect_true("is_one_of_v<int, char, int, double>", asc::std::__is_one_of_v<int, char, int, double>);
    expect_true("is_one_of_v<int, int, int>", asc::std::__is_one_of_v<int, int, int>);

    // Type is not one of the listed types
    expect_false("is_one_of_v<int, char>", asc::std::__is_one_of_v<int, char>);
    expect_false("is_one_of_v<int, char, double, float>", asc::std::__is_one_of_v<int, char, double, float>);

    // Empty pack — should be false
    expect_false("is_one_of_v<int>", asc::std::__is_one_of_v<int>);

    // cv-qualified types are different
    expect_false("is_one_of_v<int, const int>", asc::std::__is_one_of_v<int, const int>);
    expect_true("is_one_of_v<const int, const int>", asc::std::__is_one_of_v<const int, const int>);

    // References are different types
    expect_false("is_one_of_v<int, int&>", asc::std::__is_one_of_v<int, int&>);
    expect_true("is_one_of_v<int&, int&>", asc::std::__is_one_of_v<int&, int&>);

    // void
    expect_true("is_one_of_v<void, void>", asc::std::__is_one_of_v<void, void>);
    expect_false("is_one_of_v<void, int>", asc::std::__is_one_of_v<void, int>);

    // Multiple matches still true
    expect_true(
        "is_one_of_v<double, int, double, double, char>", asc::std::__is_one_of_v<double, int, double, double, char>);

    return g_failures == 0 ? 0 : 1;
}
