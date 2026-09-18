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

#include <asc/std/__algorithm/reverse_copy.h>
#include <iostream>
#include <vector>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][reverse_copy] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][reverse_copy] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void check_part1()
{
    // Basic: reverse copy {1,2,3,4,5} -> {5,4,3,2,1}
    {
        int src[] = {1, 2, 3, 4, 5};
        int dst[5];
        auto result = asc::std::reverse_copy(src, src + 5, dst);
        expect_eq("basic dst[0]", dst[0], 5);
        expect_eq("basic dst[1]", dst[1], 4);
        expect_eq("basic dst[2]", dst[2], 3);
        expect_eq("basic dst[3]", dst[3], 2);
        expect_eq("basic dst[4]", dst[4], 1);
        expect_true("basic result == dst + 5", result == dst + 5);
    }

    // Empty range
    {
        int src[] = {1, 2, 3};
        int dst[3] = {0, 0, 0};
        auto result = asc::std::reverse_copy(src, src, dst);
        expect_true("empty result == dst", result == dst);
        expect_eq("empty dst[0] unchanged", dst[0], 0);
    }

    // Single element
    {
        int src[] = {42};
        int dst[1];
        auto result = asc::std::reverse_copy(src, src + 1, dst);
        expect_eq("single dst[0]", dst[0], 42);
        expect_true("single result == dst + 1", result == dst + 1);
    }

    // Even length
    {
        int src[] = {10, 20, 30, 40};
        int dst[4];
        asc::std::reverse_copy(src, src + 4, dst);
        expect_eq("even dst[0]", dst[0], 40);
        expect_eq("even dst[1]", dst[1], 30);
        expect_eq("even dst[2]", dst[2], 20);
        expect_eq("even dst[3]", dst[3], 10);
    }
}

static void check_part2()
{
    // std::vector iterators
    {
        std::vector<float> src = {1.5f, 2.5f, 3.5f};
        std::vector<float> dst(3);
        asc::std::reverse_copy(src.begin(), src.end(), dst.begin());
        expect_eq("vector dst[0]", dst[0], 3.5f);
        expect_eq("vector dst[1]", dst[1], 2.5f);
        expect_eq("vector dst[2]", dst[2], 1.5f);
    }

    // Two elements
    {
        int src[] = {1, 2};
        int dst[2];
        asc::std::reverse_copy(src, src + 2, dst);
        expect_eq("two dst[0]", dst[0], 2);
        expect_eq("two dst[1]", dst[1], 1);
    }

    // Negative values
    {
        int src[] = {-1, -2, -3};
        int dst[3];
        asc::std::reverse_copy(src, src + 3, dst);
        expect_eq("neg dst[0]", dst[0], -3);
        expect_eq("neg dst[1]", dst[1], -2);
        expect_eq("neg dst[2]", dst[2], -1);
    }

    // Float values with return value check
    {
        float src[] = {1.1f, 2.2f, 3.3f, 4.4f};
        float dst[4];
        auto result = asc::std::reverse_copy(src, src + 4, dst);
        expect_eq("float dst[0]", dst[0], 4.4f);
        expect_eq("float dst[1]", dst[1], 3.3f);
        expect_eq("float dst[2]", dst[2], 2.2f);
        expect_eq("float dst[3]", dst[3], 1.1f);
        expect_true("float result == dst + 4", result == dst + 4);
    }
}

int main()
{
    check_part1();
    check_part2();

    return g_failures == 0 ? 0 : 1;
}
