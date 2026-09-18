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

#ifndef CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_UNARY_BINARY_FUNCTION
#define CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_UNARY_BINARY_FUNCTION
#endif

#define ASC_IGNORE_DEPRECATED_API
#include <asc/std/__functional/binary_function.h>
#include <type_traits>
#include <iostream>

static int g_failures = 0;

static void check_type(const char* expr, bool result)
{
    std::cout << "[host][binary_function] " << expr << " = " << (result ? "true" : "false") << " (expected true) "
              << (result ? "OK" : "FAIL") << std::endl;
    if (!result)
        ++g_failures;
}

static void test_binary_function_struct_typedefs()
{
    // Test binary_function struct typedefs
    {
        using BF = asc::std::binary_function<int, double, bool>;
        check_type("is_same<binary_function<int,double,bool>::first_argument_type, int>",
            std::is_same<BF::first_argument_type, int>::value);
        check_type("is_same<binary_function<int,double,bool>::second_argument_type, double>",
            std::is_same<BF::second_argument_type, double>::value);
        check_type(
            "is_same<binary_function<int,double,bool>::result_type, bool>", std::is_same<BF::result_type, bool>::value);
    }
}

static void test_different_type_combination()
{
    // Test with different type combination
    {
        using BF = asc::std::binary_function<long, char, float>;
        check_type("is_same<binary_function<long,char,float>::first_argument_type, long>",
            std::is_same<BF::first_argument_type, long>::value);
        check_type("is_same<binary_function<long,char,float>::second_argument_type, char>",
            std::is_same<BF::second_argument_type, char>::value);
        check_type("is_same<binary_function<long,char,float>::result_type, float>",
            std::is_same<BF::result_type, float>::value);
    }
}

static void test_binary_function_alias_equals()
{
    // Test __binary_function alias equals binary_function when macro is defined
    {
        using BF = asc::std::binary_function<int, int, int>;
        using BFA = asc::std::__binary_function<int, int, int>;
        check_type(
            "is_same<__binary_function<int,int,int>, binary_function<int,int,int>>", std::is_same<BF, BFA>::value);
    }
}

static void test_using_binary_function_base()
{
    // Test using binary_function as a base class (primary use case)
    {
        struct my_binary_op : asc::std::binary_function<int, int, bool> {
            bool operator()(int a, int b) const
            {
                return a < b;
            }
        };

        check_type("is_same<my_binary_op::first_argument_type, int>",
            std::is_same<my_binary_op::first_argument_type, int>::value);
        check_type("is_same<my_binary_op::second_argument_type, int>",
            std::is_same<my_binary_op::second_argument_type, int>::value);
        check_type("is_same<my_binary_op::result_type, bool>", std::is_same<my_binary_op::result_type, bool>::value);

        my_binary_op op;
        bool result = op(3, 5);
        check_type("my_binary_op(3, 5) returns true (3 < 5)", result);
    }
}

static void test_binary_function_keep_layout()
{
    // Test __binary_function_keep_layout_base typedefs
    {
        using BFKL = asc::std::__binary_function_keep_layout_base<int, double, bool>;
#if CANN_ASC_STL_DETAIL_STD_VER <= 2017 || defined(CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX20_REMOVED_BINDER_TYPEDEFS)
        check_type("is_same<__binary_function_keep_layout_base<int,double,bool>::first_argument_type, int>",
            std::is_same<BFKL::first_argument_type, int>::value);
        check_type("is_same<__binary_function_keep_layout_base<int,double,bool>::second_argument_type, double>",
            std::is_same<BFKL::second_argument_type, double>::value);
        check_type("is_same<__binary_function_keep_layout_base<int,double,bool>::result_type, bool>",
            std::is_same<BFKL::result_type, bool>::value);
#else
        std::cout << "[host][binary_function] __binary_function_keep_layout_base typedefs skipped (C++20+ without "
                     "CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX20_REMOVED_BINDER_TYPEDEFS)"
                  << std::endl;
#endif
    }
}

int main()
{
    test_binary_function_struct_typedefs();
    test_different_type_combination();
    test_binary_function_alias_equals();
    test_using_binary_function_base();
    test_binary_function_keep_layout();

    return g_failures == 0 ? 0 : 1;
}
