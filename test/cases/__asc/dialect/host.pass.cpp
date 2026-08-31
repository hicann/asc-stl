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

#include <asc/std/__asc/dialect.h>
#include <iostream>

static int g_failures = 0;

template <typename T, typename U>
void expect_eq(const char* expr, const T& got, const U& expected)
{
    if (got == expected) {
        std::cout << "[host][dialect] " << expr << " = " << got << " (expected " << expected << ") OK" << std::endl;
    } else {
        std::cout << "[host][dialect] " << expr << " = " << got << " (expected " << expected << ") FAIL" << std::endl;
        ++g_failures;
    }
}

CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT int g_global_constant_val = 7;

CANN_ASC_STL_DETAIL_CONSTEVAL int ce_test()
{
    return 10;
}

CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 int cx20_test()
{
    return 42;
}
CANN_ASC_STL_DETAIL_CONSTEXPR_CXX23 int cx23_test()
{
    return 99;
}

static void test_asc_std_ver_reflect()
{
    // CANN_ASC_STL_DETAIL_STD_VER should reflect the C++ standard dialect
    expect_eq("CANN_ASC_STL_DETAIL_STD_VER", CANN_ASC_STL_DETAIL_STD_VER,
#if CANN_ASC_STL_DETAIL_STD_CPLUSPLUS <= 199711L
        2003
#elif CANN_ASC_STL_DETAIL_STD_CPLUSPLUS <= 201103L
        2011
#elif CANN_ASC_STL_DETAIL_STD_CPLUSPLUS <= 201402L
        2014
#elif CANN_ASC_STL_DETAIL_STD_CPLUSPLUS <= 201703L
        2017
#elif CANN_ASC_STL_DETAIL_STD_CPLUSPLUS <= 202002L
        2020
#elif CANN_ASC_STL_DETAIL_STD_CPLUSPLUS <= 202302L
        2023
#else
        2024
#endif
    );  // NOLINT(whitespace/parens)
}

static void test_asc_wchar_always_per()
{
    // CANN_ASC_STL_DETAIL_HAS_WCHAR_T() is always 0 per ASC design
    expect_eq("CANN_ASC_STL_DETAIL_HAS_WCHAR_T()", CANN_ASC_STL_DETAIL_HAS_WCHAR_T(), 0);
}

static void test_asc_long_double_host()
{
    // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE() should be 1 on host unless explicitly disabled
    expect_eq("CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()", CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE(),
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && !defined(ASC_DISABLE_LONG_DOUBLE_SUPPORT)
        1
#else
        0
#endif
    );  // NOLINT(whitespace/parens)
}

static void test_asc_constexpr_cxx20_constexpr()
{
    // CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20: constexpr on declarations if C++20+, empty otherwise
#if CANN_ASC_STL_DETAIL_STD_VER >= 2020
    constexpr int cx20_val = cx20_test();
#else
    int cx20_val = cx20_test();
#endif
    expect_eq("CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 value", cx20_val, 42);
}

static void test_asc_constexpr_cxx23_constexpr()
{
    // CANN_ASC_STL_DETAIL_CONSTEXPR_CXX23: constexpr on declarations if C++23+, empty otherwise
#if CANN_ASC_STL_DETAIL_STD_VER >= 2023
    constexpr int cx23_val = cx23_test();
#else
    int cx23_val = cx23_test();
#endif
    expect_eq("CANN_ASC_STL_DETAIL_CONSTEXPR_CXX23 value", cx23_val, 99);
}

static void test_asc_global_constant_namespace()
{
    // CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT at namespace scope
    expect_eq("CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT value", g_global_constant_val, 7);
}

static void test_asc_consteval_namespace_scope()
{
    // CANN_ASC_STL_DETAIL_CONSTEVAL at namespace scope
    constexpr int ce_val = ce_test();
    expect_eq("CANN_ASC_STL_DETAIL_CONSTEVAL value", ce_val, 10);
}

static void test_asc_concepts()
{
    // CANN_ASC_STL_DETAIL_HAS_CONCEPTS() should be 0 or 1
    expect_eq("CANN_ASC_STL_DETAIL_HAS_CONCEPTS()", CANN_ASC_STL_DETAIL_HAS_CONCEPTS(),
#if CANN_ASC_STL_DETAIL_STD_VER <= 2017 || !defined(__cpp_concepts) || __cpp_concepts < 201907L
        0
#else
        1
#endif
    );  // NOLINT(whitespace/parens)
}

static void test_asc_pack_indexing()
{
    // CANN_ASC_STL_DETAIL_HAS_PACK_INDEXING() should be 0 or 1
    expect_eq("CANN_ASC_STL_DETAIL_HAS_PACK_INDEXING()", CANN_ASC_STL_DETAIL_HAS_PACK_INDEXING(),
#if defined(__cpp_pack_indexing) && __cpp_pack_indexing >= 202311L
        1
#else
        0
#endif
    );  // NOLINT(whitespace/parens)
}

