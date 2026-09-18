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

#define CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_FEATURES

#include <asc/std/__functional/binder2nd.h>
#include <iostream>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][binder2nd] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

struct add_op {
    using first_argument_type = int;
    using second_argument_type = int;
    using result_type = int;
    int operator()(int a, int b) const
    {
        return a + b;
    }
};

struct sub_op {
    using first_argument_type = int;
    using second_argument_type = int;
    using result_type = int;
    int operator()(int a, int b) const
    {
        return a - b;
    }
};

struct mul_op {
    using first_argument_type = int;
    using second_argument_type = int;
    using result_type = int;
    int operator()(int a, int b) const
    {
        return a * b;
    }
};

CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_PUSH

int main()
{
    {
        asc::std::binder2nd<add_op> f(add_op(), 10);
        expect_eq("binder2nd<add>(10)(5)", f(5), 15);
        expect_eq("binder2nd<add>(10)(0)", f(0), 10);
        expect_eq("binder2nd<add>(10)(-3)", f(-3), 7);
    }

    {
        auto f = asc::std::bind2nd(add_op(), 10);
        expect_eq("bind2nd(add,10)(5)", f(5), 15);
        expect_eq("bind2nd(add,10)(100)", f(100), 110);
    }

    {
        asc::std::binder2nd<sub_op> f(sub_op(), 3);
        expect_eq("binder2nd<sub>(3)(10)", f(10), 7);
        expect_eq("binder2nd<sub>(3)(3)", f(3), 0);
        expect_eq("binder2nd<sub>(3)(0)", f(0), -3);
    }

    {
        asc::std::binder2nd<mul_op> f(mul_op(), 5);
        expect_eq("binder2nd<mul>(5)(4)", f(4), 20);
        expect_eq("binder2nd<mul>(5)(0)", f(0), 0);
        expect_eq("binder2nd<mul>(5)(-2)", f(-2), -10);
    }

    {
        auto f = asc::std::bind2nd(mul_op(), 7);
        expect_eq("bind2nd(mul,7)(6)", f(6), 42);
        expect_eq("bind2nd(mul,7)(1)", f(1), 7);
    }

    {
        asc::std::binder2nd<add_op> f(add_op(), 100);
        const int val = 50;
        expect_eq("binder2nd<add>(100)(const 50)", f(val), 150);
    }

    {
        asc::std::binder2nd<add_op> f(add_op(), 1);
        int val = 42;
        expect_eq("binder2nd<add>(1)(42)", f(val), 43);
    }

    return g_failures == 0 ? 0 : 1;
}

CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_POP
