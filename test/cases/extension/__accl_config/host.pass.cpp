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

#include <asc/__accl_config>
#include <iostream>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][__accl_config] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][__accl_config] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
#if defined(CANN_ASC_STL_DETAIL_STD_VER)
    bool has_std_ver = true;
#else
    bool has_std_ver = false;
#endif
    expect_true("CANN_ASC_STL_DETAIL_STD_VER is defined", has_std_ver);

#if defined(CANN_ASC_STL_HOST_DEVICE)
    bool has_host_device = true;
#else
    bool has_host_device = false;
#endif
    expect_true("CANN_ASC_STL_HOST_DEVICE is defined", has_host_device);

#if defined(CANN_ASC_STL_DETAIL_AICORE_FN)
    bool has_aicore_fn = true;
#else
    bool has_aicore_fn = false;
#endif
    expect_true("CANN_ASC_STL_DETAIL_AICORE_FN is defined", has_aicore_fn);

#if defined(CANN_ASC_STL_ACCL_VERSION)
    bool has_version = true;
#else
    bool has_version = false;
#endif
    expect_true("CANN_ASC_STL_ACCL_VERSION is defined", has_version);

    expect_eq("CANN_ASC_STL_ACCL_MAJOR_VERSION", CANN_ASC_STL_ACCL_MAJOR_VERSION, 1);
    expect_eq("CANN_ASC_STL_ACCL_MINOR_VERSION", CANN_ASC_STL_ACCL_MINOR_VERSION, 0);
    expect_eq("CANN_ASC_STL_ACCL_PATCH_VERSION", CANN_ASC_STL_ACCL_PATCH_VERSION, 0);

    return g_failures == 0 ? 0 : 1;
}
