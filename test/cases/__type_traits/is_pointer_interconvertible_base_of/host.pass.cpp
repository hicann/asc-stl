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

#include <asc/std/__type_traits/is_pointer_interconvertible_base_of.h>
#include <iostream>

static int g_failures = 0;

static void expect_bool(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_pointer_interconvertible_base_of] " << expr << " = " << (got ? "true" : "false")
              << " (expected " << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

struct Base {};
struct Derived : Base {};
struct DerivedWithMember : Base {
    int x;
};
struct Unrelated {};
struct NonStandardLayout : Base {
    virtual ~NonStandardLayout()
    {}
};

int main()
{
    // Same type (class) -> true
    expect_bool("is_pointer_interconvertible_base_of_v<Base, Base>",
        asc::std::is_pointer_interconvertible_base_of_v<Base, Base>, true);
    expect_bool("is_pointer_interconvertible_base_of_v<Derived, Derived>",
        asc::std::is_pointer_interconvertible_base_of_v<Derived, Derived>, true);

    // Base of derived (standard layout, pointer-interconvertible) -> true
    expect_bool("is_pointer_interconvertible_base_of_v<Base, Derived>",
        asc::std::is_pointer_interconvertible_base_of_v<Base, Derived>, true);
    expect_bool("is_pointer_interconvertible_base_of_v<Base, DerivedWithMember>",
        asc::std::is_pointer_interconvertible_base_of_v<Base, DerivedWithMember>, true);

    // Unrelated types -> false
    expect_bool("is_pointer_interconvertible_base_of_v<Base, Unrelated>",
        asc::std::is_pointer_interconvertible_base_of_v<Base, Unrelated>, false);
    expect_bool("is_pointer_interconvertible_base_of_v<Unrelated, Base>",
        asc::std::is_pointer_interconvertible_base_of_v<Unrelated, Base>, false);

    // Non-class types -> false
    expect_bool("is_pointer_interconvertible_base_of_v<int, int>",
        asc::std::is_pointer_interconvertible_base_of_v<int, int>, false);
    expect_bool("is_pointer_interconvertible_base_of_v<int, Base>",
        asc::std::is_pointer_interconvertible_base_of_v<int, Base>, false);

    // Reverse: derived is not pointer-interconvertible base of base -> false
    expect_bool("is_pointer_interconvertible_base_of_v<Derived, Base>",
        asc::std::is_pointer_interconvertible_base_of_v<Derived, Base>, false);

    // Non-standard-layout derived (has virtual function) -> false
    expect_bool("is_pointer_interconvertible_base_of_v<Base, NonStandardLayout>",
        asc::std::is_pointer_interconvertible_base_of_v<Base, NonStandardLayout>, false);

    // struct form
    expect_bool("is_pointer_interconvertible_base_of<Base, Derived>::value",
        asc::std::is_pointer_interconvertible_base_of<Base, Derived>::value, true);
    expect_bool("is_pointer_interconvertible_base_of<Base, Unrelated>::value",
        asc::std::is_pointer_interconvertible_base_of<Base, Unrelated>::value, false);

    // const/volatile same type variations (class types)
    expect_bool("is_pointer_interconvertible_base_of_v<const Base, const Base>",
        asc::std::is_pointer_interconvertible_base_of_v<const Base, const Base>, true);
    expect_bool("is_pointer_interconvertible_base_of_v<Base, const Base>",
        asc::std::is_pointer_interconvertible_base_of_v<Base, const Base>, true);
    expect_bool("is_pointer_interconvertible_base_of_v<const Base, Base>",
        asc::std::is_pointer_interconvertible_base_of_v<const Base, Base>, true);
    expect_bool("is_pointer_interconvertible_base_of_v<volatile Base, volatile Base>",
        asc::std::is_pointer_interconvertible_base_of_v<volatile Base, volatile Base>, true);
    expect_bool("is_pointer_interconvertible_base_of_v<const volatile Base, const volatile Base>",
        asc::std::is_pointer_interconvertible_base_of_v<const volatile Base, const volatile Base>, true);

    return g_failures == 0 ? 0 : 1;
}
