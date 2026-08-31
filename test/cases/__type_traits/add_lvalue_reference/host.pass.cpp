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

#include <asc/std/__type_traits/add_lvalue_reference.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

template <typename Actual, typename Expected>
static void expect_same(const char* expr)
{
    bool ok = std::is_same<Actual, Expected>::value;
    std::cout << "[host][add_lvalue_reference] " << expr << " -> " << (ok ? "correct" : "WRONG") << " "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

struct MyStruct {};

int main()
{
    // Basic referenceable types -> T&
    expect_same<asc::std::add_lvalue_reference_t<int>, int&>("add_lvalue_reference_t<int>");
    expect_same<asc::std::add_lvalue_reference_t<float>, float&>("add_lvalue_reference_t<float>");
    expect_same<asc::std::add_lvalue_reference_t<const int>, const int&>("add_lvalue_reference_t<const int>");
    expect_same<asc::std::add_lvalue_reference_t<int*>, int*&>("add_lvalue_reference_t<int*>");

    // Reference collapsing
    expect_same<asc::std::add_lvalue_reference_t<int&>, int&>("add_lvalue_reference_t<int&>");
    expect_same<asc::std::add_lvalue_reference_t<int&&>, int&>("add_lvalue_reference_t<int&&>");

    // Non-referenceable types -> unchanged
    expect_same<asc::std::add_lvalue_reference_t<void>, void>("add_lvalue_reference_t<void>");
    expect_same<asc::std::add_lvalue_reference_t<const void>, const void>("add_lvalue_reference_t<const void>");

    // User-defined type
    expect_same<asc::std::add_lvalue_reference_t<MyStruct>, MyStruct&>("add_lvalue_reference_t<MyStruct>");

    // Function type -> reference to function
    expect_same<asc::std::add_lvalue_reference_t<void(int)>, void (&)(int)>("add_lvalue_reference_t<void(int)>");

    // Struct member type alias matches the _t alias
    expect_same<asc::std::add_lvalue_reference<int>::type, int&>("add_lvalue_reference<int>::type");
    expect_same<asc::std::add_lvalue_reference<void>::type, void>("add_lvalue_reference<void>::type");
    expect_same<asc::std::add_lvalue_reference<int&>::type, int&>("add_lvalue_reference<int&>::type");

    return g_failures == 0 ? 0 : 1;
}
