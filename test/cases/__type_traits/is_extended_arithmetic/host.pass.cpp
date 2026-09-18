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

#include <asc/std/__type_traits/is_extended_arithmetic.h>
#include <iostream>

static int g_failures = 0;

static void expect_eq(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_extended_arithmetic] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

struct MyStruct {};

static void test_standard_integral_types_arithmetic()
{
    // Standard integral types — is_arithmetic_v is true, so __is_extended_arithmetic_v is true
    expect_eq("__is_extended_arithmetic_v<bool>", asc::std::__is_extended_arithmetic_v<bool>, true);
    expect_eq("__is_extended_arithmetic_v<char>", asc::std::__is_extended_arithmetic_v<char>, true);
    expect_eq("__is_extended_arithmetic_v<signed char>", asc::std::__is_extended_arithmetic_v<signed char>, true);
    expect_eq("__is_extended_arithmetic_v<unsigned char>", asc::std::__is_extended_arithmetic_v<unsigned char>, true);
    expect_eq("__is_extended_arithmetic_v<short>", asc::std::__is_extended_arithmetic_v<short>, true);
    expect_eq("__is_extended_arithmetic_v<unsigned short>", asc::std::__is_extended_arithmetic_v<unsigned short>, true);
    expect_eq("__is_extended_arithmetic_v<int>", asc::std::__is_extended_arithmetic_v<int>, true);
    expect_eq("__is_extended_arithmetic_v<unsigned int>", asc::std::__is_extended_arithmetic_v<unsigned int>, true);
    expect_eq("__is_extended_arithmetic_v<long>", asc::std::__is_extended_arithmetic_v<long>, true);
    expect_eq("__is_extended_arithmetic_v<unsigned long>", asc::std::__is_extended_arithmetic_v<unsigned long>, true);
    expect_eq("__is_extended_arithmetic_v<long long>", asc::std::__is_extended_arithmetic_v<long long>, true);
    expect_eq("__is_extended_arithmetic_v<unsigned long long>",
        asc::std::__is_extended_arithmetic_v<unsigned long long>, true);
}

static void test_standard_floating_point_types()
{
    // Standard floating-point types — is_arithmetic_v is true
    expect_eq("__is_extended_arithmetic_v<float>", asc::std::__is_extended_arithmetic_v<float>, true);
    expect_eq("__is_extended_arithmetic_v<double>", asc::std::__is_extended_arithmetic_v<double>, true);
    expect_eq("__is_extended_arithmetic_v<long double>", asc::std::__is_extended_arithmetic_v<long double>, true);
}

static void test_qualified_standard_arithmetic_types()
{
    // CV-qualified standard arithmetic types — is_arithmetic_v handles CV
    expect_eq("__is_extended_arithmetic_v<const int>", asc::std::__is_extended_arithmetic_v<const int>, true);
    expect_eq("__is_extended_arithmetic_v<volatile float>", asc::std::__is_extended_arithmetic_v<volatile float>, true);
    expect_eq("__is_extended_arithmetic_v<const volatile double>",
        asc::std::__is_extended_arithmetic_v<const volatile double>, true);
}

static void test_non_arithmetic_types_false()
{
    // Non-arithmetic types — false
    expect_eq("__is_extended_arithmetic_v<void>", asc::std::__is_extended_arithmetic_v<void>, false);
    expect_eq("__is_extended_arithmetic_v<int*>", asc::std::__is_extended_arithmetic_v<int*>, false);
    expect_eq("__is_extended_arithmetic_v<MyStruct>", asc::std::__is_extended_arithmetic_v<MyStruct>, false);
}

static void test_extended_floating_point_types()
{
    // Extended floating-point types (when available) — true via __is_extended_floating_point_v
#if CANN_ASC_STL_DETAIL_HAS_HALF()
    expect_eq("__is_extended_arithmetic_v<half>", asc::std::__is_extended_arithmetic_v<half>, true);
#else
    std::cout << "[host][is_extended_arithmetic] half not available, skipping" << std::endl;
#endif

#if CANN_ASC_STL_DETAIL_HAS_BFLOAT16()
    expect_eq("__is_extended_arithmetic_v<bfloat16_t>", asc::std::__is_extended_arithmetic_v<bfloat16_t>, true);
#else
    std::cout << "[host][is_extended_arithmetic] bfloat16_t not available, skipping" << std::endl;
#endif

#if CANN_ASC_STL_DETAIL_HAS_FP8_E4M3()
    expect_eq("__is_extended_arithmetic_v<float8_e4m3_t>", asc::std::__is_extended_arithmetic_v<float8_e4m3_t>, true);
#else
    std::cout << "[host][is_extended_arithmetic] float8_e4m3_t not available, skipping" << std::endl;
#endif

#if CANN_ASC_STL_DETAIL_HAS_FP8_E5M2()
    expect_eq("__is_extended_arithmetic_v<float8_e5m2_t>", asc::std::__is_extended_arithmetic_v<float8_e5m2_t>, true);
#else
    std::cout << "[host][is_extended_arithmetic] float8_e5m2_t not available, skipping" << std::endl;
#endif

#if CANN_ASC_STL_DETAIL_HAS_FP8_E8M0()
    expect_eq("__is_extended_arithmetic_v<float8_e8m0_t>", asc::std::__is_extended_arithmetic_v<float8_e8m0_t>, true);
#else
    std::cout << "[host][is_extended_arithmetic] float8_e8m0_t not available, skipping" << std::endl;
#endif

#if CANN_ASC_STL_DETAIL_HAS_FLOAT128()
    expect_eq("__is_extended_arithmetic_v<__float128>", asc::std::__is_extended_arithmetic_v<__float128>, true);
#else
    std::cout << "[host][is_extended_arithmetic] __float128 not available, skipping" << std::endl;
#endif
}

int main()
{
    test_standard_integral_types_arithmetic();
    test_standard_floating_point_types();
    test_qualified_standard_arithmetic_types();
    test_non_arithmetic_types_false();
    test_extended_floating_point_types();

    return g_failures == 0 ? 0 : 1;
}
