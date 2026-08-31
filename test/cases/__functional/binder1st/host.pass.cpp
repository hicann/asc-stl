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

#include <asc/std/__functional/binder1st.h>
#include <iostream>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][binder1st] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

struct plus_int {
    using first_argument_type = int;
    using second_argument_type = int;
    using result_type = int;
    int operator()(int a, int b) const
    {
        return a + b;
    }
};

struct minus_int {
    using first_argument_type = int;
    using second_argument_type = int;
    using result_type = int;
    int operator()(int a, int b) const
    {
        return a - b;
    }
};

struct multiply_int {
    using first_argument_type = int;
    using second_argument_type = int;
    using result_type = int;
    int operator()(int a, int b) const
    {
        return a * b;
    }
};

int main()
{
    {
        plus_int op;
        asc::std::binder1st<plus_int> b(op, 10);
        expect_eq("binder1st<plus>(10)(5)", b(5), 15);
        expect_eq("binder1st<plus>(10)(0)", b(0), 10);
        expect_eq("binder1st<plus>(10)(-3)", b(-3), 7);
    }

    {
        minus_int op;
        asc::std::binder1st<minus_int> b(op, 10);
        expect_eq("binder1st<minus>(10)(5)", b(5), 5);
        expect_eq("binder1st<minus>(10)(0)", b(0), 10);
        expect_eq("binder1st<minus>(10)(15)", b(15), -5);
    }

    {
        plus_int op;
        auto b = asc::std::bind1st(op, 100);
        expect_eq("bind1st<plus>(100)(7)", b(7), 107);
        expect_eq("bind1st<plus>(100)(-50)", b(-50), 50);
    }

    {
        multiply_int op;
        auto b = asc::std::bind1st(op, 3);
        expect_eq("bind1st<multiply>(3)(4)", b(4), 12);
        expect_eq("bind1st<multiply>(3)(0)", b(0), 0);
    }

    {
        plus_int op;
        const asc::std::binder1st<plus_int> b(op, 5);
        const int x = 20;
        expect_eq("const binder1st<plus>(5)(const 20)", b(x), 25);
    }

    {
        plus_int op;
        asc::std::binder1st<plus_int> b(op, 5);
        int x = 20;
        expect_eq("binder1st<plus>(5)(int& 20)", b(x), 25);
    }

    return g_failures == 0 ? 0 : 1;
}

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
