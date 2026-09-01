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

#include <asc/std/__functional/mem_fun_ref.h>
#include <iostream>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][mem_fun_ref] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

struct Foo {
    int val;
    explicit Foo(int v) : val(v)
    {}
    int get()
    {
        return val;
    }
    int add(int x)
    {
        return val + x;
    }
    int get_const() const
    {
        return val;
    }
    int add_const(int x) const
    {
        return val + x;
    }
};

static void check_part1()
{
    // mem_fun_ref: no-arg non-const member function
    {
        Foo f(42);
        auto mfr = asc::std::mem_fun_ref(&Foo::get);
        expect_eq("mem_fun_ref(&Foo::get)(f)", mfr(f), 42);
    }

    // mem_fun_ref: one-arg non-const member function
    {
        Foo f(10);
        auto mfr1 = asc::std::mem_fun_ref(&Foo::add);
        expect_eq("mem_fun_ref(&Foo::add)(f, 5)", mfr1(f, 5), 15);
    }

    // const_mem_fun_ref: no-arg const member function
    {
        Foo f(99);
        auto cmfr = asc::std::mem_fun_ref(&Foo::get_const);
        expect_eq("mem_fun_ref(&Foo::get_const)(f)", cmfr(f), 99);
    }

    // const_mem_fun1_ref: one-arg const member function
    {
        Foo f(7);
        auto cmfr1 = asc::std::mem_fun_ref(&Foo::add_const);
        expect_eq("mem_fun_ref(&Foo::add_const)(f, 3)", cmfr1(f, 3), 10);
    }

    // mem_fun: no-arg non-const member function via pointer
    {
        Foo f(55);
        auto mf = asc::std::mem_fun(&Foo::get);
        expect_eq("mem_fun(&Foo::get)(&f)", mf(&f), 55);
    }

    // mem_fun1: one-arg non-const member function via pointer
    {
        Foo f(20);
        auto mf1 = asc::std::mem_fun(&Foo::add);
        expect_eq("mem_fun(&Foo::add)(&f, 8)", mf1(&f, 8), 28);
    }

    // const_mem_fun: no-arg const member function via pointer
    {
        Foo f(33);
        auto cmf = asc::std::mem_fun(&Foo::get_const);
        expect_eq("mem_fun(&Foo::get_const)(&f)", cmf(&f), 33);
    }

    // const_mem_fun1: one-arg const member function via pointer
    {
        Foo f(15);
        auto cmf1 = asc::std::mem_fun(&Foo::add_const);
        expect_eq("mem_fun(&Foo::add_const)(&f, 6)", cmf1(&f, 6), 21);
    }
}

static void check_part2()
{
    // Direct class usage: mem_fun_ref_t
    {
        Foo f(77);
        asc::std::mem_fun_ref_t<int, Foo> mfr(&Foo::get);
        expect_eq("mem_fun_ref_t<int,Foo>(&Foo::get)(f)", mfr(f), 77);
    }

    // Direct class usage: const_mem_fun_ref_t
    {
        Foo f(88);
        asc::std::const_mem_fun_ref_t<int, Foo> cmfr(&Foo::get_const);
        expect_eq("const_mem_fun_ref_t<int,Foo>(&Foo::get_const)(f)", cmfr(f), 88);
    }

    // Direct class usage: mem_fun1_ref_t
    {
        Foo f(50);
        asc::std::mem_fun1_ref_t<int, Foo, int> mfr1(&Foo::add);
        expect_eq("mem_fun1_ref_t<int,Foo,int>(&Foo::add)(f, 25)", mfr1(f, 25), 75);
    }

    // Direct class usage: const_mem_fun1_ref_t
    {
        Foo f(60);
        asc::std::const_mem_fun1_ref_t<int, Foo, int> cmfr1(&Foo::add_const);
        expect_eq("const_mem_fun1_ref_t<int,Foo,int>(&Foo::add_const)(f, 15)", cmfr1(f, 15), 75);
    }

    // Additional value coverage
    {
        Foo f(100);
        auto mfr = asc::std::mem_fun_ref(&Foo::get);
        expect_eq("mem_fun_ref(&Foo::get)(f=100)", mfr(f), 100);

        auto mfr1 = asc::std::mem_fun_ref(&Foo::add);
        expect_eq("mem_fun_ref(&Foo::add)(f=100, 50)", mfr1(f, 50), 150);
    }

#ifdef __GNUC__
#endif
}

int main()
{
    check_part1();
    check_part2();

    return g_failures == 0 ? 0 : 1;
}
