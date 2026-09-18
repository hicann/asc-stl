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

#include <asc/std/__type_traits/add_cv.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][add_cv] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    // add_cv<int>::type should be const volatile int
    expect_true("is_same<add_cv<int>::type, const volatile int>",
        std::is_same<asc::std::add_cv<int>::type, const volatile int>::value);

    // add_cv<const int>::type should be const volatile int (cv already present)
    expect_true("is_same<add_cv<const int>::type, const volatile int>",
        std::is_same<asc::std::add_cv<const int>::type, const volatile int>::value);

    // add_cv<volatile int>::type should be const volatile int
    expect_true("is_same<add_cv<volatile int>::type, const volatile int>",
        std::is_same<asc::std::add_cv<volatile int>::type, const volatile int>::value);

    // add_cv<const volatile int>::type should be const volatile int
    expect_true("is_same<add_cv<const volatile int>::type, const volatile int>",
        std::is_same<asc::std::add_cv<const volatile int>::type, const volatile int>::value);

    // add_cv<int*>::type should be int* const volatile (cv applies to the pointer itself, not the pointee)
    expect_true("is_same<add_cv<int*>::type, int* const volatile>",
        std::is_same<asc::std::add_cv<int*>::type, int* const volatile>::value);

    // add_cv<int&>::type should be int& (references are not cv-qualified)
    expect_true("is_same<add_cv<int&>::type, int&>", std::is_same<asc::std::add_cv<int&>::type, int&>::value);

    // add_cv_t<int> should be const volatile int
    expect_true(
        "is_same<add_cv_t<int>, const volatile int>", std::is_same<asc::std::add_cv_t<int>, const volatile int>::value);

    // add_cv_t<double> should be const volatile double
    expect_true("is_same<add_cv_t<double>, const volatile double>",
        std::is_same<asc::std::add_cv_t<double>, const volatile double>::value);

    // add_cv_t<const char> should be const volatile char
    expect_true("is_same<add_cv_t<const char>, const volatile char>",
        std::is_same<asc::std::add_cv_t<const char>, const volatile char>::value);

    // add_cv<int**>::type should be int** const volatile (cv applies to the top-level pointer)
    expect_true("is_same<add_cv<int**>::type, int** const volatile>",
        std::is_same<asc::std::add_cv<int**>::type, int** const volatile>::value);

    // add_cv<void>::type should be const volatile void
    expect_true("is_same<add_cv<void>::type, const volatile void>",
        std::is_same<asc::std::add_cv<void>::type, const volatile void>::value);

    // add_cv_t<float> should be const volatile float
    expect_true("is_same<add_cv_t<float>, const volatile float>",
        std::is_same<asc::std::add_cv_t<float>, const volatile float>::value);

    return g_failures == 0 ? 0 : 1;
}
