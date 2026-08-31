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

#include <asc/std/__asc/system_header.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][system_header] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void test_header_guard()
{
    expect_true("CANN_ASC_STL_STD_DETAIL_SYSTEM_HEADER_H is defined",
#ifdef CANN_ASC_STL_STD_DETAIL_SYSTEM_HEADER_H
        true
#else
        false
#endif
    );  // NOLINT(whitespace/parens)
}

static void test_transitive_compiler_macros()
{
    expect_true("CANN_ASC_STL_DETAIL_COMPILER macro is available (from compiler.h)",
#ifdef CANN_ASC_STL_DETAIL_COMPILER
        true
#else
        false
#endif
    );  // NOLINT(whitespace/parens)
}

static void test_transitive_type_traits()
{
    expect_true("__asc_void_t is available (from is_non_narrowing_convertible.h)",
        (std::is_same<__asc_internal::__asc_void_t<int>, void>::value));

    expect_true("__is_non_narrowing_convertible<int, int>::value is true",
        __asc_internal::__is_non_narrowing_convertible<int, int>::value);

    expect_true("__is_non_narrowing_convertible<float, double>::value is false (narrowing)",
        !__asc_internal::__is_non_narrowing_convertible<float, double>::value);
}

#if defined(CANN_ASC_STL_DETAIL_COMPILER_GCC)
static void test_active_compiler_system_header_macros()
{
    expect_true("CANN_ASC_STL_DETAIL_FORCE_SYSTEM_HEADER_GCC is defined",
#ifdef CANN_ASC_STL_DETAIL_FORCE_SYSTEM_HEADER_GCC
        true
#else
        false
#endif
    );  // NOLINT(whitespace/parens)

    expect_true("CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC is defined",
#ifdef CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC
        true
#else
        false
#endif
    );  // NOLINT(whitespace/parens)
}
#elif defined(CANN_ASC_STL_DETAIL_COMPILER_CLANG)
static void test_active_compiler_system_header_macros()
{
    expect_true("CANN_ASC_STL_DETAIL_FORCE_SYSTEM_HEADER_CLANG is defined",
#ifdef CANN_ASC_STL_DETAIL_FORCE_SYSTEM_HEADER_CLANG
        true
#else
        false
#endif
    );  // NOLINT(whitespace/parens)

    expect_true("CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG is defined",
#ifdef CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG
        true
#else
        false
#endif
    );  // NOLINT(whitespace/parens)
}
#elif defined(CANN_ASC_STL_DETAIL_COMPILER_MSVC)
static void test_active_compiler_system_header_macros()
{
    expect_true("CANN_ASC_STL_DETAIL_FORCE_SYSTEM_HEADER_MSVC is defined",
#ifdef CANN_ASC_STL_DETAIL_FORCE_SYSTEM_HEADER_MSVC
        true
#else
        false
#endif
    );  // NOLINT(whitespace/parens)

    expect_true("CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC is defined",
#ifdef CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC
        true
#else
        false
#endif
    );  // NOLINT(whitespace/parens)
}
#endif

static void test_foreign_system_header_macros_absent()
{
    expect_true("_CCCL_FORCE_SYSTEM_HEADER_GCC is not defined",
#ifdef _CCCL_FORCE_SYSTEM_HEADER_GCC
        false
#else
        true
#endif
    );  // NOLINT(whitespace/parens)

    expect_true("_CCCL_IMPLICIT_SYSTEM_HEADER_GCC is not defined",
#ifdef _CCCL_IMPLICIT_SYSTEM_HEADER_GCC
        false
#else
        true
#endif
    );  // NOLINT(whitespace/parens)
}

int main()
{
    test_header_guard();
    test_transitive_compiler_macros();
    test_transitive_type_traits();
    test_active_compiler_system_header_macros();
    test_foreign_system_header_macros_absent();

    return g_failures == 0 ? 0 : 1;
}
