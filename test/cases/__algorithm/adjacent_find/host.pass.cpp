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

#include <asc/std/__algorithm/adjacent_find.h>
#include <iostream>
#include <vector>

static int g_failures = 0;

static void expect_eq(const char* expr, long got, long expected)
{
    bool ok = (got == expected);
    std::cout << "[host][adjacent_find] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void check_part1()
{
    // Test 1: Basic case from the upstream suite — first adjacent equal pair at index 2
    {
        int ia[] = {0, 1, 2, 2, 0, 1, 2, 3};
        const int sa = sizeof(ia) / sizeof(ia[0]);
        auto result = asc::std::adjacent_find(ia, ia + sa);
        expect_eq("adjacent_find({0,1,2,2,0,1,2,3}) index", static_cast<long>(result - ia), 2);
    }

    // Test 2: Empty range — returns last (== first)
    {
        int ia[] = {0, 1, 2, 2, 0, 1, 2, 3};
        auto result = asc::std::adjacent_find(ia, ia);
        expect_eq("adjacent_find(empty range) index", static_cast<long>(result - ia), 0);
    }

    // Test 3: No adjacent equal elements — returns last
    {
        int ia[] = {2, 0, 1, 2, 3};
        const int sa = sizeof(ia) / sizeof(ia[0]);
        auto result = asc::std::adjacent_find(ia, ia + sa);
        expect_eq("adjacent_find({2,0,1,2,3}) index", static_cast<long>(result - ia), sa);
    }

    // Test 4: Match at beginning
    {
        int ia[] = {5, 5, 1, 2, 3};
        const int sa = sizeof(ia) / sizeof(ia[0]);
        auto result = asc::std::adjacent_find(ia, ia + sa);
        expect_eq("adjacent_find({5,5,1,2,3}) index", static_cast<long>(result - ia), 0);
    }

    // Test 5: With custom predicate (greater-than: find first decreasing pair)
    {
        int ia[] = {1, 3, 2, 5, 4};
        const int sa = sizeof(ia) / sizeof(ia[0]);
        auto result = asc::std::adjacent_find(ia, ia + sa, [](int a, int b) { return a > b; });
        expect_eq("adjacent_find({1,3,2,5,4}, pred>) index", static_cast<long>(result - ia), 1);
    }

    // Test 6: All same elements — returns first
    {
        int ia[] = {7, 7, 7, 7};
        const int sa = sizeof(ia) / sizeof(ia[0]);
        auto result = asc::std::adjacent_find(ia, ia + sa);
        expect_eq("adjacent_find({7,7,7,7}) index", static_cast<long>(result - ia), 0);
    }
}

static void check_part2()
{
    // Test 7: Single element — returns last
    {
        int ia[] = {42};
        auto result = asc::std::adjacent_find(ia, ia + 1);
        expect_eq("adjacent_find({42}) index", static_cast<long>(result - ia), 1);
    }

    // Test 8: Using vector iterators
    {
        std::vector<int> v = {1, 2, 3, 3, 4, 5};
        auto result = asc::std::adjacent_find(v.begin(), v.end());
        expect_eq("adjacent_find(vector{1,2,3,3,4,5}) index", static_cast<long>(result - v.begin()), 2);
    }

    // Test 9: Match at end
    {
        int ia[] = {1, 2, 3, 4, 5, 5};
        const int sa = sizeof(ia) / sizeof(ia[0]);
        auto result = asc::std::adjacent_find(ia, ia + sa);
        expect_eq("adjacent_find({1,2,3,4,5,5}) index", static_cast<long>(result - ia), 4);
    }

    // Test 10: Custom predicate — no match returns last
    {
        int ia[] = {1, 2, 3, 4, 5};
        const int sa = sizeof(ia) / sizeof(ia[0]);
        auto result = asc::std::adjacent_find(ia, ia + sa, [](int a, int b) { return a > b; });
        expect_eq("adjacent_find({1,2,3,4,5}, pred> no match) index", static_cast<long>(result - ia), sa);
    }
}

int main()
{
    check_part1();
    check_part2();

    return g_failures == 0 ? 0 : 1;
}
