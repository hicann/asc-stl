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

#include <asc/std/__type_traits/always_false.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][always_false] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    // __always_false_v with no template args
    expect_true("__always_false_v<> == false", asc::std::__always_false_v<> == false);

    // __always_false_v with one type arg
    expect_true("__always_false_v<int> == false", asc::std::__always_false_v<int> == false);

    // __always_false_v with multiple type args
    expect_true("__always_false_v<int, double, char> == false", asc::std::__always_false_v<int, double, char> == false);

    // __always_false_v value is false
    expect_true("!__always_false_v<int>", !asc::std::__always_false_v<int>);

    // static_assert usage (compile-time check)
    static_assert(asc::std::__always_false_v<> == false, "");
    static_assert(asc::std::__always_false_v<int> == false, "");
    static_assert(asc::std::__always_false_v<int, char, double> == false, "");

    // Verify it is constexpr
    constexpr bool b = asc::std::__always_false_v<float>;
    expect_true("constexpr __always_false_v<float> == false", b == false);

    return g_failures == 0 ? 0 : 1;
}
