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

#include <asc/std/__iterator/access.h>
#include <iostream>
#include <vector>
#include <array>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][access] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    // Test with C-style array
    {
        int arr[] = {1, 2, 3, 4, 5};
        expect_true("begin(arr) == arr", asc::std::begin(arr) == arr);
        expect_true("end(arr) == arr + 5", asc::std::end(arr) == arr + 5);
    }

    // Test with std::vector
    {
        std::vector<int> vec = {10, 20, 30};
        expect_true("begin(vec) == vec.begin()", asc::std::begin(vec) == vec.begin());
        expect_true("end(vec) == vec.end()", asc::std::end(vec) == vec.end());
    }

    // Test with const std::vector (cbegin/cend)
    {
        const std::vector<int> cvec = {100, 200};
        expect_true("cbegin(cvec) == cvec.begin()", asc::std::cbegin(cvec) == cvec.begin());
        expect_true("cend(cvec) == cvec.end()", asc::std::cend(cvec) == cvec.end());
    }

    // Test with std::array
    {
        std::array<int, 3> aarr = {7, 8, 9};
        expect_true("begin(aarr) == aarr.begin()", asc::std::begin(aarr) == aarr.begin());
        expect_true("end(aarr) == aarr.end()", asc::std::end(aarr) == aarr.end());
    }

    return g_failures == 0 ? 0 : 1;
}
