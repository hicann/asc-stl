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

#include <asc/std/initializer_list>
#include <iostream>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][initializer_list] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][initializer_list] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void test_basic_construction_elements()
{
    // Test 1: Basic construction with elements
    {
        asc::std::initializer_list<int> il = {1, 2, 3, 4, 5};
        expect_eq("il.size()", static_cast<int>(il.size()), 5);
        expect_eq("il.begin()[0]", il.begin()[0], 1);
        expect_eq("il.begin()[4]", il.begin()[4], 5);

        int sum = 0;
        for (auto it = il.begin(); it != il.end(); ++it) {
            sum += *it;
        }
        expect_eq("sum of {1,2,3,4,5}", sum, 15);
    }
}

static void test_empty_initializer_list_used()
{
    // Test 2: Empty initializer_list (as used in expected tests with initializer_list<int>{})
    {
        asc::std::initializer_list<int> empty{};
        expect_eq("empty.size()", static_cast<int>(empty.size()), 0);
        expect_true("empty.begin() == empty.end()", empty.begin() == empty.end());
    }
}

static void test_single_element()
{
    // Test 3: Single element
    {
        asc::std::initializer_list<int> single = {42};
        expect_eq("single.size()", static_cast<int>(single.size()), 1);
        expect_eq("single.begin()[0]", single.begin()[0], 42);
    }
}

static void test_different_element_types_double()
{
    // Test 4: Different element types (double)
    {
        asc::std::initializer_list<double> dl = {1.5, 2.5, 3.5};
        expect_eq("dl.size()", static_cast<int>(dl.size()), 3);
        expect_eq("dl.begin()[0]", dl.begin()[0], 1.5);
        expect_eq("dl.begin()[2]", dl.begin()[2], 3.5);
    }
}

static void test_asc_std_initializer_list()
{
    // Test 5: __is_asc_std_initializer_list trait
    {
        expect_true("__is_asc_std_initializer_list<initializer_list<int>>",
            asc::std::__is_asc_std_initializer_list<asc::std::initializer_list<int>>);
        expect_true("!__is_asc_std_initializer_list<int>", !asc::std::__is_asc_std_initializer_list<int>);
        expect_true("!__is_asc_std_initializer_list<double>", !asc::std::__is_asc_std_initializer_list<double>);
        expect_true("__is_asc_std_initializer_list<initializer_list<double>>",
            asc::std::__is_asc_std_initializer_list<asc::std::initializer_list<double>>);
    }
}

static void test_range_based_loop()
{
    // Test 6: Range-based for loop
    {
        asc::std::initializer_list<int> il = {10, 20, 30};
        int product = 1;
        for (int x : il) {
            product *= x;
        }
        expect_eq("product of {10,20,30}", product, 6000);
    }
}

static void test_copy_construction()
{
    // Test 7: Copy construction
    {
        asc::std::initializer_list<int> orig = {1, 2, 3};
        asc::std::initializer_list<int> copy = orig;
        expect_eq("copy.size()", static_cast<int>(copy.size()), 3);
        expect_eq("copy.begin()[0]", copy.begin()[0], 1);
        expect_eq("copy.begin()[2]", copy.begin()[2], 3);
    }
}

static void test_assignment()
{
    // Test 8: Assignment
    {
        asc::std::initializer_list<int> a = {1, 2};
        asc::std::initializer_list<int> b;
        b = a;
        expect_eq("b.size() after assignment", static_cast<int>(b.size()), 2);
        expect_eq("b.begin()[0]", b.begin()[0], 1);
        expect_eq("b.begin()[1]", b.begin()[1], 2);
    }
}

int main()
{
    test_basic_construction_elements();
    test_empty_initializer_list_used();
    test_single_element();
    test_different_element_types_double();
    test_asc_std_initializer_list();
    test_range_based_loop();
    test_copy_construction();
    test_assignment();

    return g_failures == 0 ? 0 : 1;
}
