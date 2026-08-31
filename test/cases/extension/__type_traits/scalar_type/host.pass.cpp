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

#include <asc/__type_traits/scalar_type.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

template <class _Tp, class = void>
struct has_scalar_type : std::false_type {};

template <class _Tp>
struct has_scalar_type<_Tp, std::void_t<typename _Tp::type>> : std::true_type {};

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][scalar_type] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][scalar_type] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

struct CustomScalar {};
struct CustomVector2 {};

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC
template <>
struct scalar_type<::CustomVector2> {
    using type = float;
};
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

int main()
{
    expect_false("scalar_type<int> has type", has_scalar_type<asc::scalar_type<int>>::value);
    expect_false("scalar_type<CustomScalar> has type", has_scalar_type<asc::scalar_type<CustomScalar>>::value);

    expect_true("scalar_type<CustomVector2> has type", has_scalar_type<asc::scalar_type<CustomVector2>>::value);
    expect_true(
        "scalar_type<const CustomVector2> has type", has_scalar_type<asc::scalar_type<const CustomVector2>>::value);
    expect_true("scalar_type<volatile CustomVector2> has type",
        has_scalar_type<asc::scalar_type<volatile CustomVector2>>::value);
    expect_true("scalar_type<const volatile CustomVector2> has type",
        has_scalar_type<asc::scalar_type<const volatile CustomVector2>>::value);

    static_assert(std::is_same<asc::scalar_type_t<CustomVector2>, float>::value, "");
    static_assert(std::is_same<asc::scalar_type_t<const CustomVector2>, float>::value, "");
    static_assert(std::is_same<asc::scalar_type_t<volatile CustomVector2>, float>::value, "");
    static_assert(std::is_same<asc::scalar_type_t<const volatile CustomVector2>, float>::value, "");

    return g_failures == 0 ? 0 : 1;
}
