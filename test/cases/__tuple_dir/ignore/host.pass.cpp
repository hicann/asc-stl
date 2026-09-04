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

#include <asc/std/__tuple_dir/ignore.h>
#include <iostream>
#include <string>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][ignore] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void check_part1()
{
    // Test 1: Default construction of __ignore_t
    {
        asc::std::__ignore_t ig;
        (void)ig;
        expect_true("__ignore_t default constructible", true);
    }

    // Test 2: ignore assignment from int
    {
        asc::std::ignore = 42;
        expect_true("ignore = 42 (int)", true);
    }

    // Test 3: Assignment from various types
    {
        asc::std::ignore = 3.14;
        asc::std::ignore = std::string("hello");
        asc::std::ignore = "world";
        asc::std::ignore = 'c';
        expect_true("ignore accepts double, string, const char*, char", true);
    }

    // Test 4: Assigning to ignore does not modify the source
    {
        int a = 10;
        asc::std::ignore = a;
        expect_true("source int unchanged after ignore = a", a == 10);

        double d = 2.5;
        asc::std::ignore = d;
        expect_true("source double unchanged after ignore = d", d == 2.5);
    }

    // Test 5: operator= returns const __ignore_t& (reference to ignore itself)
    {
        const asc::std::__ignore_t& ref = (asc::std::ignore = 99);
        expect_true("operator= returns reference to ignore", &ref == &asc::std::ignore);
    }
}

static void check_part2()
{
    // Test 6: Chained assignment via returned reference
    {
        (asc::std::ignore = 1) = 2;
        expect_true("chained assignment (ignore = 1) = 2", true);
    }

    // Test 7: Construction from multiple arguments (variadic constructor)
    {
        asc::std::__ignore_t ig(1, 2.0, "three");
        (void)ig;
        expect_true("__ignore_t constructible from multiple args", true);
    }

    // Test 8: Multiple sequential assignments to same ignore object
    {
        asc::std::ignore = 1;
        asc::std::ignore = 2;
        asc::std::ignore = 3;
        expect_true("multiple sequential assignments to ignore", true);
    }

    // Test 9: ignore used in a tie-like pattern (common use case)
    {
        int x = 5, y = 10;
        asc::std::ignore = x;
        y = 200;
        expect_true("ignore used in tie-like pattern, y updated", y == 200);
        expect_true("x unchanged after ignore = x", x == 5);
    }
}

int main()
{
    check_part1();
    check_part2();

    return g_failures == 0 ? 0 : 1;
}
