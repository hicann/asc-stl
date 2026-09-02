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

#include <asc/std/__algorithm/remove_copy.h>
#include <iostream>
#include <vector>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][remove_copy] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void check_part1()
{
    // Basic test: remove all 3s from {1, 2, 3, 4, 3, 5}
    {
        int input[] = {1, 2, 3, 4, 3, 5};
        int output[6];
        int* result = asc::std::remove_copy(input, input + 6, output, 3);
        int count = static_cast<int>(result - output);
        expect_eq("remove_copy count (remove 3)", count, 4);
        expect_eq("output[0]", output[0], 1);
        expect_eq("output[1]", output[1], 2);
        expect_eq("output[2]", output[2], 4);
        expect_eq("output[3]", output[3], 5);
    }

    // All elements match the remove value
    {
        int input[] = {7, 7, 7, 7};
        int output[4];
        int* result = asc::std::remove_copy(input, input + 4, output, 7);
        int count = static_cast<int>(result - output);
        expect_eq("remove_copy count (all match)", count, 0);
    }

    // No elements match the remove value
    {
        int input[] = {1, 2, 3, 4};
        int output[4];
        int* result = asc::std::remove_copy(input, input + 4, output, 9);
        int count = static_cast<int>(result - output);
        expect_eq("remove_copy count (none match)", count, 4);
        expect_eq("output[0]", output[0], 1);
        expect_eq("output[1]", output[1], 2);
        expect_eq("output[2]", output[2], 3);
        expect_eq("output[3]", output[3], 4);
    }

    // Empty input range
    {
        int input[] = {1, 2, 3};
        int output[3];
        int* result = asc::std::remove_copy(input, input, output, 1);
        int count = static_cast<int>(result - output);
        expect_eq("remove_copy count (empty range)", count, 0);
    }
}

static void check_part2()
{
    // Float test
    {
        float input[] = {1.5f, 2.5f, 3.5f, 2.5f, 4.5f};
        float output[5];
        float* result = asc::std::remove_copy(input, input + 5, output, 2.5f);
        int count = static_cast<int>(result - output);
        expect_eq("remove_copy count (float, remove 2.5)", count, 3);
        expect_eq("float output[0]", output[0], 1.5f);
        expect_eq("float output[1]", output[1], 3.5f);
        expect_eq("float output[2]", output[2], 4.5f);
    }

    // Using std::vector iterators
    {
        std::vector<int> input = {10, 20, 30, 20, 40, 20, 50};
        std::vector<int> output(7);
        std::vector<int>::iterator result = asc::std::remove_copy(input.begin(), input.end(), output.begin(), 20);
        int count = static_cast<int>(result - output.begin());
        expect_eq("remove_copy count (vector, remove 20)", count, 4);
        expect_eq("vector output[0]", output[0], 10);
        expect_eq("vector output[1]", output[1], 30);
        expect_eq("vector output[2]", output[2], 40);
        expect_eq("vector output[3]", output[3], 50);
    }

    // Single element, no match
    {
        int input[] = {42};
        int output[1];
        int* result = asc::std::remove_copy(input, input + 1, output, 99);
        int count = static_cast<int>(result - output);
        expect_eq("remove_copy count (single elem, no match)", count, 1);
        expect_eq("single output[0]", output[0], 42);
    }

    // Single element, match
    {
        int input[] = {42};
        int output[1];
        int* result = asc::std::remove_copy(input, input + 1, output, 42);
        int count = static_cast<int>(result - output);
        expect_eq("remove_copy count (single elem, match)", count, 0);
    }
}

int main()
{
    check_part1();
    check_part2();

    return g_failures == 0 ? 0 : 1;
}