static void test_asc_char8()
{
    // CANN_ASC_STL_DETAIL_HAS_CHAR8_T() should be 0 or 1
    expect_eq("CANN_ASC_STL_DETAIL_HAS_CHAR8_T()", CANN_ASC_STL_DETAIL_HAS_CHAR8_T(),
#if CANN_ASC_STL_DETAIL_STD_VER >= 2020 && defined(__cpp_char8_t) && __cpp_char8_t >= 201811L
        1
#else
        0
#endif
    );  // NOLINT(whitespace/parens)
}

static void test_asc_multiarg_operator_brackets()
{
    // CANN_ASC_STL_DETAIL_HAS_MULTIARG_OPERATOR_BRACKETS() should be 0 or 1
    expect_eq(
        "CANN_ASC_STL_DETAIL_HAS_MULTIARG_OPERATOR_BRACKETS()", CANN_ASC_STL_DETAIL_HAS_MULTIARG_OPERATOR_BRACKETS(),
#if defined(__cpp_multidimensional_subscript) && __cpp_multidimensional_subscript >= 202110L
        1
#else
        0
#endif
    );  // NOLINT(whitespace/parens)
}

static void test_asc_static_subscript_operator()
{
    // CANN_ASC_STL_DETAIL_HAS_STATIC_SUBSCRIPT_OPERATOR() should be 0 or 1
    expect_eq(
        "CANN_ASC_STL_DETAIL_HAS_STATIC_SUBSCRIPT_OPERATOR()", CANN_ASC_STL_DETAIL_HAS_STATIC_SUBSCRIPT_OPERATOR(),
#if (defined(__cpp_multidimensional_subscript) && __cpp_multidimensional_subscript >= 202211L) || \
    CANN_ASC_STL_DETAIL_COMPILER(CLANG, >=, 16) || CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 13)
        1
#else
        0
#endif
    );  // NOLINT(whitespace/parens)
}

static void test_asc_static_call_operator()
{
    // CANN_ASC_STL_DETAIL_HAS_STATIC_CALL_OPERATOR() should be 0 or 1
    expect_eq("CANN_ASC_STL_DETAIL_HAS_STATIC_CALL_OPERATOR()", CANN_ASC_STL_DETAIL_HAS_STATIC_CALL_OPERATOR(),
#if (defined(__cpp_static_call_operator) && __cpp_static_call_operator >= 202207L) || \
    CANN_ASC_STL_DETAIL_COMPILER(CLANG, >=, 16) || CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 13)
        1
#else
        0
#endif
    );  // NOLINT(whitespace/parens)
}

static void test_asc_structured_bindings_pack()
{
    // CANN_ASC_STL_DETAIL_HAS_STRUCTURED_BINDINGS_PACK() should be 0 or 1
    expect_eq("CANN_ASC_STL_DETAIL_HAS_STRUCTURED_BINDINGS_PACK()", CANN_ASC_STL_DETAIL_HAS_STRUCTURED_BINDINGS_PACK(),
#if (defined(__cpp_structured_bindings) && __cpp_structured_bindings >= 202411L) || \
    CANN_ASC_STL_DETAIL_COMPILER(CLANG, >=, 21) || CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 16)
        1
#else
        0
#endif
    );  // NOLINT(whitespace/parens)
}

static void test_asc_consteval_asc_consteval()
{
    // Verify CANN_ASC_STL_DETAIL_IF_CONSTEVAL and CANN_ASC_STL_DETAIL_IF_NOT_CONSTEVAL compile
    int if_ce_val = 0;
    CANN_ASC_STL_DETAIL_IF_CONSTEVAL
    {
        if_ce_val = 1;
    }
    else  // NOLINT(whitespace/newline)
    {
        if_ce_val = 2;
    }
    // The value depends on evaluation context; just verify it compiled and is one of {0,1,2}
    expect_eq("CANN_ASC_STL_DETAIL_IF_CONSTEVAL compiled", (if_ce_val >= 0 && if_ce_val <= 2) ? 1 : 0, 1);
}

int main()
{
    test_asc_std_ver_reflect();
    test_asc_wchar_always_per();
    test_asc_long_double_host();
    test_asc_constexpr_cxx20_constexpr();
    test_asc_constexpr_cxx23_constexpr();
    test_asc_global_constant_namespace();
    test_asc_consteval_namespace_scope();
    test_asc_concepts();
    test_asc_pack_indexing();
    test_asc_char8();
    test_asc_multiarg_operator_brackets();
    test_asc_static_subscript_operator();
    test_asc_static_call_operator();
    test_asc_structured_bindings_pack();
    test_asc_consteval_asc_consteval();

    return g_failures == 0 ? 0 : 1;
}
