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

#include <asc/__type_traits/vector_type.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][vector_type] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][vector_type] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

static void test_has_vector_type_unsupported_sizes()
{
    // === Test primary template: sizes 1 and 3 are never specialized in ASCL ===
    expect_true("is_same_v<vector_type_t<int, 1>, void>", asc::std::is_same_v<asc::vector_type_t<int, 1>, void>);
    expect_true("is_same_v<vector_type_t<int, 3>, void>", asc::std::is_same_v<asc::vector_type_t<int, 3>, void>);
    expect_true("is_same_v<vector_type_t<float, 1>, void>", asc::std::is_same_v<asc::vector_type_t<float, 1>, void>);
    expect_true("is_same_v<vector_type_t<float, 3>, void>", asc::std::is_same_v<asc::vector_type_t<float, 3>, void>);
    expect_true("is_same_v<vector_type_t<signed char, 1>, void>",
        asc::std::is_same_v<asc::vector_type_t<signed char, 1>, void>);
    expect_true("is_same_v<vector_type_t<signed char, 3>, void>",
        asc::std::is_same_v<asc::vector_type_t<signed char, 3>, void>);
    expect_true(
        "is_same_v<vector_type_t<unsigned, 1>, void>", asc::std::is_same_v<asc::vector_type_t<unsigned, 1>, void>);
    expect_true(
        "is_same_v<vector_type_t<unsigned, 3>, void>", asc::std::is_same_v<asc::vector_type_t<unsigned, 3>, void>);
    expect_true(
        "is_same_v<vector_type_t<long long, 1>, void>", asc::std::is_same_v<asc::vector_type_t<long long, 1>, void>);
    expect_true(
        "is_same_v<vector_type_t<long long, 3>, void>", asc::std::is_same_v<asc::vector_type_t<long long, 3>, void>);
    // === Test has_vector_type_v for unsupported sizes (1, 3) ===
    expect_false("has_vector_type_v<int, 1>", asc::has_vector_type_v<int, 1>);
    expect_false("has_vector_type_v<int, 3>", asc::has_vector_type_v<int, 3>);
    expect_false("has_vector_type_v<float, 1>", asc::has_vector_type_v<float, 1>);
    expect_false("has_vector_type_v<float, 3>", asc::has_vector_type_v<float, 3>);
    expect_false("has_vector_type_v<signed char, 1>", asc::has_vector_type_v<signed char, 1>);
    expect_false("has_vector_type_v<signed char, 3>", asc::has_vector_type_v<signed char, 3>);
    expect_false("has_vector_type_v<unsigned, 1>", asc::has_vector_type_v<unsigned, 1>);
    expect_false("has_vector_type_v<unsigned, 3>", asc::has_vector_type_v<unsigned, 3>);
    expect_false("has_vector_type_v<long long, 1>", asc::has_vector_type_v<long long, 1>);
    expect_false("has_vector_type_v<long long, 3>", asc::has_vector_type_v<long long, 3>);
    // === Test has_vector_type type alias for unsupported sizes ===
    expect_true("has_vector_type<int,1> is false_type",
        asc::std::is_same_v<asc::has_vector_type<int, 1>, asc::std::false_type>);
    expect_true("has_vector_type<float,3> is false_type",
        asc::std::is_same_v<asc::has_vector_type<float, 3>, asc::std::false_type>);
    expect_true("has_vector_type<long long,1> is false_type",
        asc::std::is_same_v<asc::has_vector_type<long long, 1>, asc::std::false_type>);
}

static void test_section0()
{
#if CANN_ASC_STL_DETAIL_HAS_SIMT_VECTOR_TYPES()
    std::cout << "[host][vector_type] SIMT vector types are available" << std::endl;
#else
    std::cout << "[host][vector_type] SIMT vector types NOT available (host mode)" << std::endl;
#endif
}

