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

#include <asc/std/__type_traits/is_fundamental.h>
#include <iostream>

static int g_failures = 0;

static void expect_eq(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_fundamental] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

struct CustomType {};

int main()
{
    expect_eq("is_fundamental_v<void>", asc::std::is_fundamental_v<void>, true);
    expect_eq("is_fundamental_v<asc::std::nullptr_t>", asc::std::is_fundamental_v<asc::std::nullptr_t>, true);
    expect_eq("is_fundamental_v<int>", asc::std::is_fundamental_v<int>, true);
    expect_eq("is_fundamental_v<float>", asc::std::is_fundamental_v<float>, true);
    expect_eq("is_fundamental_v<bool>", asc::std::is_fundamental_v<bool>, true);
    expect_eq("is_fundamental_v<char>", asc::std::is_fundamental_v<char>, true);
    expect_eq("is_fundamental_v<const int>", asc::std::is_fundamental_v<const int>, true);
    expect_eq("is_fundamental_v<volatile double>", asc::std::is_fundamental_v<volatile double>, true);

    expect_eq("is_fundamental_v<int*>", asc::std::is_fundamental_v<int*>, false);
    expect_eq("is_fundamental_v<void*>", asc::std::is_fundamental_v<void*>, false);
    expect_eq("is_fundamental_v<CustomType>", asc::std::is_fundamental_v<CustomType>, false);
    expect_eq("is_fundamental_v<int&>", asc::std::is_fundamental_v<int&>, false);

    expect_eq("is_fundamental<void>::value", asc::std::is_fundamental<void>::value, true);
    expect_eq("is_fundamental<int>::value", asc::std::is_fundamental<int>::value, true);
    expect_eq("is_fundamental<CustomType>::value", asc::std::is_fundamental<CustomType>::value, false);

    return g_failures == 0 ? 0 : 1;
}
