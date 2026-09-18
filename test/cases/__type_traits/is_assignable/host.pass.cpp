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

#include <asc/std/__type_traits/is_assignable.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][is_assignable] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][is_assignable] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

int main()
{
    expect_true("is_assignable<int&, int>::value", asc::std::is_assignable<int&, int>::value);
    expect_true("is_assignable_v<int&, int>", asc::std::is_assignable_v<int&, int>);

    expect_true("is_assignable<int&, double>::value", asc::std::is_assignable<int&, double>::value);

    expect_false("is_assignable<int, int>::value", asc::std::is_assignable<int, int>::value);
    expect_false("is_assignable_v<int, int>", asc::std::is_assignable_v<int, int>);

    expect_false("is_assignable<int&, void>::value", asc::std::is_assignable<int&, void>::value);
    expect_false("is_assignable<void, int>::value", asc::std::is_assignable<void, int>::value);

    expect_false("is_assignable<const int&, int>::value", asc::std::is_assignable<const int&, int>::value);

    expect_false("is_assignable<int*, int*>::value", asc::std::is_assignable<int*, int*>::value);
    expect_true("is_assignable<int*&, int*>::value", asc::std::is_assignable<int*&, int*>::value);

    return g_failures == 0 ? 0 : 1;
}
