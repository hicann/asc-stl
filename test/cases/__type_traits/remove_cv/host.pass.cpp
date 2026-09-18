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

#include <asc/std/__type_traits/remove_cv.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

template <typename A, typename B>
static void expect_same(const char* expr)
{
    bool ok = std::is_same<A, B>::value;
    std::cout << "[host][remove_cv] " << expr << " => " << (ok ? "OK" : "FAIL")
              << "  (is_same<result, expected>=" << (ok ? "true" : "false") << ")" << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // remove_cv on plain type
    expect_same<asc::std::remove_cv<int>::type, int>("remove_cv<int>::type == int");
    expect_same<asc::std::remove_cv<const int>::type, int>("remove_cv<const int>::type == int");
    expect_same<asc::std::remove_cv<volatile int>::type, int>("remove_cv<volatile int>::type == int");
    expect_same<asc::std::remove_cv<const volatile int>::type, int>("remove_cv<const volatile int>::type == int");
    expect_same<asc::std::remove_cv<volatile const int>::type, int>("remove_cv<volatile const int>::type == int");

    // remove_cv_t alias
    expect_same<asc::std::remove_cv_t<int>, int>("remove_cv_t<int> == int");
    expect_same<asc::std::remove_cv_t<const int>, int>("remove_cv_t<const int> == int");
    expect_same<asc::std::remove_cv_t<volatile int>, int>("remove_cv_t<volatile int> == int");
    expect_same<asc::std::remove_cv_t<const volatile int>, int>("remove_cv_t<const volatile int> == int");

    // Pointer / reference nuances
    // const int* is "pointer to const int" — remove_cv does NOT strip the pointee's const
    expect_same<asc::std::remove_cv<const int*>::type, const int*>("remove_cv<const int*>::type == const int*");
    // int* const is "const pointer to int" — remove_cv strips the pointer's const
    expect_same<asc::std::remove_cv<int* const>::type, int*>("remove_cv<int* const>::type == int*");
    // int* volatile is "volatile pointer to int"
    expect_same<asc::std::remove_cv<int* volatile>::type, int*>("remove_cv<int* volatile>::type == int*");
    // int* const volatile
    expect_same<asc::std::remove_cv<int* const volatile>::type, int*>("remove_cv<int* const volatile>::type == int*");
    // References cannot be cv-qualified, so remove_cv is identity
    expect_same<asc::std::remove_cv<const int&>::type, const int&>("remove_cv<const int&>::type == const int&");
    expect_same<asc::std::remove_cv<int&&>::type, int&&>("remove_cv<int&&>::type == int&&");

    // With user-defined type
    struct Foo {};
    expect_same<asc::std::remove_cv<Foo>::type, Foo>("remove_cv<Foo>::type == Foo");
    expect_same<asc::std::remove_cv<const Foo>::type, Foo>("remove_cv<const Foo>::type == Foo");
    expect_same<asc::std::remove_cv<volatile Foo>::type, Foo>("remove_cv<volatile Foo>::type == Foo");
    expect_same<asc::std::remove_cv<const volatile Foo>::type, Foo>("remove_cv<const volatile Foo>::type == Foo");

    // Array types
    expect_same<asc::std::remove_cv<const int[3]>::type, int[3]>("remove_cv<const int[3]>::type == int[3]");
    expect_same<asc::std::remove_cv<volatile int[5]>::type, int[5]>("remove_cv<volatile int[5]>::type == int[5]");

    return g_failures == 0 ? 0 : 1;
}
