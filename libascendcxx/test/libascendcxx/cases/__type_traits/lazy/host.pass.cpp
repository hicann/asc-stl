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

#include <asc/std/__type_traits/lazy.h>

#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][lazy] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond) {
        ++g_failures;
    }
}

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    const bool ok = (got == expected);
    std::cout << "[host][lazy] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok) {
        ++g_failures;
    }
}

template <class... Ts>
struct arg_counter {
    static constexpr int value = static_cast<int>(sizeof...(Ts));
};

template <class... Ts>
struct first_type {
    using type = void;
};

template <class T, class... Ts>
struct first_type<T, Ts...> {
    using type = T;
};

template <class T>
using require_integral = std::enable_if_t<std::is_integral_v<T>, std::true_type>;

using deferred_invalid = asc::std::_Lazy<require_integral, double>;
using unselected_invalid = std::conditional_t<false, deferred_invalid, std::false_type>;
using selected_valid = std::conditional_t<true, asc::std::_Lazy<require_integral, int>, std::false_type>;

static_assert(!unselected_invalid::value, "forming _Lazy must not instantiate an alias in an unselected branch");
static_assert(selected_valid::value, "the selected _Lazy branch must instantiate the wrapped alias");

int main()
{
    expect_true("Lazy<add_pointer,int>::type == int*",
        std::is_same_v<typename asc::std::_Lazy<std::add_pointer, int>::type, int*>);
    expect_true("Lazy<add_pointer,int>::type == add_pointer<int>::type",
        std::is_same_v<typename asc::std::_Lazy<std::add_pointer, int>::type, typename std::add_pointer<int>::type>);
    expect_true("Lazy<add_const,int>::type == const int",
        std::is_same_v<typename asc::std::_Lazy<std::add_const, int>::type, const int>);
    expect_true("Lazy<remove_reference,int&>::type == int",
        std::is_same_v<typename asc::std::_Lazy<std::remove_reference, int&>::type, int>);
    expect_true("Lazy<remove_reference,int&&>::type == int",
        std::is_same_v<typename asc::std::_Lazy<std::remove_reference, int&&>::type, int>);

    expect_true("Lazy<is_same,int,int>::value", asc::std::_Lazy<std::is_same, int, int>::value);
    expect_true("!Lazy<is_same,int,double>::value", !asc::std::_Lazy<std::is_same, int, double>::value);
    expect_true("Lazy<is_integral,int>::value", asc::std::_Lazy<std::is_integral, int>::value);
    expect_true("!Lazy<is_integral,float>::value", !asc::std::_Lazy<std::is_integral, float>::value);

    expect_eq("Lazy<arg_counter>::value", asc::std::_Lazy<arg_counter>::value, 0);
    expect_eq("Lazy<arg_counter,int>::value", asc::std::_Lazy<arg_counter, int>::value, 1);
    expect_eq("Lazy<arg_counter,int,double,char>::value", asc::std::_Lazy<arg_counter, int, double, char>::value, 3);

    expect_true("Lazy<is_same,int,int>::value", asc::std::_Lazy<std::is_same, int, int>::value);
    expect_true("!Lazy<is_same,int,char>::value", !asc::std::_Lazy<std::is_same, int, char>::value);

    expect_true("Lazy<first_type,int,double>::type == int",
        std::is_same_v<typename asc::std::_Lazy<first_type, int, double>::type, int>);
    expect_true("Lazy<first_type>::type == void", std::is_same_v<typename asc::std::_Lazy<first_type>::type, void>);

    expect_true("Lazy inherits is_same<int,int>",
        std::is_base_of_v<std::is_same<int, int>, asc::std::_Lazy<std::is_same, int, int>>);
    expect_true("Lazy inherits add_pointer<int>",
        std::is_base_of_v<std::add_pointer<int>, asc::std::_Lazy<std::add_pointer, int>>);

    expect_true("unselected invalid alias stays deferred", !unselected_invalid::value);
    expect_true("selected valid alias is instantiated", selected_valid::value);

    return g_failures == 0 ? 0 : 1;
}
