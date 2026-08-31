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

#include <asc/std/__host_stdlib/numeric>
#include <iostream>
#include <vector>
#include <functional>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][numeric] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    int sum = std::accumulate(v.begin(), v.end(), 0);
    expect_eq("std::accumulate({1,2,3,4,5}, 0)", sum, 15);

    int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());
    expect_eq("std::accumulate({1,2,3,4,5}, 1, multiplies)", product, 120);

    std::vector<int> iota_v(5);
    std::iota(iota_v.begin(), iota_v.end(), 10);
    expect_eq("std::iota [4]", iota_v[4], 14);

    return g_failures == 0 ? 0 : 1;
}
