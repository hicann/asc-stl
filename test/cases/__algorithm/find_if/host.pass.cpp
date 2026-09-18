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

#include <asc/std/__algorithm/find_if.h>
#include <iostream>
#include <vector>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][find_if] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][find_if] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

struct Comparable {
    int val_;
    constexpr Comparable(int val) noexcept : val_(val)  // NOLINT(runtime/explicit)
    {}
    constexpr bool operator()(int other) const noexcept
    {
        return val_ == other;
    }
};

struct is_even {
    constexpr bool operator()(int x) const noexcept
    {
        return x % 2 == 0;
    }
};

static void check_part1()
{
    // Upstream test: arr = {2, 4, 6, 8}
    {
        int arr[] = {2, 4, 6, 8};

        // first element matches
        auto it = asc::std::find_if(arr, arr + 4, Comparable(2));
        expect_eq("*find_if(arr, arr+4, Comparable(2))", *it, 2);
        expect_true("find_if first match at arr", it == arr);

        // empty range returns last (== first)
        auto it2 = asc::std::find_if(arr, arr, Comparable(2));
        expect_true("find_if empty range returns first==last", it2 == arr);

        // some element matches (middle)
        auto it3 = asc::std::find_if(arr, arr + 4, Comparable(6));
        expect_eq("*find_if(arr, arr+4, Comparable(6))", *it3, 6);
        expect_true("find_if middle match at arr+2", it3 == arr + 2);

        // last element matches
        auto it4 = asc::std::find_if(arr, arr + 4, Comparable(8));
        expect_eq("*find_if(arr, arr+4, Comparable(8))", *it4, 8);
        expect_true("find_if last match at arr+3", it4 == arr + 3);

        // no element matches, returns last
        auto it5 = asc::std::find_if(arr, arr + 4, Comparable(10));
        expect_true("find_if no match returns last", it5 == arr + 4);
    }

    // multiple matches, return first match
    {
        int arr[] = {2, 4, 4, 8};
        auto it = asc::std::find_if(arr, arr + 4, Comparable(4));
        expect_eq("*find_if multiple matches", *it, 4);
        expect_true("find_if multiple matches returns first", it == arr + 1);
    }

    // is_even functor predicate
    {
        int a[] = {1, 3, 2, 5};
        auto it = asc::std::find_if(a, a + 4, is_even{});
        expect_eq("*find_if(a, a+4, is_even)", *it, 2);
        expect_true("find_if is_even at a+2", it == a + 2);
    }

    // all odd, returns last
    {
        int a[] = {1, 3, 5, 7};
        auto it = asc::std::find_if(a, a + 4, is_even{});
        expect_true("find_if all-odd returns last", it == a + 4);
    }
}

static void check_part2()
{
    // lambda predicate: find first > 12
    {
        int a[] = {5, 10, 15, 20};
        auto it = asc::std::find_if(a, a + 4, [](int x) { return x > 12; });
        expect_eq("*find_if(a, a+4, x>12)", *it, 15);
        expect_true("find_if x>12 at a+2", it == a + 2);
    }

    // vector iterator
    {
        std::vector<int> v = {3, 5, 8, 11};
        auto it = asc::std::find_if(v.begin(), v.end(), is_even{});
        expect_eq("*find_if on vector (is_even)", *it, 8);
    }

    // single element match
    {
        int a[] = {42};
        auto it = asc::std::find_if(a, a + 1, is_even{});
        expect_eq("*find_if single element (is_even)", *it, 42);
    }

    // single element no match
    {
        int a[] = {43};
        auto it = asc::std::find_if(a, a + 1, is_even{});
        expect_true("find_if single odd returns end", it == a + 1);
    }

    // negative values: find first even among negatives
    {
        int a[] = {-3, -1, -2, -5};
        auto it = asc::std::find_if(a, a + 4, is_even{});
        expect_eq("*find_if with negatives (is_even)", *it, -2);
        expect_true("find_if negatives at a+2", it == a + 2);
    }
}

int main()
{
    check_part1();
    check_part2();

    return g_failures == 0 ? 0 : 1;
}
