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

#include <asc/std/__optional/nullopt.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][nullopt] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    // nullopt is a global constant of type nullopt_t
    expect_true("is_same<remove_cv_t<decltype(nullopt)>, nullopt_t>",
        std::is_same_v<std::remove_cv_t<decltype(asc::std::nullopt)>, asc::std::nullopt_t>);

    // nullopt_t is not default-constructible (secret tag pattern prevents it)
    expect_true("!is_default_constructible<nullopt_t>", !std::is_default_constructible_v<asc::std::nullopt_t>);

    // nullopt_t is not constructible from int (secret tag pattern)
    expect_true("!is_constructible<nullopt_t, int>", !std::is_constructible_v<asc::std::nullopt_t, int>);

    // nullopt_t is copy-constructible
    expect_true("is_copy_constructible<nullopt_t>", std::is_copy_constructible_v<asc::std::nullopt_t>);

    // nullopt is usable in constexpr context
    constexpr asc::std::nullopt_t np = asc::std::nullopt;
    (void)np;
    expect_true("constexpr nullopt_t np = nullopt (compiles)", true);

    // nullopt can be copied
    asc::std::nullopt_t n1 = asc::std::nullopt;
    asc::std::nullopt_t n2 = asc::std::nullopt;
    (void)n1;
    (void)n2;
    expect_true("nullopt_t n1 = nullopt; n2 = nullopt (compiles)", true);

    // nullopt_t is an empty type (no data members)
    expect_true("is_empty<nullopt_t>", std::is_empty_v<asc::std::nullopt_t>);

    // nullopt_t is trivially destructible
    expect_true("is_trivially_destructible<nullopt_t>", std::is_trivially_destructible_v<asc::std::nullopt_t>);

    return g_failures == 0 ? 0 : 1;
}
