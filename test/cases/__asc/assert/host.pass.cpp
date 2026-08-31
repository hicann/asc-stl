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

#include <asc/std/__asc/assert.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <csignal>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][assert] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_eq(const char* expr, int got, int expected)
{
    bool ok = (got == expected);
    std::cout << "[host][assert] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

static void test_default_configuration_assertions_disabled()
{
    // Test 1: Default configuration - assertions should be disabled
#ifdef ASC_ENABLE_ASSERTIONS
    expect_true("ASC_ENABLE_ASSERTIONS not defined by default", false);
#else
    expect_true("ASC_ENABLE_ASSERTIONS not defined by default", true);
#endif

#ifdef ASC_ENABLE_HOST_ASSERTIONS
    expect_true("ASC_ENABLE_HOST_ASSERTIONS not defined by default", false);
#else
    expect_true("ASC_ENABLE_HOST_ASSERTIONS not defined by default", true);
#endif

#ifdef ASC_ENABLE_DEVICE_ASSERTIONS
    expect_true("ASC_ENABLE_DEVICE_ASSERTIONS not defined by default", false);
#else
    expect_true("ASC_ENABLE_DEVICE_ASSERTIONS not defined by default", true);
#endif
}

static void test_asc_assert_assertions_disabled()
{
    // Test 2: CANN_ASC_STL_DETAIL_ASSERT is a no-op when assertions are disabled
    {
        CANN_ASC_STL_DETAIL_ASSERT(false, "should be no-op");
        expect_true("CANN_ASC_STL_DETAIL_ASSERT(false,...) is no-op", true);

        CANN_ASC_STL_DETAIL_ASSERT(true, "should be no-op");
        expect_true("CANN_ASC_STL_DETAIL_ASSERT(true,...) is no-op", true);
    }
}

static void test_asc_assert_does_evaluate()
{
    // Test 3: CANN_ASC_STL_DETAIL_ASSERT does not evaluate its expression when disabled
    {
        int counter = 0;
        CANN_ASC_STL_DETAIL_ASSERT(++counter > 0, "expression should not be evaluated");
        expect_eq("CANN_ASC_STL_DETAIL_ASSERT does not evaluate expression (counter)", counter, 0);
    }
}

static void test_asc_true_expression_passes()
{
    // Test 4: CANN_ASC_STL_DETAIL_VERIFY with true expression passes
    {
        CANN_ASC_STL_DETAIL_VERIFY(true, "should pass");
        expect_true("CANN_ASC_STL_DETAIL_VERIFY(true,...) passes", true);

        int x = 5;
        CANN_ASC_STL_DETAIL_VERIFY(x > 0, "x should be positive");
        expect_true("CANN_ASC_STL_DETAIL_VERIFY(x>0,...) passes", true);
    }
}

static void test_asc_evaluates_expression()
{
    // Test 5: CANN_ASC_STL_DETAIL_VERIFY evaluates its expression
    {
        int counter = 0;
        CANN_ASC_STL_DETAIL_VERIFY(++counter > 0, "expression should be evaluated");
        expect_eq("CANN_ASC_STL_DETAIL_VERIFY evaluates expression (counter)", counter, 1);
    }
}

static void test_asc_false_expression_aborts()
{
    // Test 6: CANN_ASC_STL_DETAIL_VERIFY with false expression aborts
    {
        pid_t pid = fork();
        if (pid == 0) {
            // Child process - CANN_ASC_STL_DETAIL_VERIFY(false,...) should abort
            CANN_ASC_STL_DETAIL_VERIFY(false, "this should abort");
            _exit(0);  // Should never reach here
        }
        int status = 0;
        waitpid(pid, &status, 0);
        bool aborted = WIFSIGNALED(status) && (WTERMSIG(status) == SIGABRT);
        expect_true("CANN_ASC_STL_DETAIL_VERIFY(false,...) aborts with SIGABRT", aborted);
    }
}

static void test_asc_assert_device_always()
{
    // Test 7: CANN_ASC_STL_DETAIL_ASSERT_DEVICE is always a no-op
    {
        CANN_ASC_STL_DETAIL_ASSERT_DEVICE(false, "device assert should always be no-op");
        expect_true("CANN_ASC_STL_DETAIL_ASSERT_DEVICE(false,...) is no-op", true);
    }
}

static void test_asc_expression_side_effects()
{
    // Test 8: CANN_ASC_STL_DETAIL_VERIFY with expression that has side effects and is true
    {
        int x = 10;
        CANN_ASC_STL_DETAIL_VERIFY(x == 10, "x should be 10");
        expect_true("CANN_ASC_STL_DETAIL_VERIFY(x==10,...) passes", true);
    }
}

int main()
{
    test_default_configuration_assertions_disabled();
    test_asc_assert_assertions_disabled();
    test_asc_assert_does_evaluate();
    test_asc_true_expression_passes();
    test_asc_evaluates_expression();
    test_asc_false_expression_aborts();
    test_asc_assert_device_always();
    test_asc_expression_side_effects();

    return g_failures == 0 ? 0 : 1;
}
