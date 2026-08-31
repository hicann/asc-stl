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

#include <asc/std/__type_traits/is_compound.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][is_compound] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][is_compound] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

// Test types
enum E { e0, e1 };
enum class EC { a, b };
struct S {
    int x;
};
union U {
    int a;
    float b;
};
class C {
public:
    int m;
};

static void test_fundamental_types_compound_false()
{
    // --- Fundamental types: is_compound should be false ---
    expect_false("is_compound_v<void>", asc::std::is_compound_v<void>);
    expect_false("is_compound_v<nullptr_t>", asc::std::is_compound_v<nullptr_t>);
    expect_false("is_compound_v<bool>", asc::std::is_compound_v<bool>);
    expect_false("is_compound_v<char>", asc::std::is_compound_v<char>);
    expect_false("is_compound_v<signed char>", asc::std::is_compound_v<signed char>);
    expect_false("is_compound_v<unsigned char>", asc::std::is_compound_v<unsigned char>);
    expect_false("is_compound_v<wchar_t>", asc::std::is_compound_v<wchar_t>);
    expect_false("is_compound_v<short>", asc::std::is_compound_v<short>);
    expect_false("is_compound_v<unsigned short>", asc::std::is_compound_v<unsigned short>);
    expect_false("is_compound_v<int>", asc::std::is_compound_v<int>);
    expect_false("is_compound_v<unsigned int>", asc::std::is_compound_v<unsigned int>);
    expect_false("is_compound_v<long>", asc::std::is_compound_v<long>);
    expect_false("is_compound_v<unsigned long>", asc::std::is_compound_v<unsigned long>);
    expect_false("is_compound_v<long long>", asc::std::is_compound_v<long long>);
    expect_false("is_compound_v<unsigned long long>", asc::std::is_compound_v<unsigned long long>);
    expect_false("is_compound_v<float>", asc::std::is_compound_v<float>);
    expect_false("is_compound_v<double>", asc::std::is_compound_v<double>);
    expect_false("is_compound_v<long double>", asc::std::is_compound_v<long double>);
}

static void test_qualified_fundamental_types_still()
{
    // --- CV-qualified fundamental types: still fundamental, so is_compound false ---
    expect_false("is_compound_v<const int>", asc::std::is_compound_v<const int>);
    expect_false("is_compound_v<volatile float>", asc::std::is_compound_v<volatile float>);
    expect_false("is_compound_v<const volatile double>", asc::std::is_compound_v<const volatile double>);
}

static void test_compound_types_compound_true()
{
    // --- Compound types: is_compound should be true ---
    // Pointer types
    expect_true("is_compound_v<int*>", asc::std::is_compound_v<int*>);
    expect_true("is_compound_v<void*>", asc::std::is_compound_v<void*>);
    expect_true("is_compound_v<char*>", asc::std::is_compound_v<char*>);
    expect_true("is_compound_v<S*>", asc::std::is_compound_v<S*>);
}

static void test_reference_types()
{
    // Reference types
    expect_true("is_compound_v<int&>", asc::std::is_compound_v<int&>);
    expect_true("is_compound_v<const int&>", asc::std::is_compound_v<const int&>);
    expect_true("is_compound_v<int&&>", asc::std::is_compound_v<int&&>);
}

static void test_array_types()
{
    // Array types
    expect_true("is_compound_v<int[5]>", asc::std::is_compound_v<int[5]>);
    expect_true("is_compound_v<int[3][4]>", asc::std::is_compound_v<int[3][4]>);
    expect_true("is_compound_v<char[10]>", asc::std::is_compound_v<char[10]>);
}

static void test_enum_types()
{
    // Enum types
    expect_true("is_compound_v<E>", asc::std::is_compound_v<E>);
    expect_true("is_compound_v<EC>", asc::std::is_compound_v<EC>);
}

static void test_class_union_types()
{
    // Class/union types
    expect_true("is_compound_v<S>", asc::std::is_compound_v<S>);
    expect_true("is_compound_v<U>", asc::std::is_compound_v<U>);
    expect_true("is_compound_v<C>", asc::std::is_compound_v<C>);
}

static void test_function_pointer_types()
{
    // Function pointer types
    expect_true("is_compound_v<void(*)()>", asc::std::is_compound_v<void (*)()>);
    expect_true("is_compound_v<int(*)(int)>", asc::std::is_compound_v<int (*)(int)>);
}

static void test_member_pointer_types()
{
    // Member pointer types
    expect_true("is_compound_v<int S::*>", asc::std::is_compound_v<int S::*>);
    expect_true("is_compound_v<void (S::*)()>", asc::std::is_compound_v<void (S::*)()>);
}

static void test_also_struct_form_compound()
{
    // --- Also test the struct form (is_compound<T>::value) ---
    expect_false("is_compound<int>::value", asc::std::is_compound<int>::value);
    expect_true("is_compound<int*>::value", asc::std::is_compound<int*>::value);
    expect_false("is_compound<void>::value", asc::std::is_compound<void>::value);
    expect_true("is_compound<S>::value", asc::std::is_compound<S>::value);
}

static void test_inherits_bool_constant()
{
    // --- Verify it inherits from bool_constant ---
    expect_true("is_compound<int*>::value == true", asc::std::is_compound<int*>::value == true);
    expect_true("is_compound<int>::value == false", asc::std::is_compound<int>::value == false);
}

int main()
{
    test_fundamental_types_compound_false();
    test_qualified_fundamental_types_still();
    test_compound_types_compound_true();
    test_reference_types();
    test_array_types();
    test_enum_types();
    test_class_union_types();
    test_function_pointer_types();
    test_member_pointer_types();
    test_also_struct_form_compound();
    test_inherits_bool_constant();

    return g_failures == 0 ? 0 : 1;
}
