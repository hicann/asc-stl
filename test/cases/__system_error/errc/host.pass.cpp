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

#include <asc/std/__system_error/errc.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][errc] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][errc] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    // Verify asc::std::errc is an enum type
    expect_true("std::is_enum<asc::std::errc>::value", std::is_enum<asc::std::errc>::value);

    // In hosted mode asc::std::errc is std::errc; in freestanding it is a
    // scoped enum with the same three enumerators.  On non-Windows the
    // underlying integer values match the POSIX errno values used by std::errc.
    expect_eq(
        "static_cast<int>(asc::std::errc::invalid_argument)", static_cast<int>(asc::std::errc::invalid_argument), 22);
    expect_eq("static_cast<int>(asc::std::errc::result_out_of_range)",
        static_cast<int>(asc::std::errc::result_out_of_range), 34);
    expect_eq(
        "static_cast<int>(asc::std::errc::value_too_large)", static_cast<int>(asc::std::errc::value_too_large), 75);

    // Equality / inequality on the scoped enum
    expect_true("errc::invalid_argument == errc::invalid_argument",
        asc::std::errc::invalid_argument == asc::std::errc::invalid_argument);
    expect_true("errc::invalid_argument != errc::result_out_of_range",
        asc::std::errc::invalid_argument != asc::std::errc::result_out_of_range);
    expect_true("errc::invalid_argument != errc::value_too_large",
        asc::std::errc::invalid_argument != asc::std::errc::value_too_large);
    expect_true("errc::result_out_of_range != errc::value_too_large",
        asc::std::errc::result_out_of_range != asc::std::errc::value_too_large);

    // Verify all three enumerators are distinct
    expect_true("three distinct values",
        static_cast<int>(asc::std::errc::invalid_argument) != static_cast<int>(asc::std::errc::result_out_of_range) &&
            static_cast<int>(asc::std::errc::invalid_argument) != static_cast<int>(asc::std::errc::value_too_large) &&
            static_cast<int>(asc::std::errc::result_out_of_range) != static_cast<int>(asc::std::errc::value_too_large));

    return g_failures == 0 ? 0 : 1;
}
