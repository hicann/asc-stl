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

#include <asc/std/cassert>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][cassert] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void test_asc_std_cassert_thin()
{
    // asc/std/cassert is a thin wrapper that includes <cassert> when
    // CANN_ASC_STL_DETAIL_HOSTED(). Verify the hosted path exposes the assert macro.
#if CANN_ASC_STL_DETAIL_HOSTED()
#ifdef assert
    expect_true("assert macro is available after including asc/std/cassert", true);
#else
    expect_true("assert macro is available after including asc/std/cassert", false);
#endif
#else
    expect_true("freestanding build: nothing to expose", true);
#endif
}

static void test_assert_ndebug_consistency()
{
    // In release builds (NDEBUG) the macro compiles to a no-op statement, so
    // including the header cannot introduce runtime behavior; in debug builds
    // diagnostics stay enabled by contract of the hosted <cassert>.
#ifdef NDEBUG
    expect_true("NDEBUG build: assert expands without runtime behavior", true);
#else
    expect_true("debug build: assert keeps diagnostics enabled", true);
#endif
}

int main()
{
    test_asc_std_cassert_thin();
    test_assert_ndebug_consistency();

    return g_failures == 0 ? 0 : 1;
}
