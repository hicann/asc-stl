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

#include <asc/std/__type_traits/is_bounded_array.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_bounded_array] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // --- is_bounded_array_v ---
    // Bounded arrays → true
    expect_true("is_bounded_array_v<int[3]>", asc::std::is_bounded_array_v<int[3]>, true);
    expect_true("is_bounded_array_v<int[1]>", asc::std::is_bounded_array_v<int[1]>, true);
    expect_true("is_bounded_array_v<double[5]>", asc::std::is_bounded_array_v<double[5]>, true);
    expect_true("is_bounded_array_v<char[10]>", asc::std::is_bounded_array_v<char[10]>, true);
    expect_true("is_bounded_array_v<int[3][4]>", asc::std::is_bounded_array_v<int[3][4]>, true);

    // Unbounded arrays → false
    expect_true("is_bounded_array_v<int[]>", asc::std::is_bounded_array_v<int[]>, false);

    // Non-arrays → false
    expect_true("is_bounded_array_v<int>", asc::std::is_bounded_array_v<int>, false);
    expect_true("is_bounded_array_v<int*>", asc::std::is_bounded_array_v<int*>, false);
    expect_true("is_bounded_array_v<double>", asc::std::is_bounded_array_v<double>, false);
    expect_true("is_bounded_array_v<void>", asc::std::is_bounded_array_v<void>, false);

    // --- is_bounded_array (struct) ---
    expect_true("is_bounded_array<int[3]>::value", asc::std::is_bounded_array<int[3]>::value, true);
    expect_true("is_bounded_array<int[1]>::value", asc::std::is_bounded_array<int[1]>::value, true);
    expect_true("is_bounded_array<double[5]>::value", asc::std::is_bounded_array<double[5]>::value, true);

    expect_true("is_bounded_array<int[]>::value", asc::std::is_bounded_array<int[]>::value, false);
    expect_true("is_bounded_array<int>::value", asc::std::is_bounded_array<int>::value, false);
    expect_true("is_bounded_array<int*>::value", asc::std::is_bounded_array<int*>::value, false);
    expect_true("is_bounded_array<void>::value", asc::std::is_bounded_array<void>::value, false);

    // --- is_bounded_array convertible to bool (inherits bool_constant) ---
    expect_true("bool(is_bounded_array<int[3]>{})",
        bool(asc::std::is_bounded_array<int[3]>{}),  // NOLINT(readability/casting)
        true);                                       // NOLINT(readability/casting)
    expect_true("bool(is_bounded_array<int>{})",
        bool(asc::std::is_bounded_array<int>{}),  // NOLINT(readability/casting)
        false);                                   // NOLINT(readability/casting)

    // --- multi-dimensional bounded array ---
    expect_true("is_bounded_array_v<float[2][3]>", asc::std::is_bounded_array_v<float[2][3]>, true);
    expect_true("is_bounded_array_v<float[][3]>", asc::std::is_bounded_array_v<float[][3]>, false);

    return g_failures == 0 ? 0 : 1;
}
