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

#include <asc/std/__algorithm/generate_n.h>
#include <iostream>
#include <vector>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][generate_n] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][generate_n] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void check_part1()
{
    // Test 1: Basic generate_n with counter generator
    {
        int arr[5] = {0, 0, 0, 0, 0};
        int counter = 0;
        auto gen = [&counter]() { return ++counter; };
        auto result = asc::std::generate_n(arr, 5, gen);
        expect_eq("arr[0]", arr[0], 1);
        expect_eq("arr[1]", arr[1], 2);
        expect_eq("arr[2]", arr[2], 3);
        expect_eq("arr[3]", arr[3], 4);
        expect_eq("arr[4]", arr[4], 5);
        expect_true("result == arr+5", result == arr + 5);
    }

    // Test 2: n=0 (empty range)
    {
        int arr[3] = {42, 42, 42};
        int counter = 0;
        auto gen = [&counter]() { return ++counter; };
        auto result = asc::std::generate_n(arr, 0, gen);
        expect_eq("counter after n=0", counter, 0);
        expect_eq("arr[0] after n=0", arr[0], 42);
        expect_true("result == arr for n=0", result == arr);
    }

    // Test 3: Constant generator
    {
        float arr[4] = {0.0f, 0.0f, 0.0f, 0.0f};
        auto gen = []() { return 3.14f; };
        auto result = asc::std::generate_n(arr, 4, gen);
        expect_eq("const arr[0]", arr[0], 3.14f);
        expect_eq("const arr[1]", arr[1], 3.14f);
        expect_eq("const arr[2]", arr[2], 3.14f);
        expect_eq("const arr[3]", arr[3], 3.14f);
        expect_true("const result == arr+4", result == arr + 4);
    }
}

static void check_part2()
{
    // Test 4: Using std::vector iterator
    {
        std::vector<int> v(5, 0);
        int val = 10;
        auto gen = [&val]() {
            int t = val;
            val += 10;
            return t;
        };
        auto result = asc::std::generate_n(v.begin(), 5, gen);
        expect_eq("vector v[0]", v[0], 10);
        expect_eq("vector v[1]", v[1], 20);
        expect_eq("vector v[2]", v[2], 30);
        expect_eq("vector v[3]", v[3], 40);
        expect_eq("vector v[4]", v[4], 50);
        expect_true("vector result == v.end()", result == v.end());
    }

    // Test 5: Different size type (long)
    {
        int arr[3] = {0, 0, 0};
        int counter = 0;
        auto gen = [&counter]() { return counter++; };
        long n = 3;
        asc::std::generate_n(arr, n, gen);
        expect_eq("long-size arr[0]", arr[0], 0);
        expect_eq("long-size arr[1]", arr[1], 1);
        expect_eq("long-size arr[2]", arr[2], 2);
    }
}

int main()
{
    check_part1();
    check_part2();

    return g_failures == 0 ? 0 : 1;
}
