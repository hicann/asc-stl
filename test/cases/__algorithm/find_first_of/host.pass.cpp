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

#include <asc/std/__algorithm/find_first_of.h>
#include <iostream>
#include <vector>

static int g_failures = 0;

static void expect_eq(const char* expr, long long got, long long expected)
{
    bool ok = (got == expected);
    std::cout << "[host][find_first_of] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void check_part1()
{
    // Basic: find first of {2, 4, 6} in {1, 2, 3, 4, 5}
    {
        int a[] = {1, 2, 3, 4, 5};
        int b[] = {2, 4, 6};
        auto it = asc::std::find_first_of(a, a + 5, b, b + 3);
        expect_eq("find_first_of basic - index", (long long)(it - a), 1);
        expect_eq("find_first_of basic - value", (long long)*it, 2);
    }

    // No match found
    {
        int a[] = {1, 2, 3};
        int b[] = {7, 8, 9};
        auto it = asc::std::find_first_of(a, a + 3, b, b + 3);
        expect_eq("find_first_of no match - is end", (long long)(it == a + 3), 1);
    }

    // Empty first range
    {
        int a[] = {1, 2, 3};
        int b[] = {1, 2};
        auto it = asc::std::find_first_of(a, a, b, b + 2);
        expect_eq("find_first_of empty range1 - is end", (long long)(it == a), 1);
    }

    // Empty second range
    {
        int a[] = {1, 2, 3};
        int b[] = {1, 2};
        auto it = asc::std::find_first_of(a, a + 3, b, b);
        expect_eq("find_first_of empty range2 - is end", (long long)(it == a + 3), 1);
    }

    // First element matches
    {
        int a[] = {5, 4, 3};
        int b[] = {5, 6, 7};
        auto it = asc::std::find_first_of(a, a + 3, b, b + 3);
        expect_eq("find_first_of first match - index", (long long)(it - a), 0);
    }
}

static void check_part2()
{
    // Last element matches
    {
        int a[] = {1, 2, 3};
        int b[] = {3, 4, 5};
        auto it = asc::std::find_first_of(a, a + 3, b, b + 3);
        expect_eq("find_first_of last match - index", (long long)(it - a), 2);
    }

    // Duplicate in range1 - returns first occurrence
    {
        int a[] = {1, 3, 3, 5};
        int b[] = {3};
        auto it = asc::std::find_first_of(a, a + 4, b, b + 1);
        expect_eq("find_first_of duplicate - index", (long long)(it - a), 1);
    }

    // Custom predicate: find first element less than some element in b
    {
        int a[] = {10, 8, 3, 12};
        int b[] = {5, 7};
        auto it = asc::std::find_first_of(a, a + 4, b, b + 2, [](int x, int y) { return x < y; });
        // a[0]=10: 10<5? no, 10<7? no; a[1]=8: 8<5? no, 8<7? no; a[2]=3: 3<5? yes
        expect_eq("find_first_of pred less - index", (long long)(it - a), 2);
    }

    // Custom predicate: find first element greater than some element in b
    {
        int a[] = {1, 5, 15, 20};
        int b[] = {10, 20};
        auto it = asc::std::find_first_of(a, a + 4, b, b + 2, [](int x, int y) { return x > y; });
        // a[0]=1: 1>10? no, 1>20? no; a[1]=5: 5>10? no, 5>20? no; a[2]=15: 15>10? yes
        expect_eq("find_first_of pred greater - index", (long long)(it - a), 2);
    }

    // With std::vector iterators
    {
        std::vector<int> a = {10, 20, 30, 40};
        std::vector<int> b = {30, 50};
        auto it = asc::std::find_first_of(a.begin(), a.end(), b.begin(), b.end());
        expect_eq("find_first_of vectors - index", (long long)(it - a.begin()), 2);
    }
}

static void check_part3()
{
    // Single element ranges
    {
        int a[] = {42};
        int b[] = {42};
        auto it = asc::std::find_first_of(a, a + 1, b, b + 1);
        expect_eq("find_first_of single match - index", (long long)(it - a), 0);
    }

    {
        int a[] = {42};
        int b[] = {99};
        auto it = asc::std::find_first_of(a, a + 1, b, b + 1);
        expect_eq("find_first_of single no match - is end", (long long)(it == a + 1), 1);
    }
}

int main()
{
    check_part1();
    check_part2();
    check_part3();

    return g_failures == 0 ? 0 : 1;
}
