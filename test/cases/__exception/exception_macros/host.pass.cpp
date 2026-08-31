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

#include <asc/std/__exception/exception_macros.h>
#include <iostream>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][exception_macros] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][exception_macros] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

constexpr int exception_value()
{
    return 42;
}

struct ExceptionBase {
    int value = exception_value();

    [[nodiscard]] static const char* what() noexcept
    {
        return "ExceptionBase";
    }
};

struct Exception : ExceptionBase {};

struct HostException {
    int value;

    HostException() : value(exception_value())
    {}
};

#if CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS()
static void test_exception_case_1()
{
    // 1. test catch by value
    CANN_ASC_STL_DETAIL_ACCL_TRY
    {
        CANN_ASC_STL_DETAIL_ACCL_THROW(Exception);
    }
    CANN_ASC_STL_DETAIL_ACCL_CATCH(Exception e)
    {
        expect_eq("catch by value: e.value", e.value, exception_value());
        expect_true("catch by value: reached", true);
    }
    CANN_ASC_STL_DETAIL_ACCL_CATCH(ExceptionBase e)
    {
        expect_eq("catch by value (base): e.value", e.value, exception_value());
        expect_true("catch by value (base): should not reach", false);
    }
    CANN_ASC_STL_DETAIL_ACCL_CATCH_ALL
    {
        expect_true("catch by value (all): should not reach", false);
    }
}

static void test_exception_case_2()
{
    // 2. test catch by lvalue reference
    CANN_ASC_STL_DETAIL_ACCL_TRY
    {
        CANN_ASC_STL_DETAIL_ACCL_THROW(Exception);
    }
    CANN_ASC_STL_DETAIL_ACCL_CATCH(Exception & e)
    {
        expect_eq("catch by lref: e.value", e.value, exception_value());
        expect_true("catch by lref: reached", true);
    }
    CANN_ASC_STL_DETAIL_ACCL_CATCH(ExceptionBase & e)
    {
        expect_eq("catch by lref (base): e.value", e.value, exception_value());
        expect_true("catch by lref (base): should not reach", false);
    }
    CANN_ASC_STL_DETAIL_ACCL_CATCH_ALL
    {
        expect_true("catch by lref (all): should not reach", false);
    }
}

static void test_exception_case_3()
{
    // 3. test catch by const lvalue reference
    CANN_ASC_STL_DETAIL_ACCL_TRY
    {
        CANN_ASC_STL_DETAIL_ACCL_THROW(Exception);
    }
    CANN_ASC_STL_DETAIL_ACCL_CATCH(const Exception& e)
    {
        expect_eq("catch by const lref: e.value", e.value, exception_value());
        expect_true("catch by const lref: reached", true);
    }
    CANN_ASC_STL_DETAIL_ACCL_CATCH(const ExceptionBase& e)
    {
        expect_eq("catch by const lref (base): e.value", e.value, exception_value());
        expect_true("catch by const lref (base): should not reach", false);
    }
    CANN_ASC_STL_DETAIL_ACCL_CATCH_ALL
    {
        expect_true("catch by const lref (all): should not reach", false);
    }
}

static void test_exception_case_4()
{
    // 4. test rethrow
    CANN_ASC_STL_DETAIL_ACCL_TRY
    {
        CANN_ASC_STL_DETAIL_ACCL_TRY
        {
            CANN_ASC_STL_DETAIL_ACCL_THROW(Exception);
        }
        CANN_ASC_STL_DETAIL_ACCL_CATCH(Exception e)
        {
            expect_eq("rethrow inner: e.value", e.value, exception_value());
            CANN_ASC_STL_DETAIL_ACCL_RETHROW;
        }
        CANN_ASC_STL_DETAIL_ACCL_CATCH(ExceptionBase e)
        {
            expect_eq("rethrow inner (base): e.value", e.value, exception_value());
            expect_true("rethrow inner (base): should not reach", false);
        }
        CANN_ASC_STL_DETAIL_ACCL_CATCH_ALL
        {
            expect_true("rethrow inner (all): should not reach", false);
        }
    }
    CANN_ASC_STL_DETAIL_ACCL_CATCH(const Exception& e)
    {
        expect_eq("rethrow outer: e.value", e.value, exception_value());
        expect_true("rethrow outer: reached", true);
    }
    CANN_ASC_STL_DETAIL_ACCL_CATCH(const ExceptionBase& e)
    {
        expect_eq("rethrow outer (base): e.value", e.value, exception_value());
        expect_true("rethrow outer (base): should not reach", false);
    }
    CANN_ASC_STL_DETAIL_ACCL_CATCH_ALL
    {
        expect_true("rethrow outer (all): should not reach", false);
    }
}

static void test_exception_case_5()
{
    // 5. test throwing host-only exceptions
    CANN_ASC_STL_DETAIL_ACCL_TRY
    {
        CANN_ASC_STL_DETAIL_ACCL_THROW(HostException);
    }
    CANN_ASC_STL_DETAIL_ACCL_CATCH(const HostException& e)
    {
        expect_eq("host-only: e.value", e.value, exception_value());
        expect_true("host-only: reached", true);
    }
    CANN_ASC_STL_DETAIL_ACCL_CATCH_FALLTHROUGH
}

static void run_exception_macro_tests()
{
    test_exception_case_1();
    test_exception_case_2();
    test_exception_case_3();
    test_exception_case_4();
    test_exception_case_5();
}
#else
static void test_compile_only()
{
    // When exceptions are disabled, CANN_ASC_STL_DETAIL_ACCL_TRY/CANN_ASC_STL_DETAIL_ACCL_CATCH expand to if constexpr.
    // Verify the macros compile and the try-body executes normally.
    bool try_executed = false;
    CANN_ASC_STL_DETAIL_ACCL_TRY
    {
        try_executed = true;
    }
    CANN_ASC_STL_DETAIL_ACCL_CATCH(int e)
    {
        // never reached in no-exception mode
    }
    CANN_ASC_STL_DETAIL_ACCL_CATCH_ALL
    {
        // never reached in no-exception mode
    }
    expect_true("no-exceptions: try body executed", try_executed);

    bool try2_executed = false;
    CANN_ASC_STL_DETAIL_ACCL_TRY
    {
        try2_executed = true;
    }
    CANN_ASC_STL_DETAIL_ACCL_CATCH(const int& e)
    {
        // never reached in no-exception mode
    }
    CANN_ASC_STL_DETAIL_ACCL_CATCH_FALLTHROUGH
    expect_true("no-exceptions: try body executed (fallthrough)", try2_executed);
}
#endif

int main()
{
#if CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS()
    run_exception_macro_tests();
#else
    test_compile_only();
#endif
    return g_failures == 0 ? 0 : 1;
}
