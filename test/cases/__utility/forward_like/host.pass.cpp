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

#include <asc/std/__utility/forward_like.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][forward_like] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][forward_like] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void check_part1()
{
    // === Type correctness: forward_like<T>(U) -> _ForwardLike<T, U> ===
    // _ForwardLike<T, U> = __copy_cvref_t<T&&, remove_reference_t<U>>
    // i.e. copy the cvref qualifiers of T&& onto remove_reference_t<U>

    // T = int (rvalue), U = int& -> int&&
    {
        int x = 42;
        using R = decltype(asc::std::forward_like<int>(x));
        expect_true("forward_like<int>(int&) -> int&&", std::is_same_v<R, int&&>);
    }

    // T = int& (lvalue), U = int& -> int&
    {
        int x = 42;
        using R = decltype(asc::std::forward_like<int&>(x));
        expect_true("forward_like<int&>(int&) -> int&", std::is_same_v<R, int&>);
    }

    // T = const int& (lvalue), U = int& -> const int&
    {
        int x = 42;
        using R = decltype(asc::std::forward_like<const int&>(x));
        expect_true("forward_like<const int&>(int&) -> const int&", std::is_same_v<R, const int&>);
    }

    // T = int&& (rvalue), U = int& -> int&&
    {
        int x = 42;
        using R = decltype(asc::std::forward_like<int&&>(x));
        expect_true("forward_like<int&&>(int&) -> int&&", std::is_same_v<R, int&&>);
    }

    // T = const int&& (rvalue), U = int& -> const int&&
    {
        int x = 42;
        using R = decltype(asc::std::forward_like<const int&&>(x));
        expect_true("forward_like<const int&&>(int&) -> const int&&", std::is_same_v<R, const int&&>);
    }

    // T = volatile int& (lvalue), U = int& -> volatile int&
    {
        int x = 42;
        using R = decltype(asc::std::forward_like<volatile int&>(x));
        expect_true("forward_like<volatile int&>(int&) -> volatile int&", std::is_same_v<R, volatile int&>);
    }

    // T = const volatile int& (lvalue), U = int& -> const volatile int&
    {
        int x = 42;
        using R = decltype(asc::std::forward_like<const volatile int&>(x));
        expect_true(
            "forward_like<const volatile int&>(int&) -> const volatile int&", std::is_same_v<R, const volatile int&>);
    }

    // T = int (rvalue), U = int (rvalue arg) -> int&&
    {
        using R = decltype(asc::std::forward_like<int>(42));
        expect_true("forward_like<int>(42) -> int&&", std::is_same_v<R, int&&>);
    }
}

static void check_part2()
{
    // T = int (rvalue), U = const int& -> const int&& (cv from U preserved)
    {
        const int x = 42;
        using R = decltype(asc::std::forward_like<int>(x));
        expect_true("forward_like<int>(const int&) -> const int&&", std::is_same_v<R, const int&&>);
    }

    // T = const int& (lvalue), U = const int& -> const int&
    {
        const int x = 42;
        using R = decltype(asc::std::forward_like<const int&>(x));
        expect_true("forward_like<const int&>(const int&) -> const int&", std::is_same_v<R, const int&>);
    }

    // === Value correctness ===

    {
        int x = 100;
        auto&& r = asc::std::forward_like<int>(x);
        expect_eq("forward_like<int>(100)", r, 100);
    }

    {
        int x = 200;
        auto&& r = asc::std::forward_like<int&>(x);
        expect_eq("forward_like<int&>(200)", r, 200);
    }

    {
        int x = 300;
        auto&& r = asc::std::forward_like<const int&>(x);
        expect_eq("forward_like<const int&>(300)", r, 300);
    }

    {
        float f = 1.5f;
        auto&& r = asc::std::forward_like<float>(f);
        expect_eq("forward_like<float>(1.5f)", r, 1.5f);
    }

    // Different source type: forward_like<int>(double) -> double&&
    {
        double d = 3.14;
        using R = decltype(asc::std::forward_like<int>(d));
        expect_true("forward_like<int>(double) -> double&&", std::is_same_v<R, double&&>);
        auto&& r = asc::std::forward_like<int>(d);
        expect_eq("forward_like<int>(3.14) value", r, 3.14);
    }
}

static void check_part3()
{
    // === noexcept ===
    {
        int x = 42;
        expect_true("forward_like<int>(int&) is noexcept", noexcept(asc::std::forward_like<int>(x)));
    }

    // === Address preservation for lvalue T ===
    {
        int x = 999;
        auto&& r = asc::std::forward_like<int&>(x);
        expect_true("&forward_like<int&>(x) == &x", &r == &x);
    }
}

int main()
{
    check_part1();
    check_part2();
    check_part3();

    return g_failures == 0 ? 0 : 1;
}
