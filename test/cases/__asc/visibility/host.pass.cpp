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

#include <asc/std/__asc/visibility.h>
#include <iostream>

static int g_failures = 0;

static void check_defined(const char* name, bool defined)
{
    std::cout << "[host][visibility] " << name << " is " << (defined ? "defined" : "NOT defined") << " "
              << (defined ? "OK" : "FAIL") << std::endl;
    if (!defined)
        ++g_failures;
}

// Functions decorated with each macro to verify they compile and are callable
CANN_ASC_STL_API int test_api_func(int x)
{
    return x + 1;
}
CANN_ASC_STL_DETAIL_HOST_DEVICE_API int test_hd_api_func(int x)
{
    return x + 2;
}
CANN_ASC_STL_HOST_API int test_host_api_func(int x)
{
    return x + 3;
}
CANN_ASC_STL_DEVICE_API int test_device_api_func(int x)
{
    return x + 4;
}
CANN_ASC_STL_DETAIL_NODEBUG_API int test_nodebug_api_func(int x)
{
    return x + 6;
}
CANN_ASC_STL_DETAIL_NODEBUG_HOST_API int test_nodebug_host_api_func(int x)
{
    return x + 7;
}
CANN_ASC_STL_DETAIL_NODEBUG_DEVICE_API int test_nodebug_device_api_func(int x)
{
    return x + 8;
}
CANN_ASC_STL_DETAIL_TRIVIAL_API int test_trivial_api_func(int x)
{
    return x + 9;
}
CANN_ASC_STL_DETAIL_TRIVIAL_HOST_API int test_trivial_host_api_func(int x)
{
    return x + 10;
}
CANN_ASC_STL_DETAIL_TRIVIAL_DEVICE_API int test_trivial_device_api_func(int x)
{
    return x + 11;
}
CANN_ASC_STL_DETAIL_PUBLIC_API int test_public_api_func(int x)
{
    return x + 12;
}
CANN_ASC_STL_DETAIL_PUBLIC_HOST_API int test_public_host_api_func(int x)
{
    return x + 13;
}
CANN_ASC_STL_DETAIL_PUBLIC_DEVICE_API int test_public_device_api_func(int x)
{
    return x + 14;
}
CANN_ASC_STL_DETAIL_FORCEINLINE int test_forceinline_func(int x)
{
    return x + 16;
}
CANN_ASC_STL_DETAIL_HIDE_FROM_ABI int test_hide_from_abi_func(int x)
{
    return x + 17;
}

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][visibility] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void test_expected()
{
    // --- Check that all expected macros are defined ---
#ifdef CANN_ASC_STL_DETAIL_AICORE_FN
    check_defined("CANN_ASC_STL_DETAIL_AICORE_FN", true);
#else
    check_defined("CANN_ASC_STL_DETAIL_AICORE_FN", false);
#endif
#ifdef CANN_ASC_STL_DETAIL_FORCEINLINE
    check_defined("CANN_ASC_STL_DETAIL_FORCEINLINE", true);
#else
    check_defined("CANN_ASC_STL_DETAIL_FORCEINLINE", false);
#endif
#ifdef CANN_ASC_STL_DETAIL_HIDE_FROM_ABI
    check_defined("CANN_ASC_STL_DETAIL_HIDE_FROM_ABI", true);
#else
    check_defined("CANN_ASC_STL_DETAIL_HIDE_FROM_ABI", false);
#endif
#ifdef CANN_ASC_STL_API
    check_defined("CANN_ASC_STL_API", true);
#else
    check_defined("CANN_ASC_STL_API", false);
#endif
#ifdef CANN_ASC_STL_DETAIL_HOST_DEVICE_API
    check_defined("CANN_ASC_STL_DETAIL_HOST_DEVICE_API", true);
#else
    check_defined("CANN_ASC_STL_DETAIL_HOST_DEVICE_API", false);
#endif
#ifdef CANN_ASC_STL_HOST_API
    check_defined("CANN_ASC_STL_HOST_API", true);
#else
    check_defined("CANN_ASC_STL_HOST_API", false);
#endif
#ifdef CANN_ASC_STL_DEVICE_API
    check_defined("CANN_ASC_STL_DEVICE_API", true);
#else
    check_defined("CANN_ASC_STL_DEVICE_API", false);
#endif
#ifdef CANN_ASC_STL_DETAIL_NODEBUG_API
    check_defined("CANN_ASC_STL_DETAIL_NODEBUG_API", true);
#else
    check_defined("CANN_ASC_STL_DETAIL_NODEBUG_API", false);
#endif
}

