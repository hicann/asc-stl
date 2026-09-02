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

#include <asc/std/__numeric/transform_exclusive_scan.h>
#include <iostream>
#include <vector>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][transform_exclusive_scan] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][transform_exclusive_scan] " << expr << " = " << (cond ? "true" : "false")
              << " (expected true) " << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_vec_eq(const char* expr, const std::vector<int>& got, const std::vector<int>& expected)
{
    bool ok = got.size() == expected.size();
    for (auto g = got.begin(), e = expected.begin(); ok && g != got.end(); ++g, ++e) {
        ok = (*g == *e);
    }
    std::cout << "[host][transform_exclusive_scan] " << expr << " = [";
    for (size_t i = 0; i < got.size(); ++i) {
        std::cout << got[i] << (i + 1 < got.size() ? ", " : "");
    }
    std::cout << "] (expected [";
    for (size_t i = 0; i < expected.size(); ++i) {
        std::cout << expected[i] << (i + 1 < expected.size() ? ", " : "");
    }
    std::cout << "]) " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void check_part1()
{
    // Test 1: Basic exclusive scan with addition and identity transform
    {
        std::vector<int> in = {1, 2, 3, 4, 5};
        std::vector<int> out(5);
        auto result = asc::std::transform_exclusive_scan(
            in.begin(), in.end(), out.begin(), 0, [](int a, int b) { return a + b; }, [](int x) { return x; });
        expect_true("basic: result == out.end()", result == out.end());
        expect_vec_eq("basic: scan({1,2,3,4,5}, init=0, add, id)", out, {0, 1, 3, 6, 10});
    }

    // Test 2: With non-zero init
    {
        std::vector<int> in = {1, 2, 3, 4};
        std::vector<int> out(4);
        asc::std::transform_exclusive_scan(
            in.begin(), in.end(), out.begin(), 10, [](int a, int b) { return a + b; }, [](int x) { return x; });
        expect_vec_eq("init=10: scan({1,2,3,4}, init=10, add, id)", out, {10, 11, 13, 16});
    }

    // Test 3: With unary transform (multiply by 2)
    {
        std::vector<int> in = {1, 2, 3, 4};
        std::vector<int> out(4);
        asc::std::transform_exclusive_scan(
            in.begin(), in.end(), out.begin(), 0, [](int a, int b) { return a + b; }, [](int x) { return x * 2; });
        expect_vec_eq("u=x*2: scan({1,2,3,4}, init=0, add, x*2)", out, {0, 2, 6, 12});
    }

    // Test 4: Empty range
    {
        std::vector<int> in;
        std::vector<int> out;
        auto result = asc::std::transform_exclusive_scan(
            in.begin(), in.end(), out.begin(), 0, [](int a, int b) { return a + b; }, [](int x) { return x; });
        expect_true("empty: result == out.begin()", result == out.begin());
    }

    // Test 5: Single element
    {
        std::vector<int> in = {42};
        std::vector<int> out(1);
        asc::std::transform_exclusive_scan(
            in.begin(), in.end(), out.begin(), 5, [](int a, int b) { return a + b; }, [](int x) { return x; });
        expect_vec_eq("single: scan({42}, init=5)", out, {5});
    }
}

static void check_part2()
{
    // Test 6: With multiplication as binary op
    {
        std::vector<int> in = {1, 2, 3, 4};
        std::vector<int> out(4);
        asc::std::transform_exclusive_scan(
            in.begin(), in.end(), out.begin(), 1, [](int a, int b) { return a * b; }, [](int x) { return x; });
        expect_vec_eq("mul: scan({1,2,3,4}, init=1, mul, id)", out, {1, 1, 2, 6});
    }

    // Test 7: Float with addition
    {
        std::vector<float> in = {1.5f, 2.5f, 3.5f};
        std::vector<float> out(3);
        asc::std::transform_exclusive_scan(
            in.begin(), in.end(), out.begin(), 0.0f, [](float a, float b) { return a + b; }, [](float x) { return x; });
        expect_eq("float out[0]", out[0], 0.0f);
        expect_eq("float out[1]", out[1], 1.5f);
        expect_eq("float out[2]", out[2], 4.0f);
    }

    // Test 8: Return iterator points past last written element
    {
        std::vector<int> in = {1, 2, 3};
        std::vector<int> out(5, -1);
        auto result = asc::std::transform_exclusive_scan(
            in.begin(), in.end(), out.begin(), 0, [](int a, int b) { return a + b; }, [](int x) { return x; });
        expect_true("return iter: result == out.begin()+3", result == out.begin() + 3);
        expect_eq("return iter: out[3] unchanged", out[3], -1);
    }

    // Test 9: Negative numbers
    {
        std::vector<int> in = {-3, -1, 2, 5};
        std::vector<int> out(4);
        asc::std::transform_exclusive_scan(
            in.begin(), in.end(), out.begin(), 0, [](int a, int b) { return a + b; }, [](int x) { return x; });
        expect_vec_eq("neg: scan({-3,-1,2,5}, init=0, add, id)", out, {0, -3, -4, -2});
    }
}

int main()
{
    check_part1();
    check_part2();

    return g_failures == 0 ? 0 : 1;
}
