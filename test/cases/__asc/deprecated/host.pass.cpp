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

// ASC-STL accepts only ASC-prefixed configuration inputs.
#define ASC_IGNORE_DEPRECATED_CPP_DIALECT
#define ASC_IGNORE_DEPRECATED_API
#include <asc/std/__asc/deprecated.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][deprecated] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

// ASC_DEPRECATED applied to a function
ASC_DEPRECATED
int deprecated_func()
{
    return 42;
}

// ASC_DEPRECATED_BECAUSE applied to a function with a message
ASC_DEPRECATED_BECAUSE("use new_func instead")
int deprecated_func_msg()
{
    return 99;
}

// CANN_ASC_STL_DETAIL_DEPRECATED_IN_CXX20 applied to a function
CANN_ASC_STL_DETAIL_DEPRECATED_IN_CXX20
int dep_cxx20_func()
{
    return 20;
}

// CANN_ASC_STL_DETAIL_DEPRECATED_IN_CXX23 applied to a function
CANN_ASC_STL_DETAIL_DEPRECATED_IN_CXX23
int dep_cxx23_func()
{
    return 23;
}

// ASC_DEPRECATED applied to a variable
ASC_DEPRECATED
int deprecated_var = 100;

static void test_asc_deprecated()
{
    // 1. Verify all macros are defined
#ifdef ASC_DEPRECATED
    expect_true("ASC_DEPRECATED is defined", true);
#else
    expect_true("ASC_DEPRECATED is defined", false);
#endif

#ifdef ASC_DEPRECATED_BECAUSE
    expect_true("ASC_DEPRECATED_BECAUSE is defined", true);
#else
    expect_true("ASC_DEPRECATED_BECAUSE is defined", false);
#endif

#ifdef CANN_ASC_STL_DETAIL_DEPRECATED_IN_CXX20
    expect_true("CANN_ASC_STL_DETAIL_DEPRECATED_IN_CXX20 is defined", true);
#else
    expect_true("CANN_ASC_STL_DETAIL_DEPRECATED_IN_CXX20 is defined", false);
#endif

#ifdef CANN_ASC_STL_DETAIL_DEPRECATED_IN_CXX23
    expect_true("CANN_ASC_STL_DETAIL_DEPRECATED_IN_CXX23 is defined", true);
#else
    expect_true("CANN_ASC_STL_DETAIL_DEPRECATED_IN_CXX23 is defined", false);
#endif
}

static void test_deprecated_functions_variables_still()
{
    // 2. Verify deprecated functions/variables still work correctly
    expect_true("deprecated_func() == 42", deprecated_func() == 42);
    expect_true("deprecated_func_msg() == 99", deprecated_func_msg() == 99);
    expect_true("dep_cxx20_func() == 20", dep_cxx20_func() == 20);
    expect_true("dep_cxx23_func() == 23", dep_cxx23_func() == 23);
    expect_true("deprecated_var == 100", deprecated_var == 100);
}

static void test_asc_dialect_cascade_dialect()
{
    // 3. Verify ASC dialect cascade: DIALECT -> CPP_14 -> CPP_11 -> COMPILER
#ifdef ASC_IGNORE_DEPRECATED_CPP_DIALECT
    expect_true("ASC DIALECT remains defined", true);
#else
    expect_true("ASC DIALECT remains defined", false);
#endif

#ifdef ASC_IGNORE_DEPRECATED_CPP_14
    expect_true("DIALECT cascades to CPP_14", true);
#else
    expect_true("DIALECT cascades to CPP_14", false);
#endif

#ifdef ASC_IGNORE_DEPRECATED_CPP_11
    expect_true("CPP_14 cascades to CPP_11", true);
#else
    expect_true("CPP_14 cascades to CPP_11", false);
#endif

#ifdef ASC_IGNORE_DEPRECATED_COMPILER
    expect_true("cascade reaches COMPILER", true);
#else
    expect_true("cascade reaches COMPILER", false);
#endif
}

static void test_asc_api_opt_out()
{
    // 4. Verify the ASC API opt-out remains active.
#ifdef ASC_IGNORE_DEPRECATED_API
    expect_true("ASC_IGNORE_DEPRECATED_API remains defined", true);
#else
    expect_true("ASC_IGNORE_DEPRECATED_API remains defined", false);
#endif
}

static void test_asc_std_ver_consistency()
{
    // 5. Verify CANN_ASC_STL_DETAIL_STD_VER consistency
    expect_true("CANN_ASC_STL_DETAIL_STD_VER >= 2003", CANN_ASC_STL_DETAIL_STD_VER >= 2003);
    expect_true("CANN_ASC_STL_DETAIL_STD_VER <= 2024", CANN_ASC_STL_DETAIL_STD_VER <= 2024);
}

int main()
{
    test_asc_deprecated();
    test_deprecated_functions_variables_still();
    test_asc_dialect_cascade_dialect();
    test_asc_api_opt_out();
    test_asc_std_ver_consistency();

    return g_failures == 0 ? 0 : 1;
}
