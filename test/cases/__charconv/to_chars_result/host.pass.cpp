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

#include <asc/std/__charconv/to_chars_result.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][to_chars_result] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][to_chars_result] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

static void check_part1()
{
    // Test operator bool() - success case (ec == errc{})
    {
        char buf[10];
        asc::std::to_chars_result r{buf, asc::std::errc{}};
        expect_true("operator bool() with errc{} (success)", static_cast<bool>(r));
    }

    // Test operator bool() - failure case (ec != errc{})
    {
        char buf[10];
        asc::std::to_chars_result r{buf, asc::std::errc::invalid_argument};
        expect_false("operator bool() with invalid_argument (failure)", static_cast<bool>(r));
    }

    // Test operator bool() - another failure case
    {
        char buf[10];
        asc::std::to_chars_result r{buf, asc::std::errc::result_out_of_range};
        expect_false("operator bool() with result_out_of_range (failure)", static_cast<bool>(r));
    }

    // Test member access
    {
        char buf[10];
        asc::std::to_chars_result r{buf, asc::std::errc{}};
        expect_true("ptr member access", r.ptr == buf);
        expect_true("ec member access", r.ec == asc::std::errc{});
    }

    // Test operator== - same ptr and ec
    {
        char buf[10];
        asc::std::to_chars_result r1{buf, asc::std::errc{}};
        asc::std::to_chars_result r2{buf, asc::std::errc{}};
        expect_true("operator== same ptr and ec", r1 == r2);
    }
}

static void check_part2()
{
    // Test operator== - different ptr, same ec
    {
        char buf1[10];
        char buf2[10];
        asc::std::to_chars_result r1{buf1, asc::std::errc{}};
        asc::std::to_chars_result r2{buf2, asc::std::errc{}};
        expect_false("operator== different ptr", r1 == r2);
    }

    // Test operator== - same ptr, different ec
    {
        char buf[10];
        asc::std::to_chars_result r1{buf, asc::std::errc{}};
        asc::std::to_chars_result r2{buf, asc::std::errc::invalid_argument};
        expect_false("operator== different ec", r1 == r2);
    }

    // Test operator!= - equal (should be false)
    {
        char buf[10];
        asc::std::to_chars_result r1{buf, asc::std::errc{}};
        asc::std::to_chars_result r2{buf, asc::std::errc{}};
        expect_false("operator!= equal", r1 != r2);
    }

    // Test operator!= - different ptr and ec (should be true)
    {
        char buf1[10];
        char buf2[10];
        asc::std::to_chars_result r1{buf1, asc::std::errc{}};
        asc::std::to_chars_result r2{buf2, asc::std::errc::invalid_argument};
        expect_true("operator!= different", r1 != r2);
    }
}

static void check_part3()
{
    // Test operator!= - same ptr, different ec (should be true)
    {
        char buf[10];
        asc::std::to_chars_result r1{buf, asc::std::errc{}};
        asc::std::to_chars_result r2{buf, asc::std::errc::result_out_of_range};
        expect_true("operator!= same ptr different ec", r1 != r2);
    }
}

int main()
{
    check_part1();
    check_part2();
    check_part3();

    return g_failures == 0 ? 0 : 1;
}