static void test_vector_type_size2()
{
#if CANN_ASC_STL_DETAIL_HAS_SIMT_VECTOR_TYPES()
    // === Test vector_type_t mappings for size 2 ===
    expect_true("is_same_v<vector_type_t<signed char, 2>, char2>",
        asc::std::is_same_v<asc::vector_type_t<signed char, 2>, ::char2>);
    expect_true("is_same_v<vector_type_t<unsigned char, 2>, uchar2>",
        asc::std::is_same_v<asc::vector_type_t<unsigned char, 2>, ::uchar2>);
    expect_true(
        "is_same_v<vector_type_t<short, 2>, short2>", asc::std::is_same_v<asc::vector_type_t<short, 2>, ::short2>);
    expect_true("is_same_v<vector_type_t<unsigned short, 2>, ushort2>",
        asc::std::is_same_v<asc::vector_type_t<unsigned short, 2>, ::ushort2>);
    expect_true("is_same_v<vector_type_t<int, 2>, int2>", asc::std::is_same_v<asc::vector_type_t<int, 2>, ::int2>);
    expect_true(
        "is_same_v<vector_type_t<unsigned, 2>, uint2>", asc::std::is_same_v<asc::vector_type_t<unsigned, 2>, ::uint2>);
    expect_true("is_same_v<vector_type_t<long, 2>, long2>", asc::std::is_same_v<asc::vector_type_t<long, 2>, ::long2>);
    expect_true("is_same_v<vector_type_t<unsigned long, 2>, ulong2>",
        asc::std::is_same_v<asc::vector_type_t<unsigned long, 2>, ::ulong2>);
    expect_true("is_same_v<vector_type_t<long long, 2>, longlong2>",
        asc::std::is_same_v<asc::vector_type_t<long long, 2>, ::longlong2>);
    expect_true("is_same_v<vector_type_t<unsigned long long, 2>, ulonglong2>",
        asc::std::is_same_v<asc::vector_type_t<unsigned long long, 2>, ::ulonglong2>);
    expect_true(
        "is_same_v<vector_type_t<float, 2>, float2>", asc::std::is_same_v<asc::vector_type_t<float, 2>, ::float2>);
#else
    std::cout << "[host][vector_type] SIMT vector types NOT available (host mode)" << std::endl;
#endif
}

static void test_vector_type_size4()
{
#if CANN_ASC_STL_DETAIL_HAS_SIMT_VECTOR_TYPES()
    // === Test vector_type_t mappings for size 4 ===
    expect_true("is_same_v<vector_type_t<signed char, 4>, char4>",
        asc::std::is_same_v<asc::vector_type_t<signed char, 4>, ::char4>);
    expect_true("is_same_v<vector_type_t<unsigned char, 4>, uchar4>",
        asc::std::is_same_v<asc::vector_type_t<unsigned char, 4>, ::uchar4>);
    expect_true(
        "is_same_v<vector_type_t<short, 4>, short4>", asc::std::is_same_v<asc::vector_type_t<short, 4>, ::short4>);
    expect_true("is_same_v<vector_type_t<unsigned short, 4>, ushort4>",
        asc::std::is_same_v<asc::vector_type_t<unsigned short, 4>, ::ushort4>);
    expect_true("is_same_v<vector_type_t<int, 4>, int4>", asc::std::is_same_v<asc::vector_type_t<int, 4>, ::int4>);
    expect_true(
        "is_same_v<vector_type_t<unsigned, 4>, uint4>", asc::std::is_same_v<asc::vector_type_t<unsigned, 4>, ::uint4>);
    expect_true("is_same_v<vector_type_t<long, 4>, long4>", asc::std::is_same_v<asc::vector_type_t<long, 4>, ::long4>);
    expect_true("is_same_v<vector_type_t<unsigned long, 4>, ulong4>",
        asc::std::is_same_v<asc::vector_type_t<unsigned long, 4>, ::ulong4>);
    expect_true("is_same_v<vector_type_t<long long, 4>, longlong4>",
        asc::std::is_same_v<asc::vector_type_t<long long, 4>, ::longlong4>);
    expect_true("is_same_v<vector_type_t<unsigned long long, 4>, ulonglong4>",
        asc::std::is_same_v<asc::vector_type_t<unsigned long long, 4>, ::ulonglong4>);
    expect_true(
        "is_same_v<vector_type_t<float, 4>, float4>", asc::std::is_same_v<asc::vector_type_t<float, 4>, ::float4>);
#else
    std::cout << "[host][vector_type] SIMT vector types NOT available (host mode)" << std::endl;
#endif
}

