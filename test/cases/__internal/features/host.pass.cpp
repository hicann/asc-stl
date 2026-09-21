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

#include <asc/std/__internal/features.h>
#include <iostream>
#include <cstdint>

static int g_failures = 0;

static void expect_eq(const char* expr, int got, int expected)
{
    bool ok = (got == expected);
    std::cout << "[host][features] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][features] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

// Independently compute expected values at preprocessing time (mirror the
// header logic but do NOT call the header macros to produce expected).
#if !CANN_ASC_STL_DETAIL_COMPILER(CLANG) || CANN_ASC_STL_DETAIL_STD_VER >= 2020
#define EXPECTED_CHRONO_LITERALS 1
#else
#define EXPECTED_CHRONO_LITERALS 0
#endif

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && defined(__cpp_aligned_new) && __cpp_aligned_new >= 201606
#define EXPECTED_ALIGNED_ALLOC 1
#else
#define EXPECTED_ALIGNED_ALLOC 0
#endif

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTANT_EVALUATED) && \
    !CANN_ASC_STL_DETAIL_COMPILER(MSVC)
#define EXPECTED_CONSTEXPR_COMPLEX 1
#else
#define EXPECTED_CONSTEXPR_COMPLEX 0
#endif

#if CANN_ASC_STL_DETAIL_HOSTED()
#define EXPECTED_MONOTONIC_CLOCK 1
#else
#define EXPECTED_MONOTONIC_CLOCK 0
#endif

CANN_ASC_STL_DETAIL_ACCL_DIAGNOSE_WARNING(false, "test warning")
static int diagnose_warning_probe()
{
    return 1;
}

CANN_ASC_STL_DETAIL_ACCL_DIAGNOSE_ERROR(false, "test error")
static int diagnose_error_probe()
{
    return 2;
}

static void check_fixed_value_macros()
{
    // ---- Fixed-value macros (always 0 in ASC-STL) ----
    expect_eq("CANN_ASC_STL_DETAIL_ACCL_HAS_MONOTONIC_CLOCK()", CANN_ASC_STL_DETAIL_ACCL_HAS_MONOTONIC_CLOCK(),
        EXPECTED_MONOTONIC_CLOCK);
    expect_eq(
        "CANN_ASC_STL_DETAIL_ACCL_HAS_SPACESHIP_OPERATOR()", CANN_ASC_STL_DETAIL_ACCL_HAS_SPACESHIP_OPERATOR(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_ACCL_HAS_SIMD_F32X2_INTRINSICS()",
        CANN_ASC_STL_DETAIL_ACCL_HAS_SIMD_F32X2_INTRINSICS(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_ACCL_HAS_SIMD_F32X2()", CANN_ASC_STL_DETAIL_ACCL_HAS_SIMD_F32X2(), 0);
}

static void check_conditional_feature_macros()
{
    // ---- Conditional macros (expected values computed independently) ----
    expect_eq("CANN_ASC_STL_DETAIL_ACCL_HAS_CXX20_CHRONO_LITERALS()",
        CANN_ASC_STL_DETAIL_ACCL_HAS_CXX20_CHRONO_LITERALS(), EXPECTED_CHRONO_LITERALS);
    expect_eq("CANN_ASC_STL_DETAIL_ACCL_HAS_ALIGNED_ALLOCATION()", CANN_ASC_STL_DETAIL_ACCL_HAS_ALIGNED_ALLOCATION(),
        EXPECTED_ALIGNED_ALLOC);
    expect_eq("CANN_ASC_STL_DETAIL_ACCL_HAS_CONSTEXPR_COMPLEX_OPERATIONS()",
        CANN_ASC_STL_DETAIL_ACCL_HAS_CONSTEXPR_COMPLEX_OPERATIONS(), EXPECTED_CONSTEXPR_COMPLEX);

    // ---- CANN_ASC_STL_DETAIL_ACCL_HAS_NO_INCOMPLETE_RANGES should always be defined ----
#ifdef CANN_ASC_STL_DETAIL_ACCL_HAS_NO_INCOMPLETE_RANGES
    expect_true("CANN_ASC_STL_DETAIL_ACCL_HAS_NO_INCOMPLETE_RANGES is defined", true);
#else
    expect_true("CANN_ASC_STL_DETAIL_ACCL_HAS_NO_INCOMPLETE_RANGES is defined", false);
#endif

    // ---- constexpr dynamic allocation stays unsupported; the macro is absent ----
#ifndef CANN_ASC_STL_DETAIL_ACCL_CONSTEXPR_CXX20_ALLOCATION
    expect_true("CANN_ASC_STL_DETAIL_ACCL_CONSTEXPR_CXX20_ALLOCATION is not defined", true);
#else
    expect_true("CANN_ASC_STL_DETAIL_ACCL_CONSTEXPR_CXX20_ALLOCATION is not defined", false);
#endif
}

static void check_diagnose_and_alignment_macros()
{
    // ---- CANN_ASC_STL_DETAIL_ACCL_DIAGNOSE_WARNING / CANN_ASC_STL_DETAIL_ACCL_DIAGNOSE_ERROR compile as function
    // attributes or empty shims ----
    expect_eq("CANN_ASC_STL_DETAIL_ACCL_DIAGNOSE_WARNING probe", diagnose_warning_probe(), 1);
    expect_eq("CANN_ASC_STL_DETAIL_ACCL_DIAGNOSE_ERROR probe", diagnose_error_probe(), 2);

    // ---- CANN_ASC_STL_DETAIL_ACCL_ALIGNAS / CANN_ASC_STL_DETAIL_ACCL_ALIGNAS_TYPE ----
    CANN_ASC_STL_DETAIL_ACCL_ALIGNAS(16) int aligned_var = 0;
    expect_true("CANN_ASC_STL_DETAIL_ACCL_ALIGNAS(16) produces 16-byte alignment", ((uintptr_t)&aligned_var % 16) == 0);

    struct TestStruct {
        double a;
        int b;
    };
    CANN_ASC_STL_DETAIL_ACCL_ALIGNAS_TYPE(TestStruct) int aligned_type_var = 0;
    expect_true("CANN_ASC_STL_DETAIL_ACCL_ALIGNAS_TYPE(TestStruct) produces TestStruct alignment",
        ((uintptr_t)&aligned_type_var % alignof(TestStruct)) == 0);

    // ---- CANN_ASC_STL_DETAIL_ACCL_CONSTEXPR_COMPLEX ----
    CANN_ASC_STL_DETAIL_ACCL_CONSTEXPR_COMPLEX int cc_val = 10;
    expect_eq("CANN_ASC_STL_DETAIL_ACCL_CONSTEXPR_COMPLEX int", cc_val, 10);
}

static void check_cxx17_removed_binders_gates()
{
    // ---- CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_BINDERS conditional definition ----
#if !defined(CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_FEATURES)
#ifdef CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_BINDERS
    expect_true(
        "CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_BINDERS not defined (no "
        "CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_FEATURES)",
        false);
#else
    expect_true(
        "CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_BINDERS not defined (no "
        "CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_FEATURES)",
        true);
#endif
#else
#ifdef CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_BINDERS
    expect_true(
        "CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_BINDERS defined (with "
        "CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_FEATURES)",
        true);
#else
    expect_true(
        "CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_BINDERS defined (with "
        "CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_FEATURES)",
        false);
#endif
#endif
}

int main()
{
    check_fixed_value_macros();
    check_conditional_feature_macros();
    check_diagnose_and_alignment_macros();
    check_cxx17_removed_binders_gates();

    return g_failures == 0 ? 0 : 1;
}
