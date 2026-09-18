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

#include <asc/std/__type_traits/dependent_type.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][dependent_type] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

// A simple type to use as the base for __dependent_type
struct Foo {
    static constexpr int value = 42;
};

// A type with a nested type, to test SFINAE-dependent instantiation
struct Bar {
    using type = int;
    static constexpr double pi = 3.14;
};

static void test_dependent_type_derives()
{
    // Test 1: __dependent_type derives from _Tp
    {
        using DT = asc::std::__dependent_type<Foo, true>;
        expect_true("std::is_base_of_v<Foo, __dependent_type<Foo,true>>", std::is_base_of_v<Foo, DT>);
    }
}

static void test_dependent_type_bool_true()
{
    // Test 2: __dependent_type with bool=true still has the members of _Tp
    {
        using DT = asc::std::__dependent_type<Foo, true>;
        expect_true("__dependent_type<Foo,true>::value == 42", DT::value == 42);
    }
}

static void test_dependent_type_bool_false()
{
    // Test 3: __dependent_type with bool=false also derives from _Tp
    {
        using DT = asc::std::__dependent_type<Foo, false>;
        expect_true("std::is_base_of_v<Foo, __dependent_type<Foo,false>>", std::is_base_of_v<Foo, DT>);
    }
}

static void test_dependent_type_bool_false_2()
{
    // Test 4: __dependent_type with bool=false also has members of _Tp
    {
        using DT = asc::std::__dependent_type<Foo, false>;
        expect_true("__dependent_type<Foo,false>::value == 42", DT::value == 42);
    }
}

static void test_dependent_type_preserves_nested()
{
    // Test 5: __dependent_type preserves nested types of _Tp
    {
        using DT = asc::std::__dependent_type<Bar, true>;
        expect_true("std::is_same_v<__dependent_type<Bar,true>::type, int>", std::is_same_v<DT::type, int>);
    }
}

static void test_dependent_type_preserves_static()
{
    // Test 6: __dependent_type preserves static members of _Tp
    {
        using DT = asc::std::__dependent_type<Bar, false>;
        expect_true("__dependent_type<Bar,false>::pi == 3.14", DT::pi == 3.14);
    }
}

static void test_dependent_type_itself_complete()
{
    // Test 7: __dependent_type is itself a complete type
    {
        using DT = asc::std::__dependent_type<Foo, true>;
        expect_true("std::is_class_v<__dependent_type<Foo,true>>", std::is_class_v<DT>);
    }
}

static void test_different_bool_template_args()
{
    // Test 8: Different bool template args produce different types
    {
        using DT_true = asc::std::__dependent_type<Foo, true>;
        using DT_false = asc::std::__dependent_type<Foo, false>;
        expect_true("!std::is_same_v<__dependent_type<Foo,true>, __dependent_type<Foo,false>>",
            !std::is_same_v<DT_true, DT_false>);
    }
}

static void test_dependent_type_empty_struct()
{
    // Test 9: __dependent_type with an empty struct
    {
        struct Empty {};
        using DT = asc::std::__dependent_type<Empty, true>;
        expect_true("std::is_empty_v<__dependent_type<Empty,true>>", std::is_empty_v<DT>);
    }
}

static void test_dependent_type_default_constructed()
{
    // Test 10: __dependent_type can be default-constructed when _Tp can
    {
        using DT = asc::std::__dependent_type<Foo, true>;
        DT obj;
        (void)obj;
        expect_true("__dependent_type<Foo,true> default-constructible", std::is_default_constructible_v<DT>);
    }
}

int main()
{
    test_dependent_type_derives();
    test_dependent_type_bool_true();
    test_dependent_type_bool_false();
    test_dependent_type_bool_false_2();
    test_dependent_type_preserves_nested();
    test_dependent_type_preserves_static();
    test_dependent_type_itself_complete();
    test_different_bool_template_args();
    test_dependent_type_empty_struct();
    test_dependent_type_default_constructed();

    return g_failures == 0 ? 0 : 1;
}
