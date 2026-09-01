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

#define CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_FEATURES
#define ASC_IGNORE_DEPRECATED_API

#include <asc/std/__functional/pointer_to_binary_function.h>
#include <iostream>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][pointer_to_binary_function] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static int add_int(int a, int b)
{
    return a + b;
}
static double mul_double(double a, double b)
{
    return a * b;
}
static float sub_float(float a, float b)
{
    return a - b;
}

int main()
{
    // Test pointer_to_binary_function constructor and operator() with int
    {
        asc::std::pointer_to_binary_function<int, int, int> f(&add_int);
        expect_eq("f(3, 4)", f(3, 4), 7);
        expect_eq("f(-2, 5)", f(-2, 5), 3);
        expect_eq("f(0, 0)", f(0, 0), 0);
    }

    // Test with double
    {
        asc::std::pointer_to_binary_function<double, double, double> f(&mul_double);
        expect_eq("f(2.5, 4.0)", f(2.5, 4.0), 10.0);
        expect_eq("f(1.5, 3.0)", f(1.5, 3.0), 4.5);
    }

    // Test with float
    {
        asc::std::pointer_to_binary_function<float, float, float> f(&sub_float);
        expect_eq("f(5.0f, 3.0f)", f(5.0f, 3.0f), 2.0f);
        expect_eq("f(1.0f, 4.0f)", f(1.0f, 4.0f), -3.0f);
    }

    // Test ptr_fun helper with int
    {
        auto f = asc::std::ptr_fun(add_int);
        expect_eq("ptr_fun(add_int)(10, 20)", f(10, 20), 30);
        expect_eq("ptr_fun(add_int)(-5, -3)", f(-5, -3), -8);
    }

    // Test ptr_fun helper with double
    {
        auto f = asc::std::ptr_fun(mul_double);
        expect_eq("ptr_fun(mul_double)(3.0, 7.0)", f(3.0, 7.0), 21.0);
    }

    // Test ptr_fun helper with float
    {
        auto f = asc::std::ptr_fun(sub_float);
        expect_eq("ptr_fun(sub_float)(10.0f, 3.0f)", f(10.0f, 3.0f), 7.0f);
    }

    // Test const operator() — call on const instance
    {
        const asc::std::pointer_to_binary_function<int, int, int> f(&add_int);
        expect_eq("const f(100, 200)", f(100, 200), 300);
    }

    // Test that ptr_fun returns correct type (assignable to pointer_to_binary_function)
    {
        asc::std::pointer_to_binary_function<int, int, int> f = asc::std::ptr_fun(add_int);
        expect_eq("assigned ptr_fun(add_int)(7, 8)", f(7, 8), 15);
    }

    // Test explicit constructor — must not allow implicit conversion
    {
        asc::std::pointer_to_binary_function<float, float, float> f(&sub_float);
        expect_eq("explicit ctor f(100.0f, 1.0f)", f(100.0f, 1.0f), 99.0f);
    }

    return g_failures == 0 ? 0 : 1;
}
