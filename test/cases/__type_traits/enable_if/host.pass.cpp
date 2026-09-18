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

#include <asc/std/__type_traits/enable_if.h>
#include <type_traits>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][enable_if] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

// SFINAE helper: check if enable_if<B, T>::type exists
template <bool B, class T = void, class = void>
struct has_enable_if_type : std::false_type {};

template <bool B, class T>
struct has_enable_if_type<B, T, std::void_t<typename asc::std::enable_if<B, T>::type>> : std::true_type {};

// SFINAE helper: check if enable_if_t<B, T> is valid
template <bool B, class T = void, class = void>
struct has_enable_if_t : std::false_type {};

template <bool B, class T>
struct has_enable_if_t<B, T, std::void_t<asc::std::enable_if_t<B, T>>> : std::true_type {};

// Test using enable_if in a SFINAE context
// Use a dummy parameter to avoid redefinition conflicts
template <class T, class = asc::std::enable_if_t<std::is_integral_v<T>>>
static constexpr bool is_integral_check(T)
{
    return true;
}

template <class T, class = asc::std::enable_if_t<std::is_floating_point_v<T>>>
static constexpr bool is_floating_check(T)
{
    return true;
}

int main()
{
    // enable_if<true>::type == void
    expect_true("is_same<enable_if<true>::type, void>", std::is_same<asc::std::enable_if<true>::type, void>::value);

    // enable_if<true, int>::type == int
    expect_true(
        "is_same<enable_if<true, int>::type, int>", std::is_same<asc::std::enable_if<true, int>::type, int>::value);

    // enable_if<true, double>::type == double
    expect_true("is_same<enable_if<true, double>::type, double>",
        std::is_same<asc::std::enable_if<true, double>::type, double>::value);

    // enable_if<false> does NOT have ::type
    expect_true("!has_enable_if_type<false>", !has_enable_if_type<false>::value);

    // enable_if<false, int> does NOT have ::type
    expect_true("!has_enable_if_type<false, int>", !has_enable_if_type<false, int>::value);

    // enable_if_t<true> == void
    expect_true("is_same<enable_if_t<true>, void>", std::is_same<asc::std::enable_if_t<true>, void>::value);

    // enable_if_t<true, int> == int
    expect_true("is_same<enable_if_t<true, int>, int>", std::is_same<asc::std::enable_if_t<true, int>, int>::value);

    // enable_if_t<true, double> == double
    expect_true(
        "is_same<enable_if_t<true, double>, double>", std::is_same<asc::std::enable_if_t<true, double>, double>::value);

    // enable_if_t<false> is not valid (SFINAE)
    expect_true("!has_enable_if_t<false>", !has_enable_if_t<false>::value);

    // enable_if_t<false, int> is not valid (SFINAE)
    expect_true("!has_enable_if_t<false, int>", !has_enable_if_t<false, int>::value);

    // SFINAE in function template context
    expect_true("is_integral_check(42)", is_integral_check(42));
    expect_true("is_floating_check(3.14)", is_floating_check(3.14));

    return g_failures == 0 ? 0 : 1;
}
