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

#include <asc/std/__fwd/string.h>
#include <iostream>
#include <string>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][string] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][string] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

int main()
{
    // __is_std_basic_string_v should be true for std::basic_string specializations
    expect_true("asc::std::__is_std_basic_string_v<std::string>", asc::std::__is_std_basic_string_v<std::string>);
    expect_true("asc::std::__is_std_basic_string_v<std::wstring>", asc::std::__is_std_basic_string_v<std::wstring>);

    // __is_std_basic_string_v should be false for non-string types
    expect_false("asc::std::__is_std_basic_string_v<int>", asc::std::__is_std_basic_string_v<int>);
    expect_false("asc::std::__is_std_basic_string_v<double>", asc::std::__is_std_basic_string_v<double>);
    expect_false("asc::std::__is_std_basic_string_v<const char*>", asc::std::__is_std_basic_string_v<const char*>);

    // Verify std::basic_string forward declaration is compatible with real type
    std::string s = "hello";
    expect_true("std::string s == \"hello\"", s == "hello");
    expect_true("std::string s.size() == 5", s.size() == 5);

    return g_failures == 0 ? 0 : 1;
}
