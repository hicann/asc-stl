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

#include <asc/std/__type_traits/remove_const.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][remove_const] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][remove_const] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

int main()
{
    // remove_const<int> -> int
    expect_true(
        "std::is_same<remove_const<int>::type, int>", (std::is_same<asc::std::remove_const<int>::type, int>::value));

    // remove_const<const int> -> int
    expect_true("std::is_same<remove_const<const int>::type, int>",
        (std::is_same<asc::std::remove_const<const int>::type, int>::value));

    // remove_const<const int*> -> const int*  (pointer to const int: no top-level const on pointer)
    expect_true("std::is_same<remove_const<const int*>::type, const int*>",
        (std::is_same<asc::std::remove_const<const int*>::type, const int*>::value));

    // remove_const<int* const> -> int*  (const pointer to non-const: top-level const removed)
    expect_true("std::is_same<remove_const<int* const>::type, int*>",
        (std::is_same<asc::std::remove_const<int* const>::type, int*>::value));

    // remove_const<const int* const> -> const int*  (only top-level const removed)
    expect_true("std::is_same<remove_const<const int* const>::type, const int*>",
        (std::is_same<asc::std::remove_const<const int* const>::type, const int*>::value));

    // remove_const<int&> -> int&  (references are not const-qualified)
    expect_true("std::is_same<remove_const<int&>::type, int&>",
        (std::is_same<asc::std::remove_const<int&>::type, int&>::value));

    // remove_const<const int&> -> const int&  (reference to const: const is not top-level)
    expect_true("std::is_same<remove_const<const int&>::type, const int&>",
        (std::is_same<asc::std::remove_const<const int&>::type, const int&>::value));

    // remove_const_t alias
    expect_true("std::is_same<remove_const_t<const int>, int>",
        (std::is_same<asc::std::remove_const_t<const int>, int>::value));

    // remove_const_t<int> -> int
    expect_true("std::is_same<remove_const_t<int>, int>", (std::is_same<asc::std::remove_const_t<int>, int>::value));

    // remove_const on volatile const -> volatile int
    expect_true("std::is_same<remove_const<const volatile int>::type, volatile int>",
        (std::is_same<asc::std::remove_const<const volatile int>::type, volatile int>::value));

    // remove_const on volatile (non-const) -> unchanged
    expect_true("std::is_same<remove_const<volatile int>::type, volatile int>",
        (std::is_same<asc::std::remove_const<volatile int>::type, volatile int>::value));

    // remove_const on const double -> double
    expect_true("std::is_same<remove_const<const double>::type, double>",
        (std::is_same<asc::std::remove_const<const double>::type, double>::value));

    // remove_const on array of const -> array of non-const
    expect_true("std::is_same<remove_const<const int[3]>::type, int[3]>",
        (std::is_same<asc::std::remove_const<const int[3]>::type, int[3]>::value));

    // Verify that remove_const<const int>::type is actually non-const
    expect_false("std::is_const<remove_const<const int>::type>",
        (std::is_const<asc::std::remove_const<const int>::type>::value));

    // Verify that remove_const<int>::type is not const
    expect_false("std::is_const<remove_const<int>::type>", (std::is_const<asc::std::remove_const<int>::type>::value));

    return g_failures == 0 ? 0 : 1;
}