static void test_has_vector_type_probe()
{
#if CANN_ASC_STL_DETAIL_HAS_SIMT_VECTOR_TYPES()
    // === Test has_vector_type_v is true for supported (type, size) pairs ===
    expect_true("has_vector_type_v<signed char, 2>", asc::has_vector_type_v<signed char, 2>);
    expect_true("has_vector_type_v<signed char, 4>", asc::has_vector_type_v<signed char, 4>);
    expect_true("has_vector_type_v<unsigned char, 2>", asc::has_vector_type_v<unsigned char, 2>);
    expect_true("has_vector_type_v<unsigned char, 4>", asc::has_vector_type_v<unsigned char, 4>);
    expect_true("has_vector_type_v<short, 2>", asc::has_vector_type_v<short, 2>);
    expect_true("has_vector_type_v<short, 4>", asc::has_vector_type_v<short, 4>);
    expect_true("has_vector_type_v<unsigned short, 2>", asc::has_vector_type_v<unsigned short, 2>);
    expect_true("has_vector_type_v<unsigned short, 4>", asc::has_vector_type_v<unsigned short, 4>);
    expect_true("has_vector_type_v<int, 2>", asc::has_vector_type_v<int, 2>);
    expect_true("has_vector_type_v<int, 4>", asc::has_vector_type_v<int, 4>);
    expect_true("has_vector_type_v<unsigned, 2>", asc::has_vector_type_v<unsigned, 2>);
    expect_true("has_vector_type_v<unsigned, 4>", asc::has_vector_type_v<unsigned, 4>);
    expect_true("has_vector_type_v<long, 2>", asc::has_vector_type_v<long, 2>);
    expect_true("has_vector_type_v<long, 4>", asc::has_vector_type_v<long, 4>);
    expect_true("has_vector_type_v<unsigned long, 2>", asc::has_vector_type_v<unsigned long, 2>);
    expect_true("has_vector_type_v<unsigned long, 4>", asc::has_vector_type_v<unsigned long, 4>);
    expect_true("has_vector_type_v<long long, 2>", asc::has_vector_type_v<long long, 2>);
    expect_true("has_vector_type_v<long long, 4>", asc::has_vector_type_v<long long, 4>);
    expect_true("has_vector_type_v<unsigned long long, 2>", asc::has_vector_type_v<unsigned long long, 2>);
    expect_true("has_vector_type_v<unsigned long long, 4>", asc::has_vector_type_v<unsigned long long, 4>);
    expect_true("has_vector_type_v<float, 2>", asc::has_vector_type_v<float, 2>);
    expect_true("has_vector_type_v<float, 4>", asc::has_vector_type_v<float, 4>);
#else
    std::cout << "[host][vector_type] SIMT vector types NOT available (host mode)" << std::endl;
#endif
}

static void test_has_vector_type_probe_2()
{
#if CANN_ASC_STL_DETAIL_HAS_SIMT_VECTOR_TYPES()
    // === Test has_vector_type is true_type for supported types ===
    expect_true(
        "has_vector_type<int,2> is true_type", asc::std::is_same_v<asc::has_vector_type<int, 2>, asc::std::true_type>);
    expect_true("has_vector_type<float,4> is true_type",
        asc::std::is_same_v<asc::has_vector_type<float, 4>, asc::std::true_type>);
    expect_true("has_vector_type<long long,2> is true_type",
        asc::std::is_same_v<asc::has_vector_type<long long, 2>, asc::std::true_type>);
    expect_true("has_vector_type<unsigned,4> is true_type",
        asc::std::is_same_v<asc::has_vector_type<unsigned, 4>, asc::std::true_type>);
#else
    std::cout << "[host][vector_type] SIMT vector types NOT available (host mode)" << std::endl;
#endif
}

