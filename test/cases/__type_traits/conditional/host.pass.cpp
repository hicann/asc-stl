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

#include <asc/std/__type_traits/conditional.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][conditional] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][conditional] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

static void test_conditional_true_type()
{
    // --- conditional<true, T, F>::type == T ---
    expect_true("conditional<true,int,double>::type is int",
        (std::is_same<asc::std::conditional<true, int, double>::type, int>::value));
    expect_true("conditional<true,char,long>::type is char",
        (std::is_same<asc::std::conditional<true, char, long>::type, char>::value));
    expect_true("conditional<true,float,int>::type is float",
        (std::is_same<asc::std::conditional<true, float, int>::type, float>::value));
}

static void test_conditional_false_type()
{
    // --- conditional<false, T, F>::type == F ---
    expect_true("conditional<false,int,double>::type is double",
        (std::is_same<asc::std::conditional<false, int, double>::type, double>::value));
    expect_true("conditional<false,char,long>::type is long",
        (std::is_same<asc::std::conditional<false, char, long>::type, long>::value));
    expect_true("conditional<false,float,int>::type is int",
        (std::is_same<asc::std::conditional<false, float, int>::type, int>::value));
}

static void test_conditional_alias()
{
    // --- conditional_t alias ---
    expect_true("conditional_t<true,int,double> is int",
        (std::is_same<asc::std::conditional_t<true, int, double>, int>::value));
    expect_true("conditional_t<false,int,double> is double",
        (std::is_same<asc::std::conditional_t<false, int, double>, double>::value));
    expect_true("conditional_t<true,unsigned,signed> is unsigned",
        (std::is_same<asc::std::conditional_t<true, unsigned, signed>, unsigned>::value));
    expect_true("conditional_t<false,unsigned,signed> is signed",
        (std::is_same<asc::std::conditional_t<false, unsigned, signed>, signed>::value));
}

static void test_same_type_both_branches()
{
    // --- same type on both branches ---
    expect_true("conditional<true,int,int>::type is int",
        (std::is_same<asc::std::conditional<true, int, int>::type, int>::value));
    expect_true("conditional<false,int,int>::type is int",
        (std::is_same<asc::std::conditional<false, int, int>::type, int>::value));
}

static void test_pointer_reference_types()
{
    // --- pointer / reference types ---
    expect_true("conditional<true,int*,double*>::type is int*",
        (std::is_same<asc::std::conditional<true, int*, double*>::type, int*>::value));
    expect_true("conditional<false,int*,double*>::type is double*",
        (std::is_same<asc::std::conditional<false, int*, double*>::type, double*>::value));
}

static void test_user_types()
{
    // --- user-defined types ---
    struct A {};
    struct B {};
    expect_true("conditional<true,A,B>::type is A", (std::is_same<asc::std::conditional<true, A, B>::type, A>::value));
    expect_true(
        "conditional<false,A,B>::type is B", (std::is_same<asc::std::conditional<false, A, B>::type, B>::value));
}

static void test_alias_internal_part_header()
{
    // --- _If alias (internal but part of header) ---
    expect_true("_If<true,int,double> is int", (std::is_same<asc::std::_If<true, int, double>, int>::value));
    expect_true("_If<false,int,double> is double", (std::is_same<asc::std::_If<false, int, double>, double>::value));
}

static void test_runtime_usage_instantiate_variable()
{
    // --- runtime usage: instantiate a variable of the selected type ---
    {
        using T = asc::std::conditional_t<true, int, double>;
        T val = 42;
        expect_true("conditional_t<true,int,double> variable holds 42", val == 42);
        expect_true("conditional_t<true,int,double> variable is int", (std::is_same<T, int>::value));
    }
    {
        using T = asc::std::conditional_t<false, int, double>;
        T val = 3.14;
        expect_false("conditional_t<false,int,double> variable == 3 (truncated check)", val == 3.0);
        expect_true("conditional_t<false,int,double> variable is double", (std::is_same<T, double>::value));
    }
}

static void test_sizeof_conditional_add_overhead()
{
    // --- sizeof check: conditional should not add overhead ---
    expect_true("sizeof(conditional_t<true,int,char>) == sizeof(int)",
        sizeof(asc::std::conditional_t<true, int, char>) == sizeof(int));
    expect_true("sizeof(conditional_t<false,int,char>) == sizeof(char)",
        sizeof(asc::std::conditional_t<false, int, char>) == sizeof(char));
}

int main()
{
    test_conditional_true_type();
    test_conditional_false_type();
    test_conditional_alias();
    test_same_type_both_branches();
    test_pointer_reference_types();
    test_user_types();
    test_alias_internal_part_header();
    test_runtime_usage_instantiate_variable();
    test_sizeof_conditional_add_overhead();

    return g_failures == 0 ? 0 : 1;
}
