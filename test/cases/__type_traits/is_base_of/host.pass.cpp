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

#include <asc/std/__type_traits/is_base_of.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][is_base_of] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][is_base_of] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

struct Base {};
struct Derived : Base {};
struct Unrelated {};
struct DerivedDerived : Derived {};
struct PrivDerived : private Base {};

int main()
{
    // Basic inheritance
    expect_true("is_base_of_v<Base, Derived>", asc::std::is_base_of_v<Base, Derived>);
    expect_true("is_base_of_v<Base, DerivedDerived>", asc::std::is_base_of_v<Base, DerivedDerived>);
    expect_true("is_base_of_v<Derived, DerivedDerived>", asc::std::is_base_of_v<Derived, DerivedDerived>);

    // Reverse direction
    expect_false("is_base_of_v<Derived, Base>", asc::std::is_base_of_v<Derived, Base>);

    // Unrelated types
    expect_false("is_base_of_v<Base, Unrelated>", asc::std::is_base_of_v<Base, Unrelated>);
    expect_false("is_base_of_v<Unrelated, Base>", asc::std::is_base_of_v<Unrelated, Base>);

    // Same class is its own base
    expect_true("is_base_of_v<Base, Base>", asc::std::is_base_of_v<Base, Base>);

    // Private inheritance
    expect_true("is_base_of_v<Base, PrivDerived>", asc::std::is_base_of_v<Base, PrivDerived>);

    // Non-class types
    expect_false("is_base_of_v<int, int>", asc::std::is_base_of_v<int, int>);
    expect_false("is_base_of_v<int, Base>", asc::std::is_base_of_v<int, Base>);
    expect_false("is_base_of_v<Base, int>", asc::std::is_base_of_v<Base, int>);

    // is_base_of::value (struct form)
    expect_true("is_base_of<Base, Derived>::value", asc::std::is_base_of<Base, Derived>::value);
    expect_false("is_base_of<Base, Unrelated>::value", asc::std::is_base_of<Base, Unrelated>::value);
    expect_true("is_base_of<Derived, DerivedDerived>::value", asc::std::is_base_of<Derived, DerivedDerived>::value);

    // integral_constant relationship: true_type is an alias for integral_constant<bool, true>
    expect_true("is_base_of<integral_constant<bool,true>, true_type>::value",
        asc::std::is_base_of<asc::std::integral_constant<bool, true>, asc::std::true_type>::value);

    return g_failures == 0 ? 0 : 1;
}
