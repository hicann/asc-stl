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

#include <asc/std/__type_traits/integral_constant.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][integral_constant] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][integral_constant] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // --- value member ---
    expect_eq("integral_constant<int,5>::value", asc::std::integral_constant<int, 5>::value, 5);
    expect_eq("integral_constant<int,0>::value", asc::std::integral_constant<int, 0>::value, 0);
    expect_eq("integral_constant<int,-3>::value", asc::std::integral_constant<int, -3>::value, -3);

    // --- true_type / false_type ---
    expect_eq("true_type::value", asc::std::true_type::value, true);
    expect_eq("false_type::value", asc::std::false_type::value, false);

    // --- bool_constant ---
    expect_eq("bool_constant<true>::value", asc::std::bool_constant<true>::value, true);
    expect_eq("bool_constant<false>::value", asc::std::bool_constant<false>::value, false);

    // --- value_type typedef ---
    expect_true("true_type::value_type is bool", std::is_same<asc::std::true_type::value_type, bool>::value);
    expect_true("integral_constant<int,7>::value_type is int",
        std::is_same<asc::std::integral_constant<int, 7>::value_type, int>::value);

    // --- type typedef (self-referential) ---
    expect_true("true_type::type is true_type", std::is_same<asc::std::true_type::type, asc::std::true_type>::value);
    expect_true("integral_constant<int,42>::type is integral_constant<int,42>",
        std::is_same<asc::std::integral_constant<int, 42>::type, asc::std::integral_constant<int, 42>>::value);

    // --- implicit conversion operator ---
    {
        asc::std::integral_constant<int, 9> ic;
        int converted = ic;  // operator value_type()
        expect_eq("implicit conversion integral_constant<int,9> -> int", converted, 9);
    }
    {
        asc::std::true_type tt;
        bool b = tt;
        expect_true("implicit conversion true_type -> bool", b == true);
    }
    {
        asc::std::false_type ft;
        bool b = ft;
        expect_true("implicit conversion false_type -> bool", b == false);
    }

    // --- call operator ---
    {
        asc::std::integral_constant<int, 42> ic;
        expect_eq("integral_constant<int,42>()()", ic(), 42);
    }
    {
        asc::std::true_type tt;
        expect_true("true_type()()", tt() == true);
    }
    {
        asc::std::false_type ft;
        expect_true("false_type()()", ft() == false);
    }

    // --- using in conditional / static_assert contexts ---
    expect_true("true_type::value is true (conditional use)", asc::std::true_type::value == true);

    // --- integral_constant with different types ---
    expect_eq("integral_constant<unsigned,100>::value", asc::std::integral_constant<unsigned, 100>::value, 100u);
    expect_eq("integral_constant<long,1234567890L>::value", asc::std::integral_constant<long, 1234567890L>::value,
        1234567890L);

    return g_failures == 0 ? 0 : 1;
}
