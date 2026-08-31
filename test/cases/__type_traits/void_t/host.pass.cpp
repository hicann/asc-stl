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

#include <asc/std/__type_traits/void_t.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][void_t] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

// SFINAE detection idiom using void_t
template <typename T, typename = void>
struct has_value_type : std::false_type {};

template <typename T>
struct has_value_type<T, asc::std::void_t<typename T::value_type>> : std::true_type {};

struct WithValueType {
    using value_type = int;
};
struct WithoutValueType {};

int main()
{
    // Basic: void_t with various type packs maps to void
    expect_true("is_same<void_t<int>, void>", std::is_same<asc::std::void_t<int>, void>::value);
    expect_true("is_same<void_t<>, void>", std::is_same<asc::std::void_t<>, void>::value);
    expect_true(
        "is_same<void_t<int, double, char>, void>", std::is_same<asc::std::void_t<int, double, char>, void>::value);
    expect_true("is_same<void_t<void>, void>", std::is_same<asc::std::void_t<void>, void>::value);

    // SFINAE: void_t used in detection idiom
    expect_true("has_value_type<WithValueType>", has_value_type<WithValueType>::value);
    expect_true("!has_value_type<WithoutValueType>", !has_value_type<WithoutValueType>::value);

    return g_failures == 0 ? 0 : 1;
}
