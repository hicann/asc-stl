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

#include <asc/std/__asc/host_std_lib.h>
#include <iostream>

static int g_failures = 0;

static void expect_eq(const char* expr, int got, int expected)
{
    bool ok = (got == expected);
    std::cout << "[host][host_std_lib] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // ---- Test CANN_ASC_STL_DETAIL_HOST_STD_LIB_MAKE_VERSION ----
    expect_eq("CANN_ASC_STL_DETAIL_HOST_STD_LIB_MAKE_VERSION(1, 0)",
        CANN_ASC_STL_DETAIL_HOST_STD_LIB_MAKE_VERSION(1, 0), 100);
    expect_eq("CANN_ASC_STL_DETAIL_HOST_STD_LIB_MAKE_VERSION(12, 5)",
        CANN_ASC_STL_DETAIL_HOST_STD_LIB_MAKE_VERSION(12, 5), 1205);
    expect_eq("CANN_ASC_STL_DETAIL_HOST_STD_LIB_MAKE_VERSION(0, 99)",
        CANN_ASC_STL_DETAIL_HOST_STD_LIB_MAKE_VERSION(0, 99), 99);
    expect_eq("CANN_ASC_STL_DETAIL_HOST_STD_LIB_MAKE_VERSION(16, 0)",
        CANN_ASC_STL_DETAIL_HOST_STD_LIB_MAKE_VERSION(16, 0), 1600);

    // ---- Test CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB ----
    // On a hosted system with a standard library, this must be 1
    expect_eq("CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()", CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB(), 1);

    // ---- Test 1-arg form: library validity ----
    // At least one library must be detected as valid on a hosted system
    int any_valid = CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBSTDCXX) || CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBCXX) ||
        CANN_ASC_STL_DETAIL_HOST_STD_LIB(STL);
    expect_eq("at least one lib valid", any_valid, 1);

    // Print which libraries are detected (diagnostic)
    std::cout << "[host][host_std_lib] CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBSTDCXX) = "
              << CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBSTDCXX) << std::endl;
    std::cout << "[host][host_std_lib] CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBCXX) = "
              << CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBCXX) << std::endl;
    std::cout << "[host][host_std_lib] CANN_ASC_STL_DETAIL_HOST_STD_LIB(STL) = "
              << CANN_ASC_STL_DETAIL_HOST_STD_LIB(STL) << std::endl;

    // ---- Test 3-arg form: version comparison (major only) ----
    // Results must be 0 or 1
    int r3a = CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBSTDCXX, >=, 7);
    int r3b = CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBCXX, >=, 16);
    int r3c = CANN_ASC_STL_DETAIL_HOST_STD_LIB(STL, >=, 142);
    expect_eq("CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBSTDCXX, >=, 7) in {0,1}", (r3a == 0 || r3a == 1) ? 1 : 0, 1);
    expect_eq("CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBCXX, >=, 16) in {0,1}", (r3b == 0 || r3b == 1) ? 1 : 0, 1);
    expect_eq("CANN_ASC_STL_DETAIL_HOST_STD_LIB(STL, >=, 142) in {0,1}", (r3c == 0 || r3c == 1) ? 1 : 0, 1);

    // ---- Test 4-arg form: version comparison (major.minor) ----
    int r4a = CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBCXX, >=, 16, 0);
    int r4b = CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBSTDCXX, >=, 7, 0);
    expect_eq("CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBCXX, >=, 16, 0) in {0,1}", (r4a == 0 || r4a == 1) ? 1 : 0, 1);
    expect_eq("CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBSTDCXX, >=, 7, 0) in {0,1}", (r4b == 0 || r4b == 1) ? 1 : 0, 1);

    // ---- Consistency: valid library implies version >= 1 ----
    if (CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBCXX)) {
        expect_eq("LIBCXX valid => LIBCXX >= 1", CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBCXX, >=, 1), 1);
    }
    if (CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBSTDCXX)) {
        expect_eq("LIBSTDCXX valid => LIBSTDCXX >= 1", CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBSTDCXX, >=, 1), 1);
    }
    if (CANN_ASC_STL_DETAIL_HOST_STD_LIB(STL)) {
        expect_eq("STL valid => STL >= 1", CANN_ASC_STL_DETAIL_HOST_STD_LIB(STL, >=, 1), 1);
    }

    // ---- Consistency: invalid library implies version check returns 0 ----
    if (!CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBCXX)) {
        expect_eq("LIBCXX invalid => LIBCXX >= 1 == 0", CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBCXX, >=, 1), 0);
    }
    if (!CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBSTDCXX)) {
        expect_eq("LIBSTDCXX invalid => LIBSTDCXX >= 1 == 0", CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBSTDCXX, >=, 1), 0);
    }
    if (!CANN_ASC_STL_DETAIL_HOST_STD_LIB(STL)) {
        expect_eq("STL invalid => STL >= 1 == 0", CANN_ASC_STL_DETAIL_HOST_STD_LIB(STL, >=, 1), 0);
    }

    return g_failures == 0 ? 0 : 1;
}
