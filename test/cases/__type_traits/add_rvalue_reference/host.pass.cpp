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

#include <asc/std/__type_traits/add_rvalue_reference.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

template <typename T, typename Expected>
static void expect_same(const char* expr)
{
    bool ok = std::is_same_v<T, Expected>;
    std::cout << "[host][add_rvalue_reference] " << expr << " -> " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // Basic types: add_rvalue_reference adds &&
    expect_same<asc::std::add_rvalue_reference_t<int>, int&&>("add_rvalue_reference_t<int>");
    expect_same<asc::std::add_rvalue_reference<int>::type, int&&>("add_rvalue_reference<int>::type");

    // lvalue reference: reference collapsing & + && = &
    expect_same<asc::std::add_rvalue_reference_t<int&>, int&>("add_rvalue_reference_t<int&>");

    // rvalue reference: reference collapsing && + && = &&
    expect_same<asc::std::add_rvalue_reference_t<int&&>, int&&>("add_rvalue_reference_t<int&&>");

    // void: not referenceable, stays void
    expect_same<asc::std::add_rvalue_reference_t<void>, void>("add_rvalue_reference_t<void>");

    // const-qualified types
    expect_same<asc::std::add_rvalue_reference_t<const int>, const int&&>("add_rvalue_reference_t<const int>");

    // Function types (referenceable)
    expect_same<asc::std::add_rvalue_reference_t<void()>, void (&&)()>("add_rvalue_reference_t<void()>");

    // Pointer types
    expect_same<asc::std::add_rvalue_reference_t<int*>, int*&&>("add_rvalue_reference_t<int*>");

    // const volatile
    expect_same<asc::std::add_rvalue_reference_t<const volatile int>, const volatile int&&>(
        "add_rvalue_reference_t<const volatile int>");

    // long, double, char
    expect_same<asc::std::add_rvalue_reference_t<long>, long&&>("add_rvalue_reference_t<long>");
    expect_same<asc::std::add_rvalue_reference_t<double>, double&&>("add_rvalue_reference_t<double>");
    expect_same<asc::std::add_rvalue_reference_t<char>, char&&>("add_rvalue_reference_t<char>");

    // const void (not referenceable)
    expect_same<asc::std::add_rvalue_reference_t<const void>, const void>("add_rvalue_reference_t<const void>");

    // volatile void (not referenceable)
    expect_same<asc::std::add_rvalue_reference_t<volatile void>, volatile void>(
        "add_rvalue_reference_t<volatile void>");

    return g_failures == 0 ? 0 : 1;
}
