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

#include <asc/std/__algorithm/for_each.h>
#include <iostream>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][for_each] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

struct add_two {
    constexpr void operator()(int& a) const noexcept
    {
        a += 2;
    }
};

struct for_each_counter {
    int count;
    constexpr for_each_counter(int c) : count(c)  // NOLINT(runtime/explicit)
    {}
    void operator()(int& i)
    {
        ++i;
        ++count;
    }
};

int main()
{
    // Test 1: add_two functor modifies elements in place (from the upstream constexpr suite)
    {
        int ia[] = {1, 3, 6, 7};
        int expected[] = {3, 5, 8, 9};
        asc::std::for_each(ia, ia + 4, add_two{});
        for (int i = 0; i < 4; ++i) {
            expect_eq("ia[i] after for_each(add_two)", ia[i], expected[i]);
        }
    }

    // Test 2: functor with state - increments elements and counts calls (from the upstream suite)
    {
        int ia[] = {0, 1, 2, 3, 4, 5};
        const int s = 6;
        for_each_counter f = asc::std::for_each(ia, ia + s, for_each_counter(0));
        expect_eq("returned functor count", f.count, s);
        for (int i = 0; i < s; ++i) {
            expect_eq("ia[i] after for_each(increment)", ia[i], i + 1);
        }
    }

    // Test 3: lambda functor - multiply by 3
    {
        int ia[] = {1, 2, 3, 4, 5};
        int expected[] = {3, 6, 9, 12, 15};
        asc::std::for_each(ia, ia + 5, [](int& v) { v *= 3; });
        for (int i = 0; i < 5; ++i) {
            expect_eq("ia[i] after for_each(multiply3)", ia[i], expected[i]);
        }
    }

    // Test 4: empty range - functor not called, returned functor unchanged
    {
        int ia[] = {1, 2, 3};
        int call_count = 0;
        asc::std::for_each(ia, ia, [&call_count](int&) { ++call_count; });
        expect_eq("call_count for empty range", call_count, 0);
    }

    // Test 5: single element range
    {
        int ia[] = {42};
        asc::std::for_each(ia, ia + 1, [](int& v) { v = v * v; });
        expect_eq("ia[0] after for_each(square)", ia[0], 1764);
    }

    return g_failures == 0 ? 0 : 1;
}
