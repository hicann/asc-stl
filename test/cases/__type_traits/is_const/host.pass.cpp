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

#include <asc/std/__type_traits/is_const.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_const] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // is_const_v tests
    expect_true("is_const_v<int>", asc::std::is_const_v<int>, false);
    expect_true("is_const_v<const int>", asc::std::is_const_v<const int>, true);
    expect_true("is_const_v<const volatile int>", asc::std::is_const_v<const volatile int>, true);
    expect_true("is_const_v<volatile int>", asc::std::is_const_v<volatile int>, false);
    expect_true("is_const_v<int*>", asc::std::is_const_v<int*>, false);
    expect_true("is_const_v<const int*>", asc::std::is_const_v<const int*>, false);
    expect_true("is_const_v<int* const>", asc::std::is_const_v<int* const>, true);
    expect_true("is_const_v<const int&>", asc::std::is_const_v<const int&>, false);
    expect_true("is_const_v<int&>", asc::std::is_const_v<int&>, false);
    expect_true("is_const_v<void>", asc::std::is_const_v<void>, false);
    expect_true("is_const_v<const void>", asc::std::is_const_v<const void>, true);

    // is_const (struct) tests
    expect_true("is_const<int>::value", asc::std::is_const<int>::value, false);
    expect_true("is_const<const int>::value", asc::std::is_const<const int>::value, true);
    expect_true("is_const<const volatile int>::value", asc::std::is_const<const volatile int>::value, true);
    expect_true("is_const<volatile int>::value", asc::std::is_const<volatile int>::value, false);
    expect_true("is_const<int*>::value", asc::std::is_const<int*>::value, false);
    expect_true("is_const<const int*>::value", asc::std::is_const<const int*>::value, false);
    expect_true("is_const<int* const>::value", asc::std::is_const<int* const>::value, true);
    expect_true("is_const<const int&>::value", asc::std::is_const<const int&>::value, false);
    expect_true("is_const<int&>::value", asc::std::is_const<int&>::value, false);
    expect_true("is_const<void>::value", asc::std::is_const<void>::value, false);
    expect_true("is_const<const void>::value", asc::std::is_const<const void>::value, true);

    // is_const inherits from bool_constant (callable as functor)
    expect_true("is_const<const int>()", asc::std::is_const<const int>(), true);
    expect_true("is_const<int>()", asc::std::is_const<int>(), false);

    // typedef'd const
    using CI = const int;
    expect_true("is_const_v<CI>", asc::std::is_const_v<CI>, true);

    // array types
    expect_true("is_const_v<int[3]>", asc::std::is_const_v<int[3]>, false);
    expect_true("is_const_v<const int[3]>", asc::std::is_const_v<const int[3]>, true);

    return g_failures == 0 ? 0 : 1;
}
