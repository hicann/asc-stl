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

#include <asc/std/__asc/extended_data_types.h>
#include <iostream>

static int g_failures = 0;

static void expect_eq(const char* expr, int got, int expected)
{
    bool ok = (got == expected);
    std::cout << "[host][extended_data_types] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // __int128 detection
#if defined(__SIZEOF_INT128__)
    expect_eq("CANN_ASC_STL_DETAIL_HAS_INT128()", CANN_ASC_STL_DETAIL_HAS_INT128(), 1);
#else
    expect_eq("CANN_ASC_STL_DETAIL_HAS_INT128()", CANN_ASC_STL_DETAIL_HAS_INT128(), 0);
#endif

    // Device-specific types should not be available on host
    expect_eq("CANN_ASC_STL_DETAIL_HAS_HALF()", CANN_ASC_STL_DETAIL_HAS_HALF(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_HAS_HALF2()", CANN_ASC_STL_DETAIL_HAS_HALF2(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_HAS_BFLOAT16()", CANN_ASC_STL_DETAIL_HAS_BFLOAT16(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_HAS_BFLOAT16X2()", CANN_ASC_STL_DETAIL_HAS_BFLOAT16X2(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_HAS_FP8_E4M3()", CANN_ASC_STL_DETAIL_HAS_FP8_E4M3(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_HAS_FP8_E5M2()", CANN_ASC_STL_DETAIL_HAS_FP8_E5M2(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_HAS_FP8_E4M3X2()", CANN_ASC_STL_DETAIL_HAS_FP8_E4M3X2(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_HAS_FP8_E5M2X2()", CANN_ASC_STL_DETAIL_HAS_FP8_E5M2X2(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_HAS_FP4_E2M1X2()", CANN_ASC_STL_DETAIL_HAS_FP4_E2M1X2(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_HAS_FP16()", CANN_ASC_STL_DETAIL_HAS_FP16(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_HAS_BF16()", CANN_ASC_STL_DETAIL_HAS_BF16(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_HAS_FP8()", CANN_ASC_STL_DETAIL_HAS_FP8(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_HAS_FP4()", CANN_ASC_STL_DETAIL_HAS_FP4(), 0);

    // Formats without an AscendC scalar/vector equivalent stay unavailable in this base layer.
    expect_eq("CANN_ASC_STL_DETAIL_HAS_FP8_E8M0()", CANN_ASC_STL_DETAIL_HAS_FP8_E8M0(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_HAS_FP8_E8M0X2()", CANN_ASC_STL_DETAIL_HAS_FP8_E8M0X2(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_HAS_FP8_E8M0X4()", CANN_ASC_STL_DETAIL_HAS_FP8_E8M0X4(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_HAS_FP8_E4M3X4()", CANN_ASC_STL_DETAIL_HAS_FP8_E4M3X4(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_HAS_FP8_E5M2X4()", CANN_ASC_STL_DETAIL_HAS_FP8_E5M2X4(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_HAS_FP6_E2M3()", CANN_ASC_STL_DETAIL_HAS_FP6_E2M3(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_HAS_FP6_E3M2()", CANN_ASC_STL_DETAIL_HAS_FP6_E3M2(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_HAS_FP6_E2M3X2()", CANN_ASC_STL_DETAIL_HAS_FP6_E2M3X2(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_HAS_FP6_E3M2X2()", CANN_ASC_STL_DETAIL_HAS_FP6_E3M2X2(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_HAS_FP6_E2M3X4()", CANN_ASC_STL_DETAIL_HAS_FP6_E2M3X4(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_HAS_FP6_E3M2X4()", CANN_ASC_STL_DETAIL_HAS_FP6_E3M2X4(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_HAS_FP4_E2M1()", CANN_ASC_STL_DETAIL_HAS_FP4_E2M1(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_HAS_FP4_E2M1X4()", CANN_ASC_STL_DETAIL_HAS_FP4_E2M1X4(), 0);

    // __float128 detection
#if (defined(__SIZEOF_FLOAT128__) || defined(__FLOAT128__)) && \
    !(defined(__STRICT_ANSI__) && defined(__GNUC__) && !defined(ASC_GCC_HAS_EXTENDED_NUMERIC_LITERALS))
    expect_eq("CANN_ASC_STL_DETAIL_HAS_FLOAT128()", CANN_ASC_STL_DETAIL_HAS_FLOAT128(), 1);
#else
    expect_eq("CANN_ASC_STL_DETAIL_HAS_FLOAT128()", CANN_ASC_STL_DETAIL_HAS_FLOAT128(), 0);
#endif

    return g_failures == 0 ? 0 : 1;
}
