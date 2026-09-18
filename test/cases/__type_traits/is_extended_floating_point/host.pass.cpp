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

#include <asc/std/__type_traits/is_extended_floating_point.h>
#include <iostream>

static int g_failures = 0;

static void expect_eq(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_extended_floating_point] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void test_standard_floating_point_types()
{
    // Standard floating point types are NOT "extended"
    expect_eq("__is_extended_floating_point_v<float>", asc::std::__is_extended_floating_point_v<float>, false);
    expect_eq("__is_extended_floating_point_v<double>", asc::std::__is_extended_floating_point_v<double>, false);
    expect_eq(
        "__is_extended_floating_point_v<long double>", asc::std::__is_extended_floating_point_v<long double>, false);
}

static void test_non_floating_point_types()
{
    // Non-floating-point types
    expect_eq("__is_extended_floating_point_v<int>", asc::std::__is_extended_floating_point_v<int>, false);
    expect_eq("__is_extended_floating_point_v<char>", asc::std::__is_extended_floating_point_v<char>, false);
    expect_eq("__is_extended_floating_point_v<bool>", asc::std::__is_extended_floating_point_v<bool>, false);
    expect_eq("__is_extended_floating_point_v<unsigned long long>",
        asc::std::__is_extended_floating_point_v<unsigned long long>, false);
}

static void test_qualified_variants_via_extended()
{
    // CV-qualified variants via __is_cv_extended_floating_point_v (should strip CV and still be false for standard
    // types)
    expect_eq("__is_cv_extended_floating_point_v<const float>",
        asc::std::__is_cv_extended_floating_point_v<const float>, false);
    expect_eq("__is_cv_extended_floating_point_v<volatile double>",
        asc::std::__is_cv_extended_floating_point_v<volatile double>, false);
    expect_eq("__is_cv_extended_floating_point_v<const volatile int>",
        asc::std::__is_cv_extended_floating_point_v<const volatile int>, false);
}

static void test_float128_extended_available_host()
{
    // __float128 (extended) — available on host with GCC on Linux x86_64
#if CANN_ASC_STL_DETAIL_HAS_FLOAT128()
    expect_eq("__is_extended_floating_point_v<__float128>", asc::std::__is_extended_floating_point_v<__float128>, true);
    expect_eq("__is_cv_extended_floating_point_v<const __float128>",
        asc::std::__is_cv_extended_floating_point_v<const __float128>, true);
    expect_eq("__is_cv_extended_floating_point_v<volatile __float128>",
        asc::std::__is_cv_extended_floating_point_v<volatile __float128>, true);
#else
    std::cout << "[host][is_extended_floating_point] __float128 not available, skipping" << std::endl;
#endif
}

static void test_half_extended_device_type()
{
    // half (extended) — device-only type
#if CANN_ASC_STL_DETAIL_HAS_HALF()
    expect_eq("__is_extended_floating_point_v<half>", asc::std::__is_extended_floating_point_v<half>, true);
    expect_eq(
        "__is_cv_extended_floating_point_v<const half>", asc::std::__is_cv_extended_floating_point_v<const half>, true);
#else
    std::cout << "[host][is_extended_floating_point] half not available, skipping" << std::endl;
#endif
}

static void test_bfloat16_extended_device_type()
{
    // bfloat16_t (extended) — device-only type
#if CANN_ASC_STL_DETAIL_HAS_BFLOAT16()
    expect_eq("__is_extended_floating_point_v<bfloat16_t>", asc::std::__is_extended_floating_point_v<bfloat16_t>, true);
    expect_eq("__is_cv_extended_floating_point_v<volatile bfloat16_t>",
        asc::std::__is_cv_extended_floating_point_v<volatile bfloat16_t>, true);
#else
    std::cout << "[host][is_extended_floating_point] bfloat16_t not available, skipping" << std::endl;
#endif
}

static void test_float8_e4m3_extended_device()
{
    // float8_e4m3_t (extended) — device-only type on C310
#if CANN_ASC_STL_DETAIL_HAS_FP8_E4M3()
    expect_eq(
        "__is_extended_floating_point_v<float8_e4m3_t>", asc::std::__is_extended_floating_point_v<float8_e4m3_t>, true);
    expect_eq("__is_cv_extended_floating_point_v<const float8_e4m3_t>",
        asc::std::__is_cv_extended_floating_point_v<const float8_e4m3_t>, true);
#else
    std::cout << "[host][is_extended_floating_point] float8_e4m3_t not available, skipping" << std::endl;
#endif
}

static void test_float8_e5m2_extended_device()
{
    // float8_e5m2_t (extended) — device-only type on C310
#if CANN_ASC_STL_DETAIL_HAS_FP8_E5M2()
    expect_eq(
        "__is_extended_floating_point_v<float8_e5m2_t>", asc::std::__is_extended_floating_point_v<float8_e5m2_t>, true);
    expect_eq("__is_cv_extended_floating_point_v<const float8_e5m2_t>",
        asc::std::__is_cv_extended_floating_point_v<const float8_e5m2_t>, true);
#else
    std::cout << "[host][is_extended_floating_point] float8_e5m2_t not available, skipping" << std::endl;
#endif
}

static void test_float8_e8m0_extended_device()
{
    // float8_e8m0_t (extended) - device-only scalar type on C310 mixed CCE
#if CANN_ASC_STL_DETAIL_HAS_FP8_E8M0()
    expect_eq(
        "__is_extended_floating_point_v<float8_e8m0_t>", asc::std::__is_extended_floating_point_v<float8_e8m0_t>, true);
    expect_eq("__is_cv_extended_floating_point_v<const float8_e8m0_t>",
        asc::std::__is_cv_extended_floating_point_v<const float8_e8m0_t>, true);
#else
    std::cout << "[host][is_extended_floating_point] float8_e8m0_t not available, skipping" << std::endl;
#endif
}

int main()
{
    test_standard_floating_point_types();
    test_non_floating_point_types();
    test_qualified_variants_via_extended();
    test_float128_extended_available_host();
    test_half_extended_device_type();
    test_bfloat16_extended_device_type();
    test_float8_e4m3_extended_device();
    test_float8_e5m2_extended_device();
    test_float8_e8m0_extended_device();

    return g_failures == 0 ? 0 : 1;
}
