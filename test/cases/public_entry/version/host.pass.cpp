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

#include <asc/version>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][version] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][version] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // asc/std/version defines ASC-STL feature-test macros.
    // Verify that the feature-test macros exist and have their documented values.
    expect_eq("CANN_ASC_STL_DETAIL_LIB_bool_constant", CANN_ASC_STL_DETAIL_LIB_bool_constant, 201505L);
    expect_eq("CANN_ASC_STL_DETAIL_LIB_integral_constant_callable", CANN_ASC_STL_DETAIL_LIB_integral_constant_callable,
        201304L);

#if CANN_ASC_STL_DETAIL_STD_VER >= 2017
    expect_eq("CANN_ASC_STL_DETAIL_LIB_void_t", CANN_ASC_STL_DETAIL_LIB_void_t, 201411L);
#else
    expect_true("CANN_ASC_STL_DETAIL_LIB_void_t not defined (pre-C++17)", true);
#endif

#if CANN_ASC_STL_DETAIL_STD_VER >= 2020
    expect_eq("CANN_ASC_STL_DETAIL_LIB_endian", CANN_ASC_STL_DETAIL_LIB_endian, 201907L);
    expect_eq("CANN_ASC_STL_DETAIL_LIB_type_identity", CANN_ASC_STL_DETAIL_LIB_type_identity, 201806L);
#else
    expect_true("CANN_ASC_STL_DETAIL_LIB_endian / CANN_ASC_STL_DETAIL_LIB_type_identity not defined (pre-C++20)", true);
#endif

    // CANN_ASC_STL_DETAIL_STD_VER should be one of the recognized dialect values
    bool valid_ver = (CANN_ASC_STL_DETAIL_STD_VER == 2003 || CANN_ASC_STL_DETAIL_STD_VER == 2011 ||
        CANN_ASC_STL_DETAIL_STD_VER == 2014 || CANN_ASC_STL_DETAIL_STD_VER == 2017 ||
        CANN_ASC_STL_DETAIL_STD_VER == 2020 || CANN_ASC_STL_DETAIL_STD_VER == 2023 ||
        CANN_ASC_STL_DETAIL_STD_VER == 2024);
    expect_true("CANN_ASC_STL_DETAIL_STD_VER is a recognized dialect", valid_ver);

    return g_failures == 0 ? 0 : 1;
}
