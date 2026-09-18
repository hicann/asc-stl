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

#include <asc/std/__type_traits/add_volatile.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][add_volatile] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    // Basic: add_volatile<int>::type == volatile int
    expect_true("is_same<add_volatile<int>::type, volatile int>",
        (std::is_same<asc::std::add_volatile<int>::type, volatile int>::value));

    // add_volatile_t<int> == volatile int
    expect_true("is_same<add_volatile_t<int>, volatile int>",
        (std::is_same<asc::std::add_volatile_t<int>, volatile int>::value));

    // add_volatile on already volatile type
    expect_true("is_same<add_volatile<volatile int>::type, volatile int>",
        (std::is_same<asc::std::add_volatile<volatile int>::type, volatile int>::value));

    expect_true("is_same<add_volatile_t<volatile int>, volatile int>",
        (std::is_same<asc::std::add_volatile_t<volatile int>, volatile int>::value));

    // add_volatile on const type -> const volatile
    expect_true("is_same<add_volatile<const int>::type, const volatile int>",
        (std::is_same<asc::std::add_volatile<const int>::type, const volatile int>::value));

    expect_true("is_same<add_volatile_t<const int>, const volatile int>",
        (std::is_same<asc::std::add_volatile_t<const int>, const volatile int>::value));

    // add_volatile on pointer -> pointer-to-int volatile (volatile on the pointer itself)
    expect_true("is_same<add_volatile<int*>::type, int* volatile>",
        (std::is_same<asc::std::add_volatile<int*>::type, int* volatile>::value));

    expect_true("is_same<add_volatile_t<int*>, int* volatile>",
        (std::is_same<asc::std::add_volatile_t<int*>, int* volatile>::value));

    // add_volatile on reference -> reference unchanged (references cannot be volatile-qualified)
    expect_true(
        "is_same<add_volatile<int&>::type, int&>", (std::is_same<asc::std::add_volatile<int&>::type, int&>::value));

    expect_true("is_same<add_volatile_t<int&>, int&>", (std::is_same<asc::std::add_volatile_t<int&>, int&>::value));

    // add_volatile on double
    expect_true("is_same<add_volatile<double>::type, volatile double>",
        (std::is_same<asc::std::add_volatile<double>::type, volatile double>::value));

    expect_true("is_same<add_volatile_t<double>, volatile double>",
        (std::is_same<asc::std::add_volatile_t<double>, volatile double>::value));

    // add_volatile on a custom struct type
    struct MyStruct {};
    expect_true("is_same<add_volatile<MyStruct>::type, volatile MyStruct>",
        (std::is_same<asc::std::add_volatile<MyStruct>::type, volatile MyStruct>::value));

    expect_true("is_same<add_volatile_t<MyStruct>, volatile MyStruct>",
        (std::is_same<asc::std::add_volatile_t<MyStruct>, volatile MyStruct>::value));

    // add_volatile on void
    expect_true("is_same<add_volatile<void>::type, volatile void>",
        (std::is_same<asc::std::add_volatile<void>::type, volatile void>::value));

    expect_true("is_same<add_volatile_t<void>, volatile void>",
        (std::is_same<asc::std::add_volatile_t<void>, volatile void>::value));

    return g_failures == 0 ? 0 : 1;
}
