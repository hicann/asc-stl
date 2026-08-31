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

#define ASC_ENABLE_EXPERIMENTAL_HOST_ATOMICS_128B
#include <asc/std/__internal/atomic.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][atomic] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][atomic] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    // CANN_ASC_STL_DETAIL_ACCL_ATOMIC_FLAG_TYPE should be int
    expect_true("CANN_ASC_STL_DETAIL_ACCL_ATOMIC_FLAG_TYPE is int",
        std::is_same<CANN_ASC_STL_DETAIL_ACCL_ATOMIC_FLAG_TYPE, int>::value);

    // CANN_ASC_STL_DETAIL_ACCL_ATOMIC_ALWAYS_LOCK_FREE on host (GCC) delegates to __atomic_always_lock_free
    expect_true("CANN_ASC_STL_DETAIL_ACCL_ATOMIC_ALWAYS_LOCK_FREE(1, nullptr)",
        (bool)CANN_ASC_STL_DETAIL_ACCL_ATOMIC_ALWAYS_LOCK_FREE(1, nullptr));  // NOLINT(readability/casting)
    expect_true("CANN_ASC_STL_DETAIL_ACCL_ATOMIC_ALWAYS_LOCK_FREE(8, nullptr)",
        (bool)CANN_ASC_STL_DETAIL_ACCL_ATOMIC_ALWAYS_LOCK_FREE(8, nullptr));  // NOLINT(readability/casting)

    // ASC-STL exposes only the ASC-prefixed opt-in.
#ifdef ASC_ENABLE_EXPERIMENTAL_HOST_ATOMICS_128B
    expect_true("ASC atomics opt-in is defined", true);
#else
    expect_true("ASC atomics opt-in is defined", false);
#endif

    // CANN_ASC_STL_DETAIL_ACCL_HOST_128_ATOMICS_ENABLED() should be 1 with the ASC opt-in.
    expect_eq(
        "CANN_ASC_STL_DETAIL_ACCL_HOST_128_ATOMICS_ENABLED()", CANN_ASC_STL_DETAIL_ACCL_HOST_128_ATOMICS_ENABLED(), 1);

    // CANN_ASC_STL_DETAIL_ACCL_HOST_128_ATOMICS_MAYBE() should be 0 when the opt-in forces enabled
    expect_eq(
        "CANN_ASC_STL_DETAIL_ACCL_HOST_128_ATOMICS_MAYBE()", CANN_ASC_STL_DETAIL_ACCL_HOST_128_ATOMICS_MAYBE(), 0);

    // CANN_ASC_STL_DETAIL_ACCL_ATOMIC_UNSAFE_AUTOMATIC_STORAGE should NOT be defined
#ifdef CANN_ASC_STL_DETAIL_ACCL_ATOMIC_UNSAFE_AUTOMATIC_STORAGE
    expect_true("CANN_ASC_STL_DETAIL_ACCL_ATOMIC_UNSAFE_AUTOMATIC_STORAGE not defined", false);
#else
    expect_true("CANN_ASC_STL_DETAIL_ACCL_ATOMIC_UNSAFE_AUTOMATIC_STORAGE not defined", true);
#endif

    return g_failures == 0 ? 0 : 1;
}