static void test_asc_nodebug_host_api()
{
#ifdef CANN_ASC_STL_DETAIL_NODEBUG_HOST_API
    check_defined("CANN_ASC_STL_DETAIL_NODEBUG_HOST_API", true);
#else
    check_defined("CANN_ASC_STL_DETAIL_NODEBUG_HOST_API", false);
#endif
#ifdef CANN_ASC_STL_DETAIL_NODEBUG_DEVICE_API
    check_defined("CANN_ASC_STL_DETAIL_NODEBUG_DEVICE_API", true);
#else
    check_defined("CANN_ASC_STL_DETAIL_NODEBUG_DEVICE_API", false);
#endif
#ifdef CANN_ASC_STL_DETAIL_TRIVIAL_API
    check_defined("CANN_ASC_STL_DETAIL_TRIVIAL_API", true);
#else
    check_defined("CANN_ASC_STL_DETAIL_TRIVIAL_API", false);
#endif
#ifdef CANN_ASC_STL_DETAIL_TRIVIAL_HOST_API
    check_defined("CANN_ASC_STL_DETAIL_TRIVIAL_HOST_API", true);
#else
    check_defined("CANN_ASC_STL_DETAIL_TRIVIAL_HOST_API", false);
#endif
#ifdef CANN_ASC_STL_DETAIL_TRIVIAL_DEVICE_API
    check_defined("CANN_ASC_STL_DETAIL_TRIVIAL_DEVICE_API", true);
#else
    check_defined("CANN_ASC_STL_DETAIL_TRIVIAL_DEVICE_API", false);
#endif
#ifdef CANN_ASC_STL_DETAIL_PUBLIC_API
    check_defined("CANN_ASC_STL_DETAIL_PUBLIC_API", true);
#else
    check_defined("CANN_ASC_STL_DETAIL_PUBLIC_API", false);
#endif
#ifdef CANN_ASC_STL_DETAIL_PUBLIC_HOST_API
    check_defined("CANN_ASC_STL_DETAIL_PUBLIC_HOST_API", true);
#else
    check_defined("CANN_ASC_STL_DETAIL_PUBLIC_HOST_API", false);
#endif
#ifdef CANN_ASC_STL_DETAIL_PUBLIC_DEVICE_API
    check_defined("CANN_ASC_STL_DETAIL_PUBLIC_DEVICE_API", true);
#else
    check_defined("CANN_ASC_STL_DETAIL_PUBLIC_DEVICE_API", false);
#endif
}

static void test_foreign_abi_macro_absent()
{
#ifdef _LIBCUDACXX_HIDE_FROM_ABI
    std::cout << "[host][visibility] _LIBCUDACXX_HIDE_FROM_ABI is unexpectedly defined FAIL" << std::endl;
    ++g_failures;
#else
    std::cout << "[host][visibility] _LIBCUDACXX_HIDE_FROM_ABI is not exported OK" << std::endl;
#endif
}

static void test_functions_decorated_callable_correct()
{
    // --- Verify functions decorated with macros are callable and correct ---
    expect_eq("test_api_func(0)", test_api_func(0), 1);
    expect_eq("test_hd_api_func(0)", test_hd_api_func(0), 2);
    expect_eq("test_host_api_func(0)", test_host_api_func(0), 3);
    expect_eq("test_device_api_func(0)", test_device_api_func(0), 4);
    expect_eq("test_nodebug_api_func(0)", test_nodebug_api_func(0), 6);
    expect_eq("test_nodebug_host_api_func(0)", test_nodebug_host_api_func(0), 7);
    expect_eq("test_nodebug_device_api_func(0)", test_nodebug_device_api_func(0), 8);
    expect_eq("test_trivial_api_func(0)", test_trivial_api_func(0), 9);
    expect_eq("test_trivial_host_api_func(0)", test_trivial_host_api_func(0), 10);
    expect_eq("test_trivial_device_api_func(0)", test_trivial_device_api_func(0), 11);
    expect_eq("test_public_api_func(0)", test_public_api_func(0), 12);
    expect_eq("test_public_host_api_func(0)", test_public_host_api_func(0), 13);
    expect_eq("test_public_device_api_func(0)", test_public_device_api_func(0), 14);
    expect_eq("test_forceinline_func(0)", test_forceinline_func(0), 16);
    expect_eq("test_hide_from_abi_func(0)", test_hide_from_abi_func(0), 17);
}

int main()
{
    test_expected();
    test_asc_nodebug_host_api();
    test_foreign_abi_macro_absent();
    test_functions_decorated_callable_correct();

    return g_failures == 0 ? 0 : 1;
}
