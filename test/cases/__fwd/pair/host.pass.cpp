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

#include <asc/std/__fwd/pair.h>
#include <iostream>
#include <utility>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][pair] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][pair] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

int main()
{
    expect_true(
        "__is_asc_std_pair<asc::std::pair<int, float>>", asc::std::__is_asc_std_pair<asc::std::pair<int, float>>);
    expect_true("__is_asc_std_pair<asc::std::pair<int, int>>", asc::std::__is_asc_std_pair<asc::std::pair<int, int>>);
    expect_true(
        "__is_asc_std_pair<asc::std::pair<double, char>>", asc::std::__is_asc_std_pair<asc::std::pair<double, char>>);

    expect_false("__is_asc_std_pair<int>", asc::std::__is_asc_std_pair<int>);
    expect_false("__is_asc_std_pair<float>", asc::std::__is_asc_std_pair<float>);
    expect_false("__is_asc_std_pair<std::pair<int, int>>", asc::std::__is_asc_std_pair<std::pair<int, int>>);

    return g_failures == 0 ? 0 : 1;
}
