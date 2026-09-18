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

#include <asc/std/__type_traits/is_fully_bounded_array.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_fully_bounded_array] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // Non-array types → false
    expect_true("__is_fully_bounded_array_v<int>", asc::std::__is_fully_bounded_array_v<int>, false);
    expect_true("__is_fully_bounded_array_v<double>", asc::std::__is_fully_bounded_array_v<double>, false);
    expect_true("__is_fully_bounded_array_v<char>", asc::std::__is_fully_bounded_array_v<char>, false);

    // Unbounded array of non-array element → false
    expect_true("__is_fully_bounded_array_v<int[]>", asc::std::__is_fully_bounded_array_v<int[]>, false);

    // Bounded 1-D array → true
    expect_true("__is_fully_bounded_array_v<int[1]>", asc::std::__is_fully_bounded_array_v<int[1]>, true);
    expect_true("__is_fully_bounded_array_v<int[5]>", asc::std::__is_fully_bounded_array_v<int[5]>, true);
    expect_true("__is_fully_bounded_array_v<double[10]>", asc::std::__is_fully_bounded_array_v<double[10]>, true);

    // Bounded multi-dimensional array of bounded element → true
    expect_true("__is_fully_bounded_array_v<int[1][2]>", asc::std::__is_fully_bounded_array_v<int[1][2]>, true);
    expect_true("__is_fully_bounded_array_v<int[1][1][1]>", asc::std::__is_fully_bounded_array_v<int[1][1][1]>, true);
    expect_true("__is_fully_bounded_array_v<int[2][3][4]>", asc::std::__is_fully_bounded_array_v<int[2][3][4]>, true);

    // Unbounded multi-dimensional arrays → false
    // int[][2]: outer unbounded → false
    expect_true("__is_fully_bounded_array_v<int[][2]>", asc::std::__is_fully_bounded_array_v<int[][2]>, false);
    // int[][1][1]: outer unbounded → false
    expect_true("__is_fully_bounded_array_v<int[][1][1]>", asc::std::__is_fully_bounded_array_v<int[][1][1]>, false);

    return g_failures == 0 ? 0 : 1;
}
