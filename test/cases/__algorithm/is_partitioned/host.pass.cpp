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

#include <asc/std/__algorithm/is_partitioned.h>
#include <iostream>
#include <vector>

static int g_failures = 0;

static void expect_eq(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_partitioned] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

struct is_even {
    bool operator()(int v) const
    {
        return v % 2 == 0;
    }
};

struct is_positive {
    bool operator()(int v) const
    {
        return v > 0;
    }
};

static void check_part1()
{
    // Empty range — vacuously true
    {
        int a[] = {1, 2, 3, 4};
        expect_eq("is_partitioned(empty, is_even)", asc::std::is_partitioned(a, a, is_even{}), true);
    }

    // All satisfy predicate (all even)
    {
        int a[] = {2, 4, 6, 8};
        expect_eq("is_partitioned({2,4,6,8}, is_even)", asc::std::is_partitioned(a, a + 4, is_even{}), true);
    }

    // None satisfy predicate (all odd)
    {
        int a[] = {1, 3, 5, 7};
        expect_eq("is_partitioned({1,3,5,7}, is_even)", asc::std::is_partitioned(a, a + 4, is_even{}), true);
    }

    // Properly partitioned: evens then odds
    {
        int a[] = {2, 4, 1, 3};
        expect_eq("is_partitioned({2,4,1,3}, is_even)", asc::std::is_partitioned(a, a + 4, is_even{}), true);
    }

    // Not partitioned: odd appears before even after transition
    {
        int a[] = {2, 1, 4, 3};
        expect_eq("is_partitioned({2,1,4,3}, is_even)", asc::std::is_partitioned(a, a + 4, is_even{}), false);
    }

    // Alternating even/odd — not partitioned
    {
        int a[] = {1, 2, 3, 4};
        expect_eq("is_partitioned({1,2,3,4}, is_even)", asc::std::is_partitioned(a, a + 4, is_even{}), false);
    }

    // Single element that satisfies predicate
    {
        int a[] = {2};
        expect_eq("is_partitioned({2}, is_even)", asc::std::is_partitioned(a, a + 1, is_even{}), true);
    }

    // Single element that does not satisfy predicate
    {
        int a[] = {1};
        expect_eq("is_partitioned({1}, is_even)", asc::std::is_partitioned(a, a + 1, is_even{}), true);
    }
}

static void check_part2()
{
    // is_positive: properly partitioned (positives then negatives)
    {
        int a[] = {3, 5, -1, -2};
        expect_eq("is_partitioned({3,5,-1,-2}, is_positive)", asc::std::is_partitioned(a, a + 4, is_positive{}), true);
    }

    // is_positive: not partitioned
    {
        int a[] = {3, -1, 5, -2};
        expect_eq("is_partitioned({3,-1,5,-2}, is_positive)", asc::std::is_partitioned(a, a + 4, is_positive{}), false);
    }

    // Lambda predicate: >= 10
    {
        int a[] = {10, 20, 1, 3};
        auto pred = [](int v) { return v >= 10; };
        expect_eq("is_partitioned({10,20,1,3}, >=10)", asc::std::is_partitioned(a, a + 4, pred), true);
    }

    // Lambda predicate: not partitioned
    {
        int a[] = {10, 1, 20, 3};
        auto pred = [](int v) { return v >= 10; };
        expect_eq("is_partitioned({10,1,20,3}, >=10)", asc::std::is_partitioned(a, a + 4, pred), false);
    }

    // Using std::vector iterators
    {
        std::vector<int> v = {2, 4, 6, 1};
        expect_eq(
            "is_partitioned(vector{2,4,6,1}, is_even)", asc::std::is_partitioned(v.begin(), v.end(), is_even{}), true);
    }

    // Edge: first element does not satisfy, rest do not either
    {
        int a[] = {1, 3, 5};
        expect_eq("is_partitioned({1,3,5}, is_even)", asc::std::is_partitioned(a, a + 3, is_even{}), true);
    }

    // Edge: transition then regression (odd, even, odd)
    {
        int a[] = {1, 2, 3};
        expect_eq("is_partitioned({1,2,3}, is_even)", asc::std::is_partitioned(a, a + 3, is_even{}), false);
    }
}

static void check_part3()
{
    // Two elements: even then odd — partitioned
    {
        int a[] = {2, 1};
        expect_eq("is_partitioned({2,1}, is_even)", asc::std::is_partitioned(a, a + 2, is_even{}), true);
    }

    // Two elements: odd then even — not partitioned
    {
        int a[] = {1, 2};
        expect_eq("is_partitioned({1,2}, is_even)", asc::std::is_partitioned(a, a + 2, is_even{}), false);
    }
}

int main()
{
    check_part1();
    check_part2();
    check_part3();

    return g_failures == 0 ? 0 : 1;
}
