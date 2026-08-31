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

#include <asc/std/__asc/compiler.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][compiler] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][compiler] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

static void expect_eq_int(const char* expr, int got, int expected)
{
    bool ok = (got == expected);
    std::cout << "[host][compiler] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void test_asc_version_major_asc()
{
    // ========================================================================
    // 1. CANN_ASC_STL_DETAIL_VERSION_MAJOR_ / CANN_ASC_STL_DETAIL_VERSION_MINOR_ (two-arg forms)
    // ========================================================================
    expect_eq_int("CANN_ASC_STL_DETAIL_VERSION_MAJOR_(3, 7)", CANN_ASC_STL_DETAIL_VERSION_MAJOR_(3, 7), 3);
    expect_eq_int("CANN_ASC_STL_DETAIL_VERSION_MINOR_(3, 7)", CANN_ASC_STL_DETAIL_VERSION_MINOR_(3, 7), 7);
    expect_eq_int("CANN_ASC_STL_DETAIL_VERSION_MAJOR_(0, 99)", CANN_ASC_STL_DETAIL_VERSION_MAJOR_(0, 99), 0);
    expect_eq_int("CANN_ASC_STL_DETAIL_VERSION_MINOR_(0, 99)", CANN_ASC_STL_DETAIL_VERSION_MINOR_(0, 99), 99);
}

static void test_asc_version_major_asc_2()
{
    // ========================================================================
    // 2. CANN_ASC_STL_DETAIL_VERSION_MAJOR / CANN_ASC_STL_DETAIL_VERSION_MINOR (pair macro forms)
    // ========================================================================
    expect_eq_int("CANN_ASC_STL_DETAIL_VERSION_MAJOR((3, 7))", CANN_ASC_STL_DETAIL_VERSION_MAJOR((3, 7)), 3);
    expect_eq_int("CANN_ASC_STL_DETAIL_VERSION_MINOR((3, 7))", CANN_ASC_STL_DETAIL_VERSION_MINOR((3, 7)), 7);
    expect_eq_int("CANN_ASC_STL_DETAIL_VERSION_MAJOR((0, 99))", CANN_ASC_STL_DETAIL_VERSION_MAJOR((0, 99)), 0);
    expect_eq_int("CANN_ASC_STL_DETAIL_VERSION_MINOR((0, 99))", CANN_ASC_STL_DETAIL_VERSION_MINOR((0, 99)), 99);
    expect_eq_int("CANN_ASC_STL_DETAIL_VERSION_MAJOR((0, 0))", CANN_ASC_STL_DETAIL_VERSION_MAJOR((0, 0)), 0);
    expect_eq_int("CANN_ASC_STL_DETAIL_VERSION_MINOR((0, 0))", CANN_ASC_STL_DETAIL_VERSION_MINOR((0, 0)), 0);
}

static void test_asc_version_invalid_asc()
{
    // ========================================================================
    // 3. CANN_ASC_STL_DETAIL_VERSION_INVALID / CANN_ASC_STL_DETAIL_VERSION_IS_INVALID
    // ========================================================================
    expect_true("CANN_ASC_STL_DETAIL_VERSION_IS_INVALID(CANN_ASC_STL_DETAIL_VERSION_INVALID())",
        CANN_ASC_STL_DETAIL_VERSION_IS_INVALID(CANN_ASC_STL_DETAIL_VERSION_INVALID()));
    expect_false("CANN_ASC_STL_DETAIL_VERSION_IS_INVALID((5, 2))", CANN_ASC_STL_DETAIL_VERSION_IS_INVALID((5, 2)));
    expect_false("CANN_ASC_STL_DETAIL_VERSION_IS_INVALID((0, 0))", CANN_ASC_STL_DETAIL_VERSION_IS_INVALID((0, 0)));
}

static void test_asc_make_version()
{
    // ========================================================================
    // 4. CANN_ASC_STL_DETAIL_MAKE_VERSION
    // ========================================================================
    expect_eq_int("CANN_ASC_STL_DETAIL_MAKE_VERSION((3, 7))", CANN_ASC_STL_DETAIL_MAKE_VERSION((3, 7)), 307);
    expect_eq_int("CANN_ASC_STL_DETAIL_MAKE_VERSION((1, 0))", CANN_ASC_STL_DETAIL_MAKE_VERSION((1, 0)), 100);
    expect_eq_int("CANN_ASC_STL_DETAIL_MAKE_VERSION((0, 99))", CANN_ASC_STL_DETAIL_MAKE_VERSION((0, 99)), 99);
    expect_eq_int("CANN_ASC_STL_DETAIL_MAKE_VERSION((0, 0))", CANN_ASC_STL_DETAIL_MAKE_VERSION((0, 0)), 0);
}

static void test_asc_compiler_make_version()
{
    // ========================================================================
    // 5. CANN_ASC_STL_DETAIL_COMPILER_MAKE_VERSION
    // ========================================================================
    expect_eq_int(
        "CANN_ASC_STL_DETAIL_COMPILER_MAKE_VERSION(3, 7)", CANN_ASC_STL_DETAIL_COMPILER_MAKE_VERSION(3, 7), 307);
    expect_eq_int(
        "CANN_ASC_STL_DETAIL_COMPILER_MAKE_VERSION(1, 0)", CANN_ASC_STL_DETAIL_COMPILER_MAKE_VERSION(1, 0), 100);
    expect_eq_int(
        "CANN_ASC_STL_DETAIL_COMPILER_MAKE_VERSION(0, 0)", CANN_ASC_STL_DETAIL_COMPILER_MAKE_VERSION(0, 0), 0);
}

static void test_asc_compiler_cce_invalid()
{
    // ========================================================================
    // 6. CANN_ASC_STL_DETAIL_COMPILER macro — CCE is invalid on non-CCE host
    // ========================================================================
    expect_false("CANN_ASC_STL_DETAIL_COMPILER(CCE)", CANN_ASC_STL_DETAIL_COMPILER(CCE));
    expect_false("CANN_ASC_STL_DETAIL_COMPILER(CCE, >=, 1)", CANN_ASC_STL_DETAIL_COMPILER(CCE, >=, 1));
    expect_false("CANN_ASC_STL_DETAIL_COMPILER(CCE, >=, 1, 0)", CANN_ASC_STL_DETAIL_COMPILER(CCE, >=, 1, 0));
}

static void test_asc_compiler_host_compiler()
{
    // ========================================================================
    // 7. CANN_ASC_STL_DETAIL_COMPILER macro — host compiler should be valid
    // ========================================================================
#if defined(CANN_ASC_STL_DETAIL_COMPILER_GCC)
    expect_true("CANN_ASC_STL_DETAIL_COMPILER(GCC)", CANN_ASC_STL_DETAIL_COMPILER(GCC));
    expect_true("CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 4)", CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 4));
    expect_true("CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 4, 0)", CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 4, 0));
    expect_false("CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 99)", CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 99));
    expect_false("CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 99, 0)", CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 99, 0));
    expect_false("CANN_ASC_STL_DETAIL_COMPILER(MSVC)", CANN_ASC_STL_DETAIL_COMPILER(MSVC));
    expect_false("CANN_ASC_STL_DETAIL_COMPILER(CLANG)", CANN_ASC_STL_DETAIL_COMPILER(CLANG));
