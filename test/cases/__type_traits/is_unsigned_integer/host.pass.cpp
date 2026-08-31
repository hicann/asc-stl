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

#include <asc/std/__type_traits/is_unsigned_integer.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][is_unsigned_integer] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][is_unsigned_integer] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

int main()
{
    // --- __asc_is_unsigned_integer_v: unsigned integer types -> true
    expect_true("__asc_is_unsigned_integer_v<unsigned char>", asc::std::__asc_is_unsigned_integer_v<unsigned char>);
    expect_true("__asc_is_unsigned_integer_v<unsigned short>", asc::std::__asc_is_unsigned_integer_v<unsigned short>);
    expect_true("__asc_is_unsigned_integer_v<unsigned int>", asc::std::__asc_is_unsigned_integer_v<unsigned int>);
    expect_true("__asc_is_unsigned_integer_v<unsigned long>", asc::std::__asc_is_unsigned_integer_v<unsigned long>);
    expect_true(
        "__asc_is_unsigned_integer_v<unsigned long long>", asc::std::__asc_is_unsigned_integer_v<unsigned long long>);

    // --- __asc_is_unsigned_integer_v: signed integer types -> false
    expect_false("__asc_is_unsigned_integer_v<signed char>", asc::std::__asc_is_unsigned_integer_v<signed char>);
    expect_false("__asc_is_unsigned_integer_v<short>", asc::std::__asc_is_unsigned_integer_v<short>);
    expect_false("__asc_is_unsigned_integer_v<int>", asc::std::__asc_is_unsigned_integer_v<int>);
    expect_false("__asc_is_unsigned_integer_v<long>", asc::std::__asc_is_unsigned_integer_v<long>);
    expect_false("__asc_is_unsigned_integer_v<long long>", asc::std::__asc_is_unsigned_integer_v<long long>);

    // --- __asc_is_unsigned_integer_v: non-integer types -> false
    expect_false("__asc_is_unsigned_integer_v<bool>", asc::std::__asc_is_unsigned_integer_v<bool>);
    expect_false("__asc_is_unsigned_integer_v<float>", asc::std::__asc_is_unsigned_integer_v<float>);
    expect_false("__asc_is_unsigned_integer_v<double>", asc::std::__asc_is_unsigned_integer_v<double>);
    expect_false("__asc_is_unsigned_integer_v<char>", asc::std::__asc_is_unsigned_integer_v<char>);
    expect_false("__asc_is_unsigned_integer_v<void>", asc::std::__asc_is_unsigned_integer_v<void>);

    // --- __asc_is_cv_unsigned_integer_v: CV-qualified unsigned types -> true
    expect_true("__asc_is_cv_unsigned_integer_v<const unsigned int>",
        asc::std::__asc_is_cv_unsigned_integer_v<const unsigned int>);
    expect_true("__asc_is_cv_unsigned_integer_v<volatile unsigned int>",
        asc::std::__asc_is_cv_unsigned_integer_v<volatile unsigned int>);
    expect_true("__asc_is_cv_unsigned_integer_v<const volatile unsigned int>",
        asc::std::__asc_is_cv_unsigned_integer_v<const volatile unsigned int>);
    expect_true("__asc_is_cv_unsigned_integer_v<const unsigned char>",
        asc::std::__asc_is_cv_unsigned_integer_v<const unsigned char>);
    expect_true("__asc_is_cv_unsigned_integer_v<volatile unsigned long long>",
        asc::std::__asc_is_cv_unsigned_integer_v<volatile unsigned long long>);

    // --- __asc_is_cv_unsigned_integer_v: CV-qualified signed types -> false
    expect_false("__asc_is_cv_unsigned_integer_v<const int>", asc::std::__asc_is_cv_unsigned_integer_v<const int>);
    expect_false(
        "__asc_is_cv_unsigned_integer_v<volatile short>", asc::std::__asc_is_cv_unsigned_integer_v<volatile short>);
    expect_false("__asc_is_cv_unsigned_integer_v<const volatile long>",
        asc::std::__asc_is_cv_unsigned_integer_v<const volatile long>);

    // --- __asc_is_cv_unsigned_integer_v: CV-qualified non-integer types -> false
    expect_false("__asc_is_cv_unsigned_integer_v<const float>", asc::std::__asc_is_cv_unsigned_integer_v<const float>);
    expect_false("__asc_is_cv_unsigned_integer_v<const bool>", asc::std::__asc_is_cv_unsigned_integer_v<const bool>);

    // --- __asc_is_cv_unsigned_integer_v: unqualified unsigned types -> true
    expect_true("__asc_is_cv_unsigned_integer_v<unsigned int>", asc::std::__asc_is_cv_unsigned_integer_v<unsigned int>);
    expect_true(
        "__asc_is_cv_unsigned_integer_v<unsigned long>", asc::std::__asc_is_cv_unsigned_integer_v<unsigned long>);

    // --- __asc_is_cv_unsigned_integer_v: unqualified signed types -> false
    expect_false("__asc_is_cv_unsigned_integer_v<int>", asc::std::__asc_is_cv_unsigned_integer_v<int>);
    expect_false("__asc_is_cv_unsigned_integer_v<double>", asc::std::__asc_is_cv_unsigned_integer_v<double>);

    return g_failures == 0 ? 0 : 1;
}
