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

#include <asc/std/__algorithm/generate.h>
#include <iostream>
#include <vector>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][generate] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // Test 1: Basic fill with constant generator
    {
        int arr[5] = {0, 0, 0, 0, 0};
        asc::std::generate(arr, arr + 5, []() { return 42; });
        for (int i = 0; i < 5; ++i) {
            expect_eq("arr[i] after generate 42", arr[i], 42);
        }
    }

    // Test 2: Incrementing generator with captured state
    {
        int arr[5] = {0, 0, 0, 0, 0};
        int counter = 0;
        asc::std::generate(arr, arr + 5, [&counter]() { return counter++; });
        for (int i = 0; i < 5; ++i) {
            expect_eq("arr[i] after generate counter++", arr[i], i);
        }
    }

    // Test 3: Empty range should not modify the container
    {
        int arr[5] = {1, 2, 3, 4, 5};
        asc::std::generate(arr, arr, []() { return 99; });
        for (int i = 0; i < 5; ++i) {
            expect_eq("arr[i] after empty generate", arr[i], i + 1);
        }
    }

    // Test 4: Float vector
    {
        std::vector<float> vec(3);
        asc::std::generate(vec.begin(), vec.end(), []() { return 3.14f; });
        for (size_t i = 0; i < 3; ++i) {
            expect_eq("vec[i] after generate 3.14f", vec[i], 3.14f);
        }
    }

    return g_failures == 0 ? 0 : 1;
}
