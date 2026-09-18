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

#include <asc/std/__numeric/iota.h>
#include <iostream>
#include <vector>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][iota] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

static void check_basic_sequences()
{
    // Basic: iota from 0
    {
        int arr[5] = {0};
        asc::std::iota(arr, arr + 5, 0);
        expect_eq("iota(arr, arr+5, 0)[0]", arr[0], 0);
        expect_eq("iota(arr, arr+5, 0)[1]", arr[1], 1);
        expect_eq("iota(arr, arr+5, 0)[2]", arr[2], 2);
        expect_eq("iota(arr, arr+5, 0)[3]", arr[3], 3);
        expect_eq("iota(arr, arr+5, 0)[4]", arr[4], 4);
    }

    // Non-zero start
    {
        int arr[5] = {0};
        asc::std::iota(arr, arr + 5, 10);
        expect_eq("iota(arr, arr+5, 10)[0]", arr[0], 10);
        expect_eq("iota(arr, arr+5, 10)[1]", arr[1], 11);
        expect_eq("iota(arr, arr+5, 10)[4]", arr[4], 14);
    }
}

static void check_boundary_cases()
{
    // Negative start
    {
        int arr[5] = {0};
        asc::std::iota(arr, arr + 5, -3);
        expect_eq("iota(arr, arr+5, -3)[0]", arr[0], -3);
        expect_eq("iota(arr, arr+5, -3)[1]", arr[1], -2);
        expect_eq("iota(arr, arr+5, -3)[4]", arr[4], 1);
    }

    // Empty range (no change)
    {
        int arr[1] = {42};
        asc::std::iota(arr, arr, 0);
        expect_eq("iota(arr, arr, 0)[0] (empty range)", arr[0], 42);
    }

    // Single element
    {
        int arr[1] = {0};
        asc::std::iota(arr, arr + 1, 100);
        expect_eq("iota(arr, arr+1, 100)[0]", arr[0], 100);
    }
}

static void check_floating_and_iterators()
{
    // Float type
    {
        float arr[4] = {0};
        asc::std::iota(arr, arr + 4, 0.5f);
        expect_eq("iota(arr, arr+4, 0.5f)[0]", arr[0], 0.5f);
        expect_eq("iota(arr, arr+4, 0.5f)[1]", arr[1], 1.5f);
        expect_eq("iota(arr, arr+4, 0.5f)[2]", arr[2], 2.5f);
        expect_eq("iota(arr, arr+4, 0.5f)[3]", arr[3], 3.5f);
    }

    // Vector iterator
    {
        std::vector<int> v(6, 0);
        asc::std::iota(v.begin(), v.end(), 1);
        expect_eq("iota(v.begin(), v.end(), 1)[0]", v[0], 1);
        expect_eq("iota(v.begin(), v.end(), 1)[3]", v[3], 4);
        expect_eq("iota(v.begin(), v.end(), 1)[5]", v[5], 6);
    }
}

int main()
{
    check_basic_sequences();
    check_boundary_cases();
    check_floating_and_iterators();
}
