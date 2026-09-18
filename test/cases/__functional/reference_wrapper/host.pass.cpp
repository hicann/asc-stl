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

#include <asc/std/__fwd/reference_wrapper.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][reference_wrapper] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][reference_wrapper] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

int main()
{
    // __is_asc_std_reference_wrapper_v should be false for non-reference_wrapper types
    expect_false("__is_asc_std_reference_wrapper_v<int>", asc::std::__is_asc_std_reference_wrapper_v<int>);
    expect_false("__is_asc_std_reference_wrapper_v<double>", asc::std::__is_asc_std_reference_wrapper_v<double>);
    expect_false("__is_asc_std_reference_wrapper_v<float>", asc::std::__is_asc_std_reference_wrapper_v<float>);
    expect_false("__is_asc_std_reference_wrapper_v<void*>", asc::std::__is_asc_std_reference_wrapper_v<void*>);

    // __is_asc_std_reference_wrapper_v should be true for reference_wrapper<T> types
    expect_true("__is_asc_std_reference_wrapper_v<reference_wrapper<int>>",
        asc::std::__is_asc_std_reference_wrapper_v<asc::std::reference_wrapper<int>>);
    expect_true("__is_asc_std_reference_wrapper_v<reference_wrapper<double>>",
        asc::std::__is_asc_std_reference_wrapper_v<asc::std::reference_wrapper<double>>);
    expect_true("__is_asc_std_reference_wrapper_v<reference_wrapper<float>>",
        asc::std::__is_asc_std_reference_wrapper_v<asc::std::reference_wrapper<float>>);

    return g_failures == 0 ? 0 : 1;
}
