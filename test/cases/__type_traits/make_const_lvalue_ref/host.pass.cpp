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

#include <asc/std/__type_traits/make_const_lvalue_ref.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][make_const_lvalue_ref] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    // __make_const_lvalue_ref<T> = const remove_reference_t<T>&
    // Use std::is_same_v / std::remove_reference_t as independent references

    // Basic type
    expect_true("is_same<__make_const_lvalue_ref<int>, const int&>",
        std::is_same_v<asc::std::__make_const_lvalue_ref<int>, const int&>);

    // lvalue reference — reference removed, then const& added
    expect_true("is_same<__make_const_lvalue_ref<int&>, const int&>",
        std::is_same_v<asc::std::__make_const_lvalue_ref<int&>, const int&>);

    // rvalue reference — reference removed, then const& added
    expect_true("is_same<__make_const_lvalue_ref<int&&>, const int&>",
        std::is_same_v<asc::std::__make_const_lvalue_ref<int&&>, const int&>);

    // const type
    expect_true("is_same<__make_const_lvalue_ref<const int>, const int&>",
        std::is_same_v<asc::std::__make_const_lvalue_ref<const int>, const int&>);

    // const lvalue reference
    expect_true("is_same<__make_const_lvalue_ref<const int&>, const int&>",
        std::is_same_v<asc::std::__make_const_lvalue_ref<const int&>, const int&>);

    // const rvalue reference
    expect_true("is_same<__make_const_lvalue_ref<const int&&>, const int&>",
        std::is_same_v<asc::std::__make_const_lvalue_ref<const int&&>, const int&>);

    // Different base types
    expect_true("is_same<__make_const_lvalue_ref<double>, const double&>",
        std::is_same_v<asc::std::__make_const_lvalue_ref<double>, const double&>);

    expect_true("is_same<__make_const_lvalue_ref<float&>, const float&>",
        std::is_same_v<asc::std::__make_const_lvalue_ref<float&>, const float&>);

    // Independent computation: const std::remove_reference_t<T>&
    expect_true("independent: __make_const_lvalue_ref<int> == const std::remove_reference_t<int>&",
        std::is_same_v<asc::std::__make_const_lvalue_ref<int>, const std::remove_reference_t<int>&>);

    expect_true("independent: __make_const_lvalue_ref<int&&> == const std::remove_reference_t<int&&>&",
        std::is_same_v<asc::std::__make_const_lvalue_ref<int&&>, const std::remove_reference_t<int&&>&>);

    // Verify it is actually a const lvalue reference
    expect_true("is_lvalue_reference_v<__make_const_lvalue_ref<int>>",
        std::is_lvalue_reference_v<asc::std::__make_const_lvalue_ref<int>>);

    expect_true("is_const_v<remove_reference_t<__make_const_lvalue_ref<int>>>",
        std::is_const_v<std::remove_reference_t<asc::std::__make_const_lvalue_ref<int>>>);

    return g_failures == 0 ? 0 : 1;
}
