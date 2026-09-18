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

#include <asc/std/__host_stdlib/math.h>
#include <iostream>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][math] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_near(const char* expr, double got, double expected, double tol = 1e-9)
{
    bool ok = fabs(got - expected) < tol;
    std::cout << "[host][math] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool ok)
{
    std::cout << "[host][math] " << expr << " = " << (ok ? "true" : "false") << " (expected true) "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void test_header_wraps_host_math()
{
    // This header wraps the host <math.h> and validates that the C++
    // compatible version (not the C macro version) is included.
    // Verify that standard math functions are accessible after including it.
}

static void test_basic_arithmetic_power_functions()
{
    // --- Basic arithmetic / power functions ---
    expect_near("fabs(-3.0)", fabs(-3.0), 3.0);
    expect_near("sqrt(16.0)", sqrt(16.0), 4.0);
    expect_near("cbrt(27.0)", cbrt(27.0), 3.0);
    expect_near("pow(2.0, 10.0)", pow(2.0, 10.0), 1024.0);
    expect_near("exp(0.0)", exp(0.0), 1.0);
    expect_near("exp2(3.0)", exp2(3.0), 8.0);
    expect_near("expm1(0.0)", expm1(0.0), 0.0);
    expect_near("log(1.0)", log(1.0), 0.0);
    expect_near("log2(8.0)", log2(8.0), 3.0);
    expect_near("log10(1000.0)", log10(1000.0), 3.0);
    expect_near("log1p(0.0)", log1p(0.0), 0.0);
    expect_near("hypot(3.0, 4.0)", hypot(3.0, 4.0), 5.0);
}

static void test_trigonometric_functions()
{
    // --- Trigonometric functions ---
    expect_near("sin(0.0)", sin(0.0), 0.0);
    expect_near("cos(0.0)", cos(0.0), 1.0);
    expect_near("tan(0.0)", tan(0.0), 0.0);
    expect_near("asin(0.0)", asin(0.0), 0.0);
    expect_near("acos(1.0)", acos(1.0), 0.0);
    expect_near("atan(0.0)", atan(0.0), 0.0);
    expect_near("atan2(0.0, 1.0)", atan2(0.0, 1.0), 0.0);
}

static void test_hyperbolic_functions()
{
    // --- Hyperbolic functions ---
    expect_near("sinh(0.0)", sinh(0.0), 0.0);
    expect_near("cosh(0.0)", cosh(0.0), 1.0);
    expect_near("tanh(0.0)", tanh(0.0), 0.0);
    expect_near("asinh(0.0)", asinh(0.0), 0.0);
    expect_near("acosh(1.0)", acosh(1.0), 0.0);
    expect_near("atanh(0.0)", atanh(0.0), 0.0);
}

static void test_rounding_floor_ceil()
{
    // --- Rounding / floor / ceil ---
    expect_near("ceil(2.3)", ceil(2.3), 3.0);
    expect_near("floor(2.7)", floor(2.7), 2.0);
    expect_near("trunc(2.9)", trunc(2.9), 2.0);
    expect_near("round(2.5)", round(2.5), 3.0);
    expect_near("round(2.4)", round(2.4), 2.0);
    expect_near("nearbyint(2.6)", nearbyint(2.6), 3.0);
}

static void test_fmin_fmax_fmod_fdim()
{
    // --- fmin / fmax / fmod / fdim ---
    expect_near("fmax(3.0, 5.0)", fmax(3.0, 5.0), 5.0);
    expect_near("fmin(3.0, 5.0)", fmin(3.0, 5.0), 3.0);
    expect_near("fmod(10.0, 3.0)", fmod(10.0, 3.0), 1.0);
    expect_near("fdim(5.0, 3.0)", fdim(5.0, 3.0), 2.0);
    expect_near("fdim(3.0, 5.0)", fdim(3.0, 5.0), 0.0);
}

static void test_fma_fused_multiply_add()
{
    // --- fma (fused multiply-add) ---
    expect_near("fma(2.0, 3.0, 1.0)", fma(2.0, 3.0, 1.0), 7.0);
}

static void test_copysign()
{
    // --- copysign ---
    expect_near("copysign(3.0, -1.0)", copysign(3.0, -1.0), -3.0);
    expect_near("copysign(3.0, 1.0)", copysign(3.0, 1.0), 3.0);
}

static void test_error_gamma_functions()
{
    // --- Error / gamma functions ---
    expect_near("erf(0.0)", erf(0.0), 0.0);
    expect_near("erfc(0.0)", erfc(0.0), 1.0);
    expect_near("tgamma(1.0)", tgamma(1.0), 1.0);
    expect_near("tgamma(5.0)", tgamma(5.0), 24.0);
    expect_near("lgamma(1.0)", lgamma(1.0), 0.0);
}

static void test_ldexp_frexp_scalbn()
{
    // --- ldexp / frexp / scalbn ---
    expect_near("ldexp(1.5, 2)", ldexp(1.5, 2), 6.0);
    expect_near("scalbn(1.5, 1)", scalbn(1.5, 1), 3.0);
}

static void test_nextafter()
{
    // --- nextafter ---
    expect_true("nextafter(1.0, 2.0) > 1.0", nextafter(1.0, 2.0) > 1.0);
    expect_true("nextafter(1.0, 0.0) < 1.0", nextafter(1.0, 0.0) < 1.0);
}

static void test_classification_functions_return_int()
{
    // --- Classification functions (return int/bool) ---
    expect_eq("isnan(0.0)", (int)isnan(0.0), 0);            // NOLINT(readability/casting)
    expect_eq("isinf(HUGE_VAL)", (int)isinf(HUGE_VAL), 1);  // NOLINT(readability/casting)
    expect_eq("isfinite(1.0)", (int)isfinite(1.0), 1);      // NOLINT(readability/casting)
    expect_eq("isnormal(1.0)", (int)isnormal(1.0), 1);      // NOLINT(readability/casting)
    expect_eq("signbit(-1.0)", (int)signbit(-1.0), 1);      // NOLINT(readability/casting)
    expect_eq("signbit(1.0)", (int)signbit(1.0), 0);        // NOLINT(readability/casting)
}

int main()
{
    test_header_wraps_host_math();
    test_basic_arithmetic_power_functions();
    test_trigonometric_functions();
    test_hyperbolic_functions();
    test_rounding_floor_ceil();
    test_fmin_fmax_fmod_fdim();
    test_fma_fused_multiply_add();
    test_copysign();
    test_error_gamma_functions();
    test_ldexp_frexp_scalbn();
    test_nextafter();
    test_classification_functions_return_int();

    return g_failures == 0 ? 0 : 1;
}
