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

#include <asc/std/__type_traits/conjunction.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][conjunction] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][conjunction] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

int main()
{
    // Empty conjunction → true
    expect_true("conjunction<>::value", asc::std::conjunction<>::value);

    // Single true_type → true
    expect_true("conjunction<true_type>::value", asc::std::conjunction<asc::std::true_type>::value);

    // Single false_type → false
    expect_false("conjunction<false_type>::value", asc::std::conjunction<asc::std::false_type>::value);

    // Multiple all true → true
    expect_true("conjunction<true_type, true_type>::value",
        asc::std::conjunction<asc::std::true_type, asc::std::true_type>::value);

    // Multiple, last false → false
    expect_false("conjunction<true_type, false_type>::value",
        asc::std::conjunction<asc::std::true_type, asc::std::false_type>::value);

    // Multiple, first false → false (short-circuit)
    expect_false("conjunction<false_type, true_type>::value",
        asc::std::conjunction<asc::std::false_type, asc::std::true_type>::value);

    // All false → false
    expect_false("conjunction<false_type, false_type>::value",
        asc::std::conjunction<asc::std::false_type, asc::std::false_type>::value);

    // conjunction_v
    expect_true("conjunction_v<>", asc::std::conjunction_v<>);
    expect_true("conjunction_v<true_type, true_type, true_type>",
        asc::std::conjunction_v<asc::std::true_type, asc::std::true_type, asc::std::true_type>);
    expect_false("conjunction_v<true_type, false_type, true_type>",
        asc::std::conjunction_v<asc::std::true_type, asc::std::false_type, asc::std::true_type>);

    // Using bool_constant
    expect_true("conjunction<bool_constant<true>>::value", asc::std::conjunction<asc::std::bool_constant<true>>::value);
    expect_false(
        "conjunction<bool_constant<false>>::value", asc::std::conjunction<asc::std::bool_constant<false>>::value);

    // Three args: true, true, false → false
    expect_false("conjunction<true_type, true_type, false_type>::value",
        asc::std::conjunction<asc::std::true_type, asc::std::true_type, asc::std::false_type>::value);

    // Three args: false, true, true → false (short-circuit on first)
    expect_false("conjunction<false_type, true_type, true_type>::value",
        asc::std::conjunction<asc::std::false_type, asc::std::true_type, asc::std::true_type>::value);

    // Three args all true → true
    expect_true("conjunction<true_type, true_type, true_type>::value",
        asc::std::conjunction<asc::std::true_type, asc::std::true_type, asc::std::true_type>::value);

    // conjunction<true_type> inherits from true_type (type identity check)
    expect_true("is_base_of<true_type, conjunction<true_type>>",
        std::is_base_of<asc::std::true_type, asc::std::conjunction<asc::std::true_type>>::value);

    // conjunction<false_type> inherits from false_type
    expect_true("is_base_of<false_type, conjunction<false_type>>",
        std::is_base_of<asc::std::false_type, asc::std::conjunction<asc::std::false_type>>::value);

    // conjunction<> inherits from true_type
    expect_true(
        "is_base_of<true_type, conjunction<>>", std::is_base_of<asc::std::true_type, asc::std::conjunction<>>::value);

    return g_failures == 0 ? 0 : 1;
}
