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

#include <asc/std/__fwd/complex.h>
#include <complex>
#include <iostream>

static int g_failures = 0;

static void report(const char* trait, bool got, bool expected)
{
    const bool ok = (got == expected);
    std::cout << "[host][fwd.complex] " << trait << ": " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void test_std_complex_trait_matches()
{
    report("__is_std_complex_v<std::complex<float>>", asc::std::__is_std_complex_v<::std::complex<float>>, true);
    report("__is_std_complex_v<std::complex<double>>", asc::std::__is_std_complex_v<::std::complex<double>>, true);
    report("__is_std_complex_v<std::complex<long double>>", asc::std::__is_std_complex_v<::std::complex<long double>>,
        true);
}

static void test_std_complex_trait_rejects_non_complex()
{
    report("__is_std_complex_v<float>", asc::std::__is_std_complex_v<float>, false);
    report("__is_std_complex_v<int>", asc::std::__is_std_complex_v<int>, false);
    report("__is_std_complex_v<double>", asc::std::__is_std_complex_v<double>, false);
}

static void test_std_complex_trait_cv_propagation()
{
    report("__is_std_complex_v<const std::complex<float>>", asc::std::__is_std_complex_v<const ::std::complex<float>>,
        true);
    report("__is_std_complex_v<volatile std::complex<double>>",
        asc::std::__is_std_complex_v<volatile ::std::complex<double>>, true);
    report("__is_std_complex_v<const volatile std::complex<float>>",
        asc::std::__is_std_complex_v<const volatile ::std::complex<float>>, true);
    report("__is_std_complex_v<const float>", asc::std::__is_std_complex_v<const float>, false);
}

static void test_asc_std_complex_is_separate_domain()
{
    // asc::std::complex is the ASC-STL forward declaration and is not the
    // hosted ::std::complex specialization the trait recognizes.
    report(
        "__is_std_complex_v<asc::std::complex<float>>", asc::std::__is_std_complex_v<asc::std::complex<float>>, false);
}

static void test_incomplete_type_usable()
{
    const asc::std::complex<double>* null_cplx = nullptr;
    report("pointer to incomplete asc::std::complex is null", null_cplx == nullptr, true);
}

int main()
{
    test_std_complex_trait_matches();
    test_std_complex_trait_rejects_non_complex();
    test_std_complex_trait_cv_propagation();
    test_asc_std_complex_is_separate_domain();
    test_incomplete_type_usable();

    return g_failures == 0 ? 0 : 1;
}
