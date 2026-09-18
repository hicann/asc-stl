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

#include <asc/std/__algorithm/remove_copy_if.h>
#include <iostream>
#include <vector>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][remove_copy_if] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][remove_copy_if] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void check_part1()
{
    // Basic test: remove odd numbers from int array
    {
        int input[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int output[10] = {};
        auto result = asc::std::remove_copy_if(input, input + 10, output, [](int x) { return x % 2 != 0; });
        int count = static_cast<int>(result - output);
        expect_eq("basic count (remove odd)", count, 5);
        expect_eq("output[0]", output[0], 2);
        expect_eq("output[1]", output[1], 4);
        expect_eq("output[2]", output[2], 6);
        expect_eq("output[3]", output[3], 8);
        expect_eq("output[4]", output[4], 10);
    }

    // Empty range: result should equal output begin
    {
        int input[] = {1, 2, 3};
        int output[3] = {};
        auto result = asc::std::remove_copy_if(input, input, output, [](int x) {
            static_cast<void>(x);
            return true;
        });
        expect_true("empty range result == output", result == output);
    }

    // All elements match predicate: nothing copied
    {
        int input[] = {1, 2, 3, 4, 5};
        int output[5] = {0};
        auto result = asc::std::remove_copy_if(input, input + 5, output, [](int x) { return x > 0; });
        expect_true("all match result == output", result == output);
    }

    // No elements match predicate: all copied
    {
        int input[] = {1, 2, 3, 4, 5};
        int output[5] = {};
        auto result = asc::std::remove_copy_if(input, input + 5, output, [](int x) { return x > 10; });
        int count = static_cast<int>(result - output);
        expect_eq("none match count", count, 5);
        expect_eq("none match output[0]", output[0], 1);
        expect_eq("none match output[1]", output[1], 2);
        expect_eq("none match output[2]", output[2], 3);
        expect_eq("none match output[3]", output[3], 4);
        expect_eq("none match output[4]", output[4], 5);
    }
}

static void check_part2()
{
    // Test with floats: remove values > 3.0f
    {
        float input[] = {1.5f, 2.5f, 3.5f, 4.5f, 5.5f};
        float output[5] = {};
        auto result = asc::std::remove_copy_if(input, input + 5, output, [](float x) { return x > 3.0f; });
        int count = static_cast<int>(result - output);
        expect_eq("float count", count, 2);
        expect_eq("float output[0]", output[0], 1.5f);
        expect_eq("float output[1]", output[1], 2.5f);
    }

    // Test with vector iterators: remove value 30
    {
        std::vector<int> input = {10, 20, 30, 40, 50};
        std::vector<int> output(5);
        auto result =
            asc::std::remove_copy_if(input.begin(), input.end(), output.begin(), [](int x) { return x == 30; });
        int count = static_cast<int>(result - output.begin());
        expect_eq("vector count (remove 30)", count, 4);
        expect_eq("vector output[0]", output[0], 10);
        expect_eq("vector output[1]", output[1], 20);
        expect_eq("vector output[2]", output[2], 40);
        expect_eq("vector output[3]", output[3], 50);
    }

    // Single element: predicate matches (removed)
    {
        int input[] = {42};
        int output[1] = {0};
        auto result = asc::std::remove_copy_if(input, input + 1, output, [](int x) { return x == 42; });
        expect_true("single match result == output", result == output);
    }

    // Single element: predicate does not match (kept)
    {
        int input[] = {42};
        int output[1] = {0};
        auto result = asc::std::remove_copy_if(input, input + 1, output, [](int x) { return x == 99; });
        expect_eq("single no-match output[0]", output[0], 42);
        expect_true("single no-match result == output+1", result == output + 1);
    }
}

static void check_part3()
{
    // Return value points past last written element
    {
        int input[] = {5, 10, 15, 20, 25};
        int output[5] = {};
        auto result = asc::std::remove_copy_if(input, input + 5, output, [](int x) { return x >= 15; });
        int count = static_cast<int>(result - output);
        expect_eq("return value count", count, 2);
        expect_eq("return value output[0]", output[0], 5);
        expect_eq("return value output[1]", output[1], 10);
    }
}

int main()
{
    check_part1();
    check_part2();
    check_part3();

    return g_failures == 0 ? 0 : 1;
}
