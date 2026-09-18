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

#include <asc/std/__iterator/empty.h>
#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>

static int g_failures = 0;

static void expect_eq(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][empty] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // Container overload - std::vector
    {
        std::vector<int> v_empty;
        std::vector<int> v_nonempty = {1, 2, 3};
        expect_eq("empty(vector<int>())", asc::std::empty(v_empty), true);
        expect_eq("empty(vector<int>{1,2,3})", asc::std::empty(v_nonempty), false);
    }

    // Container overload - std::string
    {
        std::string s_empty;
        std::string s_nonempty = "hello";
        expect_eq("empty(string())", asc::std::empty(s_empty), true);
        expect_eq("empty(string(\"hello\"))", asc::std::empty(s_nonempty), false);
    }

    // Array overload - always returns false for any sized array
    {
        int arr5[5] = {1, 2, 3, 4, 5};
        expect_eq("empty(int[5])", asc::std::empty(arr5), false);
    }
    {
        int arr1[1] = {42};
        expect_eq("empty(int[1])", asc::std::empty(arr1), false);
    }

    // initializer_list overload
    {
        asc::std::initializer_list<int> il_empty;
        asc::std::initializer_list<int> il_nonempty = {1, 2, 3};
        expect_eq("empty(initializer_list<int>())", asc::std::empty(il_empty), true);
        expect_eq("empty(initializer_list<int>{1,2,3})", asc::std::empty(il_nonempty), false);
    }

    return g_failures == 0 ? 0 : 1;
}
