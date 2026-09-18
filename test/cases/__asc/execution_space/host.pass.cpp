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

#include <asc/std/__asc/execution_space.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][execution_space] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_eq_int(const char* expr, int got, int expected)
{
    bool ok = (got == expected);
    std::cout << "[host][execution_space] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// --- Test CANN_ASC_STL_HOST on a free function ---
CANN_ASC_STL_HOST int host_fn()
{
    return 1;
}

// --- Test CANN_ASC_STL_HOST_DEVICE on a free function ---
CANN_ASC_STL_HOST_DEVICE int host_device_fn()
{
    return 2;
}

// --- Test CANN_ASC_STL_DETAIL_TARGET_CONSTEXPR on a free function ---
CANN_ASC_STL_DETAIL_TARGET_CONSTEXPR int square(int n)
{
    return n * n;
}

static void test_asc_host_expand_nothing()
{
    // --- CANN_ASC_STL_HOST should be defined and expand to nothing on host ---
    {
        int CANN_ASC_STL_HOST x = 42;
        expect_eq_int("int CANN_ASC_STL_HOST x = 42", x, 42);
    }
}

static void test_asc_device_expand_nothing()
{
    // --- CANN_ASC_STL_DEVICE should be defined and expand to nothing on host ---
    {
        int CANN_ASC_STL_DEVICE y = 99;
        expect_eq_int("int CANN_ASC_STL_DEVICE y = 99", y, 99);
    }
}

static void test_asc_host_device_expand()
{
    // --- CANN_ASC_STL_HOST_DEVICE should be defined and expand to nothing on host ---
    {
        int CANN_ASC_STL_HOST_DEVICE z = 7;
        expect_eq_int("int CANN_ASC_STL_HOST_DEVICE z = 7", z, 7);
    }
}

static void test_asc_global_variable_expand()
{
    // --- CANN_ASC_STL_DETAIL_GLOBAL_VARIABLE should be defined and expand to nothing ---
    {
        int CANN_ASC_STL_DETAIL_GLOBAL_VARIABLE g = 33;
        expect_eq_int("int CANN_ASC_STL_DETAIL_GLOBAL_VARIABLE g = 33", g, 33);
    }
}

static void test_asc_target_constexpr_expand()
{
    // --- CANN_ASC_STL_DETAIL_TARGET_CONSTEXPR should expand to constexpr ---
    {
        CANN_ASC_STL_DETAIL_TARGET_CONSTEXPR int val = 100;
        expect_eq_int("CANN_ASC_STL_DETAIL_TARGET_CONSTEXPR int val", val, 100);
    }
}

static void test_asc_host_function()
{
    // --- CANN_ASC_STL_HOST on a function ---
    expect_eq_int("CANN_ASC_STL_HOST function returns", host_fn(), 1);
}

static void test_asc_host_device_function()
{
    // --- CANN_ASC_STL_HOST_DEVICE on a function ---
    expect_eq_int("CANN_ASC_STL_HOST_DEVICE function returns", host_device_fn(), 2);
}

static void test_asc_target_constexpr_function()
{
    // --- CANN_ASC_STL_DETAIL_TARGET_CONSTEXPR on a function ---
    expect_eq_int("CANN_ASC_STL_DETAIL_TARGET_CONSTEXPR square(5)", square(5), 25);
    expect_eq_int("CANN_ASC_STL_DETAIL_TARGET_CONSTEXPR square(0)", square(0), 0);
    expect_eq_int("CANN_ASC_STL_DETAIL_TARGET_CONSTEXPR square(-3)", square(-3), 9);
}

static void test_asc_known_asc_arch()
{
    // --- CANN_ASC_STL_DETAIL_KNOWN_ASC_ARCH_LIST should be defined ---
    {
#ifdef CANN_ASC_STL_DETAIL_KNOWN_ASC_ARCH_LIST
        expect_true("CANN_ASC_STL_DETAIL_KNOWN_ASC_ARCH_LIST is defined", true);
#else
        expect_true("CANN_ASC_STL_DETAIL_KNOWN_ASC_ARCH_LIST is defined", false);
#endif
    }
}

static void test_asc_known_asc_arch_2()
{
    // --- CANN_ASC_STL_DETAIL_KNOWN_ASC_ARCH_SPECIFIC_LIST should be defined ---
    {
#ifdef CANN_ASC_STL_DETAIL_KNOWN_ASC_ARCH_SPECIFIC_LIST
        expect_true("CANN_ASC_STL_DETAIL_KNOWN_ASC_ARCH_SPECIFIC_LIST is defined", true);
#else
        expect_true("CANN_ASC_STL_DETAIL_KNOWN_ASC_ARCH_SPECIFIC_LIST is defined", false);
#endif
    }
}

static void test_header_guard()
{
    // --- Header guard should be defined ---
    {
#ifdef CANN_ASC_STL_STD_DETAIL_EXECUTION_SPACE_H
        expect_true("header guard CANN_ASC_STL_STD_DETAIL_EXECUTION_SPACE_H is defined", true);
#else
        expect_true("header guard CANN_ASC_STL_STD_DETAIL_EXECUTION_SPACE_H is defined", false);
#endif
    }
}

int main()
{
    test_asc_host_expand_nothing();
    test_asc_device_expand_nothing();
    test_asc_host_device_expand();
    test_asc_global_variable_expand();
    test_asc_target_constexpr_expand();
    test_asc_host_function();
    test_asc_host_device_function();
    test_asc_target_constexpr_function();
    test_asc_known_asc_arch();
    test_asc_known_asc_arch_2();
    test_header_guard();

    return g_failures == 0 ? 0 : 1;
}