#elif defined(CANN_ASC_STL_DETAIL_COMPILER_CLANG)
    expect_true("CANN_ASC_STL_DETAIL_COMPILER(CLANG)", CANN_ASC_STL_DETAIL_COMPILER(CLANG));
    expect_true("CANN_ASC_STL_DETAIL_COMPILER(CLANG, >=, 3)", CANN_ASC_STL_DETAIL_COMPILER(CLANG, >=, 3));
    expect_true("CANN_ASC_STL_DETAIL_COMPILER(CLANG, >=, 3, 0)", CANN_ASC_STL_DETAIL_COMPILER(CLANG, >=, 3, 0));
    expect_false("CANN_ASC_STL_DETAIL_COMPILER(CLANG, >=, 99)", CANN_ASC_STL_DETAIL_COMPILER(CLANG, >=, 99));
    expect_false("CANN_ASC_STL_DETAIL_COMPILER(CLANG, >=, 99, 0)", CANN_ASC_STL_DETAIL_COMPILER(CLANG, >=, 99, 0));
    expect_false("CANN_ASC_STL_DETAIL_COMPILER(MSVC)", CANN_ASC_STL_DETAIL_COMPILER(MSVC));
    expect_false("CANN_ASC_STL_DETAIL_COMPILER(GCC)", CANN_ASC_STL_DETAIL_COMPILER(GCC));
