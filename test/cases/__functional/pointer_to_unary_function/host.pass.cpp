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

#ifndef CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_FEATURES
#define CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_FEATURES
#define ASC_IGNORE_DEPRECATED_API
#endif

#include <asc/std/__functional/pointer_to_unary_function.h>
#include <iostream>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][pointer_to_unary_function] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static int double_value(int x)
{
    return x * 2;
}
static float negate_value(float x)
{
    return -x;
}
static double int_to_double(int x)
{
    return x * 1.5;
}

int main()
{
    // Test pointer_to_unary_function constructor and operator() with int->int
    {
        asc::std::pointer_to_unary_function<int, int> f(double_value);
        expect_eq("f(5)", f(5), 10);
        expect_eq("f(0)", f(0), 0);
        expect_eq("f(-3)", f(-3), -6);
    }

    // Test pointer_to_unary_function with float->float
    {
        asc::std::pointer_to_unary_function<float, float> f(negate_value);
        expect_eq("f(3.5f)", f(3.5f), -3.5f);
        expect_eq("f(-2.0f)", f(-2.0f), 2.0f);
    }

    // Test pointer_to_unary_function with int->double (different arg/result types)
    {
        asc::std::pointer_to_unary_function<int, double> f(int_to_double);
        expect_eq("f(4)", f(4), 6.0);
    }

    // Test const correctness: operator() is declared const
    {
        const asc::std::pointer_to_unary_function<int, int> f(double_value);
        expect_eq("const f(5)", f(5), 10);
    }

    // Test ptr_fun helper with int->int
    {
        auto f = asc::std::ptr_fun(double_value);
        expect_eq("ptr_fun(double_value)(7)", f(7), 14);
    }

    // Test ptr_fun helper with float->float
    {
        auto f = asc::std::ptr_fun(negate_value);
        expect_eq("ptr_fun(negate_value)(4.5f)", f(4.5f), -4.5f);
    }

    return g_failures == 0 ? 0 : 1;
}
