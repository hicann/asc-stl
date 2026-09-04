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

#include <asc/std/__charconv/from_chars_result.h>
#include <iostream>

using asc::std::errc;

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][asc::std::from_chars_result] " << expr << " = " << (cond ? "true" : "false")
              << " (expected true) " << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][asc::std::from_chars_result] " << expr << " = " << (cond ? "true" : "false")
              << " (expected false) " << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

static void check_part1()
{
    using asc::std::from_chars_result;

    // --- operator bool() tests ---
    {
        const char* str = "hello";
        asc::std::from_chars_result r{str, errc{}};
        expect_true("bool(r) with no error", static_cast<bool>(r));
    }
    {
        const char* str = "hello";
        asc::std::from_chars_result r{str, errc::invalid_argument};
        expect_false("bool(r) with invalid_argument", static_cast<bool>(r));
    }
    {
        const char* str = "hello";
        asc::std::from_chars_result r{str, errc::result_out_of_range};
        expect_false("bool(r) with result_out_of_range", static_cast<bool>(r));
    }
    {
        const char* str = "hello";
        asc::std::from_chars_result r{str, errc::value_too_large};
        expect_false("bool(r) with value_too_large", static_cast<bool>(r));
    }

    // --- operator== tests ---
    {
        const char* str = "hello";
        asc::std::from_chars_result a{str, errc{}};
        asc::std::from_chars_result b{str, errc{}};
        expect_true("a == b (same ptr, same ec no error)", a == b);
    }
    {
        const char* str = "hello";
        asc::std::from_chars_result a{str, errc{}};
        asc::std::from_chars_result b{str, errc::invalid_argument};
        expect_false("a == b (same ptr, different ec)", a == b);
    }
    {
        const char* str1 = "hello";
        const char* str2 = "world";
        asc::std::from_chars_result a{str1, errc{}};
        asc::std::from_chars_result b{str2, errc{}};
        expect_false("a == b (different ptr, same ec)", a == b);
    }
    {
        const char* str1 = "hello";
        const char* str2 = "world";
        asc::std::from_chars_result a{str1, errc{}};
        asc::std::from_chars_result b{str2, errc::invalid_argument};
        expect_false("a == b (different ptr, different ec)", a == b);
    }
}

static void check_part2()
{
    // --- operator!= tests ---
    {
        const char* str = "hello";
        asc::std::from_chars_result a{str, errc{}};
        asc::std::from_chars_result b{str, errc{}};
        expect_false("a != b (same ptr, same ec)", a != b);
    }
    {
        const char* str = "hello";
        asc::std::from_chars_result a{str, errc{}};
        asc::std::from_chars_result b{str, errc::invalid_argument};
        expect_true("a != b (same ptr, different ec)", a != b);
    }
    {
        const char* str1 = "hello";
        const char* str2 = "world";
        asc::std::from_chars_result a{str1, errc{}};
        asc::std::from_chars_result b{str2, errc{}};
        expect_true("a != b (different ptr, same ec)", a != b);
    }

    // --- nullptr ptr edge cases ---
    {
        asc::std::from_chars_result r{nullptr, errc{}};
        expect_true("bool(r) with nullptr ptr, no error", static_cast<bool>(r));
    }
    {
        asc::std::from_chars_result r{nullptr, errc::invalid_argument};
        expect_false("bool(r) with nullptr ptr, invalid_argument", static_cast<bool>(r));
    }
    {
        asc::std::from_chars_result a{nullptr, errc{}};
        asc::std::from_chars_result b{nullptr, errc{}};
        expect_true("a == b (both nullptr, same ec)", a == b);
    }
    {
        asc::std::from_chars_result a{nullptr, errc{}};
        asc::std::from_chars_result b{nullptr, errc::result_out_of_range};
        expect_false("a == b (both nullptr, different ec)", a == b);
    }
}

static void check_part3()
{
    // --- constexpr context ---
    {
        constexpr asc::std::from_chars_result r{"abc", asc::std::errc{}};
        static_assert(static_cast<bool>(r), "constexpr operator bool");
        constexpr asc::std::from_chars_result r2{"abc", asc::std::errc::invalid_argument};
        static_assert(!static_cast<bool>(r2), "constexpr operator bool with error");
        constexpr asc::std::from_chars_result a{"abc", asc::std::errc{}};
        constexpr asc::std::from_chars_result b{"abc", asc::std::errc{}};
        static_assert(a == b, "constexpr operator==");
        static_assert(a != asc::std::from_chars_result{"xyz", asc::std::errc{}}, "constexpr operator!=");
    }
}

int main()
{
    check_part1();
    check_part2();
    check_part3();

    return g_failures == 0 ? 0 : 1;
}
