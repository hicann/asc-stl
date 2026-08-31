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

#include <asc/std/__type_traits/negation.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][negation] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][negation] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

int main()
{
    // negation<true_type>::value should be false
    expect_false("negation<true_type>::value", asc::std::negation<asc::std::true_type>::value);

    // negation<false_type>::value should be true
    expect_true("negation<false_type>::value", asc::std::negation<asc::std::false_type>::value);

    // negation_v<true_type> should be false
    expect_false("negation_v<true_type>", asc::std::negation_v<asc::std::true_type>);

    // negation_v<false_type> should be true
    expect_true("negation_v<false_type>", asc::std::negation_v<asc::std::false_type>);

    // _Not alias
    expect_false("_Not<true_type>::value", asc::std::_Not<asc::std::true_type>::value);
    expect_true("_Not<false_type>::value", asc::std::_Not<asc::std::false_type>::value);

    // Test with integral_constant<int, 0> — !0 is true
    expect_true(
        "negation<integral_constant<int,0>>::value", asc::std::negation<asc::std::integral_constant<int, 0>>::value);

    // Test with integral_constant<int, 5> — !5 is false
    expect_false(
        "negation<integral_constant<int,5>>::value", asc::std::negation<asc::std::integral_constant<int, 5>>::value);

    // negation_v with integral_constant
    expect_true("negation_v<integral_constant<int,0>>", asc::std::negation_v<asc::std::integral_constant<int, 0>>);
    expect_false("negation_v<integral_constant<int,5>>", asc::std::negation_v<asc::std::integral_constant<int, 5>>);

    // Double negation
    expect_true(
        "negation<negation<true_type>>::value", asc::std::negation<asc::std::negation<asc::std::true_type>>::value);
    expect_false(
        "negation<negation<false_type>>::value", asc::std::negation<asc::std::negation<asc::std::false_type>>::value);

    // Compile-time checks
    static_assert(asc::std::negation<asc::std::true_type>::value == false, "");
    static_assert(asc::std::negation<asc::std::false_type>::value == true, "");
    static_assert(asc::std::negation_v<asc::std::true_type> == false, "");
    static_assert(asc::std::negation_v<asc::std::false_type> == true, "");

    return g_failures == 0 ? 0 : 1;
}
