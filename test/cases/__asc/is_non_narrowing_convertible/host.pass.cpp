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

#include <asc/std/__asc/is_non_narrowing_convertible.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][is_non_narrowing_convertible] " << expr << " = " << (cond ? "true" : "false")
              << " (expected true) " << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][is_non_narrowing_convertible] " << expr << " = " << (cond ? "true" : "false")
              << " (expected false) " << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

template <class Dest, class Source>
constexpr bool is_nnc = __asc_internal::__is_non_narrowing_convertible<Dest, Source>::value;

int main()
{
    // ---- Same type: always true ----
    expect_true("int -> int", is_nnc<int, int>);
    expect_true("double -> double", is_nnc<double, double>);
    expect_true("float -> float", is_nnc<float, float>);

    // ---- Widening arithmetic conversions: true ----
    expect_true("int -> long", is_nnc<long, int>);
    expect_true("int -> long long", is_nnc<long long, int>);
    expect_true("short -> int", is_nnc<int, short>);
    expect_true("char -> int", is_nnc<int, char>);
    expect_true("float -> double", is_nnc<double, float>);
    expect_true("bool -> int", is_nnc<int, bool>);
    expect_true("unsigned char -> unsigned int", is_nnc<unsigned int, unsigned char>);

    // ---- Narrowing arithmetic conversions: false ----
    expect_false("int -> char", is_nnc<char, int>);
    expect_false("int -> short", is_nnc<short, int>);
    expect_false("long long -> int", is_nnc<int, long long>);
    expect_false("double -> float", is_nnc<float, double>);
    expect_false("float -> int", is_nnc<int, float>);
    expect_false("int -> float", is_nnc<float, int>);
    expect_false("int -> double", is_nnc<double, int>);

    // ---- Signed/unsigned mismatch: narrowing ----
    expect_false("unsigned int -> int", is_nnc<int, unsigned int>);
    expect_false("int -> unsigned int", is_nnc<unsigned int, int>);

    // ---- Bool narrowing ----
    expect_false("int -> bool", is_nnc<bool, int>);

    // ---- Non-convertible ----
    expect_false("void* <- int", is_nnc<void*, int>);
    expect_false("int* <- double*", is_nnc<int*, double*>);

    return g_failures == 0 ? 0 : 1;
}
