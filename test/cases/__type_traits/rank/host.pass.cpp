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

#include <asc/std/__type_traits/rank.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][rank] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // Non-array types: rank == 0
    expect_eq("rank_v<int>", asc::std::rank_v<int>, static_cast<size_t>(0));
    expect_eq("rank_v<double>", asc::std::rank_v<double>, static_cast<size_t>(0));
    expect_eq("rank_v<void*>", asc::std::rank_v<void*>, static_cast<size_t>(0));
    expect_eq("rank_v<char>", asc::std::rank_v<char>, static_cast<size_t>(0));

    // One-dimensional arrays: rank == 1
    expect_eq("rank_v<int[3]>", asc::std::rank_v<int[3]>, static_cast<size_t>(1));
    expect_eq("rank_v<double[5]>", asc::std::rank_v<double[5]>, static_cast<size_t>(1));
    expect_eq("rank_v<char[10]>", asc::std::rank_v<char[10]>, static_cast<size_t>(1));

    // Multi-dimensional arrays
    expect_eq("rank_v<int[2][3]>", asc::std::rank_v<int[2][3]>, static_cast<size_t>(2));
    expect_eq("rank_v<int[2][3][4]>", asc::std::rank_v<int[2][3][4]>, static_cast<size_t>(3));
    expect_eq("rank_v<int[2][3][4][5]>", asc::std::rank_v<int[2][3][4][5]>, static_cast<size_t>(4));

    // Unbounded arrays
    expect_eq("rank_v<int[]>", asc::std::rank_v<int[]>, static_cast<size_t>(1));
    expect_eq("rank_v<int[][3]>", asc::std::rank_v<int[][3]>, static_cast<size_t>(2));
    expect_eq("rank_v<int[][3][4]>", asc::std::rank_v<int[][3][4]>, static_cast<size_t>(3));

    // rank struct (integral_constant): check ::value and implicit conversion
    expect_eq("rank<int>::value", asc::std::rank<int>::value, static_cast<size_t>(0));
    expect_eq("rank<int[3]>::value", asc::std::rank<int[3]>::value, static_cast<size_t>(1));
    expect_eq("rank<int[2][3]>::value", asc::std::rank<int[2][3]>::value, static_cast<size_t>(2));
    expect_eq("rank<int[2][3][4]>::value", asc::std::rank<int[2][3][4]>::value, static_cast<size_t>(3));

    // rank as integral_constant: check value_type and operator()
    {
        asc::std::rank<int[5]> r;
        expect_eq("rank<int[5]>()()", r(), static_cast<size_t>(1));
        expect_eq("rank<int[5]> operator value_type", static_cast<size_t>(r), static_cast<size_t>(1));
    }

    // Consistency: rank_v<T> == rank<T>::value
    expect_eq("rank_v<int[2][3][4]> == rank<int[2][3][4]>::value", asc::std::rank_v<int[2][3][4]>,
        asc::std::rank<int[2][3][4]>::value);

    // Array of pointers is not a multi-dimensional array
    expect_eq("rank_v<int*[3]>", asc::std::rank_v<int* [3]>, static_cast<size_t>(1));

    // Function type: rank == 0
    expect_eq("rank_v<void()>", asc::std::rank_v<void()>, static_cast<size_t>(0));

    return g_failures == 0 ? 0 : 1;
}
