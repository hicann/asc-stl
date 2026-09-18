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

#include <asc/std/__type_traits/extent.h>
#include <iostream>
#include <cstddef>

static int g_failures = 0;

static void expect_eq_size(const char* expr, std::size_t got, std::size_t expected)
{
    bool ok = (got == expected);
    std::cout << "[host][extent] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // Non-array type
    expect_eq_size("extent<int, 0>::value", asc::std::extent<int, 0>::value, 0);
    expect_eq_size("extent<int>::value", asc::std::extent<int>::value, 0);

    // Single-dimension array
    expect_eq_size("extent<int[3], 0>::value", asc::std::extent<int[3], 0>::value, 3);
    expect_eq_size("extent<int[3]>::value", asc::std::extent<int[3]>::value, 3);

    // Multi-dimension array
    expect_eq_size("extent<int[3][2], 0>::value", asc::std::extent<int[3][2], 0>::value, 3);
    expect_eq_size("extent<int[3][2], 1>::value", asc::std::extent<int[3][2], 1>::value, 2);
    expect_eq_size("extent<int[3][2], 2>::value", asc::std::extent<int[3][2], 2>::value, 0);

    // Three-dimension array
    expect_eq_size("extent<int[5][4][3], 0>::value", asc::std::extent<int[5][4][3], 0>::value, 5);
    expect_eq_size("extent<int[5][4][3], 1>::value", asc::std::extent<int[5][4][3], 1>::value, 4);
    expect_eq_size("extent<int[5][4][3], 2>::value", asc::std::extent<int[5][4][3], 2>::value, 3);
    expect_eq_size("extent<int[5][4][3], 3>::value", asc::std::extent<int[5][4][3], 3>::value, 0);

    // Unbounded array
    expect_eq_size("extent<int[], 0>::value", asc::std::extent<int[], 0>::value, 0);

    // extent_v variable template
    expect_eq_size("extent_v<int>", asc::std::extent_v<int>, 0);
    expect_eq_size("extent_v<int[3]>", asc::std::extent_v<int[3]>, 3);
    expect_eq_size("extent_v<int[3][2], 0>", asc::std::extent_v<int[3][2], 0>, 3);
    expect_eq_size("extent_v<int[3][2], 1>", asc::std::extent_v<int[3][2], 1>, 2);
    expect_eq_size("extent_v<int[5][4][3], 2>", asc::std::extent_v<int[5][4][3], 2>, 3);

    // Different element types
    expect_eq_size("extent<double[7], 0>::value", asc::std::extent<double[7], 0>::value, 7);
    expect_eq_size("extent<char[1], 0>::value", asc::std::extent<char[1], 0>::value, 1);

    // integral_constant inheritance: operator value_type() and operator()
    expect_eq_size("extent<int[3], 0>()()", static_cast<std::size_t>(asc::std::extent<int[3], 0>()()), 3);
    expect_eq_size("extent<int[3], 0> conversion", static_cast<std::size_t>(asc::std::extent<int[3], 0>{}), 3);

    return g_failures == 0 ? 0 : 1;
}
