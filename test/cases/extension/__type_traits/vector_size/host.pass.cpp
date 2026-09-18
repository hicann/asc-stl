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

// Same-spelling Host stand-ins must not activate Device-only specializations.
// Native mixed/pure C310 types are covered by the Bisheng compile tests.
struct int2 {};
struct float2 {};
struct dim3 {};

#include <asc/__type_traits/vector_size.h>
#include <iostream>
#include <cstddef>

#ifndef CANN_ASC_STL_DETAIL_HAS_HALF2
#define CANN_ASC_STL_DETAIL_HAS_HALF2() 0
#endif
#ifndef CANN_ASC_STL_DETAIL_HAS_BFLOAT16X2
#define CANN_ASC_STL_DETAIL_HAS_BFLOAT16X2() 0
#endif
#ifndef CANN_ASC_STL_DETAIL_HAS_FP8_E4M3X2
#define CANN_ASC_STL_DETAIL_HAS_FP8_E4M3X2() 0
#endif
#ifndef CANN_ASC_STL_DETAIL_HAS_FP8_E5M2X2
#define CANN_ASC_STL_DETAIL_HAS_FP8_E5M2X2() 0
#endif
#ifndef CANN_ASC_STL_DETAIL_ACCL_HAS_FP4_E2M1X2
#define CANN_ASC_STL_DETAIL_ACCL_HAS_FP4_E2M1X2() 0
#endif

static int g_failures = 0;

static void expect_eq(const char* expr, std::size_t got, std::size_t expected)
{
    bool ok = (got == expected);
    std::cout << "[host][vector_size] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // Non-vector types should be 0
    expect_eq("vector_size_v<int>", asc::vector_size_v<int>, 0);
    expect_eq("vector_size_v<float>", asc::vector_size_v<float>, 0);
    expect_eq("vector_size_v<double>", asc::vector_size_v<double>, 0);
    expect_eq("vector_size_v<char>", asc::vector_size_v<char>, 0);
    expect_eq("vector_size_v<long>", asc::vector_size_v<long>, 0);
    expect_eq("vector_size_v<unsigned>", asc::vector_size_v<unsigned>, 0);

    // Host types do not acquire CCE vector semantics from their spelling.
    expect_eq("vector_size_v<int2>", asc::vector_size_v<int2>, 0);
    expect_eq("vector_size_v<float2>", asc::vector_size_v<float2>, 0);
    expect_eq("vector_size_v<dim3>", asc::vector_size_v<dim3>, 0);

    // const/volatile/const volatile variants (cv-qualifier forwarding)
    expect_eq("vector_size_v<const float2>", asc::vector_size_v<const float2>, 0);
    expect_eq("vector_size_v<volatile int2>", asc::vector_size_v<volatile int2>, 0);
    expect_eq("vector_size_v<const dim3>", asc::vector_size_v<const dim3>, 0);

    // const/volatile non-vector types (should still be 0)
    expect_eq("vector_size_v<const int>", asc::vector_size_v<const int>, 0);
    expect_eq("vector_size_v<volatile double>", asc::vector_size_v<volatile double>, 0);
    expect_eq("vector_size_v<const volatile float>", asc::vector_size_v<const volatile float>, 0);

    // vector_size type alias (integral_constant)
    expect_eq("vector_size<float2>::value", asc::vector_size<float2>::value, 0);
    expect_eq("vector_size<int2>::value", asc::vector_size<int2>::value, 0);
    expect_eq("vector_size<int>::value", asc::vector_size<int>::value, 0);
    expect_eq("vector_size<dim3>::value", asc::vector_size<dim3>::value, 0);

    // vector_size as callable (operator())
    asc::vector_size<float2> vs_callable;
    expect_eq("vector_size<float2>()()", vs_callable(), 0);

    // Conditional types
#if CANN_ASC_STL_DETAIL_HAS_HALF2()
    expect_eq("vector_size_v<half2>", asc::vector_size_v<half2>, 2);
#endif

#if CANN_ASC_STL_DETAIL_HAS_BFLOAT16X2()
    expect_eq("vector_size_v<bfloat16x2_t>", asc::vector_size_v<bfloat16x2_t>, 2);
#endif

    return g_failures == 0 ? 0 : 1;
}