#elif defined(CANN_ASC_STL_DETAIL_COMPILER_MSVC)
    expect_true("CANN_ASC_STL_DETAIL_COMPILER(MSVC)", CANN_ASC_STL_DETAIL_COMPILER(MSVC));
    expect_true("CANN_ASC_STL_DETAIL_COMPILER(MSVC, >=, 19)", CANN_ASC_STL_DETAIL_COMPILER(MSVC, >=, 19));
    expect_true("CANN_ASC_STL_DETAIL_COMPILER(MSVC, >=, 19, 0)", CANN_ASC_STL_DETAIL_COMPILER(MSVC, >=, 19, 0));
    expect_false("CANN_ASC_STL_DETAIL_COMPILER(MSVC, >=, 99)", CANN_ASC_STL_DETAIL_COMPILER(MSVC, >=, 99));
    expect_false("CANN_ASC_STL_DETAIL_COMPILER(GCC)", CANN_ASC_STL_DETAIL_COMPILER(GCC));
    expect_false("CANN_ASC_STL_DETAIL_COMPILER(CLANG)", CANN_ASC_STL_DETAIL_COMPILER(CLANG));
#else
    std::cout << "[host][compiler] Unknown host compiler, skipping compiler-specific version checks" << std::endl;
#endif
}

static void test_compilation_mode_detection()
{
    // ========================================================================
    // 8. Compilation mode detection
    // ========================================================================
    expect_true("CANN_ASC_STL_DETAIL_HOST_COMPILATION()", CANN_ASC_STL_DETAIL_HOST_COMPILATION());
    expect_false("CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()", CANN_ASC_STL_DETAIL_DEVICE_COMPILATION());
}

static void test_freestanding_hosted_detection()
{
    // ========================================================================
    // 9. Freestanding / hosted detection
    // ========================================================================
    expect_false("CANN_ASC_STL_DETAIL_FREESTANDING()", CANN_ASC_STL_DETAIL_FREESTANDING());
    expect_true("CANN_ASC_STL_DETAIL_HOSTED()", CANN_ASC_STL_DETAIL_HOSTED());
}

static void test_asc_pragma_unroll_asc()
{
    // ========================================================================
    // 10. CANN_ASC_STL_DETAIL_PRAGMA_UNROLL / CANN_ASC_STL_DETAIL_PRAGMA_NOUNROLL compile and work
    // ========================================================================
    {
        int sum = 0;
        int arr[8] = {0, 1, 2, 3, 4, 5, 6, 7};
        CANN_ASC_STL_DETAIL_PRAGMA_UNROLL(8)
        for (int i = 0; i < 8; ++i) {
            sum += arr[i];
        }
        expect_eq_int("CANN_ASC_STL_DETAIL_PRAGMA_UNROLL loop sum", sum, 28);
    }
}

static void test_asc_compiler_version_returns()
{
    // ========================================================================
    // 11. CANN_ASC_STL_DETAIL_COMPILER_VERSION_*() returns correct pair for the detected host
    // ========================================================================
#if defined(CANN_ASC_STL_DETAIL_COMPILER_GCC)
    expect_eq_int("CANN_ASC_STL_DETAIL_VERSION_MAJOR(CANN_ASC_STL_DETAIL_COMPILER_VERSION_GCC())",
        CANN_ASC_STL_DETAIL_VERSION_MAJOR(CANN_ASC_STL_DETAIL_COMPILER_VERSION_GCC()), __GNUC__);
    expect_eq_int("CANN_ASC_STL_DETAIL_VERSION_MINOR(CANN_ASC_STL_DETAIL_COMPILER_VERSION_GCC())",
        CANN_ASC_STL_DETAIL_VERSION_MINOR(CANN_ASC_STL_DETAIL_COMPILER_VERSION_GCC()), __GNUC_MINOR__);
#elif defined(CANN_ASC_STL_DETAIL_COMPILER_CLANG)
    expect_eq_int("CANN_ASC_STL_DETAIL_VERSION_MAJOR(CANN_ASC_STL_DETAIL_COMPILER_VERSION_CLANG())",
        CANN_ASC_STL_DETAIL_VERSION_MAJOR(CANN_ASC_STL_DETAIL_COMPILER_VERSION_CLANG()), __clang_major__);
    expect_eq_int("CANN_ASC_STL_DETAIL_VERSION_MINOR(CANN_ASC_STL_DETAIL_COMPILER_VERSION_CLANG())",
        CANN_ASC_STL_DETAIL_VERSION_MINOR(CANN_ASC_STL_DETAIL_COMPILER_VERSION_CLANG()), __clang_minor__);
#endif
}

int main()
{
    test_asc_version_major_asc();
    test_asc_version_major_asc_2();
    test_asc_version_invalid_asc();
    test_asc_make_version();
    test_asc_compiler_make_version();
    test_asc_compiler_cce_invalid();
    test_asc_compiler_host_compiler();
    test_compilation_mode_detection();
    test_freestanding_hosted_detection();
    test_asc_pragma_unroll_asc();
    test_asc_compiler_version_returns();

    return g_failures == 0 ? 0 : 1;
}
