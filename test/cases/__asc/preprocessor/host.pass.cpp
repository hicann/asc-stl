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

#include <asc/std/__asc/preprocessor.h>
#include <iostream>
#include <string>

static int g_failures = 0;

#define ASC_TEST_STRINGIZE_IMPL(_X) #_X
#define ASC_TEST_STRINGIZE(_X) ASC_TEST_STRINGIZE_IMPL(_X)
#define ASC_TEST_ADD_VALUE(_X) +_X
#define ASC_TEST_DECLARE_VALUE(_X) int CANN_ASC_STL_DETAIL_PP_CAT(value_, _X) = _X;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][preprocessor] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_eq_int(const char* expr, int got, int expected)
{
    const bool ok = (got == expected);
    std::cout << "[host][preprocessor] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_eq_string(const char* expr, const char* got, const char* expected)
{
    const bool ok = (std::string(got) == expected);
    std::cout << "[host][preprocessor] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    expect_true("CANN_ASC_STL_STD_DETAIL_PREPROCESSOR_H is defined",
#ifdef CANN_ASC_STL_STD_DETAIL_PREPROCESSOR_H
        true
#else
        false
#endif
    );  // NOLINT(whitespace/parens)

    expect_eq_int("CANN_ASC_STL_DETAIL_PP_COUNT(a, b, c, d)", CANN_ASC_STL_DETAIL_PP_COUNT(a, b, c, d), 4);
    expect_eq_int("CANN_ASC_STL_DETAIL_PP_INC(41)", CANN_ASC_STL_DETAIL_PP_INC(41), 42);
    expect_eq_int("CANN_ASC_STL_DETAIL_PP_DEC(42)", CANN_ASC_STL_DETAIL_PP_DEC(42), 41);
    expect_eq_string(
        "CANN_ASC_STL_DETAIL_PP_CAT(foo, bar)", ASC_TEST_STRINGIZE(CANN_ASC_STL_DETAIL_PP_CAT(foo, bar)), "foobar");

    const int sum = 0 CANN_ASC_STL_DETAIL_PP_FOR_EACH(ASC_TEST_ADD_VALUE, 1, 2, 3, 4);
    expect_eq_int("CANN_ASC_STL_DETAIL_PP_FOR_EACH sum", sum, 10);

    CANN_ASC_STL_DETAIL_PP_FOR_EACH(ASC_TEST_DECLARE_VALUE, 1, 2, 3)
    expect_eq_int("CANN_ASC_STL_DETAIL_PP_FOR_EACH declarations", value_1 + value_2 + value_3, 6);

    // Verify that foreign legacy macro names do not leak through this header.
#ifdef _CCCL_PP_COUNT
    std::cout << "[host][preprocessor] _CCCL_PP_COUNT is defined (unexpected) - FAIL" << std::endl;
    ++g_failures;
#else
    std::cout << "[host][preprocessor] _CCCL_PP_COUNT is NOT defined (expected) - OK" << std::endl;
#endif

#ifdef _CCCL_PP_CAT
    std::cout << "[host][preprocessor] _CCCL_PP_CAT is defined (unexpected) - FAIL" << std::endl;
    ++g_failures;
#else
    std::cout << "[host][preprocessor] _CCCL_PP_CAT is NOT defined (expected) - OK" << std::endl;
#endif

#ifdef _CCCL_PP_INC
    std::cout << "[host][preprocessor] _CCCL_PP_INC is defined (unexpected) - FAIL" << std::endl;
    ++g_failures;
#else
    std::cout << "[host][preprocessor] _CCCL_PP_INC is NOT defined (expected) - OK" << std::endl;
#endif

    return g_failures == 0 ? 0 : 1;
}