static void test_vector_type_size2_2()
{
#if CANN_ASC_STL_DETAIL_HAS_SIMT_VECTOR_TYPES()
    // === Without SIMT vector types, sizes 2 and 4 also yield void ===
    expect_true("is_same_v<vector_type_t<int, 2>, void>", asc::std::is_same_v<asc::vector_type_t<int, 2>, void>);
    expect_true("is_same_v<vector_type_t<int, 4>, void>", asc::std::is_same_v<asc::vector_type_t<int, 4>, void>);
    expect_true("is_same_v<vector_type_t<float, 2>, void>", asc::std::is_same_v<asc::vector_type_t<float, 2>, void>);
    expect_true("is_same_v<vector_type_t<float, 4>, void>", asc::std::is_same_v<asc::vector_type_t<float, 4>, void>);
    expect_true("is_same_v<vector_type_t<signed char, 2>, void>",
        asc::std::is_same_v<asc::vector_type_t<signed char, 2>, void>);
    expect_true("is_same_v<vector_type_t<signed char, 4>, void>",
        asc::std::is_same_v<asc::vector_type_t<signed char, 4>, void>);
    expect_true("is_same_v<vector_type_t<unsigned char, 2>, void>",
        asc::std::is_same_v<asc::vector_type_t<unsigned char, 2>, void>);
    expect_true("is_same_v<vector_type_t<unsigned char, 4>, void>",
        asc::std::is_same_v<asc::vector_type_t<unsigned char, 4>, void>);
    expect_true("is_same_v<vector_type_t<short, 2>, void>", asc::std::is_same_v<asc::vector_type_t<short, 2>, void>);
    expect_true("is_same_v<vector_type_t<short, 4>, void>", asc::std::is_same_v<asc::vector_type_t<short, 4>, void>);
    expect_true("is_same_v<vector_type_t<unsigned short, 2>, void>",
        asc::std::is_same_v<asc::vector_type_t<unsigned short, 2>, void>);
    expect_true("is_same_v<vector_type_t<unsigned short, 4>, void>",
        asc::std::is_same_v<asc::vector_type_t<unsigned short, 4>, void>);
    expect_true(
        "is_same_v<vector_type_t<unsigned, 2>, void>", asc::std::is_same_v<asc::vector_type_t<unsigned, 2>, void>);
    expect_true(
        "is_same_v<vector_type_t<unsigned, 4>, void>", asc::std::is_same_v<asc::vector_type_t<unsigned, 4>, void>);
    expect_true("is_same_v<vector_type_t<long, 2>, void>", asc::std::is_same_v<asc::vector_type_t<long, 2>, void>);
    expect_true("is_same_v<vector_type_t<long, 4>, void>", asc::std::is_same_v<asc::vector_type_t<long, 4>, void>);
    expect_true("is_same_v<vector_type_t<unsigned long, 2>, void>",
        asc::std::is_same_v<asc::vector_type_t<unsigned long, 2>, void>);
    expect_true("is_same_v<vector_type_t<unsigned long, 4>, void>",
        asc::std::is_same_v<asc::vector_type_t<unsigned long, 4>, void>);
    expect_true(
        "is_same_v<vector_type_t<long long, 2>, void>", asc::std::is_same_v<asc::vector_type_t<long long, 2>, void>);
    expect_true(
        "is_same_v<vector_type_t<long long, 4>, void>", asc::std::is_same_v<asc::vector_type_t<long long, 4>, void>);
    expect_true("is_same_v<vector_type_t<unsigned long long, 2>, void>",
        asc::std::is_same_v<asc::vector_type_t<unsigned long long, 2>, void>);
    expect_true("is_same_v<vector_type_t<unsigned long long, 4>, void>",
        asc::std::is_same_v<asc::vector_type_t<unsigned long long, 4>, void>);
#else
    std::cout << "[host][vector_type] SIMT vector types NOT available (host mode)" << std::endl;
#endif
}

