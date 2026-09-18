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

#include <asc/std/__algorithm/replace_if.h>
#include <iostream>
#include <vector>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][replace_if] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_vec_eq(const char* expr, const std::vector<int>& got, const std::vector<int>& expected)
{
    bool ok = (got == expected);
    std::cout << "[host][replace_if] " << expr << (ok ? " OK" : " FAIL") << std::endl;
    if (!ok) {
        std::cout << "  actual  :";
        for (const int v : got)
            std::cout << ' ' << v;
        std::cout << '\n' << "  expected:";
        for (const int v : expected)
            std::cout << ' ' << v;
        std::cout << std::endl;
        ++g_failures;
    }
}

static void check_part1()
{
    // Basic test: replace even numbers with 0
    {
        std::vector<int> v = {1, 2, 3, 4, 5, 6};
        asc::std::replace_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; }, 0);
        expect_vec_eq("replace even with 0", v, std::vector<int>({1, 0, 3, 0, 5, 0}));
    }

    // All match
    {
        std::vector<int> v = {10, 20, 30};
        asc::std::replace_if(v.begin(), v.end(), [](int x) { return x > 0; }, -1);
        expect_vec_eq("all match", v, std::vector<int>({-1, -1, -1}));
    }

    // None match
    {
        std::vector<int> v = {1, 2, 3};
        asc::std::replace_if(v.begin(), v.end(), [](int x) { return x > 100; }, 0);
        expect_vec_eq("none match", v, std::vector<int>({1, 2, 3}));
    }

    // Empty range
    {
        std::vector<int> v;
        asc::std::replace_if(
            v.begin(), v.end(),
            [](int x) {
                static_cast<void>(x);
                return true;
            },
            42);
        expect_vec_eq("empty range", v, std::vector<int>({}));
    }

    // Single element matching
    {
        std::vector<int> v = {5};
        asc::std::replace_if(v.begin(), v.end(), [](int x) { return x == 5; }, 99);
        expect_vec_eq("single match", v, std::vector<int>({99}));
    }
}

static void check_part2()
{
    // Float test: replace negatives with 0
    {
        std::vector<float> v = {1.0f, -2.0f, 3.0f, -4.0f};
        asc::std::replace_if(v.begin(), v.end(), [](float x) { return x < 0.0f; }, 0.0f);
        expect_eq("float[0]", v[0], 1.0f);
        expect_eq("float[1]", v[1], 0.0f);
        expect_eq("float[2]", v[2], 3.0f);
        expect_eq("float[3]", v[3], 0.0f);
    }

    // Replace values >= 5 with 0
    {
        std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
        asc::std::replace_if(v.begin(), v.end(), [](int x) { return x >= 5; }, 0);
        expect_vec_eq("replace >=5 with 0", v, std::vector<int>({3, 1, 4, 1, 0, 0, 2, 0}));
    }

    // Replace with different type value (double new_value into float range)
    {
        std::vector<float> v = {1.5f, 2.5f, 3.5f};
        asc::std::replace_if(v.begin(), v.end(), [](float x) { return x > 2.0f; }, 0.0f);
        expect_eq("mixed[0]", v[0], 1.5f);
        expect_eq("mixed[1]", v[1], 0.0f);
        expect_eq("mixed[2]", v[2], 0.0f);
    }
}

int main()
{
    check_part1();
    check_part2();

    return g_failures == 0 ? 0 : 1;
}
