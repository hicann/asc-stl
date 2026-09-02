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

#include <asc/std/__algorithm/for_each_n.h>
#include <iostream>
#include <vector>
#include <array>
#include <cstddef>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][for_each_n] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][for_each_n] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void check_part1()
{
    // Basic: apply function to 5 elements, verify side effects
    {
        int data[] = {1, 2, 3, 4, 5};
        int* first = data;
        auto result = asc::std::for_each_n(first, 5, [](int& v) { v *= 10; });
        expect_eq("data[0] after for_each_n", data[0], 10);
        expect_eq("data[1] after for_each_n", data[1], 20);
        expect_eq("data[2] after for_each_n", data[2], 30);
        expect_eq("data[3] after for_each_n", data[3], 40);
        expect_eq("data[4] after for_each_n", data[4], 50);
        expect_true("return iterator == first + 5", result == first + 5);
    }

    // n = 0: no elements processed, return == first
    {
        int data[] = {7, 8, 9};
        int* first = data;
        auto result = asc::std::for_each_n(first, 0, [](int& v) { v = 0; });
        expect_eq("data[0] unchanged (n=0)", data[0], 7);
        expect_eq("data[1] unchanged (n=0)", data[1], 8);
        expect_eq("data[2] unchanged (n=0)", data[2], 9);
        expect_true("return iterator == first (n=0)", result == first);
    }

    // n = 1: single element
    {
        int data[] = {42, 99};
        int* first = data;
        auto result = asc::std::for_each_n(first, 1, [](int& v) { v += 8; });
        expect_eq("data[0] after n=1", data[0], 50);
        expect_eq("data[1] unchanged", data[1], 99);
        expect_true("return iterator == first + 1", result == first + 1);
    }

    // Partial range: process only first 3 of 6 elements
    {
        std::vector<int> data = {0, 0, 0, 0, 0, 0};
        auto first = data.begin();
        auto result = asc::std::for_each_n(first, 3, [](int& v) { v = -1; });
        expect_eq("data[0] partial", data[0], -1);
        expect_eq("data[1] partial", data[1], -1);
        expect_eq("data[2] partial", data[2], -1);
        expect_eq("data[3] unchanged", data[3], 0);
        expect_eq("data[4] unchanged", data[4], 0);
        expect_eq("data[5] unchanged", data[5], 0);
        expect_true("return iterator == begin + 3", result == data.begin() + 3);
    }
}

static void check_part2()
{
    // Float elements
    {
        float data[] = {1.5f, 2.5f, 3.5f};
        float* first = data;
        auto result = asc::std::for_each_n(first, 3, [](float& v) { v = v * v; });
        expect_eq("float data[0]", data[0], 2.25f);
        expect_eq("float data[1]", data[1], 6.25f);
        expect_eq("float data[2]", data[2], 12.25f);
        expect_true("float return == first + 3", result == first + 3);
    }

    // Using std::array with size_t count
    {
        std::array<int, 4> data = {1, 2, 3, 4};
        std::size_t n = 4;
        auto result = asc::std::for_each_n(data.begin(), n, [](int& v) { v = v * v * v; });
        expect_eq("array data[0] cubed", data[0], 1);
        expect_eq("array data[1] cubed", data[1], 8);
        expect_eq("array data[2] cubed", data[2], 27);
        expect_eq("array data[3] cubed", data[3], 64);
        expect_true("array return == begin + 4", result == data.begin() + 4);
    }

    // Function captures external state (sum)
    {
        int data[] = {10, 20, 30, 40};
        int sum = 0;
        auto result = asc::std::for_each_n(data, 4, [&sum](const int& v) { sum += v; });
        expect_eq("captured sum", sum, 100);
        expect_true("return == data + 4", result == data + 4);
    }

    // The upstream suite deliberately accepts floating counts by converting them to long
    // long first.  A count of 2.9 therefore processes exactly two elements.
    {
        int data[] = {1, 2, 3, 4};
        auto result = asc::std::for_each_n(data, 2.9, [](int& v) { v += 10; });
        expect_eq("floating count data[0]", data[0], 11);
        expect_eq("floating count data[1]", data[1], 12);
        expect_eq("floating count data[2] unchanged", data[2], 3);
        expect_true("floating count return == data + 2", result == data + 2);
    }
}

static void check_part3()
{
    // Negative counts are converted but do not enter the loop.
    {
        int data[] = {5, 6};
        auto result = asc::std::for_each_n(data, -3, [](int& v) { v = 0; });
        expect_eq("negative count leaves data[0] unchanged", data[0], 5);
        expect_true("negative count return == data", result == data);
    }
}

int main()
{
    check_part1();
    check_part2();
    check_part3();

    return g_failures == 0 ? 0 : 1;
}
