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

#include <asc/std/__type_traits/is_signed_integer.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][is_signed_integer] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][is_signed_integer] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

int main()
{
    // Signed integer types should be true
    expect_true("__asc_is_signed_integer_v<signed char>", asc::std::__asc_is_signed_integer_v<signed char>);
    expect_true("__asc_is_signed_integer_v<signed short>", asc::std::__asc_is_signed_integer_v<signed short>);
    expect_true("__asc_is_signed_integer_v<signed int>", asc::std::__asc_is_signed_integer_v<signed int>);
    expect_true("__asc_is_signed_integer_v<signed long>", asc::std::__asc_is_signed_integer_v<signed long>);
    expect_true("__asc_is_signed_integer_v<signed long long>", asc::std::__asc_is_signed_integer_v<signed long long>);

    // Non-signed-integer types should be false
    expect_false("__asc_is_signed_integer_v<bool>", asc::std::__asc_is_signed_integer_v<bool>);
    expect_false("__asc_is_signed_integer_v<unsigned char>", asc::std::__asc_is_signed_integer_v<unsigned char>);
    expect_false("__asc_is_signed_integer_v<unsigned short>", asc::std::__asc_is_signed_integer_v<unsigned short>);
    expect_false("__asc_is_signed_integer_v<unsigned int>", asc::std::__asc_is_signed_integer_v<unsigned int>);
    expect_false("__asc_is_signed_integer_v<unsigned long>", asc::std::__asc_is_signed_integer_v<unsigned long>);
    expect_false(
        "__asc_is_signed_integer_v<unsigned long long>", asc::std::__asc_is_signed_integer_v<unsigned long long>);
    expect_false("__asc_is_signed_integer_v<float>", asc::std::__asc_is_signed_integer_v<float>);
    expect_false("__asc_is_signed_integer_v<double>", asc::std::__asc_is_signed_integer_v<double>);
    expect_false("__asc_is_signed_integer_v<char>", asc::std::__asc_is_signed_integer_v<char>);
    expect_false("__asc_is_signed_integer_v<wchar_t>", asc::std::__asc_is_signed_integer_v<wchar_t>);
    expect_false("__asc_is_signed_integer_v<char16_t>", asc::std::__asc_is_signed_integer_v<char16_t>);
    expect_false("__asc_is_signed_integer_v<char32_t>", asc::std::__asc_is_signed_integer_v<char32_t>);

    // CV-qualified versions via __asc_is_cv_signed_integer_v
    expect_true(
        "__asc_is_cv_signed_integer_v<const signed int>", asc::std::__asc_is_cv_signed_integer_v<const signed int>);
    expect_true("__asc_is_cv_signed_integer_v<volatile signed long>",
        asc::std::__asc_is_cv_signed_integer_v<volatile signed long>);
    expect_true("__asc_is_cv_signed_integer_v<const volatile signed char>",
        asc::std::__asc_is_cv_signed_integer_v<const volatile signed char>);
    expect_true("__asc_is_cv_signed_integer_v<const signed long long>",
        asc::std::__asc_is_cv_signed_integer_v<const signed long long>);
    expect_false(
        "__asc_is_cv_signed_integer_v<const unsigned int>", asc::std::__asc_is_cv_signed_integer_v<const unsigned int>);
    expect_false(
        "__asc_is_cv_signed_integer_v<volatile float>", asc::std::__asc_is_cv_signed_integer_v<volatile float>);
    expect_false("__asc_is_cv_signed_integer_v<const volatile bool>",
        asc::std::__asc_is_cv_signed_integer_v<const volatile bool>);
    expect_false("__asc_is_cv_signed_integer_v<const char>", asc::std::__asc_is_cv_signed_integer_v<const char>);

    return g_failures == 0 ? 0 : 1;
}
