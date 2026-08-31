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

#include <asc/std/__type_traits/add_const.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][add_const] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    // add_const<int>::type should be const int
    expect_true(
        "is_same<add_const<int>::type, const int>", (std::is_same<asc::std::add_const<int>::type, const int>::value));

    // add_const_t<int> should be const int
    expect_true("is_same<add_const_t<int>, const int>", (std::is_same<asc::std::add_const_t<int>, const int>::value));

    // add_const on already-const type: add_const<const int>::type == const int
    expect_true("is_same<add_const<const int>::type, const int>",
        (std::is_same<asc::std::add_const<const int>::type, const int>::value));

    // add_const on volatile: add_const<volatile int>::type == const volatile int
    expect_true("is_same<add_const<volatile int>::type, const volatile int>",
        (std::is_same<asc::std::add_const<volatile int>::type, const volatile int>::value));

    // add_const on pointer: add_const<int*>::type == int* const
    expect_true("is_same<add_const<int*>::type, int* const>",
        (std::is_same<asc::std::add_const<int*>::type, int* const>::value));

    // add_const on reference: add_const<int&>::type == int& (references cannot be const-qualified)
    expect_true("is_same<add_const<int&>::type, int&>", (std::is_same<asc::std::add_const<int&>::type, int&>::value));

    // add_const_t alias matches add_const<...>::type
    expect_true("is_same<add_const_t<double>, add_const<double>::type>",
        (std::is_same<asc::std::add_const_t<double>, asc::std::add_const<double>::type>::value));

    // add_const on char
    expect_true("is_same<add_const<char>::type, const char>",
        (std::is_same<asc::std::add_const<char>::type, const char>::value));

    // Verify const-ness: a variable declared as add_const_t<int> should hold its value
    {
        asc::std::add_const_t<int> ci = 42;
        (void)ci;
        expect_true("add_const_t<int> value is 42", ci == 42);
    }

    return g_failures == 0 ? 0 : 1;
}
