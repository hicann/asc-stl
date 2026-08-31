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

#include <asc/__functional/always_true_false.h>
#include <iostream>
#include <string>

static int g_failures = 0;

static void expect_true(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][always_true_false] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // --- always_true ---
    {
        asc::always_true f;
        expect_true("always_true{}()", f(), true);
        expect_true("always_true{}(42)", asc::always_true{}(42), true);
        expect_true("always_true{}(1, 2, 3)", asc::always_true{}(1, 2, 3), true);
        expect_true("always_true{}(3.14, \"hello\")", asc::always_true{}(3.14, std::string("hello")), true);
    }

    // --- always_false ---
    {
        asc::always_false f;
        expect_true("always_false{}()", f(), false);
        expect_true("always_false{}(42)", asc::always_false{}(42), false);
        expect_true("always_false{}(1, 2, 3)", asc::always_false{}(1, 2, 3), false);
        expect_true("always_false{}(3.14, \"hello\")", asc::always_false{}(3.14, std::string("hello")), false);
    }

    // --- constexpr check ---
    {
        constexpr bool ct_true = asc::always_true{}();
        constexpr bool ct_false = asc::always_false{}();
        expect_true("constexpr always_true{}()", ct_true, true);
        expect_true("constexpr always_false{}()", ct_false, false);
    }

    // --- noexcept check ---
    {
        expect_true("noexcept(always_true{}())", noexcept(asc::always_true{}()), true);
        expect_true("noexcept(always_false{}())", noexcept(asc::always_false{}()), true);
    }

    // --- used as predicate in a realistic scenario ---
    {
        int data[] = {1, 2, 3, 4, 5};
        bool all_true = true;
        bool all_false = true;
        for (int v : data) {
            if (!asc::always_true{}(v))
                all_true = false;
            if (asc::always_false{}(v))
                all_false = false;
        }
        expect_true("all_true via always_true predicate", all_true, true);
        expect_true("all_false via always_false predicate", all_false, true);
    }

    return g_failures == 0 ? 0 : 1;
}
