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

#include <asc/std/__concepts/arithmetic.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][arithmetic] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][arithmetic] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

int main()
{
    // integral
    expect_true("asc::std::integral<int>", asc::std::integral<int>);
    expect_true("asc::std::integral<unsigned>", asc::std::integral<unsigned>);
    expect_true("asc::std::integral<bool>", asc::std::integral<bool>);
    expect_true("asc::std::integral<char>", asc::std::integral<char>);
    expect_false("asc::std::integral<float>", asc::std::integral<float>);
    expect_false("asc::std::integral<double>", asc::std::integral<double>);

    // signed_integral
    expect_true("asc::std::signed_integral<int>", asc::std::signed_integral<int>);
    expect_true("asc::std::signed_integral<signed char>", asc::std::signed_integral<signed char>);
    expect_false("asc::std::signed_integral<unsigned>", asc::std::signed_integral<unsigned>);
    expect_false("asc::std::signed_integral<float>", asc::std::signed_integral<float>);

    // unsigned_integral
    expect_true("asc::std::unsigned_integral<unsigned>", asc::std::unsigned_integral<unsigned>);
    expect_false("asc::std::unsigned_integral<int>", asc::std::unsigned_integral<int>);
    expect_false("asc::std::unsigned_integral<float>", asc::std::unsigned_integral<float>);

    // floating_point
    expect_true("asc::std::floating_point<float>", asc::std::floating_point<float>);
    expect_true("asc::std::floating_point<double>", asc::std::floating_point<double>);
    expect_false("asc::std::floating_point<int>", asc::std::floating_point<int>);

    // __asc_signed_integer
    expect_true("asc::std::__asc_signed_integer<int>", asc::std::__asc_signed_integer<int>);
    expect_false("asc::std::__asc_signed_integer<unsigned>", asc::std::__asc_signed_integer<unsigned>);
    expect_false("asc::std::__asc_signed_integer<float>", asc::std::__asc_signed_integer<float>);

    return g_failures == 0 ? 0 : 1;
}
