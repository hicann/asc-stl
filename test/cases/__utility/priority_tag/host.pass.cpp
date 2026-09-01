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

#include <asc/std/__utility/priority_tag.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][priority_tag] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

// Overload set to verify priority resolution semantics
static int overload_select(asc::std::__priority_tag<0>)
{
    return 0;
}
static int overload_select(asc::std::__priority_tag<1>)
{
    return 1;
}
static int overload_select(asc::std::__priority_tag<2>)
{
    return 2;
}

int main()
{
    // --- Inheritance chain ---
    expect_true("__priority_tag<1> derives from __priority_tag<0>",
        std::is_base_of<asc::std::__priority_tag<0>, asc::std::__priority_tag<1>>::value);
    expect_true("__priority_tag<2> derives from __priority_tag<1>",
        std::is_base_of<asc::std::__priority_tag<1>, asc::std::__priority_tag<2>>::value);
    expect_true("__priority_tag<2> derives from __priority_tag<0>",
        std::is_base_of<asc::std::__priority_tag<0>, asc::std::__priority_tag<2>>::value);
    expect_true("__priority_tag<0> does NOT derive from __priority_tag<1>",
        !std::is_base_of<asc::std::__priority_tag<1>, asc::std::__priority_tag<0>>::value);

    // --- Overload resolution: most-derived tag wins ---
    expect_true("overload_select(__priority_tag<0>{}) == 0", overload_select(asc::std::__priority_tag<0>{}) == 0);
    expect_true("overload_select(__priority_tag<1>{}) == 1", overload_select(asc::std::__priority_tag<1>{}) == 1);
    expect_true("overload_select(__priority_tag<2>{}) == 2", overload_select(asc::std::__priority_tag<2>{}) == 2);

    // --- Empty type (no data members) ---
    expect_true("__priority_tag<0> is empty", std::is_empty<asc::std::__priority_tag<0>>::value);
    expect_true("__priority_tag<5> is empty", std::is_empty<asc::std::__priority_tag<5>>::value);

    // --- Default-constructible ---
    expect_true("__priority_tag<3> is default-constructible",
        std::is_default_constructible<asc::std::__priority_tag<3>>::value);

    return g_failures == 0 ? 0 : 1;
}
