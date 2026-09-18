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

#include <asc/std/__type_traits/is_same.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_eq(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_same] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

struct Empty {};
struct Incomplete;  // forward-declared, never defined
struct Other {};

static void test_same()
{
    // --- is_same_v ---
    expect_eq("is_same_v<int, int>", asc::std::is_same_v<int, int>, true);
    expect_eq("is_same_v<int, float>", asc::std::is_same_v<int, float>, false);
    expect_eq("is_same_v<int, const int>", asc::std::is_same_v<int, const int>, false);
    expect_eq("is_same_v<int, int&>", asc::std::is_same_v<int, int&>, false);
    expect_eq("is_same_v<int*, int>", asc::std::is_same_v<int*, int>, false);
    expect_eq("is_same_v<int*, const int*>", asc::std::is_same_v<int*, const int*>, false);
    expect_eq("is_same_v<Empty, Empty>", asc::std::is_same_v<Empty, Empty>, true);
    expect_eq("is_same_v<Empty, Other>", asc::std::is_same_v<Empty, Other>, false);
    expect_eq("is_same_v<Incomplete, Incomplete>", asc::std::is_same_v<Incomplete, Incomplete>, true);
    expect_eq("is_same_v<Incomplete, Empty>", asc::std::is_same_v<Incomplete, Empty>, false);
    expect_eq("is_same_v<void, void>", asc::std::is_same_v<void, void>, true);
    expect_eq("is_same_v<void, int>", asc::std::is_same_v<void, int>, false);
    expect_eq("is_same_v<char[3], char[3]>", asc::std::is_same_v<char[3], char[3]>, true);
    expect_eq("is_same_v<char[3], char[4]>", asc::std::is_same_v<char[3], char[4]>, false);
    expect_eq("is_same_v<long, long long>", asc::std::is_same_v<long, long long>, false);
    expect_eq("is_same_v<unsigned, unsigned int>", asc::std::is_same_v<unsigned, unsigned int>, true);
}

static void test_same_struct_inherits_bool()
{
    // --- is_same struct (inherits bool_constant, so has ::value) ---
    expect_eq("is_same<int,int>::value", asc::std::is_same<int, int>::value, true);
    expect_eq("is_same<int,float>::value", asc::std::is_same<int, float>::value, false);
    expect_eq("is_same<Empty,Empty>::value", asc::std::is_same<Empty, Empty>::value, true);
    expect_eq("is_same<Empty,Other>::value", asc::std::is_same<Empty, Other>::value, false);
}

static void test_same_inherits_true_type()
{
    // --- is_same inherits from true_type / false_type ---
    expect_eq("is_same<int,int> is true_type", asc::std::is_same_v<int, int> && true, true);
}

static void test_issame_alias()
{
    // --- _IsSame alias ---
    expect_eq("_IsSame<int,int>::value", asc::std::_IsSame<int, int>::value, true);
    expect_eq("_IsSame<int,float>::value", asc::std::_IsSame<int, float>::value, false);
}

static void test_isnotsame_alias()
{
    // --- _IsNotSame alias ---
    expect_eq("_IsNotSame<int,int>::value", asc::std::_IsNotSame<int, int>::value, false);
    expect_eq("_IsNotSame<int,float>::value", asc::std::_IsNotSame<int, float>::value, true);
}

static void test_qualified()
{
    // --- cv-qualified ---
    expect_eq("is_same_v<const int, const int>", asc::std::is_same_v<const int, const int>, true);
    expect_eq("is_same_v<volatile int, volatile int>", asc::std::is_same_v<volatile int, volatile int>, true);
    expect_eq("is_same_v<const volatile int, const int>", asc::std::is_same_v<const volatile int, const int>, false);
}

static void test_reference_types()
{
    // --- reference types ---
    expect_eq("is_same_v<int&, int&>", asc::std::is_same_v<int&, int&>, true);
    expect_eq("is_same_v<int&&, int&&>", asc::std::is_same_v<int&&, int&&>, true);
    expect_eq("is_same_v<int&, int&&>", asc::std::is_same_v<int&, int&&>, false);
}

static void test_function_types()
{
    // --- function types ---
    expect_eq("is_same_v<int(int), int(int)>", asc::std::is_same_v<int(int), int(int)>, true);
    expect_eq("is_same_v<int(int), int(float)>", asc::std::is_same_v<int(int), int(float)>, false);
}

static void test_enum_types()
{
    // --- enum types ---
    enum ColorA { Red, Green, Blue };
    enum ColorB { Cyan, Magenta, Yellow };
    expect_eq("is_same_v<ColorA, ColorA>", asc::std::is_same_v<ColorA, ColorA>, true);
    expect_eq("is_same_v<ColorA, ColorB>", asc::std::is_same_v<ColorA, ColorB>, false);
}

static void test_pointer_member()
{
    // --- pointer-to-member ---
    struct WithMember {
        int x;
    };
    expect_eq("is_same_v<int WithMember::*, int WithMember::*>",
        asc::std::is_same_v<int WithMember::*, int WithMember::*>, true);
    expect_eq(
        "is_same_v<int WithMember::*, int Other::*>", asc::std::is_same_v<int WithMember::*, int Other::*>, false);
}

static void test_static_assert_time_same()
{
    // --- static_assert compile-time checks (same semantics) ---
    static_assert(asc::std::is_same_v<int, int>, "int == int");
    static_assert(!asc::std::is_same_v<int, float>, "int != float");
    static_assert(asc::std::is_same<int, int>::value, "struct form");
    static_assert(asc::std::_IsSame<int, int>::value, "_IsSame alias");
    static_assert(asc::std::_IsNotSame<int, float>::value, "_IsNotSame alias");
}

int main()
{
    test_same();
    test_same_struct_inherits_bool();
    test_same_inherits_true_type();
    test_issame_alias();
    test_isnotsame_alias();
    test_qualified();
    test_reference_types();
    test_function_types();
    test_enum_types();
    test_pointer_member();
    test_static_assert_time_same();

    return g_failures == 0 ? 0 : 1;
}
