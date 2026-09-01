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

#include <asc/std/__utility/as_const.h>
#include <iostream>
#include <type_traits>
#include <utility>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][as_const] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][as_const] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

// SFINAE helper: can as_const be called with T?
template <typename T, typename = void>
struct can_call_as_const : std::false_type {};

template <typename T>
struct can_call_as_const<T, std::void_t<decltype(asc::std::as_const(std::declval<T>()))>> : std::true_type {};

static void check_part1()
{
    // ── Basic value: as_const returns a const reference to the same value ──
    {
        int x = 42;
        const int& cr = asc::std::as_const(x);
        expect_eq("as_const(int 42)", cr, 42);
    }
    {
        float f = 3.14f;
        const float& cr = asc::std::as_const(f);
        expect_eq("as_const(float 3.14)", cr, 3.14f);
    }
    {
        double d = 2.718;
        const double& cr = asc::std::as_const(d);
        expect_eq("as_const(double 2.718)", cr, 2.718);
    }

    // ── Address identity: as_const returns a reference to the same object ──
    {
        int x = 10;
        expect_true("&as_const(x) == &x", &asc::std::as_const(x) == &x);
    }
    {
        float f = 1.5f;
        expect_true("&as_const(f) == &f", &asc::std::as_const(f) == &f);
    }

    // ── Type check: decltype(as_const(T&)) is const T& ──
    {
        int x = 5;
        static_assert(
            std::is_same_v<decltype(asc::std::as_const(x)), const int&>, "as_const(int&) must return const int&");
        expect_true("is_same<as_const(int&), const int&>", true);
    }
    {
        float f = 1.0f;
        static_assert(
            std::is_same_v<decltype(asc::std::as_const(f)), const float&>, "as_const(float&) must return const float&");
        expect_true("is_same<as_const(float&), const float&>", true);
    }
    {
        static_assert(std::is_const_v<std::remove_reference_t<decltype(asc::std::as_const(std::declval<int&>()))>>,
            "remove_reference_t<as_const> must be const-qualified");
        expect_true("is_const<remove_reference_t<as_const(int&)>>", true);
    }
}

static void check_part2()
{
    // ── Already-const object: as_const on const T& still works ──
    {
        const int cx = 99;
        const int& cr = asc::std::as_const(cx);
        expect_eq("as_const(const int 99)", cr, 99);
        expect_true("&as_const(cx) == &cx", &asc::std::as_const(cx) == &cx);
    }

    // ── Mutating original is visible through the const reference ──
    {
        int x = 100;
        const int& cr = asc::std::as_const(x);
        x = 200;
        expect_eq("as_const reflects mutation (200)", cr, 200);
    }

    // ── noexcept guarantee ──
    {
        static_assert(noexcept(asc::std::as_const(std::declval<int&>())), "as_const must be noexcept");
        expect_true("noexcept(as_const(int&))", true);
    }

    // ── Rvalue overload is deleted (compile-time check via SFINAE) ──
    {
        static_assert(can_call_as_const<int&>::value, "as_const(int&) should be callable");
        static_assert(!can_call_as_const<int>::value, "as_const(int&&) must be deleted");
        static_assert(!can_call_as_const<double>::value, "as_const(double&&) must be deleted");
        expect_true("as_const(rvalue) is deleted", true);
    }

    // ── Works with char type ──
    {
        char c = 'A';
        const char& cr = asc::std::as_const(c);
        expect_eq("as_const(char 'A')", static_cast<int>(cr), static_cast<int>('A'));
    }

    // ── [[nodiscard]]: result is usable (compile-time check that it compiles) ──
    {
        int x = 7;
        int y = asc::std::as_const(x);  // implicit conversion const int& -> int
        expect_eq("as_const(int 7) assigned to int", y, 7);
    }
}

int main()
{
    check_part1();
    check_part2();

    return g_failures == 0 ? 0 : 1;
}
