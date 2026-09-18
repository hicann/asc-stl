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

#define CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_UNARY_BINARY_FUNCTION
#define CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX20_REMOVED_BINDER_TYPEDEFS
#include <asc/std/__functional/unary_function.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][unary_function] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_PUSH

    // Test unary_function struct with basic types
    {
        using UF = asc::std::unary_function<int, double>;
        expect_true(
            "is_same<unary_function<int,double>::argument_type, int>", std::is_same<UF::argument_type, int>::value);
        expect_true(
            "is_same<unary_function<int,double>::result_type, double>", std::is_same<UF::result_type, double>::value);
    }

    // Test unary_function with char/long
    {
        using UF = asc::std::unary_function<char, long>;
        expect_true(
            "is_same<unary_function<char,long>::argument_type, char>", std::is_same<UF::argument_type, char>::value);
        expect_true(
            "is_same<unary_function<char,long>::result_type, long>", std::is_same<UF::result_type, long>::value);
    }

    // Test unary_function with pointer types
    {
        using UF = asc::std::unary_function<int*, bool>;
        expect_true(
            "is_same<unary_function<int*,bool>::argument_type, int*>", std::is_same<UF::argument_type, int*>::value);
        expect_true(
            "is_same<unary_function<int*,bool>::result_type, bool>", std::is_same<UF::result_type, bool>::value);
    }

    // Test __unary_function_keep_layout_base
    {
        using B = asc::std::__unary_function_keep_layout_base<float, int>;
        expect_true("is_same<__unary_function_keep_layout_base<float,int>::argument_type, float>",
            std::is_same<B::argument_type, float>::value);
        expect_true("is_same<__unary_function_keep_layout_base<float,int>::result_type, int>",
            std::is_same<B::result_type, int>::value);
    }

    // Test __unary_function alias (maps to unary_function when macro is defined)
    {
        using UF = asc::std::__unary_function<int, double>;
        expect_true(
            "is_same<__unary_function<int,double>::argument_type, int>", std::is_same<UF::argument_type, int>::value);
        expect_true(
            "is_same<__unary_function<int,double>::result_type, double>", std::is_same<UF::result_type, double>::value);
    }

    // Verify __unary_function maps to unary_function when macro is defined
    {
        expect_true("is_same<__unary_function<int,double>, unary_function<int,double>>",
            std::is_same<asc::std::__unary_function<int, double>, asc::std::unary_function<int, double>>::value);
    }

    CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_POP

    return g_failures == 0 ? 0 : 1;
}
