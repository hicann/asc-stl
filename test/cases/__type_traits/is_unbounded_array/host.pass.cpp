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

#include <asc/std/__type_traits/is_unbounded_array.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool got)
{
    std::cout << "[host][is_unbounded_array] " << expr << " = " << (got ? "true" : "false") << " (expected true) "
              << (got ? "OK" : "FAIL") << std::endl;
    if (!got)
        ++g_failures;
}

static void expect_false(const char* expr, bool got)
{
    std::cout << "[host][is_unbounded_array] " << expr << " = " << (got ? "true" : "false") << " (expected false) "
              << (got ? "FAIL" : "OK") << std::endl;
    if (got)
        ++g_failures;
}

int main()
{
    // _v variable template — unbounded arrays
    expect_true("is_unbounded_array_v<int[]>", asc::std::is_unbounded_array_v<int[]>);
    expect_true("is_unbounded_array_v<char[]>", asc::std::is_unbounded_array_v<char[]>);
    expect_true("is_unbounded_array_v<double[]>", asc::std::is_unbounded_array_v<double[]>);
    expect_true("is_unbounded_array_v<int*[]>", asc::std::is_unbounded_array_v<int*[]>);

    // _v variable template — non-unbounded-array types
    expect_false("is_unbounded_array_v<int>", asc::std::is_unbounded_array_v<int>);
    expect_false("is_unbounded_array_v<int[5]>", asc::std::is_unbounded_array_v<int[5]>);
    expect_false("is_unbounded_array_v<int*>", asc::std::is_unbounded_array_v<int*>);
    expect_false("is_unbounded_array_v<double[3]>", asc::std::is_unbounded_array_v<double[3]>);
    expect_false("is_unbounded_array_v<float>", asc::std::is_unbounded_array_v<float>);

    // struct ::value form
    expect_true("is_unbounded_array<int[]>::value", asc::std::is_unbounded_array<int[]>::value);
    expect_false("is_unbounded_array<int>::value", asc::std::is_unbounded_array<int>::value);
    expect_false("is_unbounded_array<int[10]>::value", asc::std::is_unbounded_array<int[10]>::value);
    expect_false("is_unbounded_array<char[1]>::value", asc::std::is_unbounded_array<char[1]>::value);

    // struct inherits bool_constant — convertible to bool and callable
    {
        bool b = asc::std::is_unbounded_array<int[]>{};
        expect_true("is_unbounded_array<int[]>{} converts to bool", b);
    }
    {
        bool b = asc::std::is_unbounded_array<int>{};
        expect_false("is_unbounded_array<int>{} converts to bool", b);
    }
    {
        auto ic = asc::std::is_unbounded_array<double[]>{};
        expect_true("is_unbounded_array<double[]>{}()", ic());
    }

    return g_failures == 0 ? 0 : 1;
}