static void test_has_vector_type_probe_3()
{
#if CANN_ASC_STL_DETAIL_HAS_SIMT_VECTOR_TYPES()
    // === has_vector_type_v is false for all types/sizes on host ===
    expect_false("has_vector_type_v<int, 2>", asc::has_vector_type_v<int, 2>);
    expect_false("has_vector_type_v<int, 4>", asc::has_vector_type_v<int, 4>);
    expect_false("has_vector_type_v<float, 2>", asc::has_vector_type_v<float, 2>);
    expect_false("has_vector_type_v<float, 4>", asc::has_vector_type_v<float, 4>);
    expect_false("has_vector_type_v<signed char, 2>", asc::has_vector_type_v<signed char, 2>);
    expect_false("has_vector_type_v<signed char, 4>", asc::has_vector_type_v<signed char, 4>);
    expect_false("has_vector_type_v<unsigned char, 2>", asc::has_vector_type_v<unsigned char, 2>);
    expect_false("has_vector_type_v<unsigned char, 4>", asc::has_vector_type_v<unsigned char, 4>);
    expect_false("has_vector_type_v<short, 2>", asc::has_vector_type_v<short, 2>);
    expect_false("has_vector_type_v<short, 4>", asc::has_vector_type_v<short, 4>);
    expect_false("has_vector_type_v<unsigned short, 2>", asc::has_vector_type_v<unsigned short, 2>);
    expect_false("has_vector_type_v<unsigned short, 4>", asc::has_vector_type_v<unsigned short, 4>);
    expect_false("has_vector_type_v<unsigned, 2>", asc::has_vector_type_v<unsigned, 2>);
    expect_false("has_vector_type_v<unsigned, 4>", asc::has_vector_type_v<unsigned, 4>);
    expect_false("has_vector_type_v<long, 2>", asc::has_vector_type_v<long, 2>);
    expect_false("has_vector_type_v<long, 4>", asc::has_vector_type_v<long, 4>);
    expect_false("has_vector_type_v<unsigned long, 2>", asc::has_vector_type_v<unsigned long, 2>);
    expect_false("has_vector_type_v<unsigned long, 4>", asc::has_vector_type_v<unsigned long, 4>);
    expect_false("has_vector_type_v<long long, 2>", asc::has_vector_type_v<long long, 2>);
    expect_false("has_vector_type_v<long long, 4>", asc::has_vector_type_v<long long, 4>);
    expect_false("has_vector_type_v<unsigned long long, 2>", asc::has_vector_type_v<unsigned long long, 2>);
    expect_false("has_vector_type_v<unsigned long long, 4>", asc::has_vector_type_v<unsigned long long, 4>);
#else
    std::cout << "[host][vector_type] SIMT vector types NOT available (host mode)" << std::endl;
#endif
}

static void test_has_vector_type_probe_4()
{
#if CANN_ASC_STL_DETAIL_HAS_SIMT_VECTOR_TYPES()
    // === has_vector_type is false_type for all on host ===
    expect_true("has_vector_type<int,2> is false_type",
        asc::std::is_same_v<asc::has_vector_type<int, 2>, asc::std::false_type>);
    expect_true("has_vector_type<float,4> is false_type",
        asc::std::is_same_v<asc::has_vector_type<float, 4>, asc::std::false_type>);
    expect_true("has_vector_type<long long,2> is false_type",
        asc::std::is_same_v<asc::has_vector_type<long long, 2>, asc::std::false_type>);
    expect_true("has_vector_type<unsigned,4> is false_type",
        asc::std::is_same_v<asc::has_vector_type<unsigned, 4>, asc::std::false_type>);
#else
    std::cout << "[host][vector_type] SIMT vector types NOT available (host mode)" << std::endl;
#endif
}

int main()
{
    test_has_vector_type_unsupported_sizes();
    test_section0();
    test_vector_type_size2();
    test_vector_type_size4();
    test_has_vector_type_probe();
    test_has_vector_type_probe_2();
    test_vector_type_size2_2();
    test_has_vector_type_probe_3();
    test_has_vector_type_probe_4();

    return g_failures == 0 ? 0 : 1;
}
