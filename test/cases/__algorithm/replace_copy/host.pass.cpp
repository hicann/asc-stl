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

#include <asc/std/__algorithm/replace_copy.h>
#include <iostream>
#include <vector>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][replace_copy] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][replace_copy] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void check_part1()
{
    // Test 1: Basic replace_copy with int vector
    {
        std::vector<int> src = {1, 2, 3, 2, 5, 2, 7};
        std::vector<int> dst(7);
        auto it = asc::std::replace_copy(src.begin(), src.end(), dst.begin(), 2, 99);
        expect_true("basic: returned iterator == dst.end()", it == dst.end());
        expect_eq("basic: dst[0]", dst[0], 1);
        expect_eq("basic: dst[1]", dst[1], 99);
        expect_eq("basic: dst[2]", dst[2], 3);
        expect_eq("basic: dst[3]", dst[3], 99);
        expect_eq("basic: dst[4]", dst[4], 5);
        expect_eq("basic: dst[5]", dst[5], 99);
        expect_eq("basic: dst[6]", dst[6], 7);
    }

    // Test 2: No matches — all elements copied as-is
    {
        std::vector<int> src = {1, 3, 5, 7};
        std::vector<int> dst(4);
        auto it = asc::std::replace_copy(src.begin(), src.end(), dst.begin(), 2, 99);
        expect_true("no-match: returned iterator == dst.end()", it == dst.end());
        expect_eq("no-match: dst[0]", dst[0], 1);
        expect_eq("no-match: dst[1]", dst[1], 3);
        expect_eq("no-match: dst[2]", dst[2], 5);
        expect_eq("no-match: dst[3]", dst[3], 7);
    }

    // Test 3: All elements match old_value — all replaced
    {
        std::vector<int> src = {2, 2, 2, 2};
        std::vector<int> dst(4);
        auto it = asc::std::replace_copy(src.begin(), src.end(), dst.begin(), 2, 0);
        expect_true("all-match: returned iterator == dst.end()", it == dst.end());
        expect_eq("all-match: dst[0]", dst[0], 0);
        expect_eq("all-match: dst[1]", dst[1], 0);
        expect_eq("all-match: dst[2]", dst[2], 0);
        expect_eq("all-match: dst[3]", dst[3], 0);
    }
}

static void check_part2()
{
    // Test 4: Empty range
    {
        std::vector<int> src;
        std::vector<int> dst;
        auto it = asc::std::replace_copy(src.begin(), src.end(), dst.begin(), 2, 99);
        expect_true("empty: returned iterator == dst.begin()", it == dst.begin());
    }

    // Test 5: Single element — matches
    {
        std::vector<int> src = {2};
        std::vector<int> dst(1);
        auto it = asc::std::replace_copy(src.begin(), src.end(), dst.begin(), 2, 42);
        expect_eq("single-match: dst[0]", dst[0], 42);
        expect_true("single-match: returned iterator == dst.end()", it == dst.end());
    }

    // Test 6: Single element — no match
    {
        std::vector<int> src = {5};
        std::vector<int> dst(1);
        auto it = asc::std::replace_copy(src.begin(), src.end(), dst.begin(), 2, 42);
        expect_eq("single-no-match: dst[0]", dst[0], 5);
        expect_true("single-no-match: returned iterator == dst.end()", it == dst.end());
    }

    // Test 7: With float
    {
        std::vector<float> src = {1.5f, 2.5f, 3.5f, 2.5f};
        std::vector<float> dst(4);
        auto it = asc::std::replace_copy(src.begin(), src.end(), dst.begin(), 2.5f, 9.0f);
        expect_eq("float: dst[0]", dst[0], 1.5f);
        expect_eq("float: dst[1]", dst[1], 9.0f);
        expect_eq("float: dst[2]", dst[2], 3.5f);
        expect_eq("float: dst[3]", dst[3], 9.0f);
        expect_true("float: returned iterator == dst.end()", it == dst.end());
    }
}

static void check_part3()
{
    // Test 8: Using raw pointers (array)
    {
        int src[] = {10, 20, 30, 20, 50};
        int dst[5];
        auto it = asc::std::replace_copy(src, src + 5, dst, 20, 200);
        expect_eq("array: dst[0]", dst[0], 10);
        expect_eq("array: dst[1]", dst[1], 200);
        expect_eq("array: dst[2]", dst[2], 30);
        expect_eq("array: dst[3]", dst[3], 200);
        expect_eq("array: dst[4]", dst[4], 50);
        expect_true("array: returned iterator == dst+5", it == dst + 5);
    }

    // Test 9: old_value == new_value (no-op replace)
    {
        std::vector<int> src = {1, 2, 3, 2, 5};
        std::vector<int> dst(5);
        asc::std::replace_copy(src.begin(), src.end(), dst.begin(), 2, 2);
        expect_eq("same-old-new: dst[0]", dst[0], 1);
        expect_eq("same-old-new: dst[1]", dst[1], 2);
        expect_eq("same-old-new: dst[2]", dst[2], 3);
        expect_eq("same-old-new: dst[3]", dst[3], 2);
        expect_eq("same-old-new: dst[4]", dst[4], 5);
    }

    // Test 10: Partial range (sub-range of a larger vector)
    {
        std::vector<int> src = {1, 2, 3, 4, 5, 6};
        std::vector<int> dst(3);
        auto it = asc::std::replace_copy(src.begin() + 1, src.begin() + 4, dst.begin(), 3, 99);
        expect_eq("partial: dst[0]", dst[0], 2);
        expect_eq("partial: dst[1]", dst[1], 99);
        expect_eq("partial: dst[2]", dst[2], 4);
        expect_true("partial: returned iterator == dst.end()", it == dst.end());
    }
}

int main()
{
    check_part1();
    check_part2();
    check_part3();

    return g_failures == 0 ? 0 : 1;
}
