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

#include <asc/std/__algorithm/replace_copy_if.h>
#include <iostream>
#include <vector>
#include <iterator>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][replace_copy_if] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][replace_copy_if] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void check_part1()
{
    // Basic test: replace negative values with 0
    {
        int input[] = {1, -2, 3, -4, 5};
        int output[5];
        auto pred = [](int v) { return v < 0; };
        auto result = asc::std::replace_copy_if(input, input + 5, output, pred, 0);
        static_cast<void>(result);
        expect_true("basic: result == output + 5", result == output + 5);
        expect_eq("basic: output[0]", output[0], 1);
        expect_eq("basic: output[1]", output[1], 0);
        expect_eq("basic: output[2]", output[2], 3);
        expect_eq("basic: output[3]", output[3], 0);
        expect_eq("basic: output[4]", output[4], 5);
    }

    // Test with floats: replace values > 10 with 10.0f
    {
        float input[] = {1.0f, 15.0f, 5.0f, 20.0f, 10.0f};
        float output[5];
        auto pred = [](float v) { return v > 10.0f; };
        auto result = asc::std::replace_copy_if(input, input + 5, output, pred, 10.0f);
        static_cast<void>(result);
        expect_true("float: result == output + 5", result == output + 5);
        expect_eq("float: output[0]", output[0], 1.0f);
        expect_eq("float: output[1]", output[1], 10.0f);
        expect_eq("float: output[2]", output[2], 5.0f);
        expect_eq("float: output[3]", output[3], 10.0f);
        expect_eq("float: output[4]", output[4], 10.0f);
    }

    // Empty range: result should equal output (no elements written)
    {
        int input[] = {1, 2, 3};
        int output[3];
        auto pred = [](int v) { return v < 0; };
        auto result = asc::std::replace_copy_if(input, input, output, pred, 0);
        static_cast<void>(result);
        expect_true("empty: result == output", result == output);
    }
}

static void check_part2()
{
    // All elements match predicate: all replaced
    {
        int input[] = {1, 2, 3};
        int output[3];
        auto pred = [](int v) {
            static_cast<void>(v);
            return true;
        };
        auto result = asc::std::replace_copy_if(input, input + 3, output, pred, 99);
        static_cast<void>(result);
        expect_eq("all_match: output[0]", output[0], 99);
        expect_eq("all_match: output[1]", output[1], 99);
        expect_eq("all_match: output[2]", output[2], 99);
    }

    // No elements match predicate: pure copy
    {
        int input[] = {1, 2, 3};
        int output[3];
        auto pred = [](int v) {
            static_cast<void>(v);
            return false;
        };
        auto result = asc::std::replace_copy_if(input, input + 3, output, pred, 99);
        static_cast<void>(result);
        expect_eq("no_match: output[0]", output[0], 1);
        expect_eq("no_match: output[1]", output[1], 2);
        expect_eq("no_match: output[2]", output[2], 3);
    }

    // Using std::vector with back_inserter
    {
        std::vector<int> input = {10, 20, 30, 40, 50};
        std::vector<int> output;
        auto pred = [](int v) { return v > 25; };
        asc::std::replace_copy_if(input.begin(), input.end(), std::back_inserter(output), pred, 25);
        expect_eq("vector: output[0]", output[0], 10);
        expect_eq("vector: output[1]", output[1], 20);
        expect_eq("vector: output[2]", output[2], 25);
        expect_eq("vector: output[3]", output[3], 25);
        expect_eq("vector: output[4]", output[4], 25);
    }

    // Single element that matches predicate
    {
        int input[] = {-5};
        int output[1];
        auto pred = [](int v) { return v < 0; };
        auto result = asc::std::replace_copy_if(input, input + 1, output, pred, 0);
        static_cast<void>(result);
        expect_eq("single_match: output[0]", output[0], 0);
        expect_true("single_match: result == output + 1", result == output + 1);
    }
}

static void check_part3()
{
    // Single element that does not match predicate
    {
        int input[] = {7};
        int output[1];
        auto pred = [](int v) { return v < 0; };
        auto result = asc::std::replace_copy_if(input, input + 1, output, pred, 0);
        static_cast<void>(result);
        expect_eq("single_nomatch: output[0]", output[0], 7);
        expect_true("single_nomatch: result == output + 1", result == output + 1);
    }
}

int main()
{
    check_part1();
    check_part2();
    check_part3();

    return g_failures == 0 ? 0 : 1;
}
