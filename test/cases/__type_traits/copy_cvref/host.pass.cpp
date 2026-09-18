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

#include <asc/std/__type_traits/copy_cvref.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

template <typename T, typename Expected>
static void expect_same(const char* expr)
{
    bool ok = std::is_same<T, Expected>::value;
    std::cout << "[host][copy_cvref] " << expr << " " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // No cv-ref on _From
    expect_same<asc::std::__copy_cvref_t<int, long>, long>("copy_cvref_t<int, long>");

    // const on _From
    expect_same<asc::std::__copy_cvref_t<const int, long>, const long>("copy_cvref_t<const int, long>");

    // volatile on _From
    expect_same<asc::std::__copy_cvref_t<volatile int, long>, volatile long>("copy_cvref_t<volatile int, long>");

    // const volatile on _From
    expect_same<asc::std::__copy_cvref_t<const volatile int, long>, const volatile long>(
        "copy_cvref_t<const volatile int, long>");

    // lvalue ref on _From
    expect_same<asc::std::__copy_cvref_t<int&, long>, long&>("copy_cvref_t<int&, long>");

    // const lvalue ref on _From
    expect_same<asc::std::__copy_cvref_t<const int&, long>, const long&>("copy_cvref_t<const int&, long>");

    // volatile lvalue ref on _From
    expect_same<asc::std::__copy_cvref_t<volatile int&, long>, volatile long&>("copy_cvref_t<volatile int&, long>");

    // const volatile lvalue ref on _From
    expect_same<asc::std::__copy_cvref_t<const volatile int&, long>, const volatile long&>(
        "copy_cvref_t<const volatile int&, long>");

    // rvalue ref on _From
    expect_same<asc::std::__copy_cvref_t<int&&, long>, long&&>("copy_cvref_t<int&&, long>");

    // const rvalue ref on _From
    expect_same<asc::std::__copy_cvref_t<const int&&, long>, const long&&>("copy_cvref_t<const int&&, long>");

    // volatile rvalue ref on _From
    expect_same<asc::std::__copy_cvref_t<volatile int&&, long>, volatile long&&>("copy_cvref_t<volatile int&&, long>");

    // const volatile rvalue ref on _From
    expect_same<asc::std::__copy_cvref_t<const volatile int&&, long>, const volatile long&&>(
        "copy_cvref_t<const volatile int&&, long>");

    // Different _To type (double)
    expect_same<asc::std::__copy_cvref_t<const int, double>, const double>("copy_cvref_t<const int, double>");
    expect_same<asc::std::__copy_cvref_t<int&, double>, double&>("copy_cvref_t<int&, double>");
    expect_same<asc::std::__copy_cvref_t<int&&, double>, double&&>("copy_cvref_t<int&&, double>");

    // _To already has cv qualifiers — they should combine with _From's
    expect_same<asc::std::__copy_cvref_t<const int, volatile long>, const volatile long>(
        "copy_cvref_t<const int, volatile long>");
    expect_same<asc::std::__copy_cvref_t<volatile int, const long>, const volatile long>(
        "copy_cvref_t<volatile int, const long>");
    expect_same<asc::std::__copy_cvref_t<const int&, volatile long>, const volatile long&>(
        "copy_cvref_t<const int&, volatile long>");
    expect_same<asc::std::__copy_cvref_t<int&&, const long>, const long&&>("copy_cvref_t<int&&, const long>");

    return g_failures == 0 ? 0 : 1;
}
