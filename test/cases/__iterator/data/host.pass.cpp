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

#include <asc/std/__iterator/data.h>
#include <iostream>
#include <vector>
#include <initializer_list>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][data] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][data] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    // Test 1: container with .data() — non-const overload
    {
        std::vector<int> v = {10, 20, 30};
        int* p = asc::std::data(v);
        expect_true("data(vector) == &v[0]", p == &v[0]);
        expect_eq("data(vector)[0]", p[0], 10);
        expect_eq("data(vector)[2]", p[2], 30);
    }

    // Test 2: const container — const overload
    {
        const std::vector<int> v = {1, 2, 3};
        const int* p = asc::std::data(v);
        expect_true("data(const vector) == &v[0]", p == &v[0]);
        expect_eq("data(const vector)[1]", p[1], 2);
    }

    // Test 3: raw array overload
    {
        int arr[] = {5, 10, 15, 20};
        int* p = asc::std::data(arr);
        expect_true("data(array) == arr", p == arr);
        expect_eq("data(array)[0]", p[0], 5);
        expect_eq("data(array)[3]", p[3], 20);
    }

    // Test 4: single-element array
    {
        int arr[] = {42};
        int* p = asc::std::data(arr);
        expect_eq("data(single array)[0]", p[0], 42);
    }

    // Test 5: initializer_list overload
    {
        std::initializer_list<int> il = {7, 8, 9};
        const int* p = asc::std::data(il);
        expect_true("data(init_list) == il.begin()", p == il.begin());
        expect_eq("data(init_list)[0]", p[0], 7);
        expect_eq("data(init_list)[2]", p[2], 9);
    }

    // Test 6: empty vector
    {
        std::vector<int> v;
        int* p = asc::std::data(v);
        // For empty vector, data() may return nullptr or a valid dangling pointer;
        // just verify it is callable and does not crash.
        (void)p;
        expect_true("data(empty vector) callable", true);
    }

    // Test 7: float array
    {
        float arr[] = {1.5f, 2.5f, 3.5f};
        float* p = asc::std::data(arr);
        expect_eq("data(float array)[0]", p[0], 1.5f);
        expect_eq("data(float array)[2]", p[2], 3.5f);
    }

    return g_failures == 0 ? 0 : 1;
}
