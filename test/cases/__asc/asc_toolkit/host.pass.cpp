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

#include <asc/std/__asc/asc_toolkit.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][asc_toolkit] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][asc_toolkit] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

static void expect_eq_int(const char* expr, int got, int expected)
{
    const bool ok = (got == expected);
    std::cout << "[host][asc_toolkit] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void test_header_included_header_guard()
{
    // Verify the header can be included and its header guard is defined
    expect_true("CANN_ASC_STL_STD_DETAIL_ASC_TOOLKIT_H is defined",
#ifdef CANN_ASC_STL_STD_DETAIL_ASC_TOOLKIT_H
        true
#else
        false
#endif
    );  // NOLINT(whitespace/parens)
}

static void test_transitive_includes_compiler_accessible()
{
    // Verify transitive includes from compiler.h are accessible
    // CANN_ASC_STL_DETAIL_HOST_COMPILATION() should be 1 on host (no CCE compiler)
    expect_true("CANN_ASC_STL_DETAIL_HOST_COMPILATION() == 1", CANN_ASC_STL_DETAIL_HOST_COMPILATION() == 1);
}

static void test_asc_device_compilation_host()
{
    // CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() should be 0 on host (no CCE compiler)
    expect_false("CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() == 1", CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() == 1);
}

static void test_asc_freestanding_host()
{
    // CANN_ASC_STL_DETAIL_FREESTANDING() should be 0 on host
    expect_false("CANN_ASC_STL_DETAIL_FREESTANDING() == 1", CANN_ASC_STL_DETAIL_FREESTANDING() == 1);
}

static void test_asc_hosted_host()
{
    // CANN_ASC_STL_DETAIL_HOSTED() should be 1 on host
    expect_true("CANN_ASC_STL_DETAIL_HOSTED() == 1", CANN_ASC_STL_DETAIL_HOSTED() == 1);
}

static void test_defined()
{
    expect_true("CANN_ASC_STL_DETAIL_HAS_CANN() is boolean",
        CANN_ASC_STL_DETAIL_HAS_CANN() == 0 || CANN_ASC_STL_DETAIL_HAS_CANN() == 1);
    expect_true("CANN_ASC_STL_DETAIL_HAS_TOOLKIT() aliases CANN_ASC_STL_DETAIL_HAS_CANN()",
        CANN_ASC_STL_DETAIL_HAS_TOOLKIT() == CANN_ASC_STL_DETAIL_HAS_CANN());
    expect_eq_int("CANN_ASC_STL_DETAIL_CANN_MAKE_VERSION(9, 0)", CANN_ASC_STL_DETAIL_CANN_MAKE_VERSION(9, 0), 900);
#if defined(ASC_DEVKIT_MAJOR) && defined(ASC_DEVKIT_MINOR)
    expect_true("official CANN version makes detection valid", CANN_ASC_STL_DETAIL_HAS_CANN() == 1);
    expect_true("CANN_ASC_STL_DETAIL_CANN_AT_LEAST(ASC_DEVKIT_MAJOR, ASC_DEVKIT_MINOR)",
        CANN_ASC_STL_DETAIL_CANN_AT_LEAST(ASC_DEVKIT_MAJOR, ASC_DEVKIT_MINOR));
#else
    expect_false("CANN version is invalid without a public version header",
        !CANN_ASC_STL_DETAIL_VERSION_IS_INVALID(CANN_ASC_STL_DETAIL_CANN_VERSION()));
#endif
    expect_false("CANN_ASC_STL_DETAIL_CANN_AT_LEAST(99, 0)", CANN_ASC_STL_DETAIL_CANN_AT_LEAST(99, 0));
    expect_false("CANN_ASC_STL_DETAIL_TOOLKIT_AT_LEAST(99, 0)", CANN_ASC_STL_DETAIL_TOOLKIT_AT_LEAST(99, 0));
    expect_true("CANN_ASC_STL_DETAIL_TOOLKIT_BELOW(99, 0) aliases CANN_ASC_STL_DETAIL_CANN_BELOW(99, 0)",
        CANN_ASC_STL_DETAIL_TOOLKIT_BELOW(99, 0) == CANN_ASC_STL_DETAIL_CANN_BELOW(99, 0));
}

static void test_foreign_toolkit_macros_absent()
{
    // Foreign toolkit macro names must not leak through this header.
    expect_false("_CCCL_HAS_CTK is defined",
#ifdef _CCCL_HAS_CTK
        true
#else
        false
#endif
    );  // NOLINT(whitespace/parens)

    expect_false("_CCCL_CTK is defined",
#ifdef _CCCL_CTK
        true
#else
        false
#endif
    );  // NOLINT(whitespace/parens)

    expect_false("_CCCL_CTK_AT_LEAST is defined",
#ifdef _CCCL_CTK_AT_LEAST
        true
#else
        false
#endif
    );  // NOLINT(whitespace/parens)

    expect_false("_CCCL_CTK_BELOW is defined",
#ifdef _CCCL_CTK_BELOW
        true
#else
        false
#endif
    );  // NOLINT(whitespace/parens)

    expect_false("_CCCL_CTK_MAKE_VERSION is defined",
#ifdef _CCCL_CTK_MAKE_VERSION
        true
#else
        false
#endif
    );  // NOLINT(whitespace/parens)
}

int main()
{
    test_header_included_header_guard();
    test_transitive_includes_compiler_accessible();
    test_asc_device_compilation_host();
    test_asc_freestanding_host();
    test_asc_hosted_host();
    test_defined();
    test_foreign_toolkit_macros_absent();

    return g_failures == 0 ? 0 : 1;
}
