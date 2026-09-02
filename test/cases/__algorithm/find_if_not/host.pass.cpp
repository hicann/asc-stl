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

#include <asc/std/__algorithm/find_if_not.h>
#include <iostream>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][find_if_not] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][find_if_not] " << expr << (cond ? " satisfied" : " NOT satisfied") << " -> "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

struct MismatchFinder {
    int target_;
    constexpr MismatchFinder(int target) noexcept : target_(target)  // NOLINT(runtime/explicit)
    {}
    constexpr bool operator()(int candidate) const noexcept
    {
        return candidate != target_;
    }
};

int main()
{
    const int arr[] = {2, 4, 6, 8};

    // first element matches (pred returns false for 2, i.e., val_ == other)
    {
        auto it = asc::std::find_if_not(arr, arr + 4, MismatchFinder(2));
        expect_eq("*find_if_not(arr, arr+4, MismatchFinder(2))", *it, 2);
        expect_true("find_if_not(arr, arr+4, MismatchFinder(2)) == arr", it == arr);
    }

    // empty range; return last
    {
        auto it = asc::std::find_if_not(arr, arr, MismatchFinder(2));
        expect_true("find_if_not(arr, arr, MismatchFinder(2)) == arr", it == arr);
    }

    // multiple matches; return first match
    {
        const int arr_multiple[] = {2, 4, 4, 8};
        auto it = asc::std::find_if_not(arr_multiple, arr_multiple + 4, MismatchFinder(4));
        expect_eq("*find_if_not(arr_multiple, MismatchFinder(4))", *it, 4);
        expect_true("find_if_not result == arr_multiple+1", it == arr_multiple + 1);
    }

    // some element matches
    {
        auto it = asc::std::find_if_not(arr, arr + 4, MismatchFinder(6));
        expect_eq("*find_if_not(arr, MismatchFinder(6))", *it, 6);
        expect_true("find_if_not result == arr+2", it == arr + 2);
    }

    // last element matches
    {
        auto it = asc::std::find_if_not(arr, arr + 4, MismatchFinder(8));
        expect_eq("*find_if_not(arr, MismatchFinder(8))", *it, 8);
        expect_true("find_if_not result == arr+3", it == arr + 3);
    }

    // no element matches; return last
    {
        auto it = asc::std::find_if_not(arr, arr + 4, MismatchFinder(10));
        expect_true("find_if_not(arr, MismatchFinder(10)) == arr+4", it == arr + 4);
    }

    // lambda predicate: find first even number (pred = is_odd, find_if_not finds first not-odd = first even)
    {
        const int data[] = {1, 3, 5, 2, 7};
        auto is_odd = [](int v) { return v % 2 != 0; };
        auto it = asc::std::find_if_not(data, data + 5, is_odd);
        expect_eq("*find_if_not(data, is_odd)", *it, 2);
        expect_true("find_if_not result == data+3", it == data + 3);
    }

    return g_failures == 0 ? 0 : 1;
}
