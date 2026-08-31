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

#include <asc/std/__type_traits/is_volatile.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_volatile] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

struct MyStruct {};

int main()
{
    // --- is_volatile_v: basic types ---
    expect_true("is_volatile_v<int>", asc::std::is_volatile_v<int>, false);
    expect_true("is_volatile_v<volatile int>", asc::std::is_volatile_v<volatile int>, true);

    // const without volatile
    expect_true("is_volatile_v<const int>", asc::std::is_volatile_v<const int>, false);

    // const volatile
    expect_true("is_volatile_v<const volatile int>", asc::std::is_volatile_v<const volatile int>, true);
    expect_true("is_volatile_v<volatile const int>", asc::std::is_volatile_v<volatile const int>, true);

    // --- pointer types ---
    expect_true("is_volatile_v<int*>", asc::std::is_volatile_v<int*>, false);
    // pointer to volatile int — pointer itself is NOT volatile
    expect_true("is_volatile_v<volatile int*>", asc::std::is_volatile_v<volatile int*>, false);
    // volatile pointer to int
    expect_true("is_volatile_v<int* volatile>", asc::std::is_volatile_v<int* volatile>, true);
    // volatile pointer to const int
    expect_true("is_volatile_v<const int* volatile>", asc::std::is_volatile_v<const int* volatile>, true);
    // const pointer to volatile int — not volatile
    expect_true("is_volatile_v<volatile int* const>", asc::std::is_volatile_v<volatile int* const>, false);

    // --- references are never volatile ---
    expect_true("is_volatile_v<int&>", asc::std::is_volatile_v<int&>, false);
    expect_true("is_volatile_v<volatile int&>", asc::std::is_volatile_v<volatile int&>, false);
    expect_true("is_volatile_v<int&&>", asc::std::is_volatile_v<int&&>, false);

    // --- void ---
    expect_true("is_volatile_v<void>", asc::std::is_volatile_v<void>, false);
    expect_true("is_volatile_v<volatile void>", asc::std::is_volatile_v<volatile void>, true);

    // --- arrays ---
    expect_true("is_volatile_v<int[3]>", asc::std::is_volatile_v<int[3]>, false);
    expect_true("is_volatile_v<volatile int[3]>", asc::std::is_volatile_v<volatile int[3]>, true);

    // --- user-defined type ---
    expect_true("is_volatile_v<MyStruct>", asc::std::is_volatile_v<MyStruct>, false);
    expect_true("is_volatile_v<volatile MyStruct>", asc::std::is_volatile_v<volatile MyStruct>, true);

    // --- is_volatile struct via ::value ---
    expect_true("is_volatile<int>::value", asc::std::is_volatile<int>::value, false);
    expect_true("is_volatile<volatile int>::value", asc::std::is_volatile<volatile int>::value, true);
    expect_true("is_volatile<const int>::value", asc::std::is_volatile<const int>::value, false);
    expect_true("is_volatile<const volatile int>::value", asc::std::is_volatile<const volatile int>::value, true);
    expect_true("is_volatile<void>::value", asc::std::is_volatile<void>::value, false);
    expect_true("is_volatile<volatile void>::value", asc::std::is_volatile<volatile void>::value, true);

    // --- is_volatile struct: implicit conversion to bool ---
    expect_true("bool(is_volatile<volatile int>{})",
        bool(asc::std::is_volatile<volatile int>{}),                                     // NOLINT(readability/casting)
        true);                                                                           // NOLINT(readability/casting)
    expect_true("bool(is_volatile<int>{})", bool(asc::std::is_volatile<int>{}), false);  // NOLINT(readability/casting)

    // --- is_volatile struct: inherits from bool_constant ---
    expect_true("is_base_of true_type (volatile int)",
        std::is_base_of<asc::std::true_type, asc::std::is_volatile<volatile int>>::value, true);
    expect_true(
        "is_base_of false_type (int)", std::is_base_of<asc::std::false_type, asc::std::is_volatile<int>>::value, true);

    // --- value_type is bool ---
    expect_true("is_same value_type bool", std::is_same<asc::std::is_volatile<int>::value_type, bool>::value, true);

    return g_failures == 0 ? 0 : 1;
}
