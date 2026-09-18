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

#include <asc/std/__fwd/array.h>
#include <array>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][array] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][array] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

int main()
{
    // ---- __is_asc_std_array_v: true only for asc::std::array<T, N> ----
    expect_true(
        "__is_asc_std_array_v<asc::std::array<int, 3>>", asc::std::__is_asc_std_array_v<asc::std::array<int, 3>>);
    expect_true(
        "__is_asc_std_array_v<asc::std::array<float, 0>>", asc::std::__is_asc_std_array_v<asc::std::array<float, 0>>);
    expect_true("__is_asc_std_array_v<asc::std::array<double, 10>>",
        asc::std::__is_asc_std_array_v<asc::std::array<double, 10>>);
    expect_false("__is_asc_std_array_v<int>", asc::std::__is_asc_std_array_v<int>);
    expect_false("__is_asc_std_array_v<double>", asc::std::__is_asc_std_array_v<double>);

#if CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()
    // std::array is NOT an asc::std::array
    expect_false("__is_asc_std_array_v<std::array<int, 3>>", asc::std::__is_asc_std_array_v<std::array<int, 3>>);

    // ---- __is_std_array_v: true only for ::std::array<T, N> ----
    expect_true("__is_std_array_v<std::array<int, 3>>", asc::std::__is_std_array_v<std::array<int, 3>>);
    expect_true("__is_std_array_v<std::array<double, 5>>", asc::std::__is_std_array_v<std::array<double, 5>>);
    expect_true("__is_std_array_v<std::array<float, 0>>", asc::std::__is_std_array_v<std::array<float, 0>>);
    expect_false("__is_std_array_v<int>", asc::std::__is_std_array_v<int>);
    expect_false("__is_std_array_v<double>", asc::std::__is_std_array_v<double>);
    // asc::std::array is NOT a std::array
    expect_false("__is_std_array_v<asc::std::array<int, 3>>", asc::std::__is_std_array_v<asc::std::array<int, 3>>);
#endif  // CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()

    return g_failures == 0 ? 0 : 1;
}
