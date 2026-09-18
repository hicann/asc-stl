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

#include <asc/std/__type_traits/is_integer.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_integer] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // --- __asc_is_integer_v: signed integer types should be true ---
    expect_true("__asc_is_integer_v<signed char>", asc::std::__asc_is_integer_v<signed char>, true);
    expect_true("__asc_is_integer_v<signed short>", asc::std::__asc_is_integer_v<signed short>, true);
    expect_true("__asc_is_integer_v<signed int>", asc::std::__asc_is_integer_v<signed int>, true);
    expect_true("__asc_is_integer_v<signed long>", asc::std::__asc_is_integer_v<signed long>, true);
    expect_true("__asc_is_integer_v<signed long long>", asc::std::__asc_is_integer_v<signed long long>, true);

    // --- __asc_is_integer_v: unsigned integer types should be true ---
    expect_true("__asc_is_integer_v<unsigned char>", asc::std::__asc_is_integer_v<unsigned char>, true);
    expect_true("__asc_is_integer_v<unsigned short>", asc::std::__asc_is_integer_v<unsigned short>, true);
    expect_true("__asc_is_integer_v<unsigned int>", asc::std::__asc_is_integer_v<unsigned int>, true);
    expect_true("__asc_is_integer_v<unsigned long>", asc::std::__asc_is_integer_v<unsigned long>, true);
    expect_true("__asc_is_integer_v<unsigned long long>", asc::std::__asc_is_integer_v<unsigned long long>, true);

    // --- __asc_is_integer_v: bool and character types should be false ---
    expect_true("__asc_is_integer_v<bool>", asc::std::__asc_is_integer_v<bool>, false);
    expect_true("__asc_is_integer_v<char>", asc::std::__asc_is_integer_v<char>, false);
    expect_true(
        "__asc_is_integer_v<signed char> (already tested true)", asc::std::__asc_is_integer_v<signed char>, true);
    expect_true(
        "__asc_is_integer_v<unsigned char> (already tested true)", asc::std::__asc_is_integer_v<unsigned char>, true);
    expect_true("__asc_is_integer_v<wchar_t>", asc::std::__asc_is_integer_v<wchar_t>, false);
    expect_true("__asc_is_integer_v<char16_t>", asc::std::__asc_is_integer_v<char16_t>, false);
    expect_true("__asc_is_integer_v<char32_t>", asc::std::__asc_is_integer_v<char32_t>, false);

    // --- __asc_is_integer_v: floating point types should be false ---
    expect_true("__asc_is_integer_v<float>", asc::std::__asc_is_integer_v<float>, false);
    expect_true("__asc_is_integer_v<double>", asc::std::__asc_is_integer_v<double>, false);
    expect_true("__asc_is_integer_v<long double>", asc::std::__asc_is_integer_v<long double>, false);

    // --- __asc_is_integer_v: non-arithmetic types should be false ---
    expect_true("__asc_is_integer_v<void>", asc::std::__asc_is_integer_v<void>, false);
    expect_true("__asc_is_integer_v<int*>", asc::std::__asc_is_integer_v<int*>, false);
    expect_true("__asc_is_integer_v<stdnullptr>", asc::std::__asc_is_integer_v<std::nullptr_t>, false);

    // --- __asc_is_cv_integer_v: CV-qualified integer types should be true ---
    expect_true("__asc_is_cv_integer_v<const int>", asc::std::__asc_is_cv_integer_v<const int>, true);
    expect_true("__asc_is_cv_integer_v<volatile int>", asc::std::__asc_is_cv_integer_v<volatile int>, true);
    expect_true("__asc_is_cv_integer_v<const volatile int>", asc::std::__asc_is_cv_integer_v<const volatile int>, true);
    expect_true(
        "__asc_is_cv_integer_v<const unsigned long>", asc::std::__asc_is_cv_integer_v<const unsigned long>, true);
    expect_true(
        "__asc_is_cv_integer_v<volatile signed char>", asc::std::__asc_is_cv_integer_v<volatile signed char>, true);

    // --- __asc_is_cv_integer_v: CV-qualified non-integer types should be false ---
    expect_true("__asc_is_cv_integer_v<const bool>", asc::std::__asc_is_cv_integer_v<const bool>, false);
    expect_true("__asc_is_cv_integer_v<const char>", asc::std::__asc_is_cv_integer_v<const char>, false);
    expect_true("__asc_is_cv_integer_v<const float>", asc::std::__asc_is_cv_integer_v<const float>, false);
    expect_true("__asc_is_cv_integer_v<volatile double>", asc::std::__asc_is_cv_integer_v<volatile double>, false);
    expect_true("__asc_is_cv_integer_v<const void>", asc::std::__asc_is_cv_integer_v<const void>, false);

    // --- __asc_is_cv_integer_v: unqualified should match __asc_is_integer_v ---
    expect_true("__asc_is_cv_integer_v<int>", asc::std::__asc_is_cv_integer_v<int>, true);
    expect_true("__asc_is_cv_integer_v<unsigned>", asc::std::__asc_is_cv_integer_v<unsigned>, true);
    expect_true("__asc_is_cv_integer_v<bool>", asc::std::__asc_is_cv_integer_v<bool>, false);
    expect_true("__asc_is_cv_integer_v<float>", asc::std::__asc_is_cv_integer_v<float>, false);

    return g_failures == 0 ? 0 : 1;
}
