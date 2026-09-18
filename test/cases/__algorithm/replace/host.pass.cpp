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

#include <asc/std/__algorithm/replace.h>
#include <iostream>
#include <vector>

static int g_failures = 0;

static void expect_vec_eq(const char* expr, const std::vector<int>& got, const std::vector<int>& expected)
{
    bool ok = (got == expected);
    std::cout << "[host][replace] " << expr << " " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok) {
        std::cout << "  got:      ";
        for (auto v : got)
            std::cout << v << " ";
        std::cout << std::endl;
        std::cout << "  expected: ";
        for (auto v : expected)
            std::cout << v << " ";
        std::cout << std::endl;
        ++g_failures;
    }
}

static void check_part1()
{
    // Basic: replace all 3s with 99
    {
        std::vector<int> v = {1, 2, 3, 4, 3, 5, 3};
        asc::std::replace(v.begin(), v.end(), 3, 99);
        expect_vec_eq("replace {1,2,3,4,3,5,3} 3->99", v, (std::vector<int>{1, 2, 99, 4, 99, 5, 99}));
    }

    // No elements match
    {
        std::vector<int> v = {1, 2, 4, 5};
        asc::std::replace(v.begin(), v.end(), 3, 99);
        expect_vec_eq("replace {1,2,4,5} 3->99 (no match)", v, (std::vector<int>{1, 2, 4, 5}));
    }

    // All elements match
    {
        std::vector<int> v = {3, 3, 3};
        asc::std::replace(v.begin(), v.end(), 3, 99);
        expect_vec_eq("replace {3,3,3} 3->99 (all match)", v, (std::vector<int>{99, 99, 99}));
    }

    // Empty range
    {
        std::vector<int> v;
        asc::std::replace(v.begin(), v.end(), 3, 99);
        expect_vec_eq("replace empty range", v, (std::vector<int>{}));
    }

    // old_value == new_value
    {
        std::vector<int> v = {1, 2, 3, 3, 5};
        asc::std::replace(v.begin(), v.end(), 3, 3);
        expect_vec_eq("replace {1,2,3,3,5} 3->3 (same)", v, (std::vector<int>{1, 2, 3, 3, 5}));
    }

    // Float
    {
        std::vector<float> v = {1.0f, 2.0f, 3.0f, 4.0f, 3.0f};
        asc::std::replace(v.begin(), v.end(), 3.0f, 99.0f);
        std::vector<float> expected = {1.0f, 2.0f, 99.0f, 4.0f, 99.0f};
        bool ok = (v == expected);
        std::cout << "[host][replace] replace float {1,2,3,4,3} 3.0->99.0 " << (ok ? "OK" : "FAIL") << std::endl;
        if (!ok)
            ++g_failures;
    }
}

static void check_part2()
{
    // Plain array
    {
        int arr[] = {10, 20, 10, 30, 10};
        asc::std::replace(arr, arr + 5, 10, 0);
        int expected[] = {0, 20, 0, 30, 0};
        bool ok = true;
        for (int i = 0; i < 5; ++i) {
            if (arr[i] != expected[i]) {
                ok = false;
                break;
            }
        }
        std::cout << "[host][replace] replace array {10,20,10,30,10} 10->0 " << (ok ? "OK" : "FAIL") << std::endl;
        if (!ok)
            ++g_failures;
    }

    // Single element match
    {
        std::vector<int> v = {7};
        asc::std::replace(v.begin(), v.end(), 7, 42);
        expect_vec_eq("replace {7} 7->42 (single match)", v, (std::vector<int>{42}));
    }

    // Single element no match
    {
        std::vector<int> v = {7};
        asc::std::replace(v.begin(), v.end(), 8, 42);
        expect_vec_eq("replace {7} 8->42 (single no match)", v, (std::vector<int>{7}));
    }
}

int main()
{
    check_part1();
    check_part2();

    return g_failures == 0 ? 0 : 1;
}
