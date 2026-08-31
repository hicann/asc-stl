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

#include <asc/std/__internal/thread_api.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][thread_api] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][thread_api] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

static void expect_eq_int(const char* expr, int got, int expected)
{
    bool ok = (got == expected);
    std::cout << "[host][thread_api] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void test_stdcpp_threads_must_equal()
{
    // __STDCPP_THREADS__ must be defined and equal to 1
#ifdef __STDCPP_THREADS__
    expect_eq_int("__STDCPP_THREADS__", __STDCPP_THREADS__, 1);
#else
    expect_true("__STDCPP_THREADS__ is defined", false);
#endif
}

static void test_asc_must_define_accl()
{
    // ASC must NOT define CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_CUDA
    expect_false("CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_CUDA is not defined",
#ifdef CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_CUDA
        true
#else
        false
#endif
    );  // NOLINT(whitespace/parens)
}

static void test_exactly_one_thread_api()
{
    // Report which thread API backend is selected on host
#ifdef CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_PTHREAD
    std::cout << "[host][thread_api] CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_PTHREAD is defined OK" << std::endl;
#endif
#ifdef CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_WIN32
    std::cout << "[host][thread_api] CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_WIN32 is defined OK" << std::endl;
#endif
#ifdef CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_EXTERNAL
    std::cout << "[host][thread_api] CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_EXTERNAL is defined OK" << std::endl;
#endif
#ifdef CANN_ASC_STL_DETAIL_ACCL_UNSUPPORTED_THREAD_API
    std::cout << "[host][thread_api] CANN_ASC_STL_DETAIL_ACCL_UNSUPPORTED_THREAD_API is defined OK" << std::endl;
#endif
}

static void test_supported_host_platform_exactly()
{
    // On a supported host platform, exactly one backend should be selected
    int api_count = 0;
#ifdef CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_PTHREAD
    ++api_count;
#endif
#ifdef CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_WIN32
    ++api_count;
#endif
#ifdef CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_EXTERNAL
    ++api_count;
#endif
#ifdef CANN_ASC_STL_DETAIL_ACCL_UNSUPPORTED_THREAD_API
    ++api_count;
#endif
    expect_true("exactly one thread API backend selected", api_count == 1);
}

static void test_platform_specific()
{
    // Platform-specific checks
#if defined(__linux__) || defined(__APPLE__)
    expect_true("CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_PTHREAD defined on Linux/Apple",
#ifdef CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_PTHREAD
        true
#else
        false
#endif
    );  // NOLINT(whitespace/parens)
#elif defined(_WIN32)
    expect_true("CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_WIN32 defined on Windows",
#ifdef CANN_ASC_STL_DETAIL_ACCL_HAS_THREAD_API_WIN32
        true
#else
        false
#endif
    );  // NOLINT(whitespace/parens)
#endif
}

int main()
{
    test_stdcpp_threads_must_equal();
    test_asc_must_define_accl();
    test_exactly_one_thread_api();
    test_supported_host_platform_exactly();
    test_platform_specific();

    return g_failures == 0 ? 0 : 1;
}
