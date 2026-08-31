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

#include <asc/__fwd/complex.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][complex] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][complex] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

int main()
{
    expect_true("__is_asc_complex_v<complex<float>>", asc::__is_asc_complex_v<asc::complex<float>>);
    expect_true("__is_asc_complex_v<complex<double>>", asc::__is_asc_complex_v<asc::complex<double>>);
    expect_true("__is_asc_complex_v<const complex<float>>", asc::__is_asc_complex_v<const asc::complex<float>>);
    expect_true("__is_asc_complex_v<volatile complex<float>>", asc::__is_asc_complex_v<volatile asc::complex<float>>);
    expect_true("__is_asc_complex_v<const volatile complex<float>>",
        asc::__is_asc_complex_v<const volatile asc::complex<float>>);

    expect_false("__is_asc_complex_v<float>", asc::__is_asc_complex_v<float>);
    expect_false("__is_asc_complex_v<int>", asc::__is_asc_complex_v<int>);
    expect_false("__is_asc_complex_v<double>", asc::__is_asc_complex_v<double>);

    return g_failures == 0 ? 0 : 1;
}
