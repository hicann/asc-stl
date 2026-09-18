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

#include <asc/std/__type_traits/remove_volatile.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][remove_volatile] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    // Basic: volatile int -> int
    expect_true("is_same<remove_volatile<volatile int>::type, int>",
        std::is_same<asc::std::remove_volatile<volatile int>::type, int>::value);

    // Non-volatile stays the same
    expect_true(
        "is_same<remove_volatile<int>::type, int>", std::is_same<asc::std::remove_volatile<int>::type, int>::value);

    // remove_volatile_t alias
    expect_true("is_same<remove_volatile_t<volatile int>, int>",
        std::is_same<asc::std::remove_volatile_t<volatile int>, int>::value);

    expect_true("is_same<remove_volatile_t<int>, int>", std::is_same<asc::std::remove_volatile_t<int>, int>::value);

    // const volatile -> const (only volatile removed)
    expect_true("is_same<remove_volatile<const volatile int>::type, const int>",
        std::is_same<asc::std::remove_volatile<const volatile int>::type, const int>::value);

    expect_true("is_same<remove_volatile_t<const volatile int>, const int>",
        std::is_same<asc::std::remove_volatile_t<const volatile int>, const int>::value);

    // volatile char -> char
    expect_true("is_same<remove_volatile<volatile char>::type, char>",
        std::is_same<asc::std::remove_volatile<volatile char>::type, char>::value);

    // volatile double -> double
    expect_true("is_same<remove_volatile_t<volatile double>, double>",
        std::is_same<asc::std::remove_volatile_t<volatile double>, double>::value);

    // pointer to volatile int -> unchanged (volatile is on pointee, not top-level)
    expect_true("is_same<remove_volatile_t<volatile int*>, volatile int*>",
        std::is_same<asc::std::remove_volatile_t<volatile int*>, volatile int*>::value);

    // volatile pointer to int -> pointer to int (volatile is top-level on pointer)
    expect_true("is_same<remove_volatile_t<int* volatile>, int*>",
        std::is_same<asc::std::remove_volatile_t<int* volatile>, int*>::value);

    // Reference types - volatile on a reference is ignored, so type stays the same
    expect_true("is_same<remove_volatile_t<int&>, int&>", std::is_same<asc::std::remove_volatile_t<int&>, int&>::value);

    return g_failures == 0 ? 0 : 1;
}
