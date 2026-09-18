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

#include <asc/std/__type_traits/lazy.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][lazy] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][lazy] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

// Test template: counts the number of type arguments
template <class... Ts>
struct arg_counter {
    static constexpr int value = sizeof...(Ts);
};

// Test template: always has value == true
template <class... Ts>
struct always_true {
    static constexpr bool value = true;
};

int main()
{
    // _Lazy<F, Args...> inherits from F<Args...>, so members of F<Args...> are accessible
    expect_eq("_Lazy<arg_counter, int, float, char>::value", asc::std::_Lazy<arg_counter, int, float, char>::value, 3);

    expect_eq("_Lazy<arg_counter, int>::value", asc::std::_Lazy<arg_counter, int>::value, 1);

    expect_eq("_Lazy<arg_counter>::value", asc::std::_Lazy<arg_counter>::value, 0);

    expect_eq("_Lazy<always_true, int, float>::value", asc::std::_Lazy<always_true, int, float>::value, true);

    // _Lazy<F, Args...> is derived from F<Args...>
    expect_true("is_base_of<arg_counter<int,float,char>, _Lazy<arg_counter,int,float,char>>",
        std::is_base_of_v<arg_counter<int, float, char>, asc::std::_Lazy<arg_counter, int, float, char>>);

    expect_true("is_base_of<always_true<>, _Lazy<always_true>>",
        std::is_base_of_v<always_true<>, asc::std::_Lazy<always_true>>);

    return g_failures == 0 ? 0 : 1;
}
