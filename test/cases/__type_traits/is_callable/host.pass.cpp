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

#include <asc/std/__type_traits/is_callable.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][is_callable] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][is_callable] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

// Test functions
int func_int_int([[maybe_unused]] int value)
{
    return 0;
}
// NOLINTNEXTLINE(readability/casting)
int func_int_int_noexcept([[maybe_unused]] int value) noexcept
{
    return 0;
}
void func_void()
{}
double func_double_float([[maybe_unused]] float value)
{
    return 0.0;
}
int func_add(int, int)
{
    return 0;
}

// Test functors
struct Functor {
    int operator()(int x) const
    {
        return x;
    }
};

struct NotCallable {};

struct NullaryFunctor {
    void operator()() const
    {}
};

int main()
{
    // === __is_callable_v tests ===

    // Simple function pointer with matching args - callable
    expect_true(
        "__is_callable_v<decltype(&func_int_int), int>", asc::std::__is_callable_v<decltype(&func_int_int), int>);

    // Simple function pointer with mismatched args - not callable
    expect_false("__is_callable_v<decltype(&func_int_int), const char*>",
        asc::std::__is_callable_v<decltype(&func_int_int), const char*>);

    // Function pointer with no args - callable with no args
    expect_true("__is_callable_v<decltype(&func_void)>", asc::std::__is_callable_v<decltype(&func_void)>);

    // Function pointer with no args - not callable with extra args
    expect_false("__is_callable_v<decltype(&func_void), int>", asc::std::__is_callable_v<decltype(&func_void), int>);

    // Multi-arg function - callable with matching args
    expect_true(
        "__is_callable_v<decltype(&func_add), int, int>", asc::std::__is_callable_v<decltype(&func_add), int, int>);

    // Multi-arg function - not callable with wrong number of args
    expect_false("__is_callable_v<decltype(&func_add), int>", asc::std::__is_callable_v<decltype(&func_add), int>);

    // Lambda callable
    {
        auto lambda = [](int x) -> int { return x + 1; };
        expect_true("__is_callable_v<decltype(lambda), int>", asc::std::__is_callable_v<decltype(lambda), int>);
        expect_false(
            "__is_callable_v<decltype(lambda), const char*>", asc::std::__is_callable_v<decltype(lambda), const char*>);
    }

    // Functor callable
    expect_true("__is_callable_v<Functor, int>", asc::std::__is_callable_v<Functor, int>);
    expect_false("__is_callable_v<Functor, const char*>", asc::std::__is_callable_v<Functor, const char*>);

    // Non-callable types
    expect_false("__is_callable_v<NotCallable, int>", asc::std::__is_callable_v<NotCallable, int>);
    expect_false("__is_callable_v<int, int>", asc::std::__is_callable_v<int, int>);

    // Nullary functor
    expect_true("__is_callable_v<NullaryFunctor>", asc::std::__is_callable_v<NullaryFunctor>);

    // === __is_callable struct (has ::value) ===
    expect_true("__is_callable<decltype(&func_int_int), int>::value",
        asc::std::__is_callable<decltype(&func_int_int), int>::value);
    expect_false("__is_callable<NotCallable, int>::value", asc::std::__is_callable<NotCallable, int>::value);

    // === __call_result_t type check ===
    expect_true("__call_result_t<decltype(&func_int_int), int> == int",
        std::is_same<asc::std::__call_result_t<decltype(&func_int_int), int>, int>::value);
    expect_true("__call_result_t<decltype(&func_double_float), float> == double",
        std::is_same<asc::std::__call_result_t<decltype(&func_double_float), float>, double>::value);

    // === __is_nothrow_callable_v tests ===

    // Noexcept function - nothrow callable
    expect_true("__is_nothrow_callable_v<decltype(&func_int_int_noexcept), int>",
        asc::std::__is_nothrow_callable_v<decltype(&func_int_int_noexcept), int>);

    // Non-noexcept function - not nothrow callable
    expect_false("__is_nothrow_callable_v<decltype(&func_int_int), int>",
        asc::std::__is_nothrow_callable_v<decltype(&func_int_int), int>);

    // Nothrow lambda
    {
        auto nl = [](int x) noexcept -> int { return x; };
        expect_true("__is_nothrow_callable_v<decltype(nl), int>", asc::std::__is_nothrow_callable_v<decltype(nl), int>);
    }

    // Throwing lambda
    {
        auto tl = [](int x) -> int { return x; };
        expect_false(
            "__is_nothrow_callable_v<decltype(tl), int>", asc::std::__is_nothrow_callable_v<decltype(tl), int>);
    }

    // Non-callable type - not nothrow callable
    expect_false("__is_nothrow_callable_v<NotCallable, int>", asc::std::__is_nothrow_callable_v<NotCallable, int>);

    // === __is_nothrow_callable struct (has ::value) ===
    expect_true("__is_nothrow_callable<decltype(&func_int_int_noexcept), int>::value",
        asc::std::__is_nothrow_callable<decltype(&func_int_int_noexcept), int>::value);
    expect_false("__is_nothrow_callable<decltype(&func_int_int), int>::value",
        asc::std::__is_nothrow_callable<decltype(&func_int_int), int>::value);

    return g_failures == 0 ? 0 : 1;
}
