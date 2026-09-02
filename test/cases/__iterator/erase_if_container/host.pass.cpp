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

#include <asc/std/__iterator/erase_if_container.h>
#include <algorithm>
#include <iostream>
#include <vector>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][erase_if_container] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_vec_eq(const char* expr, const std::vector<int>& got, const std::vector<int>& expected)
{
    const bool ok = (got.size() == expected.size()) && std::equal(got.begin(), got.end(), expected.begin());
    std::cout << "[host][erase_if_container] " << expr << " = [";
    for (size_t i = 0; i < got.size(); ++i) {
        if (i)
            std::cout << ", ";
        std::cout << got[i];
    }
    std::cout << "] (expected [";
    for (size_t i = 0; i < expected.size(); ++i) {
        if (i)
            std::cout << ", ";
        std::cout << expected[i];
    }
    std::cout << "]) " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void check_part1()
{
    // Test 1: Remove even numbers
    {
        std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        auto pred = [](int x) { return x % 2 == 0; };
        auto erased = asc::std::__asc_erase_if_container(v, pred);
        expect_eq("erase_if_container(remove even) count", erased, (std::vector<int>::size_type)5);
        expect_vec_eq("erase_if_container(remove even) contents", v, std::vector<int>({1, 3, 5, 7, 9}));
    }

    // Test 2: Remove odd numbers
    {
        std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        auto pred = [](int x) { return x % 2 != 0; };
        auto erased = asc::std::__asc_erase_if_container(v, pred);
        expect_eq("erase_if_container(remove odd) count", erased, (std::vector<int>::size_type)5);
        expect_vec_eq("erase_if_container(remove odd) contents", v, std::vector<int>({2, 4, 6, 8, 10}));
    }

    // Test 3: Remove nothing (predicate always false)
    {
        std::vector<int> v = {1, 2, 3};
        auto pred = [](int) { return false; };
        auto erased = asc::std::__asc_erase_if_container(v, pred);
        expect_eq("erase_if_container(remove none) count", erased, (std::vector<int>::size_type)0);
        expect_vec_eq("erase_if_container(remove none) contents", v, std::vector<int>({1, 2, 3}));
    }

    // Test 4: Remove everything (predicate always true)
    {
        std::vector<int> v = {1, 2, 3, 4, 5};
        auto pred = [](int) { return true; };
        auto erased = asc::std::__asc_erase_if_container(v, pred);
        expect_eq("erase_if_container(remove all) count", erased, (std::vector<int>::size_type)5);
        expect_vec_eq("erase_if_container(remove all) contents", v, std::vector<int>({}));
    }

    // Test 5: Remove elements greater than threshold
    {
        std::vector<int> v = {5, 3, 8, 1, 9, 2, 7, 4, 6};
        auto pred = [](int x) { return x > 5; };
        auto erased = asc::std::__asc_erase_if_container(v, pred);
        expect_eq("erase_if_container(remove >5) count", erased, (std::vector<int>::size_type)4);
        expect_vec_eq("erase_if_container(remove >5) contents", v, std::vector<int>({5, 3, 1, 2, 4}));
    }
}

static void check_part2()
{
    // Test 6: Empty container
    {
        std::vector<int> v;
        auto pred = [](int) { return true; };
        auto erased = asc::std::__asc_erase_if_container(v, pred);
        expect_eq("erase_if_container(empty) count", erased, (std::vector<int>::size_type)0);
        expect_vec_eq("erase_if_container(empty) contents", v, std::vector<int>({}));
    }

    // Test 7: Single element removed
    {
        std::vector<int> v = {42};
        auto pred = [](int x) { return x == 42; };
        auto erased = asc::std::__asc_erase_if_container(v, pred);
        expect_eq("erase_if_container(single remove) count", erased, (std::vector<int>::size_type)1);
        expect_vec_eq("erase_if_container(single remove) contents", v, std::vector<int>({}));
    }

    // Test 8: Single element kept
    {
        std::vector<int> v = {42};
        auto pred = [](int x) { return x != 42; };
        auto erased = asc::std::__asc_erase_if_container(v, pred);
        expect_eq("erase_if_container(single keep) count", erased, (std::vector<int>::size_type)0);
        expect_vec_eq("erase_if_container(single keep) contents", v, std::vector<int>({42}));
    }

    // Test 9: Consecutive elements at beginning removed
    {
        std::vector<int> v = {2, 4, 6, 1, 3, 5, 8, 10};
        auto pred = [](int x) { return x % 2 == 0; };
        auto erased = asc::std::__asc_erase_if_container(v, pred);
        expect_eq("erase_if_container(consecutive start) count", erased, (std::vector<int>::size_type)5);
        expect_vec_eq("erase_if_container(consecutive start) contents", v, std::vector<int>({1, 3, 5}));
    }

    // Test 10: Consecutive elements at end removed
    {
        std::vector<int> v = {1, 3, 5, 2, 4, 6, 8, 10};
        auto pred = [](int x) { return x % 2 == 0; };
        auto erased = asc::std::__asc_erase_if_container(v, pred);
        expect_eq("erase_if_container(consecutive end) count", erased, (std::vector<int>::size_type)5);
        expect_vec_eq("erase_if_container(consecutive end) contents", v, std::vector<int>({1, 3, 5}));
    }
}

int main()
{
    check_part1();
    check_part2();

    return g_failures == 0 ? 0 : 1;
}
