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

#include <asc/std/__type_traits/is_empty.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_empty] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// Empty class (no non-static data members)
struct Empty {};

// Empty class with a static data member (still empty)
struct EmptyWithStatic {
    static int s_val;
};

// Non-empty: has a non-static data member
struct NonEmpty {
    int data;
};

// Non-empty: has virtual function
struct NonEmptyVirtual {
    virtual ~NonEmptyVirtual()
    {}
};

// Empty class that inherits from another empty class
struct EmptyBase {};
struct DerivedEmpty : EmptyBase {};

// Non-empty: inherits and adds a data member
struct DerivedNonEmpty : EmptyBase {
    int extra;
};

// Union is not empty
union NonEmptyUnion {
    int a;
    float b;
};

int main()
{
    // is_empty<Empty> should be true
    expect_true("is_empty<Empty>::value", asc::std::is_empty<Empty>::value, true);
    expect_true("is_empty_v<Empty>", asc::std::is_empty_v<Empty>, true);

    // is_empty<EmptyWithStatic> should be true (static members don't count)
    expect_true("is_empty<EmptyWithStatic>::value", asc::std::is_empty<EmptyWithStatic>::value, true);
    expect_true("is_empty_v<EmptyWithStatic>", asc::std::is_empty_v<EmptyWithStatic>, true);

    // is_empty<NonEmpty> should be false (has non-static data member)
    expect_true("is_empty<NonEmpty>::value", asc::std::is_empty<NonEmpty>::value, false);
    expect_true("is_empty_v<NonEmpty>", asc::std::is_empty_v<NonEmpty>, false);

    // is_empty<NonEmptyVirtual> should be false (has vtable)
    expect_true("is_empty<NonEmptyVirtual>::value", asc::std::is_empty<NonEmptyVirtual>::value, false);
    expect_true("is_empty_v<NonEmptyVirtual>", asc::std::is_empty_v<NonEmptyVirtual>, false);

    // is_empty<DerivedEmpty> should be true (empty base, no new data)
    expect_true("is_empty<DerivedEmpty>::value", asc::std::is_empty<DerivedEmpty>::value, true);
    expect_true("is_empty_v<DerivedEmpty>", asc::std::is_empty_v<DerivedEmpty>, true);

    // is_empty<DerivedNonEmpty> should be false (adds data member)
    expect_true("is_empty<DerivedNonEmpty>::value", asc::std::is_empty<DerivedNonEmpty>::value, false);
    expect_true("is_empty_v<DerivedNonEmpty>", asc::std::is_empty_v<DerivedNonEmpty>, false);

    // is_empty<NonEmptyUnion> should be false (union is not empty)
    expect_true("is_empty<NonEmptyUnion>::value", asc::std::is_empty<NonEmptyUnion>::value, false);
    expect_true("is_empty_v<NonEmptyUnion>", asc::std::is_empty_v<NonEmptyUnion>, false);

    // is_empty<int> should be false
    expect_true("is_empty<int>::value", asc::std::is_empty<int>::value, false);
    expect_true("is_empty_v<int>", asc::std::is_empty_v<int>, false);

    // is_empty<void> should be false
    expect_true("is_empty<void>::value", asc::std::is_empty<void>::value, false);
    expect_true("is_empty_v<void>", asc::std::is_empty_v<void>, false);

    // Verify the type trait inherits from bool_constant
    static_assert(asc::std::is_empty<Empty>::value == true, "");
    static_assert(asc::std::is_empty<NonEmpty>::value == false, "");

    return g_failures == 0 ? 0 : 1;
}
