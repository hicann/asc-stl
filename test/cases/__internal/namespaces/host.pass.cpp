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

#include <asc/std/__internal/namespaces.h>
#include <iostream>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][namespaces] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_NOVERSION
int var_asc_std_noversion = 1;
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_NOVERSION

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD
int var_asc_std = 2;
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC
int var_asc = 3;
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_MR
int var_asc_mr = 4;
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_MR

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_DEVICE
int var_asc_device = 5;
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_DEVICE

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_DEVICE_EXPERIMENTAL
int var_asc_device_exp = 6;
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_DEVICE_EXPERIMENTAL

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_SIMD
int var_asc_std_simd = 7;
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_SIMD

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES
int var_asc_std_ranges = 8;
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_VIEWS
int var_asc_std_views = 9;
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_VIEWS

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(__my_cpo)
int var_cpo = 10;
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_FILESYSTEM
int var_filesystem = 11;
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_FILESYSTEM

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_EXECUTION
int var_asc_std_execution = 12;
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_EXECUTION

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_EXECUTION
int var_asc_execution = 13;
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_EXECUTION

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_ARGUMENT
int var_asc_argument = 14;
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_ARGUMENT

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_STD
int var_std = 15;
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_STD

int main()
{
    expect_eq("asc::std::var_asc_std_noversion", asc::std::var_asc_std_noversion, 1);
    expect_eq("asc::std::var_asc_std", asc::std::var_asc_std, 2);
    expect_eq("asc::var_asc", asc::var_asc, 3);
    expect_eq("asc::mr::var_asc_mr", asc::mr::var_asc_mr, 4);
    expect_eq("asc::device::var_asc_device", asc::device::var_asc_device, 5);
    expect_eq("asc::device::experimental::var_asc_device_exp", asc::device::experimental::var_asc_device_exp, 6);
    expect_eq("asc::std::simd::var_asc_std_simd", asc::std::simd::var_asc_std_simd, 7);
    expect_eq("asc::std::ranges::var_asc_std_ranges", asc::std::ranges::var_asc_std_ranges, 8);
    expect_eq("asc::std::ranges::views::var_asc_std_views", asc::std::ranges::views::var_asc_std_views, 9);
    expect_eq("__my_cpo::var_cpo", __my_cpo::var_cpo, 10);
    expect_eq("asc::std::filesystem::var_filesystem", asc::std::filesystem::var_filesystem, 11);
    expect_eq("asc::std::execution::var_asc_std_execution", asc::std::execution::var_asc_std_execution, 12);
    expect_eq("asc::execution::var_asc_execution", asc::execution::var_asc_execution, 13);
    expect_eq("asc::__argument::var_asc_argument", asc::__argument::var_asc_argument, 14);
    expect_eq("std::var_std", std::var_std, 15);

    return g_failures == 0 ? 0 : 1;
}
