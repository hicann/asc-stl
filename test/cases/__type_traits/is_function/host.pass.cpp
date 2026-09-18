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

#include <asc/std/__type_traits/is_function.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_function] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// Test function types
void free_func()
{}
int free_func2(int)  // NOLINT(readability/casting)
{
    return 0;
}
double free_func3(int, char)
{
    return 0.0;
}

struct Foo {
    void member_func()
    {}
    int member_func2(int) const
    {
        return 0;
    }
};

static void test_regular_function_types_true()
{
    // --- Regular function types: should be true ---
    expect_true("is_function_v<void()>", asc::std::is_function_v<void()>, true);
    expect_true("is_function_v<int(int)>", asc::std::is_function_v<int(int)>, true);
    expect_true("is_function_v<void(int, char)>", asc::std::is_function_v<void(int, char)>, true);
    expect_true("is_function_v<double(int,double)>", asc::std::is_function_v<double(int, double)>, true);
}

static void test_function_ref_qualifiers_still()
{
    // --- Function with cv/ref qualifiers: still function types ---
    expect_true("is_function_v<void() const>", asc::std::is_function_v<void() const>, true);
    expect_true("is_function_v<void() volatile>", asc::std::is_function_v<void() volatile>, true);
    expect_true("is_function_v<int(int) const>", asc::std::is_function_v<int(int) const>, true);
    expect_true("is_function_v<void() &>", asc::std::is_function_v<void()&>, true);
    expect_true("is_function_v<void() &&>", asc::std::is_function_v<void() &&>, true);
}

static void test_noexcept_function_types_still()
{
    // --- noexcept function types: still function types ---
    expect_true("is_function_v<void() noexcept>", asc::std::is_function_v<void() noexcept>, true);
    expect_true("is_function_v<int(int) noexcept>",
        asc::std::is_function_v<int(int) noexcept>,  // NOLINT(readability/casting)
        true);                                       // NOLINT(readability/casting)
}

static void test_function_pointers_function_types()
{
    // --- Function pointers: NOT function types ---
    expect_true("is_function_v<void(*)()>", asc::std::is_function_v<void (*)()>, false);
    expect_true("is_function_v<int(*)(int)>", asc::std::is_function_v<int (*)(int)>, false);
    expect_true("is_function_v<void(*)(int,char)>", asc::std::is_function_v<void (*)(int, char)>, false);
}

static void test_function_references_function_types()
{
    // --- Function references: NOT function types ---
    expect_true("is_function_v<void(&)()>", asc::std::is_function_v<void (&)()>, false);
    expect_true("is_function_v<int(&)(int)>", asc::std::is_function_v<int (&)(int)>, false);
}

static void test_member_function_pointers_function()
{
    // --- Member function pointers: NOT function types ---
    expect_true("is_function_v<void(Foo::*)()>", asc::std::is_function_v<void (Foo::*)()>, false);
    expect_true("is_function_v<int(Foo::*)(int) const>", asc::std::is_function_v<int (Foo::*)(int) const>, false);
}

static void test_fundamental_types_function_types()
{
    // --- Fundamental types: NOT function types ---
    expect_true("is_function_v<int>", asc::std::is_function_v<int>, false);
    expect_true("is_function_v<void>", asc::std::is_function_v<void>, false);
    expect_true("is_function_v<double>", asc::std::is_function_v<double>, false);
    expect_true("is_function_v<bool>", asc::std::is_function_v<bool>, false);
    expect_true("is_function_v<char>", asc::std::is_function_v<char>, false);
}

static void test_pointer_types_function_types()
{
    // --- Pointer types: NOT function types ---
    expect_true("is_function_v<int*>", asc::std::is_function_v<int*>, false);
    expect_true("is_function_v<void*>", asc::std::is_function_v<void*>, false);
}

static void test_reference_types_function_types()
{
    // --- Reference types: NOT function types ---
    expect_true("is_function_v<int&>", asc::std::is_function_v<int&>, false);
    expect_true("is_function_v<int&&>", asc::std::is_function_v<int&&>, false);
}

static void test_const_qualified_types_function()
{
    // --- const-qualified types: NOT function types ---
    expect_true("is_function_v<const int>", asc::std::is_function_v<const int>, false);
    expect_true("is_function_v<const double>", asc::std::is_function_v<const double>, false);
}

static void test_class_struct_types_function()
{
    // --- Class/struct types: NOT function types ---
    expect_true("is_function_v<Foo>", asc::std::is_function_v<Foo>, false);
}

static void test_array_types_function_types()
{
    // --- Array types: NOT function types ---
    expect_true("is_function_v<int[10]>", asc::std::is_function_v<int[10]>, false);
}

static void test_lambda_types_function_types()
{
    // --- Lambda types: NOT function types ---
    auto lambda = [](int) { return 0; };
    expect_true("is_function_v<decltype(lambda)>", asc::std::is_function_v<decltype(lambda)>, false);
}

static void test_function_form()
{
    // --- is_function<T>::value form ---
    expect_true("is_function<void()>::value", asc::std::is_function<void()>::value, true);
    expect_true("is_function<int>::value", asc::std::is_function<int>::value, false);
    expect_true("is_function<int(int)>::value", asc::std::is_function<int(int)>::value, true);
    expect_true("is_function<void(*)()>::value", asc::std::is_function<void (*)()>::value, false);
}

static void test_using_decltype_actual_free()
{
    // --- Using decltype on actual free functions ---
    // decltype(free_func) (unparenthesized) yields the function type void(), NOT a pointer.
    // Per [dcl.type.decltype]/1.2, an unparenthesized id-expression naming a function
    // gives the declared type (function type), so is_function_v correctly returns true.
    expect_true("is_function_v<decltype(free_func)>", asc::std::is_function_v<decltype(free_func)>, true);
    expect_true("is_function_v<decltype(&free_func)>", asc::std::is_function_v<decltype(&free_func)>, false);
    expect_true("is_function_v<decltype(free_func2)>", asc::std::is_function_v<decltype(free_func2)>, true);
}

static void test_static_assert_time()
{
    // --- static_assert checks (compile-time) ---
    static_assert(asc::std::is_function_v<void()>, "void() should be a function type");
    static_assert(!asc::std::is_function_v<int>, "int should not be a function type");
    static_assert(asc::std::is_function<int(int)>::value, "int(int) should be a function type");
    static_assert(!asc::std::is_function<void (*)()>::value, "void(*)() should not be a function type");
}

int main()
{
    test_regular_function_types_true();
    test_function_ref_qualifiers_still();
    test_noexcept_function_types_still();
    test_function_pointers_function_types();
    test_function_references_function_types();
    test_member_function_pointers_function();
    test_fundamental_types_function_types();
    test_pointer_types_function_types();
    test_reference_types_function_types();
    test_const_qualified_types_function();
    test_class_struct_types_function();
    test_array_types_function_types();
    test_lambda_types_function_types();
    test_function_form();
    test_using_decltype_actual_free();
    test_static_assert_time();

    return g_failures == 0 ? 0 : 1;
}
