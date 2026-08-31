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

#include <asc/std/__type_traits/has_virtual_destructor.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][has_virtual_destructor] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// Type with virtual destructor
struct VBase {
    virtual ~VBase()
    {}
};

// Type without virtual destructor
struct NonVBase {
    ~NonVBase()
    {}
};

// Type with no destructor at all
struct TrivialDtor {
    int x;
};

// Type inheriting from a virtual destructor base
struct Derived : VBase {};

// Type inheriting from a non-virtual destructor base
struct DerivedNonV : NonVBase {};

int main()
{
    // --- has_virtual_destructor<T>::value ---
    expect_true("has_virtual_destructor<int>::value", asc::std::has_virtual_destructor<int>::value, false);
    expect_true("has_virtual_destructor<double>::value", asc::std::has_virtual_destructor<double>::value, false);
    expect_true("has_virtual_destructor<VBase>::value", asc::std::has_virtual_destructor<VBase>::value, true);
    expect_true("has_virtual_destructor<NonVBase>::value", asc::std::has_virtual_destructor<NonVBase>::value, false);
    expect_true(
        "has_virtual_destructor<TrivialDtor>::value", asc::std::has_virtual_destructor<TrivialDtor>::value, false);
    expect_true("has_virtual_destructor<Derived>::value", asc::std::has_virtual_destructor<Derived>::value, true);
    expect_true(
        "has_virtual_destructor<DerivedNonV>::value", asc::std::has_virtual_destructor<DerivedNonV>::value, false);

    // --- has_virtual_destructor_v<T> ---
    expect_true("has_virtual_destructor_v<int>", asc::std::has_virtual_destructor_v<int>, false);
    expect_true("has_virtual_destructor_v<VBase>", asc::std::has_virtual_destructor_v<VBase>, true);
    expect_true("has_virtual_destructor_v<NonVBase>", asc::std::has_virtual_destructor_v<NonVBase>, false);
    expect_true("has_virtual_destructor_v<Derived>", asc::std::has_virtual_destructor_v<Derived>, true);
    expect_true("has_virtual_destructor_v<DerivedNonV>", asc::std::has_virtual_destructor_v<DerivedNonV>, false);

    // --- Cross-check with std::has_virtual_destructor ---
    expect_true(
        "cross-check VBase vs std", asc::std::has_virtual_destructor_v<VBase>, std::has_virtual_destructor_v<VBase>);
    expect_true("cross-check int vs std", asc::std::has_virtual_destructor_v<int>, std::has_virtual_destructor_v<int>);
    expect_true("cross-check NonVBase vs std", asc::std::has_virtual_destructor_v<NonVBase>,
        std::has_virtual_destructor_v<NonVBase>);
    expect_true("cross-check Derived vs std", asc::std::has_virtual_destructor_v<Derived>,
        std::has_virtual_destructor_v<Derived>);

    // --- Inherited bool_constant interface ---
    expect_true(
        "has_virtual_destructor<VBase>::type::value", asc::std::has_virtual_destructor<VBase>::type::value, true);
    expect_true("has_virtual_destructor<int>::type::value", asc::std::has_virtual_destructor<int>::type::value, false);

    return g_failures == 0 ? 0 : 1;
}
