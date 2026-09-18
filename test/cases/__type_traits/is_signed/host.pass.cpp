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

#include <asc/std/__type_traits/is_signed.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool got)
{
    std::cout << "[host][is_signed] " << expr << " = " << (got ? "true" : "false") << " (expected true) "
              << (got ? "OK" : "FAIL") << std::endl;
    if (!got)
        ++g_failures;
}

static void expect_false(const char* expr, bool got)
{
    std::cout << "[host][is_signed] " << expr << " = " << (got ? "true" : "false") << " (expected false) "
              << (got ? "FAIL" : "OK") << std::endl;
    if (got)
        ++g_failures;
}

int main()
{
    // --- Signed integer types ---
    expect_true("is_signed_v<signed char>", asc::std::is_signed_v<signed char>);
    expect_true("is_signed_v<short>", asc::std::is_signed_v<short>);
    expect_true("is_signed_v<int>", asc::std::is_signed_v<int>);
    expect_true("is_signed_v<long>", asc::std::is_signed_v<long>);
    expect_true("is_signed_v<long long>", asc::std::is_signed_v<long long>);

    // --- Unsigned integer types ---
    expect_false("is_signed_v<unsigned char>", asc::std::is_signed_v<unsigned char>);
    expect_false("is_signed_v<unsigned short>", asc::std::is_signed_v<unsigned short>);
    expect_false("is_signed_v<unsigned int>", asc::std::is_signed_v<unsigned int>);
    expect_false("is_signed_v<unsigned long>", asc::std::is_signed_v<unsigned long>);
    expect_false("is_signed_v<unsigned long long>", asc::std::is_signed_v<unsigned long long>);

    // --- Floating point types (always signed) ---
    expect_true("is_signed_v<float>", asc::std::is_signed_v<float>);
    expect_true("is_signed_v<double>", asc::std::is_signed_v<double>);
    expect_true("is_signed_v<long double>", asc::std::is_signed_v<long double>);

    // --- bool is unsigned ---
    expect_false("is_signed_v<bool>", asc::std::is_signed_v<bool>);

    // --- char: implementation-defined signedness; test both is_signed<char> and the value ---
    // char may be signed or unsigned depending on platform; just verify it matches std::is_signed<char>
    {
        bool got = asc::std::is_signed_v<char>;
        bool ref = (char(-1) < char(0));  // NOLINT(readability/casting)
        if (got == ref) {
            std::cout << "[host][is_signed] is_signed_v<char> = " << (got ? "true" : "false") << " (expected "
                      << (ref ? "true" : "false") << ") OK" << std::endl;
        } else {
            std::cout << "[host][is_signed] is_signed_v<char> = " << (got ? "true" : "false") << " (expected "
                      << (ref ? "true" : "false") << ") FAIL" << std::endl;
            ++g_failures;
        }
    }

    // --- Non-arithmetic types ---
    expect_false("is_signed_v<void>", asc::std::is_signed_v<void>);
    expect_false("is_signed_v<int*>", asc::std::is_signed_v<int*>);
    expect_false("is_signed_v<void*>", asc::std::is_signed_v<void*>);

    // --- CV-qualified types (should match unqualified) ---
    expect_true("is_signed_v<const int>", asc::std::is_signed_v<const int>);
    expect_true("is_signed_v<volatile int>", asc::std::is_signed_v<volatile int>);
    expect_true("is_signed_v<const volatile int>", asc::std::is_signed_v<const volatile int>);
    expect_false("is_signed_v<const unsigned int>", asc::std::is_signed_v<const unsigned int>);
    expect_true("is_signed_v<const float>", asc::std::is_signed_v<const float>);

    // --- is_signed<T>::value should match is_signed_v<T> ---
    expect_true("is_signed<int>::value", asc::std::is_signed<int>::value);
    expect_false("is_signed<unsigned>::value", asc::std::is_signed<unsigned>::value);
    expect_true("is_signed<float>::value", asc::std::is_signed<float>::value);
    expect_false("is_signed<void>::value", asc::std::is_signed<void>::value);

    // --- is_signed<T> inherits bool_constant, so convertible to bool ---
    {
        asc::std::is_signed<int> si;
        asc::std::is_signed<unsigned> su;
        expect_true("is_signed<int>()", static_cast<bool>(si));
        expect_false("is_signed<unsigned>()", static_cast<bool>(su));
    }

    return g_failures == 0 ? 0 : 1;
}
