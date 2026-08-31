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

#include <asc/std/__type_traits/is_pointer.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_pointer] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

struct Foo {};

int main()
{
    // --- is_pointer_v tests ---
    // raw pointer types
    expect_true("is_pointer_v<int*>", asc::std::is_pointer_v<int*>, true);
    expect_true("is_pointer_v<const int*>", asc::std::is_pointer_v<const int*>, true);
    expect_true("is_pointer_v<int* const>", asc::std::is_pointer_v<int* const>, true);
    expect_true("is_pointer_v<const int* const>", asc::std::is_pointer_v<const int* const>, true);
    expect_true("is_pointer_v<void*>", asc::std::is_pointer_v<void*>, true);
    expect_true("is_pointer_v<char*>", asc::std::is_pointer_v<char*>, true);
    expect_true("is_pointer_v<double*>", asc::std::is_pointer_v<double*>, true);
    expect_true("is_pointer_v<int**>", asc::std::is_pointer_v<int**>, true);

    // function pointer
    expect_true("is_pointer_v<void(*)()>", asc::std::is_pointer_v<void (*)()>, true);

    // pointer to member (NOT a pointer)
    expect_true("is_pointer_v<int Foo::*>", asc::std::is_pointer_v<int Foo::*>, false);

    // non-pointer types
    expect_true("is_pointer_v<int>", asc::std::is_pointer_v<int>, false);
    expect_true("is_pointer_v<double>", asc::std::is_pointer_v<double>, false);
    expect_true("is_pointer_v<char>", asc::std::is_pointer_v<char>, false);
    expect_true("is_pointer_v<bool>", asc::std::is_pointer_v<bool>, false);
    expect_true("is_pointer_v<void>", asc::std::is_pointer_v<void>, false);
    expect_true("is_pointer_v<int&>", asc::std::is_pointer_v<int&>, false);
    expect_true("is_pointer_v<int&&>", asc::std::is_pointer_v<int&&>, false);
    expect_true("is_pointer_v<int[]>", asc::std::is_pointer_v<int[]>, false);
    expect_true("is_pointer_v<int[5]>", asc::std::is_pointer_v<int[5]>, false);

    // --- is_pointer struct (value member) ---
    expect_true("is_pointer<int*>::value", asc::std::is_pointer<int*>::value, true);
    expect_true("is_pointer<int>::value", asc::std::is_pointer<int>::value, false);
    expect_true("is_pointer<void*>::value", asc::std::is_pointer<void*>::value, true);
    expect_true("is_pointer<void>::value", asc::std::is_pointer<void>::value, false);
    expect_true("is_pointer<int*&>::value", asc::std::is_pointer<int*&>::value, false);

    // --- is_pointer as bool_constant (convertible to bool) ---
    {
        asc::std::is_pointer<int*> p;
        expect_true("is_pointer<int*>() converts to true", (bool)p, true);  // NOLINT(readability/casting)
        asc::std::is_pointer<int> np;
        expect_true("is_pointer<int>() converts to false", (bool)np, false);  // NOLINT(readability/casting)
    }

    return g_failures == 0 ? 0 : 1;
}
