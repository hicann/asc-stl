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

#include <asc/std/__type_traits/is_char_like_type.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_char_like_type] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// --- test types ---
struct trivial_standard_layout {
    int a;
    float b;
};

struct non_trivial {
    int a;
    non_trivial() : a(0)
    {}
    non_trivial(int x) : a(x)  // NOLINT(runtime/explicit)
    {}
};

struct empty_trivial {};

struct with_virtual {
    virtual ~with_virtual()
    {}
};

int main()
{
    // char-like types: standard layout AND trivial
    expect_true("__accl_is_char_like_type_v<char>", asc::std::__accl_is_char_like_type_v<char>, true);
    expect_true("__accl_is_char_like_type_v<signed char>", asc::std::__accl_is_char_like_type_v<signed char>, true);
    expect_true("__accl_is_char_like_type_v<unsigned char>", asc::std::__accl_is_char_like_type_v<unsigned char>, true);
    expect_true("__accl_is_char_like_type_v<wchar_t>", asc::std::__accl_is_char_like_type_v<wchar_t>, true);
    expect_true("__accl_is_char_like_type_v<char16_t>", asc::std::__accl_is_char_like_type_v<char16_t>, true);
    expect_true("__accl_is_char_like_type_v<char32_t>", asc::std::__accl_is_char_like_type_v<char32_t>, true);
    expect_true("__accl_is_char_like_type_v<int>", asc::std::__accl_is_char_like_type_v<int>, true);
    expect_true("__accl_is_char_like_type_v<float>", asc::std::__accl_is_char_like_type_v<float>, true);
    expect_true("__accl_is_char_like_type_v<int*>", asc::std::__accl_is_char_like_type_v<int*>, true);
    expect_true("__accl_is_char_like_type_v<trivial_standard_layout>",
        asc::std::__accl_is_char_like_type_v<trivial_standard_layout>, true);
    expect_true("__accl_is_char_like_type_v<empty_trivial>", asc::std::__accl_is_char_like_type_v<empty_trivial>, true);

    // non-char-like types
    expect_true("!__accl_is_char_like_type_v<non_trivial>", !asc::std::__accl_is_char_like_type_v<non_trivial>, true);
    expect_true("!__accl_is_char_like_type_v<with_virtual>", !asc::std::__accl_is_char_like_type_v<with_virtual>, true);

    return g_failures == 0 ? 0 : 1;
}
