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

#include <asc/std/__asc/os.h>
#include <iostream>

static int g_failures = 0;

static void expect_eq(const char* expr, int got, int expected)
{
    bool ok = (got == expected);
    std::cout << "[host][os] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // Each ASC_OS(...) must expand to 0 or 1
    // On the Linux host where this test runs:
    //   WINDOWS=0, LINUX=1, ANDROID=0, QNX=0, APPLE=0
    expect_eq("ASC_OS(WINDOWS)", ASC_OS(WINDOWS), 0);
    expect_eq("ASC_OS(LINUX)", ASC_OS(LINUX), 1);
    expect_eq("ASC_OS(ANDROID)", ASC_OS(ANDROID), 0);
    expect_eq("ASC_OS(QNX)", ASC_OS(QNX), 0);
    expect_eq("ASC_OS(APPLE)", ASC_OS(APPLE), 0);

    // Internal CANN_ASC_STL_DETAIL_OS(...) must match the public ASC_OS(...)
    expect_eq("CANN_ASC_STL_DETAIL_OS(WINDOWS)", CANN_ASC_STL_DETAIL_OS(WINDOWS), 0);
    expect_eq("CANN_ASC_STL_DETAIL_OS(LINUX)", CANN_ASC_STL_DETAIL_OS(LINUX), 1);
    expect_eq("CANN_ASC_STL_DETAIL_OS(ANDROID)", CANN_ASC_STL_DETAIL_OS(ANDROID), 0);
    expect_eq("CANN_ASC_STL_DETAIL_OS(QNX)", CANN_ASC_STL_DETAIL_OS(QNX), 0);
    expect_eq("CANN_ASC_STL_DETAIL_OS(APPLE)", CANN_ASC_STL_DETAIL_OS(APPLE), 0);

    // Consistency: ASC_OS and CANN_ASC_STL_DETAIL_OS must agree for every OS
    expect_eq("ASC_OS(WINDOWS)==CANN_ASC_STL_DETAIL_OS(WINDOWS)", ASC_OS(WINDOWS), CANN_ASC_STL_DETAIL_OS(WINDOWS));
    expect_eq("ASC_OS(LINUX)==CANN_ASC_STL_DETAIL_OS(LINUX)", ASC_OS(LINUX), CANN_ASC_STL_DETAIL_OS(LINUX));
    expect_eq("ASC_OS(ANDROID)==CANN_ASC_STL_DETAIL_OS(ANDROID)", ASC_OS(ANDROID), CANN_ASC_STL_DETAIL_OS(ANDROID));
    expect_eq("ASC_OS(QNX)==CANN_ASC_STL_DETAIL_OS(QNX)", ASC_OS(QNX), CANN_ASC_STL_DETAIL_OS(QNX));
    expect_eq("ASC_OS(APPLE)==CANN_ASC_STL_DETAIL_OS(APPLE)", ASC_OS(APPLE), CANN_ASC_STL_DETAIL_OS(APPLE));

    // Return values are usable in boolean / preprocessor expressions
    bool windows_is_false = !ASC_OS(WINDOWS);
    bool linux_is_true = ASC_OS(LINUX);
    expect_eq("!ASC_OS(WINDOWS)", windows_is_false ? 1 : 0, 1);
    expect_eq("ASC_OS(LINUX) as bool", linux_is_true ? 1 : 0, 1);

    // Mutually exclusive check: on this Linux host, LINUX is true and the rest are false
    int all_correct = (ASC_OS(LINUX) && !ASC_OS(WINDOWS) && !ASC_OS(ANDROID) && !ASC_OS(QNX) && !ASC_OS(APPLE)) ? 1 : 0;
    expect_eq("LINUX && !WINDOWS && !ANDROID && !QNX && !APPLE", all_correct, 1);

    // Preprocessor-level usage (#if)
#if ASC_OS(LINUX)
    expect_eq("#if ASC_OS(LINUX) branch taken", 1, 1);
#else
    expect_eq("#if ASC_OS(LINUX) branch taken", 0, 1);
#endif

#if ASC_OS(WINDOWS)
    expect_eq("#if ASC_OS(WINDOWS) branch NOT taken", 0, 1);
#else
    expect_eq("#if ASC_OS(WINDOWS) branch NOT taken", 1, 1);
#endif

    return g_failures == 0 ? 0 : 1;
}
