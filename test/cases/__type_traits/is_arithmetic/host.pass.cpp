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

#include <asc/std/__type_traits/is_arithmetic.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][is_arithmetic] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][is_arithmetic] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

int main()
{
    // --- integral types: true ---
    expect_true("is_arithmetic_v<bool>", asc::std::is_arithmetic_v<bool>);
    expect_true("is_arithmetic_v<char>", asc::std::is_arithmetic_v<char>);
    expect_true("is_arithmetic_v<signed char>", asc::std::is_arithmetic_v<signed char>);
    expect_true("is_arithmetic_v<unsigned char>", asc::std::is_arithmetic_v<unsigned char>);
    expect_true("is_arithmetic_v<short>", asc::std::is_arithmetic_v<short>);
    expect_true("is_arithmetic_v<unsigned short>", asc::std::is_arithmetic_v<unsigned short>);
    expect_true("is_arithmetic_v<int>", asc::std::is_arithmetic_v<int>);
    expect_true("is_arithmetic_v<unsigned int>", asc::std::is_arithmetic_v<unsigned int>);
    expect_true("is_arithmetic_v<long>", asc::std::is_arithmetic_v<long>);
    expect_true("is_arithmetic_v<unsigned long>", asc::std::is_arithmetic_v<unsigned long>);
    expect_true("is_arithmetic_v<long long>", asc::std::is_arithmetic_v<long long>);
    expect_true("is_arithmetic_v<unsigned long long>", asc::std::is_arithmetic_v<unsigned long long>);
    expect_true("is_arithmetic_v<wchar_t>", asc::std::is_arithmetic_v<wchar_t>);
    expect_true("is_arithmetic_v<char16_t>", asc::std::is_arithmetic_v<char16_t>);
    expect_true("is_arithmetic_v<char32_t>", asc::std::is_arithmetic_v<char32_t>);

    // --- floating point types: true ---
    expect_true("is_arithmetic_v<float>", asc::std::is_arithmetic_v<float>);
    expect_true("is_arithmetic_v<double>", asc::std::is_arithmetic_v<double>);
    expect_true("is_arithmetic_v<long double>", asc::std::is_arithmetic_v<long double>);

    // --- cv-qualified arithmetic types: true ---
    expect_true("is_arithmetic_v<const int>", asc::std::is_arithmetic_v<const int>);
    expect_true("is_arithmetic_v<volatile float>", asc::std::is_arithmetic_v<volatile float>);
    expect_true("is_arithmetic_v<const volatile double>", asc::std::is_arithmetic_v<const volatile double>);
    expect_true("is_arithmetic_v<const unsigned long>", asc::std::is_arithmetic_v<const unsigned long>);

    // --- non-arithmetic types: false ---
    expect_false("is_arithmetic_v<void>", asc::std::is_arithmetic_v<void>);
    expect_false("is_arithmetic_v<void*>", asc::std::is_arithmetic_v<void*>);
    expect_false("is_arithmetic_v<int*>", asc::std::is_arithmetic_v<int*>);
    expect_false("is_arithmetic_v<const char*>", asc::std::is_arithmetic_v<const char*>);
    expect_false("is_arithmetic_v<int[3]>", asc::std::is_arithmetic_v<int[3]>);
    expect_false("is_arithmetic_v<int&>", asc::std::is_arithmetic_v<int&>);
    expect_false("is_arithmetic_v<int&&>", asc::std::is_arithmetic_v<int&&>);

    struct S {};
    expect_false("is_arithmetic_v<S>", asc::std::is_arithmetic_v<S>);
    expect_false("is_arithmetic_v<S*>", asc::std::is_arithmetic_v<S*>);

    enum E { e0 };
    expect_false("is_arithmetic_v<E>", asc::std::is_arithmetic_v<E>);

    // --- struct form: is_arithmetic<T>::value ---
    expect_true("is_arithmetic<int>::value", asc::std::is_arithmetic<int>::value);
    expect_true("is_arithmetic<float>::value", asc::std::is_arithmetic<float>::value);
    expect_false("is_arithmetic<void>::value", asc::std::is_arithmetic<void>::value);
    expect_false("is_arithmetic<S>::value", asc::std::is_arithmetic<S>::value);

    // --- inheritance from bool_constant (base-of, not same-type) ---
    expect_true("is_arithmetic<int> derives from true_type",
        std::is_base_of_v<asc::std::true_type, asc::std::is_arithmetic<int>>);
    expect_true("is_arithmetic<void> derives from false_type",
        std::is_base_of_v<asc::std::false_type, asc::std::is_arithmetic<void>>);

    return g_failures == 0 ? 0 : 1;
}
