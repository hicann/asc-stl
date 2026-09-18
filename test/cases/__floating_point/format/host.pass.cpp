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

#include <asc/std/__floating_point/format.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_eq_fmt(const char* expr, asc::std::__fp_format got, asc::std::__fp_format expected)
{
    bool ok = (got == expected);
    std::cout << "[host][format] " << expr << " = " << static_cast<int>(got) << " (expected "
              << static_cast<int>(expected) << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // Basic floating-point type format detection via variable template
    expect_eq_fmt("__fp_format_of_v<float>", asc::std::__fp_format_of_v<float>, asc::std::__fp_format::__binary32);
    expect_eq_fmt("__fp_format_of_v<double>", asc::std::__fp_format_of_v<double>, asc::std::__fp_format::__binary64);

    // Non-floating-point types return __invalid
    expect_eq_fmt("__fp_format_of_v<int>", asc::std::__fp_format_of_v<int>, asc::std::__fp_format::__invalid);
    expect_eq_fmt("__fp_format_of_v<char>", asc::std::__fp_format_of_v<char>, asc::std::__fp_format::__invalid);
    expect_eq_fmt("__fp_format_of_v<long>", asc::std::__fp_format_of_v<long>, asc::std::__fp_format::__invalid);

    // cv-qualified versions propagate the format
    expect_eq_fmt(
        "__fp_format_of_v<const float>", asc::std::__fp_format_of_v<const float>, asc::std::__fp_format::__binary32);
    expect_eq_fmt("__fp_format_of_v<volatile double>", asc::std::__fp_format_of_v<volatile double>,
        asc::std::__fp_format::__binary64);
    expect_eq_fmt("__fp_format_of_v<const volatile float>", asc::std::__fp_format_of_v<const volatile float>,
        asc::std::__fp_format::__binary32);

    // __fp_format_of_v_impl function template (direct call)
    expect_eq_fmt(
        "__fp_format_of_v_impl<float>()", asc::std::__fp_format_of_v_impl<float>(), asc::std::__fp_format::__binary32);
    expect_eq_fmt("__fp_format_of_v_impl<double>()", asc::std::__fp_format_of_v_impl<double>(),
        asc::std::__fp_format::__binary64);
    expect_eq_fmt(
        "__fp_format_of_v_impl<int>()", asc::std::__fp_format_of_v_impl<int>(), asc::std::__fp_format::__invalid);

    // __asc_fp specialization returns the format directly
    expect_eq_fmt("__fp_format_of_v<__asc_fp<__binary16>>",
        asc::std::__fp_format_of_v<asc::std::__asc_fp<asc::std::__fp_format::__binary16>>,
        asc::std::__fp_format::__binary16);
    expect_eq_fmt("__fp_format_of_v<__asc_fp<__binary32>>",
        asc::std::__fp_format_of_v<asc::std::__asc_fp<asc::std::__fp_format::__binary32>>,
        asc::std::__fp_format::__binary32);
    expect_eq_fmt("__fp_format_of_v<__asc_fp<__binary64>>",
        asc::std::__fp_format_of_v<asc::std::__asc_fp<asc::std::__fp_format::__binary64>>,
        asc::std::__fp_format::__binary64);
    expect_eq_fmt("__fp_format_of_v<__asc_fp<__invalid>>",
        asc::std::__fp_format_of_v<asc::std::__asc_fp<asc::std::__fp_format::__invalid>>,
        asc::std::__fp_format::__invalid);

    // __fp_format is an enum class
    expect_eq_fmt("is_enum check (cast)",
        std::is_enum_v<asc::std::__fp_format> ? asc::std::__fp_format::__binary32 : asc::std::__fp_format::__invalid,
        asc::std::__fp_format::__binary32);

    return g_failures == 0 ? 0 : 1;
}
