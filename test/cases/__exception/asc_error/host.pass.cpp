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

#include <asc/std/__exception/asc_error.h>
#include <iostream>
#include <string>
#include <type_traits>

#if __has_include(<acl/acl_base_rt.h>)
#include <acl/acl_base_rt.h>
static_assert(std::is_same_v<asc::__asc_error_t, aclError>);
#endif

static int g_failures = 0;

static void expect_eq(const char* expr, int got, int expected)
{
    bool ok = (got == expected);
    std::cout << "[host][asc_error] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][asc_error] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_contains(const char* expr, const std::string& haystack, const char* needle)
{
    bool ok = haystack.find(needle) != std::string::npos;
    std::cout << "[host][asc_error] " << expr << " contains \"" << needle << "\" " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void check_part1()
{
    // Test 1: Basic construction and status()
    {
        asc::asc_error err(42, "something went wrong");
        expect_eq("err.status()", err.status(), 42);
        expect_true("err.what() != nullptr", err.what() != nullptr);
        expect_contains("err.what()", err.what(), "something went wrong");
        expect_contains("err.what()", err.what(), "aclError");
        expect_contains("err.what()", err.what(), "(42)");
    }

    // Test 2: With api parameter
    {
        asc::asc_error err(7, "device error", "aclSetTensorInfo");
        expect_eq("err.status() with api", err.status(), 7);
        expect_contains("err.what() with api", err.what(), "aclSetTensorInfo");
        expect_contains("err.what() with api", err.what(), "device error");
        expect_contains("err.what() with api", err.what(), "(7)");
    }

    // Test 3: Inherits from std::runtime_error
    {
        asc::asc_error err(99, "runtime failure");
        std::runtime_error& base = err;
        expect_contains("base.what()", base.what(), "runtime failure");
    }

    // Test 4: Throw and catch as asc_error
    {
        bool caught = false;
        try {
            throw asc::asc_error(100, "thrown error");
        } catch (const asc::asc_error& e) {
            caught = true;
            expect_eq("thrown err.status()", e.status(), 100);
            expect_contains("thrown err.what()", e.what(), "thrown error");
        }
        expect_true("caught asc_error", caught);
    }
}

static void check_part2()
{
    // Test 5: Throw and catch as std::runtime_error
    {
        bool caught = false;
        try {
            throw asc::asc_error(200, "base catch test");
        } catch (const std::runtime_error& e) {
            caught = true;
            expect_contains("caught as runtime_error", e.what(), "base catch test");
        }
        expect_true("caught as std::runtime_error", caught);
    }

    // Test 6: Zero status
    {
        asc::asc_error err(0, "no error");
        expect_eq("err.status() zero", err.status(), 0);
        expect_contains("err.what() zero", err.what(), "no error");
        expect_contains("err.what() zero", err.what(), "(0)");
    }

    // Test 7: Negative status
    {
        asc::asc_error err(-1, "negative status");
        expect_eq("err.status() negative", err.status(), -1);
        expect_contains("err.what() negative", err.what(), "negative status");
        expect_contains("err.what() negative", err.what(), "(-1)");
    }

    // Test 8: Empty message
    {
        asc::asc_error err(5, "");
        expect_eq("err.status() empty msg", err.status(), 5);
        expect_true("err.what() empty msg != nullptr", err.what() != nullptr);
    }
}

int main()
{
    check_part1();
    check_part2();

    return g_failures == 0 ? 0 : 1;
}
