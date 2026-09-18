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

#include <asc/std/__functional/is_transparent.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][is_transparent] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][is_transparent] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

// Type with is_transparent nested type (void)
struct TransparentType {
    using is_transparent = void;
};

// Type without is_transparent nested type
struct NonTransparentType {};

// Type with is_transparent as int
struct TransparentIntType {
    using is_transparent = int;
};

int main()
{
    // Type with is_transparent = void -> true
    expect_true("__is_transparent<TransparentType, int>", asc::std::__is_transparent<TransparentType, int>);

    // Type without is_transparent -> false
    expect_false("__is_transparent<NonTransparentType, int>", asc::std::__is_transparent<NonTransparentType, int>);

    // Type with is_transparent = int -> true (any nested type named is_transparent counts)
    expect_true("__is_transparent<TransparentIntType, double>", asc::std::__is_transparent<TransparentIntType, double>);

    // _Up doesn't matter: same _Tp, different _Up
    expect_true("__is_transparent<TransparentType, double>", asc::std::__is_transparent<TransparentType, double>);
    expect_false(
        "__is_transparent<NonTransparentType, double>", asc::std::__is_transparent<NonTransparentType, double>);

    // Test with void as _Up
    expect_true("__is_transparent<TransparentType, void>", asc::std::__is_transparent<TransparentType, void>);
    expect_false("__is_transparent<NonTransparentType, void>", asc::std::__is_transparent<NonTransparentType, void>);

    return g_failures == 0 ? 0 : 1;
}
