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

#include <asc/std/__algorithm/copy_if.h>
#include <iostream>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][copy_if] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

static void check_part1()
{
    // Test 1: Copy elements divisible by 3 from {0,1,...,9}
    {
        int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        int ib[10] = {0};
        auto pred = [](int i) { return i % 3 == 0; };
        int* r = asc::std::copy_if(ia, ia + 10, ib, pred);
        expect_eq("copy_if mod3 count", static_cast<int>(r - ib), 4);
        expect_eq("copy_if mod3 ib[0]", ib[0], 0);
        expect_eq("copy_if mod3 ib[1]", ib[1], 3);
        expect_eq("copy_if mod3 ib[2]", ib[2], 6);
        expect_eq("copy_if mod3 ib[3]", ib[3], 9);
        expect_eq("copy_if mod3 ib[4] (untouched)", ib[4], 0);
    }

    // Test 2: Copy elements equal to 6 from {2,4,6,8,6}
    {
        int ia[] = {2, 4, 6, 8, 6};
        int ic[7] = {0, 0, 0, 0, 0, 0, 0};
        auto pred = [](int i) { return i == 6; };
        int* p = asc::std::copy_if(ia, ia + 5, ic, pred);
        expect_eq("copy_if eq6 count", static_cast<int>(p - ic), 2);
        expect_eq("copy_if eq6 ic[0]", ic[0], 6);
        expect_eq("copy_if eq6 ic[1]", ic[1], 6);
        expect_eq("copy_if eq6 ic[2] (untouched)", ic[2], 0);
    }

    // Test 3: Empty range (first == last)
    {
        int ia[] = {1, 2, 3};
        int ib[3] = {0};
        auto pred = [](int i) { return i > 0; };
        int* r = asc::std::copy_if(ia, ia, ib, pred);
        expect_eq("copy_if empty range count", static_cast<int>(r - ib), 0);
    }

    // Test 4: No elements match predicate
    {
        int ia[] = {1, 2, 4, 5, 7};
        int ib[5] = {0};
        auto pred = [](int i) { return i % 3 == 0; };
        int* r = asc::std::copy_if(ia, ia + 5, ib, pred);
        expect_eq("copy_if no match count", static_cast<int>(r - ib), 0);
    }
}

static void check_part2()
{
    // Test 5: All elements match predicate
    {
        int ia[] = {3, 6, 9, 12};
        int ib[4] = {0};
        auto pred = [](int i) { return i % 3 == 0; };
        int* r = asc::std::copy_if(ia, ia + 4, ib, pred);
        expect_eq("copy_if all match count", static_cast<int>(r - ib), 4);
        expect_eq("copy_if all match ib[0]", ib[0], 3);
        expect_eq("copy_if all match ib[1]", ib[1], 6);
        expect_eq("copy_if all match ib[2]", ib[2], 9);
        expect_eq("copy_if all match ib[3]", ib[3], 12);
    }

    // Test 6: Single element matching
    {
        int ia[] = {6};
        int ib[1] = {0};
        auto pred = [](int i) { return i == 6; };
        int* r = asc::std::copy_if(ia, ia + 1, ib, pred);
        expect_eq("copy_if single match count", static_cast<int>(r - ib), 1);
        expect_eq("copy_if single match ib[0]", ib[0], 6);
    }

    // Test 7: Single element not matching
    {
        int ia[] = {5};
        int ib[1] = {0};
        auto pred = [](int i) { return i == 6; };
        int* r = asc::std::copy_if(ia, ia + 1, ib, pred);
        expect_eq("copy_if single no match count", static_cast<int>(r - ib), 0);
        expect_eq("copy_if single no match ib[0]", ib[0], 0);
    }
}

int main()
{
    check_part1();
    check_part2();

    return g_failures == 0 ? 0 : 1;
}
