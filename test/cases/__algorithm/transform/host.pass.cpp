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

#include <asc/std/__algorithm/transform.h>
#include <iostream>
#include <vector>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][transform] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][transform] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

struct plusOne {
    constexpr int operator()(const int v) const noexcept
    {
        return v + 1;
    }
};

static void check_part1()
{
    // Test unary transform with plusOne (matching the upstream test semantics)
    {
        const int N = 4;
        int ia[N] = {1, 3, 6, 7};
        int ib[N + 1] = {0, 0, 0, 0, 0};
        int expected[N] = {2, 4, 7, 8};

        int* r = asc::std::transform(ia, ia + N, ib, plusOne{});
        expect_true("unary transform return == ib + N", r == ib + N);
        for (int i = 0; i < N; ++i) {
            expect_eq("unary transform ib[i]", ib[i], expected[i]);
        }
        expect_eq("unary transform ib[N] (untouched)", ib[N], 0);
    }

    // Test unary transform with lambda (float, multiply by 2)
    {
        float in[] = {1.5f, 2.5f, 3.5f};
        float out[3] = {0.0f, 0.0f, 0.0f};
        float expected[] = {3.0f, 5.0f, 7.0f};

        auto op = [](float v) { return v * 2.0f; };
        float* r = asc::std::transform(in, in + 3, out, op);
        expect_true("unary float transform return == out + 3", r == out + 3);
        for (int i = 0; i < 3; ++i) {
            expect_eq("unary float transform out[i]", out[i], expected[i]);
        }
    }

    // Test binary transform (addition)
    {
        int a[] = {1, 2, 3, 4};
        int b[] = {10, 20, 30, 40};
        int out[4] = {0, 0, 0, 0};
        int expected[] = {11, 22, 33, 44};

        auto add = [](int x, int y) { return x + y; };
        int* r = asc::std::transform(a, a + 4, b, out, add);
        expect_true("binary transform return == out + 4", r == out + 4);
        for (int i = 0; i < 4; ++i) {
            expect_eq("binary transform out[i]", out[i], expected[i]);
        }
    }
}

static void check_part2()
{
    // Test empty range (unary)
    {
        int ia[] = {1, 2, 3};
        int ib[3] = {0, 0, 0};
        int* r = asc::std::transform(ia, ia, ib, plusOne{});
        expect_true("empty range return == ib", r == ib);
        expect_eq("empty range ib[0] untouched", ib[0], 0);
    }

    // Test with std::vector iterators (unary)
    {
        std::vector<int> in = {5, 10, 15};
        std::vector<int> out(3);
        asc::std::transform(in.begin(), in.end(), out.begin(), plusOne{});
        expect_eq("vector unary transform out[0]", out[0], 6);
        expect_eq("vector unary transform out[1]", out[1], 11);
        expect_eq("vector unary transform out[2]", out[2], 16);
    }

    // Test binary transform with std::vector (multiplication)
    {
        std::vector<int> a = {1, 2, 3};
        std::vector<int> b = {100, 200, 300};
        std::vector<int> out(3);
        auto mul = [](int x, int y) { return x * y; };
        asc::std::transform(a.begin(), a.end(), b.begin(), out.begin(), mul);
        expect_eq("vector binary transform out[0]", out[0], 100);
        expect_eq("vector binary transform out[1]", out[1], 400);
        expect_eq("vector binary transform out[2]", out[2], 900);
    }

    // Test single element (unary)
    {
        int in[] = {42};
        int out[1] = {0};
        int* r = asc::std::transform(in, in + 1, out, plusOne{});
        expect_true("single element return == out + 1", r == out + 1);
        expect_eq("single element out[0]", out[0], 43);
    }
}

static void check_part3()
{
    // Test binary transform with negative values (subtraction)
    {
        int a[] = {-5, -3, 0, 7};
        int b[] = {10, -2, 0, -1};
        int out[4] = {0, 0, 0, 0};
        int expected[] = {-15, -1, 0, 8};
        auto sub = [](int x, int y) { return x - y; };
        asc::std::transform(a, a + 4, b, out, sub);  // NOLINT(build/include_what_you_use)
        for (int i = 0; i < 4; ++i) {
            expect_eq("binary transform (sub) out[i]", out[i], expected[i]);
        }
    }
}

int main()
{
    check_part1();
    check_part2();
    check_part3();

    return g_failures == 0 ? 0 : 1;
}
