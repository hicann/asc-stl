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

#include <asc/std/__type_traits/is_standard_layout.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_standard_layout] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// Standard-layout types
struct StandardLayout {
    int a;
    float b;
};

struct EmptyStruct {};

struct StructWithPtr {
    int* p;
};

enum Color { Red, Green, Blue };

// Non-standard-layout types
struct NonStandardLayoutVirtual {
    virtual void f()
    {}
    int a;
};

struct NonStandardLayoutMixedAccess {
public:
    int a;

private:
    int b;
};

struct NonStandardLayoutMember {
    NonStandardLayoutVirtual m;
    int x;
};

static void test_basic_scalar_types_standard()
{
    // Basic scalar types — standard layout
    expect_true("is_standard_layout_v<int>", asc::std::is_standard_layout_v<int>, true);
    expect_true("is_standard_layout_v<float>", asc::std::is_standard_layout_v<float>, true);
    expect_true("is_standard_layout_v<double>", asc::std::is_standard_layout_v<double>, true);
    expect_true("is_standard_layout_v<char>", asc::std::is_standard_layout_v<char>, true);
    expect_true("is_standard_layout_v<bool>", asc::std::is_standard_layout_v<bool>, true);
    expect_true("is_standard_layout_v<unsigned long>", asc::std::is_standard_layout_v<unsigned long>, true);
}

static void test_pointers_standard_layout()
{
    // Pointers — standard layout
    expect_true("is_standard_layout_v<int*>", asc::std::is_standard_layout_v<int*>, true);
    expect_true("is_standard_layout_v<void*>", asc::std::is_standard_layout_v<void*>, true);
}

static void test_arrays_standard_layout()
{
    // Arrays — standard layout
    expect_true("is_standard_layout_v<int[5]>", asc::std::is_standard_layout_v<int[5]>, true);
    expect_true("is_standard_layout_v<float[10]>", asc::std::is_standard_layout_v<float[10]>, true);
}

static void test_enums_standard_layout()
{
    // Enums — standard layout
    expect_true("is_standard_layout_v<Color>", asc::std::is_standard_layout_v<Color>, true);
}

static void test_simple_structs_standard_layout()
{
    // Simple structs — standard layout
    expect_true("is_standard_layout_v<StandardLayout>", asc::std::is_standard_layout_v<StandardLayout>, true);
    expect_true("is_standard_layout_v<EmptyStruct>", asc::std::is_standard_layout_v<EmptyStruct>, true);
    expect_true("is_standard_layout_v<StructWithPtr>", asc::std::is_standard_layout_v<StructWithPtr>, true);
}

static void test_non_standard_layout_types()
{
    // Non-standard-layout types
    expect_true("is_standard_layout_v<NonStandardLayoutVirtual>",
        asc::std::is_standard_layout_v<NonStandardLayoutVirtual>, false);
    expect_true("is_standard_layout_v<NonStandardLayoutMixedAccess>",
        asc::std::is_standard_layout_v<NonStandardLayoutMixedAccess>, false);
    expect_true("is_standard_layout_v<NonStandardLayoutMember>",
        asc::std::is_standard_layout_v<NonStandardLayoutMember>, false);
}

static void test_qualified_types_standard_layout()
{
    // CV-qualified types — standard layout preserved
    expect_true("is_standard_layout_v<const int>", asc::std::is_standard_layout_v<const int>, true);
    expect_true("is_standard_layout_v<volatile float>", asc::std::is_standard_layout_v<volatile float>, true);
    expect_true(
        "is_standard_layout_v<const StandardLayout>", asc::std::is_standard_layout_v<const StandardLayout>, true);
}

static void test_references_standard_layout()
{
    // References — not standard layout
    expect_true("is_standard_layout_v<int&>", asc::std::is_standard_layout_v<int&>, false);
    expect_true("is_standard_layout_v<int&&>", asc::std::is_standard_layout_v<int&&>, false);
}

static void test_struct_form_matches_form()
{
    // Struct form matches _v form
    expect_true("is_standard_layout<int>::value", asc::std::is_standard_layout<int>::value, true);
    expect_true("is_standard_layout<float>::value", asc::std::is_standard_layout<float>::value, true);
    expect_true("is_standard_layout<StandardLayout>::value", asc::std::is_standard_layout<StandardLayout>::value, true);
    expect_true("is_standard_layout<NonStandardLayoutVirtual>::value",
        asc::std::is_standard_layout<NonStandardLayoutVirtual>::value, false);
    expect_true("is_standard_layout<NonStandardLayoutMixedAccess>::value",
        asc::std::is_standard_layout<NonStandardLayoutMixedAccess>::value, false);
    expect_true("is_standard_layout<NonStandardLayoutMember>::value",
        asc::std::is_standard_layout<NonStandardLayoutMember>::value, false);
}

static void test_inherits_integral_constant_type()
{
    // Inherits from integral_constant: value_type is bool
    {
        using VT = asc::std::is_standard_layout<int>::value_type;
        expect_true("is_standard_layout<int>::value_type is bool", std::is_same<VT, bool>::value, true);
    }
}

static void test_consistency_tested_types()
{
    // Consistency: ::value == _v for all tested types
    expect_true("consistency: is_standard_layout<int>::value == is_standard_layout_v<int>",
        asc::std::is_standard_layout<int>::value == asc::std::is_standard_layout_v<int>, true);
    expect_true(
        "consistency: is_standard_layout<NonStandardLayoutVirtual>::value == "
        "is_standard_layout_v<NonStandardLayoutVirtual>",
        asc::std::is_standard_layout<NonStandardLayoutVirtual>::value ==
            asc::std::is_standard_layout_v<NonStandardLayoutVirtual>,
        true);
}

int main()
{
    test_basic_scalar_types_standard();
    test_pointers_standard_layout();
    test_arrays_standard_layout();
    test_enums_standard_layout();
    test_simple_structs_standard_layout();
    test_non_standard_layout_types();
    test_qualified_types_standard_layout();
    test_references_standard_layout();
    test_struct_form_matches_form();
    test_inherits_integral_constant_type();
    test_consistency_tested_types();

    return g_failures == 0 ? 0 : 1;
}
